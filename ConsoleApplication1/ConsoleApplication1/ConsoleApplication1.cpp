#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
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
private:
    string flight_no;
    string date;
    int number_seats;
    map<string, Seat> seats;
    vector<SeatRange> seatRanges;

public:
    Airplane() = default;

    Airplane(const string& flight, const string& flightDate, int seats, const vector<SeatRange>& ranges)
        : flight_no(flight), date(flightDate), number_seats(seats), seatRanges(ranges) {
        initializeSeats();  
    }

        string getDate() const { 
            return date; 
        }

        string getFlightNo() const { 
            return flight_no; 
        }

    int getNumberSeats() const { 
        return number_seats; 
    }

    map<string, Seat>& getSeats() {
        return seats; 
    }

    const vector<SeatRange>& getSeatRanges() const { 
        return seatRanges; 
    }



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
        cout << "Available seats for flight " << flight_no << " on date " << date << ":\n";
        for (const auto& seat : seats) {
            if (seat.second.status == "free") {
                cout << seat.second.id << " - " << seat.second.price << "$\n";
            }
        }
    }
};


class Ticket {
private:
    int id;
    string username;
    string seat_number;
    string flight_no;
    double price;

public:

    Ticket() = default;

    Ticket(int idValue, const string& user, const string& seat, const string& flight, double priceValue)
        : id(idValue), username(user), seat_number(seat), flight_no(flight), price(priceValue) {}

    int getId() const { 
        return id; 
    }

    string getUsername() const { 
        return username; 
    }

    string getSeatNumber() const { 
        return seat_number; 
    }

    string getFlightNo() const { 
        return flight_no; 
    
   }

    double getPrice() const { 
        return price; 
    }

};




class AirlineSystem {
public:
    map<string, Airplane> airplanes;
    map<int, Ticket> tickets;
    int ticketCounter = 1;

    void fillAirplaneFromLine(Airplane& airplane, const string& line) {
        istringstream iss(line);
        int startRow, endRow;
        double price;
        char dash, dollar;
        string date, flight_no;
        int number_seats;

        iss >> date >> flight_no >> number_seats;

        vector<SeatRange> seatRanges;
        while (iss >> startRow >> dash >> endRow >> price >> dollar) {
            if (dollar != '$') {
                cout << "Format error: expected $ after price." << endl;
                return;
            }
            seatRanges.push_back(SeatRange{startRow, endRow, price, number_seats});
        }

        airplane = Airplane(flight_no, date, number_seats, seatRanges);
    }

    void checkFlight(const string& date, const string& flight_no) const {
        if (airplanes.find(flight_no) != airplanes.end()) {
            const Airplane& airplane = airplanes.at(flight_no);
            if (airplane.getDate() == date) {
                airplane.checkAvailability();  
                return;
            }
        }
        cout << "Record not found or incorrect date.\n";
    }

    void bookSeat(const string& date, const string& flight_no, const string& seatId, const string& username) {
        if (airplanes.find(flight_no) == airplanes.end()) {
            cout << "Flight not found or incorrect date.\n";
            return;
        }

        Airplane& airplane = airplanes[flight_no];

        if (airplane.getDate() != date) {
            cout << "Date is incorrect.\n";
            return;
        }

        auto& seats = airplane.getSeats();
        if (seats.find(seatId) == seats.end()) {
            cout << "Seat doesn't exist for flight " << airplane.getFlightNo() << endl;
            return;
        }

        if (seats[seatId].status == "free") {
            seats[seatId].status = "booked";

            Ticket ticket(ticketCounter++, username, seatId, flight_no, seats[seatId].price);
            tickets[ticket.getId()] = ticket;

            cout << "Booking confirmed with seat ID " << seatId << endl;
        } else {
            cout << "Seat is already booked.\n";
        }
    }

    void returnTicket(int ticketId) {
        if (tickets.find(ticketId) == tickets.end()) {
            cout << "Ticket not found.\n";
            return;
        }

        Ticket& ticket = tickets[ticketId];
        Airplane& airplane = airplanes[ticket.getFlightNo()];

        auto& seats = airplane.getSeats();
        if (seats[ticket.getSeatNumber()].status == "booked") {
            seats[ticket.getSeatNumber()].status = "free";
            cout << "Refund confirmed for " << seats[ticket.getSeatNumber()].price << "$ to " << ticket.getUsername() << endl;
            tickets.erase(ticketId);  
        } else {
            cout << "The seat is already free.\n";
        }
    }

    void view(int ticketId) const {
        if (tickets.find(ticketId) == tickets.end()) {
            cout << "Ticket not found.\n";
            return;
        }

        const Ticket& ticket = tickets.at(ticketId);
        const Airplane& airplane = airplanes.at(ticket.getFlightNo());
        cout << "Flight " << ticket.getFlightNo() << ", " << airplane.getDate()
            << ", seat " << ticket.getSeatNumber() << ", price " 
            << ticket.getPrice() << "$, " << ticket.getUsername() << endl;
    }

    void view(const string& username) {
        bool found = false;
        for (const auto& pair : tickets) {
            const int& id = pair.first;
            const Ticket& ticket = pair.second;
            const Airplane& airplane = airplanes.at(ticket.getFlightNo());

            if (ticket.getUsername() == username) {
                cout << "Flight " << ticket.getFlightNo() << ", " << airplane.getDate()
                    << ", seat " << ticket.getSeatNumber() << ", price " 
                    << ticket.getPrice() << "$" << endl;
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

            if (ticket.getFlightNo() == flight_no && airplanes.at(flight_no).getDate() == date) {
                cout << "Flight " << ticket.getFlightNo() << ", " << airplanes.at(ticket.getFlightNo()).getDate()
                    << ", seat " << ticket.getSeatNumber() << ", price " << ticket.getPrice()
                    << "$, User: " << ticket.getUsername() << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No tickets found for flight: " << flight_no << " on date: " << date << endl;
        }
    }
};



class FileReader {
public:
    static void readFlightsFromFile(const string& filePath, AirlineSystem& system) {
        ifstream file(filePath);  
        if (!file.is_open()) {
            cerr << "Error opening file: " << filePath << endl;
            return;
        }

        int flightCount;
        file >> flightCount;  
        file.ignore();  

        for (int i = 0; i < flightCount; ++i) {
            string line;
            getline(file, line);  
            Airplane airplane;
            system.fillAirplaneFromLine(airplane, line);
            system.airplanes[airplane.getFlightNo()] = airplane;

        }

        file.close();
        cout << "Successfully read " << flightCount << " flights from the file." << endl;
    }
};

int main() {
    AirlineSystem system;
    FileReader::readFlightsFromFile("D:/OOPD/OOPD-assigment1/ConsoleApplication1/ConsoleApplication1/configurationFile.txt", system);


    string commands[] = {

        "book 11.12.2022 FQ12 1A AdamSmith",
        "book 11.12.2022 FQ12 1B AdamSmith",
        //"book 11.12.2022 FQ12 1C AdamSmith",
        //"book 11.12.2022 FQ12 1D AdamSmith",
        //"book 11.12.2022 FQ12 1E AdamSmith",
        //"book 11.12.2022 FQ12 1F AdamSmith",
        //"book 11.12.2022 FQ12 1G AdamSmith",
        //"book 11.12.2022 FQ12 1H AdamSmith",
        //"book 11.12.2022 FQ12 1I AdamSmith",
        //"book 11.12.2022 FQ21 1I AdamSmith",
        "view 10",
        //"book 11.12.2022 FQ12 1A AdamSmith",
        //"book 11.12.2022 F5612 1A AdamSmith",
        //"book 12.12.2022 FQ12 1A AdamSmith",
        //"book 11.12.2022 FQ12 1A AdamdSmith",

        "check 11.12.2022 FQ12",

        "view 11.12.2022 FQ12",
        "view 1"
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

        } else if (cmd == "view") {
            string param1;
            iss >> param1;
            if (all_of(param1.begin(), param1.end(), ::isdigit)) {  
                int ticketId = stoi(param1);
                system.view(ticketId);
            } else if (param1.find('.') != string::npos) {  
                string flight_no;
                iss >> flight_no;
                system.view(param1, flight_no);
            } else {  
                system.view(param1);
            }
        } else {
            cout << "Unknown command: " << cmd << endl;
        }
    }

    return 0;
}
