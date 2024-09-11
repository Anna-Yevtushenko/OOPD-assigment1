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
};



class Airplane {
public:
    string flight_no;
    string date;
    int number_seats;
    map<string, Seat> seats;
    vector<SeatRange> seatRanges;


    void initializeSeats() {
        for (const auto& range : seatRanges) {
            for (int row = range.startRow; row <= range.endRow; ++row) {
                for (char seat = 'A'; seat <= 'D'; ++seat) { // Guess,that there are 4 places in the row : A, B, C, D
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


    void fillAirplaneFromLine(Airplane& plane, const string& line) {
        istringstream iss(line);
        iss >> plane.date >> plane.flight_no >> plane.number_seats;

        string seatRange;
        int startRow, endRow;
        double price;
        char dash, dollar;

        while (iss >> startRow >> dash >> endRow >> price >> dollar) {
            if (dollar != '$') {
                cout << "Format mistake" << endl;
                return;
            }
            plane.seatRanges.push_back({startRow, endRow, price});
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
};


int main() {
    AirlineSystem system;


    Airplane plane1;
    string line1 = "01.01.2023 JK321 8 1-10 100$ 11-20 90$ 21-30 50$";
    system.fillAirplaneFromLine(plane1, line1);
    system.airplanes[plane1.flight_no] = plane1;


    Airplane plane2;
    string line2 = "03.01.2023 LM654 9 1-25 95$ 26-50 65$";
    system.fillAirplaneFromLine(plane2, line2);
    system.airplanes[plane2.flight_no] = plane2;


    Airplane plane3;
    string line3 = "01.09.2023 JK324 8 1-10 100$ 11-20 90$ 21-30 50$";
    system.fillAirplaneFromLine(plane3, line3);
    system.airplanes[plane3.flight_no] = plane3;

  
    string command = "check 01.01.2023 JK321"; 
    istringstream iss(command);
    string cmd, date, flight_no;
    iss >> cmd >> date >> flight_no;



    if (cmd == "check") {
        system.checkFlight(date, flight_no);
    } else {
        cout << "Unknow command." << endl;
    }

    
    command = "check 03.01.2023 LM654"; 
    istringstream iss2(command);
    iss2 >> cmd >> date >> flight_no;

    if (cmd == "check") {
        system.checkFlight(date, flight_no);
    } else {
        cout << "Unknow command." << endl;
    }



    command = "check 01.09.2023 JK324 ";
    istringstream iss3(command);
    iss3 >> cmd >> date >> flight_no;

    if (cmd == "check") {
        system.checkFlight(date, flight_no);
    } else {
        cout << "Unknow command." << endl;
    }


    return 0;
}
