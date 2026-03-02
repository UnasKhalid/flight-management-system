/*
 *  File Name: airline.h
 *  Assignment: ENSF 337 Term Project
 *  Lab and Lecture Section: 1
 *  Completed by: Unas Khalid, Jacob Plourde
 *  Development Date: November 28, 2025
 */

#ifndef HEADER_FOR_AIRLINE
#define HEADER_FOR_AIRLINE
#include "flight.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class Airline {
    
private:
    
    vector<Flight> flight_list;
    string airline_name;

public:
    
    Airline(const string &name);
    
    void addFlight(const string &flight_id, int rows, int seats_per_row, const string &origin, const string &destination);
    /* REQUIRES: flight_id, origin, and destination to be valid strings.
     *           rows and seats_per_row being positive integers.
     * PROMISES: Creates a new Flight object using provided parameters,
     *           then appends it to the airline's internal flight_list vector.
     */
    
    vector<Flight>* get_flights();

    string get_name() const; 
};

#endif
