//
// Created by gudmundur on 25.10.2018.
//

#include "Functions.cpp"
#include "SaveFile.h"

#ifndef SKILAVERKEFNI4_FLIGHTBOOKING_H
#define SKILAVERKEFNI4_FLIGHTBOOKING_H


class FlightBooking {
public:
    FlightBooking(int id, int capacity, int reserved);
    void printStatus();
    bool reserveSeats(int number_ob_seats);
    bool canceReservations(int number_ob_seats);
    int getReserved();
    int getCapacity();
    // Operators
    bool operator < (FlightBooking *compare_to);
    bool operator > (FlightBooking *compare_to);
    bool operator >= (FlightBooking *compare_to);
    bool operator <= (FlightBooking *compare_to);
    bool operator == (FlightBooking *compare_to);
    bool operator != (FlightBooking *compare_to);
    ostream& operator << (ostream& stream);
private:
    bool isAllowedReservation(int reservation);
    int id;
    int capacity;
    int reserved;
};


// FlightBooking list
struct FlightBookingElement {
    int id;
    FlightBooking *booking;
    FlightBookingElement *next = nullptr;
};

class FlightBookingList {
private:
    FlightBookingElement *first;
    FlightBookingElement *getElement(int id);
    FlightBookingElement *getElementBefore(int id);
    FlightBookingElement *last();
public:
    FlightBookingList();
    bool add(int id, FlightBooking *booking);
    FlightBooking *get(int id);
    bool has(int id);
    void remove(int id);
    void printAll();
    void saveToFile();
    void loadFromFile();
};


#endif //SKILAVERKEFNI4_FLIGHTBOOKING_H