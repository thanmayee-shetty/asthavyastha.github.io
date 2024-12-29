#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

struct Produce {
    string name;
    int quantity;
    bool operator<(const Produce &other) const {
        return quantity > other.quantity;
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
            ss >> farmerName;

            string produceName;
            int quantity;
            vector<Produce> produceList;
            while (ss >> produceName) {
                ss.ignore(1);
                ss >> quantity;
                ss.ignore(1);

                Produce p = {produceName, quantity};
                produceList.push_back(p);
            }

            farmerData[farmerName] = produceList;
        }
    }

    void displaySortedProduce(const string &farmerName) {
        if (farmerData.find(farmerName) != farmerData.end()) {
            cout << "Farmer: " << farmerName << endl;
            vector<Produce> produceList = farmerData[farmerName];
            sort(produceList.begin(), produceList.end());

            for (const auto &produce : produceList) {
                cout << produce.name << " (" << produce.quantity << ")\n";
            }
        } else {
            cout << "Farmer not found!" << endl;
        }
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
