/*!
 * @file Student.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Student.h"

using namespace std;

unsigned int Student::m_nextMatrikelNumber = 1009000;

Student::Student(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address) :
								m_firstName(firstName), m_lastName(lastName),
								m_dateOfBirth(dateOfBirth), m_address(address)
{
	this->m_matrikelNumber = ++(Student::m_nextMatrikelNumber);
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

const std::string& Student::getfirstName() const
{
	return this->m_firstName;
}

const std::string& Student::getlastName() const
{
	return this->m_lastName;
}

const std::vector<Enrollment>& Student::getenrollments() const
{
	return this->m_enrollments;
}

const std::shared_ptr<Address> Student::getaddress() const
{
	return this->m_address;
}

string Student::printStudent() const
{
//	string out = to_string(getmatrikelNumber()) + ";" + this->m_firstName + ";" +
//			this->m_lastName + ";" << this->m_dateOfBirth.day() << "." <<
//			this->m_dateOfBirth.month() << "." << this->m_dateOfBirth.year();
//
//	return out;
	string out = this->m_firstName + ";" +  this->m_lastName + ";" +
			to_string(this->m_dateOfBirth.day()) + "." + to_string(this->m_dateOfBirth.month())
			+ "." + to_string(this->m_dateOfBirth.year());

	return out;

//	for(const Enrollment& eachEntries: this->m_enrollments)
//	{
//		cout << to_string(eachEntries.getcourse()->getcourseKey()) << ";" <<
//				eachEntries.getsemester() << ";" << to_string(eachEntries.getgrade()) << endl;
//	}
//	cout << endl;
}

void Student::addEnrollment(const std::string& semester, Course *newCourseId)
{
	for(Enrollment& enrollments: this->m_enrollments)
	{
		if(enrollments.getcourse()->getcourseKey() == newCourseId->getcourseKey())
		{
			cout << "WARNING: Enrollment already exists!!!" << endl;
			return; //! Exit early if duplicate found.
		}
	}

	this->m_enrollments.push_back(Enrollment(semester, newCourseId));
}
