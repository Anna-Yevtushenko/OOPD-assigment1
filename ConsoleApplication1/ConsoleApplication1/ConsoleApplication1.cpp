#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

//uint8_t
//uint_16t


class Seat {
public:
    string id;
    double price;
    string status; // "free", "booked"
};

class SeatRange {

public:
    int startRow;
    int endRow;
    double price;
    int seatsPerRow;  
};



class Airplane {
public:
    string flight_no;
    string date;
    int number_seats;
    map<string, Seat> seats;
    vector<SeatRange> seatRanges;


    void initializeSeats() {
        for (auto& range : seatRanges) {
            for (int row = range.startRow; row <= range.endRow; ++row) {
                for (char seat = 'A'; seat < 'A' + range.seatsPerRow; ++seat) {
                    string seatId = to_string(row) + seat;
                    seats[seatId] = {seatId, range.price, "free"};  
                }
            }
        }
    }



    void checkAvailability() const {
        cout << "Availible seats " << flight_no << " on date " << date << ":\n";
        for (const auto& seat : seats) {
            if (seat.second.status == "free") {
                cout << seat.second.id << " " << seat.second.price << "$, ";
            }
        }
        cout << endl;
    }
};



class Ticket {
public:
    int id;
    string username;
    string seat_number;
    string flight_no;
    double price;
};


class AirlineSystem {
public:
    map<string, Airplane> airplanes;
    map<int, Ticket> tickets;
    int ticketcounter = 1;


    void fillAirplaneFromLine(Airplane& plane, const string& line) {
        istringstream iss(line);
        int startRow, endRow;
        double price;
        char dash;

        iss >> plane.date >> plane.flight_no >> plane.number_seats;
        while (iss >> startRow >> dash >> endRow >> price) {
            plane.seatRanges.push_back(SeatRange{startRow, endRow, price, plane.number_seats});
        }

        plane.initializeSeats();
    }


    void checkFlight(const string& date, const string& flight_no) const {
        for (const auto& airplane : airplanes) {
            if (airplane.second.date == date && airplane.second.flight_no == flight_no) {
                airplane.second.checkAvailability();
                return;
            }
        }
        cout << "Record diid not find or date is not correct.\n";
    }


    void bookSeat(const string& date, const string& flight_no, const string& seatId, const string& username) {

        if (airplanes.find(flight_no) == airplanes.end()) {
            cout << "Flight not found or date is`n correct ";
            return;
        }

        Airplane& airplane = airplanes[flight_no];

        if (airplane.date != date) {
            cout << "Date is incorrect" << endl;
            return;
        }

        if (airplane.seats.find(seatId) == airplane.seats.end()) {
            cout << "Seat doesn`t exist for flight " << airplane.flight_no << endl;
            return;

        }


        if (airplane.seats[seatId].status == "free") {
            airplane.seats[seatId].status = "booked";

            Ticket ticket;
            ticket.id = ticketcounter++;
            ticket.username = username;
            ticket.seat_number = seatId;
            ticket.flight_no = flight_no;
            ticket.price = airplane.seats[seatId].price;

            tickets[ticket.id] = ticket;

            cout << "Confirmed with ID " << seatId << endl;

        }
        else {
            cout << "Seat is already booked or does not exist." << endl;
        }

    }


    void returnTicket(int ticketId) {
        if (tickets.count(ticketId) == 0) {
            cout << "Ticket not found" << endl;
            return;
        }

        Ticket& ticket = tickets[ticketId];
        Airplane& airplane = airplanes[ticket.flight_no];

        if (airplane.seats[ticket.seat_number].status == "booked") {
            airplane.seats[ticket.seat_number].status = "free";
            cout << "Confirmed " << airplane.seats[ticket.seat_number].price << "$ refund for " << ticket.username << endl;
            tickets.erase(ticketId);  
        } else {
            cout << "The seat is already free" << endl;
        }
    }


    void view(int ticketId) const {
        if (tickets.find(ticketId) == tickets.end()) {
            cout << "Ticket not found.\n";
            return;
        }

        const Ticket& ticket = tickets.at(ticketId);
        const Airplane& airplane = airplanes.at(ticket.flight_no);
        cout << "Flight " << ticket.flight_no << ", " << airplane.date 
            << ", seat " << ticket.seat_number << ", price " 
            << ticket.price << "$, " << ticket.username << endl;
    }

    void view(const string& username) {
        bool found = false;
        for (const auto& pair : tickets) {
            const int& id = pair.first;
            const Ticket& ticket = pair.second;
            const Airplane& airplane = airplanes.at(ticket.flight_no);

            if (ticket.username == username) {
                cout << "Flight " << ticket.flight_no << ", " << airplane.date 
                    << ", seat " << ticket.seat_number << ", price " 
                    << ticket.price << "$," << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No tickets found for user: " << username << endl;
        }
    }

    void view(const string& date, const string& flight_no) const {
        bool found = false;
        for (const auto& pair : tickets) {
            const Ticket& ticket = pair.second;

            if (ticket.flight_no == flight_no && airplanes.at(flight_no).date == date) {
                cout << "Flight " << ticket.flight_no << ", " << airplanes.at(ticket.flight_no).date
                    << ", seat " << ticket.seat_number << ", price " << ticket.price
                    << "$, User: " << ticket.username << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No tickets found for flight: " << flight_no << " on date: " << date << endl;
        }
    }


};



int main() {
    AirlineSystem system;
    Airplane plane1, plane2, plane3;

    string line1 = "01.01.2023 JK321 8 1-10 100$ 11-20 90$ 21-30 50$";
    string line2 = "03.01.2023 LM654 9 1-25 95$ 26-50 65$";
    string line3 = "01.09.2023 JK324 8 1-10 100$ 11-20 90$ 21-30 50$";

    system.fillAirplaneFromLine(plane1, line1);
    system.fillAirplaneFromLine(plane2, line2);
    system.fillAirplaneFromLine(plane3, line3);

    system.airplanes[plane1.flight_no] = plane1;
    system.airplanes[plane2.flight_no] = plane2;
    system.airplanes[plane3.flight_no] = plane3;

    string commands[] = {
        //"check 01.01.2023 JK321",
        "book 01.01.2023 JK321 1A AdamSmith",
        "book 01.01.2023 JK321 2A JohnDoe",
        //"book 01.01.2023 JK321 1A JoîîîîhnDoe",
        //"return 1",
        //"book 01.01.2023 JK321 1A JoîîîîhnDoe",
        //"view 1",
        //"view AdamSmith",
        "view 01.01.2023 JK321",
    };


    for (const string& command : commands) {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "check") {
            string date, flight_no;
            iss >> date >> flight_no;
            system.checkFlight(date, flight_no);

        }
        else if (cmd == "book") {
            string date, flight_no, seatId, username;
            iss >> date >> flight_no >> seatId >> username;
            system.bookSeat(date, flight_no, seatId, username);

        }
        else if (cmd == "return") {
            int ticketId;
            iss >> ticketId;
            system.returnTicket(ticketId);

        }
        else if (cmd == "view") {
            string param1;
            iss >> param1;
            cout << "Processing view command with param1: " << param1 << endl;

            
            if (all_of(param1.begin(), param1.end(), ::isdigit)) {  
                int ticketId = stoi(param1);
                cout << "Viewing ticket by ID: " << ticketId << endl;
                system.view(ticketId);

            }
            else if (param1.find('.') != string::npos) { 
                string flight_no;
                iss >> flight_no;
                cout << "Viewing tickets for date: " << param1 << " and flight: " << flight_no << endl;
                system.view(param1, flight_no);
            }
            else {  
                cout << "Viewing tickets for user: " << param1 << endl;
                system.view(param1);
            }
        }
        else {
            cout << "Unknown command: " << cmd << endl;
        }
    }

    return 0;


}
    