/*!
 * @file Course.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Course.h"

using namespace std;

//map<unsigned char, std::string> Course::m_majorById = {{'E', "EMBEDDED"}, {'A', "AUTOMATION"},
//													   {'C', "COMMUNICATION"}, {'P', "POWER"}};

using namespace std;

Course::Course(unsigned int courseKey, std::string title, std::string major,
		float creditPoints) : m_courseKey(courseKey), m_title(title), m_creditPoints(creditPoints)
{
	setMajor(major);
	setmajorById(major);
}

void Course::setmajorById(std::string major)
{
	this->m_majorById[getmajor()] = major;
}

void Course::setMajor(std::string major)
{
	if(!major.empty())
	{
		this->m_major = major[0];
	}
}

const std::map<unsigned char, std::string> Course::getmajorById() const
{
	return this->m_majorById;
}

const unsigned int Course::getcourseKey() const
{
	return this->m_courseKey;
}

const std::string Course::gettitle() const
{
	return this->m_title;
}

const unsigned char Course::getmajor() const
{
	return this->m_major;
}

const float Course::getcreditPoints() const
{
	return this->m_creditPoints;
}

Course::~Course()
{
}

void Course::print() const
{
	for(const auto& x : this->m_majorById)
	{
		string major = x.second;

		cout << "Course Title: " << gettitle() << endl
			 << "Course Key: " << getcourseKey() << endl
			 << "Course Major ID: " << getmajor() << endl
			 << "Course creditPoints: " << getcreditPoints() << endl
			 << "Course Major: " << major << endl;
	}
}