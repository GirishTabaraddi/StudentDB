/*!
 * @file Student.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <vector>

#include "Enrollment.h"
#include "Address.h"

/*!
 * @class Student
 * @brief Represents a student with associated
 * details and enrollment information.
 */
class Student
{
private:
	/*!
	 * @var m_nextMatrikelNumber - Next Matrikel Number
	 * incremented after assigning to a student.
	 */
	static unsigned int m_nextMatrikelNumber;

	/*!
	 * @var m_matrikelNumber - A student's Matrikel Number.
	 */
	unsigned int m_matrikelNumber;

	/*!
	 * @var m_firstName - Student's first name.
	 */
	std::string m_firstName;

	/*!
	 * @var m_lastName - Student's last name.
	 */
	std::string m_lastName;

	/*!
	 * @var m_dateOfBirth - Student's date of birth.
	 */
	Poco::Data::Date m_dateOfBirth;

	/*!
	 * @var m_enrollments - A vector of enrollments for a student.
	 */
	std::vector<Enrollment> m_enrollments;

	/*!
	 * @var m_address - A shared pointer that holds the
	 * details of the Address class.
	 */
	std::shared_ptr<Address> m_address;

public:
	/*!
	 * @brief Parameterized constructor for the Student class.
	 *
	 * Initializes the private members of the Student class,
	 * including a shared pointer to the address.
	 *
	 * @param firstName Student's first name.
	 * @param lastName Student's last name.
	 * @param dateOfBirth Student's date of birth.
	 * @param address Shared pointer to the Address class.
	 */
	Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address);

	/*!
	 * @brief Default destructor for the Student class.
	 */
	virtual ~Student();

	/*!
	 * @brief Getter method that returns the Matrikel number of a student.
	 *
	 * @return The Matrikel number as an unsigned integer.
	 */
	const unsigned int getMatrikelNumber() const;

	/*!
	 * @brief Getter method that returns a string of the first name.
	 *
	 * @return std::string representing the first name.
	 */
	const std::string& getFirstName() const;

	/*!
	 * @brief Getter method that returns a string of the last name.
	 *
	 * @return std::string representing the last name.
	 */
	const std::string& getLastName() const;

	/*!
	 * @brief Getter method to obtain the date of birth of a student.
	 *
	 * @return Poco::Data::Date representing the date of birth.
	 */
	const Poco::Data::Date getDateOfBirth() const;

	/*!
	 * @brief Getter method to list all the enrollments done.
	 *
	 * @return Vector of class Enrollment representing the enrollments.
	 */
	const std::vector<Enrollment>& getEnrollments() const;

	/*!
	 * @brief Getter method to obtain the Address class.
	 *
	 * @return Shared pointer of class Address
	 * representing the address.
	 */
	const std::shared_ptr<Address> getAddress() const;

	/*!
	 * @brief Setter method that sets the next Matrikel
	 * number for new students.
	 *
	 * @param newMatrikelNumber The new Matrikel number to set.
	 */
	static void setNextMatrikelNumber(unsigned int newMatrikelNumber);

	/**
	 * @brief Set the first name of the student.
	 *
	 * @param firstName New first name.
	 */
	void setFirstName(const std::string& firstName);

	/**
	 * @brief Set the last name of the student.
	 *
	 * @param lastName New last name.
	 */
	void setLastName(const std::string& lastName);

	/**
	 * @brief Set the date of birth of the student.
	 *
	 * @param dateOfBirth New date of birth.
	 */
	void setDateOfBirth(const Poco::Data::Date& dateOfBirth);

	/**
	 * @brief Update the address of the student.
	 *
	 * @param address Shared pointer to the Address class
	 * representing the new address.
	 */
	void setAddress(const std::shared_ptr<Address> address);

	/*!
	 * @brief Add enrollment for the student.
	 *
	 * Queries the user for a matrikel number, a course id, and a semester,
	 * and adds the enrollment.
	 * If the enrollment already exists, a warning message is printed.
	 *
	 * @param semester Semester for the enrollment.
	 * @param courseId Pointer to the Course object.
	 */
	void addEnrollment(const std::string& semester, const Course* courseId);

	/*!
	 * @brief Delete enrollment based on the course key.
	 *
	 * @param courseKey Course key for the enrollment to be deleted.
	 */
	void deleteEnrollment(const unsigned int& courseKey);

	/*!
	 * @brief Update the grade for a specific enrollment.
	 *
	 * @param grade New grade value.
	 * @param courseKey Course key for the enrollment to be updated.
	 */
	void updateGrade(const float& grade, const unsigned int& courseKey);

	/**
	 * @brief Write the student's data to the provided output stream.
	 *
	 * This method writes the basic details of the student to the output stream.
	 * It is intended to be used as a default implementation for writing student
	 * details.
	 *
	 * @param out The output stream where the student's data will be written.
	 */
	void write(std::ostream& out) const;

	/*!
	 * @brief Read a Student object from the specified input stream.
	 *
	 * This static function reads information from the given input stream and
	 * constructs a Student object based on the data. The input stream is expected
	 * to contain semicolon-separated values representing matrikel number,
	 * first name, last name, date of birth, street name, postal code,
	 * city name, and additional address information.
	 *
	 * @param in The input stream from which the Student information will be read.
	 * @return The constructed Student object.
	 */
	static Student read(std::istream& in);

	/**
	 * @brief Create a Student object from JSON data.
	 *
	 * This static method takes a boost::json::object representing JSON data
	 * and constructs a Student object from it.
	 *
	 * @param jsonDataObject The boost::json::object containing JSON data.
	 * @return A pointer to the dynamically allocated Student object,
	 *         or nullptr if the input data is invalid.
	 *         The caller is responsible for deleting the allocated memory.
	 */
	static Student* fromJson(const boost::json::object &jsonDataObject);

	boost::json::object toJson() const;
};

#endif /* STUDENT_H_ */
