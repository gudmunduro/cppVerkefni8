#pragma once
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

namespace Functions { // Fyiri einhver random föll sem ég held að ég muni geta nota' aftur
    inline string Input(string message = ": ", string nullValue = "")
    {
        // Til að einfalda að fá input frá lyklaborðinu.
        cout << message;
        string input = "";
        do {
            cin >> input;
        } while (input == "");
        return input;
    }
    inline int IntInput(string message = ": ", int nullValue = -1)
    {
        // Til að einfalda að fá input frá lyklaborðinu fyrir integer.
        cout << message;
        int input = nullValue;
        do {
            cin >> input;
        } while (input == -1);
        return input;
    }
    inline void IntArrayInput(int *arrayValue, string message = ": ")
    {
        // Tekur inn input sem array og setur það í arrayValue
        cout << message;
        for (int i = 0; i < 4; i++)
        {
            cin >> arrayValue[i];
        }
    }

    inline void SplitString(string str, char on, string *result)
    {
        string buffer;
        stringstream stream(str);

        int current = 0;
        while (getline(stream, buffer, on))
        {
            result[current] = buffer;
            current++;
        }
    }

    inline void ArrayStringToInt(string* from, int* to, int size)
    {
        for (int i = 0; i < size; i++)
        {
            to[i] = stoi(from[i]);
        }
    }
}