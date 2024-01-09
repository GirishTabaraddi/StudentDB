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

Course::Course(std::string major) :
m_courseKey(0), m_title(major), m_creditPoints(0.0)
{
	setMajor(major);
	setmajorById();
}

void Course::setmajorById()
{
	this->m_majorById[getmajor()] = gettitle();
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
		cout << x.first << endl << x.second << endl;
	}
}
