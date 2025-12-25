#pragma once
#include <iostream>

using namespace std;

class AddressFunction {
public:
	virtual int getAddress(int k, int address, int& i, int n) = 0;
	virtual ~AddressFunction(){}
};

class SplitSequenceLinearHashing : public AddressFunction {
public:
	SplitSequenceLinearHashing(int k1, int s1 = 67, int s2 =71 ) :s1(s1), s2(s2), k1(k1) {}
	int getAddress(int k2, int address, int& i, int n) override {
		return static_cast<int>(fmod((address + (k2 < k1 ? s1 : s2) * i++), n));
	}
private:
	int s1, s2, k1;
};