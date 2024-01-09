/*!
 * @file Enrollment.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Enrollment.h"

using namespace std;

Enrollment::Enrollment(float grade, std::string semester, const Course* courseObj) :
		m_grade(grade), m_semester(semester), m_course(courseObj)
{
}

Enrollment::~Enrollment()
{
}

const float Enrollment::getgrade() const
{
	return this->m_grade;
}

const std::string& Enrollment::getsemester() const
{
	return this->m_semester;
}

const Course* Enrollment::getcourse() const
{
	return this->m_course;
}

void Enrollment::print() const
{
	cout << "Enrollment Grade: " << this->m_grade << endl
			<< "Enrollment Semester: " << this->m_semester << endl
			<< "Enrollment Major: " << this->m_course->getmajorById().at(this->m_course->getmajor()) << endl;

	cout << endl;

	this->m_course->print();
}
