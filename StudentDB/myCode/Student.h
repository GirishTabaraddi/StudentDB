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

#include <iostream>
#include <string>
#include <Poco/Data/Date.h>

class Student
{
private:
	/*!
	 * @var m_nextMatrikelNumber - Next Matrikel Number incremented
	 * 								after assigning to a student.
	 */
	unsigned int m_nextMatrikelNumber = 1009000;

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

public:
	Student();
	virtual ~Student();
};

#endif /* STUDENT_H_ */
