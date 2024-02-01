/*!
 * @file Course.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Course.h"

#include "BlockCourse.h"
#include "WeeklyCourse.h"

using namespace std;

std::map<unsigned char, std::string> Course::m_majorById =
{
		{'A', "Automation"},
		{'E', "Embedded Systems"},
		{'C', "Communication"},
		{'P', "Power"}
};

Course::Course(unsigned int courseKey, std::string title, std::string major,
		float creditPoints) : m_courseKey(courseKey), m_title(title), m_creditPoints(creditPoints)
{
	setMajor(major);
}

void Course::setMajor(std::string major)
{
	for(const auto& itr : this->getmajorById())
	{
		if(boost::algorithm::icontains(itr.second, major))
		{
			this->m_major = toupper(major[0]);
		}
	}
}

const std::map<unsigned char, std::string> Course::getmajorById()
{
	return Course::m_majorById;
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

void Course::write(std::ostream &out) const
{
	auto itr = this->m_majorById.find(this->m_major);

	if(itr != this->m_majorById.end())
	{
		ostringstream oss;

		oss << fixed << setprecision(1) << this->m_creditPoints;

		string creditpoints = oss.str();

		out << to_string(this->m_courseKey) << ";" << this->m_title << ";"
				<< this->m_majorById.at(this->m_major) << ";" << creditpoints;
	}
}

std::unique_ptr<Course> Course::read(std::istream &in)
{
	string inStr;

	getline(in, inStr);

	string courseType = splitAt(inStr, ';');

	if(courseType == "B" || courseType == "b")
	{
		istringstream iss(inStr);

		unique_ptr<BlockCourse> blockCoursePtr = BlockCourse::read(iss);

		return blockCoursePtr;
	}
	else if(courseType == "W" || courseType == "w")
	{
		istringstream iss(inStr);

		unique_ptr<WeeklyCourse> weeklyCoursePtr = WeeklyCourse::read(iss);

		return weeklyCoursePtr;
	}

	return nullptr;
}

boost::json::object Course::toJson() const
{
	boost::json::object returnObj;

	returnObj.emplace("courseKey", this->m_courseKey);
	returnObj.emplace("title", this->m_title);
	returnObj.emplace("major", this->m_majorById.at(this->m_major));
	returnObj.emplace("creditPoints", this->m_creditPoints);

	return returnObj;
}
