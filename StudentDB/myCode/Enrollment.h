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

/*!
 * @class Enrollment
 * @brief Represents the enrollment of a student in a course for a specific semester.
 */
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
     * @brief Parameterized constructor for Enrollment.
     *
     * Initializes the enrolled course through m_course,
     * which is a pointer object of the Course class.
     *
     * @param semester  The semester in which the course is enrolled.
     * @param courseObj Pointer to the Course object.
     */
	Enrollment(std::string semester, const Course* courseObj);

    /*!
     * @brief Default destructor for the Enrollment class.
     */
	virtual ~Enrollment();

    /*!
     * @brief Getter method to obtain the grade of the enrolled course.
     *
     * @return float representing the grade.
     */
	const float getgrade() const;

    /*!
     * @brief Getter method to obtain the enrolled semester value.
     *
     * @return const std::string& representing the semester.
     */
	const std::string& getsemester() const;

    /*!
     * @brief Getter method to obtain the Course object.
     *
     * @return const Course* representing the enrolled course.
     */
	const Course* getcourse() const;

    /*!
     * @brief Setter function to set the grade value.
     *
     * @param grade The grade to be set.
     */
	void setgrade(float grade);

    /*!
     * @brief Method to print the enrollment details.
     *
     * @return std::string representing the formatted enrollment information.
     */
	std::string printEnrollment() const;

	/*!
	 *
	 */
	void write(std::ostream& out) const;
};

#endif /* ENROLLMENT_H_ */
