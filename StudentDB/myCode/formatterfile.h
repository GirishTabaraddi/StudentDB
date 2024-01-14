/*!
 * @file formatterfile.h
 *
 * \n Created on: 11-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef FORMATTERFILE_H_
#define FORMATTERFILE_H_

#include <iostream>
#include <string>
#include <regex>

#include <Poco/DateTimeFormatter.h>
#include <Poco/Data/Date.h>
#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeParser.h>
#include <Poco/Timestamp.h>
#include <Poco/Data/Time.h>
#include <Poco/DateTime.h>

std::string pocoDateToStringFromatter(const Poco::Data::Date &date);

Poco::Data::Date stringToPocoDateFormatter(const std::string& stringDate);

std::string pocoTimeToStringFromatter(const Poco::Data::Time &time);

Poco::Data::Time stringToPocoTimeFormatter(const std::string& stringTime);

Poco::DateTime::DaysOfWeek getDayOfWeekFromString(const std::string& dayString);

//std::string pocoWeekDayToStringFromatter(const Poco::DateTime::DaysOfWeek &daysOfWeek);
//
//Poco::DateTime::DaysOfWeek stringToPocoWeekDayFormatter(const std::string& stringTime);

#endif /* FORMATTERFILE_H_ */
