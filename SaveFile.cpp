//
// Created by gudmundur on 20.11.2018.
//

#include "SaveFile.h"

SaveFile::SaveFile(string name)
{
    this->filename = name;
}

bool SaveFile::setColumnValue(int row, int column, string value)
{
    if (row > 99 || column > 49) return false;
    values[row][column] = value;
    return true;
}

void SaveFile::write()
{
    ofstream fileOutput(filename);
    for (int row = 0; row < 100; row++)
    {
        if (values[row][0].empty()) break;
        for (int column = 0; column < 50; column++)
        {
            if (values[row][column].empty()) break;
            fileOutput << values[row][column] << ";";
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
        string *result = new string[100];
        istringstream iss(line);
        SplitString(iss.str(), ';', result);
        for (int i = 0; i < 100; i++) {
            if (result[i].empty()) break;
            values[lineNum][i] = result[i];
        }
        lineNum++;
    }
}