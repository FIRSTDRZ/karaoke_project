#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Membership.cpp"
using namespace std;

// User struct to store user information
struct User {
    string username;
    string password;
    bool isAdmin;
};

// Room struct with expanded properties
struct Room {
    string type;
    int capacity;
    bool isAvailable;
    double price;
    string bookedBy;
};

// Booking struct to track bookings
struct Booking {
    int roomId;
    string username;
    string date;
};

// Global variables
vector<User> users;
vector<Room> rooms;
vector<Booking> bookings;
User* currentUser = nullptr;

// Function to initialize sample data
void initializeData() {
    // Add sample users (including admin)
    users.push_back({"admin", "admin123", true});
    users.push_back({"user1", "pass123", false});
    users.push_back({"user2", "pass456", false});
    
    
    
    // Add sample rooms
    rooms.push_back({"Small Conference Room", 5, true, 50.0, ""});
    rooms.push_back({"Medium Conference Room", 10, true, 100.0, ""});
    rooms.push_back({"Large Conference Room", 20, true, 200.0, ""});
    rooms.push_back({"Executive Meeting Room", 8, true, 150.0, ""});
    rooms.push_back({"Training Room", 30, true, 250.0, ""});
}

// User Authentication
bool login() {
    string username, password;
    cout << "\n===== LOGIN =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    
    for (auto& user : users) {
        if (user.username == username && user.password == password) {
            currentUser = &user;
            cout << "\nLogin successful! Welcome, " << username << "!\n";
            return true;
        }
    }
    
    cout << "\nInvalid username or password. Please try again.\n";
    return false;
}

// Display main menu based on user type
void displayMainMenu() {
    cout << "\n===== ROOM BOOKING SYSTEM =====\n";
    cout << "1. View Available Rooms\n";
    cout << "2. Book a Room\n";
    cout << "3. View My Bookings\n";
    cout << "4. Cancel Booking\n";
    
    if (currentUser->isAdmin) {
        cout << "5. Add New Room\n";
        cout << "6. View All Bookings\n";
        cout << "7. Add New User\n";
    }
    
    cout << "0. Logout\n";
    cout << "Enter your choice: ";
}

// Show available rooms with filtering by capacity
void showAvailableRooms(int requiredCapacity = 0) {
    cout << "\n===== AVAILABLE ROOMS =====\n";
    bool roomsFound = false;
    
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].isAvailable && (requiredCapacity == 0 || rooms[i].capacity >= requiredCapacity)) {
            cout << i + 1 << ". " << rooms[i].type 
                 << " (Capacity: " << rooms[i].capacity 
                 << ", Price: $" << rooms[i].price << ")\n";
            roomsFound = true;
        }
    }
    
    if (!roomsFound) {
        cout << "No rooms available matching your criteria.\n";
    }
}

// Book a room
void bookRoom() {
    int people;
    string date;
    
    cout << "\n===== BOOK A ROOM =====\n";
    cout << "Enter number of people: ";
    cin >> people;
    
    if (people <= 0) {
        cout << "Invalid number of people.\n";
        return;
    }
    
    cout << "Enter booking date (DD/MM/YYYY): ";
    cin >> date;
    
    // Show rooms that can accommodate the requested number of people
    cout << "\nRooms available for " << people << " people:\n";
    bool availableRoomsExist = false;
    
    for (size_t i = 0; i < rooms.size(); ++i) {
        if (rooms[i].isAvailable && rooms[i].capacity >= people) {
            cout << i + 1 << ". " << rooms[i].type 
                 << " (Capacity: " << rooms[i].capacity 
                 << ", Price: $" << rooms[i].price << ")\n";
            availableRoomsExist = true;
        }
    }
    
    if (!availableRoomsExist) {
        cout << "No rooms available for the given number of people.\n";
        return;
    }
    
    int choice;
    cout << "\nSelect a room by entering the corresponding number (0 to cancel): ";
    cin >> choice;
    
    if (choice == 0) {
        cout << "Booking cancelled.\n";
        return;
    }
    
    if (choice >= 1 && choice <= rooms.size() && rooms[choice - 1].isAvailable && rooms[choice - 1].capacity >= people) {
        rooms[choice - 1].isAvailable = false;
        rooms[choice - 1].bookedBy = currentUser->username;
        
        // Add to bookings
        Booking newBooking = {choice - 1, currentUser->username, date};
        bookings.push_back(newBooking);
        
        cout << "\nRoom '" << rooms[choice - 1].type << "' has been booked successfully for " << date << "!\n";
    } else {
        cout << "\nInvalid choice or room not available!\n";
    }
}

// View user's bookings
void viewMyBookings() {
    cout << "\n===== MY BOOKINGS =====\n";
    bool hasBookings = false;
    
    for (size_t i = 0; i < bookings.size(); ++i) {
        if (bookings[i].username == currentUser->username) {
            int roomId = bookings[i].roomId;
            cout << i + 1 << ". Room: " << rooms[roomId].type 
                 << " (Date: " << bookings[i].date << ")\n";
            hasBookings = true;
        }
    }
    
    if (!hasBookings) {
        cout << "You have no current bookings.\n";
    }
}

// View all bookings (admin only)
void viewAllBookings() {
    if (!currentUser->isAdmin) {
        cout << "Access denied. Admin privileges required.\n";
        return;
    }
    
    cout << "\n===== ALL BOOKINGS =====\n";
    if (bookings.empty()) {
        cout << "No bookings in the system.\n";
        return;
    }
    
    for (size_t i = 0; i < bookings.size(); ++i) {
        int roomId = bookings[i].roomId;
        cout << i + 1 << ". Room: " << rooms[roomId].type 
             << " (Booked by: " << bookings[i].username 
             << ", Date: " << bookings[i].date << ")\n";
    }
}

// Cancel a booking
void cancelBooking() {
    cout << "\n===== CANCEL BOOKING =====\n";
    
    // Show user's bookings
    vector<int> userBookingIndices;
    for (size_t i = 0; i < bookings.size(); ++i) {
        if (bookings[i].username == currentUser->username) {
            int roomId = bookings[i].roomId;
            cout << userBookingIndices.size() + 1 << ". Room: " << rooms[roomId].type 
                 << " (Date: " << bookings[i].date << ")\n";
            userBookingIndices.push_back(i);
        }
    }
    
    if (userBookingIndices.empty()) {
        cout << "You have no bookings to cancel.\n";
        return;
    }
    
    int choice;
    cout << "\nSelect booking to cancel (0 to go back): ";
    cin >> choice;
    
    if (choice == 0) {
        return;
    }
    
    if (choice >= 1 && choice <= userBookingIndices.size()) {
        int bookingIndex = userBookingIndices[choice - 1];
        int roomId = bookings[bookingIndex].roomId;
        
        // Free up the room
        rooms[roomId].isAvailable = true;
        rooms[roomId].bookedBy = "";
        
        // Remove booking
        string roomType = rooms[roomId].type;
        bookings.erase(bookings.begin() + bookingIndex);
        
        cout << "Booking for room '" << roomType << "' has been cancelled successfully.\n";
    } else {
        cout << "Invalid choice.\n";
    }
}

// Add a new room (admin only)
void addNewRoom() {
    if (!currentUser->isAdmin) {
        cout << "Access denied. Admin privileges required.\n";
        return;
    }
    
    Room newRoom;
    cout << "\n===== ADD NEW ROOM =====\n";
    
    cin.ignore();
    cout << "Enter room type: ";
    getline(cin, newRoom.type);
    
    cout << "Enter room capacity: ";
    cin >> newRoom.capacity;
    
    cout << "Enter room price: $";
    cin >> newRoom.price;
    
    newRoom.isAvailable = true;
    newRoom.bookedBy = "";
    
    rooms.push_back(newRoom);
    cout << "New room '" << newRoom.type << "' added successfully!\n";
}

// Add a new user (admin only)
void addNewUser() {
    if (!currentUser->isAdmin) {
        cout << "Access denied. Admin privileges required.\n";
        return;
    }
    
    User newUser;
    cout << "\n===== ADD NEW USER =====\n";
    
    cout << "Enter username: ";
    cin >> newUser.username;
    
    // Check if username already exists
    for (const auto& user : users) {
        if (user.username == newUser.username) {
            cout << "Username already exists. Please choose another one.\n";
            return;
        }
    }
    
    cout << "Enter password: ";
    cin >> newUser.password;
    
    char adminChoice;
    cout << "Give admin privileges? (y/n): ";
    cin >> adminChoice;
    newUser.isAdmin = (adminChoice == 'y' || adminChoice == 'Y');
    
    users.push_back(newUser);
    cout << "New user '" << newUser.username << "' added successfully!\n";
}

// Main program function
int main() {
    // Initialize sample data
    initializeData();
    
    bool running = true;
    
    while (running) {
        // User authentication
        if (!currentUser) {
            char choice;
            cout << "\n===== WELCOME TO THE ROOM BOOKING SYSTEM =====\n";
            cout << "L - Login\n";
            cout << "Q - Quit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            
            switch (toupper(choice)) {
                case 'L':
                    if (!login()) {
                        continue;
                    }
                    break;
                case 'Q':
                    running = false;
                    cout << "Thank you for using the Room Booking System. Goodbye!\n";
                    continue;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    continue;
            }
        }
        
        // Main menu
        int menuChoice;
        displayMainMenu();
        cin >> menuChoice;
        
        switch (menuChoice) {
            case 0: // Logout
                cout << "Logging out...\n";
                currentUser = nullptr;
                break;
                
            case 1: // View Available Rooms
                showAvailableRooms();
                break;
                
            case 2: // Book a Room
                bookRoom();
                break;
                
            case 3: // View My Bookings
                viewMyBookings();
                break;
                
            case 4: // Cancel Booking
                cancelBooking();
                break;
                
            case 5: // Add New Room (Admin only)
                if (currentUser->isAdmin) {
                    addNewRoom();
                } else {
                    cout << "Invalid option. Please try again.\n";
                }
                break;
                
            case 6: // View All Bookings (Admin only)
                if (currentUser->isAdmin) {
                    viewAllBookings();
                } else {
                    cout << "Invalid option. Please try again.\n";
                }
                break;
                
            case 7: // Add New User (Admin only)
                if (currentUser->isAdmin) {
                    addNewUser();
                } else {
                    cout << "Invalid option. Please try again.\n";
                }
                break;
                
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    }
    
    return 0;
}