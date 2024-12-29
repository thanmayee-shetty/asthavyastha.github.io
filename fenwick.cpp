#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

class FenwickTree {
public:
    FenwickTree(int size) : n(size) {
        bit.assign(size + 1, 0);
    }

    void update(int x, int delta) {
        for (int i = x; i <= n; i += (i & -i)) {
            bit[i] += delta;
        }
    }

    int query(int x) {
        int sum = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            sum += bit[i];
        }
        return sum;
    }

private:
    vector<int> bit;
    int n;
};

struct FarmerProduce {
    string produceName;
    FenwickTree* fenwick;
    map<int, int> produceData;
};

map<string, map<string, FarmerProduce>> farmerData;

void loadFarmerDataFromFile(const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string farmerName;
        getline(ss, farmerName, ':');

        string produceInfo;
        map<string, FarmerProduce> produceMap;

        while (getline(ss, produceInfo, ',')) {
            produceInfo.erase(remove_if(produceInfo.begin(), produceInfo.end(), ::isspace), produceInfo.end());

            size_t startPos = produceInfo.find('(');
            size_t endPos = produceInfo.find(')');
            if (startPos != string::npos && endPos != string::npos) {
                string name = produceInfo.substr(0, startPos);
                int quantity = stoi(produceInfo.substr(startPos + 1, endPos - startPos - 1));

                if (produceMap.find(name) == produceMap.end()) {
                    produceMap[name] = {name, new FenwickTree(100)};
                }
                produceMap[name].fenwick->update(1, quantity);
            }
        }
        farmerData[farmerName] = produceMap;
    }
}

void displayFarmerProduce(const string& farmerName) {
    if (farmerData.find(farmerName) != farmerData.end()) {
        cout << "Farmer: " << farmerName << endl;
        for (const auto& produceEntry : farmerData[farmerName]) {
            const string& produceName = produceEntry.first;
            int totalQuantity = produceEntry.second.fenwick->query(100);
            cout << produceName << " (" << totalQuantity << ")\n";
        }
    } else {
        cout << "Farmer not found!" << endl;
    }
}

int main() {
    string filename = "farmer.txt";
    loadFarmerDataFromFile(filename);

    string farmerName;
    cout << "Enter the farmer's name: ";
    getline(cin, farmerName);

    displayFarmerProduce(farmerName);

    cout << "Updating Apples for JohnDoe by +3..." << endl;
    farmerData["JohnDoe"]["Apples"].fenwick->update(1, 3);
    displayFarmerProduce("JohnDoe");

    return 0;
}