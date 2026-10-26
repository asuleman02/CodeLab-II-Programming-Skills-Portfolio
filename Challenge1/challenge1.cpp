
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// Ask the user how many miles they travelled
double getDistance() {
    double distance;

    while (true) {
        cout << "Enter distance in miles: ";
        cin >> distance;

        if (cin && distance >= 0) {
            return distance;
        }

        cout << "Invalid distance. Please try again." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Ask the user what fuel their car uses
string getFuelType() {
    string fuel;

    while (true) {
        cout << "Enter fuel type (petrol or diesel): ";
        cin >> fuel;

        if (fuel == "petrol" || fuel == "diesel") {
            return fuel;
        }

        cout << "Invalid fuel type. Please try again." << endl;
    }
}

// Work out the CO2 emissions for the journey
double calculateCO2(double distance, string fuel) {
    double fuelUsed = (distance / 100.0) * 9.66;
    double co2 = 0;

    if (fuel == "petrol") {
        co2 = fuelUsed * 2.31;
    }
    else if (fuel == "diesel") {
        co2 = fuelUsed * 2.68;
    }

    return co2;
}

int main() {
    double distance;
    string fuel;
    double result;

    cout << "CO2 Calculator" << endl;

    distance = getDistance();
    fuel = getFuelType();

    result = calculateCO2(distance, fuel);

    cout << fixed << setprecision(2);
    cout << "Total CO2 emissions: " << result << " kg" << endl;

    return 0;
}
