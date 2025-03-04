#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<chrono>
#include<thread>
#include<unistd.h>
#include"intro.cpp"
#include"Membership.cpp"
#include"data.cpp"
#include"Cancel_booking.cpp"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include<cmath>

using namespace std;

class KaraokeAdmin {
    public:
        struct RoomSettings {
            int smallRoomCount = 3;
            int mediumRoomCount = 2;
            int largeRoomCount = 1;
            int smallRoomCapacity = 3;
            int mediumRoomCapacity = 5;
            int largeRoomCapacity = 8;
            double smallRoomPrice = 70;
            double mediumRoomPrice = 90;
            double largeRoomPrice = 120;
            int openingHour = 11;
            int closingHour = 20;
        };
    
    private:
        const string ADMIN_PASSWORD = "admin123";
        static RoomSettings defaultSettings; // ตั้งค่าเริ่มต้นของห้อง
        RoomSettings settings;
        bool isLoggedIn = false;
    
    public:
        // ฟังก์ชันสำหรับเริ่มการทำงานของ Admin และคืนค่าการตั้งค่าเมื่อเสร็จสิ้น
        RoomSettings startAdmin() {
            adminMenu();
            return settings;
        }

        bool login() {
            string password;
            cout << "Input Admin Password : ";
            cin >> password;
            isLoggedIn = (password == ADMIN_PASSWORD);
            return isLoggedIn;
        }
        
        void adminMenu() {
            if (!login()) {
                cout << "Incorrect Password\n";
                return;
            }
            int choice;
            do {
                cout << "\n=== Admin Menu ===\n";
                cout << "1. Room Count settings\n";
                cout << "2. Room Capacity settings\n";
                cout << "3. Room Price settings\n";
                cout << "4. Setting open time - close time\n";
                cout << "5. Show All settings\n";
                cout << "0. Log Out Admin Menu\n";
                cout << "Select Menu : ";
                cin >> choice;
                switch(choice) {
                    case 1:
                        setRoomCounts();
                        break;
                    case 2:
                        setRoomCapacities();
                        break;
                    case 3:
                        setRoomPrices();
                        break;
                    case 4:
                        setOperatingHours();
                        break;
                    case 5:
                        displaySettings();
                        break;
                    case 0:
                        cout << "Log Out Admin Menu\n";
                        isLoggedIn = false;
                        break;
                    default:
                        cout << "Incorrect Menu!!! Please New Selected\n";
                }
            } while (choice != 0);
        }
        
        void setRoomCounts() {
            system("cls");
            cout << "\n=== Room Count settings ===\n";
            cout << "Small Room Count : ";
            cin >> settings.smallRoomCount;
            cout << "Medium Room Count : ";
            cin >> settings.mediumRoomCount;
            cout << "Large Room Count : ";
            cin >> settings.largeRoomCount;
        }
        
        void setRoomCapacities() {
            system("cls");
            cout << "\n=== Room Capacity settings ( Number of People ) ===\n";
            cout << "Small Room Capacity : ";
            cin >> settings.smallRoomCapacity;
            cout << "Medium Room Capacity : ";
            cin >> settings.mediumRoomCapacity;
            cout << "Large Room Capacity : ";
            cin >> settings.largeRoomCapacity;
        }
        
        void setRoomPrices() {
            system("cls");
            cout << "\n=== Settings the room rate per hour ===\n";
            cout << "Small Room Price : ";
            cin >> settings.smallRoomPrice;
            cout << "Medium Room Price : ";
            cin >> settings.mediumRoomPrice;
            cout << "Large Room Price : ";
            cin >> settings.largeRoomPrice;
        }
        
        void setOperatingHours() {
            system("cls");
            cout << "\n=== Setting open time - close time ===\n";
            do {
                cout << "Open Time (0-23): ";
                cin >> settings.openingHour;
            } while (settings.openingHour < 0 || settings.openingHour > 23);
            
            do {
                cout << "Close Time (0-23): ";
                cin >> settings.closingHour;
            } while (settings.closingHour < 0 || settings.closingHour > 23 || 
                    settings.closingHour <= settings.openingHour);
        }
        
        void displaySettings() {
            system("cls");
            cout << "\n=== ALl Settings ===\n";
            cout << "Number of rooms :\n";
            cout << "  Small Room : " << settings.smallRoomCount << " room\n";
            cout << "  Mediun Room : " << settings.mediumRoomCount << " room\n";
            cout << "  Large Room : " << settings.largeRoomCount << " room\n";
            
            cout << "\nRoom Capacity :\n";
            cout << "  Small Room : " << settings.smallRoomCapacity << " people\n";
            cout << "  Medium Room : " << settings.mediumRoomCapacity << " people\n";
            cout << "  Large Room : " << settings.largeRoomCapacity << " people\n";
            
            cout << "\nRoom Rate per Hour :\n";
            cout << "  Small Room : " << settings.smallRoomPrice << " Baht\n";
            cout << "  Medium Room : " << settings.mediumRoomPrice << " Baht\n";
            cout << "  Large Room : " << settings.largeRoomPrice << " Baht\n";
            
            cout << "\nOpening hours :\n";
            cout << "  Open : " << settings.openingHour << ":00 \n";
            cout << "  Close : " << settings.closingHour << ":00 \n";
        }
    };
class BookingManager {
private:
    KaraokeAdmin::RoomSettings settings;

public:
    // เพิ่ม constructor ที่รับค่า settings
    BookingManager(const KaraokeAdmin::RoomSettings& adminSettings) : settings(adminSettings) {}

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
        int cost;
        if (roomType == "S") {
            cost = settings.smallRoomPrice;
        } else if (roomType == "M") {
            cost = settings.mediumRoomPrice;
        } else {
            cost = settings.largeRoomPrice;
        }
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

        file << code << "," << roomType << "," << hours << "," 
             << checkinFormatted.str() << "," << checkoutFormatted.str() << "," 
             << name << endl;
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

void Booking_System(KaraokeAdmin::RoomSettings& settings) {  // รับ settings เป็น reference
    srand(time(0));
    BookingManager bm(settings);
    string name, roomType;
    int hours, people;
    char confirm;
    
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter number of people: ";
    cin >> people;
    while (people > settings.largeRoomCapacity || people == 0) {
        cout << "Too much people or No people (can contain )" << endl;
        cout << "Enter number of people: ";
        cin >> people;
    }

    cout << "Suggest room types: ";
    if (people <= settings.smallRoomCapacity) cout << " S " <<"( available " << settings.smallRoomCount <<" )"; 
    if (people <= settings.mediumRoomCapacity) cout << " M "<<"( available " << settings.mediumRoomCount <<" )";
    if (people <= settings.largeRoomCapacity) cout << " L "<<"( available " << settings.largeRoomCount <<" )";
    cout << endl;
    
    do {
        cout << "Select room type (S/M/L): ";
        cin >> roomType;
        transform(roomType.begin(), roomType.end(), roomType.begin(), ::toupper);
        if ((roomType == "S" && people > settings.smallRoomCapacity) ||
            (roomType == "M" && people > settings.mediumRoomCapacity) ||
            (roomType == "L" && people > settings.largeRoomCapacity)) {
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
        bool canBook = false;
        // เช็คเฉพาะประเภทห้องที่ต้องการจอง
        if (roomType == "S" && settings.smallRoomCount > 0) {
            canBook = true;
            settings.smallRoomCount--;
        } else if (roomType == "M" && settings.mediumRoomCount > 0) {
            canBook = true;
            settings.mediumRoomCount--;
        } else if (roomType == "L" && settings.largeRoomCount > 0) {
            canBook = true;
            settings.largeRoomCount--;
        }

        if (canBook) {
            bm.bookRoom(name, roomType, hours, isMember);
        } else {
            cout << "This Room type is fulled , Wait for someone cancel" << endl;
        }
    } else {
        cout << "Booking canceled." << endl;
    }
}

void cancel_member() {
    ifstream inputfile("booking.txt");
    if (!inputfile.is_open()) {
        cerr << "can't open file" << endl;
        return; // จบการทำงานโปรแกรมด้วยรหัสผิดพลาด
    }

    // สร้าง vector เพื่อเก็บรหัสการจองห้อง
    vector<string> bookingcodes;

    // อ่านข้อมูลจากไฟล์ทีละบรรทัด
    string line;
    while (getline(inputfile, line)) {
        // ใช้ stringstream เพื่อแยกข้อมูลในบรรทัด
        stringstream ss(line);
        string firstValue;

        // อ่านค่าแรกก่อนเครื่องหมาย ','
        getline(ss, firstValue, ',');

        // เพิ่มค่าแรกเข้าไปใน vector
        bookingcodes.push_back(firstValue);
    }

    // ปิดไฟล์หลังจากอ่านเสร็จ
    inputfile.close();

    bool validChoice = false;
    while (!validChoice) {
        // รหัสการจองห้องที่ต้องการตรวจสอบ
        string roomBookingCode;
        cout << "Enter the room booking code: ";
        cin >> roomBookingCode;

        // ตรวจสอบว่ารหัสการจองห้องมีอยู่ในรายการหรือไม่
        if (checkRoomBookingCode(roomBookingCode, bookingcodes)) {
            cout << "Room booking code found" << endl;
            cout << "==========================" << endl;

            cout << "Do you want to cancel this booking?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No" << endl;
            cout << "Please select (1-2): ";

            int choice_cancel;
            cin >> choice_cancel;

            if (choice_cancel == 1) {
                // เรียกใช้ฟังก์ชันลบบรรทัด
                deleteBookingLine(roomBookingCode);
                cout << "cancel completed";
                validChoice = true;
            } else if (choice_cancel == 2) {
                cout << "Operation cancelled" << endl;
                validChoice = false;
            } else {
                cout << "Invalid choice. Please try again." << endl;
                validChoice = false;
            }
        } else {
            cout << "Room booking code not found" << endl;
        }
    }
}

int adminoruser() {
    system("cls");
    int user_type = 0;
    
    while (true) {
        cout << "==========================" << endl;
        cout << "Are you an Admin or a User ?? " << endl;
        cout << "Admin(1)" << " " << "User(2)" <<" "<<"Log out (3)"<< endl;
        cout << "Please choose the type of user you are: ";
        cin >> user_type;
        
        if (user_type == 1 || user_type == 2 || user_type == 3) {
            return user_type;
        }
        system("cls");
        cout << "Invalid input" << endl;
    }
}

int clear_booking() {
    ofstream file("booking.txt", ios::trunc); // เปิดไฟล์และลบข้อมูล
    if (file.is_open()) {
        system("cls");
        cout << "Preparing data....\n";
        sleep(1);
        file.close();
    } else {
        cerr << "Error\n";
    }
    return 0;
}

int main() {

    clear_booking();
    system("cls");
    intro();
    KaraokeAdmin admin;
    KaraokeAdmin::RoomSettings settings;
    int defult_small = 0;
    int defult_medium = 0;
    int defult_large = 0;
    
    bool running = true;
    while(running) {
        int userType = adminoruser();
        
        if (userType == 1) {
            settings = admin.startAdmin();
            defult_small = settings.smallRoomCount;
            defult_medium = settings.mediumRoomCount;
            defult_large = settings.largeRoomCount;
        }
        else if (userType == 2) {
            bool userMenuRunning = true;
            while (userMenuRunning) {
                system("cls");
                cout << "==========================" << endl;
                cout << "      Welcome User    " << endl;
                cout << "==========================" << endl;
                cout << "1. Membership Services" << endl;
                cout << "2. View Room Information" << endl;
                cout << "3. Book Room" << endl;
                cout << "4. Cancel Booking" << endl;
                cout << "5. Checking Queue" << endl;
                cout << "6. Exit" << endl;
                cout << "Please select an option: ";
                int choice;
                cin >> choice; 
                
                if (choice == 1) {
                    bool check = true;
                    while (check) {
                        cout << "==========================" << endl;
                        cout << "Here are our service\n";
                        cout << "New Memberships (1)" << endl;
                        cout << "Login Memberships (2)" << endl;
                        cout << "Edit Memberships (3)" << endl;
                        cout << "Exit (4)" << endl;
                        cout << "Please choose the service you want to use: ";
                        int choice_member;
                        cin >> choice_member;    
                        
                        if (choice_member == 1) {
                            new_membership();
                        }
                        else if (choice_member == 2) {
                            login_membership();
                        }
                        else if (choice_member == 3) {
                            edit_membership();
                        }
                        else if (choice_member == 4) {
                            user();
                            check = false;
                        }
                        else {
                            cout << "Invalid choice! Please try again." << endl;
                        }
                    }
                }
                
                else if (choice == 2) {
                    system("cls");
                    bool viewRoomInfo = true;
                    while (viewRoomInfo) {
                        system("cls");
                        viewRoom();
                        int choice_room;
                        bool validInput = false;
                        do {
                            cout << "\nEnter your choice (1-3) : ";
                            cin >> choice_room;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                system("cls");
                                cout << "Invalid input. Please enter a number between 1-3" << endl;
                                sleep(2);
                                system("cls");
                                viewRoom();

                            } else if (choice_room >= 1 && choice_room <= 3) {
                                validInput = true;
                            } else {
                                system("cls");
                                cout << "Please enter a number between 1-3" << endl;
                                sleep(2);
                                system("cls");
                                viewRoom();
                            }
                            
                        } while (!validInput);

                        switch (choice_room) {
                            case 1:
                                system("cls");
                                cout << "Small Room Information"<< endl;
                                cout << "Total Rooms: " << defult_small<< endl;
                                cout << "Vacant Rooms: " << settings.smallRoomCount<< endl;
                                cout << "==========================" << endl;
                                cout << "Price: " << settings.smallRoomPrice << " Baht per hour" << endl;
                                cout << "Capacity: " << settings.smallRoomCapacity << " people" << endl;
                                break;
                            case 2:
                                system("cls");
                                cout << "Medium Room Information" << endl;
                                cout << "Total Rooms: " << defult_medium<< endl;
                                cout << "Vacant Rooms: " << settings.mediumRoomCount<< endl;
                                cout << "==========================" << endl;
                                cout << "Price: " << settings.mediumRoomPrice << " Baht per hour" << endl;
                                cout << "Capacity: " << settings.mediumRoomCapacity << " people" << endl;
                                break;
                            case 3:
                                system("cls");
                                cout << "Large Room Information"<< endl;
                                cout << "Total Rooms: " << defult_large<< endl;
                                cout << "Vacant Rooms: " << settings.largeRoomCount << endl;
                                cout << "==========================" << endl;
                                cout << "Price: " << settings.largeRoomPrice << " Baht per hour" << endl;
                                cout << "Capacity: " << settings.largeRoomCapacity << " people" << endl;
                                break;
                        }
                        continueviewRoom();
                        int continueChoice;
                        bool validContinueChoice = false;
                        do {
                            cout << "\nEnter your choice (1-2): ";
                            cin >> continueChoice;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                system("cls");
                                cout << "Invalid input. Please enter 1 or 2." << endl;
                                sleep(2);
                                system("cls");
                                continueviewRoom();
                            } else if (continueChoice == 1 || continueChoice == 2) {
                                validContinueChoice = true;
                                if (continueChoice == 2) {
                                    viewRoomInfo = false;
                                }
                            } else {
                                system("cls");
                                cout << "Please enter either 1 or 2." << endl;
                                sleep(2);
                                system("cls");
                                continueviewRoom();
                            }
                        } while (!validContinueChoice);
                    }
                }
                
                else if (choice == 3){
                    system("cls");
                    bool bookingMenu = true;
                    while (bookingMenu) {
                        cout << "==========================" << endl;
                        cout << "Here are our booking" << endl;
                        cout << "==========================" << endl;
                        cout << "Booking (1)" << endl;
                        cout << "Exit (2)"<< endl;
                        int choice_book;
                        cout << "Please choose the service you want to use: ";
                        cin >> choice_book;
                        
                        if (choice_book == 1){
                            system("cls");
                            Booking_System(settings);
                        }
                        else if (choice_book == 2){
                            bookingMenu = false;
                        }
                        else {
                            cout << "Invalid option! Please try again." << endl;
                        }
                        
                    }
                }
                else if (choice == 4) {
                    system("cls");
                    cancel_member();
                }
                else if (choice == 5) {
                    system("cls");
                    bool checkingQueue = true;
                    while (checkingQueue) {
                        system("cls");
                        viewQueue();
                        int choice_room;
                        bool validInput = false;
                        do {
                            cout << "Enter your choice (1-3) : ";
                            cin >> choice_room;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "Invalid input. Please enter a number between 1-3" << endl;
                            } else if (choice_room >= 1 && choice_room <= 3) {
                                validInput = true;
                            } else {
                                system("cls");
                                cout << "Please enter a number between 1-3" << endl;
                                sleep(2);
                                system("cls");
                                viewQueue();
                            }
                        } while (!validInput);

                        ifstream file("booking.txt");
                        string line;
                        switch (choice_room) {
                            case 1:
                                system("cls");
                                if (!file) {
                                    cerr << "Unable to open file!" << endl;
                                    return 1; // Exit the program if the file cannot be opened
                                }
                                while (getline(file, line)) {
                                    // Find the first non-space or non-tab character
                                    size_t first_char = line.find_first_not_of(" \t");
                                    // Check if the line starts with 'S' or 's'
                                    if (first_char != string::npos && (line[first_char] == 'S' || line[first_char] == 's')) {
                                        cout << line << endl; // Display the line that starts with 'S' or 's'
                                    }
                                }
                                file.close(); 
                                break;
                            case 2:
                                system("cls");
                                if (!file) {
                                    cerr << "Unable to open file!" << endl;
                                    return 1; // Exit the program if the file cannot be opened
                                }
                                while (getline(file, line)) {
                                    size_t first_char = line.find_first_not_of(" \t");
                                    if (first_char != string::npos && (line[first_char] == 'M' || line[first_char] == 'm')) {
                                        cout << line << endl; 
                                    }
                                }
                                file.close(); 
                                break;

                            case 3:
                                system("cls");
                                if (!file) {
                                    cerr << "Unable to open file!" << endl;
                                    return 1; // Exit the program if the file cannot be opened
                                }
                                while (getline(file, line)) {
                                    size_t first_char = line.find_first_not_of(" \t");
                                    if (first_char != string::npos && (line[first_char] == 'L' || line[first_char] == 'l')) {
                                        cout << line << endl; 
                                    }
                                }
                                file.close(); 
                                break;
                        }
                        // Add the logic for checking the queue here
                        cout << "=====================================" << endl;
                        cout << "Do you want to check the queue again?" << endl;
                        cout << "(Yes = 1 | No = 0): ";
                        int checkAgain;
                        bool validCheckAgain = false;
                        do {
                            cin >> checkAgain;
                            if (cin.fail() || (checkAgain != 0 && checkAgain != 1)) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                system("cls");
                                cout << "Invalid input! Please enter 1 or 0: "<< endl;
                                cout << "=====================================" << endl;
                                cout << "Do you want to check the queue again?" << endl;
                                cout << "(Yes = 1 | No = 0): ";
                                sleep(2);
                            } else {
                                validCheckAgain = true;
                            }
                        } while (!validCheckAgain);

                        if (checkAgain == 0) {
                            checkingQueue = false;
                        }
                    }
                }
                else if (choice == 6) {
                    userMenuRunning = false;
                }
                else {
                    cout << "Invalid option! Please try again." << endl;
                }
            }
        }
        else if (userType == 3) {
            system("cls");
            cout<<"Thank you for using the Room Booking System. Goodbye!"<<endl;
            running = false;
        }
    }
    return 0;
}