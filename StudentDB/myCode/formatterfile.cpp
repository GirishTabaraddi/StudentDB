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

std::string pocoDateToStringFormatter(const Poco::Data::Date &date)
{
	string dateString = Poco::DateTimeFormatter::format
			(Poco::LocalDateTime(date.year(), date.month(), date.day()), "%d.%m.%Y");

	return dateString;
}

Poco::Data::Date stringToPocoDateFormatter(const std::string& stringDate)
{
	//!	regex datePattern(R"(\d{2}\.\d{2}\.\d{4})");
	//! The above regex is old one for date like 20.01.2024
	//! and the below one is for 1.1.2024
	regex datePattern(R"((\d{1,2})\.(\d{1,2})\.(\d{4}))");

	smatch match; //!< match_results for string objects

	Poco::DateTime datetime;

	int i = 0;

	if (!regex_match(stringDate, match, datePattern))
	{
	    cout << "ERROR: Please enter a valid date format - dd.mm.YYYY : " << endl;
	    datetime = Poco::DateTimeParser::parse("%d.%m.%Y", "00.00.0000", i);
	}
	else
	{
	    int day = stoi(match[1].str());
	    int month = stoi(match[2].str());
	    int year = stoi(match[3].str());

	    datetime.assign(year, month, day);
	}

	return Poco::Data::Date(datetime.year(), datetime.month(), datetime.day());
}

std::string pocoTimeToStringFormatter(const Poco::Data::Time &time)
{
	string timeString;

	timeString = Poco::DateTimeFormatter::format(Poco::LocalDateTime(1,1,1,time.hour(), time.minute()), "%H:%M");

	return timeString;
}

Poco::Data::Time stringToPocoTimeFormatter(const std::string &stringTime)
{
	regex timePattern(R"(\d{1,2}\:\d{1,2})");

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

    //! Extract the time components
    int hours = datetime.hour();
    int minutes = datetime.minute();
    int seconds = datetime.second();

    //! Construct a Poco::Data::Time instance
    Poco::Data::Time pocoTime(hours, minutes, seconds);

    return pocoTime;
}

Poco::DateTime::DaysOfWeek getDayOfWeekFromString(const std::string& dayString)
{
    static const unordered_map<string, Poco::DateTime::DaysOfWeek> dayMap =
    {
        {"monday", Poco::DateTime::MONDAY},
        {"tuesday", Poco::DateTime::TUESDAY},
        {"wednesday", Poco::DateTime::WEDNESDAY},
        {"thursday", Poco::DateTime::THURSDAY},
        {"friday", Poco::DateTime::FRIDAY},
        {"saturday", Poco::DateTime::SATURDAY},
        {"sunday", Poco::DateTime::SUNDAY}
    };

    string lowerDayString;

    for (char c : dayString)
    {
        lowerDayString += tolower(c);
    }

    for(auto& entry : dayMap)
    {
        if(boost::algorithm::icontains(entry.first, lowerDayString))
        {
        	return entry.second;
        }
    }

    istringstream iss(dayString);

    int numericDay;

    if (iss >> numericDay && numericDay >= 1 && numericDay <= 7)
    {
        return static_cast<Poco::DateTime::DaysOfWeek>(numericDay);
    }

    //! Handle invalid input or return a default value
    cerr << "Invalid day input: " << dayString
    		<< ". Defaulting to Monday." << endl;

    return Poco::DateTime::MONDAY;
}
