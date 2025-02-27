#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// ฟังก์ชันเพื่อตรวจสอบว่าห้องจองมีอยู่ในรายการหรือไม่
bool checkRoomBookingCode(const string& roomBookingCode, const vector<string>& bookingCodes) {
    for (const auto& code : bookingCodes) {
        if (code == roomBookingCode) {
            return true; // พบรหัส
        }
    }
    return false; // ไม่พบรหัส
}

int main() {
    // เปิดไฟล์ booking.txt เพื่ออ่านข้อมูล
    ifstream inputfile("booking.txt");
    if (!inputfile.is_open()) {
        cerr << "can't open file" << endl;
        return 1; // จบการทำงานโปรแกรมด้วยรหัสผิดพลาด
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
            
                int choice;
                cin >> choice;
            
            
                if (choice == 1){
                    cout << "Booking cancelled successfully" << endl;
                    validChoice = true;
                }
                else if(choice == 2){
                    cout << "Operation cancelled" << endl;
                    validChoice = false;
                }    
                else {
                    validChoice = false;
                }
            }
            
            else{
                cout << "Room booking code not found" << endl;
            }
        }
    return 0;
}
    
