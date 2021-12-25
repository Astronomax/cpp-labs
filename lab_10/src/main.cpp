#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cassert>
#include "employees.h"

int main(int, char **) {
    EmployeesArray employees;
    std::string cmd;
    while (std::cin >> cmd) {
        if (cmd == "exit") {
            break;
        } else if (cmd == "load") {
            std::string path;
            std::cin >> path;
            std::ifstream in(path);
            in >> employees;
            in.close();
        } else if (cmd == "save") {
            std::string path;
            std::cin >> path;
            std::ofstream out(path);
            out << employees;
            out.close();
        } else if (cmd == "add") {
            int t; std::cin >> t;
            Employee* _employee = build_employee(static_cast<employee_type>(t));
            std::cin >> *_employee;
            employees.add(_employee);
        } else if (cmd == "list") {
            std::cout << employees;
        }
    }
    return 0;
}
