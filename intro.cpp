#include<iostream>
#include <string>



using namespace std;
void press_enter() {
    cout<<"Press Enter to continue...";
    cin.get();
    system("clear");
}
void intro(){
    cout<<"=========================="<<endl;
    cout<<"Hello Welcome to My Karoke"<<endl;
    cout<<"Here are our services"<<endl;
    cout<<"=========================="<<endl;
    press_enter();
    cout<<"=========================="<<endl;
    cout<<"Booking(1)"<<endl;
    cout<<"Type of Room(2)"<<endl;
    cout<<"Memberships(3)"<<endl;
    cout<<"Show Queue(4)"<<endl;
    cout<<"Cancel Booking(5)"<<endl;
    cout<<"Log out(6)"<<endl;
    cout<<"=========================="<<endl;
    cout<<"Please choose the service you want to use: ";
}
