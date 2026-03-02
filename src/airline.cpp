/*
 *  File Name: airline.cpp
 *  Assignment: ENSF 337 Term Project
 *  Lab and Lecture Section: 1
 *  Completed by: Unas Khalid, Jacob Plourde
 *  Development Date: November 28, 2025
 */

#include "airline.h"

Airline::Airline(const string &name) {
    airline_name = name;
}

void Airline::addFlight(const string &flight_id, int rows, int seats_per_row, const string &origin, const string &destination){
    flight_list.push_back(Flight(flight_id, rows, seats_per_row, origin, destination));
}

vector<Flight>* Airline::get_flights() {
    return &flight_list;
}

string Airline::get_name() const {
    return airline_name;
}
