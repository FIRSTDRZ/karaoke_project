#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


void new_membership() {
    
}


int main() {
    ifstream membership_file("Member.txt");

    cout<<"=========================="<<endl;
    cout<<"Here are our memberships"<<endl;
    cout<<"New Membership(1)"<<endl;
    cout<<"Log in Membership(2)"<<endl;
    cout<<"Edit Membership(3)"<<endl;
    cout<<"Please choose the service you want to use: ";
    int choice_member;
    cin>>choice_member;
        
}