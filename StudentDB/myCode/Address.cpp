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

void Address::printAddress() const
{
	cout << this->m_street + ";" + to_string(this->m_postalCode) + ";" +
			this->m_cityName + ";" + this->m_additionalInfo << endl;
}