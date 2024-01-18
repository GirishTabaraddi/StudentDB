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

	cout << "\t 0	-> To Exit Main Menu" << endl;
	cout << "\t 1 	-> Add New Course" << endl;
	cout << "\t 2 	-> List the Courses" << endl;
	cout << "\t 3 	-> Add new Student" << endl;
	cout << "\t 4 	-> Add Enrollment" << endl;
	cout << "\t 5 	-> Print Student Details" << endl;
	cout << "\t 6 	-> Search Student in Database" << endl;
	cout << "\t 7 	-> Update Student Details" << endl;
	cout << "\t 8 	-> Write Student Database to a text file" << endl;
	cout << "\t 9 	-> Read Student Database from a file" << endl;
	cout << "\t 10 	-> Read Student Database from a server" << endl;

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
				case 8:
				{
					cout << endl << "\t Enter the file name to write the data(.txt): ";

					string filename;
					getline(cin, filename);

					ofstream myfile(filename, ios::trunc);
					if(myfile.is_open())
					{
						this->m_db.write(myfile);
						myfile.close();

						cout << "\n\t Student Database is written to the file" << endl;
					}
					else
					{
						cout << "Unable to open file" << endl;
					}
				}
				break;
				case 9:
				{
					cout << endl << "\t Enter the file name to read the data from(.txt): ";

					string filename = "read_StudentDb.txt";
					getline(cin, filename);

					ifstream inputFile(filename);
					if(inputFile.is_open())
					{
						this->m_db.read(inputFile);
						inputFile.close();

						cout << "\n\t Read the Student Database from the file" << endl;
					}
					else
					{
						cout << "Unable to open file" << endl;
					}
				}
				break;
				case 10:
				{
					cout << "read from server" << endl;

					this->m_db.readFromServer();
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
			}
		}
		catch(const invalid_argument& e)
		{
			cout << endl << "ERROR: Invalid argument" << endl;
		}
//		catch(const out_of_range& e)
//		{
//			cout << endl << "ERROR: Invalid Input, Please enter a numeric value between - [0-10]" << endl;
//		}
	}
}
