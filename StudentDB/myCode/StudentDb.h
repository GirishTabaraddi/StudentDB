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
#include <memory>

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
	StudentDb();

	const std::map<int, Student> getstudents() const;

	const std::map<int, std::unique_ptr<const Course>>& getcourses() const;

};

#endif /* STUDENTDB_H_ */
