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
	std::map<unsigned char, std::string> m_majorById;

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

private:
	/*!
	 * The method setmajorById sets the title's first char using setMajor method
	 */
	void setmajorById(std::string major);

	/*!
	 * The method setMajor takes the major passed through the constructor,
	 * checks if the major is not empty and then assigns the first char to m_major.
	 */
	void setMajor(std::string major);

public:
	/*!
	 * A parameterized constructor that takes string major as input,
	 * it calls setMajor and setmajorById methods and the respective value is set.
	 * Also takes course key and it's credit points and sets the respective values.
	 * @param courseKey
	 * @param title
	 * @param major
	 * @param creditPoints
	 */
	Course(unsigned int courseKey, std::string title, std::string major, float creditPoints);

	/*!
	 * A Destructor of class Course.
	 */
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

	std::string printCourse() const;
};

#endif /* COURSE_H_ */
