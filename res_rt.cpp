#include "stdio.h"
#include "iostream"
#include "fstream"
#include "vector"
#include "map"

using namespace std;

map<string, string> footprintcode2type ={
        {"0402", "C"},
        {"0603", "C"},
        {"0805", "C"},
        {"1206", "A"},
        {"1210", "A"}
};

void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Please input: ./res res.csv" << endl;
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
  int count = 0;
  while (!inFile.eof()) {
    string line;
    getline(inFile, line);
    count++;
    if (line.empty())
    {
      cout << "line is empty, count = " << count << endl;
      continue;
    }
    vector<string> column;
    SplitString(line, column, "\",\"");
    string partNumber = column[3];
    string valueString = column[14];
    vector<string> value;
    SplitString(valueString, value, " ");
    if (value[0].size() == 1) {
      valueString = value[0] + ".00" + value[1];
    } else if (value[0].size() == 2) {
      valueString = value[0] + ".0" + value[1];
    }else if(value[0].size() == 3){
      if (value[0].find(".") == std::string::npos)
      {
        valueString = value[0] + value[1];
      }
      else{
        valueString = value[0] + "0" + value[1];
      }
    } else if (value[0].size() == 4)
    {
      valueString = value[0] + value[1];
    }
    valueString.erase(0, valueString.find_first_not_of(" "));
    string precision = column[15];
    string footprintString = column[22];
    string code = partNumber.substr(11, partNumber.size() - 11 - 1);
//    cout << partNumber << " " << valueString <<precision<< " " << code<<" " << footprintString << endl;
    string  description = footprintString + " " + valueString + "(" + code +")" + precision;
    outFile << "Resistor," << footprintcode2type[footprintString] << ",,";
    outFile << description << "," << description << "," << description << ",";
    outFile << valueString << precision << ",'" << footprintString << ",RES,\\lib\\lib.Schlib,r";
    outFile << footprintString << ",\\lib\\r" << footprintString << ".pcblib,YAGEO,";
    outFile << partNumber << endl;
  }
  cout << "exit" << endl;
  inFile.close();
  outFile.close();
  return 0;
  return 0;
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
