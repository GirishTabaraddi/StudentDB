//! Standard (system) header files
#include <iostream>
#include <cstdlib>

using namespace std;

//! Add your project's header files here
#include "SimpleUI.h"

#include "formatterfile.h"

//! Main program
int main ()
{
	cout << "StudentDB started." << endl << endl;

	StudentDb Database;

	SimpleUI UI(Database);

	UI.run();

	return 0;
}


/*!
 * @startuml

	class SimpleUI
	{
		-m_db : StudentDb&

		+SimpleUI(StudentDb& db)
		+~SimpleUI()
		+run() : void
	}

	class StudentDb
	{
		-m_students : std::map<int, Student>
		-m_courses : std::map<int, std::unique_ptr<const Course>>

		-updateAddress(Student& student) : void
		-updateDateofBirth(Student& student) : void
		-updateFirstName(Student& student) : void
		-updateLastName(Student& student) : void
		-performEnrollmentUpdate(Student& student, std::string& courseKey) : void
		-performStudentUpdate(Student& student) : void

		+StudentDb()
		+getstudents() : std::map<int , Student> {query}
		+getcourses() : std::map<int , std::unique_ptr<const Course>>& {query}
		+addEnrollment() : void
		+addNewCourse() : void
		+addNewStudent() : void
		+listCourses() : void
		+printDb() : void {query}
		+printStudent() : void
		+searchStudent() : void
		+updateStudent() : void
	}

	class Student
	{
		-m_dateOfBirth : Poco::Data::Date
		-{static} m_nextMatrikelNumber : static unsigned int
		-m_firstName : std::string
		-m_lastName : std::string
		-m_address : std::shared_ptr<Address>
		-m_enrollments : std::vector<Enrollment>
		-m_matrikelNumber : unsigned int

		+Student(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth, std::shared_ptr<Address> address)
		+~Student()
		+getDoB() : Poco::Data::Date {query}
		+getaddress() : std::shared_ptr<Address> {query}
		+getFullName() : std::string {query}
		+printStudent() : std::string {query}
		+getfirstName() : std::string& {query}
		+getlastName() : std::string& {query}
		+getenrollments() : std::vector<Enrollment>& {query}
		+getmatrikelNumber() : unsigned int {query}
		+addEnrollment(const std::string& semester, Course* courseId) : void
		+deleteEnrollment(unsigned int courseKey) : void
		+updateAddress(std::shared_ptr<Address> address) : void
		+updateGrade(float grade, unsigned int courseKey) : void
		+updateStudent(std::string firstName, std::string lastName,
			Poco::Data::Date dateOfBirth) : void
	}

	class Address
	{
		-m_additionalInfo : std::string
		-m_cityName : std::string
		-m_street : std::string
		-m_postalCode : unsigned short

		+Address(std::string street, unsigned short postalCode,
			std::string cityName, std::string additionalInfo)
		+~Address()
		+printAddress() : std::string {query}
		+getadditionalInfo() : std::string& {query}
		+getcityName() : std::string& {query}
		+getstreet() : std::string& {query}
		+getpostalCode() : unsigned short {query}
	}

	class Enrollment
	{
		-m_course : const Course*
		-m_grade : float
		-m_semester : std::string

		+Enrollment(std::string semester, const Course* courseObj)
		+~Enrollment()
		+getcourse() : Course* {query}
		+getgrade() : float {query}
		+printEnrollment() : std::string {query}
		+getsemester() : std::string& {query}
		+setgrade(float grade) : void
	}

	abstract class Course
	{
		-m_courseKey : unsigned int
		-m_creditPoints : float
		-m_majorById : std::map<unsigned char, std::string>
		-m_major : unsigned char
		-m_title : std::string

		-setMajor(std::string major) : void
		-setmajorById(std::string major) : void

		+Course(unsigned int courseKey, std::string title, std::string major, float creditPoints)
		+~Course()
		+getcreditPoints() : float {query}
		+getmajorById() : std::map<unsigned char , std::string> {query}
		+gettitle() : std::string {query}
		+printCourse() : std::string {query}
		+getmajor() : unsigned char {query}
		+getcourseKey() : unsigned int {query}
		+{abstract} print() : void {query}
	}

	class BlockCourse
	{
		-m_endDate : Poco::Data::Date
		-m_startDate : Poco::Data::Date
		-m_endTime : Poco::Data::Time
		-m_startTime : Poco::Data::Time

		+BlockCourse(unsigned int courseKey, std::string title,
			std::string major, float creditPoints, Poco::Data::Date startDate,
			Poco::Data::Date endDate, Poco::Data::Time startTime, Poco::Data::Time endTime)
		+~BlockCourse()
		+getEndDate() : Poco::Data::Date {query}
		+getStartDate() : Poco::Data::Date {query}
		+getEndTime() : Poco::Data::Time {query}
		+getStartTime() : Poco::Data::Time {query}
		+printBlockCourse() : std::string {query}
		+print() : void {query}
	}

	class WeeklyCourse
	{
		-m_endTime : Poco::Data::Time
		-m_startTime : Poco::Data::Time
		-m_daysOfWeek : Poco::DateTime::DaysOfWeek

		+WeeklyCourse(unsigned int courseKey, std::string title,
			std::string major, float creditPoints, Poco::DateTime::DaysOfWeek daysOfWeek,
			Poco::Data::Time startTime, Poco::Data::Time endTime)
		+~WeeklyCourse()
		+getDaysOfWeek() : Poco::DateTime::DaysOfWeek {query}
		+getEndTime() : Poco::Data::Time {query}
		+getStartTime() : Poco::Data::Time {query}
		+printWeeklyCourse() : std::string {query}
		+print() : void {query}
	}

 * SimpleUI --> StudentDb : Association
 * StudentDb *--> Student : Composition
 * StudentDb *--> Course : Composition
 * Student *--> Enrollment : Composition
 * Enrollment o--> Course : Aggregation
 * Student *--> Address : Composition
 * BlockCourse --|> Course : Inheritance
 * WeeklyCourse --|> Course : Inheritance

 * @enduml
 */
