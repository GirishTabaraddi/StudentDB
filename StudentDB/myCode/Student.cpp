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

const std::string Student::getFullName() const
{
	return (this->m_firstName + " " + this->m_lastName);
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
//	string out = to_string(getmatrikelNumber()) + ";" + this->m_firstName + ";" +
//			this->m_lastName + ";" << this->m_dateOfBirth.day() << "." <<
//			this->m_dateOfBirth.month() << "." << this->m_dateOfBirth.year();
//
//	return out;
	string out = (to_string(this->m_matrikelNumber)
			+ ";" + this->m_firstName
			+ ";" + this->m_lastName
			+ ";" + pocoDateToStringFromatter(this->m_dateOfBirth) + ";");

	out += getAddress()->printAddress();

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

void Student::updateStudent(std::string firstName, std::string lastName,
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
	auto newEnd = remove_if(this->m_enrollments.begin(), this->m_enrollments.end(),
			[courseKey](const Enrollment& enrollments)
			{
				return enrollments.getcourse()->getcourseKey() == courseKey;
			});

		if(newEnd != this->m_enrollments.end())
		{
			cout << "Entered Enrollment Deleted!!" << endl;
			this->m_enrollments.erase(newEnd, this->m_enrollments.end());
		}
}

void Student::updateGrade(float grade, unsigned int courseKey)
{
	for(Enrollment& enrollment : this->m_enrollments)
	{
		if(enrollment.getcourse()->getcourseKey() == courseKey)
		{
			enrollment.setgrade(grade);
		}
	}
}

void Student::write(std::ostream &out) const
{
	out << printStudent() << endl;
}
