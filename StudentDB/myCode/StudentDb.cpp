/*!
 * @file StudentDb.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "StudentDb.h"

using namespace std;

StudentDb::StudentDb()
{
}

const std::map<int, Student> StudentDb::getstudents() const
{
	return this->m_students;
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getcourses() const
{
	return this->m_courses;
}

void StudentDb::addNewCourse()
{
//	unique_ptr<const Course> course = make_unique<Course>(1234, "APT", "Automation", 5);
//	unique_ptr<const Course> course1 = make_unique<Course>(1235, "EOS", "Embedded", 5);
//
//	this->m_courses.insert(make_pair(course->getcourseKey(), move(course)));
//	this->m_courses.insert(make_pair(course1->getcourseKey(), move(course1)));

	string courseKey = "0";
	string title = "NA";
	string major = "NA";
	string credits = "0.0";

	cout << endl << "Enter CourseKey: ";
	getline(cin, courseKey);

	cout << endl << "Enter Title of the Course: ";
	getline(cin, title);

	cout << endl << "Enter the Major in which the Course belongs to: ";
	getline(cin, major);

	cout << endl << "Enter the  credit points of the Course: ";
	getline(cin, credits);

	unique_ptr<const Course> course = make_unique<Course>(stoi(courseKey), title, major, stof(credits));
	this->m_courses.insert(make_pair(course->getcourseKey(), move(course)));
}

void StudentDb::listCourses()
{
	cout << this->m_courses.size() << endl;

	for(const auto& courses: this->m_courses)
	{
		cout << courses.second.get()->printCourse() << endl;
	}
}

void StudentDb::addNewStudent()
{
//	shared_ptr<Address> address = make_shared<Address>("Am Karlshof", 64287, "Darmstadt", "xyz Info");
//
//	Poco::Data::Date dateOfBirth(1997,3,31);
//
//	Student student = Student("Girish", "Tabaraddi", dateOfBirth, address);
//
//	this->m_students.insert(make_pair(student.getmatrikelNumber(), student));

	string firstName = "NA";
	string lastName = "NA";
	string DoBstring = "01.01.1990";
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "Enter First Name of the Student: ";
	getline(cin, firstName);

	cout << endl << "Enter Last Name of the Student: ";
	getline(cin, lastName);

	cout << endl << "Enter Date of Birth of the Student - dd..mm..YYY : ";
	getline(cin, DoBstring);

	cout << endl << "Enter Street Name of the Student's Address: ";
	getline(cin, streetName);

	cout << endl << "Enter Postal Code of the Student's Address: ";
	getline(cin, postalCode);

	cout << endl << "Enter City Name of the Student's Address: ";
	getline(cin, cityName);

	cout << endl << "Enter Additional Info related Student's Address: ";
	getline(cin, additionalInfo);

	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode), cityName, additionalInfo);

	Student student = Student(firstName, lastName, stringToPocoDateFormatter(DoBstring), address);

	this->m_students.insert(make_pair(student.getmatrikelNumber(), student));
}

void StudentDb::addEnrollment()
{
	string matrikelNumber = "0";
	string semester = "0";
	string courseKey = "0";

	cout << endl << "Enter the Matrikel Number of the Student, "
			"to add his/her Enrollment: ";
	getline(cin, matrikelNumber);

	cout << endl << "Enter the Semester of the Student "
			"studying currently: ";
	getline(cin, semester);

	cout << endl << "Enter the Course Key, "
			"to which he/she wants to enroll: ";
	getline(cin, courseKey);

	auto matrikelNumberItr = this->m_students.find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_students.end())
	{
		auto findCourseIdItr = this->m_courses.find(stoi(courseKey));

		if(findCourseIdItr != this->m_courses.end())
		{
			Course* course = const_cast<Course*>(findCourseIdItr->second.get());

			matrikelNumberItr->second.addEnrollment(semester, course);

			cout << "Enrollment Added" << endl;
		}
		else
		{
			cout << endl << "\t \t \t ERROR: Entered Course Key "
					"doesn't exist in the database!!!" << endl;
		}
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Matrikel Number "
				"doesn't exist in the database!!!" << endl;
	}

	//	for(auto& pairItr : this->m_students)
	//	{
	//		auto enrollments = pairItr.second.getenrollments();
	//		for(auto& enrollmentItr : enrollments)
	//		{
	//			cout << enrollmentItr.printEnrollment() << endl;
	//		}
	//	}
}

void StudentDb::printStudent()
{
	string matrikelNumber = "0";

	cout << endl << "Enter the Matrikel Number of the Student, "
			"to print his/her details: ";
	getline(cin, matrikelNumber);

	auto matrikelNumberItr = this->m_students.find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_students.end())
	{
		cout << matrikelNumberItr->second.printStudent() << endl;

		for(auto& itr : matrikelNumberItr->second.getenrollments())
		{
			cout << itr.printEnrollment() << endl;
		}
	}
}

void StudentDb::searchStudent()
{
	string searchString = "Gir";

	cout << endl << "Enter Student Name to search in the Database: ";
	getline(cin, searchString);

	bool matchFound = false;

	for(const auto& pairItr : this->m_students)
	{
		const auto& findStudent = pairItr.second;

		string firstName = findStudent.getfirstName();
		string lastName = findStudent.getlastName();

		if (firstName.find(searchString) != string::npos ||
				lastName.find(searchString) != string::npos)
		{
			matchFound = true;
			cout << findStudent.printStudent() << endl;
		}
	}
	if(matchFound == false)
	{
		cout << "Entered string doesn't match the Student Name "
				"or the Student does not exist in the Database" << endl;
	}
}

void StudentDb::updateStudent()
{
	string matrikelNumber = "0";

	cout << endl << "Enter the Matrikel Number of the Student, "
			"to update his/her details: ";
	getline(cin, matrikelNumber);

	auto studentItr = this->m_students.find(stoi(matrikelNumber));

	if(studentItr != this->m_students.end())
	{
		cout << endl << "\t \t UPDATE STUDENT MENU: "
				"Below are the index number to update the details" << endl << endl;

		cout << "\t \t \t 0 -> To Exit Update Student Menu" << endl;
		cout << "\t \t \t 1 -> Update First Name" << endl;
		cout << "\t \t \t 2 -> Update Last Name" << endl;
		cout << "\t \t \t 3 -> Update Date of Birth" << endl;
		cout << "\t \t \t 4 -> Update Address" << endl;
		cout << "\t \t \t 5 -> Update Enrollment" << endl;

		performStudentUpdate(studentItr->second); //! Method to handle the above options.
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Matrikel Number "
				"doesn't exist in the database!!!" << endl;
	}
}

void StudentDb::performStudentUpdate(Student &student)
{
	bool exitFlag = false;

	while(exitFlag == false)
	{
		string choice;

		cout << endl << "\t \t \t Enter your choice to perform "
				"the respective operation between 0 and 5: ";
		getline(cin, choice);

		try
		{
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

					this->updateFirstName(student);
				}
				break;
				case 2:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Last Name." <<endl;

					this->updateLastName(student);
				}
				break;
				case 3:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Date of Birth." <<endl;

					this->updateDateofBirth(student);
				}
				break;
				case 4:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Address." <<endl;

					this->updateAddress(student);
				}
				break;
				case 5:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Enrollment." <<endl << endl;

					string courseKey = "0";

					cout << endl << "Enter CourseKey: ";
					getline(cin, courseKey);

					auto courseKeyItr = this->m_courses.find(stoi(courseKey));

					if(courseKeyItr != this->m_courses.end())
					{
						cout << "\t \t \t \t 0 -> To Exit Update Enrollment Menu" << endl;
						cout << "\t \t \t \t 1 -> Delete Enrollment" << endl;
						cout << "\t \t \t \t 2 -> Update Grade" << endl;

						this->performEnrollmentUpdate(student, courseKey);
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
		}
		catch(const invalid_argument& e)
		{
			cout << endl << "\t \t \t ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-5]" << endl;
		}
	}
}

void StudentDb::updateFirstName(Student &student)
{
	string firstName = "NA";

	cout << endl << "Enter First Name of the Student to Update: ";
	getline(cin, firstName);
}

void StudentDb::updateLastName(Student &student)
{
	string lastName = "NA";

	cout << endl << "Enter Last Name of the Student to Update: ";
	getline(cin, lastName);
}

void StudentDb::updateDateofBirth(Student &student)
{
	string DoBstring = "31.12.9999";

	cout << endl << "Enter Date of Birth of the Student "
			"to Update - dd..mm..YYY : ";
	getline(cin, DoBstring);

	Poco::Data::Date pocoDoB = stringToPocoDateFormatter(DoBstring);

	student.updateStudent("NA", "NA", pocoDoB);
}

void StudentDb::updateAddress(Student &student)
{
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "Enter Street Name of the Student's Address to Update: ";
	getline(cin, streetName);

	cout << endl << "Enter Postal Code of the Student's Address to Update: ";
	getline(cin, postalCode);

	cout << endl << "Enter City Name of the Student's Address to Update: ";
	getline(cin, cityName);

	cout << endl << "Enter Additional Info related Student's Address to Update: ";
	getline(cin, additionalInfo);

	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode), cityName, additionalInfo);

	student.updateAddress(address);
}

void StudentDb::performEnrollmentUpdate(Student &student,
		std::string &courseKey)
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

					student.deleteEnrollment(stoi(courseKey));
				}
				break;
				case 2:
				{
					cout << endl << "\t \t \t \t You chose option : " << numericChoice
							<< " to update Grade." <<endl;

					string grade = "0";

					cout << endl << "Enter Grade to Update: ";
					getline(cin, grade);

					student.updateGrade(stof(grade), stoi(courseKey));
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

void StudentDb::printDb() const
{
	for(const auto& studentsPair: this->m_students)
	{
		const unsigned int matrikelNumber = studentsPair.first;
		const Student& student = studentsPair.second;

		cout << matrikelNumber << ";" << student.printStudent() << endl;
	}

	for(const auto& coursesPair: this->m_courses)
	{
		//		const unsigned int coursekey = coursesPair.first;
		const Course* course = coursesPair.second.get();

		cout << course->printCourse() << endl;
	}
}
