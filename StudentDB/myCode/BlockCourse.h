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

/*!
 * @class BlockCourse
 * @brief Represents a block course with specific scheduling details.
 */
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
     * @brief Parameterized constructor for BlockCourse.
     *
     * Initializes all members of the abstract class and derived class.
     *
     * @param courseKey 	Unique identifier for the course.
     * @param title 		Title of the course.
     * @param major 		Major associated with the course.
     * @param creditPoints	Number of credit points for the course.
     * @param startDate 	Start date of the course.
     * @param endDate 		End date of the course.
     * @param startTime		Start time of the course.
     * @param endTime 		End time of the course.
     */
	BlockCourse(unsigned int courseKey, std::string title, std::string major,
			float creditPoints, Poco::Data::Date startDate, Poco::Data::Date endDate,
			Poco::Data::Time startTime, Poco::Data::Time endTime);

	/*!
	 * @brief Default destructor for BlockCourse class.
	 */
	virtual ~BlockCourse();

    /*!
     * @brief Getter method for the start date of the course.
     *
     * @return Poco::Data::Date representing the start date.
     */
	Poco::Data::Date getStartDate() const;

    /*!
     * @brief Getter method for the end date of the course.
     *
     * @return Poco::Data::Date representing the end date.
     */
	Poco::Data::Date getEndDate() const;

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
     * @brief Print method that outputs the data of the block course.
     *
     * @return String representation of the course data.
     */
	std::string printBlockCourse() const;

	/**
	 * @brief Prints specific information about the BlockCourse.
	 *
	 * This function prints additional details specific to the BlockCourse,
	 * such as start and end dates, start and end times.
	 *
	 * @note This function overrides the virtual function in the base Course class.
	 */
	void print() const override;
};

#endif /* BLOCKCOURSE_H_ */
