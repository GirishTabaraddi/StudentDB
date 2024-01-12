/*!
 * @file formatterfile.cpp
 *
 * \n Created on: 11-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "formatterfile.h"

using namespace std;

std::string pocoDateToStringFromatter(const Poco::Data::Date &date)
{
	string dateString = Poco::DateTimeFormatter::format
			(Poco::LocalDateTime(date.year(), date.month(), date.day()), "%d.%m.%Y");

	return dateString;
}

Poco::Data::Date stringToPocoDateFormatter(const std::string& stringDate)
{
	Poco::DateTime datetime;

	int i = 0;

	datetime = Poco::DateTimeParser::parse("%d.%m.%Y", stringDate, i);

	return datetime;
}
