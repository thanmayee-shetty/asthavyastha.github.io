#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

void trim(string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    str = str.substr(first, (last - first + 1));
}

void loadFarmersData(const string& filename, unordered_map<string, string>& farmersMap) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name, data;
        getline(ss, name, ':');
        getline(ss, data);
        trim(name);
        trim(data);
        farmersMap[name] = data;
    }
    file.close();
}

void getFarmerInfo(const unordered_map<string, string>& farmersMap, const string& name) {
    auto it = farmersMap.find(name);
    if (it != farmersMap.end()) {
        cout << name << ": " << it->second << endl;
    } else {
        cout << "Farmer not found!" << endl;
    }
}

int main() {
    unordered_map<string, string> farmersMap;
    string filename = "farmers_data.txt";
    loadFarmersData(filename, farmersMap);
    
    string name;
    cout << "Enter the farmer's name: ";
    getline(cin, name);
    trim(name);
    
    getFarmerInfo(farmersMap, name);
    
    return 0;
}