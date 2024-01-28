/*!
 * @file SimpleUI.h
 *
 * \n Created on: 13-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDb.h"
#include <fstream>
/*!
 * @class SimpleUI
 * @brief Represents a simple user interface for interacting with a Student Database.
 */
class SimpleUI
{
private:
    /*!
     * @var m_db - A reference to the StudentDb class.
     */
    StudentDb& m_db;

public:
    /*!
     * @brief Parameterized constructor for SimpleUI.
     *
     * Initializes the SimpleUI class with a reference to a StudentDb object.
     *
     * @param db A reference to the StudentDb class.
     */
    SimpleUI(StudentDb& db);

    /*!
     * @brief Default destructor for the SimpleUI class.
     */
    virtual ~SimpleUI();

    /*!
     * @brief Lists all the properties available in the database, requests input from the user,
     *        and executes the respective operation.
     */
    void run();

    /*!
     * @brief Get user inputs for creating a new course.
     */
    void getUserInputsforNewCourse();

    /*!
     * @brief List's all courses.
     */
    void listCourses();

    /*!
     * @brief Get user inputs for adding a new student.
     */
    void getUserInputsforNewStudent();

    /*!
     * @brief Get user inputs for enrolling a student in a course.
     */
    void getUserInputforNewEnrollment();

    /*!
     * @brief Print details of a student, including enrolled courses and results.
     *
     * Queries the user for a matrikel number and prints the corresponding student details.
     */
    void printStudent();

    /*!
     * @brief Search for students based on a provided string.
     *
     * Queries the user for a string and prints the matrikel number, last name, and first name of all students
     * having the provided string as a substring in their first or last name.
     */
    void searchStudent();

    /*!
     * @brief Get user inputs for updating student information.
     */
    void getUserInputforStudentUpdate();

    /*!
     * @brief Perform updates on a Student object.
     *
     * @param updateStudent Reference to a Student object.
     */
    void performStudentUpdate(Student& updateStudent);

    /*!
     * @brief Get user inputs for updating student's address information.
     *
     * @param updateStudent Reference to a Student object.
     */
    void getUserInputforAddressUpdate(Student& updateStudent);

    /*!
     * @brief Perform updates on a student's enrollment information.
     *
     * @param updateStudent Reference to a Student object.
     * @param courseKey The key of the course to be updated.
     */
    void performEnrollmentUpdate(Student& updateStudent, const std::string& courseKey);
};


#endif /* SIMPLEUI_H_ */
