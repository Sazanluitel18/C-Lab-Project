#include <iostream>  //  Library function that allows the program to display messages and get user input
#include <vector>    // Library function that provides the definition to store dynamic arrays that can grow or shrink in size.
#include <stdexcept> // This header file includes standard exceptions like bad argument.
#include <string>    // Library function that provides tools to work with text data

using namespace std; // Use the std namespace to replace std prefixes

class NetworkAccessPoint {
public:
    // Constructor for initializing the access point (turned off initially, no month set)
    NetworkAccessPoint() : state(false), month("") {}

    // Check if the access point is on
    bool isOn() const {
        return state;
    }

    // Confirm the month the access point was turned on, if it's on
    string ConfirmMonth() const {
        return month;
    }

    // Mutator method to turn the access point on and set the month
    void turnOn(const string& month) {
        state = true; // Access point is now on
        this->month = month; // Set the month the access point was turned on
    }

    // Mutator method to turn the access point off and reset the month
    void turnOff() {
        state = false; // Access point is now off
        month = ""; // Reset the month to an empty string
    }

private:
    bool state; // Boolean to store the state (on/off) of the access point
    string month; // Store the month when the access point was turned on
};

class Room {
public:
    // Initialize the room with a given number of access points
    Room(int NumberOfAccessPoints) {
        AccessPoints.resize(NumberOfAccessPoints); // Create a vector of access points for the room
    }

    // Confirm the number of access points in the room
    int ConfirmNumberOfAccessPoints() const {
        return AccessPoints.size();
    }

    // Confirm specific access point by position
    NetworkAccessPoint& ConfirmAccessPoint(int position) {
        if (position < 0 || position >= AccessPoints.size()) {
            throw invalid_argument("Access point does not exist."); // Error if access point position is invalid
        }
        return AccessPoints.at(position); // Return the access point at the specified position
    }

private:
    vector<NetworkAccessPoint> AccessPoints; // Vector to store multiple access points in the room
};

class Floor {
public:
    // Initialize the floor with a given number of rooms, each with access points
    Floor(int NumberRooms, int NumberAccessPointsPerRoom) {
        rooms.resize(NumberRooms, Room(NumberAccessPointsPerRoom)); // Create rooms, each with access points
    }

    // Confirm the number of rooms on the floor
    int ConfirmNumberRooms() const {
        return rooms.size();
    }

    // Confirm a specific room by position
    Room& ConfirmRoom(int position) {
        if (position < 0 || position >= rooms.size()) {
            throw invalid_argument("Room does not exist."); // Error if room position is invalid
        }
        return rooms.at(position); // Return the room at the specified position
    }

private:
    vector<Room> rooms; // Vector to store multiple rooms on the floor
};

class Building {
public:
    // Initialize the building with floors, rooms, and access points
    Building(int NumberFloors, int NumberRoomsPerFloor, int NumAccessPointsPerRoom) {
        floors.resize(NumberFloors, Floor(NumberRoomsPerFloor, NumAccessPointsPerRoom)); // Create floors with rooms and access points
    }

    // Confirm the number of floors in the building
    int ConfirmNumberFloors() const {
        return floors.size();
    }

    // Confirm a specific floor by position
    Floor& ConfirmFloor(int position) {
        if (position < 0 || position >= floors.size()) {
            throw invalid_argument("Floor does not exist."); // Error if floor position is invalid
        }
        return floors.at(position); // Return the floor at the specified position
    }

    // Mutator method to add an additional floor to the building
    void AddFloor(int NumberRooms, int NumberAccessPointsPerRoom) {
        floors.push_back(Floor(NumberRooms, NumberAccessPointsPerRoom)); // Add a new floor with the given number of rooms and access points
    }

private:
    vector<Floor> floors; // Vector to store multiple floors in the building
};

int main() {
    try {
        // Create a building with 6 floors, 4 rooms per floor, and 3 access points per room
        Building building(6, 4, 3);

        // Turn on an access point in room 1, floor 0, and set the month to "January"
        building.ConfirmFloor(0).ConfirmRoom(1).ConfirmAccessPoint(2).turnOn("January");

        // Output the state of the access point and the month it was turned on
        cout << "Floor 0, Room 1, Access Point 2 - State: " 
             << (building.ConfirmFloor(0).ConfirmRoom(1).ConfirmAccessPoint(2).isOn() ? "On" : "Off") 
             << ", Month Turned On: " 
             << building.ConfirmFloor(0).ConfirmRoom(1).ConfirmAccessPoint(2).ConfirmMonth() << endl;

        // Turn on an access point in room 3, floor 2, and set the month to "February"
        building.ConfirmFloor(2).ConfirmRoom(3).ConfirmAccessPoint(1).turnOn("February");

        // Output the state of the access point and the month it was turned on
        cout << "Floor 2, Room 3, Access Point 1 - State: " 
             << (building.ConfirmFloor(2).ConfirmRoom(3).ConfirmAccessPoint(1).isOn() ? "On" : "Off") 
             << ", Month Turned On: " 
             << building.ConfirmFloor(2).ConfirmRoom(3).ConfirmAccessPoint(1).ConfirmMonth() << endl;

        // Turn on an access point in room 0, floor 4, and set the month to "March"
        building.ConfirmFloor(4).ConfirmRoom(0).ConfirmAccessPoint(0).turnOn("March");

        // Output the state of the access point and the month it was turned on
        cout << "Floor 4, Room 0, Access Point 0 - State: " 
             << (building.ConfirmFloor(4).ConfirmRoom(0).ConfirmAccessPoint(0).isOn() ? "On" : "Off") 
             << ", Month Turned On: " 
             << building.ConfirmFloor(4).ConfirmRoom(0).ConfirmAccessPoint(0).ConfirmMonth() << endl;

        // Add another floor to the building with 2 rooms and 3 access points per room
        building.AddFloor(2, 3);

    } catch (const invalid_argument& e) {
        cerr << e.what() << endl; // Handle exceptions if an invalid floor, room, or access point is referenced
    }

    return 0; // Return 0 to indicate the program has finished successfully
}
