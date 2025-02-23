#include<iostream>
#include<string>
#include <unistd.h>
#include "Membership.cpp"

using namespace std;
void press_enter() {
    cout<<"Press Enter to continue...";
    cin.get();
    system("clear");
}
void printIntro() {
    string ascii_art =
    "_____  _____    ____       _ ______ _____ _______ \n"
    "|  __ \\|  __ \\ / __ \\     | |  ____/ ____|__   __|\n"
    "| |__) | |__) | |  | |    | | |__ | |       | |\n"   
    "|  ___/|  _  /| |  | |_   | |  __|| |       | |\n"   
    "| |    | | \\ \\| |__| | |__| | |___| |____   | |\n"   
    "|_|    |_|  \\_\\\\____/ \\____/|______\\_____|  |_|\n";   
                                                      
                                                      
   
    cout << ascii_art << endl;
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
}
void admin(){
    system("clear");
    cout<<"=========================="<<endl;
    cout<<"Hello Admin"<<endl;
    cout<<"Here are your services"<<endl;
    cout<<"=========================="<<endl;
    cout<<"\n";
    cout<<"\n";
    press_enter();
}
void user(){
    system("clear");
    cout<<"=========================="<<endl;
    cout<<"\n";
    cout<<"Hello User"<<endl;
    cout<<"Here are your services"<<endl;
    cout<<"\n";
    cout<<"=========================="<<endl;
    cout<<"\n";
    cout<<"Booking(1)"<<endl;
    cout<<"Type of Room(2)"<<endl;
    cout<<"Memberships(3)"<<endl;
    cout<<"Show Queue(4)"<<endl;
    cout<<"Cancel Booking(5)"<<endl;
    cout<<"Log out(6)"<<endl;
    cout<<"\n";
    cout<<"=========================="<<endl;
    cout<<"\n";
    cout<<"\n";
    cout<<"\n";
    cout<<"Please choose the service you want to use: ";
    int choice;
    cin>>choice;     // แก้เป็นswitch case
    if (choice == 3) {
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
                    user(); 
                    check = false;
                    break;
                default:
                    cout << "Invalid choice! Please try again." << endl;
            }
        }
    }
    if (choice == 6) {
        cout << "Logging out...";
        cout << "\nGoodbye!" << endl;
        exit(0);     // Properly end the program
    }
} 


void intro(){
    printIntro();
    press_enter();
    cout<<"=========================="<<endl;
    cout<<"\n";
    cout<<"Hello Welcome to My Karoke"<<endl;
    cout<<"Here are our services"<<endl;
    cout<<"\n";
    cout<<"=========================="<<endl;
    cout<<"\n";
    cout<<"\n";
    press_enter();
    system("clear");  
}
