//
// Created by gudmundur on 20.11.2018.
//

#include "SaveFile.h"

SaveFile::SaveFile(string name)
{
    this->filename = name;
}

void SaveFile::setColumnValue(int row, int column, string value)
{
    values[row][column] = value;
}

void SaveFile::write()
{
    ofstream fileOutput(filename);
    for (auto row : values) {
        for (string comlumn :  row) {
            fileOutput << comlumn << ";";
        }
        fileOutput << endl;
    }
    fileOutput.close();
}

void SaveFile::read()
{
    ifstream fileInput;
    fileInput.open(filename);
    string line;
    int lineNum = 0;

    while (getline(fileInput, line))
    {
        lineNum++;
        string *result = new string[100];
        istringstream iss(line);
        SplitString(iss.str(), ';', result);
        for (int i = 0; i < 100; i++) {
            if (result[i] == "") break;
            values[lineNum][i] = result[i];
        }
    }
}

vector <vector<string>> SaveFile::getValues()
{
    return values;
}