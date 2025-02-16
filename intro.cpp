#include<iostream>
#include<string>
#include"admin.cpp"

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
    system("clear");  //clear' is not recognized as an internal or external command
    int loopcheck1 = 0;
    while (loopcheck1 == 0){
        cout<<"=========================="<<endl;
        cout<<"Are you an Admin or a User ?? "<<endl;
        int  user_type;
        cout<<"Admin(1)"<<" "<<"User(2)"<<endl;
        cout<<"Please choose the type of user you are: ";
        cin >> user_type;
        if (user_type == 1){
            system("clear");
            cout<<"=========================="<<endl;
            cout<<"Hello Admin"<<endl;
            cout<<"Here are your services"<<endl;
            cout<<"=========================="<<endl;
            cout<<"\n";
            cout<<"\n";
            press_enter();
            KaraokeAdmin admin;
            admin.adminMenu();
            loopcheck1 = 1;
        }
        else if (user_type == 2){
            system("clear");
            cout<<"=========================="<<endl;
            cout<<"Hello User"<<endl;
            cout<<"Here are your services"<<endl;
            cout<<"=========================="<<endl;
            cout<<"\n";
            cout<<"\n";
            cout<<"=========================="<<endl;
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
            loopcheck1 = 1;
        }
        else{
            system("clear");
            cout<<"Invalid input"<<endl;

        }
    }

}
int main() {
    intro();
    return 0;
}