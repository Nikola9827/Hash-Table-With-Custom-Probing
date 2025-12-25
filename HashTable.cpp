#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "HashTable.h"
#include "dz3p1.h"
#include "AddressFunction.h"
#include "exceptions.h"

using namespace std;

void HashTable::copy(const HashTable& ht) {
	n = ht.n;
	success_find_prob = ht.success_find_prob;
	unsuccess_find = ht.unsuccess_find;
	unsuccess_find_count = ht.unsuccess_find_count;
	records = new Info * [n];
	for (int i = 0; i < n; i++) {
		*records[i] = *ht.records[i];
	}
}
void HashTable::move(HashTable& ht) {
	n = ht.n;
	success_find_prob = ht.success_find_prob;
	unsuccess_find = ht.unsuccess_find;
	unsuccess_find_count = ht.unsuccess_find_count;
	records = ht.records;
	ht.records = nullptr;
}
void HashTable::remove() {
	for (int i = 0; i < n; delete records[i++]);
	delete[] records;
}

int HashTable::HashFunction(int K)const {
	double c = 0.61803;								//Golden Ratio
	return static_cast<int>(n * fmod(c * K, 1));
}
int HashTable::Find(const string& k, int& i) {
	i = 1;
	int address = HashFunction(Key(k));
	int temp_address = address;
	vector<int> v;
	while (records[temp_address]) {		//records[address]->Key() != k
		//for (int x : v)if (x == temp_address)return -1;
		if (!records[temp_address]->deleted && records[temp_address]->getKey() == k)break;	//samo u ovom slucaju nije kilizija, a da nije nullptr
		else {
			SplitSequenceLinearHashing af(Key(records[temp_address]->getKey()));
			temp_address = af.getAddress(Key(k), address, i, n);
			for (int x : v)if (x == temp_address)return -1;
			v.push_back(temp_address);
		}
	}
	return temp_address;
}
Info* HashTable::findKey(const string& k) {
	/*int address = HashFunction(Key(k)), i = 0;
	vector<int> v;
	while (records[address]) {		//records[address]->Key() != k
		for (int x : v)if (x == address)return nullptr;
		if (!records[address]->deleted && records[address]->Key()==k)break;	//samo u ovom slucaju nije kilizija, a da nije nullptr
		else {
			SplitSequenceLinearHashing af(Key(records[address]->Key()));	//
			address = af.getAddress(Key(k), address, i, n);					//ne valja
			v.push_back(address);
		}
	}
	return records[address];*/
	int i;
	int address = Find(k, i);
	if (address == -1) { unsuccess_find += i; unsuccess_find_count++; return nullptr; }
	else if (!records[address]) { unsuccess_find += i; unsuccess_find_count++; }
	return records[address];
}
bool HashTable::insertKey(Info& info) try {
	if (keyCount() == n) throw Insert_error(" Hes tabela je puna.");
	string k = info.getKey();
	int i = 1;
	int address = HashFunction(Key(k));
	int temp_address = address;
	vector<int> v;
	while (records[temp_address]) {		//records[address]->Key() != k
		/*for (int x : v)if (x == temp_address) {
			unsuccess_find += i; unsuccess_find_count++; throw Insert_error(" Hes tabela je puna."); }*/
		if (records[temp_address]->deleted) {  	//ako je deleted true moze na tom mestu da se unosi
			delete records[temp_address];
			records[temp_address] = nullptr;
			break;
		}
		else if (records[temp_address]->getKey() == k) throw Insert_error(" Kljuc vec postoji u hes tabeli.");
		else {
			SplitSequenceLinearHashing af(Key(records[temp_address]->getKey()));
			temp_address = af.getAddress(Key(k), address, i, n);				//jeste dobro
			for (int x : v)if (x == temp_address) {
				unsuccess_find += i; unsuccess_find_count++; throw Insert_error(" Hes tabela je puna.");
			}
			v.push_back(temp_address);
		}
	}
	unsuccess_find += i; unsuccess_find_count++;
	success_find_prob += i;
	records[temp_address] = &info;		//treba mi sa nullptr da tu ubacim
	return true;
}
catch (Insert_error & ie) {
	cout << ie.what() << endl;
	return false;
}
bool HashTable::deleteKey(const string& k) try {
	if (keyCount() == 0) throw Delete_error(" Hes tabela je prazna");
	int i;
	int address = Find(k, i);
	if (address == -1 || !records[address]) { unsuccess_find += i; unsuccess_find_count++; throw Delete_error(" Kljuc ne postoji u hes tabeli."); }
	records[address]->deleted = true;
	return true;
}
catch (Delete_error & de) {
	cout << de.what() << endl;
	return false;
}
double HashTable::avgAccessSuccess()const try {
	if (!keyCount())throw Invalid_division(" Nema kljuceva u tabeli.");
	return success_find_prob * 1.0 / keyCount(); 
}
catch (Invalid_division & id) {
	cout << id.what() << endl;
	return 0;
}
double HashTable::avgAccessUnsuccess()const try {
	if (!unsuccess_find_count)throw Invalid_division(" Nije se desila neuspesna pretraga.\n");
	return unsuccess_find * 1.0 / unsuccess_find_count;
}
catch (Invalid_division & id) {
	cout << id.what() << endl;
	return 0;
}
double HashTable::avgAccessUnsuccessEst()const try {
	double x = 1.0 - fillRatio();
	if (!x)throw Invalid_division(" Tabela je puna.");
	return 1.0 / (1.0 - fillRatio());
}
catch (Invalid_division & id) {
	cout << id.what() << endl;
	return 0;
}
void HashTable::clear() {
	for (int i = 0; i < n; i++) {
		if (records[i])records[i]->deleted = true;
	}
	resetStatistics();
}
int HashTable::keyCount()const {	//moze i da se azurira sa svakim unosim i brisanjem pa do ovo bude geter
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (records[i]) {
			if (!records[i]->deleted)sum++;
		}
	}
	return sum;
}
int HashTable::tableSize()const {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (records[i]) {
			if(!records[i]->deleted) sum += records[i]->Size();
		}
	}
	return sum;
}