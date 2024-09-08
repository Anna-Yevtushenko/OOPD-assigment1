#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

class Ticket {
private:
    string passengerName;
    string seatNumber;
    bool seatAvailability;
    string flightNumber;
    double ticketPrice;
    int bookingID;

public:
    Ticket() : passengerName("Unknown"), seatNumber("Unknown"), seatAvailability(false), flightNumber("Unknown"), ticketPrice(0.0), bookingID(0) {
    }

    Ticket(string name, string seat, string flight, double price, int id)
        : passengerName(name), seatNumber(seat), flightNumber(flight), ticketPrice(price), bookingID(id), seatAvailability(true) {}

    ~Ticket() {}

    string getPassengerName() const {
        return passengerName;
    }

    string getSeatNumber() const { 
        return seatNumber;
    }

    bool getSeatAvailability() const {
        return seatAvailability;
    }

    string getFlightNumber() const {
        return flightNumber;
    }

    double getTicketPrice() const {
        return ticketPrice;
    }

    int getBookingID() const { 
        return bookingID; 
    }

    void cancelBooking() { 
        seatAvailability = false; 
    }

    void printTicketInfo() const {
        cout << "Passenger: " << passengerName << ", Seat: " << seatNumber
            << ", Flight: " << flightNumber << ", Price: $" << ticketPrice
            << ", Booking ID: " << bookingID << endl;
    }
};

class Airplane {
private:
    string flightNumber;
    string flightDate;
    map<string, bool> seatAvailability;
    map<int, Ticket> bookedTickets;  
    map<string, double> rowPrices;  
    int bookingCounter;  

public:
    Airplane(string flightnumber, string date, vector<string> seats, map<string, double> prices)
        : flightNumber(flightnumber), flightDate(date), rowPrices(prices), bookingCounter(1) {
        for (const auto& seat : seats) {
            seatAvailability[seat] = false;  
        }
    }

    bool isSeatAvailable(string seatNumber) {  
              
        if (seatAvailability.find(seatNumber) != seatAvailability.end()) {
            return !seatAvailability[seatNumber];  
        } else {
            cout << "The ticket with number: [" << seatNumber << "] is not found" << endl;
            return false;
        }
    }


};

vector<string> generateSeats(int seatsPerRow, int rows) {
    vector<string> seats;
    string seatLetters = "ABCDEF";  

    for (int row = 1; row <= rows; ++row) {
        for (int seat = 0; seat < seatsPerRow; ++seat) {
            seats.push_back(to_string(row) + seatLetters[seat]);  
        }
    }
    return seats;
}

int main() {
    ifstream file("D:/OOPD/OOPD-assigment1/ConsoleApplication1/ConsoleApplication1/configurationFile.txt");
    if (!file.is_open()) {
        cout << "Error with opening file" << endl;
        return 1;
    }

   

    file.close();
    return 0;
}
