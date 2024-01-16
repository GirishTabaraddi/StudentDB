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

#include "Enrollment.h"
#include "Address.h"
#include "formatterfile.h"

#include <vector>
#include <memory>

/*!
 * @class Student
 * @brief Represents a student with associated details and enrollment information.
 */
class Student {
private:
    /*!
     * @var m_nextMatrikelNumber - Next Matrikel Number incremented after assigning to a student.
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
     * @var m_address - A shared pointer that holds the details of the Address class.
     */
    std::shared_ptr<Address> m_address;

public:
    /*!
     * @brief Parameterized constructor for the Student class.
     *
     * Initializes the private members of the Student class, including a shared pointer to the address.
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
     * @return unsigned integer representing the Matrikel number.
     */
    const unsigned int getMatrikelNumber() const;

    /*!
     * @brief Getter method that returns a string of the full name (first name + last name).
     *
     * @return std::string representing the full name.
     */
    const std::string getFullName() const;

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
     * @return Shared pointer of class Address representing the address.
     */
    const std::shared_ptr<Address> getAddress() const;

    /*!
     * @brief Method to print the student details.
     *
     * @return std::string representing the formatted student information.
     */
    std::string printStudent() const;

    /*!
     * @brief Add enrollment for the student.
     *
     * Queries the user for a matrikel number, a course id, and a semester, and adds the enrollment.
     * If the enrollment already exists, a warning message is printed.
     *
     * @param semester Semester for the enrollment.
     * @param courseId Pointer to the Course object.
     */
    void addEnrollment(const std::string& semester, Course* courseId);

    /*!
     * @brief Update the student details.
     *
     * @param firstName New first name.
     * @param lastName New last name.
     * @param dateOfBirth New date of birth.
     */
    void updateStudent(std::string firstName, std::string lastName, Poco::Data::Date dateOfBirth);

    /*!
     * @brief Update the address of the student.
     *
     * @param address Shared pointer to the Address class representing the new address.
     */
    void updateAddress(std::shared_ptr<Address> address);

    /*!
     * @brief Delete enrollment based on the course key.
     *
     * @param courseKey Course key for the enrollment to be deleted.
     */
    void deleteEnrollment(unsigned int courseKey);

    /*!
     * @brief Update the grade for a specific enrollment.
     *
     * @param grade New grade value.
     * @param courseKey Course key for the enrollment to be updated.
     */
    void updateGrade(float grade, unsigned int courseKey);

    /**
     * @brief Write the student's data to the provided output stream.
     *
     * This virtual method is intended to be overridden by derived classes
     * to write the specific data of the student to the output stream. It
     * allows objects to represent themselves in a standardized format when
     * output is needed, such as writing to a file or printing to the console.
     *
     * @param out The output stream where the student's data will be written.
     */
    virtual void write(std::ostream& out) const;

};


#endif /* STUDENT_H_ */
