#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<chrono>
#include<thread>
#include"intro.cpp"
#include "Membership.cpp"
using namespace std;

class User{
    public:
            int id,password;
            string booking_code;

    private:
};

class Admin{
    public:
           int id,password;


    private:

};


int main() {
    intro();
    
    int choice;
    cin>>choice;   
    //if (choice == 3 ) Membership(); // fixing 
   
    if (choice == 2) {
        cout<<"=========================="<<endl;
        cout<<"Here are our rooms"<<endl;
        cout<<"Small Room(1)"<<endl;
        cout<<"Medium Room(2)"<<endl;
        cout<<"Large Room(3)"<<endl;
        cout<<"Please choose the room you want to book: ";
        int choice_room;
        cin>>choice_room;
    }

    if (choice == 6) {
        system("clear");
        cout<<"======================================"<<endl;
        cout<<"thank you for using our service"<<endl;
        cout <<"======================================" << endl;
        return 0;
    }


    
    
    
    
    
    
    
    return 0;
}
    