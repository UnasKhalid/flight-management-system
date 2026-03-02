/*
 *  File Name: route.h
 *  Assignment: ENSF 337 Term Project
 *  Lab and Lecture Section: 1
 *  Completed by: Unas Khalid, Jacob Plourde
 *  Development Date: November 28, 2025
 */

#ifndef HEADER_FOR_ROUTE
#define HEADER_FOR_ROUTE
#include <string>

using std::string;

class Route {

private:
    
    string source;
    string destination;
    
public:

    Route(): source(""), destination("") {};

    Route(const string &from, const string &to);
    /* REQUIRES: from and to being valid, non-empty strings representing
     *           the starting city and destination city, respectively.
     * PROMISES: Initializes a Route object with 'source' set to 'from'
     *           and 'destination' set to 'to'.
     */
        
    string get_source() const;
    
    string get_destination() const;

};

#endif
