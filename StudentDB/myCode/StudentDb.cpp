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
	unique_ptr<const Course> course = make_unique<Course>(1234, "APT", "Automation", 5);
	unique_ptr<const Course> course1 = make_unique<Course>(1235, "EOS", "Embedded", 5);

	this->m_courses.insert(make_pair(course->getcourseKey(), move(course)));
	this->m_courses.insert(make_pair(course1->getcourseKey(), move(course1)));
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
	// I need to take inputs from the user for address and student details,
	// for now they are hard coded.
	shared_ptr<Address> address = make_shared<Address>("Am Karlshof", 64287, "Darmstadt", "xyz Info");

	Poco::Data::Date dateOfBirth(1997,3,31);

	Student student = Student("Girish", "Tabaraddi", dateOfBirth, address);

	this->m_students.insert(make_pair(student.getmatrikelNumber(), student));

}

void StudentDb::addEnrollment()
{
	// Need to take inputs - semester, courseID(goes to courseKey) and matrikel number
	// to enrol to a course.

	string matrikelNumber = "1009001";

	string semester = "SS2023";

	string courseKey = "1234";

	auto matrikelNumberItr = this->m_students.find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_students.end())
	{
		auto findCourseIdItr = this->m_courses.find(stoi(courseKey));

		if(findCourseIdItr != this->m_courses.end())
		{
			Course* course = const_cast<Course*>(findCourseIdItr->second.get());

			matrikelNumberItr->second.addEnrollment(semester, course);
		}
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
	// get the matrikel number and print all the details of the student
	// including the enrolled courses.

	string matrikelNumber = "1009001";

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
	string searchString = "Girish Tabaraddi";

	for(const auto& pairItr : this->m_students)
	{
		const auto& findStudent = pairItr.second;

		string firstName = findStudent.getfirstName();
		string lastName = findStudent.getlastName();

		if(searchString.find(firstName) != string::npos ||
				searchString.find(lastName) != string::npos)
		{
			cout << findStudent.printStudent() << endl;
		}
	}
}

void StudentDb::updateStudent()
{
	// take matrikel number as input and list all the properties

	string matrikelNumber = "1009001";

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

					string courseKey = "1234";

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
						cout << endl << "\t \t \t ERROR: Entered Matrikel Number "
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
				//			updateFlag1 = true;
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
	Poco::Data::Date NADate(1900,1,1);
	student.updateStudent("Pavan", "NA", NADate);
}

void StudentDb::updateLastName(Student &student)
{
	Poco::Data::Date NADate(1900,1,1);
	student.updateStudent("NA", "Joshi", NADate);
}

void StudentDb::updateDateofBirth(Student &student)
{
	string DoBstring = "01.01.1990";
	Poco::Data::Date pocoDoB = stringToPocoDateFormatter(DoBstring);

	student.updateStudent("NA", "NA", pocoDoB);
}

void StudentDb::updateAddress(Student &student)
{
	string street = "Berliner Alle";
	unsigned short postalCode = 64295;
	string cityName = "Darmstadt";
	string additionalInfo = "abc";

	shared_ptr<Address> address =
			make_shared<Address>(street, postalCode, cityName, additionalInfo);
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

					string matrikelNumber = "1009001";

					student.deleteEnrollment(stoi(courseKey));

				}
				break;
				case 2:
				{
					cout << endl << "\t \t \t \t You chose option : " << numericChoice
							<< " to update Grade." <<endl;

					float grade = 1.3;

					student.updateGrade(grade, stoi(courseKey));

				}
				break;
				}
			}
			else
			{
				cout << endl << "\t \t \t ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-2]" << endl;
				//updateFlag2 = true;
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
