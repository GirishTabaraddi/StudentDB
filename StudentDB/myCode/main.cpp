//! Standard (system) header files
#include <iostream>
#include <cstdlib>

using namespace std;

//! Add your project's header files here
#include "Student.h"
#include "StudentDb.h"


//! Main program
int main ()
{
	cout << "StudentDB started." << endl << endl;

//	Course c(1234, "APT", "Automation", 5);

//	c.printCourse();

//	Enrollment e("WS2023", &c);

//	e.printEnrollment();
//
//	shared_ptr<Address> address = make_shared<Address>("Am Karlshof", 64287, "Darmstadt", "xyz Info");
//
//	Poco::Data::Date dateOfBirth(1997,3,31);
//
//	Student s("Girish", "Tabaraddi", dateOfBirth, address);
//
//	s.addEnrollment("WS2023", &c);
//	s.printStudent();
//
//	Course c1(1235, "ASDT", "Embedded", 5);
//
//	s.addEnrollment("WS2023", &c1);
//	s.printStudent();
//
//	s.addEnrollment("WS2024", &c);
//	s.printStudent();

	StudentDb Database;

	Database.addNewCourse();

	Database.addNewStudent();

	Database.printDb();

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
 *
 * 		+ Student()
 * 		+ ~Student()
 * 		+ const getmatrikelNumber(): unsigned int const
 * 		+ const getFullName(): std::string const
 * 		+ const getDoB(): Poco::Data::Date const
 * }
 *
 * class Course
 * {
 * 		- m_majorById: std::map<unsigned char, std::string>
 * 		- m_courseKey: unsigned int
 * 		- m_title: std::string
 * 		- m_major: unsigned char
 * 		- m_creditPoints: float
 *
 * 		- setMajor(): void
 * 		- setmajorById(): void
 *
 * 		+ Course(major: std::string)
 * 		+ ~Course()
 * 		+ const getmajorById(): std::map<unsigned char, std::string> const
 * 		+ const getcourseKey(): unsigned int const
 * 		+ const gettitle(): std::string const
 * 		+ const getmajor(): unsigned char
 * 		+ const getcreditPoints(): float const
 * }
 *
 * StudentDb *--> Student : Composition
 * StudentDb *--> Course : Composition
 *
 * Class Enrollment
 * {
 * 		- m_grade: float
 * 		- m_semester: std::string
 * 		- m_course: Course*
 *
 * 		+ Enrollment(courseObj: const Course*)
 * 		+ ~Enrollment()
 * 		+ const getgrade(): float const
 * 		+ const getsemester(): std::string const
 * }
 *
 * Student *--> Enrollment : Composition
 *
 * Enrollment o--> Course : Aggregation
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
