#include "employees.h"

Employee* build_employee(employee_type t) {
    switch(t) {
        case (DEVELOPER):
            return new Developer();
        case (SALES_MANAGER):
            return new SalesManager();
        default:
            return new Developer();
    }
}

void Employee::input(std::istream& in) {
    in >> _name >> _base_salary;
}

void Employee::output(std::ostream& out) const {
    out << "Name: " << _name << std::endl;
    out << "Base Salary: " << _base_salary << std::endl;
}

void Employee::input(std::ifstream& in) {
    char* str = new char[MAX_NAME_SIZE];
    in.getline(str, MAX_NAME_SIZE, '\0');
    _name = std::string(str);
    in.read((char*)&_base_salary, sizeof(_base_salary));
    delete [] str;
}

void Employee::output(std::ofstream& out) const {
    out.write(_name.c_str(), sizeof(char) * (_name.size() + 1));
    out.write((char*)&_base_salary, sizeof(_base_salary));
}

std::istream& operator>>(std::istream& in, Employee &e) {
    e.input(in);
    return in;
}

std::ostream& operator<<(std::ostream& out, const Employee &e) {
    e.output(out);
    return out;
}

std::ifstream& operator>>(std::ifstream& in, Employee &e) {
    e.input(in);
    return in;
}

std::ofstream& operator<<(std::ofstream& out, const Employee &e) {
    e.output(out);
    return out;
}

std::ifstream& operator>>(std::ifstream &in,  EmployeesArray &arr) {
    int32_t n;
    in.read((char*)&n, sizeof(n));
    for(int i = 0; i < n; i++) {
        int32_t t;
        in.read((char*)&t, sizeof(t));
        Employee* _employee = build_employee(static_cast<employee_type>(t));
        in >> *_employee;
        arr._employees.push_back(_employee);
    }
    return in;
}

std::ofstream& operator<<(std::ofstream &out, const EmployeesArray &arr) {
    int32_t* temp = new int32_t(arr._employees.size());
    out.write((char*)temp, sizeof(int32_t));
    delete temp;
    for(auto &i : arr._employees)
        out << *i;
    return out;
}

std::ostream& operator<<(std::ostream& out, const EmployeesArray &arr) {
    for(std::size_t i = 0; i < arr._employees.size(); i++)
        out << i + 1 << ". " << *(arr._employees[i]);
    out << "== Total salary: " << arr.total_salary() << std::endl << std::endl;
    return out;
}

void Developer::input(std::ifstream& in) {
    Employee::input(in);
    in.read((char*)&_has_bonus, sizeof(_has_bonus));
}

void SalesManager::input(std::ifstream& in) {
    Employee::input(in);
    in.read((char*)&_sold_nm, sizeof(_sold_nm));
    in.read((char*)&_price, sizeof(_price));
}

void Developer::output(std::ofstream& out) const {
    int32_t* temp = new int32_t(DEVELOPER);
    out.write((char*)temp, sizeof(int32_t));
    delete temp;
    Employee::output(out);
    out.write((char*)&_has_bonus, sizeof(_has_bonus));
}

void SalesManager::output(std::ofstream& out) const {
    int32_t* temp = new int32_t(SALES_MANAGER);
    out.write((char*)temp, sizeof(int32_t));
    delete temp;
    Employee::output(out);
    out.write((char*)&_sold_nm, sizeof(_sold_nm));
    out.write((char*)&_price, sizeof(_price));
}

void Developer::input(std::istream& in) {
    Employee::input(in);
    in >> _has_bonus;
}

void SalesManager::input(std::istream& in) {
    Employee::input(in);
    in >> _sold_nm >> _price;
}

void Developer::output(std::ostream& out) const {
    out << "Developer" << std::endl;
    Employee::output(out);
    out << "Has bonus: " << ((_has_bonus) ? "+" : "-") << std::endl;
}

void SalesManager::output(std::ostream& out) const {
    out << "Sales Manager" << std::endl;
    Employee::output(out);
    out << "Sold items: " << _sold_nm << std::endl;
    out << "Item price: " << _price << std::endl;
}

int Developer::salary() const {
    int salary = _base_salary;
    if (_has_bonus) { salary += 1000; }
    return salary;
}

int SalesManager::salary() const {
    return _base_salary + _sold_nm * _price * 0.01;
}

EmployeesArray::~EmployeesArray() {
    for(auto &i : _employees)
        delete i;
}

void EmployeesArray::add(Employee *e) {
    _employees.push_back(e);
}

int EmployeesArray::total_salary() const {
    int res = 0;
    for(auto &i : _employees)
        res += i->salary();
    return res;
}
