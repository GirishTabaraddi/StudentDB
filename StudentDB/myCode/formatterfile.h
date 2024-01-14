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

#include <boost/algorithm/string.hpp>

/*!
 * @brief Converts Poco::Data::Date to a formatted string.
 *
 * @param date Poco::Data::Date object to be converted.
 * @return std::string representing the formatted date.
 */
std::string pocoDateToStringFromatter(const Poco::Data::Date &date);

/*!
 * @brief Converts a string to Poco::Data::Date.
 *
 * @param stringDate std::string containing the date to be converted.
 * @return Poco::Data::Date representing the parsed date.
 */
Poco::Data::Date stringToPocoDateFormatter(const std::string& stringDate);

/*!
 * @brief Converts Poco::Data::Time to a formatted string.
 *
 * @param time Poco::Data::Time object to be converted.
 * @return std::string representing the formatted time.
 */
std::string pocoTimeToStringFromatter(const Poco::Data::Time &time);

/*!
 * @brief Converts a string to Poco::Data::Time.
 *
 * @param stringTime std::string containing the time to be converted.
 * @return Poco::Data::Time representing the parsed time.
 */
Poco::Data::Time stringToPocoTimeFormatter(const std::string& stringTime);

/*!
 * @brief Converts a string representation of a day to Poco::DateTime::DaysOfWeek.
 *
 * @param dayString std::string containing the day to be converted.
 * @return Poco::DateTime::DaysOfWeek representing the parsed day of the week.
 */
Poco::DateTime::DaysOfWeek getDayOfWeekFromString(const std::string& dayString);

#endif /* FORMATTERFILE_H_ */
