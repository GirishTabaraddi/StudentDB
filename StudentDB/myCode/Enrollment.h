/*!
 * @file Enrollment.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include "Course.h"

class Enrollment
{
private:
	/*!
	 * @var m_grade - stores the value of enrolled course grade.
	 */
	float m_grade;

	/*!
	 * @var m_semester - stores the value of semester enrolled by a student.
	 */
	std::string m_semester;

	/*!
	 * @var m_course - stores the value of enrolled course as a pointer object of class Course.
	 */
	const Course* m_course;

public:
	/*!
	 * A parameterized constructor which initializes the enrolled course through
	 * m_course which is a pointer object of the class Course.
	 * @param courseObj
	 */
	Enrollment(float grade, std::string semester, const Course* courseObj);

	/*!
	 * A default destructor for class Enrollment.
	 */
	virtual ~Enrollment();

	/*!
	 * A getter method to obtain the value of m_grade of enrolled course.
	 * @return float type.
	 */
	const float getgrade() const;

	/*!
	 * A getter method to obtain the enrolled semester value.
	 * @return std::string type.
	 */
	const std::string& getsemester() const;

	/*!
	 * A getter method to obtain the course object.
	 * @return class Course type.
	 */
	const Course* getcourse() const;

	void print() const;
};

#endif /* ENROLLMENT_H_ */
