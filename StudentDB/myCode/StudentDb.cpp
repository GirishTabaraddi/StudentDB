/*!
 * @file StudentDb.cpp
 *
 * \n Created on: 09-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "StudentDb.h"

using namespace std;

StudentDb::StudentDb()
{
}

const std::map<int, Student>& StudentDb::getStudents() const
{
	return this->m_students;
}

const std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses() const
{
	return this->m_courses;
}

void StudentDb::addNewCourse()
{
	//	unique_ptr<const Course> course = make_unique<Course>(1234, "APT", "Automation", 5);
	//	unique_ptr<const Course> course1 = make_unique<Course>(1235, "EOS", "Embedded", 5);
	//
	//	this->m_courses.insert(make_pair(course->getcourseKey(), move(course)));
	//	this->m_courses.insert(make_pair(course1->getcourseKey(), move(course1)));

	string courseKey = "0";
	string title = "NA";
	string major = "NA";
	string credits = "0.0";

	string startTime = "0";
	string endTime = "0";
	string startDate = "0";
	string endDate = "0";
	string dayOfWeek = "0";
	string courseType = "NA";

	cout << endl << "\t \t Enter CourseKey: ";
	getline(cin, courseKey);

	cout << endl << "\t \t Enter Title of the Course: ";
	getline(cin, title);

	cout << endl << "\t \t Enter the Major in which the Course belongs to: ";
	getline(cin, major);

	cout << endl << "\t \t Enter the  credit points of the Course: ";
	getline(cin, credits);

	cout << endl << "\t \t Enter the Course Type - Weekly(W)/Block(B): ";
	getline(cin, courseType);

	cout << endl << "\t \t Enter the Course Start Time - HH:MM : ";
	getline(cin, startTime);

	cout << endl << "\t \t Enter the Course End Time - HH:MM : ";
	getline(cin, endTime);

	if(courseType == "B" || courseType == "b")
	{
		cout << endl << "\t \t Enter the Course Start Date - dd.mm.YYYY : ";
		getline(cin, startDate);

		cout << endl << "\t \t Enter the Course End Date - dd.mm.YYYY : ";
		getline(cin, endDate);

		unique_ptr<BlockCourse> blockCourse =
				make_unique<BlockCourse>(stoi(courseKey), title, major, stof(credits),
						stringToPocoDateFormatter(startDate), stringToPocoDateFormatter(endDate),
						stringToPocoTimeFormatter(startTime), stringToPocoTimeFormatter(endTime));

		this->m_courses.insert(make_pair(blockCourse->getcourseKey(), move(blockCourse)));
	}
	if(courseType == "W" || courseType == "w")
	{
		cout << endl << "\t \t Enter the Course Week - Monday-Sunday : ";
		getline(cin, dayOfWeek);

		Poco::DateTime::DaysOfWeek dayOfWeekinPoco = getDayOfWeekFromString(dayOfWeek);

		unique_ptr<WeeklyCourse> weeklyCourse = make_unique<WeeklyCourse>(stoi(courseKey),
				title, major, stof(credits), dayOfWeekinPoco,
				stringToPocoTimeFormatter(startTime), stringToPocoTimeFormatter(endTime));

		this->m_courses.insert(make_pair(weeklyCourse->getcourseKey(), move(weeklyCourse)));
	}
}

void StudentDb::listCourses()
{
	cout << this->m_courses.size() << endl;

	for(const auto& courses: this->m_courses)
	{
//		courses.second.get()->print();
		ostream& out = cout;
		courses.second.get()->write(out);
	}
}

void StudentDb::addNewStudent()
{
	//	shared_ptr<Address> address = make_shared<Address>("Am Karlshof", 64287, "Darmstadt", "xyz Info");
	//
	//	Poco::Data::Date dateOfBirth(1997,3,31);
	//
	//	Student student = Student("Girish", "Tabaraddi", dateOfBirth, address);
	//
	//	this->m_students.insert(make_pair(student.getmatrikelNumber(), student));

	string firstName = "NA";
	string lastName = "NA";
	string DoBstring = "01.01.1990";
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "\t \t Enter First Name of the Student - a-z/A-Z: ";
	getline(cin, firstName);

	cout << endl << "\t \t Enter Last Name of the Student - a-z/A-Z: ";
	getline(cin, lastName);

	cout << endl << "\t \t Enter Date of Birth of the Student - dd..mm..YYY : ";
	getline(cin, DoBstring);

	cout << endl << "\t \t Enter Street Name of the Student's Address - a-z/A-Z: ";
	getline(cin, streetName);

	cout << endl << "\t \t Enter Postal Code of the Student's Address - 0-9: ";
	getline(cin, postalCode);

	cout << endl << "\t \t Enter City Name of the Student's Address - a-z/A-Z: ";
	getline(cin, cityName);

	cout << endl << "\t \t Enter Additional Info related Student's Address - 0-9/a-z/A-Z: ";
	getline(cin, additionalInfo);

	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode), cityName, additionalInfo);

	Student student = Student(firstName, lastName, stringToPocoDateFormatter(DoBstring), address);

	this->m_students.insert(make_pair(student.getMatrikelNumber(), student));
}

void StudentDb::addEnrollment()
{
	string matrikelNumber = "0";
	string semester = "0";
	string courseKey = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to add his/her Enrollment - 0-9: ";
	getline(cin, matrikelNumber);

	cout << endl << "\t \t Enter the Semester of the Student "
			"studying currently - a-z/A-Z/0-9: ";
	getline(cin, semester);

	cout << endl << "\t \t Enter the Course Key, "
			"to which he/she wants to enroll - 0-9: ";
	getline(cin, courseKey);

	auto matrikelNumberItr = this->m_students.find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_students.end())
	{
		auto findCourseIdItr = this->m_courses.find(stoi(courseKey));

		if(findCourseIdItr != this->m_courses.end())
		{
			Course* course = const_cast<Course*>(findCourseIdItr->second.get());

			matrikelNumberItr->second.addEnrollment(semester, course);

			cout << "\t \t Enrollment Added" << endl;
		}
		else
		{
			cout << endl << "\t \t \t ERROR: Entered Course Key "
					"doesn't exist in the database!!!" << endl;
		}
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Matrikel Number "
				"doesn't exist in the database!!!" << endl;
	}

	//	for(auto& pairItr : this->m_students)
	//	{
	//		auto enrollments = pairItr.second.getenrollments();
	//		for(auto& enrollmentItr : enrollments)
	//		{
	//			cout << enrollmentItr.printEnrollment() << endl;
	//		}
	//	}
}

void StudentDb::printStudent()
{
	string matrikelNumber = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to print his/her details - 0-9: ";
	getline(cin, matrikelNumber);

	auto matrikelNumberItr = this->m_students.find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_students.end())
	{
		cout << "\n\t \t \t " << matrikelNumberItr->second.printStudent() << endl;

		for(auto& itr : matrikelNumberItr->second.getEnrollments())
		{
			cout << "\n\t \t \t " << itr.printEnrollment() << endl;
		}
	}
	else
	{
		cout << "\t \t Entered Matrikel Number does not match "
				"any student in the database." << endl;
	}
}

void StudentDb::searchStudent()
{
	string searchString = "Gir";

	cout << endl << "\t \t Enter Student Name to search in the Database - a-z/A-Z: ";
	getline(cin, searchString);

	bool matchFound = false;

	for(const auto& pairItr : this->m_students)
	{
		const auto& findStudent = pairItr.second;

		string firstName = findStudent.getFirstName();
		string lastName = findStudent.getLastName();

		if (boost::algorithm::icontains(firstName, searchString) ||
				boost::algorithm::icontains(lastName, searchString))
		{
			matchFound = true;
			cout << "\n\t \t \t " << findStudent.printStudent() << endl;
		}
	}
	if(matchFound == false)
	{
		cout << "\t \t Entered string doesn't match the Student Name "
				"or the Student does not exist in the Database" << endl;
	}
}

void StudentDb::updateStudent()
{
	string matrikelNumber = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to update his/her details - 0-9: ";
	getline(cin, matrikelNumber);

	auto studentItr = this->m_students.find(stoi(matrikelNumber));

	if(studentItr != this->m_students.end())
	{
		cout << endl << "\t \t UPDATE STUDENT MENU: "
				"Below are the index number to update the details" << endl << endl;

		cout << "\t \t \t 0 -> To Exit Update Student Menu" << endl;
		cout << "\t \t \t 1 -> Update First Name" << endl;
		cout << "\t \t \t 2 -> Update Last Name" << endl;
		cout << "\t \t \t 3 -> Update Date of Birth" << endl;
		cout << "\t \t \t 4 -> Update Address" << endl;
		cout << "\t \t \t 5 -> Update Enrollment" << endl;

		performStudentUpdate(studentItr->second); //! Method to handle the above options.
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Matrikel Number "
				"doesn't exist in the database!!!" << endl;
	}
}

void StudentDb::performStudentUpdate(Student &student)
{
	bool exitFlag = false;

	while(exitFlag == false)
	{
		string choice;

		cout << endl << "\t \t \t Enter your choice to perform "
				"the respective operation between 0 and 5: ";
		getline(cin, choice);

		try
		{
			int numericChoice = stoi(choice);

			if(numericChoice >= 0 && numericChoice <= 5)
			{
				switch(numericChoice)
				{
				case 0:
				{
					cout << endl << "\t \t Exited Student Update Menu : "
							<< numericChoice <<endl;
					exitFlag = true;
				}
				break;
				case 1:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update First Name." <<endl;

					this->updateFirstName(student);
				}
				break;
				case 2:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Last Name." <<endl;

					this->updateLastName(student);
				}
				break;
				case 3:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Date of Birth." <<endl;

					this->updateDateOfBirth(student);
				}
				break;
				case 4:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Address." <<endl;

					this->updateAddress(student);
				}
				break;
				case 5:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to update Enrollment." <<endl << endl;

					string courseKey = "0";

					cout << endl << "\t \t \t \t Enter CourseKey - 0-9: ";
					getline(cin, courseKey);

					auto courseKeyItr = this->m_courses.find(stoi(courseKey));

					if(courseKeyItr != this->m_courses.end())
					{
						cout << "\t \t \t \t 0 -> To Exit Update Enrollment Menu" << endl;
						cout << "\t \t \t \t 1 -> Delete Enrollment" << endl;
						cout << "\t \t \t \t 2 -> Update Grade" << endl;

						this->performEnrollmentUpdate(student, courseKey);
					}
					else
					{
						cout << endl << "\t \t \t ERROR: Entered Course Key "
								"doesn't exist in the database!!!" << endl;
					}
				}
				break;
				default:
				{
					cout << endl << "\t \t \t ERROR: Invalid Input, "
							"Please enter a numeric value between - [0-5]" << endl;
				}
				break;
				}
			}
			else
			{
				cout << endl << "\t \t \t ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-5]" << endl;
			}
		}
		catch(const invalid_argument& e)
		{
			cout << endl << "\t \t \t ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-5]" << endl;
		}
	}
}

void StudentDb::updateFirstName(Student &student)
{
	string firstName = "NA";

	cout << endl << "\t \t \t \t Enter First Name of the Student to Update - a-z/A-Z: ";
	getline(cin, firstName);
}

void StudentDb::updateLastName(Student &student)
{
	string lastName = "NA";

	cout << endl << "\t \t \t \t Enter Last Name of the Student to Update - a-z/A-Z: ";
	getline(cin, lastName);
}

void StudentDb::updateDateOfBirth(Student &student)
{
	string DoBstring = "31.12.9999";

	cout << endl << "\t \t \t \t Enter Date of Birth of the Student "
			"to Update - dd..mm..YYY : ";
	getline(cin, DoBstring);

	Poco::Data::Date pocoDoB = stringToPocoDateFormatter(DoBstring);

	student.updateStudent("NA", "NA", pocoDoB);
}

void StudentDb::updateAddress(Student &student)
{
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "\t \t \t \t Enter Street Name of the "
			"Student's Address to Update - a-z/A-Z: ";
	getline(cin, streetName);

	cout << endl << "\t \t \t \t Enter Postal Code of the "
			"Student's Address to Update - 0-9: ";
	getline(cin, postalCode);

	cout << endl << "\t \t \t \t Enter City Name of the "
			"Student's Address to Update - a-z/A-Z: ";
	getline(cin, cityName);

	cout << endl << "\t \t \t \t Enter Additional Info related "
			"to Student's Address to Update - a-z/A-Z: ";
	getline(cin, additionalInfo);

	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode),
					cityName, additionalInfo);

	student.updateAddress(address);
}

void StudentDb::performEnrollmentUpdate(Student& student, const std::string& courseKey)
{
	bool exitFlag2 = false;

	while(exitFlag2 == false)
	{
		string choice;

		cout << endl << "\t \t \t \t Enter the index number "
				"to delete enrollment / enter mark: ";
		getline(cin, choice);

		try
		{
			int numericChoice = stoi(choice);

			if(numericChoice >= 0 && numericChoice <= 2)
			{
				switch(numericChoice)
				{
				case 0:
				{
					cout << endl << "\t \t \t You chose option : " << numericChoice
							<< " to exit Update Enrollment." <<endl;
					exitFlag2 = true;
				}
				break;
				case 1:
				{
					cout << endl << "\t \t \t \t You chose option : " << numericChoice
							<< " to Delete Enrollment." <<endl;

					student.deleteEnrollment(stoi(courseKey));
				}
				break;
				case 2:
				{
					cout << endl << "\t \t \t \t You chose option : " << numericChoice
							<< " to update Grade." <<endl;

					string grade = "0";

					cout << endl << "\t \t \t \t \t Enter Grade to Update - 0-9: ";
					getline(cin, grade);

					student.updateGrade(stof(grade), stoi(courseKey));
				}
				break;
				}
			}
			else
			{
				cout << endl << "\t \t \t ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-2]" << endl;
			}
		}
		catch(const invalid_argument& e)
		{
			cout << endl << "\t \t \t ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-2]" << endl;
		}
	}
}

void StudentDb::printAllStudentsDb(std::ostream &out) const
{
	out << this->m_students.size() << endl;

	for(const auto& studentsPair: this->m_students)
	{
		const Student& student = studentsPair.second;

		out << student.printStudent() << endl;
	}
}

void StudentDb::printAllCoursesDb(std::ostream &out) const
{
	out << this->m_courses.size() << endl;

	for(const auto& coursesPair: this->m_courses)
	{
		const Course* course = coursesPair.second.get();

		course->write(out);
	}
}

void StudentDb::printAllEnrollments(std::ostream &out) const
{
	map<unsigned int, vector<Enrollment>> StudentEnrollments;

	for(const auto& eachStudent: this->m_students)
	{
		unsigned int matrikelNumber = eachStudent.second.getMatrikelNumber();

		for(const Enrollment& enrollment : eachStudent.second.getEnrollments())
		{
			StudentEnrollments[matrikelNumber].push_back(enrollment);
		}
	}

	for(auto& itr: StudentEnrollments)
	{
//		auto& count = itr.second;

		out << itr.second.size() << endl;

		for(const Enrollment& enrItr: itr.second)
		{
			out << itr.first << ";";
			out << enrItr.printEnrollment();
		}
	}
}

void StudentDb::write(std::ostream &out) const
{
	printAllCoursesDb(out);
	printAllStudentsDb(out);
	printAllEnrollments(out);
}

void StudentDb::read(std::istream &in)
{
	//! Clearing the database.
	this->m_courses.clear();
	this->m_students.clear();

	processCoursesData(in);
	processStudentsData(in);
	processEnrollmentData(in);
}

void StudentDb::processCoursesData(std::istream &in)
{
	string readLine, count;

	getline(in, count);
	int noofCourses = stoi(count);

	int loopIdx = 0;

	while(loopIdx < noofCourses)
	{
		getline(in, readLine);
		istringstream iss(readLine);

		vector<string> filedata;

		while(getline(iss, readLine,';'))
		{
			filedata.push_back(readLine);
		}

		unsigned char courseType = filedata.at(0)[0];

		unsigned int courseKey;
		string title, major;
		Poco::DateTime::DaysOfWeek dayOfWeek;
		Poco::Data::Time startTime, endTime;
		Poco::Data::Date startDate, endDate;
		float creditPoints;

		if(courseType == 'W' or courseType == 'w')
		{
			courseKey = stoi(filedata.at(1));
			title = filedata.at(2);
			major = filedata.at(3);
			creditPoints = stof(filedata.at(4));
			dayOfWeek = getDayOfWeekFromString(filedata.at(5));
			startTime = stringToPocoTimeFormatter(filedata.at(6));
			endTime = stringToPocoTimeFormatter(filedata.at(7));

			unique_ptr<WeeklyCourse> weeklyCourse =
					make_unique<WeeklyCourse>(courseKey, title, major, creditPoints,
							dayOfWeek, startTime, endTime);

			this->m_courses[courseKey] = move(weeklyCourse);
		}
		else if(courseType == 'B' or courseType == 'b')
		{
			courseKey = stoi(filedata.at(1));
			title = filedata.at(2);
			major = filedata.at(3);
			creditPoints = stof(filedata.at(4));
			startDate = stringToPocoDateFormatter(filedata.at(5));
			endDate = stringToPocoDateFormatter(filedata.at(6));
			startTime = stringToPocoTimeFormatter(filedata.at(7));
			endTime = stringToPocoTimeFormatter(filedata.at(8));

			unique_ptr<BlockCourse> blockCourse =
					make_unique<BlockCourse>(courseKey, title, major, creditPoints,
							startDate, endDate, startTime, endTime);

			this->m_courses[courseKey] = move(blockCourse);
		}
		loopIdx++;
	}
}

void StudentDb::processStudentsData(std::istream &in)
{
	string count, readLine;

	getline(in, count);
	unsigned int noOfStudents = stoi(count);

	unsigned int loopIdx = 0;

	while(loopIdx < noOfStudents)
	{
		getline(in, readLine);
		istringstream iss(readLine);

		vector<string> filedata;

		while(getline(iss, readLine, ';'))
		{
			filedata.push_back(readLine);
		}

		unsigned int matrikelNumber = stoi(filedata.at(0));
		string firstName = filedata.at(1);
		string lastName = filedata.at(2);
		Poco::Data::Date dateOfBirth = stringToPocoDateFormatter(filedata.at(3));
		string streetName = filedata.at(4);
		unsigned int postalCode = stoi(filedata.at(5));
		string cityName = filedata.at(6);
		string additionalInfo = filedata.at(7);

		shared_ptr<Address> address =
				make_shared<Address>(streetName, postalCode, cityName, additionalInfo);

		Student addStudent(firstName, lastName, dateOfBirth, address);

		this->m_students.insert(make_pair(matrikelNumber, addStudent));


		loopIdx++;
	}
}

void StudentDb::processEnrollmentData(std::istream &in)
{
	string count, readLine;

	getline(in, count);
	unsigned int noOfEnrollments = stoi(count);

	unsigned int loopIdx = 0;

	while(loopIdx < noOfEnrollments)
	{
		getline(in, readLine);
		istringstream iss(readLine);

		vector<string> filedata;

		while(getline(iss, readLine, ';'))
		{
			filedata.push_back(readLine);
		}

		unsigned int matrikelNumber = stoi(filedata.at(0));
		unsigned int courseKey = stoi(filedata.at(1));
		string semester = filedata.at(2);
		float grade = stof(filedata.at(3));

		auto studentItr = this->m_students.find(matrikelNumber);

		if(studentItr != this->m_students.end())
		{
			auto courseItr = this->m_courses.find(courseKey);

			if(courseItr != this->m_courses.end())
			{
				Course* course = const_cast<Course*>(courseItr->second.get());

				studentItr->second.addEnrollment(semester, course);
				studentItr->second.updateGrade(grade, courseKey);
			}
		}

		loopIdx++;
	}
}
