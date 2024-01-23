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

unsigned int Student::m_nextMatrikelNumber = 100000;

Student::Student(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address) :
								m_firstName(firstName), m_lastName(lastName),
								m_dateOfBirth(dateOfBirth), m_address(address)
{
	this->m_matrikelNumber = (Student::m_nextMatrikelNumber)++;
}

Student::~Student()
{
}

const unsigned int Student::getMatrikelNumber() const
{
	return this->m_matrikelNumber;
}

void Student::setNextMatrikelNumber(unsigned int newMatrikelnumber)
{
	m_nextMatrikelNumber = newMatrikelnumber;
}

unsigned int Student::getNextMatrikelNumber()
{
	return m_nextMatrikelNumber;
}

const Poco::Data::Date Student::getDateOfBirth() const
{
	return this->m_dateOfBirth;
}

const std::string& Student::getFirstName() const
{
	return this->m_firstName;
}

const std::string& Student::getLastName() const
{
	return this->m_lastName;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return this->m_enrollments;
}

const std::shared_ptr<Address> Student::getAddress() const
{
	return this->m_address;
}

std::string Student::printStudent() const
{
	string out = (to_string(this->m_matrikelNumber)
			+ ";" + this->m_firstName
			+ ";" + this->m_lastName
			+ ";" + pocoDateToStringFormatter(this->m_dateOfBirth) + ";");

	out += getAddress()->printAddress();

	return out;
}

void Student::addEnrollment(const std::string& semester, const Course *newCourseId)
{
	unsigned int courseKey = newCourseId->getcourseKey();

	auto isEnrolled = [courseKey](const Enrollment& enrollment){
		return (enrollment.getcourse()->getcourseKey() == courseKey);
	};

	auto addEnrollmentItr = find_if(this->m_enrollments.begin(),
			this->m_enrollments.end(), isEnrolled);

	if(addEnrollmentItr != this->m_enrollments.end())
	{
		cout << "\n\t \t WARNING: Enrollment already exists!!!" << endl;
		return;
	}
	else
	{
		this->m_enrollments.push_back(Enrollment(semester, newCourseId));
	}
}

void Student::updateStudentDetails(std::string firstName, std::string lastName,
		Poco::Data::Date dateOfBirth)
{
	Poco::Data::Date NADate(1900,1,1);

	if(firstName != "NA")
	{
		this->m_firstName = firstName;
	}
	if(lastName != "NA")
	{
		this->m_lastName = lastName;
	}
	if(dateOfBirth != NADate)
	{
		this->m_dateOfBirth = dateOfBirth;
	}
}

void Student::updateAddress(std::shared_ptr<Address> address)
{
	this->m_address = address;
}

void Student::deleteEnrollment(unsigned int courseKey)
{
	auto isEnrolled = [courseKey](const Enrollment& enrollment){
		return enrollment.getcourse()->getcourseKey() == courseKey;
	};

	auto delEnrollmentItr = remove_if(this->m_enrollments.begin(),
			this->m_enrollments.end(), isEnrolled);

	if(delEnrollmentItr != this->m_enrollments.end())
	{
		//TODO: remove this cout
		cout << "Entered Enrollment Deleted!!" << endl;
		this->m_enrollments.erase(delEnrollmentItr, this->m_enrollments.end());
	}
}

void Student::updateGrade(float grade, unsigned int courseKey)
{
	auto isEnrolled = [courseKey](const Enrollment& enrollment){
		return enrollment.getcourse()->getcourseKey() == courseKey;
	};

	auto enrollmentItr = find_if(this->m_enrollments.begin(),
			this->m_enrollments.end(), isEnrolled);

	if(enrollmentItr != this->m_enrollments.end())
	{
		enrollmentItr->setgrade(grade);
	}
}

void Student::write(std::ostream &out) const
{
	out << to_string(this->m_matrikelNumber)
		<< ";" << this->m_firstName
		<< ";" << this->m_lastName << ";"
		<< pocoDateToStringFormatter(this->m_dateOfBirth) + ";";

	this->getAddress()->write(out);
}
