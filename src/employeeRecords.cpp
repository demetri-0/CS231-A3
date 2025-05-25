/*
	Author: Demetri Karras
	Assignment Number: 3
	Date of Submission: May 25th, 2025

	File Name: employeeRecords.cpp

	Description:
	This program reads lines from an input file that correspond to an employee.
	The data from each line is parsed, and an employee is created and added to a
	vector of employees. This vector is sorted, and employee information is
	printed to the console.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "employeeData.h"

using namespace std;

void parseLine(string line, vector<Employee>& employees);
void sortByEducation(vector<Employee>& employees);
void giveRaise(vector<Employee>& employees);
void printEducationCount(vector<Employee>& employees);
void printEmployees(vector<Employee>& employees);
string getEducationString(Education education);

int main() {

	/*
	 * Obtains the input file from the user.
	 */
	string fileName;
	cout << "Welcome to the Employee Records Manager!" << endl;
	cout << "Please enter the name of the input file: " << flush;
	cin >> fileName;

	cout << endl;
	ifstream inputFile(fileName);

	if (inputFile.is_open()) {

		/*
		 * Reads the content of the input file line-by-line, storing data in
		 * employees vector.
		 */
		string line;
		vector<Employee> employees;
		while (getline(inputFile, line)) {
			parseLine(line, employees);
		}

		/*
		 * Employees are sorted and given raises based on their education.
		 * Employee data is printed to the console.
		 */
		sortByEducation(employees);
		giveRaise(employees);

		printEducationCount(employees);
		cout << endl;
		printEmployees(employees);
	}

	return 0;
}

/*
 * Function Name: parseLine
 *
 * Input:
 * Param1(line) - the line from the input file from which data is obtained,
 * structured as follows: <name>,<education>,$<salary>
 * Param2(employees) - the vector of employees to which this function applies
 *
 * Output: None - changes are reflected in the input vector.
 *
 * Description:
 * Reads a line from the input file and obtains employee data. Creates a new
 * employee struct and adds it to the specified employees vector.
 */
void parseLine(string line, vector<Employee>& employees) {

	/*
	 * The first comma in the line is found. The employee name is the substring
	 * from the beginning of the line to that comma. The line string is
	 * shortened up to the first character after the first comma.
	 */
	int indexOfComma = line.find(',');
	string name = line.substr(0, indexOfComma);
	line = line.substr(indexOfComma + 1);

	/*
	 * The next comma is found in the new line string. The employee education is
	 * the substring between the beginning of the line string, and the new
	 * comma, which gets converted to a valid Education enum. The line string is
	 * shortened again up to the first character after this comma.
	 */
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

	/*
	 * The dollar sign is found, and the salary is the substring from the
	 * character after the dollar sign to the end of the line. This substring is
	 * converted to an integer.
	 */
	string salaryStr = line.substr(line.find('$') + 1);
	int salary = stoi(salaryStr);

	/*
	 * A new employee struct is created using the above attributes and it is
	 * added to the employees vector.
	 */
	Employee employee = {
		name,
		education,
		salary
	};

	employees.push_back(employee);
}

/*
 * Function Name: giveRaise
 *
 * Input:
 * Param1(employees) - the vector of employees to which this function applies
 *
 * Output: None - changes are reflected in the input vector.
 *
 * Description:
 * Gives a raise to each employee corresponding to their education in the
 * specified vector.
 */
void giveRaise(vector<Employee>& employees) {

	const float highEducationRaise = 1.3;
	const float medEducationRaise = 1.2;
	const float lowEducationRaise = 1.1;

	transform(employees.begin(), employees.end(), employees.begin(), [&](Employee& employee) {

		if (employee.education == DOCTORATE) {
			employee.salary *= highEducationRaise;
		}
		else if (employee.education == MASTERS || employee.education == BACHELORS) {
			employee.salary *= medEducationRaise;
		}
		else {
			employee.salary *= lowEducationRaise;
		}
		return employee;
	});
}

/*
 * Function Name: sortByEducation
 *
 * Input:
 * Param1(employees) - the vector of employees to which this function applies
 *
 * Output: None - changes are reflected in the input vector.
 *
 * Description:
 * Sorts the specified vector of employees by education in ascending order. If
 * education among employees is equal, they are sorted by salary in ascending
 * order.
 */
void sortByEducation(vector<Employee>& employees) {

	sort(employees.begin(), employees.end(), [](Employee& employee1, Employee& employee2) {

		if (employee1.education == employee2.education) {
			return employee1.salary < employee2.salary;
		}

		return employee1.education < employee2.education;
	});
}

/*
 * Function Name: printEducationCount
 *
 * Input:
 * Param1(employees) - the vector of employees to which this function applies
 *
 * Output: None - output is printed to the console.
 *
 * Description:
 * Prints the number of employees with a particular level of education.
 */
void printEducationCount(vector<Employee>& employees) {

	int doctorateCount = 0, mastersCount = 0, bachelorsCount = 0, highSchoolCount = 0;

	transform(employees.begin(), employees.end(), employees.begin(), [&](Employee& employee) {
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
		return employee;
	});

	cout << "== HIGHEST EDUCATION OF EMPLOYEES ==" << endl;
	cout << "Doctorate: " << doctorateCount << endl;
	cout << "Masters: " << mastersCount << endl;
	cout << "Bachelors: " << bachelorsCount << endl;
	cout << "High School: " << highSchoolCount << endl;
}

/*
 * Function Name: printEmployees
 *
 * Input:
 * Param1(employees) - the vector of employees to which this function applies
 *
 * Output: None - output is printed to the console.
 *
 * Description:
 * Iterates through vector of employees, printing their names, education levels,
 * and salaries in a structured format.
 */
void printEmployees(vector<Employee>& employees) {
	cout << "== EMPLOYEES ==" << endl;
	for_each(employees.begin(), employees.end(), [](Employee& employee) {
		cout << "Name: " << employee.name << " // ";
		cout << "Education: " << getEducationString(employee.education) << " // ";
		cout << "Salary: $" << employee.salary << endl;
	});
}

/*
 * Function Name: getEducationString
 *
 * Input:
 * Param1(education) - the Education enum to be converted into a string
 *
 * Output: A string representation of the input Education enum.
 *
 * Description:
 * Returns a string corresponding to a specified education level.
 */
string getEducationString(Education education) {

	if (education == DOCTORATE) {
		return "Doctorate";
	}
	if (education == MASTERS) {
		return "Masters";
	}
	if (education == BACHELORS) {
		return "Bachelors";
	}
	return "High School";
}
