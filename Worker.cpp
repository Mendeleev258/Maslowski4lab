#pragma once
#include "Worker.h"

Worker::Worker(std::string name, bool sex, ushort age, std::string address, std::string phone_number, std::string dept, std::string post, ushort years, uint salary)
{
	this->name = name;
	this->sex = sex;
	this->age = age;
	this->address = address;
	this->phone_number = phone_number;
	this->dept = dept;
	this->post = post;
	this->years = years;
	this->salary = salary;
}

Worker::Worker(std::ifstream& file)
{
	std::getline(file, name);

	std::string sex_str;
	std::getline(file, sex_str);
	(sex_str == "Male" || sex_str == "male") ? sex = true : sex = false;

	file >> age;
	file.ignore();
	std::getline(file, address);
	std::getline(file, phone_number);
	std::getline(file, dept);
	std::getline(file, post);
	file >> years;
	file.ignore();
	file >> salary;
	file.ignore();
	if (!file.eof())
	{
		std::string delim_line;
		std::getline(file, delim_line);
	}
	if (file.peek() == '\n')
		file.ignore();
}

void Worker::print(std::ostream& stream) const
{
	stream << name << '\n' <<
		get_sex_str() << '\n' <<
		age << '\n' <<
		address << '\n' <<
		phone_number << '\n' <<
		dept << '\n' <<
		post << '\n' <<
		years << '\n' <<
		salary << '\n' <<
		"========================\n";
}