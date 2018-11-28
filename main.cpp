
#include "FlightBooking.h"
#include "Functions.cpp"

using namespace Functions;

FlightBookingList *flightBookings;

void createArgumentsArray(string *cmdSplit, string *arguments)
{
    for (int i = 0; i < 10; i++)
    {
        arguments[i] = cmdSplit[i + 1];  // Taka úr einu sæti fyrir ofan í cmdSplit því commandið sjálft er fyrst í því
    }
}

void printError(int code = 0)
{
    switch (code)
    {
        case 0: break;
        case 1: cout << "Error: Flight does not exist(Invalid ID)" << endl; break;
        case 2: cout << "Error: Flight already exists" << endl; break;
        case 3: cout << "Error: Invalid command" << endl; break;
        case 4: cout << "Error: Seats cannot be at more than 105% capacity" << endl; break;
        case 5: cout << "Error: Seats cannot be at below 0% capacity" << endl; break;
        case 6: cout << "Error: Unknown error" << endl; break;
    }
    cout << "Cannot perform this operation" << endl;
}

void processCommand(string command, string *arguments)
{
    if (command == "quit") return;

    if (command == "save")
    {
        flightBookings->saveToFile();
        return;
    }

    if (command == "load")
    {
        flightBookings->loadFromFile();
        return;
    }

    if (command == "printall")
    {
        flightBookings->printAll();
        return;
    }

    // Commands með arguments

    if (arguments[0].empty())
    {
        /* Hætta við ef command hefur engin arguments */
        printError(3);
    }

    int id = stoi(arguments[0]);

    if (command == "create")
    {
        if (!flightBookings->has(id))
        {
            if (!flightBookings->add(id, new FlightBooking(id, stoi(arguments[1]), 0)))
                printError(6);
        }
        else printError(2);
    }
    if (command == "delete")
    {
        if (flightBookings->has(id))
            flightBookings->remove(id);
        else printError(1);
    }
    if (command == "add")
    {
        if (flightBookings->has(id))
        {
            if (!flightBookings->get(id)->reserveSeats(stoi(arguments[1])))
                printError(4); // Prentar út error ef það tókst ekki
        }
        else printError(1);
    }
    if (command == "cancel")
    {
        if (flightBookings->has(id))
        {
            if (!flightBookings->get(id)->canceReservations(stoi(arguments[1])))
                printError(5); // Prentar út error ef það tókst ekki
        }
        else printError(1);
    }
}

int main() {

    flightBookings = new FlightBookingList();
    flightBookings->loadFromFile();

    string command;

    while (command != "quit")
    {
        cout << "What would you like to do?: ";
        getline(cin, command);

        if (command.empty())
        {
            /* Hætta við ef ekkert er skirfað */
            printError(3);
            continue;
        }

        string *cmdSplit = new string[11];
        string *arguments = new string[10];
        SplitString(command, ' ', cmdSplit);
        createArgumentsArray(cmdSplit, arguments); // Taka öll arguments og setja í sér array

        processCommand(cmdSplit[0], arguments);

        if (!arguments[0].empty() && flightBookings->has(stoi(arguments[0])))
            flightBookings->get(stoi(arguments[0]))->printStatus(); // Ef flugið með þetta id er til prentar það status
    }

    return 0;
}
