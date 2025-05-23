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
