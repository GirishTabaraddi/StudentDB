/*!
 * @file SimpleUI.cpp
 *
 * \n Created on: 13-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "SimpleUI.h"

using namespace std;

SimpleUI::SimpleUI(StudentDb &db) : m_db(db)
{
}

SimpleUI::~SimpleUI()
{
}

void SimpleUI::run() const
{
	bool exitFlag = false;

	cout << "Main Menu: Below are the properties of Student Database : " << endl << endl;

	cout << "\t 0	-> To Exit Main Menu" << endl;
	cout << "\t 1 	-> Add New Course" << endl;
	cout << "\t 2 	-> List the Courses" << endl;
	cout << "\t 3 	-> Add new Student" << endl;
	cout << "\t 4 	-> Add Enrollment" << endl;
	cout << "\t 5 	-> Print Student Details" << endl;
	cout << "\t 6 	-> Search Student in Database" << endl;
	cout << "\t 7 	-> Update Student Details" << endl;
	cout << "\t 8 	-> Write Student Database to a text file" << endl;
	cout << "\t 9 	-> Read Student Database from a file" << endl;
	cout << "\t 10 	-> Read Student Database from a server" << endl;

	while(exitFlag == false)
	{
		string choice;

		cout << endl << "\t Enter your choice to perform the respective "
				"operation between 0 and 10: ";
		getline(cin, choice);

		if(!integerInputCheck(choice))
		{
			cerr << endl << "\t You entered an invalid choice (hint: 0-10)" << endl;
			return;
		}


		int numericChoice = stoi(choice);

		if(numericChoice >= 0 && numericChoice <= 10)
		{
			switch(numericChoice)
			{
			case 0:
			{
				cout << endl << "Exited Main Menu : " << numericChoice << endl;
				exitFlag = true;
			}
			break;
			case 1:
			{
				cout << endl << "\t You chose option : " << numericChoice
						<< " to add new course." <<endl;

				this->getUserInputsforNewCourse();
			}
			break;
			case 2:
			{
				cout << endl << "\t You chose option : " << numericChoice
						<< " to list all courses." <<endl;

				this->listCourses();
			}
			break;
			case 3:
			{
				cout << endl << "\t You chose option : " << numericChoice
						<< " to add new student to the database." <<endl;

				this->getUserInputsforNewStudent();
			}
			break;
			case 4:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to add new enrollment." <<endl;

				this->getUserInputforNewEnrollment();
			}
			break;
			case 5:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to print the details of the student." <<endl;

				this->printStudent();
			}
			break;
			case 6:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to search specific student in database." <<endl;

				this->searchStudent();
			}
			break;
			case 7:
			{
				cout << endl << "\t You chose option : "
						<< numericChoice << " to update the student details." <<endl;

				this->getUserInputforStudentUpdate();
			}
			break;
			case 8:
			{
				cout << endl << "\t Enter the file name to write the data(.txt): ";

				string filename = "fileData.txt";
				getline(cin, filename);

				if(!isValidFilename(filename))
				{
					cerr << "Invalid filename format (hint: use .txt extension)" << endl;
					return;
				}

				ofstream writeFile(filename, ios::trunc);
				if(writeFile.is_open())
				{
					this->m_db.write(writeFile);

					writeFile.close();

					cout << "\n\t Student Database is written to the file" << endl;
				}
				else
				{
					cout << "Unable to open file" << endl;
				}
			}
			break;
			case 9:
			{
				cout << endl << "\t Enter the file name "
						"to read the data from(.txt): ";

				string filename = "read_StudentDb.txt";
				getline(cin, filename);

				if(!isValidFilename(filename))
				{
					cerr << "Invalid filename format (hint: use .txt extension)" << endl;
					return;
				}

				ifstream readFile(filename);
				if(readFile.is_open())
				{
					this->m_db.read(readFile);

					readFile.close();

					cout << "\n\t Read the Student Database from the file" << endl;
				}
				else
				{
					cout << "Unable to open file" << endl;
				}
			}
			break;
			case 10:
			{
				string noOfUserDate = "1";
				string readLine;

				cout << "Enter the number of Student Data to be "
						"extracted from the server: ";
				getline(cin, noOfUserDate);

				if(!integerInputCheck(noOfUserDate))
				{
					cerr << endl << "\t You entered an invalid choice (hint: 0-999)" << endl;
					return;
				}

				this->m_db.readStudentDataFromServer(stoul(noOfUserDate));
			}
			break;
			default:
			{
				cerr << endl << "ERROR: Invalid Input, "
						"Please enter a numeric value between - [0-10]" << endl;
			}
			}
		}
		else
		{
			cerr << endl << "ERROR: Invalid Input, "
					"Please enter a numeric value between - [0-10]" << endl;
		}
	}
}

void SimpleUI::getUserInputsforNewCourse() const
{
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

	cout << endl << "\t \t Enter CourseKey - (0-9): ";
	getline(cin, courseKey);

	if(!integerInputCheck(courseKey))
	{
		cerr << endl << "\t You entered an invalid course key (hint: int)" << endl;
		return;
	}

	cout << endl << "\t \t Enter Title of the Course - (a-z/A-Z): ";
	getline(cin, title);

	if(!stringInputCheck(title))
	{
		cerr << endl << "\t You entered an invalid title (hint: alpha)" << endl;
		return;
	}

	cout << endl << "\t \t Available Majors are : Automation, Embedded Systems,"
			" Communication and Power\n \t \t Enter the Major in which the Course belongs to: ";
	getline(cin, major);

	bool isValidMajor = false;

	for(const auto& itr : Course::getmajorById())
	{
		if(!boost::algorithm::icontains(itr.second, major))
		{
			isValidMajor = true;
			break;
		}
	}

	if(!isValidMajor)
	{
		cerr << endl << "\t You entered a wrong Major" << endl;
		return;
	}

	cout << endl << "\t \t Enter the credit points of the Course - (0-9): ";
	getline(cin, credits);

	if(!floatInputCheck(credits))
	{
		cerr << endl << "\t You entered an invalid credits (hint: float)" << endl;
		return;
	}

	cout << endl << "\t \t Enter the Course Type - Weekly(W/w)/Block(B/b): ";
	getline(cin, courseType);

	if(courseType != "B" && courseType != "b" && courseType != "W" && courseType != "w")
	{
		cerr << endl << "\t You entered an invalid course type (hint: B/W/b/w)" << endl;
		return;
	}

	regex timePattern(R"(\d{1,2}\:\d{1,2})");

	cout << endl << "\t \t Enter the Course Start Time - HH:MM : ";
	getline(cin, startTime);

	if(!regex_match(startTime, timePattern))
	{
		cerr << "You entered an invalid time format (hint: HH:MM)" << endl;
		return;
	}

	cout << endl << "\t \t Enter the Course End Time - HH:MM : ";
	getline(cin, endTime);

	if(!regex_match(endTime, timePattern))
	{
		cerr << "You entered an invalid time format (hint: HH:MM)" << endl;
		return;
	}

	if(courseType == "B" || courseType == "b")
	{
		regex datePattern(R"((\d{1,2})\.(\d{1,2})\.(\d{4}))");

		cout << endl << "\t \t Enter the Course Start Date - dd.mm.YYYY : ";
		getline(cin, startDate);

		if(!regex_match(startDate, datePattern))
		{
			cerr << "You entered an invalid date format (hint: dd.mm.YYYY)" << endl;
			return;
		}

		cout << endl << "\t \t Enter the Course End Date - dd.mm.YYYY : ";
		getline(cin, endDate);

		if(!regex_match(endDate, datePattern))
		{
			cerr << "You entered an invalid date format (hint: dd.mm.YYYY)" << endl;
			return;
		}
	}

	if(courseType == "W" || courseType == "w")
	{
		cout << endl << "\t \t Enter the Course Week - (Monday-Sunday) : ";
		getline(cin, dayOfWeek);

		if(!stringInputCheck(dayOfWeek))
		{
			cerr << endl << "\t You entered an invalid Week (hint: Monday-Sunday)" << endl;
			return;
		}
	}

	//! Call the addNewCourse function from the StudentDb.h
	StudentDb::RC_StudentDb_t result =
			this->m_db.addNewCourse(courseKey, title, major, credits,
					courseType, startTime, endTime, startDate,
					endDate, dayOfWeek);

	switch(result)
	{
	case StudentDb::RC_StudentDb_t::RC_Success:
	{
		cout << "\t \t \nNew Course Added" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Course_Exists:
	{
		cout << "\t \t \nCourse with the given details already exists in the database." << endl;
		break;
	}
	default:
	{
		cout << "\t \t \nUnexpected error during add course" << endl;
		break;
	}
	}
}

void SimpleUI::listCourses() const
{
	cout << this->m_db.getCourses().size() << endl;

	for(const auto& courses: this->m_db.getCourses())
	{
		cout << courses.second.get()->printCourse() << endl;
	}
}

void SimpleUI::getUserInputsforNewStudent() const
{
	string firstName = "NA";
	string lastName = "NA";
	string DoBstring = "01.01.1990";
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "\t \t Enter First Name of the Student - (a-z/A-Z): ";
	getline(cin, firstName);

	if(!stringInputCheck(firstName))
	{
		cerr << endl << "\t You entered an invalid first name (hint: a-z/A-Z)" << endl;
		return;
	}

	cout << endl << "\t \t Enter Last Name of the Student - (a-z/A-Z): ";
	getline(cin, lastName);

	if(!stringInputCheck(lastName))
	{
		cerr << endl << "\t You entered an invalid last name (hint: a-z/A-Z)" << endl;
		return;
	}

	cout << endl << "\t \t Enter Date of Birth of the Student - dd..mm..YYYY : ";
	getline(cin, DoBstring);

	regex datePattern(R"((\d{1,2})\.(\d{1,2})\.(\d{4}))");

	if(!regex_match(DoBstring, datePattern))
	{
		cerr << "You entered an invalid date format (hint: dd.mm.YYYY)" << endl;
		return;
	}

	cout << endl << "\t \t Enter Street Name of the Student's Address - (a-z/A-Z): ";
	getline(cin, streetName);

	if(!isPrintableInput(streetName))
	{
		cerr << endl << "\t You entered an invalid street name (hint: a-z/A-Z)" << endl;
		return;
	}

	cout << endl << "\t \t Enter Postal Code of the Student's Address - 0-9: ";
	getline(cin, postalCode);

	if(!integerInputCheck(postalCode))
	{
		cerr << endl << "\t You entered an invalid post code (hint: 0-9)" << endl;
		return;
	}

	cout << endl << "\t \t Enter City Name of the Student's Address - a-z/A-Z: ";
	getline(cin, cityName);

	if(!isPrintableInput(cityName))
	{
		cerr << endl << "\t You entered an invalid city name (hint: a-z/A-Z)" << endl;
		return;
	}

	cout << endl << "\t \t Enter Additional Info related Student's Address - 0-9/a-z/A-Z: ";
	getline(cin, additionalInfo);

	if(!isPrintableInput(additionalInfo))
	{
		cerr << endl << "\t You entered an invalid additionalInfo (hint: 0-9/a-z/A-Z)" << endl;
		return;
	}

	//! Call the addnewstudent function from the StudentDb.h
	StudentDb::RC_StudentDb_t result =
			this->m_db.addNewStudent(firstName, lastName, DoBstring,
					streetName, postalCode, cityName, additionalInfo);

	switch(result)
	{
	case StudentDb::RC_StudentDb_t::RC_Success:
	{
		cout << "\t \t \nNew Student Added" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Student_Exists:
	{
		cout << "\t \t \nStudent with the given details already exists in the database." << endl;
		break;
	}
	default:
	{
		cout << "\t \t \nUnexpected error during add student" << endl;
		break;
	}
	}
}

void SimpleUI::getUserInputforNewEnrollment() const
{
	string matrikelNumber = "0";
	string semester = "0";
	string courseKey = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to add his/her Enrollment - (0-9): ";
	getline(cin, matrikelNumber);

	if(!integerInputCheck(matrikelNumber))
	{
		cerr << endl << "\t You entered an invalid matrikelNumber (hint: 0-9)" << endl;
		return;
	}

	cout << endl << "\t \t Enter the Semester of the Student "
			"studying currently - (hint: WiSe2023/SoSe2024): ";
	getline(cin, semester);

	regex semesterPattern("^(SoSe|WiSe)\\d{4}");

	if(!regex_match(semester, semesterPattern))
	{
		cerr << endl << "\t You entered an invalid matrikelNumber (hint: WiSe2023/SoSe2024)" << endl;
		return;
	}

	cout << endl << "\t \t Enter the Course Key, "
			"to which he/she wants to enroll - 0-9: ";
	getline(cin, courseKey);

	if(!integerInputCheck(courseKey))
	{
		cerr << endl << "\t You entered an invalid course key (hint: int)" << endl;
		return;
	}

	//! Call the addEnrollment function from the StudentDb.h
	StudentDb::RC_StudentDb_t result =
			this->m_db.addEnrollment(matrikelNumber, semester, courseKey);

	switch(result)
	{
	case StudentDb::RC_StudentDb_t::RC_Success:
	{
		cout << "\t \t \nNew Enrollment Added" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Wrong_Course_Key:
	{
		cout << "\t \t \nProvided course key is incorrect or not found" << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Wrong_MatrikelNumber:
	{
		cout << "\t \t \nProvided matrikel number is incorrect or not found." << endl;
		break;
	}
	case StudentDb::RC_StudentDb_t::RC_Enrollment_Exists:
	{
		cout << "\t \t \nEnrollment for the student and course already exists in the database." << endl;
		break;
	}
	default:
	{
		cerr << "\t \t \nUnexpected error during add enrollment" << endl;
		break;
	}
	}
}

void SimpleUI::printStudent() const
{
	string matrikelNumber = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to print his/her details - 0-9: ";
	getline(cin, matrikelNumber);

	if(!integerInputCheck(matrikelNumber))
	{
		cerr << endl << "\t You entered an invalid matrikelNumber (hint: 0-9)" << endl;
		return;
	}

	auto matrikelNumberItr = this->m_db.getStudents().find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_db.getStudents().end())
	{
		cout << "\n\t \t \t " << matrikelNumberItr->second.printStudent() << endl;

		for(const Enrollment& enrollmentItr : matrikelNumberItr->second.getEnrollments())
		{
			cout << "\n\t \t \t " << enrollmentItr.printEnrollment() << endl;
		}
	}
	else
	{
		cerr << "\n\t \t Entered Matrikel Number does not match "
				"any student in the database." << endl;
	}
}

void SimpleUI::searchStudent() const
{
	string searchString = "Gir";

	cout << endl << "\t \t Enter Student Name to search in the Database - a-z/A-Z: ";
	getline(cin, searchString);

	if(!stringInputCheck(searchString))
	{
		cerr << endl << "\t You entered an invalid string to search student (hint: a-z/A-Z)" << endl;
		return;
	}

	bool matchFound = false;

	for(const auto& pairItr : this->m_db.getStudents())
	{
		const Student& findStudent = pairItr.second;

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
		cerr << "\t \t Entered string doesn't match the Student Name "
				"or the Student does not exist in the Database" << endl;
	}
}

void SimpleUI::getUserInputforStudentUpdate() const
{
	string matrikelNumber = "0";

	cout << endl << "\t \t Enter the Matrikel Number of the Student, "
			"to update his/her details - 0-9: ";
	getline(cin, matrikelNumber);

	if(!integerInputCheck(matrikelNumber))
	{
		cerr << endl << "\t You entered an invalid matrikelNumber (hint: 0-9)" << endl;
		return;
	}

	auto studentItr =  this->m_db.getStudents().find(stoi(matrikelNumber));

	if(studentItr != this->m_db.getStudents().end())
	{
		cout << endl << "\t \t UPDATE STUDENT MENU: "
				"Below are the index number to update the details" << endl << endl;

		cout << "\t \t \t 0 -> To Exit Update Student Menu" << endl;
		cout << "\t \t \t 1 -> Update First Name" << endl;
		cout << "\t \t \t 2 -> Update Last Name" << endl;
		cout << "\t \t \t 3 -> Update Date of Birth" << endl;
		cout << "\t \t \t 4 -> Update Address" << endl;
		cout << "\t \t \t 5 -> Update Enrollment" << endl;

		const Student& updateStudent = studentItr->second;

		this->performStudentUpdate(studentItr->first, updateStudent);
	}
	else
	{
		cerr << endl << "\t \t \t ERROR: Entered Matrikel Number "
				"doesn't exist in the database!!!" << endl;
	}
}

void SimpleUI::performStudentUpdate(unsigned int matrikelNumber,
		const Student& updateStudent) const
{
	bool exitFlag = false;

	while(exitFlag == false)
	{
		string choice;

		cout << endl << "\t \t \t Enter your choice to perform "
				"the respective operation between 0 and 5: ";
		getline(cin, choice);

		if(!integerInputCheck(choice))
		{
			cerr << endl << "\t You entered an invalid choice (hint: 0-5)" << endl;
			return;
		}

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

				this->getUserInputforFirstName(matrikelNumber, updateStudent);
			}
			break;
			case 2:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Last Name." <<endl;

				this->getUserInputforLastName(matrikelNumber, updateStudent);
			}
			break;
			case 3:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Date of Birth." <<endl;

				this->getUserInputforDateOfBirth(matrikelNumber, updateStudent);
			}
			break;
			case 4:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Address." <<endl;

				this->getUserInputforAddressUpdate(matrikelNumber, updateStudent);
			}
			break;
			case 5:
			{
				cout << endl << "\t \t \t You chose option : " << numericChoice
						<< " to update Enrollment." <<endl << endl;

				this->getUserInputforEnrollmentUpdate(matrikelNumber, updateStudent);
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
}

void SimpleUI::getUserInputforFirstName(unsigned int matrikelNumber,
		const Student& updateStudent)const
{
	string firstName = "NA";

	cout << endl << "\t \t \t \t Existing First Name of the Student: "
			<< updateStudent.getFirstName() << endl;
	cout << endl << "\t \t \t \t Enter First Name of the Student to Update - a-z/A-Z: ";
	getline(cin, firstName);

	if(!stringInputCheck(firstName))
	{
		cerr << endl << "\t You entered an invalid first name (hint: a-z/A-Z)" << endl;
		return;
	}

	this->m_db.updateFirstName(firstName, matrikelNumber);
}

void SimpleUI::getUserInputforLastName(unsigned int matrikelNumber,
		const Student& updateStudent) const
{
	string lastName = "NA";

	cout << endl << "\t \t \t \t Existing Last Name of the Student: "
			<< updateStudent.getLastName() << endl;
	cout << endl << "\t \t \t \t Enter Last Name of the Student to Update - a-z/A-Z: ";
	getline(cin, lastName);

	if(!stringInputCheck(lastName))
	{
		cerr << endl << "\t You entered an invalid last name (hint: a-z/A-Z)" << endl;
		return;
	}

	this->m_db.updateLastName(lastName, matrikelNumber);
}

void SimpleUI::getUserInputforDateOfBirth(unsigned int matrikelNumber,
		const Student& updateStudent) const
{
	string DoBstring = "31.12.9999";

	cout << endl << "\t \t \t \t Existing Date of Birth of the Student: "
			<< pocoDateToStringFormatter(updateStudent.getDateOfBirth()) << endl;
	cout << endl << "\t \t \t \t Enter Date of Birth of the Student "
			"to Update - dd..mm..YYY : ";
	getline(cin, DoBstring);

	regex datePattern(R"((\d{1,2})\.(\d{1,2})\.(\d{4}))");

	if(!regex_match(DoBstring, datePattern))
	{
		cerr << "You entered an invalid date format (hint: dd.mm.YYYY)" << endl;
		return;
	}

	Poco::Data::Date pocoDoB = stringToPocoDateFormatter(DoBstring);

	this->m_db.updateDateOfBirth(pocoDoB, matrikelNumber);
}

void SimpleUI::getUserInputforAddressUpdate(unsigned int matrikelNumber,
		const Student& updateStudent) const
{
	string streetName = "NA";
	string postalCode = "NA";
	string cityName = "NA";
	string additionalInfo = "NA";

	cout << endl << "\t \t \t \t Existing Street Name of the Student's Address: "
			<< updateStudent.getAddress()->getstreet() << endl;
	cout << endl << "\t \t \t \t Enter Street Name of the "
			"Student's Address to Update - a-z/A-Z: ";
	getline(cin, streetName);

	if(!isPrintableInput(streetName))
	{
		cerr << endl << "\t You entered an invalid street name (hint: a-z/A-Z)" << endl;
		return;
	}

	cout << endl << "\t \t \t \t Existing Post Code of the Student's Address: "
			<< updateStudent.getAddress()->getpostalCode() << endl;
	cout << endl << "\t \t \t \t Enter Postal Code of the "
			"Student's Address to Update - 0-9: ";
	getline(cin, postalCode);

	if(!integerInputCheck(postalCode))
	{
		cerr << endl << "\t You entered an invalid post code (hint: 0-9)" << endl;
		return;
	}

	cout << endl << "\t \t \t \t Existing City Name of the Student's Address: "
			<< updateStudent.getAddress()->getcityName() << endl;
	cout << endl << "\t \t \t \t Enter City Name of the "
			"Student's Address to Update - a-z/A-Z: ";
	getline(cin, cityName);

	if(!isPrintableInput(cityName))
	{
		cerr << endl << "\t You entered an invalid city name (hint: a-z/A-Z)" << endl;
		return;
	}

	cout << endl << "\t \t \t \t Existing Additional Info of the Student's Address: "
			<< updateStudent.getAddress()->getadditionalInfo() << endl;
	cout << endl << "\t \t \t \t Enter Additional Info related "
			"to Student's Address to Update - a-z/A-Z: ";
	getline(cin, additionalInfo);

	if(!isPrintableInput(additionalInfo))
	{
		cerr << endl << "\t You entered an invalid additionalInfo (hint: 0-9/a-z/A-Z)" << endl;
		return;
	}

	this->m_db.updateAddress(streetName, stoi(postalCode),
			cityName, additionalInfo, matrikelNumber);
}

void SimpleUI::getUserInputforEnrollmentUpdate(unsigned int matrikelNumber,
		const Student &updateStudent) const
{
	if(updateStudent.getEnrollments().empty())
	{
		cout << endl << "\t \t \t ERROR: Entered Student not "
				"enrolled to update grade or delete enrollment!!!" << endl;
		return;
	}

	string courseKey = "0";

	cout << endl << "\t \t \t \t Enter CourseKey to perform Enrollment Update - 0-9: ";
	getline(cin, courseKey);

	if(!integerInputCheck(courseKey))
	{
		cerr << endl << "\t You entered an invalid course key (hint: integer)" << endl;
		return;
	}

	auto courseKeyItr = this->m_db.getCourses().find(stoi(courseKey));


	if(courseKeyItr != this->m_db.getCourses().end())
	{
		cout << endl << "\t \t \t \t 0 -> To Exit Update Enrollment Menu" << endl;
		cout << endl << "\t \t \t \t 1 -> Delete Enrollment" << endl;
		cout << endl << "\t \t \t \t 2 -> Update Grade" << endl;

		this->performEnrollmentUpdate(courseKey, updateStudent);
	}
	else
	{
		cout << endl << "\t \t \t ERROR: Entered Course Key "
				"doesn't exist in the database!!!" << endl;
	}
}

void SimpleUI::performEnrollmentUpdate(const std::string& courseKey,
		const Student& updateStudent) const
{
	bool exitFlag2 = false;

	while(exitFlag2 == false)
	{
		string choice;

		cout << endl << "\t \t \t \t Enter the index number "
				"0 -> To Exit Update Enrollment Menu"
				"1 -> To Delete an Enrollment "
				"2 -> To Enter a Grade (hint: 0-2): ";
		getline(cin, choice);

		if(!integerInputCheck(choice))
		{
			cerr << endl << "\t You entered an invalid choice (hint: 0-2)" << endl;
			return;
		}
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

				this->m_db.deleteEnrollment(stoi(courseKey),
						updateStudent.getMatrikelNumber());
			}
			break;
			case 2:
			{
				cout << endl << "\t \t \t \t You chose option : " << numericChoice
						<< " to update Grade." <<endl;

				string grade = "0";

				cout << endl << "\t \t \t \t \t Enter Grade to Update - 1.0 to 4.0: ";
				getline(cin, grade);

				if(!floatInputCheck(grade))
				{
					cerr << endl << "\t \t \t \t \t You entered an invalid grade "
							"(hint: float)" << endl;
					return;
				}

				this->m_db.updateGrade(stoi(courseKey), (stof(grade)),
						updateStudent.getMatrikelNumber());
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
}
