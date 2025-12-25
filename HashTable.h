#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Info {
	string original_language, original_title, release_date, revenue, runtime;
	bool deleted;
	Info(const string& ol, const string& ot, const string& rd, const string& rev, const string& run, bool d = false) :original_language(ol), original_title(ot), release_date(rd), revenue(rev), runtime(run), deleted(d) {}
	const string& getKey()const { return original_title; }
	int Size()const { return original_language.size() + original_title.size() + release_date.size() + revenue.size() + runtime.size(); }
	friend ostream& operator<<(ostream& os, const Info& i) {
		return os << " " << setw(5) << i.original_language << " " << setw(50) << i.original_title << " " << setw(12) << i.release_date << " " << setw(12) << i.revenue << " " << setw(4) << i.runtime;
	}
};

class HashTable {
public:
	HashTable(int pn) :n(pn), records(new Info* [n]), success_find_prob(0), unsuccess_find(0), unsuccess_find_count(0) { for (int i = 0; i < n; records[i++] = nullptr); }
	HashTable(const HashTable& ht) { copy(ht); };
	HashTable(HashTable&& ht) noexcept { move(ht); };
	~HashTable() { remove(); };
	HashTable& operator=(const HashTable& ht) {
		if (this != &ht) {
			remove();
			copy(ht);
		}
		return *this;
	};
	HashTable& operator=(HashTable&& ht) noexcept {
		if (this != &ht) {
			remove();
			move(ht);
		}
		return *this;
	};

	Info* findKey(const string&);
	bool insertKey(Info&);
	bool deleteKey(const string&);
	double avgAccessSuccess()const;
	double avgAccessUnsuccess()const;
	double avgAccessUnsuccessEst()const;
	void resetStatistics() { unsuccess_find = 0; unsuccess_find_count = 0; }
	void clear();
	int keyCount()const;
	int tableSize()const;
	friend ostream& operator<<(ostream& os, const HashTable& ht) {
		for (int i = 0; i < ht.n; i++) {
			if (!ht.records[i]) os << " EMPTY";
			else if (ht.records[i]->deleted) os << " DELETED";
			else os << *ht.records[i];
			os << endl;
		}
		return os;
	}
	double fillRatio()const { return keyCount() * 1.0 / n; }
	int getn()const { return n; }

private:
	int n, success_find_prob, unsuccess_find, unsuccess_find_count;
	Info** records;

	void copy(const HashTable&);
	void move(HashTable&);
	void remove();
	int HashFunction(int)const;
	int Find(const string&, int&);
};