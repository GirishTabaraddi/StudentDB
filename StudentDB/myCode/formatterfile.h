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
#include <Poco/DateTimeFormatter.h>
#include <Poco/Data/Date.h>
#include <Poco/LocalDateTime.h>
#include <Poco/DateTimeParser.h>
#include <Poco/Timestamp.h>

std::string pocoDateToStringFromatter(const Poco::Data::Date &date);

Poco::Data::Date stringToPocoDateFormatter(const std::string& stringDate);

#endif /* FORMATTERFILE_H_ */
