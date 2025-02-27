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
#include"booking.cpp"
#include"data.cpp"

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

int main() {
    system("cls");
    intro();
    KaraokeAdmin admin;
    KaraokeAdmin::RoomSettings settings;
    int defult_small = settings.smallRoomCount;
    int defult_medium = settings.mediumRoomCount;
    int defult_large = settings.largeRoomCount;
    
    bool running = true;
    while(running) {
        int userType = adminoruser();
        
        if (userType == 1) {
            settings = admin.startAdmin();
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
                
                if (choice == 2) {
                    system("cls");
                    bool viewRoomInfo = true;
                    while (viewRoomInfo) {
                        system("cls");
                        viewRoom();
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
                                cout << "Please enter a number between 1-3" << endl;
                            }
                            
                        } while (!validInput);

                        switch (choice_room) {
                            case 1:
                                system("cls");
                                cout << "Small Room Information"<< endl;
                                cout << "Total Rooms: " << defult_small<< endl;
                                cout << "Vacant Rooms: " << settings.smallRoomCount<< endl;
                                break;
                            case 2:
                                system("cls");
                                cout << "Medium Room Information" << endl;
                                cout << "Total Rooms: " << defult_medium<< endl;
                                cout << "Vacant Rooms: " << settings.mediumRoomCount<< endl;
                                break;
                            case 3:
                                system("cls");
                                cout << "Large Room Information"<< endl;
                                cout << "Total Rooms: " << defult_large<< endl;
                                cout << "Vacant Rooms: " << settings.largeRoomCount << endl;
                                break;
                        }
                        continueviewRoom();
                        int continueChoice;
                        bool validContinueChoice = false;
                        do {
                            cout << "Enter your choice (1-2): ";
                            cin >> continueChoice;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                cout << "Invalid input. Please enter 1 or 2." << endl;
                            } else if (continueChoice == 1 || continueChoice == 2) {
                                validContinueChoice = true;
                                if (continueChoice == 2) {
                                    viewRoomInfo = false;
                                }
                            } else {
                                cout << "Please enter either 1 or 2." << endl;
                            }
                        } while (!validContinueChoice);
                    }
                }
                else if (choice == 1) {
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
                else if (choice == 6) {
                    userMenuRunning = false;
                }
                else if (choice == 3){
                    bool bookingMenu = true;
                    while (bookingMenu) {
                        system("cls");
                        cout << "==========================" << endl;
                        cout << "Here are our booking" << endl;
                        cout << "Booking (1)" << endl;
                        cout << "Exit (2)"<< endl;
                        int choice_book;
                        cout << "Please choose the service you want to use: ";
                        cin >> choice_book;
                        
                        if (choice_book == 1){
                            system("cls");
                            bookRoom();
                        }
                        else if (choice_book == 2){
                            bookingMenu = false;
                        }
                        else {
                            cout << "Invalid option! Please try again." << endl;
                        }
                        
                    }
                }
                else if (choice == 5) {
                    bool checkingQueue = true;
                    while (checkingQueue) {
                        cout << "Checking Queue..." << endl;
                        // Add the logic for checking the queue here
                        cout << "Do you want to check the queue again?"<< endl;
                        cout << "(Yes = 1 | No = 0): ";
                        int checkAgain;
                        cin >> checkAgain;
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
