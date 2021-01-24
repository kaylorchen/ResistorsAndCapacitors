//
// Created by kaylor on 2021/1/23.
//
#include "stdio.h"
#include "iostream"
#include "fstream"
#include "vector"
#include "map"
#include "string"
#include "sstream"

using namespace std;
map<string, string> precisionTOchar = {
        {"5%",  "J"},
        {"10%", "K"},
        {"20%", "M"}
};

map<string, string> charTOprecision = {
        {"J", "5%"},
        {"K", "10%"},
        {"M", "20%"}
};
map<string, string> voltageTOdigit = {
        {"6.3V", "5"},
        {"10V",  "6"},
        {"16V",  "7"},
        {"25V",  "8"},
        {"50V",  "9"}
};
map<string, string> digitTOvoltage = {
        {"5", "6.3V"},
        {"6", "10V"},
        {"7", "16V"},
        {"8", "25V"},
        {"9", "50V"},
        {"C", "1KV"},
        {"D", "2KV"},
        {"S", "2.5KV"},
        {"E", "3KV"},
        {"Y", "250V"},
        {"0", "100V"},
        {"A", "200V"},
        {"B", "500V"},
        {"Z", "630V"},
        {"G", "35V"}
};

map<string, string> dimensionCode = {
        {"BA", "0201"},
        {"CA", "0402"},
        {"DA", "0603"},
        {"DB", "0603"},
        {"DC", "0603"},
        {"EB", "0805"},
        {"EA", "0805"},
        {"E0", "0805"},
        {"FD", "1206"},
        {"FC", "1206"},
        {"FA", "1206"},
        {"F1", "1206"},
        {"F0", "1206"},
        {"GD", "1210"},
        {"GC", "1210"},
        {"G3", "1210"},
        {"GB", "1210"},
        {"G2", "1210"},
        {"GA", "1210"},
        {"G1", "1210"},
        {"G0", "1210"},
        {"JC", "1812"},
        {"JB", "1812"},
        {"JA", "1812"}
};

struct para {
    string footprint;
    string value;
    string unit;
    string precision;
    string valuecode;
    string voltage;
};

struct para getPara(string partNumber);

void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c);

void writeFile(ofstream &outFile, string partNumber);

template<class Type>
Type stringToNum(const string &str) {
    istringstream iss(str);
    Type num;
    iss >> num;
    return num;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "Please input: ./cc_x7r xxxx.csv" << endl;
        return -1;
    }
    ofstream outFile;
    ifstream inFile;
    string fileName = argv[1];
    cout << fileName << endl;
    outFile.open(fileName.substr(0, fileName.find(".csv")) + "_result.csv", ios::out);
    inFile.open(fileName, ios::in);
    if (!inFile.is_open()) {
        cout << "Open file error!!\n";
        return -1;
    }
    int count;
    while (!inFile.eof()) {
        string line;
        getline(inFile, line);
        vector<string> column;
        SplitString(line, column, "\",\"");
        string partNumber = column[3];
//        struct para part = getPara(partNumber);
//        count++;
//        if (part.precision == "")
//        {
//            cout << count << " " << column[3] << " " << column[15] << " " << column[16] << endl;
//            cout << part.footprint << endl;
//            cout << part.value << part.unit << part.precision << endl;
//            cout << part.voltage << part.valuecode << endl;
//        }

        writeFile(outFile, partNumber);
    }

    inFile.close();
    outFile.close();
    return 0;
}

struct para getPara(string partNumber) {
    struct para part;
    part.valuecode = partNumber.substr(partNumber.length() - 3);
    part.footprint = partNumber.substr(2, 4);
    part.precision = charTOprecision[partNumber.substr(6, 1)];
    part.voltage = digitTOvoltage[partNumber.substr(11, 1)];
    uint64_t tmp = stringToNum<uint64_t>(partNumber.substr(partNumber.length() - 3, 2));
    uint64_t count = stringToNum<uint64_t>(partNumber.substr(partNumber.length() - 1));
    for (int i = 0; i < count; ++i) {
        tmp *= 10;
    }

    if (tmp < 1000) {
        part.value = to_string(tmp);
        part.unit = "pF";
    } else if (tmp < 10000 && tmp >= 1000) {
        part.value = to_string(tmp / 1000.0f).substr(0, 3);
        part.unit = "nF";
    } else if (tmp < 1000000 && tmp >= 10000) {
        part.value = to_string(tmp / 1000);
        part.unit = "nF";
    } else if (tmp < 10000000 && tmp >= 1000000) {
        part.value = to_string(tmp / 1000000.0f).substr(0, 3);
        part.unit = "uF";
    } else if (tmp >= 10000000) {
        part.value = to_string(tmp / 1000000);
        part.unit = "uF";
    }
    return part;
}

void writeFile(ofstream &outFile, string partNumber) {
    struct para part = getPara(partNumber);
    string description = part.footprint + " " + part.value + part.unit + "(" + part.valuecode + ")±"\
 + part.precision + " " + part.voltage;
    string valuestring = part.value + part.unit + " " + part.voltage;
    uint16_t tmp = stringToNum<uint16_t>(part.footprint);
    string type = "A";
    if (tmp <= 805) {
        type = "C";
    }
    outFile << "Capacitor," << type << ",,";
    outFile << description << "," << description << "," << description << ",";
    outFile << valuestring << ",'" << part.footprint << ",CAP,\\lib\\lib.Schlib,C";
    outFile << part.footprint << ",\\lib\\c" << part.footprint << ".pcblib,YAGEO(国巨),";
    outFile << partNumber << endl;
}

void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c) {
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}
