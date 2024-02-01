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
		m_matrikelNumber(Student::m_nextMatrikelNumber++),
		m_firstName(firstName), m_lastName(lastName),
		m_dateOfBirth(dateOfBirth), m_address(address)
{
}

Student::~Student()
{
}

const unsigned int Student::getMatrikelNumber() const
{
	return this->m_matrikelNumber;
}

const std::string& Student::getFirstName() const
{
	return this->m_firstName;
}

const std::string& Student::getLastName() const
{
	return this->m_lastName;
}

const Poco::Data::Date Student::getDateOfBirth() const
{
	return this->m_dateOfBirth;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return this->m_enrollments;
}

const std::shared_ptr<Address> Student::getAddress() const
{
	return this->m_address;
}

void Student::setNextMatrikelNumber(unsigned int newMatrikelnumber)
{
	m_nextMatrikelNumber = newMatrikelnumber;
}

void Student::setFirstName(const std::string &firstName)
{
	this->m_firstName = firstName;
}

void Student::setLastName(const std::string &lastName)
{
	this->m_lastName = lastName;
}

void Student::setDateOfBirth(const Poco::Data::Date &dateOfBirth)
{
	this->m_dateOfBirth = dateOfBirth;
}

void Student::setAddress(const std::shared_ptr<Address> address)
{
	this->m_address = address;
}

void Student::addEnrollment(const std::string& semester, const Course *newCourseId)
{
	unsigned int courseKey = newCourseId->getcourseKey();

	bool enrollmentFound = false;

	for(const Enrollment& enrollment : this->m_enrollments)
	{
		if(enrollment.getcourse()->getcourseKey() == courseKey)
		{
			enrollmentFound = true;
			break;
		}
	}
	if(!enrollmentFound)
	{
		this->m_enrollments.push_back(Enrollment(semester, newCourseId));
	}
}

void Student::deleteEnrollment(const unsigned int &courseKey)
{
	for(vector<Enrollment>::iterator itr = this->m_enrollments.begin();
			itr != this->m_enrollments.end();)
	{
		if(itr->getcourse()->getcourseKey() == courseKey)
		{
			itr = this->m_enrollments.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void Student::updateGrade(const float &grade, const unsigned int &courseKey)
{
	for(vector<Enrollment>::iterator itr = this->m_enrollments.begin();
			itr != this->m_enrollments.end(); itr++)
	{
		if(itr->getcourse()->getcourseKey() == courseKey)
		{
			itr->setgrade(grade);
			break;
		}
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

Student Student::read(std::istream &in)
{
	//	string readLine;
	//
	//	getline(in, readLine);
	//	istringstream iss(readLine);
	//
	//	vector<string> filedata;
	//
	//	while(getline(iss, readLine, ';'))
	//	{
	//		filedata.push_back(readLine);
	//	}
	//
	////	unsigned int matrikelNumber =
	////			(filedata.size()>=1) ? stoi(filedata.at(0)) : 0;
	//	string firstName =
	//			(filedata.size()>=2) ? filedata.at(1) : "(firstName not assigned)";
	//	string lastName =
	//			(filedata.size()>=3) ? filedata.at(2) : "(lastName not assigned)";
	//	Poco::Data::Date dateOfBirth =
	//			(filedata.size()>=4) ? stringToPocoDateFormatter(filedata.at(3)) : Poco::Data::Date();
	//	string streetName =
	//			(filedata.size()>=5) ? filedata.at(4) : "(streetName not assigned)";
	//	unsigned int postalCode =
	//			(filedata.size()>=6) ? stoi(filedata.at(5)) : 0;
	//	string cityName =
	//			(filedata.size()>=7) ? filedata.at(6) : "(cityName not assigned)";
	//	string additionalInfo =
	//			(filedata.size()>=8) ? filedata.at(7) : "(additionalInfo not assigned)";

	string inStr;

	getline(in, inStr);

	unsigned int matrikelNumber = stoul(splitAt(inStr, ';'));

	Student::m_nextMatrikelNumber = matrikelNumber;

	string firstName = splitAt(inStr, ';');
	string lastName = splitAt(inStr, ';');
	Poco::Data::Date dateOfBirth = stringToPocoDateFormatter(splitAt(inStr, ';'));

	istringstream iss(inStr);

	shared_ptr<Address> address = Address::read(iss);

	Student addStudent(firstName, lastName, dateOfBirth, address);

	return addStudent;
}

Student* Student::fromJson(const boost::json::object &jsonDataObject)
{
	string firstName = jsonDataObject.at("name").at("firstName").as_string().c_str();
	string lastName = jsonDataObject.at("name").at("lastName").as_string().c_str();

	int year = jsonDataObject.at("dateOfBirth").at("year").as_int64() + 1900;
	int month = jsonDataObject.at("dateOfBirth").at("month").as_int64() + 1;
	int day = jsonDataObject.at("dateOfBirth").at("date").as_int64();

	if(isPrintable(firstName) && isPrintable(lastName) && isPrintable(to_string(year)) &&
			isPrintable(to_string(month)) && isPrintable(to_string(day)))
	{
		Poco::Data::Date dateOfBirth(year, month, day);

		boost::json::object jsonAddress = jsonDataObject.at("location").get_object();

		shared_ptr<Address> address = Address::fromJson(jsonAddress);

		if(address != nullptr)
		{
			return (new Student(firstName, lastName, dateOfBirth, address));
		}
		else
		{
			return nullptr;
		}
	}

	return nullptr;
}
