//ต้องแก้ cin เป็น get line และเพิ่มการเรียกใช้งานฟังก์ชัน Membership ใน main 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

// Class to hold member information
class Member {
private:
    string name;
    string password;
    string telephone;

public:
    // Constructor
    Member(string n = "", string p = "", string t = "")
        : name(n), password(p), telephone(t) {}

    // Getters
    string getName() const { return name; }
    string getPassword() const { return password; }
    string getTelephone() const { return telephone; }

    // Setters
    void setName(string n) { name = n; }
    void setPassword(string p) { password = p; }
    void setTelephone(string t) { telephone = t; }

    // Method to display member details
    void display() const {
        cout << "Name: " << name << ", Telephone: " << telephone << endl;
    }
};

// Function to split a string by a delimiter
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to load members from the file
vector<Member> loadMembers() {
    vector<Member> members;
    ifstream file("Member.txt");
    string line;
    while (getline(file, line)) {
        vector<string> data = split(line, ',');
        if (data.size() == 3) {
            members.push_back(Member(data[0], data[1], data[2]));
        }
    }
    file.close();
    return members;
}

// Function to save members to the file
void saveMembers(const vector<Member> &members) {
    ofstream file("Member.txt");
    for (const auto &member : members) {
        file << member.getName() << "," << member.getPassword() << "," << member.getTelephone() << endl;
    }
    file.close();
}

// Function to create a new membership
void new_membership() {
    string name, password, telephone;
    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter your password: ";
    getline(cin, password);
    cout << "Enter your telephone number: ";
    getline(cin, telephone);

    // Load existing members
    vector<Member> members = loadMembers();

    // Check if the member already exists
    for (const auto &member : members) {
        if (member.getName() == name) {
            cout << "Member already exists!" << endl;
            return;
        }
    }

    // Add new member
    members.push_back(Member(name, password, telephone));
    saveMembers(members);
    cout << "New membership created successfully!" << endl;
}

// Function to log in to a membership
void login_membership() {
    string name, password;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;

    // Load existing members
    vector<Member> members = loadMembers();

    // Check if the member exists and the password is correct
    for (const auto &member : members) {
        if (member.getName() == name && member.getPassword() == password) {
            cout << "Login successful! Welcome, " << member.getName() << "!" << endl;
            return;
        }
    }
    cout << "Invalid name or password!" << endl;
}

// Function to edit a membership
void edit_membership() {
    string name, password,newTelephone;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your password: ";
    cin >> password;

    // Load existing members
    vector<Member> members = loadMembers();

    // Find the member and verify the password
    for (auto &member : members) {
        if (member.getName() == name && member.getPassword() == password) {
            cout << "Enter new telephone number: ";
            cin >> newTelephone;
            member.setTelephone(newTelephone);
            saveMembers(members);
            cout << "Membership updated successfully!" << endl;
            return;
        }
    }
    cout << "Invalid name or password!" << endl;
}

int main() {
    while (true) {
        cout << "==========================" << endl;
        cout << "Here are our memberships" << endl;
        cout << "New Membership (1)" << endl;
        cout << "Log in Membership (2)" << endl;
        cout << "Edit Membership (3)" << endl;
        cout << "Exit (4)" << endl;
        cout << "Please choose the service you want to use: ";
        int choice_member;
        cin >> choice_member;

        switch (choice_member) {
            case 1:
                new_membership();
                break;
            case 2:
                login_membership();
                break;
            case 3:
                edit_membership();
                break;
            case 4:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}