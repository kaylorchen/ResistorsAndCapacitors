//
// Created by kaylor on 2021/1/16.
//
#include "iostream"
#include "stdio.h"
#include "fstream"

using namespace std;

void writeFile(ofstream &outFile, string &partNumber);

string generatePartNumberString(uint16_t value, int pow, string &precision, string &footprint);

int main() {
    printf("EIA-96:\n");
    uint16_t code[] =
            {100, 102, 105, 107, 110, 113, 115, 118, 121, 124, 127, 130, \
            133, 137, 140, 143, 147, 150, 154, 158, 162, 165, 169, 174, \
            178, 182, 187, 191, 196, 200, 205, 210, 215, 221, 226, 232, \
            237, 243, 249, 255, 261, 267, 274, 280, 287, 294, 301, 309, \
            316, 324, 332, 340, 348, 357, 365, 374, 383, 392, 402, 412, \
            422, 432, 442, 453, 464, 475, 487, 499, 511, 523, 536, 549, \
            562, 576, 590, 604, 619, 634, 649, 665, 681, 698, 715, 732, \
            750, 768, 787, 806, 825, 845, 866, 887, 909, 931, 953, 976};
    string footprint = "0805";
    char partNumber[100] = {0};
//             string description = footprint;
//             string value;
    string precision = "±1%";
    ofstream outFile;
    string fileName = footprint;
    fileName += ".csv";
    outFile.open(fileName.c_str(), ios::out);
//    for (int i = 0; i < 96; ++i) {
//        memset(partNumber, 0, 100);
//        if (code[i] % 100 == 0) {
//            sprintf(partNumber, "RC%sFR-07%dRL", footprint, code[i] / 100);
//        } else {
//            if (code[i] % 10 == 0) {
//                sprintf(partNumber, "RC%sFR-07%dR%dL", footprint, code[i] / 100, code[i] % 100 / 10);
//            } else {
//                sprintf(partNumber, "RC%sFR-07%dR%d%dL", footprint, code[i] / 100, code[i] % 100 / 10, code[i] % 10);
//            }
//        }
//        string tmp = partNumber;
//        writeFile(outFile, tmp);
//    }
//    for (int i = 0; i < 96; ++i) {
//        memset(partNumber, 0, 100);
//        if (code[i] % 10 == 0) {
//            sprintf(partNumber, "RC%sFR-07%dRL", footprint, code[i] / 10);
//        } else {
//            sprintf(partNumber, "RC%sFR-07%dR%dL", footprint, code[i]/ 10, code[i] % 10);
//        }
//        string tmp = partNumber;
//        writeFile(outFile, tmp);
//    }
//    for (int i = 0; i < 96; ++i) {
//        memset(partNumber, 0, 100);
//        sprintf(partNumber, "RC%sFR-07%dRL", footprint, code[i]);
//        string tmp = partNumber;
//        writeFile(outFile, tmp);
//    }
    for (int i = 0; i < sizeof(code) / sizeof(uint16_t); ++i) {
        cout << generatePartNumberString(code[i], -2, precision, footprint) << endl;
        cout << generatePartNumberString(code[i], -1, precision, footprint) << endl;
        cout << generatePartNumberString(code[i], 0, precision, footprint) << endl;
        cout << generatePartNumberString(code[i], 1, precision, footprint) << endl;
        cout << generatePartNumberString(code[i], 2, precision, footprint) << endl;
        cout << generatePartNumberString(code[i], 3, precision, footprint) << endl;
        cout << generatePartNumberString(code[i], 4, precision, footprint) << endl;
        cout << generatePartNumberString(code[i], 5, precision, footprint) << endl;
    }
    outFile.close();
    return 0;
}

string convertResString(uint16_t value, int pow) {
    string str = to_string(value);
    switch (pow) {
        case -2:
            str.insert(1,"R");
            break;
        case -1:
            str.insert(2,"R");
            break;
        case 0:
            str.insert(3,"R");
            break;
        case 1:
            str.insert(1,"K");
            break;
        case 2:
            str.insert(2,"K");
            break;
        case 3:
            str.insert(3,"K");
            break;
        case 4:
            str.insert(1,"M");
            break;
        case 5:
            str.insert(2,"M");
            break;
    }

    while (str[str.length() - 1] == '0')
    {
        str.erase(str.length() -1);
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

void writeFile(ofstream &outFile, string &partNumber) {
//    cout << partNumber.substr(6,1);
    string footprint = partNumber.substr(2, 4);
    string precision = partNumber.substr(6, 1);
    if (precision == "B") {
        precision = "±0.1%";
    } else if (precision == "D") {
        precision = "±0.5%";
    } else if (precision == "F") {
        precision = "±1%";
    } else if (precision == "J") {
        precision = "±5%";
    }
    string unit = "";
    string code = "";
    string value = partNumber.substr(11);
    value.replace(value.find("L"), 1, "");
    if (value.find("R") != string::npos) {
        code = value;
        value.replace(value.find("R"), 1, ".");
        while (value.size() != 4) {
            value.append("0");
            code.append("0");
        }
        if (code.find("R") == 3) {
            code[3] = '0';
            value.replace(3, 1, "");
        }
        unit = "Ω";
    } else if (value.find("K") != string::npos) {
        value.replace(value.find("K"), 1, ".");
        unit = "KΩ";
    } else if (value.find("M") != string::npos) {
        value.replace(value.find("M"), 1, ".");
        unit = "MΩ";
    }
//    cout << code << " "<<value << unit <<endl;
    string description = footprint;
    description = description + " " + value + unit + "(" + code + ")" + precision;
//    cout << description <<endl;
    outFile << "Resistor,," << description << "," << description << "," << description << ",";
    outFile << value << unit << precision << ",'" << footprint << "," << "RES,\\lib\\lib.Schlib,";
    outFile << "r" << footprint << "," << "\\lib\\r" << footprint << ".pcblib,YAGEO(国巨)," << partNumber;
    outFile << "\n";

}