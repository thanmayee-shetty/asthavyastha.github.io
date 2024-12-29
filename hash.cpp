#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

struct EmergencyUnit {
    string id; 
    string location;
    bool available;
    vector<string> equipment; 

    EmergencyUnit(string id, string location, bool available, vector<string> equipment) 
        : id(id), location(location), available(available), equipment(equipment) {}
};

class EmergencyDispatch {
private:
    unordered_map<string, EmergencyUnit> units; 

public:
    void addUnit(const EmergencyUnit& unit) {
        units[unit.id] = unit; 
    }

    EmergencyUnit* findUnit(const string& id) {
        if (units.count(id) > 0) {
            return &units[id];
        }
        return nullptr; 
    }

    EmergencyUnit* findClosestAvailableUnit(const string& location, const vector<string>& requiredEquipment) {
        EmergencyUnit* closestUnit = nullptr;
        // Calculate distances to all units (simplified example)
        for (auto& unit : units) {
            if (unit.second.available && 
                includes(unit.second.equipment.begin(), unit.second.equipment.end(), 
                         requiredEquipment.begin(), requiredEquipment.end())) {
                // Simplified distance calculation (replace with actual distance calculation)
                // ...
                if (closestUnit == nullptr || /* Distance to this unit is less than distance to closestUnit */) {
                    closestUnit = &unit.second;
                }
            }
        }
        return closestUnit;
    }
};

int main() {
    EmergencyDispatch dispatch;

    // Create some emergency units
    EmergencyUnit unit1("Ambulance1", "HospitalA", true, {"CPR", "Defibrillator"});
    EmergencyUnit unit2("FireTruck1", "StationB", true, {"Ladder", "Hose"});
    EmergencyUnit unit3("Ambulance2", "HospitalC", true, {"CPR", "Oxygen"});

    dispatch.addUnit(unit1);
    dispatch.addUnit(unit2);
    dispatch.addUnit(unit3);

    // Find the closest available ambulance with CPR and Defibrillator
    vector<string> requiredEquipment = {"CPR", "Defibrillator"};
    EmergencyUnit* closestUnit = dispatch.findClosestAvailableUnit("IncidentLocation", requiredEquipment);

    if (closestUnit != nullptr) {
        cout << "Closest available unit: " << closestUnit->id << endl;
    } else {
        cout << "No suitable unit found." << endl;
    }

    return 0;
}
