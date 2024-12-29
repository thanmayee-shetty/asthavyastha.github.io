#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cctype>
#include <locale>
using namespace std;

struct Produce {
    string name;
    int quantity;
    bool operator<(const Produce &other) const {
        return quantity > other.quantity;  // Sort in descending order of quantity
    }
};

class Farmer {
public:
    map<string, vector<Produce>> farmerData;

    void readFile(const string &filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string farmerName;
            getline(ss, farmerName, ':'); // Read the farmer name until ':'

            farmerName = trim(farmerName);  // Trim any spaces around the name

            string produceName;
            int quantity;
            vector<Produce> produceList;

            // Process the produce data in the line
            while (ss >> produceName) {
                // Ignore the opening parenthesis '('
                size_t startPos = produceName.find('(');
                size_t endPos = produceName.find(')');
                
                // Extract produce name and quantity
                if (startPos != string::npos && endPos != string::npos) {
                    // Extract the produce name (before '(')
                    string name = produceName.substr(0, startPos);
                    // Extract the quantity (inside parentheses)
                    int quantity = stoi(produceName.substr(startPos + 1, endPos - startPos - 1));
                    
                    Produce p = {name, quantity};
                    produceList.push_back(p);
                }
            }

            farmerData[farmerName] = produceList;
        }
    }

    void displaySortedProduce(const string &farmerName) {
        string searchName = farmerName;
        searchName = trim(searchName);  // Trim spaces from input

        if (farmerData.find(searchName) != farmerData.end()) {
            cout << "Farmer: " << searchName << endl;
            vector<Produce> produceList = farmerData[searchName];

            // Sort produce based on quantity (highest to lowest)
            sort(produceList.begin(), produceList.end());

            // Display sorted produce
            for (const auto &produce : produceList) {
                cout << produce.name << " (" << produce.quantity << ")\n";
            }
        } else {
            cout << "Farmer not found!" << endl;
        }
    }

private:
    string trim(const string &str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        if (first == string::npos || last == string::npos)
            return "";
        return str.substr(first, (last - first + 1));
    }
};

int main() {
    Farmer farmer;
    farmer.readFile("farmer.txt");

    string farmerName;
    cout << "Enter the farmer's name: ";
    getline(cin, farmerName);

    farmer.displaySortedProduce(farmerName);

    return 0;
}


