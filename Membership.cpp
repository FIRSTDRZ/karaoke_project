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
    cout << "ชื่อผู้ใช้: ";
    cin.ignore();
    getline(cin, name);
    cout << "รหัสผ่าน: ";
    getline(cin, password);
    cout << "เบอร์โทรศัพท์มือถือ: ";
    getline(cin, telephone);

    // Load existing members
    vector<Member> members = loadMembers();

    // Check if the member already exists
    for (const auto &member : members) {
        if (member.getName() == name) {
            cout << "เป็นสมาชิกอยู่แล้ว!" << endl;
            return;
        }
    }

    // Add new member
    members.push_back(Member(name, password, telephone));
    saveMembers(members);
    cout << "สมัครสมาชิกใหม่สำเร็จ!" << endl;
}

// Function to log in to a membership
void login_membership() {
    string name, password;
    cout << "ชื่อผู้ใช้: ";
    cin.ignore();
    getline(cin, name);
    cout << "รหัสผ่าน: ";
    getline(cin, password);

    // Load existing members
    vector<Member> members = loadMembers();

    // Check if the member exists and the password is correct
    for (const auto &member : members) {
        if (member.getName() == name && member.getPassword() == password) {
            cout << "ล็อคอิน สำเร็จ! ยินดีต้อนรับ, " << member.getName() << "!" << endl;
            return;
        }
    }
    cout << "ชื่อผู้ใช้หรือรหัสผ่านผู้ใช้ผิด!" << endl;
}

// Function to edit a membership
void edit_membership() {     
    string name, password,newTelephone;
    cout << "ชื่อผู้ใช้: ";
    cin.ignore();
    getline(cin, name);
    cout << "รหัสผ่าน: ";
    getline(cin, password);
    // Load existing members
    vector<Member> members = loadMembers();

    // Find the member and verify the password
    for (auto &member : members) {
        if (member.getName() == name && member.getPassword() == password) {
            cout<<"แก้ไขรหัสผ่าน (1) หรือ เบอร์โทรศัพท์มือถือ (2): ";
            int choice;
            cin>>choice;
            if(choice==1){
                cout << "กรอกรหัสผ่านใหม่: ";
                cin >> password;
                member.setPassword(password);
            }
            else if(choice==2){
                cout << "กรอกเบอร์โทรศัพท์มือถือใหม่: ";
                cin >> newTelephone;
                member.setTelephone(newTelephone);
            }
            else{
                cout<<"โปรดเลือก (1) หรือ (2)"<<endl;
                cin>>choice;
            }      
            saveMembers(members);      
            cout << "สมาชิกมีการเปลี่ยนแปลง สำเร็จ!" << endl;
            return;
        }
    }
    cout << "ชื่อผู้ใช้หรือรหัสผ่านผู้ใช้ผิด!" << endl;
}

int main() {
    while (true) {
        cout << "==========================" << endl;
        cout << "นี่คือบริการสำหรับสมาชิกของเรา\n";
        cout << "สมัครสมาชิกใหม่ (1)" << endl;
        cout << "ล็อคอินเข้าสู่ระบบ (2)" << endl;
        cout << "แก้ไขสมาชิก (3)" << endl;
        cout << "ออก (4)" << endl;
        cout << "โปรดเลือกบริการที่คุณต้องการ: ";
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