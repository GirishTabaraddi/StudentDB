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

void BlockCourse::write(std::ostream &out) const
{
	out << "B;";

	Course::write(out);

	out << ";" << pocoDateToStringFormatter(this->m_startDate)
		<< ";" << pocoDateToStringFormatter(this->m_endDate)
		<< ";" << pocoTimeToStringFormatter(this->m_startTime)
		<< ";" << pocoTimeToStringFormatter(this->m_endTime)
		<< endl;
}

std::unique_ptr<BlockCourse> BlockCourse::read(std::istream &in)
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
	//	string startDate, endDate, startTime, endTime;
	//	getline(in >> std::ws, startDate, ';');
	//	getline(in >> std::ws, endDate, ';');
	//	getline(in >> std::ws, startTime, ';');
	//	getline(in >> std::ws, endTime, '\n');

	string inStr;

	getline(in, inStr);

	string courseKey = splitAt(inStr, ';');
	string title = splitAt(inStr, ';');
	string major = splitAt(inStr, ';');
	string creditPoints = splitAt(inStr, ';');
	string startDate = splitAt(inStr, ';');
	string endDate = splitAt(inStr, ';');
	string startTime = splitAt(inStr, ';');
	string endTime = splitAt(inStr, '\n');

	return make_unique<BlockCourse>(stoi(courseKey), title, major, stof(creditPoints),
			stringToPocoDateFormatter(startDate), stringToPocoDateFormatter(endDate),
			stringToPocoTimeFormatter(startTime), stringToPocoTimeFormatter(endTime));
}
