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

Enrollment::Enrollment(std::string semester, const Course* courseObj) :
		m_grade(0.0), m_semester(semester), m_course(courseObj)
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

void Enrollment::setgrade(float grade)
{
	this->m_grade = grade;
}

std::string Enrollment::printEnrollment() const
{
	ostringstream oss;

	oss << fixed << setprecision(1) << this->m_grade;

	string out = to_string(this->m_course->getcourseKey())
			+ ";" + this->m_semester
			+ ";" + oss.str();

	return out;
}
