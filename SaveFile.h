//
// Created by gudmundur on 20.11.2018.
//

#include <fstream>
#include <vector>
#include "Functions.cpp"

using namespace Functions;

#ifndef SKILAVERKEFNI7_SAVEFILE_H
#define SKILAVERKEFNI7_SAVEFILE_H

class SaveFile {
private:
    string filename;
public:
    SaveFile(string name);
    bool setColumnValue(int row, int column, string value);
    void write();
    void read();
    // vector <vector<string>> getValues();
    string values[50][100];
};


#endif //SKILAVERKEFNI7_SAVEFILE_H
