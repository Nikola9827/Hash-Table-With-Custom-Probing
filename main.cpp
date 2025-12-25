#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "HashTable.h"
#include "dz3p1.h"
#include "AddressFunction.h"
#include "exceptions.h"

using namespace std;

int Key(const string& s) {
	int sum = 0;
	for (char x : s) sum += static_cast<int>(x);
	return sum;
}

void Insert(HashTable& ht) {
	int c;
	cout << " Umetanje u hash tabelu:\n 0. Iz datoteke\n 1. Sa tastature\n\n Izaberite jednu od opcija navodeci njen broj: ";
	cin >> c;
	cout << endl;
	if (c) {
		cout << " Unesite iformacije koje su potrebne za hes tabelu (da bi se unos zavrsio potrebno je uneti \"stop\"): " << endl << endl;
		bool q = true;
		while (true) {
			string original_language, original_title, release_date, revenue, runtime;
			cout << " Original language: ";
			if (q) { cin.ignore(); q = false; }
			getline(cin, original_language);
			cout << endl;
			if (original_language == "stop") break;
			cout << " Original title: ";
			getline(cin, original_title);
			cout << endl;
			if (original_title == "stop") break;
			cout << " Release date: ";
			getline(cin, release_date);
			cout << endl;
			if (release_date == "stop") break;
			cout << " Revenue: ";
			getline(cin, revenue);
			cout << endl;
			if (revenue == "stop") break;
			cout << " Runtime: ";
			getline(cin, runtime);
			cout << endl;
			if (runtime == "stop") break;
			Info* temp_info_p = new Info(original_language, original_title, release_date, revenue, runtime);
			if (ht.insertKey(*temp_info_p))cout << " Kljuc je uspesno umetnut." << endl;
			else cout << " Kljuc nije uspesno umetnut." << endl;
			cout << "_____________________________________" << endl;
		}
	}
	else {
		string name;
		fstream file;
		cout << " Unesite ime datoteke za unos: ";
		cin >> name;
		cout << endl;
		file.open(name, ios::in);
		string line;
		int i = 1;
		vector<string>v;
		while (getline(file, line) && ht.keyCount()<ht.getn()) {
			stringstream s(line);
			string data;
			while (getline(s, data, ',')) {
				v.push_back(data);
			}
			if (v.size() != 5) {
				cout << " Greska pri citanju " << i << ". reda." << endl;
				v.clear();
				i++;
				continue;
			}
			Info* temp_info_p = new Info(v[0], v[1], v[2], v[3], v[4]);
			ht.insertKey(*temp_info_p);
			v.clear();
			i++;
		}
		file.close();
	}
	cout << " Umetanje je zavrseno." << endl << endl;
}

void TestFunction(const vector<Info*>& v1, const vector<string>& v2, HashTable* ht) {
	for (Info* x : v1) {
		ht->insertKey(*x);
		if (ht->getn() == ht->keyCount())break;
	}
	for (string x : v2) {
		Info* tmp_info= ht->findKey(x);
		if (tmp_info)cout << " Kljuc " << x << " postoji u hes tabeli i pokazuje na zapis:" << endl << *tmp_info << endl;
		else cout << " Kljuc " << x << " ne postoji u hes tabeli." << endl;
	}
	cout << endl;
	cout << *ht << endl;
	cout << " Prosecan br. pristupa tabeli prilikom uspesnog trazenja je: " << ht->avgAccessSuccess() << endl;
	cout << " Prosecan br.pristupa tabeli prilikom neuspesnog trazenja je: " << ht->avgAccessUnsuccess() << endl;
	cout << " Procena prosecnog br.pristupa tabeli prilikom neuspesnog trazenja je: " << ht->avgAccessUnsuccessEst() << endl;
}

int main() {
	HashTable* h_table = nullptr;
	bool c = true;
	while (c) {
		try {
			int u;
			cout << "____________________________________________________________________________" << endl << endl;
			cout << " 0.  Stvaranje hes tabele\n 1.  Umetanje kljuca u hes tabelu\n 2.  Brisanje kljuca iz hes tabele\n 3.  Pretraga na zadati kjluc\n 4.  Prosecan br. pristupa tabeli prilikom uspesnog trazenja\n 5.  Prosecan br. pristupa tabeli prilikom neuspesnog trazenja\n 6.  Procena prosecnog br. pristupa tabeli prilikom neuspesnog trazenja\n 7.  Resetovanje podataka za neuspesnu pretragu\n 8.  Brisanje svih kjluceva\n 9.  Broj kjuceva\n 10. Velicina hes tabele\n 11. Ispis hes tabele\n 12. Stepen popunjenosti hes tabele\n 13. Pokreni funkciju za testiranje\n 14. Brisanje tabele\n 15. Zavrsetak programa\n\n Izaberite jednu od opcija navodeci njen broj: ";
			cin >> u;
			cout << endl;
			switch (u) {
			case 0: {
				if (h_table) throw Menu_error(" Objekat HashTabele vec postoji.");
				int n;
				while (true) {
					cout << " Unesite velicinu Hes tabele: ";
					cin >> n;
					cout << endl;
					if (n > 0) break;
					cout << " Vrednost nije validna, pokusajte ponovo. " << endl << endl;
				}
				h_table = new HashTable(n);
			}
				  break;
			case 1: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				Insert(*h_table);
			}
				  break;
			case 2: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				string key;
				cout << " Unesite kljuc podatka koji zelite da izbrisete: ";
				cin.ignore();
				getline(cin, key);
				if (h_table->deleteKey(key))cout << endl << " Podatak sa kljucem " << key << " je uspesno izbrisan." << endl;
				else cout << endl << " Brisanje nije izvrseno." << endl;
			}
				  break;
			case 3: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				string key;
				cout << " Unesite kjuc za pretragu: ";
				cin.ignore();
				getline(cin, key);
				Info* tmp_info = h_table->findKey(key);
				if (tmp_info)cout << endl << " Kljuc " << key << " postoji u hes tabeli i pokazuje na zapis:" << endl << *tmp_info << endl;
				else cout << endl << " Kljuc " << key << " ne postoji u hes tabeli." << endl;
			}
				  break;
			case 4: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				cout << " Prosecan br. pristupa tabeli prilikom uspesnog trazenja je: " << h_table->avgAccessSuccess() << endl;
			}
				  break;
			case 5: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				cout << " Prosecan br.pristupa tabeli prilikom neuspesnog trazenja je: " << h_table->avgAccessUnsuccess() << endl;
			}
				  break;
			case 6: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				cout << "Procena prosecnog br.pristupa tabeli prilikom neuspesnog trazenja je: " << h_table->avgAccessUnsuccessEst() << endl;
			}
				  break;
			case 7: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				h_table->resetStatistics();
				cout << " Resetovanje je izvrseno." << endl;
			}
				  break;
			case 8: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				h_table->clear();
				cout << " Brisanje svih kljuceva je izvrseno." << endl;
			}
				  break;
			case 9: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				cout << " Broj kljuceva je: " << h_table->keyCount() << endl;
			}
				  break;
			case 10: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				cout << " Velicina hes tabele je: " << h_table->tableSize() << endl;
			}
				  break;
			case 11: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				cout << *h_table << endl << endl;
			}
				   break;
			case 12: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				cout << " Stepen popunjenosti hes tabele je: " << h_table->fillRatio() << endl;
			}
				   break;
			case 13: {
				if (!h_table) throw Menu_error(" HashTabela nije stvorena.");
				int c;
				cout << " Zadavanje skupa objekata koji se umecu:\n 0. Iz datoteke\n 1. Sa tastature\n\n Izaberite jednu od opcija navodeci njen broj: ";
				cin >> c;
				cout << endl;
				vector<Info*>v1;
				if (c) {
					cout << " Unesite iformacije koje su potrebne za hes tabelu (da bi se unos zavrsio potrebno je uneti \"stop\"): " << endl;
					bool q = true;
					while (true) {
						string original_language, original_title, release_date, revenue, runtime;
						cout << " Original language: ";
						if (q) { cin.ignore(); q = false; }
						getline(cin, original_language);
						cout << endl;
						if (original_language == "stop") break;
						cout << " Original title: ";
						getline(cin, original_title);
						cout << endl;
						if (original_title == "stop") break;
						cout << " Release date: ";
						getline(cin, release_date);
						cout << endl;
						if (release_date == "stop") break;
						cout << " Revenue: ";
						getline(cin, revenue);
						cout << endl;
						if (revenue == "stop") break;
						cout << " Runtime: ";
						getline(cin, runtime);
						cout << endl;
						if (runtime == "stop") break;
						Info* temp_info_p = new Info(original_language, original_title, release_date, revenue, runtime);
						v1.push_back(temp_info_p);
						cout << "_____________________________________" << endl;
					}
				}
				else {
					string name;
					fstream file;
					cout << " Unesite ime datoteke za unos: ";
					cin >> name;
					cout << endl;
					file.open(name, ios::in);
					string line;
					int i = 1;
					vector<string>v;
					while (getline(file, line)) {
						stringstream s(line);
						string data;
						while (getline(s, data, ',')) {
							v.push_back(data);
						}
						if (v.size() != 5) {
							cout << " Greska pri citanju " << i << ". reda." << endl;
							v.clear();
							i++;
							continue;
						}
						Info* temp_info_p = new Info(v[0], v[1], v[2], v[3], v[4]);
						v1.push_back(temp_info_p);
						v.clear();
						i++;
					}
					cout << endl;
					file.close();
				}
				cout << " Zadavanje skupa kljuceva za pretragu:\n 0. Iz datoteke\n 1. Sa tastature\n\n Izaberite jednu od opcija navodeci njen broj: ";
				cin >> c;
				cout << endl;
				vector<string>v2;
				if (c) {
					cout << " Unesite kljuceve za pretragu (da bi se unos zavrsio potrebno je uneti \"stop\"): " << endl;
					bool q = true;
					while (true) {
						string key;
						if (q) { cin.ignore(); q = false; }
						getline(cin, key);
						if (key == "stop") break;
						v2.push_back(key);
						cout << "_______________" << endl;
					}
				}
				else {
					string name;
					fstream file;
					cout << " Unesite ime datoteke za unos: ";
					cin >> name;
					cout << endl;
					file.open(name, ios::in);
					string key;
					while (getline(file, key)) {
						v2.push_back(key);
					}
					file.close();
				}
				TestFunction(v1, v2, h_table);
			}
				   break;
			case 14: {
				delete h_table;
				h_table = nullptr;
				cout << " Hes tabela je izbrisana." << endl;
			}
				   break;
			case 15: {
				delete h_table;
				h_table = nullptr;
				c = false;
			}
				   break;
			default:cout << " Opcija koju ste izabrali ne postiji, pokusajte ponovo." << endl << endl;
			}
		}
		catch (Menu_error & me) { cout << me.what() << endl; }
		cout << "____________________________________________________________________________" << endl << endl;
		system("pause");
	}
}