/*
 *  File Name: flight.h
 *  Assignment: Term Project
 *  Lecture Section: L01
 *  Completed by: Jacob Plourde, Julia Izuogu
 *  Development Date: November 29, 2025
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <climits>

#include "airline.h"
#include "flight.h"
#include "passenger.h"
#include "seat.h"
#include "route.h"

using namespace std;

int get_choice(int min, int max);
int get_int();
int get_string();
int get_num_lines(const string& file);
char get_valid_seat_letter(int maxSeatsPerRow);
string get_nonempty_string(const string &label);

int main(void) {
  // Title.
  cout << "FMAS Version: 1.0" << endl
       << "Term Project - Flight Management Application System" << endl
       << "Produced by group#: 12" << endl
       << "Names: Jacob Plourde, Julia Izuogo, Unas Khalid" << endl << endl
       << "<<< Press Return to Continue >>>" << endl;
  cin.ignore(256, '\n');

  // Load data from files.
  ifstream input;

  // Flight data.
  Airline west_jet("WestJet");
  input.open("flights.txt");
  if(input.fail()) {
    cout << "flights.txt: failed to open file" << endl;
    exit(1);
  }
  {
    // Goes through the file line by line, adding each flight to a vector of flights.
    string id, src, dest;
    int num_rows, num_seats_per_row;
    for(int line = 0; line < get_num_lines("flights.txt"); line++) {
      input >> id >> src >> dest >> num_rows >> num_seats_per_row;
      west_jet.addFlight(id, num_rows, num_seats_per_row, src, dest);
    }
  }
  input.close();

  // Passenger data;
  input.open("passengers.txt");
  if(input.fail()) {
    cout << "passengers.txt: failed to open file" << endl;
    exit(1);
  }
  {
    string flight_id, fname, lname, phone;
    int row_num, seat_char, id;
    for(int line = 0; line < get_num_lines("passengers.txt"); line++) {
      row_num = 0;

      input >> flight_id >> fname >> lname >> phone;

      // Get row number without character because there is no whitespace between the number and character.
      input.get();
      do {
        char c = input.get();
        row_num = 10 * row_num + (c - '0');
      } while(input.peek() >= '0' && input.peek() <= '9');
     
      seat_char = input.get();
      input >> id;

      // Add passenger to a flight, matching the flight id.
      for(size_t i = 0; i < west_jet.get_flights()->size(); i++) {
        if(west_jet.get_flights()->at(i).get_id() == flight_id) {
          west_jet.get_flights()->at(i).addPassenger(id, fname, lname, phone, row_num, seat_char);
        }
      }
    }
  }
  input.close();



  int selected_flight = 0;

  // Main loop.
  while(1) {
    cout << endl;
    // Main menu.
    cout << "Please select one of the following options:" << endl
         << "\t1. Select a flight" << endl
         << "\t2. Display flight seat map" << endl
         << "\t3. Display passenger's information" << endl
         << "\t4. Add a new passenger" << endl
         << "\t5. Remove an existing passenger" << endl
         << "\t6. Save data" << endl
         << "\t7. Quit" << endl;
    cout << "Enter your choice (1, 2, 3, 4, 5, 6, or 7): ";
    int choice = get_choice(1, 7);
    cout << endl;

    switch(choice) {
      // Case for selecting a flight.
      case 1:
        // List flights.
        cout << "Here is the list of available flights. Please select one:" << endl;
        size_t i;
        for(i = 0; i < west_jet.get_flights()->size(); i++) {
          Flight *flight = &west_jet.get_flights()->at(i);
          cout << "\t" << i + 1 << ". " << flight->get_id() << setw(10)
                                        << flight->get_route().get_source() << setw(10)
                                        << flight->get_route().get_destination() << setw(10)
                                        << flight->get_number_of_rows() << setw(6)
                                        << flight->get_number_of_seats_per_row() << endl;
        }
        cout << "Enter your choice: ";
        selected_flight = get_choice(1, i);
        break;
     
      // Case for displaying the selecting flight's seat map.
      case 2:
        // Ensures a flight is selected before the user attempts to list display it's seat map.
        if(!selected_flight) {
          cout << "Must select flight first" << endl;
          break;
        }

        west_jet.get_flights()->at(selected_flight - 1).print_seat_map();
        break;

      // Case for displaying a passenger's information.
      case 3:
        // Ensures a flight is selected before the user attempts to list it's passengers.
        if(!selected_flight) {
          cout << "Must select flight first" << endl;
          break;
        }

        {
          Flight *sel_flight = &west_jet.get_flights()->at(selected_flight - 1);
          // Table title.
          cout << "Passenger List(Flight: " << sel_flight->get_id() << " from "
                                            << sel_flight->get_route().get_source() << " to "
                                            << sel_flight->get_route().get_destination() << ")" << endl;

          // Tabled header.
          cout << left << setw(15) << "First Name" << setw(15) << "Last Name" << setw(15) << "Phone" << setw(8) << "Row" << setw(8) << "Seat" << "ID" << endl;
          cout << string(67, '-') << endl;

          // List passengers, with a separator between rows.
          for(size_t i = 0; i < sel_flight->get_passengers().size() * 2; i++) {
            const Passenger *passenger = &sel_flight->get_passengers().at(i / 2);
            if(i % 2 == 0) {
              cout << left << setw(15) << passenger->get_first_name() << setw(15) << passenger->get_last_name()
                           << setw(15) << passenger->get_phone_number() << setw(8) << passenger->get_seat()->get_row_number() + 1
                           << setw(8) << passenger->get_seat()->get_seat_character() << passenger->get_id() << endl;
            }
            else {
              cout << string(67, '-') << endl;
            }
          }
        }

        
        break;

  
     case 4:
        if (!selected_flight) {
          cout << "Must select flight first\n";
          break;
        }

        {
          Flight &sel_flight = west_jet.get_flights()->at(selected_flight - 1);

          // ---- Get ID (validated integer) ----
          cout << "Please enter the passenger ID: ";
          int id = get_choice(1, INT_MAX);

          // ---- Get strings (validated non-empty) ----
          string fname = get_nonempty_string("first name");
          string lname = get_nonempty_string("last name");
          string phone = get_nonempty_string("phone number");

          // ---- Get row ----
          cout << "Enter the passenger's desired row: ";
          int row = get_choice(1, sel_flight.get_number_of_rows());

          // ---- Get seat letter ----
          cout << "Enter the passenger's desired seat letter (A-"
               << char('A' + sel_flight.get_number_of_seats_per_row() - 1)
               << "): ";
          char seat_char = get_valid_seat_letter(sel_flight.get_number_of_seats_per_row());

          // ---- Check if seat is occupied ----
          if (sel_flight.get_seats().at(row - 1).at(seat_char - 'A').get_occupied()) {
              cout << "Error: That seat is already occupied.\n";
              break;
          }

          // ---- Add passenger ----
          sel_flight.addPassenger(id, fname, lname, phone, row, seat_char);
          cout << "Passenger successfully added.\n";

        }
        break;


      // Case for removing an existing passenger.
    case 5:
        if (!selected_flight) {
                cout << "Must select flight first\n";
                break;
            }

            {
                Flight &sel_flight = west_jet.get_flights()->at(selected_flight - 1);

                // ---- Get ID (validated integer) ----
                cout << "Please enter the ID of the passenger to remove: ";
                int id = get_choice(1, INT_MAX);

                // ---- Remove passenger ----
                bool removed = false;
                auto &passengers = sel_flight.get_passengers(); // reference to vector
                for (size_t i = 0; i < passengers.size(); ++i) {
                    if (passengers.at(i).get_id() == id) {
                        passengers.at(i).get_seat()->set_occupied(false); // free the seat
                        sel_flight.removePassenger(passengers.at(i).get_id()); // remove the passenger
                        removed = true;
                        break;
                    }
                }

                if (removed) {
                    cout << "Passenger with ID " << id << " was successfully removed.\n";
                } else {
                    cout << "Error: No passenger with that ID was found.\n";
                }

            }
            break;
      // Case for saving data to files.
  
    case 6:
    {
        char save_choice;
        cout << "Do you want to save the data in \"passengers.txt\"? (Y or N): ";
        cin >> save_choice;
        save_choice = toupper(save_choice);

        if (save_choice == 'Y') {

            ofstream out("passengers.txt");
            if(out.fail()) {
              cout << "passengers.txt: failed to open" << endl;
              exit(1);
            }

            // Loop through flights
            for (size_t f = 0; f < west_jet.get_flights()->size(); f++) {

                Flight &flight = west_jet.get_flights()->at(f);
                auto &passengers = flight.get_passengers();   // vector<Passenger>

                // Loop through passengers for this flight
                for (size_t p = 0; p < passengers.size(); p++) {

                    const Passenger &passenger = passengers.at(p);
                    Seat *seat = passenger.get_seat();

                    out << flight.get_id() << " "
                        << passenger.get_first_name() << " "
                        << passenger.get_last_name() << " "
                        << passenger.get_phone_number() << " "
                        << seat->get_row_number() + 1
                        << seat->get_seat_character() << " "
                        << passenger.get_id() << endl;
                }
            }

            out.close();
            cout << "All passenger data has been saved." << endl;
        }
        else {
            cout << "Save cancelled." << endl;
        }

    }
    break;

      case 7:
        // Case for quitting.
      {
        cout << "Program terminated." << endl;
        exit(0);
        break;
      }
        
    }
    cout << "<<< Press Return to Continue >>>";
    cin.ignore(256, '\n');
  }
  return 0;
}



int get_choice(int min, int max) {
  /* REQUIRES: min and max are valid integers.
   * PROMISES: Gets user input until the user enters a valid integer within the interval [min, max], and returns this integer.
  */
  while(1) {
    string input;
    getline(cin, input);

    char *endptr;
    int choice = strtol(input.c_str(), &endptr, 10);
    if(*endptr) {
      cout << "Invalid input: Must enter a valid integer. Try again: ";
      continue;
    }

    if(choice < min || choice > max) {
      cout << "Invalid input: Must be between " << min << " and " << max << ". Try again: ";
      continue;
    }

    return choice;
  }
}

int get_num_lines(const string& file) {
  /* REQUIRES: file is the name of a file in the directory the program is run in.
   * PROMISES: returns the line count of the input file.
  */
  int count = 0;
  ifstream input(file);
  if(input.fail()) {
    cout << file << ": failed to open" << endl;
  }
  char chr;
  while((chr = input.get()) != EOF) {
    if(chr == '\n') count++;
  }

  return count;
}

string get_nonempty_string(const string &label) {
  /* REQUIRES: label is a valid string.
   * PROMISES: returns the string that is input by a user, ensuring empty strings are not returned.
  */
    while (true) {
        cout << "Please enter the passenger " << label << ": ";
        string input;
        getline(cin, input);

        if (input.empty()) {
            cout << "Input cannot be empty. Try again.\n";
            continue;
        }

        return input;
    }
}
char get_valid_seat_letter(int maxSeatsPerRow) {
  /* REQUIRES: maxSeatsPerRow is a valid positive interger.
   * PROMISES: returns an alphabetical character equivalent, based on the user input
  */
    while (true) {
        string input;
        getline(cin, input);

        if (input.length() != 1) {
            cout << "Invalid input: enter a single seat letter. Try again: ";
            continue;
        }

        char seat = toupper(input[0]);

        if (seat < 'A' || seat >= char('A' + maxSeatsPerRow)) {
            cout << "Invalid seat: must be between A and "
                 << char('A' + maxSeatsPerRow - 1)
                 << ". Try again: ";
            continue;
        }

        return seat;
    }
}
