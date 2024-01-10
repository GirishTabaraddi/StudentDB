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
//	Course course = Course(1234, "APT", "Automation", 5);

	this->m_courses.insert(make_pair(course->getcourseKey(), move(course)));
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
		const unsigned int coursekey = coursesPair.first;
		const Course* course = coursesPair.second.get();

		cout << coursekey << ";" << course->printCourse() << endl;
	}
}
