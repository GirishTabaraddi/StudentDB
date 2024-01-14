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

/*!
 * @class SimpleUI
 * @brief Represents a simple user interface for interacting with a Student Database.
 */
class SimpleUI
{
private:
    /*!
     * @var m_db - A reference to the StudentDb class.
     */
    StudentDb& m_db;

public:
    /*!
     * @brief Parameterized constructor for SimpleUI.
     *
     * Initializes the SimpleUI class with a reference to a StudentDb object.
     *
     * @param db A reference to the StudentDb class.
     */
    SimpleUI(StudentDb& db);

    /*!
     * @brief Default destructor for the SimpleUI class.
     */
    virtual ~SimpleUI();

    /*!
     * @brief Lists all the properties available in the database, requests input from the user,
     *        and executes the respective operation.
     */
    void run();
};


#endif /* SIMPLEUI_H_ */
