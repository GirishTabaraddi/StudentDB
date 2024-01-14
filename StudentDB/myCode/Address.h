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

/*!
 * @class Address
 * @brief Represents an address with specific details.
 */
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
     * @brief Parameterized constructor for Address.
     *
     * Initializes all private members of the Address class.
     *
     * @param street 			The street address.
     * @param postalCode 		The postal code.
     * @param cityName 			The city name.
     * @param additionalInfo 	Additional information about the address.
     */
	Address(std::string street, unsigned short postalCode,
			std::string cityName, std::string additionalInfo);

    /*!
     * @brief Default destructor for the Address class.
     */
	virtual ~Address();

    /*!
     * @brief Getter method for the street address.
     *
     * @return const std::string& representing the street address.
     */
	const std::string& getstreet() const;

    /*!
     * @brief Getter method for the postal code.
     *
     * @return unsigned short representing the postal code.
     */
	const unsigned short getpostalCode() const;

    /*!
     * @brief Getter method for the city name.
     *
     * @return const std::string& representing the city name.
     */
	const std::string& getcityName() const;

    /*!
     * @brief Getter method for additional information about the address.
     *
     * @return const std::string& representing additional information.
     */
	const std::string& getadditionalInfo() const;

    /*!
     * @brief Method to print the address.
     *
     * @return std::string representing the formatted address.
     */
	std::string printAddress() const;
};

#endif /* ADDRESS_H_ */
