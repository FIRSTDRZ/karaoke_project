#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio> // สำหรับฟังก์ชัน remove และ rename

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

// ฟังก์ชันเพื่อลบบรรทัดที่มีรหัสการจองห้องที่กำหนด
void deleteBookingLine(const string& roomBookingCodeToDelete) {
    string filename = "booking.txt"; // ชื่อไฟล์ต้นทาง
    string tempFilename = "temp_booking.txt"; // ชื่อไฟล์ชั่วคราว

    // เปิดไฟล์ต้นทางสำหรับอ่าน
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "can't open file" << endl;
        return;
    }

    // เปิดไฟล์ชั่วคราวสำหรับเขียน
    ofstream tempFile(tempFilename);
    if (!tempFile.is_open()) {
        cerr << "Unable to create temporary file!" << endl;
        inputFile.close();
        return;
    }

    // อ่านข้อมูลทีละบรรทัดจากไฟล์ต้นทาง
    string line;
    bool found = false;
    while (getline(inputFile, line)) {
        // ใช้ stringstream เพื่อแยกค่าแรกจากบรรทัด
        stringstream ss(line);
        string firstValue;
        getline(ss, firstValue, ',');

        // ตรวจสอบว่าค่าแรกตรงกับรหัสที่ต้องการลบหรือไม่
        if (firstValue == roomBookingCodeToDelete) {
            found = true; // พบรหัสที่ต้องการลบ
            continue; // ข้ามการเขียนบรรทัดนี้ลงในไฟล์ชั่วคราว
        }

        // เขียนบรรทัดที่ไม่ได้ลบลงในไฟล์ชั่วคราว
        tempFile << line << endl;
    }

    // ปิดไฟล์ทั้งสอง
    inputFile.close();
    tempFile.close();

    // ตรวจสอบว่าพบรหัสที่ต้องการลบหรือไม่
    if (!found) {
        cout << "The room reservation code you want to delete was not found!" << endl;
        remove(tempFilename.c_str()); // ลบไฟล์ชั่วคราว
        return;
    }

    // ลบไฟล์ต้นทาง
    if (remove(filename.c_str())) {
        cerr << "Unable to delete source file!" << endl;
        return;
    }

    // เปลี่ยนชื่อไฟล์ชั่วคราวเป็นชื่อไฟล์ต้นทาง
    if (rename(tempFilename.c_str(), filename.c_str())) {
        cerr << "Unable to rename temporary file!" << endl;
        return;
    }

}

// int main() {
//     // เปิดไฟล์ booking.txt เพื่ออ่านข้อมูล
//     ifstream inputfile("booking.txt");
//     if (!inputfile.is_open()) {
//         cerr << "can't open file" << endl;
//         return 1; // จบการทำงานโปรแกรมด้วยรหัสผิดพลาด
//     }

//     // สร้าง vector เพื่อเก็บรหัสการจองห้อง
//     vector<string> bookingcodes;

//     // อ่านข้อมูลจากไฟล์ทีละบรรทัด
//     string line;
//     while (getline(inputfile, line)) {
//         // ใช้ stringstream เพื่อแยกข้อมูลในบรรทัด
//         stringstream ss(line);
//         string firstValue;

//         // อ่านค่าแรกก่อนเครื่องหมาย ','
//         getline(ss, firstValue, ',');

//         // เพิ่มค่าแรกเข้าไปใน vector
//         bookingcodes.push_back(firstValue);
//     }

//     // ปิดไฟล์หลังจากอ่านเสร็จ
//     inputfile.close();

//     bool validChoice = false;
//     while (!validChoice) {
//         // รหัสการจองห้องที่ต้องการตรวจสอบ
//         string roomBookingCode;
//         cout << "Enter the room booking code: ";
//         cin >> roomBookingCode;

//         // ตรวจสอบว่ารหัสการจองห้องมีอยู่ในรายการหรือไม่
//         if (checkRoomBookingCode(roomBookingCode, bookingcodes)) {
//             cout << "Room booking code found" << endl;
//             cout << "==========================" << endl;

//             cout << "Do you want to cancel this booking?" << endl;
//             cout << "1. Yes" << endl;
//             cout << "2. No" << endl;
//             cout << "Please select (1-2): ";

//             int choice_cancel;
//             cin >> choice_cancel;

//             if (choice_cancel == 1) {
//                 // เรียกใช้ฟังก์ชันลบบรรทัด
//                 deleteBookingLine(roomBookingCode);
//                 cout << "cancel completed";
//                 validChoice = true;
//             } else if (choice_cancel == 2) {
//                 cout << "Operation cancelled" << endl;
//                 validChoice = false;
//             } else {
//                 cout << "Invalid choice. Please try again." << endl;
//                 validChoice = false;
//             }
//         } else {
//             cout << "Room booking code not found" << endl;
//         }
//     }


//     return 0;
// }