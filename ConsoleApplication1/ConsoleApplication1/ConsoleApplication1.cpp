#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Ticket {
private:
	string passengerName;
	string seatNumber;
	bool seatAvailability;
public:
	Ticket(string name, string seat, bool availible) 
		: passengerName(name), seatNumber(seat), seatAvailability(availible){
	}
	Ticket(string seat)
		: passengerName("Unknown"), seatNumber(seat), seatAvailability(false) {}

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




};



int main() {




	return 0;
}
