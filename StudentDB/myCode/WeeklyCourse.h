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

/*!
 * @class WeeklyCourse
 * @brief Represents a weekly course with specific scheduling details.
 */
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
     * @brief Parameterized constructor for WeeklyCourse.
     *
     * Initializes all members of the abstract class and derived class.
     *
     * @param courseKey 	Unique identifier for the course.
     * @param title 		Title of the course.
     * @param major 		Major associated with the course.
     * @param creditPoints 	Number of credit points for the course.
     * @param daysOfWeek 	Days of the week the course is scheduled (Sunday - 0, Saturday - 6).
     * @param startTime 	Start time of the course.
     * @param endTime 		End time of the course.
     */
	WeeklyCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::DateTime::DaysOfWeek daysOfWeek,
			Poco::Data::Time startTime, Poco::Data::Time endTime);

	/*!
	 * @brief A Default destructor for WeeklyCourse class.
	 *
	 */
	virtual ~WeeklyCourse();

    /*!
     * @brief Getter method for the day of the week for the weekly course.
     *
     * @return Poco::DateTime::DaysOfWeek (Sunday - 0, Saturday - 6).
     */
	Poco::DateTime::DaysOfWeek getDaysOfWeek() const;

    /*!
     * @brief Getter method for the start time of the course.
     *
     * @return Poco::Data::Time representing the start time.
     */
	Poco::Data::Time getStartTime() const;

    /*!
     * @brief Getter method for the end time of the course.
     *
     * @return Poco::Data::Time representing the end time.
     */
	Poco::Data::Time getEndTime() const;

    /*!
     * @brief Print method that outputs the data of the weekly course.
     *
     * @return String representation of the course data.
     */
	std::string printWeeklyCourse() const;

	/**
	 * @brief Prints specific information about the WeeklyCourse.
	 *
	 * This function prints additional details specific to the WeeklyCourse,
	 * such as day of week, start and end times.
	 *
	 * @note This function overrides the virtual function in the base Course class.
	 */
	void print() const override;
};

#endif /* WEEKLYCOURSE_H_ */