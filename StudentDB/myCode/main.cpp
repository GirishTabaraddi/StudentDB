//! Standard (system) header files
#include <iostream>
#include <cstdlib>

using namespace std;

//! Add your project's header files here


//! Main program
int main ()
{
	cout << "StudentDB started." << endl << endl;

	return 0;
}




/*
 *
 * @startuml
 *
 * class SimpleUI
 * {
 * 		+ SimpleUI(db: StudentDb&)
 * 		+ run(): void
 * }
 *
 * class StudentDb
 * {
 * 		- m_students: std::map<int, student>
 * 		- m_courses: std::map<int, std::unique_ptr<const Course>>
 * }
 *
 * SimpleUI --> StudentDb : Association
 *
 * class Student
 * {
 * 		- m_nextMatrikelNumber: unsigned int = 1000000
 * 		- m_matrikelNumber: unsigned int
 * 		- m_firstName: std::string
 * 		- m_lastName: std::string
 * 		- m_dataOfBirth: Poco::Data::Date
 * 		- m_enrollments: std::vector<Enrollment>
 * }
 *
 * Class Enrollment
 * {
 * 		- m_grade: float
 * 		- m_semester: std::string
 * 		- course: Course*
 * }
 *
 * Student *--> Enrollment : Composition
 *
 * class Course
 * {
 * 		- m_majorById: std::map<unsigned char, std::string>
 * 		- m_courseKey: unsigned int
 * 		- m_title: std::string
 * 		- m_major: unsigned char
 * 		- m_creditPoints: float
 * }
 *
 * Enrollment o--> Course : Aggregation
 *
 * StudentDb *--> Student : Composition
 * StudentDb *--> Course : Composition
 *
 * class Address
 * {
 * 		- m_street: std::string
 * 		- m_postalCode: unsigned short
 * 		- m_cityName: std::string
 * 		- m_additionalInfo: std::String
 * }
 *
 * Student *--> Address : Composition
 *
 * class BlockCourse
 * {
 * 		- m_startDate: Poco::Data::Date
 * 		- m_endDate: Poco::Data::Date
 * 		- m_startTime: Poco::Data::Time
 * 		- m_endTime: Poco::Data::Time
 * }
 *
 * class WeeklyCourse
 * {
 * 		- m_dayOfWeek: Poco::DataTime::DaysOfWeek
 * 		- m_startTime: Poco::Data::Time
 * 		- m_endTime: Poco::Data::Time
 * }
 *
 * BlockCourse --|> Course : Inheritance
 * WeeklyCourse --|> Course : Inheritance
 *
 * @enduml
 */
