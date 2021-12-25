#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdio>
#include <stdint.h>
#include <vector>

enum employee_type {
    DEVELOPER = 1,
    SALES_MANAGER
};

class Employee {
public:
    virtual ~Employee() {};
    virtual int salary() const = 0;
    friend std::istream& operator>>(std::istream& in, Employee &e);
    friend std::ostream& operator<<(std::ostream& out, const Employee &e);
    friend std::ifstream& operator>>(std::ifstream& in, Employee &e);
    friend std::ofstream& operator<<(std::ofstream& out, const Employee &e);
protected:
    virtual void input(std::istream& in);
    virtual void output(std::ostream& out) const;
    virtual void input(std::ifstream& in);
    virtual void output(std::ofstream& out) const;
    std::string _name;
    int32_t _base_salary;
    const int32_t MAX_NAME_SIZE = 110;
};

class Developer : public Employee {
public:
    int salary() const override;
    void input(std::istream& in) override;
    void output(std::ostream& out) const override;
    void input(std::ifstream& in) override;
    void output(std::ofstream& out) const override;
private:
    bool _has_bonus;
};

class SalesManager : public Employee {
public:
    int salary() const override;
    void input(std::istream& in) override;
    void output(std::ostream& out) const override;
    void input(std::ifstream& in) override;
    void output(std::ofstream& out) const override;
private:
    int32_t _sold_nm, _price;
};

class EmployeesArray {
public:
    ~EmployeesArray();
    void add(Employee *e);
    int total_salary() const;

    friend std::ifstream &operator>>(std::ifstream &in, EmployeesArray &arr);
    friend std::ofstream &operator<<(std::ofstream &out, const EmployeesArray &arr);
    friend std::ostream &operator<<(std::ostream &out, const EmployeesArray &arr);
private:
    std::vector<Employee*> _employees;
};

Employee* build_employee(employee_type t);

#endif
