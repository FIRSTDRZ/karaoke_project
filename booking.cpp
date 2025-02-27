#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>
using namespace std;

const int SMALL_ROOM_COST = 80;
const int MEDIUM_ROOM_COST = 120;
const int LARGE_ROOM_COST = 200;
const int SMALL_ROOM_CAPACITY = 4;
const int MEDIUM_ROOM_CAPACITY = 8;
const int LARGE_ROOM_CAPACITY = 12;

class BookingManager {
public:
    struct Booking {
        string name;
        string roomType;
        int hours;
        time_t bookingTime;
        string bookingCode;
    };

    void bookRoom(string name, string roomType, int hours, bool isMember) {
        time_t now = time(0);
        tm *localTime = localtime(&now);
        //localTime->tm_hour -= 2;
        now = mktime(localTime);
        time_t checkoutTime = now + (hours * 3600);

        string code = generateBookingCode(roomType);
        int price = calculatePrice(roomType, hours, isMember);

        saveBooking(name, roomType, hours, checkoutTime, code);
        cout << "Booking successful!\nBooking Code: " << code << endl;
        cout << "Checkout Time: " << ctime(&checkoutTime);
        cout << "Total Price: " << price << " Baht" << endl;
    }

private:
    string generateBookingCode(string roomType) {
        ifstream file("booking.txt");
        string line;
        int count = 0;
        while (getline(file, line)) {
            vector<string> data;
            stringstream ss(line);
            string token;
            while (getline(ss, token, ',')) {
                data.push_back(token);
            }
            if (!data.empty() && data[1] == roomType) {
                count++;
            }
        }
        file.close();

        stringstream ss;
        ss << roomType << setw(3) << setfill('0') << (count + 1);
        return ss.str();
    }

    int calculatePrice(string roomType, int hours, bool isMember) {
        int cost = (roomType == "S") ? SMALL_ROOM_COST : (roomType == "M") ? MEDIUM_ROOM_COST : LARGE_ROOM_COST;
        int total = cost * hours;
        return isMember ? total * 0.9 : total;
    }

    void saveBooking(string name, string roomType, int hours, time_t checkoutTime, string code) {
        ofstream file("booking.txt", ios::app);
        
        // Get current time for check-in
        time_t now = time(0);
        tm *checkinTime = localtime(&now);
        stringstream checkinFormatted;
        checkinFormatted << setw(2) << setfill('0') << checkinTime->tm_hour << ":"
                         << setw(2) << setfill('0') << checkinTime->tm_min << ":"
                         << setw(2) << setfill('0') << checkinTime->tm_sec;

        // Format checkout time
        tm *checkoutTimeInfo = localtime(&checkoutTime);
        stringstream checkoutFormatted;
        checkoutFormatted << setw(2) << setfill('0') << checkoutTimeInfo->tm_hour << ":"
                          << setw(2) << setfill('0') << checkoutTimeInfo->tm_min << ":"
                          << setw(2) << setfill('0') << checkoutTimeInfo->tm_sec;

        file << name << "," << roomType << "," << hours << "," 
             << checkinFormatted.str() << "," << checkoutFormatted.str() << "," 
             << code << endl;
        file.close();
    }
    
};

bool checkMembership(const string& name) {
    ifstream file("Member.txt");
    string line;
    
    while (getline(file, line)) {
        vector<string> data;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            data.push_back(token);
        }
        if (!data.empty() && data[0] == name) {
            return true; 
        }
    }
    
    return false; 
}

int main() {
    srand(time(0));
    BookingManager bm;
    string name, roomType;
    int hours, people;
    char confirm;
    
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter number of people: ";
    cin >> people;
    while (people > 15 || people == 0) {   // ต้องรอเชื่อมกับ admin
        cout << "Too much people or No people (can contain )" << endl;
        cout << "Enter number of people: ";
        cin >> people;
    }
    
    cout << "Available room types: ";
    if (people <= SMALL_ROOM_CAPACITY) cout << "S ";
    if (people <= MEDIUM_ROOM_CAPACITY) cout << "M ";
    if (people <= LARGE_ROOM_CAPACITY) cout << "L ";
    cout << endl;
    
    do {
        cout << "Select room type (S/M/L): ";
        cin >> roomType;
        transform(roomType.begin(), roomType.end(), roomType.begin(), ::toupper);
        if ((roomType == "S" && people > SMALL_ROOM_CAPACITY) ||
            (roomType == "M" && people > MEDIUM_ROOM_CAPACITY) ||
            (roomType == "L" && people > LARGE_ROOM_CAPACITY)) {
            cout << "Invalid choice! Room too small for the group. Try again." << endl;
        } else {
            break;
        }
    } while (true);
    
    cout << "Enter hours (limit 3 hours): ";
    double temp_hours;  // ใช้ double เพื่อตรวจจับเลขทศนิยม
    while (!(cin >> temp_hours) || temp_hours > 3 || temp_hours <= 0 || 
           floor(temp_hours) != temp_hours) {  // เช็คว่าเป็นจำนวนเต็มหรือไม่
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (floor(temp_hours) != temp_hours) {
            cout << "Please enter whole numbers only!" << endl;
        } else {
            cout << "Invalid choice! Limit 3 hours. Try again." << endl;
        }
        cout << "Enter hours (limit 3 hours): ";
    }
    hours = static_cast<int>(temp_hours);  // แปลงเป็น int หลังจากตรวจสอบแล้ว
    bool isMember = checkMembership(name);
    cout << "Member status: " << (isMember ? "Yes" : "No") << endl;
    cout << "Confirm booking? (Y/N): ";
    cin >> confirm;
    if (confirm == 'Y' || confirm == 'y') {
        bm.bookRoom(name, roomType, hours, isMember);
    } else {
        cout << "Booking canceled." << endl;
    }
    
    return 0;
}

