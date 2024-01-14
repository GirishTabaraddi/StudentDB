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
	regex datePattern(R"(\d{2}\.\d{2}\.\d{4})");

	Poco::DateTime datetime;

	int i = 0;

	if(!regex_match(stringDate, datePattern))
	{
		cout << "ERROR: Please enter a valid date format - dd.mm.YYY : " << endl;

		datetime = Poco::DateTimeParser::parse("%d.%m.%Y", "00.00.0000", i);
	}
	else
	{
		datetime = Poco::DateTimeParser::parse("%d.%m.%Y", stringDate, i);
	}

	return datetime;
}

std::string pocoTimeToStringFromatter(const Poco::Data::Time &time)
{
	string timeString;

	timeString = Poco::DateTimeFormatter::format(Poco::LocalDateTime(1,1,1,time.hour(), time.minute()), "%H:%M");

	return timeString;
}

Poco::Data::Time stringToPocoTimeFormatter(const std::string &stringTime)
{
	regex timePattern(R"(\d{2}\:\d{2})");

	Poco::DateTime datetime;

	int i = 0;

	if(!regex_match(stringTime, timePattern))
	{
		cout << "ERROR: Please enter a valid time format - HH:MM : " << endl;

		datetime = Poco::DateTimeParser::parse("%H:%M", "00:00", i);
	}
	else
	{
		datetime = Poco::DateTimeParser::parse("%H:%M", stringTime, i);
	}

	return datetime;
}

Poco::DateTime::DaysOfWeek getDayOfWeekFromString(const std::string& dayString)
{
    if (dayString == "Monday" || dayString == "monday") {
        return Poco::DateTime::MONDAY;
    } else if (dayString == "Tuesday" || dayString == "tuesday") {
        return Poco::DateTime::TUESDAY;
    } else if (dayString == "Wednesday" || dayString == "wednesday") {
        return Poco::DateTime::WEDNESDAY;
    } else if (dayString == "Thursday" || dayString == "thursday") {
        return Poco::DateTime::THURSDAY;
    } else if (dayString == "Friday" || dayString == "friday") {
        return Poco::DateTime::FRIDAY;
    } else if (dayString == "Saturday" || dayString == "saturday") {
        return Poco::DateTime::SATURDAY;
    } else if (dayString == "Sunday" || dayString == "sunday") {
        return Poco::DateTime::SUNDAY;
    } else {
        // Handle invalid input or return a default value
        return Poco::DateTime::MONDAY; // Defaulting to Monday in case of invalid input
    }
}
