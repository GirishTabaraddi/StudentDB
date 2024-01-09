/*!
 * @file StudentDb.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "StudentDb.h"

StudentDb::StudentDb()
{
}

const std::map<int, Student> StudentDb::getstudents() const
{
	return this->m_students;
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getcourses() const
{
	return this->m_courses;
}
