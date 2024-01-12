/*!
 * @file Student.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include "Enrollment.h"
#include "Address.h"
#include "formatterfile.h"

#include <Poco/Data/Date.h>

#include <vector>
#include <memory>

class Student
{
private:
	/*!
	 * @var m_nextMatrikelNumber - Next Matrikel Number incremented
	 * 								after assigning to a student.
	 */
	static unsigned int m_nextMatrikelNumber;

	/*!
	 * @var m_matrikelNumber - A Students Matrikel Number.
	 */
	unsigned int m_matrikelNumber;

	/*!
	 * @var m_firstName - Student's first name.
	 */
	std::string m_firstName;

	/*!
	 * @var m_lastName - Student's last name.
	 */
	std::string m_lastName;

	/*!
	 * @var m_dateOfBirth - Student's date of birth.
	 */
	Poco::Data::Date m_dateOfBirth;

	/*!
	 * @var m_enrollments - a vector of enrollments for a student.
	 */
	std::vector<Enrollment> m_enrollments;

	/*!
	 * @var m_address - a shared pointer that holds the details to class Address.
	 */
	std::shared_ptr<Address> m_address;

public:

	/*!
	 * A parameterized constructor that initializes the private members of Student class,
	 * also it takes the shared_pointer to address as argument and init's it's members.
	 * @param matrikelNumber
	 * @param firstName
	 * @param lastName
	 * @param dateOfBirth
	 * @param address
	 */
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address);

	/*!
	 * A default constructor for Student class.
	 */
	virtual ~Student();

	/*!
	 * A getter method that returns the matrikel number of a student.
	 * @return unsigned integer type.
	 */
	const unsigned int getmatrikelNumber() const;

	/*!
	 * A getter method that returns a string of full name(firstname + lastname).
	 * @return std::string type.
	 */
	const std::string getFullName() const;

	/*!
	 * A getter method that returns a string of first name.
	 * @return std::string type.
	 */
	const std::string& getfirstName() const;

	/*!
	 * A getter method that returns a string of last name.
	 * @return std::string type.
	 */
	const std::string& getlastName() const;

	/*!
	 * A getter method to obtain the date of birth of a student.
	 * @return Poco::Data::Date format.
	 */
	const Poco::Data::Date getDoB() const;

	/*!
	 * A getter to list all the enrollments done.
	 * @return vector of class Enrollment type.
	 */
	const std::vector<Enrollment>& getenrollments() const;

	/*!
	 * A getter method to obtain the address class.
	 * @return a shared pointer of class Address type.
	 */
	const std::shared_ptr<Address> getaddress() const;

	/*!
	 *
	 * @return string value.
	 */
	std::string printStudent() const;

	/*!
	 * Add enrollment: Queries the user for a matrikel number, a course id and a semester and
	 * adds the enrollment. If the enrollment already exists, a warning messages is printed.
	 * @param semester
	 * @param courseId
	 *
	 * @return void
	 */
	void addEnrollment(const std::string& semester, Course* courseId);

	/*!
	 * This method updates the details of the students which will be passed as an argument.
	 * @param firstName
	 * @param lastName
	 * @param dateOfBirth
	 *
	 * @return void
	 */
	void updateStudent(std::string firstName, std::string lastName,  Poco::Data::Date dateOfBirth);

	/*!
	 * This method takes Address class object and updates the address passed as argument.
	 * @param address
	 */
	void updateAddress(std::shared_ptr<Address> address);

	/*!
	 * This method takes courseKey as an argument and finds the key in
	 * Enrollments, if there is one, then that enrollment is deleted.
	 * @param courseKey
	 */
	void deleteEnrollment(unsigned int courseKey);

	void updateGrade(float grade, unsigned int courseKey);
};

#endif /* STUDENT_H_ */
