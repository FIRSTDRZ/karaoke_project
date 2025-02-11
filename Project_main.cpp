#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<vector>
#include "intro.cpp"
using namespace std;

void enter_memberships(int n) ;

int main() {
    intro();
    int choice;
    cin>>choice;   
    if (choice == 3 ) {
        cout<<"=========================="<<endl;
        cout<<"Here are our memberships"<<endl;
        cout<<"New Membership(1)"<<endl;
        cout<<"Log in Membership(2)"<<endl;
        cout<<"Edit Membership(3)"<<endl;
        cout<<"Please choose the service you want to use: ";
        int choice_member;
        cin>>choice_member;
    }

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
    