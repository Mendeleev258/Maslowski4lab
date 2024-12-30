#pragma once
#include <iostream>
#include <fstream>
#include <string>

using ushort = unsigned short;
using uint = unsigned int;

struct Worker
{
private:
	std::string name;
	bool sex; // female = 0, male = 1
	ushort age;
	std::string address;
	std::string phone_number;
	std::string dept; // department
	std::string post;
	ushort years; // >= age + 18
	uint salary;
public:
	Worker() {}
	Worker(std::string name, bool sex, ushort age, std::string address, std::string phone_number, std::string dept, std::string post, ushort years, uint salary);
	Worker(std::ifstream& file);
	void print(std::ostream& stream = std::cout) const;
	bool get_sex() const { return sex; }
	std::string get_sex_str() const { return sex ? "Male" : "Female"; }
	std::string get_dept() const { return dept; }
	std::string get_post() const { return post; }
	ushort get_age() const { return age; }
	ushort get_years() const { return years; }
	uint get_salary() const { return salary; }
};