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
     *
     */
    void getUserInputsforNewCourse();

    /*!
     *
     */
    void getUserInputsforNewStudent();

    /*!
     *
     */
    void getUserInputforNewEnrollment();

    /*!
     *
     */
    void getUserInputforStudentUpdate();

    /*!
     * @brief Private method to perform student updates.
     *
     * @param student Reference to a Student object.
     */
    void performStudentUpdate(Student& updateStudent);

    /*!
     *
     */
    void getUserInputforAddressUpdate(Student& updateStudent);

    /*!
     *
     * @param student
     * @param courseKey
     */
    void performEnrollmentUpdate(Student& updateStudent, const std::string& courseKey);

    /*!
     * @brief Print student details.
     *
     * Queries the user for a matrikel number and prints the student, including the enrolled courses and their results.
     */
    void printStudent(std::string& matrikelNumber);

    /*!
     * @brief Search for students.
     *
     * Queries the user for a string and prints the matrikel number, last name, and first name of all students
     * that have the provided string as a substring in their first or last name.
     */
    void searchStudent(std::string& searchString);
};


#endif /* SIMPLEUI_H_ */
