#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "employee_data.h"

using namespace std;

void parseLine(string line, vector<Employee>& employees);
void sortByEducation(vector<Employee>& employees);
void giveRaise(vector<Employee>& employees);
void printEducationCount(vector<Employee>& employees);
void printEmployees(vector<Employee>& employees);
string getEducationString(Education education);

int main() {

	string fileName;
	cout << "Welcome to the Employee Records Manager!" << endl;
	cout << "Please enter the name of the input file: " << flush;
	cin >> fileName;

	cout << endl;

	ifstream inputFile(fileName);

	if (inputFile.is_open()) {
		string line;
		vector<Employee> employees;
		while (getline(inputFile, line)) {
			parseLine(line, employees);
		}

		sortByEducation(employees);

		giveRaise(employees);
		printEducationCount(employees);
		cout << endl;
		printEmployees(employees);
	}

	return 0;
}

void parseLine(string line, vector<Employee>& employees) {

	int indexOfComma = line.find(',');
	string name = line.substr(0, indexOfComma);
	line = line.substr(indexOfComma + 1);

	indexOfComma = line.find(',');
	string educationStr = line.substr(0, indexOfComma);
	Education education;
	if (educationStr == "Doctorate") {
		education = DOCTORATE;
	}
	else if (educationStr == "Masters") {
		education = MASTERS;
	}
	else if (educationStr == "Bachelors") {
		education = BACHELORS;
	}
	else {
		education = HIGH_SCHOOL;
	}
	line = line.substr(indexOfComma + 1);

	string salaryStr = line.substr(line.find('$') + 1);
	int salary = stoi(salaryStr);

	Employee employee = {
		name,
		education,
		salary
	};

	employees.push_back(employee);
}

void giveRaise(vector<Employee>& employees) {

	for_each(employees.begin(), employees.end(), [](Employee& employee) {

		if (employee.education == DOCTORATE) {
			employee.salary *= 1.3;
		}
		else if (employee.education == MASTERS || employee.education == BACHELORS) {
			employee.salary *= 1.2;
		}
		else {
			employee.salary *= 1.1;
		}
	});
}

void sortByEducation(vector<Employee>& employees) {

	sort(employees.begin(), employees.end(), [](Employee& employee1, Employee& employee2) {

		if (employee1.education == employee2.education) {
			return employee1.salary > employee2.salary;
		}

		return employee1.education > employee2.education;
	});
}

void printEducationCount(vector<Employee>& employees) {

	int doctorateCount = 0, mastersCount = 0, bachelorsCount = 0, highSchoolCount = 0;

	for_each(employees.begin(), employees.end(),[&](Employee& employee) {
		if (employee.education == DOCTORATE) {
			doctorateCount++;
		}
		else if (employee.education == MASTERS) {
			mastersCount++;
		}
		else if (employee.education == BACHELORS) {
			bachelorsCount++;
		}
		else {
			highSchoolCount++;
		}
	});

	cout << "== HIGHEST EDUCATION OF EMPLOYEES ==" << endl;
	cout << "Doctorate: " << doctorateCount << endl;
	cout << "Masters: " << mastersCount << endl;
	cout << "Bachelors: " << bachelorsCount << endl;
	cout << "High School: " << highSchoolCount << endl;
}

void printEmployees(vector<Employee>& employees) {
	cout << "== EMPLOYEES ==" << endl;
	for_each(employees.begin(), employees.end(),[](Employee& employee) {
		cout << "Name: " << employee.name << " // ";
		cout << "Education: " << getEducationString(employee.education) << " // ";
		cout << "Salary: $" << employee.salary << endl;
	});
}

string getEducationString(Education education) {
	if (education == DOCTORATE) {
		return "Doctorate";
	}
	else if (education == MASTERS) {
		return "Masters";
	}
	else if (education == BACHELORS) {
		return "Bachelors";
	}
	else {
		return "High School";
	}
}
