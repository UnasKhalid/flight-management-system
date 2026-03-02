/*
 *  File Name: passenger.cpp
 *  Assignment: Term Project
 *  Lecture Section: L01
 *  Completed by: Jacob Plourde
 *  Development Date: November 27, 2025
 */
#include "passenger.h"

Passenger::Passenger(int id, const string& fname, const string& lname, const string& phone, Seat *seat): id(id), first_name(fname), last_name(lname), phone_number(phone), seat(seat) {}

