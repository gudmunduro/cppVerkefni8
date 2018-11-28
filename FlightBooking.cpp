#include "FlightBooking.h"//
// Created by gudmundur on 25.10.2018.
//

#include "FlightBooking.h"

FlightBooking::FlightBooking(int id, int capacity, int reserved)
{
    this->id = id;
    this->capacity = capacity;
    if (!isAllowedReservation(reserved))
    {
        throw invalid_argument("Reserved value above capacity");
    }
    if (reserved < 0) reserved = 0; // Ef það er í mínus breytist það í núll
    this->reserved = reserved;
}
void FlightBooking::printStatus()
{
    const float seatsReserved = ((float)reserved) / ((float)capacity) * 100.0f;
    cout << "Flight " << id << " : " << reserved << "/" << capacity << " (" << seatsReserved << "%) seats reserved" << endl;
}
bool FlightBooking::reserveSeats(int number_ob_seats)
{
    if (isAllowedReservation(number_ob_seats + reserved) && number_ob_seats >= 0) // Ef niðurstaðan eftir breytingar er leyfileg og talan sem var sett inn er ekki í mínus
    {
        reserved += number_ob_seats;
        return true;
    }
    return false;
}
bool FlightBooking::canceReservations(int number_ob_seats)
{
    if (reserved - number_ob_seats >= 0 && number_ob_seats >= 0) // Ef niðurstaðan eftir breytingu verður hærri en núll og talan sem var sett inn er ekki í mínus
    {
        reserved -= number_ob_seats;
        return true;
    }
    return false;
}
bool FlightBooking::isAllowedReservation(int reservation)
{
    return ((float)reservation) / ((float)capacity) < 1.05; // Skilar true eða false eftir því hvort það sé yfir leyfilega magninu sem er 105%
}

int FlightBooking::getReserved() {
    return reserved;
}

int FlightBooking::getCapacity() {
    return capacity;
}

// Operators

bool FlightBooking::operator < (FlightBooking *compare_to)
{
    return this->id < compare_to->id;
}

bool FlightBooking::operator > (FlightBooking *compare_to)
{
    return this->id > compare_to->id;
}

bool FlightBooking::operator >= (FlightBooking *compare_to)
{
    return this->id >= compare_to->id;
}

bool FlightBooking::operator <= (FlightBooking *compare_to)
{
    return this->id <= compare_to->id;
}

bool FlightBooking::operator == (FlightBooking *compare_to)
{
    return this->id == compare_to->id;
}

bool FlightBooking::operator != (FlightBooking *compare_to)
{
    return this->id != compare_to->id;
}

ostream& operator<<(ostream& ostr, FlightBooking &booking) {
    const float seatsReserved = ((float)booking.getReserved()) / ((float)booking.getCapacity()) * 100.0f;
    return ostr << "Flight " << booking.id << " : " << booking.getReserved() << "/" << booking.getCapacity() << " (" << seatsReserved << "%) seats reserved";
}

// FlightBooking list

FlightBookingList::FlightBookingList()
{
    first = nullptr;
}

bool FlightBookingList::add(int id, FlightBooking *booking)
{
    /*Bætir inn í listann*/
    if (has(id)) return false; // Ef elemt með sama id er nú þegar til hættir það við

    FlightBookingElement *el = new FlightBookingElement; // Býr til nýtt element
    el->id = id; // Setur idið á því
    el->booking = booking; // Setur booking instance á því

    if (first == nullptr) // Ef firsta er ekki til (listinn tómur
    {
        first = el; // Setur það einfaldlega elementið á first breytuna
        return true; // Skilar true sem þýðir að það hafi tekist
    }
    if (id < first->id) // Ef idið er minna en það á því fyrsta
    {
        el->next = first; // Breytir next á nýja í það sjálft
        first = el; // Og setur síðan fyrsta í það nýja
        return true;
    }
    if (first->next == nullptr) // Ef það er bara eitt stak í listanum
    {
        first->next = el; // Setur það next á fyrsta
        return true;
    }
    if (last()->id < id) // Ef idið á nýja er undir því sem er aftast
    {
        last()->next = el; // Setur það bara next á síðasta
        return true;
    }

    FlightBookingElement* elBefore = getElementBefore(id); // Finnur það sem er fyrir neðan idið (á staðnum sem á að setja inn í)
    if (elBefore == nullptr) return false; // Ef það kemur ekkert út úr því er hætt við

    el->next = elBefore->next; // Setur next á því nýja í next á því sem það fann fyrir neðan
    elBefore->next = el; // Og next á því fyrir neðan í það nýja
    return true; // Skilar síðan true því það hefur tekist að setja inn í
}

FlightBooking* FlightBookingList::get(int id)
{
    /* Skilar instance af FlightBooking fyrir id */
    if (has(id)) return getElement(id)->booking;
    return nullptr;
}

FlightBookingElement *FlightBookingList::getElement(int id)
{
    /* Skilar instance af FlightBookingElement fyrir id */
    FlightBookingElement *current = first;
    while (current != nullptr)
    {
        if (current->id == id) return current;
        current = current->next;
    }
    return nullptr;
}

FlightBookingElement *FlightBookingList::getElementBefore(int id)
{
    FlightBookingElement *current = first;
    FlightBookingElement *last = nullptr;
    while (current != nullptr)
    {
        if (current->id > id) return last;
        last = current;
        current = current->next;
    }
    return nullptr;
}

bool FlightBookingList::has(int id)
{
    return getElement(id) != nullptr;
}

FlightBookingElement *FlightBookingList::last()
{
    FlightBookingElement *current = first;
    while (current != nullptr)
    {
        if (current->next == nullptr) return current;
        current = current->next;
    }
    return nullptr;
}

void FlightBookingList::printAll() {
    FlightBookingElement *current = first;
    while (current != nullptr)
    {
        current->booking->printStatus();
        current = current->next;
    }
}

void FlightBookingList::remove(int id)
{
    FlightBookingElement *current = first;
    FlightBookingElement *last = nullptr;
    while (current != nullptr)
    {
        if (current->id == id) {
            if (last != nullptr) last->next = current->next;
            if (first == current){
                if (first->next != nullptr) first = first->next;
                else first = nullptr;
            }
            return;
        }

        last = current;
        current = current->next;
    }
}

void FlightBookingList::saveToFile()
{
    SaveFile *saveFile = new SaveFile("flights.csv");

    FlightBookingElement *current = first;
    int currentColumn = 0;
    while (current != nullptr) {
        saveFile->setColumnValue(currentColumn, 0, to_string(current->id)); // Setur id fyrir save fileinn
        saveFile->setColumnValue(currentColumn, 1, to_string(current->booking->getCapacity())); // Setur reserved
        saveFile->setColumnValue(currentColumn, 2, to_string(current->booking->getReserved())); // Setur capacity

        current = current->next;
        currentColumn++;
    }

    saveFile->write();
}

void FlightBookingList::loadFromFile()
{
    SaveFile *saveFile = new SaveFile("flights.csv");
    saveFile->read();
    for (int row = 0; row < 100; row++ /*auto row : saveFile->getValues()*/) {
        if (saveFile->values[row][0].empty()) break;
        FlightBooking *booking = new FlightBooking(stoi(saveFile->values[row][0]), stoi(saveFile->values[row][1]), stoi(saveFile->values[row][2]));
        add(stoi(saveFile->values[row][0]), booking);
    }
}