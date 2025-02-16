#include<iostream>
#include<string>
#include<ctime>
#include<vector>

using namespace std;

class KaraokeAdmin {
private:
    const string ADMIN_PASSWORD = "admin123";
    
    // โครงสร้างข้อมูลสำหรับห้อง
    struct RoomSettings {
        int smallRoomCount = 0;
        int mediumRoomCount = 0;
        int largeRoomCount = 0;
        int smallRoomCapacity = 0;
        int mediumRoomCapacity = 0;
        int largeRoomCapacity = 0;
        double smallRoomPrice = 0;
        double mediumRoomPrice = 0;
        double largeRoomPrice = 0;
        int openingHour = 0;
        int closingHour = 0;
    };
    
    RoomSettings settings;

public:
    bool login() {
        string password;
        cout << "กรุณาใส่รหัสผ่าน Admin: ";
        cin >> password;
        return password == ADMIN_PASSWORD;
    }
    
    void adminMenu() {
        if (!login()) {
            cout << "รหัสผ่านไม่ถูกต้อง\n";
            return;
        }
        
        int choice;
        do {

            cout << "\n=== เมนู Admin ===\n";
            cout << "1. ตั้งค่าจำนวนห้อง\n";
            cout << "2. ตั้งค่าความจุห้อง\n";
            cout << "3. ตั้งค่าราคาห้อง\n";
            cout << "4. ตั้งค่าเวลาเปิด-ปิด\n";
            cout << "5. แสดงการตั้งค่าทั้งหมด\n";
            cout << "0. ออกจากเมนู Admin\n";
            cout << "เลือกเมนู: ";
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
                    cout << "ออกจากเมนู Admin\n";
                    break;
                default:
                    cout << "เมนูไม่ถูกต้อง กรุณาเลือกใหม่\n";
            }
        } while (choice != 0) ; system("clear"); cout<<"thank you admin"<<endl;
    }
    
private:
    void setRoomCounts() {
        cout << "\n=== ตั้งค่าจำนวนห้อง ===\n";
        cout << "จำนวนห้องเล็ก: ";
        cin >> settings.smallRoomCount;
        cout << "จำนวนห้องกลาง: ";
        cin >> settings.mediumRoomCount;
        cout << "จำนวนห้องใหญ่: ";
        cin >> settings.largeRoomCount;
    }
    
    void setRoomCapacities() {
        cout << "\n=== ตั้งค่าความจุห้อง (จำนวนคน) ===\n";
        cout << "ความจุห้องเล็ก: ";
        cin >> settings.smallRoomCapacity;
        cout << "ความจุห้องกลาง: ";
        cin >> settings.mediumRoomCapacity;
        cout << "ความจุห้องใหญ่: ";
        cin >> settings.largeRoomCapacity;
    }
    
    void setRoomPrices() {
        cout << "\n=== ตั้งค่าราคาห้องต่อชั่วโมง ===\n";
        cout << "ราคาห้องเล็ก: ";
        cin >> settings.smallRoomPrice;
        cout << "ราคาห้องกลาง: ";
        cin >> settings.mediumRoomPrice;
        cout << "ราคาห้องใหญ่: ";
        cin >> settings.largeRoomPrice;
    }
    
    void setOperatingHours() {
        cout << "\n=== ตั้งค่าเวลาเปิด-ปิด ===\n";
        do {
            cout << "เวลาเปิด (0-23): ";
            cin >> settings.openingHour;
        } while (settings.openingHour < 0 || settings.openingHour > 23);
        
        do {
            cout << "เวลาปิด (0-23): ";
            cin >> settings.closingHour;
        } while (settings.closingHour < 0 || settings.closingHour > 23 || 
                settings.closingHour <= settings.openingHour);
    }
    
    void displaySettings() {
        cout << "\n=== การตั้งค่าทั้งหมด ===\n";
        cout << "จำนวนห้อง:\n";
        cout << "  ห้องเล็ก: " << settings.smallRoomCount << " ห้อง\n";
        cout << "  ห้องกลาง: " << settings.mediumRoomCount << " ห้อง\n";
        cout << "  ห้องใหญ่: " << settings.largeRoomCount << " ห้อง\n";
        
        cout << "\nความจุห้อง:\n";
        cout << "  ห้องเล็ก: " << settings.smallRoomCapacity << " คน\n";
        cout << "  ห้องกลาง: " << settings.mediumRoomCapacity << " คน\n";
        cout << "  ห้องใหญ่: " << settings.largeRoomCapacity << " คน\n";
        
        cout << "\nราคาต่อชั่วโมง:\n";
        cout << "  ห้องเล็ก: " << settings.smallRoomPrice << " บาท\n";
        cout << "  ห้องกลาง: " << settings.mediumRoomPrice << " บาท\n";
        cout << "  ห้องใหญ่: " << settings.largeRoomPrice << " บาท\n";
        
        cout << "\nเวลาทำการ:\n";
        cout << "  เปิด: " << settings.openingHour << ":00 น.\n";
        cout << "  ปิด: " << settings.closingHour << ":00 น.\n";
    }
};
