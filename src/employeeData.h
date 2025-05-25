/*
	Author: Demetri Karras
	Assignment Number: 3
	Date of Submission: May 25th, 2025

	File Name: employeeData.h
*/

#include <string>

using namespace std;

enum Education {
	HIGH_SCHOOL,
	BACHELORS,
	MASTERS,
	DOCTORATE
};

typedef struct {
	string name;
	Education education;
	int salary;
} Employee;
