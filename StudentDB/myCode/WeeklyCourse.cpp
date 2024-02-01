/*!
 * @file WeeklyCourse.cpp
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "WeeklyCourse.h"

using namespace std;

WeeklyCourse::WeeklyCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints,
		Poco::DateTime::DaysOfWeek daysOfWeek, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
		Course(courseKey, title, major, creditPoints), m_daysOfWeek(daysOfWeek),
		m_startTime(startTime), m_endTime(endTime)
{
}

WeeklyCourse::~WeeklyCourse()
{
}

Poco::DateTime::DaysOfWeek WeeklyCourse::getDaysOfWeek() const
{
	return this->m_daysOfWeek;
}

Poco::Data::Time WeeklyCourse::getStartTime() const
{
	return this->m_startTime;
}

Poco::Data::Time WeeklyCourse::getEndTime() const
{
	return this->m_endTime;
}

void WeeklyCourse::write(std::ostream &out) const
{
	out << "W;";

	Course::write(out);

	out << ";" << to_string(this->m_daysOfWeek)
		<< ";" << pocoTimeToStringFormatter(this->m_startTime)
		<< ";" << pocoTimeToStringFormatter(this->m_endTime) << endl;
}

std::unique_ptr<WeeklyCourse> WeeklyCourse::read(std::istream &in)
{
	//	string courseType;
	//	getline(in >> std::ws, courseType, ';');
	//
	//	string courseKey;
	//	getline(in >> std::ws, courseKey, ';');
	//
	//	string title, major;
	//	getline(in >> std::ws, title, ';');
	//	getline(in >> std::ws, major, ';');
	//
	//	string creditPoints;
	//	getline(in >> std::ws, creditPoints, ';');
	//
	//	string dayOfWeek, startTime, endTime;
	//	getline(in >> std::ws, dayOfWeek, ';');
	//	getline(in >> std::ws, startTime, ';');
	//	getline(in >> std::ws, endTime, '\n');

	string inStr;

	getline(in, inStr);

	string courseKey = splitAt(inStr, ';');
	string title = splitAt(inStr, ';');
	string major = splitAt(inStr, ';');
	string creditPoints = splitAt(inStr, ';');
	string dayOfWeek = splitAt(inStr, ';');
	string startTime = splitAt(inStr, ';');
	string endTime = splitAt(inStr, '\n');

	return make_unique<WeeklyCourse>
	(stoi(courseKey), title, major, stof(creditPoints), getDayOfWeekFromString(dayOfWeek),
			stringToPocoTimeFormatter(startTime), stringToPocoTimeFormatter(endTime));
}

boost::json::object WeeklyCourse::toJson() const
{
	boost::json::object returnObj;

	boost::json::object courseObj = Course::toJson();

	returnObj.emplace("courseType", "W");

	for(const boost::json::object::value_type & pair : courseObj)
	{
		returnObj.emplace(pair.key(), pair.value());
	}

	returnObj.emplace("dayOfWeek", static_cast<int>(this->m_daysOfWeek));
	returnObj.emplace("startTime", pocoTimeToStringFormatter(this->m_startTime));
	returnObj.emplace("endTime", pocoTimeToStringFormatter(this->m_endTime));

	return returnObj;
}
