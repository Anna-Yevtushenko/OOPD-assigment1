#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Ticket {
private:
	string passengerName;
	string seatNumber;
	bool seatAvailability;
	string flightNumber;
	double ticketprice;
public:
	Ticket(string name, string seat, bool availible, string flight, double cost)
		: passengerName(name), seatNumber(seat), seatAvailability(availible), flightNumber(flight),Ticketprice(cost){
	}
	Ticket(string seat , string flight , double cost)
		: passengerName("Unknown"), seatNumber(seat), seatAvailability(false), flightNumber(flight) , Ticketprice(cost) {}

	~Ticket() {}


	string getPassengerName() const {
		return passengerName;
	}

	string getSeatNumber()const { 
		return seatNumber;
	}

	bool getSeatAvailability() const {
		return seatAvailability;

	}

	string getFlightNumber() const {
		return flightNumber;
	}
	double getTicketPrice() const {
		return ticketprice;
	}


};



class Airplane {
private:
	string flightNumber;
	string flightDate;
	map<string, bool> seatAvailability;
	map<string, Ticket> bookedTickets;
public:
	Airplane(string flightnumber, string date, vector<string> seats)
		: flightNumber(flightnumber), flightDate(date) {
		for (int i = 0; i < seats.size(); ++i) {
			seatAvailability[seats[i]] = false;
		}
	}
		bool checkSetAvailible(string seatNumber){
			if (seatAvailability.find(seatNumber) != seatAvailability.end()) {
				return !seatAvailability[seatNumber];
			}
			else {
				cout << "The ticket with number: " << seatNumber << " is not found" << endl;
				return false;
			}
		
		}


};



int main() {




	return 0;
}
