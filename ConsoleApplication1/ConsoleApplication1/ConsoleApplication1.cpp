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



    void bookSeat(const string& flightNo, const string& seatNumber, const string& username) {

        if (flightNo != flightNumber) {
            cout << "Error: Flight number does not match. Can't book seat on flight " << flightNo << endl;
            return;  
        }
        if (isSeatAvailable(seatNumber)) {
            seatAvailability[seatNumber] = true;
            int bookingID = bookingCounter++;

            cout << "Booking seat: [" << seatNumber << "]" << endl;
            cout << "Seat number length: " << seatNumber.length() << endl;


            string row = "";
            for (char ch : seatNumber) {
                if (isdigit(ch)) {
                    row += ch;  
                } else {
                    break;  
                }
            } 

            cout << "Row extracted: " << row << endl;


            if (rowPrices.find(row) == rowPrices.end()) {
                cout << "Error: No price for row " << row << endl;
                return;
            }

            double ticketPrice = rowPrices[row];   
            Ticket newTicket(username, seatNumber, flightNo, ticketPrice, bookingID);
            bookedTickets[bookingID] = newTicket;  

            cout << "Seat " << seatNumber << " has been successfully booked for " << username << " at price $" << ticketPrice << endl;
            cout << "Confirmed with Booking ID: " << bookingID << endl;

        } 
        else {
            cout << "Seat " << seatNumber << " is already booked or not available." << endl;
        }
    }    


};

vector<string> generateSeats(int seatsPerRow, int rows) {
    vector<string> seats;
    string seatLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
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

    int numberRecords;
    file >> numberRecords;
    string line;
    getline(file, line);

    vector<Airplane> airplanes;  

    for (int i = 0; i < numberRecords; i++) {  
        getline(file, line);
        cout << line << endl;
        stringstream ss(line);
        string flightDate, flightNumber;
        string rowRange1, rowRange2;
        string priceStr1, priceStr2;
        int seatsPerRow;
        ss >> flightDate >> flightNumber >> seatsPerRow >> rowRange1 >> priceStr1 >> rowRange2 >> priceStr2;

        string rowRange1Clean = "", rowRange2Clean = "", priceStr1Clean = "", priceStr2Clean = "";

        for (char ch : rowRange1) {
            if (ch != '-') {
                rowRange1Clean += ch;  
            }
        }

        for (char ch : rowRange2) {
            if (ch != '-') {
                rowRange2Clean += ch;  
            }
        }

        for (char ch : priceStr1) {
            if (ch != '$') {
                priceStr1Clean += ch;  
            }
        }

        for (char ch : priceStr2) {
            if (ch != '$') {
                priceStr2Clean += ch;  
            }
        }

        int rowStart1 = stoi(rowRange1Clean.substr(0, 1));
        int rowEnd1 = stoi(rowRange1Clean.substr(1));
        int rowStart2 = stoi(rowRange2Clean.substr(0, 2));
        int rowEnd2 = stoi(rowRange2Clean.substr(2));
        double price1 = stod(priceStr1Clean);
        double price2 = stod(priceStr2Clean);

        vector<string> seats = generateSeats(seatsPerRow, rowEnd2);
        map<string, double> rowPrice;

        for (int row = rowStart1; row <= rowEnd1; row++) {
            rowPrice[to_string(row)] = price1;
        }
        for (int row = rowStart2; row <= rowEnd2; row++) {
            rowPrice[to_string(row)] = price2;
        }


        Airplane airplane(flightNumber, flightDate, seats, rowPrice);
        airplanes.push_back(airplane);
    }


    airplanes[0].bookSeat("FQ12", "8A", "JohnDoe");  
    airplanes[1].bookSeat("FQ132", "30A", "John");    

    file.close();
    return 0;
}

