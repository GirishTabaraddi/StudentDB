/*!
 * @file BlockCourse.cpp
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "BlockCourse.h"

using namespace std;

BlockCourse::BlockCourse(unsigned int courseKey, std::string title,
		std::string major, float creditPoints, Poco::Data::Date startDate,
		Poco::Data::Date endDate, Poco::Data::Time startTime,
		Poco::Data::Time endTime) :
				Course(courseKey, title, major, creditPoints), m_startDate(startDate),
				m_endDate(endDate), m_startTime(startTime), m_endTime(endTime)
{
}

BlockCourse::~BlockCourse()
{
}

Poco::Data::Date BlockCourse::getStartDate() const
{
	return this->m_startDate;
}

Poco::Data::Date BlockCourse::getEndDate() const
{
	return this->m_endDate;
}

Poco::Data::Time BlockCourse::getStartTime() const
{
	return this->m_startTime;
}

Poco::Data::Time BlockCourse::getEndTime() const
{
	return this->m_endTime;
}

std::string BlockCourse::printBlockCourse() const
{
	string out;

	out = "B;" + Course::printCourse() + ";" + pocoDateToStringFromatter(this->m_startDate)
			+ ";" + pocoDateToStringFromatter(this->m_endDate) + ";" + pocoTimeToStringFromatter(this->m_startTime)
			+ ";" + pocoTimeToStringFromatter(this->m_endTime);
	return out;
}

void BlockCourse::print() const
{
	cout << BlockCourse::printBlockCourse() << endl;
}
