#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Room {
    string type;
    int capacity;
    bool isAvailable;
};

void showAvailableRooms(const vector<Room>& rooms) {
    cout << "\nAvailable Rooms:" << endl;
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].isAvailable) {
            cout << i + 1 << ". " << rooms[i].type << " (Capacity: " << rooms[i].capacity << ")" << endl;
        }
    }
}

void bookRoom(vector<Room>& rooms, int choice) {
    if (choice >= 1 && choice <= rooms.size() && rooms[choice - 1].isAvailable) {
        rooms[choice - 1].isAvailable = false;
        cout << "\nRoom " << rooms[choice - 1].type << " has been booked successfully!\n";
    } else {
        cout << "\nInvalid choice or room not available!\n";
    }
}

int main() {
    vector<Room> rooms = {
        {"Small Room", 5, true},
        {"Medium Room", 10, true},
        {"Large Room", 20, true}
    };

    int people;
    cout << "Enter number of people for booking: ";
    cin >> people;

    cout << "\nRooms available for " << people << " people:";
    vector<int> validChoices;
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].isAvailable && people <= rooms[i].capacity) {
            validChoices.push_back(i + 1);
        }
    }

    if (validChoices.empty()) {
        cout << "\nNo rooms available for the given number of people.\n";
        return 0;
    }

    showAvailableRooms(rooms);
    
    int choice;
    cout << "\nSelect a room by entering the corresponding number: ";
    cin >> choice;
    bookRoom(rooms, choice);
    
    return 0;
}
