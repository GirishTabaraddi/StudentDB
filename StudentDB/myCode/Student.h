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

#include <Poco/Data/Date.h>
#include <vector>

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

public:
	Student();

	Student(unsigned int matrikelNumber, std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth);

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
	 * A getter method to obtain the date of birth of a student.
	 * @return Poco::Data::Date format.
	 */
	const Poco::Data::Date getDoB() const;

};

#endif /* STUDENT_H_ */
