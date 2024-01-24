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

std::map<int, Student>& StudentDb::getStudents()
{
	return this->m_students;
}

std::map<int, std::unique_ptr<const Course> >& StudentDb::getCourses()
{
	return this->m_courses;
}

StudentDb::RC_StudentDb_t StudentDb::addNewCourse(std::string &courseKey, std::string &title,
		std::string &major, std::string &credits, std::string &courseType,
		std::string &startTime, std::string &endTime, std::string &startDate,
		std::string &endDate, std::string &dayOfWeek)
{
	auto existingCourse = find_if(this->m_courses.begin(), this->m_courses.end(),
			[&courseKey, &title](const auto& pairCourse){
		const Course& courseref = *(pairCourse.second);
		return (courseref.getcourseKey() == stoul(courseKey) &&
				courseref.gettitle() == title);
	});

	if(existingCourse != this->m_courses.end())
	{
		return RC_StudentDb_t::RC_Course_Exists;
	}
	else
	{
		if(courseType == "B" || courseType == "b")
		{
			unique_ptr<BlockCourse> blockCourse =
					make_unique<BlockCourse>(stoi(courseKey), title, major, stof(credits),
							stringToPocoDateFormatter(startDate), stringToPocoDateFormatter(endDate),
							stringToPocoTimeFormatter(startTime), stringToPocoTimeFormatter(endTime));

			this->m_courses.insert(make_pair(blockCourse->getcourseKey(), move(blockCourse)));
		}
		if(courseType == "W" || courseType == "w")
		{
			Poco::DateTime::DaysOfWeek dayOfWeekinPoco = getDayOfWeekFromString(dayOfWeek);

			unique_ptr<WeeklyCourse> weeklyCourse = make_unique<WeeklyCourse>(stoi(courseKey),
					title, major, stof(credits), dayOfWeekinPoco,
					stringToPocoTimeFormatter(startTime), stringToPocoTimeFormatter(endTime));

			this->m_courses.insert(make_pair(weeklyCourse->getcourseKey(), move(weeklyCourse)));
		}

		return RC_StudentDb_t::RC_Success;
	}
}

StudentDb::RC_StudentDb_t StudentDb::addNewStudent(std::string &firstName, std::string &lastName,
		std::string &DoBstring, std::string &streetName,
		std::string &postalCode, std::string &cityName,
		std::string &additionalInfo)
{
	auto existingStudent = find_if(this->m_students.begin(), this->m_students.end(),
			[&firstName,  &lastName, &streetName,
			 &postalCode, &cityName, &additionalInfo](const auto& studentPair){
		const Student& student = studentPair.second;
		return (student.getFirstName() == firstName &&
				student.getLastName() == lastName &&
				student.getAddress()->getstreet() == streetName &&
				student.getAddress()->getcityName() == cityName &&
				student.getAddress()->getpostalCode() == stoi(postalCode) &&
				student.getAddress()->getadditionalInfo() == additionalInfo);
	});

	if(existingStudent != this->m_students.end())
	{
		return RC_StudentDb_t::RC_Student_Exists;
	}

	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode), cityName, additionalInfo);

	Student student = Student(firstName, lastName, stringToPocoDateFormatter(DoBstring), address);

	this->m_students.insert(make_pair(student.getMatrikelNumber(), student));

	return RC_StudentDb_t::RC_Success;
}

StudentDb::RC_StudentDb_t StudentDb::addEnrollment(std::string &matrikelNumber,
		std::string &semester, std::string &courseKey)
{
	auto existingEnrollment = find_if(this->m_students.begin(), this->m_students.end(),
			[&matrikelNumber, &courseKey, &semester](const auto& pairStudent){
		const Student& student = pairStudent.second;
		const auto& enrollments = student.getEnrollments();

		auto enrollmentItr = find_if(
				enrollments.begin(), enrollments.end(),
				[&courseKey, &semester](const Enrollment& enrollment){
			return (enrollment.getcourse()->getcourseKey() == stoul(courseKey) &&
					enrollment.getsemester() == semester);
	});
		return (student.getMatrikelNumber() == stoul(matrikelNumber) &&
				enrollmentItr != enrollments.end());
	});

	auto matrikelNumberItr = this->m_students.find(stoul(matrikelNumber));

	if(matrikelNumberItr != this->m_students.end())
	{
		auto findCourseIdItr = this->m_courses.find(stoul(courseKey));

		if(findCourseIdItr != this->m_courses.end())
		{
			if(existingEnrollment != this->m_students.end())
			{
				return RC_StudentDb_t::RC_Enrollment_Exists;
			}

			const Course& courseref = *(findCourseIdItr->second);

			matrikelNumberItr->second.addEnrollment(semester, &courseref);

			return RC_StudentDb_t::RC_Success;
		}
		else
		{
			return RC_StudentDb_t::RC_Wrong_Course_Key;
		}
	}
	else
	{
		return RC_StudentDb_t::RC_Wrong_MatrikelNumber;
	}
}

void StudentDb::writeCoursesData(std::ostream &out) const
{
	out << this->m_courses.size() << endl;

	for(const auto& coursesPair: this->m_courses)
	{
		coursesPair.second.get()->write(out);
	}
}

void StudentDb::writeStudentsData(std::ostream &out) const
{
	out << this->m_students.size() << endl;

	for(const auto& studentsPair: this->m_students)
	{
		const Student& student = studentsPair.second;

		student.write(out);

		out << endl;
	}
}

void StudentDb::writeEnrollmentsData(std::ostream &out) const
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

	out << StudentEnrollments.size() << endl;

	for(auto& itr: StudentEnrollments)
	{
		for(const Enrollment& enrItr: itr.second)
		{
			out << itr.first << ";";

			enrItr.write(out);
		}

		out << endl;
	}
}

void StudentDb::write(std::ostream &out) const
{
	this->writeCoursesData(out);
	this->writeStudentsData(out);
	this->writeEnrollmentsData(out);
}

void StudentDb::read(std::istream &in)
{
	//! Clearing the database.
	this->m_courses.clear();
	this->m_students.clear();

	string LineStr;
	unsigned int count = 0;
	unsigned char caseChar;

	while(getline(in, LineStr))
	{
		if(LineStr.find(";") == string::npos)
		{
			if(count == 0)
			{
				caseChar = 'C';
			}
			if(count == 1)
			{
				caseChar = 'S';
			}
			if(count == 2)
			{
				caseChar = 'E';
			}
			count++;
		}
		else if(LineStr.find(";") != string::npos)
		{
			switch(caseChar)
			{
			case 'C':
			{
				this->readCoursesData(LineStr);
			}
			break;
			case 'S':
			{
				this->readStudentsData(LineStr);
			}
			break;
			case 'E':
			{
//				for(auto coursesItr = this->m_courses.begin(); coursesItr != this->m_courses.end(); coursesItr++)
//				{
//					cout << coursesItr->second->printCourse() << endl;
//				}
//				for(auto studentsItr = this->m_students.begin(); studentsItr != this->m_students.end(); studentsItr++)
//				{
//					cout << studentsItr->second.printStudent() << endl;
//				}
				this->readEnrollmentData(LineStr);
			}
			break;
			default:
			{
				break;
			}
			}
		}
	}
}

void StudentDb::readCoursesData(std::string &str)
{
	string courseType = splitAt(str, ';');

		if(courseType == "W" or courseType == "w")
		{
			istringstream iss(str);

			unique_ptr<WeeklyCourse> weeklyCourse = WeeklyCourse::read(iss);

			this->m_courses[weeklyCourse->getcourseKey()] = move(weeklyCourse);
		}
		else if(courseType == "B" or courseType == "b")
		{
			istringstream iss(str);

			unique_ptr<BlockCourse> blockCourse = BlockCourse::read(iss);

			this->m_courses[blockCourse->getcourseKey()] = move(blockCourse);
		}
}

void StudentDb::readStudentsData(std::string &str)
{
	istringstream iss(str);

	Student readStudent = Student::read(iss);

	this->m_students.insert(make_pair(readStudent.getMatrikelNumber(), readStudent));
}

void StudentDb::readEnrollmentData(std::string &str)
{
	unsigned int matrikelNumber = stoul(splitAt(str, ';'));

//	istringstream iss(str);
//
//	iss >> matrikelNumber;
//	iss.ignore();

	for(auto& pairItr : this->m_courses)
	{
		const Course& courseref =  *(pairItr.second.get());

		auto checkMatrikel = this->m_students.find(matrikelNumber);

		if(checkMatrikel->second.getMatrikelNumber() == matrikelNumber)
		{
//			cout << matrikelNumber << endl;

			istringstream iss(str);

			Enrollment readEnrollment = Enrollment::read(iss, &courseref);

//			float grade = readEnrollment.getgrade();
//
//			cout << "grade here: " << grade << endl;

			if(readEnrollment.getcourse() != nullptr)
			{
				checkMatrikel->second.addEnrollment(readEnrollment.getsemester(),
						readEnrollment.getcourse());
				checkMatrikel->second.updateGrade(readEnrollment.getgrade(),
						readEnrollment.getcourse()->getcourseKey());
			}
		}
	}
}

void StudentDb::readStudentDataFromServer()
{
	string hostname = "www.hhs.users.h-da.cloud";
	string port = "4242";

	boost::asio::io_service io_service;

	boost::asio::ip::tcp::resolver resolver(io_service);

	boost::asio::ip::tcp::resolver::query query(hostname, port);

	boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);

	if(iter != boost::asio::ip::tcp::resolver::iterator())
	{
		boost::asio::ip::tcp::endpoint endpoint = iter->endpoint();

		boost::asio::ip::tcp::socket socket(io_service);

		try
		{
			socket.connect(endpoint);

			if(socket.is_open())
			{
				//! TODO: need to remove cout
				cout << "Connection to the server is successful" << endl;
			}

			boost::asio::ip::tcp::iostream stream(move(socket));

			if(stream)
			{
				stream << "generate\n";
				stream.flush();

				string readLine;
				vector<string> serverData;

				while(getline(stream, readLine))
				{
					serverData.push_back(readLine);
				}

				if (!serverData.empty())
				{
					//! TODO: need to remove cout
					cout << serverData.at(0) << std::endl;

					if (serverData.size() > 1)
					{
						//! This line contains the JSON Data required.
						this->parsingJSONData(serverData.at(1));
					}

					if (serverData.size() > 2)
					{
						//! TODO: need to remove cout
						cout << serverData.at(2) << std::endl;
					}
				}
				stream << "quit\n";
				stream.flush();
			}
		}
		catch(const exception& e)
		{
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}
}

void StudentDb::parsingJSONData(std::string &JSONData)
{
//	string jsonData = R"({
//	        "location": {
//	            "city": "delitzsch",
//	            "postCode": "49733",
//	            "state": "sachsen-anhalt",
//	            "street": "2575 tannenweg"
//	        },
//	        "name": {
//	            "firstName": "josefine",
//	            "lastName": "stein",
//	            "title": "mrs"
//	        },
//			"dateOfBirth": {
//				"date": 7,
//				"day": 2,
//				"hours": 22,
//				"minutes": 7,
//				"month": 0,
//				"seconds": 13,
//				"time": -914557966854,
//				"timezoneOffset": -120,
//				"year": 41
//			}
//	    })";

	istringstream iss(JSONData);

	boost::property_tree::ptree parsedData;

	boost::property_tree::read_json(iss, parsedData);

	string firstName = parsedData.get<string>("name.firstName");
	string lastName = parsedData.get<string>("name.lastName");
	int year = parsedData.get<int>("dateOfBirth.year")+1900;
	int month = parsedData.get<int>("dateOfBirth.month")+1;
	int day = parsedData.get<int>("dateOfBirth.date");

	Poco::Data::Date dateOfBirth(year, month, day);

	string city = parsedData.get<string>("location.city");
	string street = parsedData.get<string>("location.street");
	int postCode = parsedData.get<int>("location.postCode");
	string additionalInfo = parsedData.get<string>("location.state");

	shared_ptr<Address> address =
			make_shared<Address>(street, postCode, city, additionalInfo);

	Student student(firstName, lastName, dateOfBirth, address);

	this->m_students.insert(make_pair(student.getMatrikelNumber(), student));

}

//void StudentDb::readFromServer()
//{
//	//! Create a socket address
//	Poco::Net::SocketAddress socketAddress("www.hhs.users.h-da.cloud", 4242);
//
//	string noOfUserDate = "1";
//	string readLine;
//
//	cout << "Enter the number of Student Data to be extracted from the server: ";
//	getline(cin, noOfUserDate);
//
//	int loopIdx = 0;
//
//	while(loopIdx < stoi(noOfUserDate))
//	{
//		//! Create a stream socket
//		Poco::Net::StreamSocket socket;
//
//		try
//		{
//			socket.connect(socketAddress, Poco::Timespan(5, 0));
//
//	        //! Create a SocketStream using the socket
//	        Poco::Net::SocketStream stream(socket);
//
//	        stream << "generate";
//	        stream.flush();
//
//	        //! Calling shutdownSend() indicates that you will no longer be sending data on the socket.
//	        socket.shutdownSend();
//
//	        vector<string> serverData;
//
//	        while(getline(stream, readLine))
//	        {
//	        	serverData.push_back(readLine);
//	        }
//
//	        //! Calling shutdownReceive() indicates that you will no longer be receiving data on the socket.
//	        socket.shutdownReceive();
//
//	        stream << "quit";
//	        stream.flush();
//
//	        //! the socket is no longer in use
//	        socket.close();
//
//	        if(serverData.empty() == false)
//	        {
//		        cout << serverData.at(0) << endl; // this prints 100 Generating
//
//		        cout << loopIdx+1 << " User Data\n" << endl;
//
//		        parsingJSONData(serverData.at(1));	//! This line contains the JSON Data required.
//
//		        cout << serverData.at(2) << endl;
//	        }
//		}
//		catch(const Poco::Exception& e)
//		{
//			cerr << "Exception caught: " << e.displayText() << endl;
//		}
//
//		loopIdx++;
//	}
//}

//void StudentDb::parsingJSONData(std::string &JSONData)
//{
//    Poco::JSON::Parser jsonParser;
//
//    Poco::Dynamic::Var parsedJSONData = jsonParser.parse(JSONData);
//
//    Poco::Dynamic::Var parsedJSONDataResult = jsonParser.result();
//
//    //! Get the JSON Object
//    Poco::JSON::Object::Ptr jsonObject = parsedJSONDataResult.extract<Poco::JSON::Object::Ptr>();
//
//    string firstName = jsonObject->get("name")
//    				.extract<Poco::JSON::Object::Ptr>()->getValue<string>("firstName");
//
//    string lastName = jsonObject->get("name")
//    				.extract<Poco::JSON::Object::Ptr>()->getValue<string>("lastName");
//
//    int year = jsonObject->get("dateOfBirth")
//    				.extract<Poco::JSON::Object::Ptr>()->getValue<int>("year")+1900;
//    int month = jsonObject->get("dateOfBirth")
//            				.extract<Poco::JSON::Object::Ptr>()->getValue<int>("month")+1;
//    int day = jsonObject->get("dateOfBirth")
//            				.extract<Poco::JSON::Object::Ptr>()->getValue<int>("date");
//
//    Poco::Data::Date dateOfbirth(year, month, day);
//
//    string streetName = jsonObject->get("location")
//    				.extract<Poco::JSON::Object::Ptr>()->getValue<string>("street");
//    string postalCode = jsonObject->get("location")
//    				.extract<Poco::JSON::Object::Ptr>()->getValue<string>("postCode");
//    string cityName = jsonObject->get("location")
//    				.extract<Poco::JSON::Object::Ptr>()->getValue<string>("city");
//    string additionalInfo = jsonObject->get("location")
//    				.extract<Poco::JSON::Object::Ptr>()->getValue<string>("state");
//
//    shared_ptr<Address> address =
//    		make_shared<Address>(streetName, stoi(postalCode), cityName, additionalInfo);
//
//    Student student = Student(firstName, lastName, dateOfbirth, address);
//
//    this->m_students.insert(make_pair(student.getMatrikelNumber(), student));
//}

//void StudentDb::parsingJSONData(std::string &JSONData)
//{
//	Poco::JSON::Parser jsonParser;
//
//	Poco::Dynamic::Var parsedJSONData = jsonParser.parse(JSONData);
//
//	Poco::JSON::Object::Ptr jsonObjectPtr = parsedJSONData.extract<Poco::JSON::Object::Ptr>();
//
//	Poco::DynamicStruct JSONDataStruct = *jsonObjectPtr;
//
//	string firstName = Poco::UTF8::unescape(JSONDataStruct["name"]["firstName"].toString());
//	string lastName = Poco::UTF8::unescape(JSONDataStruct["name"]["lastName"].toString());
//	int year = JSONDataStruct["dateOfBirth"]["year"].convert<int>()+1900;
//	int month = JSONDataStruct["dateOfBirth"]["month"].convert<int>()+1;
//	int day = JSONDataStruct["dateOfBirth"]["date"].convert<int>();
//
//	string streetName = Poco::UTF8::unescape(JSONDataStruct["location"]["street"].toString());
//	int postalCode = JSONDataStruct["location"]["postCode"].convert<int>();
//	string cityName = Poco::UTF8::unescape(JSONDataStruct["location"]["city"].toString());
//	string additionalInfo = Poco::UTF8::unescape(JSONDataStruct["location"]["state"].toString());
//
//	shared_ptr<Address> address =
//			make_shared<Address>(streetName, postalCode, cityName, additionalInfo);
//
//	Student student = Student(firstName, lastName, Poco::Data::Date(year, month, day), address);
//
//	this->m_students.insert(make_pair(student.getMatrikelNumber(), student));
//}
