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

std::string WeeklyCourse::printWeeklyCourse() const
{
	string out;

	out = "W;" + Course::printCourse() + ";" + to_string(this->m_daysOfWeek) + ";" +
			pocoTimeToStringFromatter(this->m_startTime) + ";" + pocoTimeToStringFromatter(this->m_endTime);

	return out;
}

void WeeklyCourse::print() const
{
	cout << WeeklyCourse::printWeeklyCourse() << endl;
}
