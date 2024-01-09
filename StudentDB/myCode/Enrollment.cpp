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

Enrollment::Enrollment() : m_grade(0.0), m_semester(0)
{
	this->m_course = new Course();
}

Enrollment::Enrollment(const Course& courseObj, float grade,
		std::string semester) :  m_grade(grade), m_semester(semester)
{
	this->m_course = new Course(courseObj);
}

Enrollment::~Enrollment()
{
}

const float Enrollment::getgrade() const
{
	return this->m_grade;
}

const std::string Enrollment::getsemester() const
{
	return this->m_semester;
}

void Enrollment::print() const
{
	cout << "Enrollment Grade: " << this->m_grade << endl
			<< "Enrollment Semester: " << this->m_semester << endl
			<< "Enrollment Major: " << this->m_course->gettitle() << endl;
}
