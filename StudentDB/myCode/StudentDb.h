/*!
 * @file StudentDb.h
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include "Student.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"

/*!
 * @class StudentDb
 * @brief Represents a database of students and courses with various operations.
 */
class StudentDb
{
private:
    /*!
     * @var m_students - A map variable that maps the student entered into the database with an integer key.
     */
    std::map<int, Student> m_students;

    /*!
     * @var m_courses - A map variable that stores the list of courses using a unique pointer and an integer as a key.
     */
    std::map<int, std::unique_ptr<const Course>> m_courses;

private:
    /*!
     * @brief Private method to perform student updates.
     *
     * @param student Reference to a Student object.
     */
    void performStudentUpdate(Student& student);

    /*!
     * @brief Private method to update the first name of the student.
     *
     * @param student Reference to a Student object.
     */
    void updateFirstName(Student& student);

    /*!
     * @brief Private method to update the last name of the student.
     *
     * @param student Reference to a Student object.
     */
    void updateLastName(Student& student);

    /*!
     * @brief Private method to update the date of birth of the student.
     *
     * @param student Reference to a Student object.
     */
    void updateDateOfBirth(Student& student);

    /*!
     * @brief Private method to update the address of the student.
     *
     * @param student Reference to a Student object.
     */
    void updateAddress(Student& student);

    /*!
     * @brief Private method to perform enrollment updates.
     *
     * @param student Reference to a Student object.
     * @param courseKey Reference to a string representing the course key.
     */
    void performEnrollmentUpdate(Student& student, const std::string& courseKey);

public:
    /*!
     * @brief Default constructor for StudentDb class.
     */
    StudentDb();

    /*!
     * @brief Getter method to fetch the students.
     *
     * @return Map representing the students.
     */
    const std::map<int, Student>& getStudents() const;

    /*!
     * @brief Getter method to fetch the courses.
     *
     * @return Map representing the courses.
     */
    const std::map<int, std::unique_ptr<const Course>>& getCourses() const;

    /*!
     * @brief Add a new course to the database.
     *
     * Queries the user for the required data and creates a new course in the database.
     */
    void addNewCourse();

    /*!
     * @brief List all courses in the database with their data.
     */
    void listCourses();

    /*!
     * @brief Add a new student to the database.
     *
     * Queries the user for the required data (member data of Student and Address)
     * and creates a new student in the database.
     */
    void addNewStudent();

    /*!
     * @brief Add enrollment for a student.
     *
     * Queries the user for a matrikel number, a course id, a semester, and adds the enrollment.
     * If the enrollment already exists, a warning message is printed.
     */
    void addEnrollment();

    /*!
     * @brief Print student details.
     *
     * Queries the user for a matrikel number and prints the student, including the enrolled courses and their results.
     */
    void printStudent();

    /*!
     * @brief Search for students.
     *
     * Queries the user for a string and prints the matrikel number, last name, and first name of all students
     * that have the provided string as a substring in their first or last name.
     */
    void searchStudent();

    /*!
     * @brief Update student details.
     *
     * Queries the user for a matrikel number. If the corresponding student is found in the database,
     * the properties (except for the matrikel number) are presented in a numbered list.
     * Entering the item number allows the user to modify the property; entering "0" terminates the update.
     */
    void updateStudent();

    /**
     * @brief Print all Students in the entire database.
     *
     * This method prints the details of all students in the database
     * to the specified output stream.
     *
     * @param out The output stream where student data will be printed.
     */
    void printAllStudentsDb(std::ostream &out) const;


    /**
     * @brief Print all Courses in the entire database.
     *
     * This method prints the details of all courses in the database
     * to the specified output stream.
     *
     * @param out The output stream where course data will be printed.
     */
    void printAllCoursesDb(std::ostream &out) const;

    /**
     * @brief Print all Enrollments of the Student.
     *
     * This method prints the details of all enrollments for each student
     * in the database to the specified output stream.
     *
     * @param out The output stream where enrollment data will be printed.
     */
    void printAllEnrollments(std::ostream &out) const;

    /**
     * @brief Write all student and course data to the provided output stream.
     *
     * This method writes the data of all students and courses in the database to
     * the specified output stream. It calls the write method of each student and
     * course to represent themselves in a standardized format when output is needed,
     * such as writing to a file or printing to the console.
     *
     * @param out The output stream where the student and course data will be written.
     */
    void write(std::ostream& out) const;

};


#endif /* STUDENTDB_H_ */
