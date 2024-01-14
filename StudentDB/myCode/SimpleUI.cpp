/*!
 * @file SimpleUI.cpp
 *
 * \n Created on: 13-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "SimpleUI.h"

using namespace std;

SimpleUI::SimpleUI(StudentDb &db) : m_db(db)
{
}

SimpleUI::~SimpleUI()
{
}

void SimpleUI::run()
{
	bool exitFlag = false;

	cout << "Main Menu: Below are the properties of Student Database : " << endl << endl;

	cout << "\t 0 -> To Exit Main Menu" << endl;
	cout << "\t 1 -> Add New Course" << endl;
	cout << "\t 2 -> List the Courses" << endl;
	cout << "\t 3 -> Add new Student" << endl;
	cout << "\t 4 -> Add Enrollment" << endl;
	cout << "\t 5 -> Print Student Details" << endl;
	cout << "\t 6 -> Search Student in Database" << endl;
	cout << "\t 7 -> Update Student Details" << endl;

	while(exitFlag == false)
	{
		string choice;

		cout << endl << "\t Enter your choice to perform the respective operation between 0 and 10: ";
		getline(cin, choice);

		try
		{
			int numericChoice = stoi(choice);

			if(numericChoice >= 0 && numericChoice <= 10)
			{
				switch(numericChoice)
				{
				case 0:
				{
					cout << endl << "Exited Main Menu : " << numericChoice << endl;
					exitFlag = true;
				}
				break;
				case 1:
				{
					cout << endl << "\t You chose option : " << numericChoice
							<< " to add new course." <<endl;
					this->m_db.addNewCourse();
				}
				break;
				case 2:
				{
					cout << endl << "\t You chose option : " << numericChoice
							<< " to list all courses." <<endl;
					this->m_db.listCourses();
				}
				break;
				case 3:
				{
					cout << endl << "\t You chose option : " << numericChoice
							<< " to add new student to the database." <<endl;
					this->m_db.addNewStudent();
				}
				break;
				case 4:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to add new enrollment." <<endl;
					this->m_db.addEnrollment();
				}
				break;
				case 5:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to print the details of the student." <<endl;
					this->m_db.printStudent();
				}
				break;
				case 6:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to search specific student in database." <<endl;
					this->m_db.searchStudent();
				}
				break;
				case 7:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to update the student details." <<endl;
					this->m_db.updateStudent();
				}
				break;
				default:
				{
					cout << endl << "ERROR: Invalid Input, Please enter a numeric value between - [0-10]" << endl;
				}
				}
			}
			else
			{
				cout << endl << "ERROR: Invalid Input, Please enter a numeric value between - [0-10]" << endl;
				//			exitFlag = true;
			}
		}
		catch(const invalid_argument& e)
		{
			cout << endl << "ERROR: Invalid Input, Please enter a numeric value between - [0-10] 111" << endl;
		}
//		catch(const out_of_range& e)
//		{
//			cout << endl << "ERROR: Invalid Input, Please enter a numeric value between - [0-10]" << endl;
//		}
	}
}
