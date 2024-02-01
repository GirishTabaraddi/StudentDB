/*!
 * @file Address.cpp
 *
 * \n Created on: 10-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#include "Address.h"

using namespace std;

Address::Address(std::string street, unsigned short postalCode,
		std::string cityName, std::string additionalInfo) :
		m_street(street), m_postalCode(postalCode),
		m_cityName(cityName), m_additionalInfo(additionalInfo)
{
}

Address::~Address()
{
}

const std::string& Address::getstreet() const
{
	return this->m_street;
}

const unsigned short Address::getpostalCode() const
{
	return this->m_postalCode;
}

const std::string& Address::getcityName() const
{
	return this->m_cityName;
}

const std::string& Address::getadditionalInfo() const
{
	return this->m_additionalInfo;
}

void Address::write(std::ostream &out) const
{
	out << this->m_street
			<< ";" << to_string(this->m_postalCode)
			<< ";" << this->m_cityName
			<< ";" << this->m_additionalInfo;
}

std::shared_ptr<Address> Address::read(std::istream &in)
{
	string inStr;
	getline(in, inStr);

	string street = splitAt(inStr, ';');
	unsigned int postalCode = stoi(splitAt(inStr, ';'));
	string city = splitAt(inStr, ';');
	string additionalInfo = splitAt(inStr, ';');

	return make_shared<Address>(street, postalCode, city, additionalInfo);
}

std::shared_ptr<Address> Address::fromJson(const boost::json::object &jsonDataObject)
{
	shared_ptr<Address> address = nullptr;

	string street = jsonDataObject.at("street").as_string().c_str();
	string postCodeStr = jsonDataObject.at("postCode").as_string().c_str();
	string city = jsonDataObject.at("city").as_string().c_str();
	string additionalInfo = jsonDataObject.at("state").as_string().c_str();

	if(isPrintable(street) && isPrintable(postCodeStr) &&
			isPrintable(city) && isPrintable(additionalInfo))
	{
		int postCode = (all_of(postCodeStr.begin(), postCodeStr.end(), ::isdigit)) ? stoi(postCodeStr) : 9999;

		address = make_shared<Address>(street, postCode, city, additionalInfo);

		return address;
	}

	return nullptr;
}

boost::json::object Address::toJson() const
{
	boost::json::object returnObj;

	returnObj.emplace("street", this->m_street);
	returnObj.emplace("postalCode", this->m_postalCode);
	returnObj.emplace("cityName", this->m_cityName);
	returnObj.emplace("additionalInfo",  this->m_additionalInfo);

	return returnObj;
}
