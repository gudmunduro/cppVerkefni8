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
    vector <vector<string>> values;
public:
    SaveFile(string name);
    void setColumnValue(int row, int column, string value);
    void write();
    void read();
    vector <vector<string>> getValues();
};


#endif //SKILAVERKEFNI7_SAVEFILE_H
