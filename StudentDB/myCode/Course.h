/*!
 * @file Course.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef COURSE_H_
#define COURSE_H_

#include <iostream>
#include <string>
#include <map>

class Course
{
private:
	/*!
	 * @var m_majorByID -
	 */
	std::map<unsigned char, std::string> m_majorByID;

	/*!
	 * @var m_courseKey - A variable that stores the course key.
	 */
	unsigned int m_courseKey;

	/*!
	 * @var m_title - A private member to store the course title.
	 */
	std::string m_title;

	/*!
	 * @var m_major - This member stores the major of the course added.
	 */
	unsigned char m_major;

	/*!
	 * @var m_creditPoints - This member stores the credit points of the course.
	 */
	float m_creditPoints;

public:
	Course();
	virtual ~Course();

	/*!
	 * A getter method to obtain the m_majorById member value.
	 * @return std::map<unsigned char, std::string> type.
	 */
	const std::map<unsigned char, std::string> getmajorById() const;

	/*!
	 * A getter method to obtain the course key.
	 * @return unsigned int type.
	 */
	const unsigned int getcourseKey() const;

	/*!
	 * A getter method to obtain the title of the course.
	 * @return std::string type.
	 */
	const std::string gettitle() const;

	/*!
	 * A getter method to obtain the major of the course.
	 * @return unsigned char type.
	 */
	const unsigned char getmajor() const;

	/*!
	 * A getter method to obtain the credit points of the course.
	 * @return float type.
	 */
	const float getcreditPoints() const;
};

#endif /* COURSE_H_ */
