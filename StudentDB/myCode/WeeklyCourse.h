/*!
 * @file WeeklyCourse.h
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"

class WeeklyCourse: public Course
{
private:
	/*!
	 * @var m_daysOfWeek - stores the day in which the course takes place.
	 */
	Poco::DateTime::DaysOfWeek m_daysOfWeek;

	/*!
	 * @var m_startTime - stores the start time of the course.
	 */
	Poco::Data::Time m_startTime;

	/*!
	 * @var m_endTime - stores the end time of the course.
	 */
	Poco::Data::Time m_endTime;

public:
	/*!
	 *
	 * @param courseKey
	 * @param title
	 * @param major
	 * @param creditPoints
	 * @param daysOfWeek
	 * @param startTime
	 * @param endTime
	 */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
			Poco::DateTime::DaysOfWeek daysOfWeek, Poco::Data::Time startTime, Poco::Data::Time endTime);

	/*!
	 * A Default destructor for WeeklyCourse class.
	 */
	virtual ~WeeklyCourse();

	/*!
	 * A getter method that returns the day of the week for the weekly course.
	 * @return Poco::DateTime::DaysOfWeek (Sunday - 0, Saturday -6)
	 */
	Poco::DateTime::DaysOfWeek getDaysOfWeek() const;

	/*!
	 * A getter method that returns the start time of the course.
	 * @return Poco::Data::Time
	 */
	Poco::Data::Time getStartTime() const;

	/*!
	 * A getter method that returns the end time of the course.
	 * @return Poco::Data::Time
	 */
	Poco::Data::Time getEndTime() const;

	std::string printWeeklyCourse() const;

	void print() const override;
};

#endif /* WEEKLYCOURSE_H_ */
