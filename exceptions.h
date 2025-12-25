#pragma once
#include <iostream>
#include <exception>

using namespace std;

class Insert_error : public exception {
public:
	Insert_error(const string& d = " Greska pri unosu.") :description(d) {}
	const char* what()const override { return description.c_str(); }
private:
	string description;
};
class Delete_error : public exception {
public:
	Delete_error(const string& d = " Greska pri brisanju") :description(d) {}
	const char* what()const override { return description.c_str(); }
private:
	string description;
};
class Invalid_division : public exception {
public:
	Invalid_division(const string& d = " Greska: deljenje sa 0.") :description(d) {}
	const char* what()const override { return description.c_str(); }
private:
	string description;
};
class Menu_error : public exception {
public:
	Menu_error(const string& d = " Greska pri odabiru opcija u meniju.") :description(d) {}
	const char* what()const override { return description.c_str(); }
private:
	string description;
};