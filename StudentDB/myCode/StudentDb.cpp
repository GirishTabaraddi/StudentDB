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

void StudentDb::addNewCourse(std::string &courseKey, std::string &title,
		std::string &major, std::string &credits, std::string &courseType,
		std::string &startTime, std::string &endTime, std::string &startDate,
		std::string &endDate, std::string &dayOfWeek)
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
}

void StudentDb::listCourses()
{
	cout << this->m_courses.size() << endl;

	for(const auto& courses: this->m_courses)
	{
		courses.second.get()->print();
	}
}

void StudentDb::addNewStudent(std::string &firstName, std::string &lastName,
		std::string &DoBstring, std::string &streetName,
		std::string &postalCode, std::string &cityName,
		std::string &additionalInfo)
{
	shared_ptr<Address> address =
			make_shared<Address>(streetName, stoi(postalCode), cityName, additionalInfo);

	Student student = Student(firstName, lastName, stringToPocoDateFormatter(DoBstring), address);

	this->m_students.insert(make_pair(student.getMatrikelNumber(), student));
}

void StudentDb::addEnrollment(std::string &matrikelNumber,
		std::string &semester, std::string &courseKey)
{
	auto matrikelNumberItr = this->m_students.find(stoi(matrikelNumber));

	if(matrikelNumberItr != this->m_students.end())
	{
		auto findCourseIdItr = this->m_courses.find(stoi(courseKey));

		if(findCourseIdItr != this->m_courses.end())
		{
			const Course& courseref = *(findCourseIdItr->second);

			matrikelNumberItr->second.addEnrollment(semester, &courseref);
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
		coursesPair.second.get()->write(out);
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

	//! This is the count present on the first line before the list of courses
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

	//! This is the count present on the first line before the list of students
	getline(in, count);
	unsigned int noOfStudents = stoi(count);

	unsigned int loopIdx = 0;
	unsigned int highestMatrikelNumber = 0;

	while(loopIdx < noOfStudents)
	{

		getline(in, readLine);
		istringstream iss(readLine);

		vector<string> filedata;

		while(getline(iss, readLine, ';'))
		{
			filedata.push_back(readLine);
		}

		unsigned int matrikelNumber =
				(filedata.size()>=1) ? stoi(filedata.at(0)) : 0;
		string firstName =
				(filedata.size()>=2) ? filedata.at(1) : "(firstName not assigned)";
		string lastName =
				(filedata.size()>=3) ? filedata.at(2) : "(lastName not assigned)";
		Poco::Data::Date dateOfBirth =
				(filedata.size()>=4) ? stringToPocoDateFormatter(filedata.at(3)) : Poco::Data::Date();
		string streetName =
				(filedata.size()>=5) ? filedata.at(4) : "(streetName not assigned)";
		unsigned int postalCode =
				(filedata.size()>=6) ? stoi(filedata.at(5)) : 0;
		string cityName =
				(filedata.size()>=7) ? filedata.at(6) : "(cityName not assigned)";
		string additionalInfo =
				(filedata.size()>=8) ? filedata.at(7) : "(additionalInfo not assigned)";

		shared_ptr<Address> address =
				make_shared<Address>(streetName, postalCode, cityName, additionalInfo);

		Student addStudent(firstName, lastName, dateOfBirth, address);

		this->m_students.insert(make_pair(matrikelNumber, addStudent));

		// Update highestMatrikelNumber if needed
		highestMatrikelNumber = (highestMatrikelNumber >= matrikelNumber)
						? highestMatrikelNumber : matrikelNumber;

		loopIdx++;
	}

	// Set the nextMatrikelNumber after processing all students
	Student::setNextMatrikelNumber(highestMatrikelNumber + 1);
}

void StudentDb::processEnrollmentData(std::istream &in)
{
	string count, readLine;

	//! This is the count present on the first line before the list of enrollments.
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

		unsigned int matrikelNumber =
				(filedata.size()>=1) ? stoi(filedata.at(0)) : 0;
		unsigned int courseKey =
				(filedata.size()>=2) ? stoi(filedata.at(1)) : 0;
		string semester =
				(filedata.size()>=3) ? filedata.at(2) : "(semester not assigned)";
		float grade =
				(filedata.size()>=4) ? stof(filedata.at(3)) : 0.0;

		auto studentItr = this->m_students.find(matrikelNumber);

		if(studentItr != this->m_students.end())
		{
			auto courseItr = this->m_courses.find(courseKey);

			if(courseItr != this->m_courses.end())
			{
				const Course& courseref =  *(courseItr->second);

				//! Check if the student is already enrolled in the specified course (using lambda function).
				//! If enrolled, the iterator 'enrollmentItr' points to the existing enrollment;
				//! otherwise, it points to the end.
				auto isEnrolled = [courseKey](const Enrollment& enrollment){
					return enrollment.getcourse()->getcourseKey() == courseKey;
				};

				auto enrollmentItr = find_if(studentItr->second.getEnrollments().begin(),
						studentItr->second.getEnrollments().end(), isEnrolled);

				//! Check if the 'enrollmentItr' points to the end of enrollments,
				//! indicating that no existing enrollment for the specified courseKey was found.
				if(enrollmentItr == studentItr->second.getEnrollments().end())
				{
					studentItr->second.addEnrollment(semester, &courseref);
					studentItr->second.updateGrade(grade, courseKey);
				}
				else
				{
					cout << ("Enrollment already exists for the specified course.") << endl;
				}
			}
			else
			{
				cout << ("Course not found") << endl;
			}
		}
		else
		{
			cout << ("Student not found") << endl;
		}

		loopIdx++;
	}
}

void StudentDb::readFromServer()
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
					std::cout << serverData.at(0) << std::endl;

					if (serverData.size() > 1)
					{
						//! This line contains the JSON Data required.
						parsingJSONData(serverData.at(1));
					}

					if (serverData.size() > 2)
					{
						std::cout << serverData.at(2) << std::endl;
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
