#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
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


    void bookSeat(const string& date, const string& flight_no, const string& seatId, const string& username ){

        for (auto& airplane : airplanes) {
            if (airplane.second.date == date && airplane.second.seats[seatId].status == "free") {
                airplane.second.seats[seatId].status = "booked";

                Ticket ticket;
                ticket.id = ticketcounter ++;
                ticket.username = username;
                ticket.seat_number = seatId;
                ticket.flight_no = flight_no;
                tickets[ticket.id] = ticket;

                cout << "Confirmed with ID " <<seatId << endl;
               

            }
            else {
                cout << "The seat is booked or doesn't exist." << endl;
            }
            return;
        }
        cout << "flight not found or data is incorrect" << endl;
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
        "check 01.01.2023 JK321",
        //"check 03.01.2023 LM654",
        //"check 01.09.2023 JK324",
        "book 01.01.2023 JK321 1A AdamSmith",
        "book 01.01.2023 JK321 2A JohnDoe", 
        "book 01.01.2023 JK321 1A JoîîîîhnDoe",
        "return 1" ,
        "book 01.01.2023 JK321 1A JoîîîîhnDoe"
        //"check 01.01.2023 JK321",
    };

    for (const string& command : commands) {
        istringstream iss(command);
        string cmd;
        iss >> cmd;

        if (cmd == "check") {
            string date, flight_no;
            iss >> date >> flight_no;
            system.checkFlight(date, flight_no);
        } else if (cmd == "book") {
            string date, flight_no, seatId, username;
            iss >> date >> flight_no >> seatId >> username;
            system.bookSeat(date, flight_no, seatId, username);
        } else if (cmd == "return") {
            int ticketId;
            iss >> ticketId;  
            system.returnTicket(ticketId);
        } else {
            cout << "Unknown command." << endl;
        }
    }


    return 0;
}