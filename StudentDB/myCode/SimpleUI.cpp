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

					this->getUserInputsforNewCourse();
				}
				break;
				case 2:
				{
					cout << endl << "\t You chose option : " << numericChoice
							<< " to list all courses." <<endl;

					this->listCourses();
				}
				break;
				case 3:
				{
					cout << endl << "\t You chose option : " << numericChoice
							<< " to add new student to the database." <<endl;

					this->getUserInputsforNewStudent();
				}
				break;
				case 4:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to add new enrollment." <<endl;

					this->getUserInputforNewEnrollment();
				}
				break;
				case 5:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to print the details of the student." <<endl;

					this->printStudent();
				}
				break;
				case 6:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to search specific student in database." <<endl;

					this->searchStudent();
				}
				break;
				case 7:
				{
					cout << endl << "\t You chose option : "
							<< numericChoice << " to update the student details." <<endl;

					this->getUserInputforStudentUpdate();
				}
				break;
				case 8:
				{
					cout << endl << "\t Enter the file name to write the data(.txt): ";

					string filename = "fileData.txt";
//					getline(cin, filename);

					ofstream writeFile(filename, ios::trunc);
					if(writeFile.is_open())
					{
						this->m_db.write(writeFile);

						writeFile.close();

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
					cout << endl << "\t Enter the file name to read the data from(.csv): ";

					string filename = "read_StudentDb.txt";
//					getline(cin, filename);

					ifstream readFile(filename);
					if(readFile.is_open())
					{
						this->m_db.read(readFile);

						readFile.close();

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
				    string noOfUserDate = "1";
				    string readLine;

				    cout << "Enter the number of Student Data to be extracted from the server: ";
				    getline(cin, noOfUserDate);

				    for(int loopIdx = 0; loopIdx < stoi(noOfUserDate); loopIdx++)
				    {
				    	this->m_db.readStudentDataFromServer();
				    }
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
	}
}

void SimpleUI::getUserInputsforNewCourse()
{
	string courseKey = "0";
	string title = "NA";
	string major = "NA";
	string credits = "0.0";

	string startTime = "0";
	string endTime = "0";
	string startDate = "0";
	string endDate = "0";
	string dayOfWeek = "0";
	string courseType = "NA";

	cout << endl << "\t \t Enter CourseKey: ";
	getline(cin, courseKey);

	cout << endl << "\t \t Enter Title of the Course: ";
	getline(cin, title);

	cout << endl << "\t \t Enter the Major in which the Course belongs to: ";
	getline(cin, major);

	cout << endl << "\t \t Enter the  credit points of the Course: ";
	getline(cin, credits);

	cout << endl << "\t \t Enter the Course Type - Weekly(W)/Block(B): ";
	getline(cin, courseType);

	cout << endl << "\t \t Enter the Course Start Time - HH:MM : ";
	getline(cin, startTime);

	cout << endl << "\t \t Enter the Course End Time - HH:MM : ";
	getline(cin, endTime);

	if(courseType == "B" || courseType == "b")
	{
		cout << endl << "\t \t Enter the Course Start Date - dd.mm.YYYY : ";
		getline(cin, startDate);

		cout << endl << "\t \t Enter the Course End Date - dd.mm.YYYY : ";
		getline(cin, endDate);
	}
	if(courseType == "W" || courseType == "w")
	{
		cout << endl << "\t \t Enter the Course Week - Monday-Sunday : ";
		getline(cin, dayOfWeek);
	}

	try
	{
		//! Call the addNewCourse function from the StudentDb.h
		 StudentDb::RC_StudentDb_t result =
					this->m_db.addNewCourse(courseKey, title, major, credits,
							courseType, startTime, endTime, startDate,
							endDate, dayOfWeek);

		 switch(result)
		 {
		 case StudentDb::RC_StudentDb_t::RC_Success:
		 {
			 cout << "\t \t \nNew Course Added" << endl;
			 break;
		 }
		 case StudentDb::RC_StudentDb_t::RC_Course_Exists:
		 {
			 cout << "\t \t \nEntered Course Already exists" << endl;
			 break;
		 }
		 default:
		 {
			 cout << "\t \t \nUnexpected error during add course" << endl;
			 break;
		 }
		 }
	}
	catch(const exception& e)
	{
		cerr << "\t \t \nException: " << e.what() << endl;
	}
}

void SimpleUI::listCourses()
{
	cout << this->m_db.getCourses().size() << endl;

	for(const auto& courses: this->m_db.getCourses())
	{
		cout << courses.second.get()->printCourse() << endl;
	}
}

void SimpleUI::getUserInputsforNewStudent()
{
	string firstName = "NA";
	string lastName = "NA";
	string DoBstring = "01.01.1990";
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "\t \t Enter First Name of the Student - a-z/A-Z: ";
	getline(cin, firstName);

	cout << endl << "\t \t Enter Last Name of the Student - a-z/A-Z: ";
	getline(cin, lastName);

	cout << endl << "\t \t Enter Date of Birth of the Student - dd..mm..YYY : ";
	getline(cin, DoBstring);

	cout << endl << "\t \t Enter Street Name of the Student's Address - a-z/A-Z: ";
	getline(cin, streetName);

	cout << endl << "\t \t Enter Postal Code of the Student's Address - 0-9: ";
	getline(cin, postalCode);

	cout << endl << "\t \t Enter City Name of the Student's Address - a-z/A-Z: ";
	getline(cin, cityName);

	cout << endl << "\t \t Enter Additional Info related Student's Address - 0-9/a-z/A-Z: ";
	getline(cin, additionalInfo);

	try
	{
		//! Call the addnewstudent function from the StudentDb.h
		 StudentDb::RC_StudentDb_t result =
				 this->m_db.addNewStudent(firstName, lastName, DoBstring,
						 streetName, postalCode, cityName, additionalInfo);

		 switch(result)
		 {
		 case StudentDb::RC_StudentDb_t::RC_Success:
		 {
			 cout << "\t \t \nNew Student Added" << endl;
			 break;
		 }
		 case StudentDb::RC_StudentDb_t::RC_Student_Exists:
		 {
			 cout << "\t \t \nEntered Student Already exists" << endl;
			 break;
		 }
		 default:
		 {
			 cout << "\t \t \nUnexpected error during add student" << endl;
			 break;
		 }
		 }
	}
	catch(const exception& e)
	{
		cerr << "\t \t \nException: " << e.what() << endl;
	}
}

void SimpleUI::getUserInputforNewEnrollment()
{
	string matrikelNumber = "0";
	string semester = "0";
	string courseKey = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to add his/her Enrollment - 0-9: ";
	getline(cin, matrikelNumber);

	cout << endl << "\t \t Enter the Semester of the Student "
			"studying currently - a-z/A-Z/0-9: ";
	getline(cin, semester);

	cout << endl << "\t \t Enter the Course Key, "
			"to which he/she wants to enroll - 0-9: ";
	getline(cin, courseKey);

	try
	{
		//! Call the addEnrollment function from the StudentDb.h
		 StudentDb::RC_StudentDb_t result =
				 this->m_db.addEnrollment(matrikelNumber, semester, courseKey);

		 switch(result)
		 {
		 case StudentDb::RC_StudentDb_t::RC_Success:
		 {
			 cout << "\t \t \nNew Enrollment Added" << endl;
			 break;
		 }
		 case StudentDb::RC_StudentDb_t::RC_Wrong_Course_Key:
		 {
			 cout << "\t \t \nEntered a wrong course key" << endl;
			 break;
		 }
		 case StudentDb::RC_StudentDb_t::RC_Wrong_MatrikelNumber:
		 {
			 cout << "\t \t \nEntered matrikel number is wrong" << endl;
			 break;
		 }
		 case StudentDb::RC_StudentDb_t::RC_Enrollment_Exists:
		 {
			 cout << "\t \t \nEntered Enrollment already exists" << endl;
			 break;
		 }
		 default:
		 {
			 cout << "\t \t \nUnexpected error during add enrollment" << endl;
			 break;
		 }
		 }
	}
	catch(const exception& e)
	{
		cerr << "\t \t \nException: " << e.what() << endl;
	}
}

void SimpleUI::getUserInputforStudentUpdate()
{
	string matrikelNumber = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to update his/her details - 0-9: ";
	getline(cin, matrikelNumber);

	auto studentItr =  this->m_db.getStudents().find(stoi(matrikelNumber));

	if(studentItr != this->m_db.getStudents().end())
	{
		cout << endl << "\t \t UPDATE STUDENT MENU: "
				"Below are the index number to update the details" << endl << endl;

		cout << "\t \t \t 0 -> To Exit Update Student Menu" << endl;
		cout << "\t \t \t 1 -> Update First Name" << endl;
		cout << "\t \t \t 2 -> Update Last Name" << endl;
		cout << "\t \t \t 3 -> Update Date of Birth" << endl;
		cout << "\t \t \t 4 -> Update Address" << endl;
		cout << "\t \t \t 5 -> Update Enrollment" << endl;

		Student& updateStudent = studentItr->second;

		this->performStudentUpdate(updateStudent);
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Matrikel Number "
				"doesn't exist in the database!!!" << endl;
	}
}

void SimpleUI::performStudentUpdate(Student &updateStudent)
{
	bool exitFlag = false;

	while(exitFlag == false)
	{
		string choice;

		cout << endl << "\t \t \t Enter your choice to perform "
				"the respective operation between 0 and 5: ";
		getline(cin, choice);

//		try
//		{
			int numericChoice = stoi(choice);

			if(numericChoice >= 0 && numericChoice <= 5)
			{
				switch(numericChoice)
				{
				case 0:
				{
					cout << endl << "\t \t Exited Student Update Menu : "
							<< numericChoice <<endl;
					exitFlag = true;
				}
				break;
				case 1:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update First Name." <<endl;

					string firstName = "NA";
					Poco::Data::Date NADate(1900,1,1);

					cout << endl << "\t \t \t Enter First Name of the Student to Update - a-z/A-Z: ";
					getline(cin, firstName);

					updateStudent.updateStudentDetails(firstName, "NA", NADate);
				}
				break;
				case 2:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Last Name." <<endl;

					string lastName = "NA";

					cout << endl << "\t \t \t Enter Last Name of the Student to Update - a-z/A-Z: ";
					getline(cin, lastName);

					Poco::Data::Date NADate(1900,1,1);

					updateStudent.updateStudentDetails("NA", lastName, NADate);
				}
				break;
				case 3:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Date of Birth." <<endl;

					string DoBstring = "31.12.9999";

					cout << endl << "\t \t \t \t Enter Date of Birth of the Student "
							"to Update - dd..mm..YYY : ";
					getline(cin, DoBstring);

					Poco::Data::Date pocoDoB = stringToPocoDateFormatter(DoBstring);

					updateStudent.updateStudentDetails("NA", "NA", pocoDoB);
				}
				break;
				case 4:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Address." <<endl;

					this->getUserInputforAddressUpdate(updateStudent);
				}
				break;
				case 5:
				{
					if(updateStudent.getEnrollments().empty())
					{
						cout << endl << "\t \t \t ERROR: Entered Student not "
								"enrolled to update grade or delete enrollment!!!" << endl;
						break;
					}
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Enrollment." <<endl << endl;

					string courseKey = "0";

					cout << endl << "\t \t \t \t Enter CourseKey - 0-9: ";
					getline(cin, courseKey);

					auto courseKeyItr = this->m_db.getCourses().find(stoi(courseKey));


					if(courseKeyItr != this->m_db.getCourses().end())
					{
						cout << "\t \t \t \t 0 -> To Exit Update Enrollment Menu" << endl;
						cout << "\t \t \t \t 1 -> Delete Enrollment" << endl;
						cout << "\t \t \t \t 2 -> Update Grade" << endl;

						this->performEnrollmentUpdate(updateStudent, courseKey);
					}
					else
					{
						cout << endl << "\t \t \t ERROR: Entered Course Key "
								"doesn't exist in the database!!!" << endl;
					}
				}
				break;
				default:
				{
					cout << endl << "\t \t \t ERROR: Invalid Input, "
							"Please enter a numeric value between - [0-5]" << endl;
				}
				break;
				}
			}
			else
			{
				cout << endl << "\t \t \t ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-5]" << endl;
			}
//		}
//		catch(const invalid_argument& e)
//		{
//			cout << endl << "\t \t \t ERROR: Invalid Input, "
//					"Please enter a numeric value between - [0-5]" << endl;
//		}
	}
}

void SimpleUI::getUserInputforAddressUpdate(Student &updateStudent)
{
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "\t \t \t \t Enter Street Name of the "
			"Student's Address to Update - a-z/A-Z: ";
	getline(cin, streetName);

	cout << endl << "\t \t \t \t Enter Postal Code of the "
			"Student's Address to Update - 0-9: ";
	getline(cin, postalCode);

	cout << endl << "\t \t \t \t Enter City Name of the "
			"Student's Address to Update - a-z/A-Z: ";
	getline(cin, cityName);

	cout << endl << "\t \t \t \t Enter Additional Info related "
			"to Student's Address to Update - a-z/A-Z: ";
	getline(cin, additionalInfo);

	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode),
					cityName, additionalInfo);

	updateStudent.updateAddress(address);
}

void SimpleUI::performEnrollmentUpdate(Student& updateStudent, const std::string& courseKey)
{
	bool exitFlag2 = false;

	while(exitFlag2 == false)
	{
		string choice;

		cout << endl << "\t \t \t \t Enter the index number "
				"to delete enrollment / enter mark: ";
		getline(cin, choice);

		try
		{
			int numericChoice = stoi(choice);

			if(numericChoice >= 0 && numericChoice <= 2)
			{
				switch(numericChoice)
				{
				case 0:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to exit Update Enrollment." <<endl;
					exitFlag2 = true;
				}
				break;
				case 1:
				{
					cout << endl << "\t \t \t \t You chose option : " << numericChoice
							<< " to Delete Enrollment." <<endl;

					updateStudent.deleteEnrollment(stoi(courseKey));
				}
				break;
				case 2:
				{
					cout << endl << "\t \t \t \t You chose option : " << numericChoice
							<< " to update Grade." <<endl;

					string grade = "0";

					cout << endl << "\t \t \t \t \t Enter Grade to Update - 0-9: ";
					getline(cin, grade);

					updateStudent.updateGrade(stof(grade), stoi(courseKey));
				}
				break;
				}
			}
			else
			{
				cout << endl << "\t \t \t ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-2]" << endl;
			}
		}
		catch(const invalid_argument& e)
		{
			cout << endl << "\t \t \t ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-2]" << endl;
		}
	}
}

void SimpleUI::printStudent()
{
//	map<int, Student>& students = this->m_db.getStudents();
	string matrikelNumber = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to print his/her details - 0-9: ";
	getline(cin, matrikelNumber);

	auto matrikelNumberItr = this->m_db.getStudents().find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_db.getStudents().end())
	{
		cout << "\n\t \t \t " << matrikelNumberItr->second.printStudent() << endl;

		for(const Enrollment& enrollmentItr : matrikelNumberItr->second.getEnrollments())
		{
			cout << "\n\t \t \t " << enrollmentItr.printEnrollment() << endl;
		}
	}
	else
	{
		cout << "\n\t \t Entered Matrikel Number does not match "
				"any student in the database." << endl;
	}
}

void SimpleUI::searchStudent()
{
	string searchString = "Gir";

	cout << endl << "\t \t Enter Student Name to search in the Database - a-z/A-Z: ";
	getline(cin, searchString);

	bool matchFound = false;

	for(const auto& pairItr : this->m_db.getStudents())
	{
		const Student& findStudent = pairItr.second;

		string firstName = findStudent.getFirstName();
		string lastName = findStudent.getLastName();

		if (boost::algorithm::icontains(firstName, searchString) ||
				boost::algorithm::icontains(lastName, searchString))
		{
			matchFound = true;

			cout << "\n\t \t \t " << findStudent.printStudent() << endl;
		}
	}
	if(matchFound == false)
	{
		cout << "\t \t Entered string doesn't match the Student Name "
				"or the Student does not exist in the Database" << endl;
	}
}
