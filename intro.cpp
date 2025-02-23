#include<iostream>
#include<string>
#include <unistd.h>


using namespace std;
void press_enter() {
    cout<<"Press Enter to continue...";
    cin.get();
    system("cls");
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
    system("cls");
    cout<<"=========================="<<endl;
    cout<<"Hello Admin"<<endl;
    cout<<"Here are your services"<<endl;
    cout<<"=========================="<<endl;
    cout<<"\n";
    cout<<"\n";
    press_enter();
}
void user(){
    system("cls");
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
    system("cls");  
}
