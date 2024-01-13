/*!
 * @file SimpleUI.h
 *
 * \n Created on: 13-Jan-2024
 * @author Girish Tabaraddi
 *
 * Built on: \showdate "%A %d-%m-%Y %H:%M:%S"
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDb.h"
#include <string>

class SimpleUI
{
private:
	/*!
	 * @var m_db - a reference to StudentDb class.
	 */
	StudentDb& m_db;

public:
	/*!
	 * A parameterized constructor that initializes the StudentDb class.
	 * @param m_db
	 */
	SimpleUI(StudentDb& db);

	/*!
	 * A Default destructor of SimpleUI class.
	 */
	virtual ~SimpleUI();

	/*!
	 * This method lists all the properties available in the database,
	 * requests input from user and executes the respective operation.
	 */
	void run();
};

#endif /* SIMPLEUI_H_ */
