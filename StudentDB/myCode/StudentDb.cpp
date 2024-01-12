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
		auto findCourseId = this->m_courses.find(stoi(courseKey));

		if(findCourseId != this->m_courses.end())
		{
			Course* course = const_cast<Course*>(findCourseId->second.get());

			matrikelNumberItr->second.addEnrollment(semester, course);
		}
	}

	for(auto& pairItr : this->m_students)
	{
		auto enrollments = pairItr.second.getenrollments();
		for(auto& enrollmentItr : enrollments)
		{
			cout << enrollmentItr.printEnrollment() << endl;
		}
	}
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

//	bool updateFlag = false;

	string matrikelNumber = "1009001";

	auto studentItr = this->m_students.find(stoi(matrikelNumber));

	if(studentItr != this->m_students.end())
	{
		cout << "Enter the index number to update the details: " << endl;
		cout << "0 -> To Exit" << endl;
		cout << "1 -> Update First Name" << endl;
		cout << "2 -> Update Last Name" << endl;
		cout << "3 -> Update Date of Birth" << endl;
		cout << "4 -> Update Address" << endl;
		cout << "5 -> Update Grade" << endl;
		cout << "6 -> Delete Enrollment" << endl;

		cout << "Choose Options [0-6]: ";

		unsigned int option = 3;

//		while(updateFlag == false)
//		{
			switch(option)
			{
			case 0:
			{
				cout << "0 -> To Exit" << endl;
//				updateFlag = true;
				break;
			}
			case 1:
			{
				cout << "1 -> Updating First Name" << endl;

				Poco::Data::Date NADate(1900,1,1);
				studentItr->second.updateStudent("Pavan", "NA", NADate);

				break;
			}
			case 2:
			{
				cout << "2 -> Update Last Name" << endl;

				Poco::Data::Date NADate(1900,1,1);
				studentItr->second.updateStudent("NA", "Joshi", NADate);

				break;
			}
			case 3:
			{
				cout << "3 -> Update Date of Birth" << endl;

				studentItr->second.updateStudent("NA", "NA", stringToPocoDateFormatter("01.01.1990"));

				break;
			}
			case 4:
			{
				cout << "4 -> Update Address" << endl;
				break;
			}
			case 5:
			{
				cout << "5 -> Update Grade" << endl;
				break;
			}
			case 6:
			{
				cout << "6 -> Delete Enrollment" << endl;
				break;
			}
			default:
			{
				cout << "You chose an Invalid Option!!!" << endl;
			}
			}
//		}
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
