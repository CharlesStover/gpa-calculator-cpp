#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


const int MAX_COURSES = 10;



// Convert letter grade to grade point.
int letter2gp(char let)
{

	// Convert A, B, C, D to 4, 3, 2, 1.
	int grade = 'E' - let;

	// Convert F to 0.
	if (grade < 0)
		grade = 0;

	return grade;
}



// Total hours with D grade.
int DRule(int n, char grades[], int hours[])
{

	// Total hours with D grade.
	int totalHours = 0;

	// For each course,
	for (int x = 0; x < n; x++)
	{

		// If grade is D, accumulate the hours.
		if (grades[x] == 'D')
			totalHours += hours[x];
	}
	return totalHours;
}



// Get a new course.
void getCourse(string& name, string& time, string& number, char& grade, int& hours, int n)
{

	// Get the course name.
	cout << endl << "What is the name of Course #" << n << " (e.g. Programming Foundations I)? ";
	getline(cin, name);

	cout << "When did you take " << name << " (e.g. Spring 2016)? ";
	getline(cin, time);

	// Get the course ID.
	cout << "What is the Course ID of " << name << " (e.g. CSCE 2004)? ";
	getline(cin, number);

	// Get the grade for the class.
	grade = ' ';
	while (
		grade != 'A' &&
		grade != 'B' &&
		grade != 'C' &&
		grade != 'D' &&
		grade != 'F' &&
		grade != 'I' &&
		grade != 'W'
	)
	{
		cout << "What was your grade in " << name << " (A, B, C, D, F, I, W)? ";
		cin >> grade;
		cin.clear();
		cin.ignore();
	}

	// Get the hours for the class.
	hours = 0;
	while (
		hours < 1 ||
		hours > 9
	)
	{
		cout << "How many hours is " << name << "? ";
		cin >> hours;
		cin.clear();
		cin.ignore();
	}
}



// Calculate the GPA.
double gpa(int n, const char grades[], const int hours[])
{
	int totalGrade = 0, // total grade
		totalHours = 0; // total hours

	// For each course taken,
	for (int x = 0; x < n; x++)
	{

		// Ignore withdrawn and incomplete classes.
		if (
			grades[x] != 'I' &&
			grades[x] != 'W'
		)
		{
			totalGrade += letter2gp(grades[x]) * hours[x];
			totalHours += hours[x];
		}
	}
	if (!totalHours)
		return 0;
	return double(totalGrade) / double(totalHours);
}



// Congratulatory or consoling message based on GPA.
void gpaMessage(double gpa, string semester)
{
	cout << endl;

	// If no courses were taken during semester GPA check.
	if (gpa < 0)
		cout << "You did not take any courses during " << semester << ".";
	else {
		if (gpa < 3)
			cout << "Sorry";
		else
			cout << "Congratulations";
		cout << ", your GPA";
		if (semester != "")
			cout << " for " << semester;
		cout << " is " << gpa << ".";
	}
	cout << endl;
}



// Display menu and get option.
char menu()
{
	// Menu
	cout << endl << "Welcome to the interactive menu!" << endl
	     << "Please enter the character next to the desired option." << endl
	     << "A) Compute your GPA" << endl
	     << "B) List courses" << endl
	     << "C) Compute the total credit hours with grade D" << endl
	     << "D) Compute the GPA for a particular semester" << endl
	     << "E) Add another course to the course list" << endl
	     << "Q) Quit" << endl << endl;

	// Get the option.
	char menuOption = ' ';
	while (
		menuOption != 'A' &&
		menuOption != 'B' &&
		menuOption != 'C' &&
		menuOption != 'D' &&
		menuOption != 'E' &&
		menuOption != 'Q' &&
		menuOption != 'a' &&
		menuOption != 'b' &&
		menuOption != 'c' &&
		menuOption != 'd' &&
		menuOption != 'e' &&
		menuOption != 'q'
	)
	{
		cout << "Your Choice: ";
		cin >> menuOption;
		cin.clear();
		cin.ignore();
	}
	if (menuOption >= 'a')
		menuOption -= 'a' - 'A';
	return menuOption;
}



// Print the courses entered thus far.
void print(int n, string names[], string times[], string numbers[], char grades[], int hours[])
{
	cout << endl << n << " Courses:" << endl
		 << "/------------------------------------------------------------------------------\\" << endl
	     << "| ID        | Course Name                        | Semester    | Hours | Grade |" << endl
	     << "--------------------------------------------------------------------------------" << endl;
	for (int x = 0; x < n; x++)
		cout <<  "| " << setw(9)  << numbers[x]
		     << " | " << setw(34) << names[x]
		     << " | " << setw(11) << times[x]
		     << " | " << setw(5)  << hours[x]
		     << " | " << setw(5)  << grades[x] << " |" << endl;
	cout << "\\------------------------------------------------------------------------------/" << endl;
}



// Calculate a semester's GPA.
double semesterGpa(int n, const string times[], const char grades[], const int hours[], string semester)
{

	// Calculate the GPA.
	int totalGrade = 0,
		totalHours = 0;

	// For each course,
	for (int x = 0; x < n; x++)
	{

		// If it belongs to this semester and counts toward GPA,
		if (
			times[x] == semester &&
			grades[x] != 'I' &&
			grades[x] != 'W'
		)
		{
			totalGrade += letter2gp(grades[x]) * hours[x];
			totalHours += hours[x];
		}
	}

	if (totalHours)
		return double(totalGrade) / double(totalHours);
	return -1;
}



// Main
int main()
{

	// Initialize Course Information
	char
		grade[MAX_COURSES] = {};  // grade (A-F) for a particular course

	int
		hours[MAX_COURSES]    = {}, // hours for a particular course
		totalCourses          = 0;  // courses you have taken

	string
		id[MAX_COURSES]       = {}, // ID of a particular course
		name[MAX_COURSES]     = {}, // name of a particular course
		semester[MAX_COURSES] = {}; // semester for a particular course

	// Welcome message
	cout << endl << "--------------------------------------------------------------------------------" << endl
	     << "Welcome to the Course Management System v1!" << endl << endl;

	// Get the number of courses.
	{
		int courses2add = 0;
		while (
			courses2add < 1 ||
			courses2add > MAX_COURSES
		)
		{
			cout << "How many courses have you taken? ";
			cin >> courses2add;
			cin.clear();
			cin.ignore();

			// Error for too many courses.
			if (courses2add > MAX_COURSES)
				cout << "This program only supports " << MAX_COURSES << " courses." << endl;
		}

		// Add the initial course list.
		for (int x = 0; x < courses2add; x++) {
			getCourse(
				name[x],
				semester[x],
				id[x],
				grade[x],
				hours[x],
				totalCourses + 1
			);
			totalCourses++;
		}
	}

	// Menu
	char menuOption = ' ';
	while (
		(menuOption = menu()) &&
		menuOption != 'Q'
	)
	{

		// Output the GPA.
		if (menuOption == 'A')
			gpaMessage(
				gpa(totalCourses, grade, hours),
				""
			);

		// List courses
		else if (menuOption == 'B')
			print(totalCourses, name, semester, id, grade, hours);

		// Compute the total credit hours with grade D
		else if (menuOption == 'C')
			cout << endl << "Total hours with grade D: " << DRule(totalCourses, grade, hours) << endl;

		// Compute the GPA for a particular semester
		else if (menuOption == 'D')
		{
			string semesterGrade = "";

			// Get the semester.
			cout << endl << "For what semester would you like to receive the GPA? ";
			getline(cin, semesterGrade);
			gpaMessage(
				semesterGpa(totalCourses, semester, grade, hours, semesterGrade),
				semesterGrade
			);
		}

		// Add another course to the course list
		else if (menuOption == 'E')
		{

			// We can't add more than 10!
			if (totalCourses + 1 > MAX_COURSES)
				cout << endl << "You cannot add more than " << MAX_COURSES << " courses." << endl;

			// Add a course.
			else {
				getCourse(
					name[totalCourses],
					semester[totalCourses],
					id[totalCourses],
					grade[totalCourses],
					hours[totalCourses],
					totalCourses + 1
				);
				cout << name[totalCourses - 1] << " -- " << name[totalCourses] << endl;
				totalCourses++;
			}
		}

		// Improper Menu Input
		else if (menuOption != 'Q')
			cout << endl << "Sorry, but '" << menuOption << "' is not a recognized option." << endl;
	}
	cout << endl << "Thank you. Goodbye!" << endl
	     << "--------------------------------------------------------------------------------" << endl << endl;
	return 0;
}
