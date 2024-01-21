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

#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketStream.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <Poco/Timespan.h>
#include <Poco/JSON/Object.h>
#include <Poco/DynamicStruct.h>
#include <Poco/UTFString.h>

#include <boost/asio.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

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
    std::map<int, Student>& getStudents();

    /*!
     * @brief Getter method to fetch the courses.
     *
     * @return Map representing the courses.
     */
    std::map<int, std::unique_ptr<const Course>>& getCourses();

    /*!
     * @brief Add a new course to the database.
     *
     * Queries the user for the required data and creates a new course in the database.
     */
    void addNewCourse(std::string& courseKey,std::string& title,
    		std::string& major,std::string& credits,
			std::string& courseType,std::string& startTime,
			std::string& endTime,std::string& startDate,
			std::string& endDate,std::string& dayOfWeek);

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
    void addNewStudent(std::string& firstName,std::string& lastName,
    		std::string& DoBstring,std::string& streetName,
			std::string& postalCode,std::string& cityName,
			std::string& additionalInfo);

    /*!
     * @brief Add enrollment for a student.
     *
     * Queries the user for a matrikel number, a course id, a semester, and adds the enrollment.
     * If the enrollment already exists, a warning message is printed.
     */
    void addEnrollment(std::string& matrikelNumber, std::string& semester,
    		std::string& courseKey);

    /*!
     * @brief Print all Students in the entire database.
     *
     * This method prints the details of all students in the database
     * to the specified output stream.
     *
     * @param out The output stream where student data will be printed.
     */
    void printAllStudentsDb(std::ostream &out) const;


    /*!
     * @brief Print all Courses in the entire database.
     *
     * This method prints the details of all courses in the database
     * to the specified output stream.
     *
     * @param out The output stream where course data will be printed.
     */
    void printAllCoursesDb(std::ostream &out) const;

    /*!
     * @brief Print all Enrollments of the Student.
     *
     * This method prints the details of all enrollments for each student
     * in the database to the specified output stream.
     *
     * @param out The output stream where enrollment data will be printed.
     */
    void printAllEnrollments(std::ostream &out) const;

    /*!
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

    /*!
     * @brief Reads data from the input stream.
     *
     * This function reads data from the provided input stream and processes
     * it accordingly. The exact behavior depends on the specific implementation
     * of the derived class.
     *
     * @param in The input stream to read data from.
     */
    void read(std::istream& in);

    /*!
     * @brief Reads data from the server.
     */
    void readFromServer();

    /*!
     * @brief Processes courses data from the input stream.
     *
     * This function processes courses data read from the input stream. It parses
     * the input and updates the internal data structures accordingly.
     *
     * @param in The input stream containing courses data.
     */
    void processCoursesData(std::istream &in);

    /*!
     * @brief Processes students data from the input stream.
     *
     * This function processes students data read from the input stream. It parses
     * the input and updates the internal data structures accordingly.
     *
     * @param in The input stream containing students data.
     */
    void processStudentsData(std::istream &in);

    /*!
     * @brief Processes enrollment data from the input stream.
     *
     * This function processes enrollment data read from the input stream. It parses
     * the input and updates the internal data structures accordingly.
     *
     * @param in The input stream containing enrollment data.
     */
    void processEnrollmentData(std::istream &in);

    /*!
     * @brief Parses JSON data.
     *
     * This function uses POCO C++ JSON for parsing data. For more information,
     * refer to the following Stack Overflow post:
     *
     * @see []
     * ()
     *
     * @param JSONData The JSON data to be parsed.
     */
    void parsingJSONData(std::string& JSONData);
};


#endif /* STUDENTDB_H_ */
