//
// Created by kaylor on 2021/1/16.
//
#include "iostream"
#include "stdio.h"
#include "fstream"

using namespace std;

void writeFile(ofstream &outFile, uint16_t value, int pow, string &precision, string &footprint);

string generatePartNumberString(uint16_t value, int pow, string &precision, string &footprint);

string getUnitString(int pow);

void outputResistorsInfo(const uint16_t *code, string &footprint);

int main() {
    uint16_t code[] =
            {100, 102, 105, 107, 110, 113, 115, 118, 121, 124, 127, 130, \
            133, 137, 140, 143, 147, 150, 154, 158, 162, 165, 169, 174, \
            178, 182, 187, 191, 196, 200, 205, 210, 215, 221, 226, 232, \
            237, 243, 249, 255, 261, 267, 274, 280, 287, 294, 301, 309, \
            316, 324, 332, 340, 348, 357, 365, 374, 383, 392, 402, 412, \
            422, 432, 442, 453, 464, 475, 487, 499, 511, 523, 536, 549, \
            562, 576, 590, 604, 619, 634, 649, 665, 681, 698, 715, 732, \
            750, 768, 787, 806, 825, 845, 866, 887, 909, 931, 953, 976};
    string footprint[4] = {"0402","0603","0805","1206"};
    for (int i = 0; i < 4; ++i) {
        outputResistorsInfo(code, footprint[i]);
    }

    return 0;
}

void outputResistorsInfo(const uint16_t *code, string &footprint) {
    string precision = "±0.1%";
    ofstream outFile;
    string fileName = footprint;
    fileName += "all.csv";
    outFile.open(fileName.c_str(), ios::out);
    for (int i = 0; i < 96; ++i) {
        writeFile(outFile, code[i], -2, precision, footprint);
    }
    for (int i = 0; i < 96; ++i) {
        writeFile(outFile, code[i], -1, precision, footprint);
    }
    for (int i = 0; i < 96; ++i) {
        writeFile(outFile, code[i], 0, precision, footprint);
    }
    for (int i = 0; i < 96; ++i) {
        writeFile(outFile, code[i], 1, precision, footprint);
    }
    for (int i = 0; i < 96; ++i) {
        writeFile(outFile, code[i], 2, precision, footprint);
    }
    for (int i = 0; i < 96; ++i) {
        writeFile(outFile, code[i], 3, precision, footprint);
    }
    for (int i = 0; i < 96; ++i) {
        writeFile(outFile, code[i], 4, precision, footprint);
    }
//    for (int i = 0; i < 96; ++i) {
//        writeFile(outFile, code[i], 5, precision, footprint);
//    }

    outFile.close();
}

string convertResString(uint16_t value, int pow) {
    string str = to_string(value);
    switch (pow) {
        case -2:
            str.insert(1, "R");
            break;
        case -1:
            str.insert(2, "R");
            break;
        case 0:
            str.insert(3, "R");
            break;
        case 1:
            str.insert(1, "K");
            break;
        case 2:
            str.insert(2, "K");
            break;
        case 3:
            str.insert(3, "K");
            break;
        case 4:
            str.insert(1, "M");
            break;
        case 5:
            str.insert(2, "M");
            break;
    }

    while (str[str.length() - 1] == '0') {
        str.erase(str.length() - 1);
    }
    return str;
}

string generatePartNumberString(uint16_t value, int pow, string &precision, string &footprint) {
    string ret = "RC" + footprint;
    if (precision == "±0.1%") {
        ret += "B";
    } else if (precision == "±0.5%") {
        ret += "D";
    } else if (precision == "±1%") {
        ret += "F";
    } else if (precision == "±5%") {
        ret += "J";
    }
    ret += "R-07";
    ret += convertResString(value, pow);
    ret += "L";
    return ret;
}

string convertValueString(uint16_t value, int pow) {
    string valueString = to_string(value);
    switch (pow) {
        case -2:
        case 1:
        case 4:
            valueString.insert(1, ".");
            break;
        case -1:
        case 2:
        case 5:
            valueString.insert(2, ".");
            break;
    }
    return valueString;
}

string getCodeString(uint16_t value, int pow) {
    string codeString = to_string(value);
    switch (pow) {
        case -2:
            codeString.insert(1, "R");
            break;
        case -1:
            codeString.insert(2, "R");
            break;
        default:
            codeString = to_string(value) + to_string(pow);
            break;
    }
    return codeString;
}

void writeFile(ofstream &outFile, uint16_t value, int pow, string &precision, string &footprint) {
        string type = "C";
    if (footprint == "1206")
    {
        type = "B";
    }
        string unit = getUnitString(pow);
    string valueString = convertValueString(value, pow);
    string partNumberString = generatePartNumberString(value, pow, precision, footprint);
    string codeString = getCodeString(value, pow);

    string description = footprint + " " + valueString + unit + "(" + codeString + ")" + precision;
//    cout << description <<endl;
    outFile << "Resistor," << type <<",," ;
    outFile << description << "," << description << "," << description << ",";
    outFile << valueString << unit << precision << ",'" << footprint << "," << "RES,\\lib\\lib.Schlib,";
    outFile << "r" << footprint << "," << "\\lib\\r" << footprint << ".pcblib,YAGEO(国巨)," << partNumberString;
    outFile << "\n";

}

string getUnitString(int pow) {
    string unit;
    switch (pow) {
        case -2:
            unit = "Ω";
            break;
        case -1:
            unit = "Ω";
            break;
        case -0:
            unit = "Ω";
            break;
        case 1:
            unit = "KΩ";
            break;
        case 2:
            unit = "KΩ";
            break;
        case 3:
            unit = "KΩ";
            break;
        case 4:
            unit = "MΩ";
            break;
        case 5:
            unit = "MΩ";
            break;
    }
    return unit;
}
