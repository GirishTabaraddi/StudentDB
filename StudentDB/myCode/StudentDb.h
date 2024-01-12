/*!
 * @file StudentDb.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include "Student.h"
#include "formatterfile.h"

class StudentDb
{
private:
	/*!
	 * @var m_students - a map variable that maps the student entered
	 * into the database with an integer key.
	 */
	std::map<int, Student> m_students;

	/*!
	 * @var m_courses - a map variable that stores the list of courses
	 * using a unique pointer and an integer as a key.
	 */
	std::map<int, std::unique_ptr<const Course>> m_courses;

public:

	/*!
	 * A default constructor for StudenDb class.
	 */
	StudentDb();

	/*!
	 * A getter method to fetch the m_students.
	 * @return map type.
	 */
	const std::map<int, Student> getstudents() const;

	/*!
	 * A getter method to fetch the m_courses.
	 * @return map type.
	 */
	const std::map<int, std::unique_ptr<const Course>>& getcourses() const;

	/*!
	 * Add new Course: Queries the user for the required data and #
	 * creates the new course in the database.
	 */
	void addNewCourse();

	/*!
	 * List courses: Prints all courses in the database with their data.
	 */
	void listCourses();

	/*!
	 * Add new student: Queries the user for the required data (member data of Student and Address)
	 * and creates a new student in the database.
	 */
	void addNewStudent();

	/*!
	 * Add enrollment: Queries the user for a matrikel number, a course id,
	 * a semester and adds the enrollment.
	 * If the enrollment already exists, a warning messages is printed.
	 */
	void addEnrollment();

	/*!
	 * Print student: Queries the user for a matrikel number and prints
	 * the student including the enrolled courses and their results.
	 */
	void printStudent();

	/*!
	 * Search student: Queries the user for a string and prints the matrikel number,
	 * last name and first name of all students that have the provided string
	 * as substring in their first or last name.
	 */
	void searchStudent();

	/*!
	 * Update student: Queries the user for a matrikel number. If the corresponding student
	 * is found in the data base, the properties (except for the matrikel number)
	 * are presented in a numbered list. Entering the item number allows the user
	 * to modify the property, entering "0" terminates the update.
	 */
	void updateStudent();

	void printDb() const;
};

#endif /* STUDENTDB_H_ */
