#include <iostream>
#include <fstream>
#include <string>
#include "FLIST.h"


template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message = "");
ushort task_menu();
void print_olders(const FLIST& list);
void print_by_salary(const FLIST& list, const uint n);
void print_by_department(const FLIST& list, const std::string& dept);
ptrWorker read_and_check();
void read_string(const char* message, std::string& str);


int main()
{
	std::ifstream inp_file("data.txt");
	FLIST list(inp_file);
    inp_file.close();
    ushort choice{};
    do
    {
        choice = task_menu();
        switch (choice)
        {
        case 1:
            list.print();
            break;
        case 2:
        {
            ptrWorker w = read_and_check();
            list.add_to_tail(w);
            std::ofstream out_file("data.txt", std::ios::app);
            w->print(out_file);
            out_file.close();
            break;
        }
        case 3:
            print_olders(list);
            break;
        case 4:
        {
            uint n{};
            validation(n, [](uint x) {return x > 0; }, "Enter N");
            print_by_salary(list, n);
            break;
        }
        case 5:
        {
            std::string dept{};
            validation(dept, [](std::string x) {return true; }, "Enter department");
            print_by_department(list, dept);
            break;
        }
        }
    } while (choice != 6);
    
}


template<typename T, typename Predicat>
void validation(T& x, Predicat condition, const char* message)
{
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cout << message << "\n>>> ";
    while (!(std::cin >> x && condition(x)))
    {
        std::cout << "Input error!" << '\n';
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << message << "\n>>> ";
    }
}

ushort task_menu()
{
    std::cout << "\n*-<===> Task Menu <===>-*\n" <<
        "1. Print to console\n" <<
        "2. Add new worker\n" <<
        "3. Print retirement age workers\n" <<
        "4. Print workers whose salary at least N\n" <<
        "5. Print workers from specified department\n" <<
        "6. Exit\n";
    short res{};
    validation(res, [](short x) {return x >= 1 && x <= 6; });
    return res;
}

void print_olders(const FLIST& list)
{
    std::cout << "Retirement age workers:\n";
    ptrNODE ptr = list.get_head()->next;
    bool printed = false;
    while (ptr)
    {
        if (ptr->info->get_sex() == false && ptr->info->get_age() >= 58)
        {
            ptr->info->print();
            if (!printed)
                printed = true;
        }
        if (ptr->info->get_sex() == true && ptr->info->get_age() >= 63)
        {
            ptr->info->print();
            if (!printed)
                printed = true;
        }
        ptr = ptr->next;
    }
    if (!printed)
        std::cout << "There're no retirement age workers\n";
}

void print_by_salary(const FLIST& list, const uint n)
{
    std::cout << "Workers whose salary at least " << n << ":\n";
    ptrNODE ptr = list.get_head()->next;
    bool printed = false;
    while (ptr)
    {
        if (ptr->info->get_salary() >= n)
        {
            ptr->info->print();
            if (!printed)
                printed = true;
        }
        ptr = ptr->next;
    }
    if (!printed)
        std::cout << "There're no workers whose salary at least " << n << '\n';
}

void print_by_department(const FLIST& list, const std::string& dept)
{
    std::cout << "workers from " << dept << " department:\n";
    ptrNODE ptr = list.get_head()->next;
    bool printed = false;
    while (ptr)
    {
        if (ptr->info->get_dept() == dept)
        {
            ptr->info->print();
            if (!printed)
                printed = true;
        }
        ptr = ptr->next;
    }
    if (!printed)
        std::cout << "There're no workers from " << dept << " department\n";
}

ptrWorker read_and_check()
{
    std::string name{}, address{}, phone_number{}, dept{}, post{}, sex_str{};
    bool sex{};
    ushort age{}, years{};
    uint salary{};
    read_string("Enter name", name);
    validation(sex_str, [](std::string str) {return str == "Male" || str == "male" || str == "Female" || str == "female"; }, "Enter sex");
    (sex_str == "Male" || sex_str == "male") ? sex = true : sex = false;
    validation(age, [](ushort x) {return x >= 18; }, "Enter age");
    read_string("Enter address", address);
    read_string("Enter phone number", phone_number);
    read_string("Enter department", dept);
    read_string("Enter post", post);
    validation(years, [age](ushort x) {return x + age >= 18; }, "Enter count of years in the company");
    validation(salary, [](uint x) { return x > 0; }, "Enter salary");
    return new Worker(name, sex, age, address, phone_number, dept, post, years, salary);
}

void read_string(const char* message, std::string& str)
{
    std::cout << message << "\n>>> ";
    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::getline(std::cin, str);
}
