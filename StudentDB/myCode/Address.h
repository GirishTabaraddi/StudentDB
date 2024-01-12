/*!
 * @file Address.h
 *
 * \n Created on: 10-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <string>
#include <iostream>

class Address
{
private:
	/*!
	 * @var m_street - a variable to store the street name.
	 */
	std::string m_street;

	/*!
	 * @var m_postalCode - a variable to store the postal code.
	 */
	unsigned short m_postalCode;

	/*!
	 * @var m_cityName - string variable that stores a city name.
	 */
	std::string m_cityName;

	/*!
	 * @var m_additionalInfo - string variable that stores additional info on address.
	 */
	std::string m_additionalInfo;

public:

	/*!
	 * A parameterized constructor that initializes all the private members of the Address class.
	 * @param street
	 * @param postalCode
	 * @param cityName
	 * @param additionalInfo
	 */
	Address(std::string street, unsigned short postalCode,
			std::string cityName, std::string additionalInfo);

	/*!
	 * A default destructor of the Address class.
	 */
	virtual ~Address();

	/*!
	 * A getter method that returns the string value of m_street.
	 * @return std::string type
	 */
	const std::string& getstreet() const;

	/*!
	 * A getter method that returns the string value of m_postalCode.
	 * @return unsigned short value.
	 */
	const unsigned short getpostalCode() const;

	/*!
	 * A getter method that returns the string value of m_cityName.
	 * @return std::string type
	 */
	const std::string& getcityName() const;

	/*!
	 * A getter method that returns the string value of m_additionalInfo.
	 * @return std::string type
	 */
	const std::string& getadditionalInfo() const;

	std::string printAddress() const;
};

#endif /* ADDRESS_H_ */
