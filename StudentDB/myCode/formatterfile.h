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
#include <sstream>
#include <unordered_map>

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
std::string pocoDateToStringFormatter(const Poco::Data::Date &date);

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
std::string pocoTimeToStringFormatter(const Poco::Data::Time &time);

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

/*!
 * @brief Split the input string at the specified delimiter.
 *
 * This function takes an input string and splits it at the specified delimiter.
 * It returns the portion of the string before the delimiter, and modifies the input
 * string to contain the remaining portion after the delimiter.
 *
 * @param remainder The input string to be split, modified to contain the remaining portion.
 * @param delimiter The character at which to split the input string.
 * @return The portion of the string before the delimiter.
 */
std::string splitAt(std::string& remainder, char delimiter);

/*!
 * @brief Checks if the given input is a valid integer.
 *
 * @param input The input string to be checked.
 * @return True if the input is a valid integer; otherwise, false.
 */
bool integerInputCheck(std::string& input);

/*!
 * @brief Checks if the given input is a valid string.
 *
 * @param input The input string to be checked.
 * @return True if the input is a valid string; otherwise, false.
 */
bool stringInputCheck(std::string& input);

/*!
 * @brief Checks if the given input is a valid floating-point number.
 *
 * @param input The input string to be checked.
 * @return True if the input is a valid floating-point number; otherwise, false.
 */
bool floatInputCheck(std::string& input);

/*!
 * @brief Checks if the given string is a valid filename.
 *
 * @param filename The string to be checked as a filename.
 * @return True if the input is a valid filename; otherwise, false.
 */
bool isValidFilename(const std::string& filename);

/*!
 * @brief Checks if the given input consists of printable characters.
 *
 * @param input The input string to be checked.
 * @return True if the input consists of printable characters; otherwise, false.
 */
bool isPrintableInput(std::string& input);


#endif /* FORMATTERFILE_H_ */
