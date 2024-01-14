/*!
 * @file BlockCourse.h
 *
 * \n Created on: 14-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"

class BlockCourse: public Course
{
private:
	/*!
	 * @var m_startDate - stores the start date of the block course.
	 */
	Poco::Data::Date m_startDate;

	/*!
	 * @var m_endDate - stores the end date of the block course.
	 */
	Poco::Data::Date m_endDate;
	/*!
	 * @var m_startTime - stores the start time of the block course.
	 */
	Poco::Data::Time m_startTime;

	/*!
	 * @var m_endTime - stores the end time of the block course.
	 */
	Poco::Data::Time m_endTime;

public:
	/*!
	 *
	 * @param courseKey
	 * @param title
	 * @param major
	 * @param creditPoints
	 * @param startDate
	 * @param endDate
	 * @param startTime
	 * @param endTime
	 */
	BlockCourse(unsigned int courseKey, std::string title, std::string major, float creditPoints,
			Poco::Data::Date startDate, Poco::Data::Date endDate, Poco::Data::Time startTime, Poco::Data::Time endTime);

	/*!
	 * A Default destructor for BlockCourse class.
	 */
	virtual ~BlockCourse();

	/*!
	 * A getter method that returns the start date of the course.
	 * @return Poco::Data::Date
	 */
	Poco::Data::Date getStartDate() const;

	/*!
	 * A getter method that returns the end date of the course.
	 * @return Poco::Data::Date
	 */
	Poco::Data::Date getEndDate() const;

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

	std::string printBlockCourse() const;

	void print() const override;
};

#endif /* BLOCKCOURSE_H_ */
