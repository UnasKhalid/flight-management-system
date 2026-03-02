/*
 *  File Name: flight.cpp
 *  Assignment: Term Project
 *  Lecture Section: L01
 *  Completed by: Jacob Plourde
 *  Development Date: November 29, 2025
 */
#include "flight.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

Flight::Flight(const string& id, int num_rows, int num_seats_per_row, const string& source, const string& dest): id(id), number_of_rows(num_rows), number_of_seats_per_row(num_seats_per_row) {
  route = Route(source, dest);
  populate_seats_vector();
}

void Flight::populate_seats_vector() {
  // Creates all seat objects in a matrix.
  seats.resize(number_of_rows);
  for(int i = 0; i < number_of_rows; i++) {
    seats.at(i).resize(number_of_seats_per_row);
  }

  // Sets all seat row numbers and characters based on their position in the matrix.
  for(int i = 0; i < number_of_rows; i++) {
    for(int j = 0; j < number_of_seats_per_row; j++) {
      seats.at(i).at(j).set_row_number(i);
      seats.at(i).at(j).set_seat_character('A' + j);
    }
  }
}

void Flight::addPassenger(int id, string& fname, string& lname, string& phone, int row_num, char seat_char) {
  passengers.push_back(Passenger(id, fname, lname, phone, &seats.at(row_num - 1).at(seat_char - 'A')));
  seats.at(row_num - 1).at(seat_char - 'A').set_occupied(true);
}

void Flight::removePassenger(int id) {
  for(size_t i = 0; i < passengers.size(); i++) {
    Passenger *cur = &passengers.at(i);
    if(cur->get_id() == id) {
      cur->get_seat()->set_occupied(false);
      passengers.erase(passengers.begin() + i);
    }
  }
}

void Flight::print_seat_map() {
  cout << "Aircraft Seat Map for Flight " << id << endl;
  // Seat char row.
  cout << setw(2) << ' ';
  for(size_t i = 0; i < seats.at(0).size(); i++) {
    cout << setw(4) << static_cast<char>(i + 'A');
  }
  cout << endl << setw(4) << "+";
  for(size_t i = 0; i < seats.at(0).size(); i++) {
    cout << "---+";
  }
  cout << endl;

  // Fill table.
  for(size_t row = 0; row < seats.size() * 2; row++) {
    // Intial column, alternating row num and table boundary.
    if(row % 2 == 0) {
      cout << setw(3) << row / 2 + 1 << "|";
    }
    else {
      cout << setw(4) << "+";
    }

    for(size_t col = 0; col < seats.at(row / 2).size(); col++) {
      // Each seat in a row, alternating row num and table boundary.
      if(row % 2 == 0) {
        cout << setw(2) << (seats.at(row / 2).at(col).get_occupied() ? 'X' : ' ') << setw(2) << "|";
      }
      else {
        cout << "---+";
      }
    }
    cout << endl;
  }
}

