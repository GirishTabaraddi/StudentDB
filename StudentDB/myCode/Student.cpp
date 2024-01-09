/*!
 * @file Student.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Student.h"

unsigned int Student::m_nextMatrikelNumber = 1009000;

Student::Student() :
		m_matrikelNumber(0), m_firstName(""), m_lastName(""),
		m_dateOfBirth(1900,1,1)
{
}

Student::Student(unsigned int matrikelNumber, std::string firstName,
		std::string lastName, Poco::Data::Date dateOfBirth) :
				m_matrikelNumber(matrikelNumber), m_firstName(firstName),
				m_lastName(lastName), m_dateOfBirth(dateOfBirth)
{
}

Student::~Student()
{
}

const unsigned int Student::getmatrikelNumber() const
{
	return this->m_matrikelNumber;
}

const std::string Student::getFullName() const
{
	return (this->m_firstName + " " + this->m_lastName);
}

const Poco::Data::Date Student::getDoB() const
{
	return this->m_dateOfBirth;
}
