/*
 *  File Name: flight.h
 *  Assignment: Term Project
 *  Lecture Section: L01
 *  Completed by: Jacob Plourde
 *  Development Date: November 29, 2025
 */
#ifndef FLIGHT_H
#define FLIGHT_H

#include <vector>
#include <string>
#include "seat.h"
#include "passenger.h"
#include "route.h"

using std::vector;
using std::string;

class Flight {
private:
    string id;
    vector<vector<Seat>> seats;
    vector<Passenger> passengers;
    int number_of_rows;
    int number_of_seats_per_row;
    Route route;

    /*
     * Requires:
     *    number_of_rows > 0 and number_of_seats_per_row > 0.
     *
     * Promises:
     *    Resizes the seat matrix to match the aircraft dimensions.
     *    Initializes each Seat object with correct row number and seat character.
     *    All seats remain unoccupied.
     */

    void populate_seats_vector();

public:
    Flight() : number_of_rows(0), number_of_seats_per_row(0) {}

    /* 
     * Requires:
     *    num_rows > 0, num_seats_per_row > 0.
     *    id, source, and dest are valid non-empty strings.
     *
     * Promises:
     *    Initializes a Flight with the given ID, route, seat layout.
     *    All seats will be created and marked unoccupied.
     */
    Flight(const string& id, int num_rows, int num_seats_per_row, const string& source, const string& dest);

    
    /*
     * Requires:
     *    row_num is a valid row index in [1, number_of_rows].
     *    seat_char is a valid seat letter in ['A', ...].
     *    The specified seat must not already be occupied.
     *
     * Promises:
     *    Creates a new Passenger and adds them to the passenger list.
     *    Marks the corresponding seat as occupied.
     */
    void addPassenger(int id, string& fname, string &lname, string& phone, int row_num, char seat_char);


    /*
     * Requires:
     *    id corresponds to an existing passenger on the flight.
     *
     * Promises:
     *    Marks the passenger’s seat as unoccupied.
     *    
     */
    void removePassenger(int id);


    /*
     * Requires:
     *    Seats must have been initialized via populate_seats_vector().
     *
     * Promises:
     *    Outputs a formatted seat map to standard output.
     *    Displays each seat as 'X' if occupied or blank if free.
     */
    void print_seat_map();

    int get_number_of_rows() const { return number_of_rows; }
    int get_number_of_seats_per_row() const { return number_of_seats_per_row; }
    string get_id() const { return id; }
    const Route& get_route() const { return route; }

    // Correct accessors for passengers & seats
    const vector<vector<Seat>>& get_seats() const { return seats; }

    const vector<Passenger>& get_passengers() const { return passengers; }
};

#endif

