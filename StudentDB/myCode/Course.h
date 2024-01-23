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

#include <map>
#include <iomanip>

#include "formatterfile.h"

/*!
 * @class Course
 * @brief Represents a course with relevant information such as title, major, and credit points.
 *
 * This class encapsulates the properties of a course, including its title, major, course key, and credit points.
 * It provides methods to access and manipulate these attributes.
 */
class Course
{
private:
	/*!
	 * @var m_majorByID - A map storing major IDs mapped to their corresponding strings.
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
	 * @brief Sets the major ID based on the first character of the given major string.
	 *
	 * This method takes a major string as input and sets the major ID based on its
	 * first character using the setMajor method.
	 *
	 * @param major A string representing the major.
	 */
	void setmajorById(std::string major);

	/*!
	 * @brief Sets the major based on the first character of the given major string.
	 *
	 * This method is responsible for setting the major attribute based on the first
	 * character of the given major string. It ensures that the major string is not empty
	 * before assigning the first character to m_major.
	 *
	 * @param major A string representing the major.
	 */
	void setMajor(std::string major);

public:
	/*!
	 * @brief Parameterized constructor for initializing a Course object.
	 *
	 * This constructor takes the necessary parameters to initialize a Course object.
	 * It sets the course key, title, major, and credit points using the provided values.
	 * Additionally, it calls setMajor and setCreditPoints methods to set the major and
	 * credit points based on the provided major string and course key.
	 *
	 * @param courseKey 	-	The unique identifier for the course.
	 * @param title 		-	The title of the course.
	 * @param major 		-	The major associated with the course.
	 * @param creditPoints 	-	The credit points assigned to the course.
	 */
	Course(unsigned int courseKey, std::string title, std::string major, float creditPoints);

	/*!
	 * @brief Destructor of class Course.
	 */
	virtual ~Course();

	/*!
	 * @brief Getter method to obtain the map of major IDs.
	 *
	 * This method returns the value of the m_majorById member.
	 *
	 * @return A map containing major IDs and their corresponding strings.
	 */
	const std::map<unsigned char, std::string> getmajorById() const;

	/*!
	 * @brief Getter method to obtain the course key.
	 *
	 * This method returns the course key.
	 *
	 * @return An unsigned integer representing the course key.
	 */
	const unsigned int getcourseKey() const;

	/*!
	 * @brief Getter method to obtain the title of the course.
	 *
	 * This method returns the title of the course.
	 *
	 * @return A string representing the title of the course.
	 */
	const std::string gettitle() const;

	/*!
	 * @brief Getter method to obtain the major of the course.
	 *
	 * This method returns the major of the course as an unsigned char.
	 *
	 * @return An unsigned char representing the major of the course.
	 */
	const unsigned char getmajor() const;

	/*!
	 * @brief Getter method to obtain the credit points of the course.
	 *
	 * This method returns the credit points assigned to the course.
	 *
	 * @return A float representing the credit points of the course.
	 */
	const float getcreditPoints() const;

	/*!
	 * @brief Generates a string representation of the Course.
	 *
	 * This method creates and returns a string representation of the Course,
	 * including its course key, title, major, and credit points.
	 *
	 * @return A string containing information about the Course.
	 */
	virtual std::string printCourse() const;

	/**
	 * @brief Write the object's data to the provided output stream.
	 *
	 * This method is pure virtual and intended to be overridden by derived classes
	 * to write their specific data to the output stream. It allows objects to
	 * represent themselves in a standardized format when output is needed,
	 * such as writing to a file or printing to the console.
	 *
	 * @param out The output stream where the object's data will be written.
	 */
	virtual void write(std::ostream& out) const;
};

#endif /* COURSE_H_ */
