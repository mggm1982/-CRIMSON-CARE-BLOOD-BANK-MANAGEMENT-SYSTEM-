#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <ctime>
using namespace std;


string filename = "F:\\BB\\bloodbank.csv";


class BloodStock {

public:
    int Apos, Aneg, Bpos, Bneg, ABpos, ABneg, Opos, Oneg;

    BloodStock(){Apos=Aneg=Bpos=Bneg=ABpos=ABneg=Opos=Oneg=0;}

    void read(ifstream &fin) {             
        string line; 
        getline(fin,line); // header row
        getline(fin,line); // values row
        stringstream ss(line);
        char comma;
        ss>>Apos>>comma>>Aneg>>comma>>Bpos>>comma>>Bneg>>comma>>ABpos>>comma>>ABneg>>comma>>Opos>>comma>>Oneg;
    }

    void write(ofstream &fout) const {
        fout<<"Apos,Aneg,Bpos,Bneg,ABpos,ABneg,Opos,Oneg\n";
        fout<<Apos<<","<<Aneg<<","<<Bpos<<","<<Bneg<<","<<ABpos<<","<<ABneg<<","<<Opos<<","<<Oneg<<"\n";
    }

    int* getRef(const string &bg) {
        if(bg=="A+") return &Apos; if(bg=="A-") return &Aneg;
        if(bg=="B+") return &Bpos; if(bg=="B-") return &Bneg;
        if(bg=="AB+") return &ABpos; if(bg=="AB-") return &ABneg;
        if(bg=="O+") return &Opos; if(bg=="O-") return &Oneg;
        return nullptr;
    }
};

class Customer {
public:
    string name,contact,hospitalID,bloodGroup;
    int donationToken,receptionToken;
    bool Transactionstatus;
    double bill;
    int fitness; //1 fit 0 unfit

    Customer(){donationToken=receptionToken=0; Transactionstatus =false; bill=0.0; fitness=1;}

    void readFromCSV(const string &line) {
        stringstream ss(line);
        string TransStr;
        string token;
        getline(ss,name,',');
        getline(ss,contact,',');
        getline(ss,hospitalID,',');
        getline(ss,token,','); donationToken=stoi(token);
        getline(ss,token,','); receptionToken=stoi(token);
        getline(ss,bloodGroup,',');
        getline(ss,TransStr,','); Transactionstatus=(TransStr=="1");
        getline(ss,token,','); bill=stod(token);
        getline(ss,token,','); fitness=stoi(token);
    }

    string toCSV() const {
        return name + "," + contact + "," + hospitalID + "," +
            to_string(donationToken) + "," + to_string(receptionToken) + "," +
            bloodGroup + "," + (Transactionstatus?"1":"0") + "," +
            to_string(bill) + "," + to_string(fitness);
    }
};

void loadAll(const string &filename, BloodStock &stock, vector<Customer> &customers) {
    customers.clear();
    ifstream fin(filename);
    if(!fin) {
        // create new file with header
        ofstream fout(filename);
        BloodStock initial;
        initial.write(fout);
        fout<<"NAME,CONTACT,HOSPITALID,DTOKEN,RTOKEN,BLOODGRP,PAYSTATUS,BILL,FITNESS\n";
        fout.close();
        fin.open(filename);
    }
    stock.read(fin);
    string header; 
    getline(fin,header); // customer header
    string line;
    while(getline(fin,line)) {
        if(line.empty()) continue;
        Customer c; c.readFromCSV(line);
        customers.push_back(c);
    }
    fin.close();
}

void overwriteFile(const string &filename, const BloodStock &stock, const vector<Customer> &customers) {
    ofstream fout(filename);
    stock.write(fout);
    fout<<"NAME,CONTACT,HOSPITALID,DTOKEN,RTOKEN,BLOODGRP,PAYSTATUS,BILL,FITNESS\n";
    for(const auto &c: customers) {
        fout<<c.toCSV()<<"\n";
    }
    fout.close();
}

int randomToken() {return rand()%9000+1000;}

int main() {

    srand(time(0));
    string filename="bloodbank.csv";
    BloodStock stock;
    vector<Customer> customers;
    loadAll(filename,stock,customers);

cout<<endl;cout<<endl;cout<<endl;    

cout<<"\033[1;31m||||||==   ||        =|||||=   =|||||=   ||||||== \033[0m "<<setw(18)<<"\033[1;31m         ||||||==      |||||    |||     ||  ||  ==  \033[0m   "<<endl; 
cout<<"\033[1;31m||    ==   ||       ||     || ||     ||  ||     == \033[0m "<<setw(10)<<"\033[1;31m        ||    ==    ||     ||  ||==    ||  || == \033[0m  "<<endl; 
cout<<"\033[1;31m|||||||    ||       ||     || ||     ||  ||     || \033[0m "<<setw(10)<<"\033[1;31m        |||||||     |||||||||  || ==   ||  |||| \033[0m  "<<endl; 
cout<<"\033[1;31m||    ==   ||       ||     || ||     ||  ||     ==  \033[0m "<<setw(10) <<"\033[1;31m       ||    ==    ||     ||  ||  ==  ||  || ==  \033[0m    "<<endl;
cout<<"\033[1;31m||||||==   |||||||   =|||||=   =|||||=   ||||||== \033[0m "<<setw(18) <<"\033[1;31m         ||||||==    ||     ||  ||   ==|||  ||  == \033[0m    "<<endl; 


cout<<endl;cout<<endl;cout<<endl;

cout<<"------------------------------------\033[1;37;44mCRIMSON CARE BLOOD BANK\033[0m-------------------------------------------"<<endl;
cout<<"-----------------------------------\033[3;37mA Drop Today, A Life Tomorrow.\033[0m------------------------------------"<<endl;

cout<<endl;cout<<endl;

    cout<<"Enter your name"<<endl;
    string name; cin>>name;

    Customer cust; bool existing=false;
    for(auto &c:customers){
        if(c.name==name){cust=c; existing=true; break;}
    }

    if(!existing){
        cout<<"Oh, you are a new customer! Enter the following details to get yourself registered in our database:\n";
        cust.name=name;
        cout<<"Contact number: ";cin>>cust.contact;
        cout<<"Hospital ID {in the form H1234 of the hospital}: ";cin>>cust.hospitalID;
        cout<<"Your Blood Group (A+/A-/B+/B-/AB+/AB-/O+/O-): ";cin>>cust.bloodGroup;
        cout<<"Your Fitness(enter 1 for fit, 0 for unfit): ";cin>>cust.fitness;
        cust.donationToken=randomToken();
        cust.receptionToken=randomToken();
        cust.Transactionstatus=false;
        cust.bill=0.0;
        customers.push_back(cust);
    }

    cout<<endl; cout<<"\033[1;32mSelect action:\n\n 1. Donate Blood \n 2. Request Blood \n 3. Update Contact/Fitness \033[0m"<<endl;
    int choice; cin>>choice;

    if(choice==1){

       // Check fitness first
    if(cust.fitness == 0){
        cout << "\033[3;31mYou are currently unfit to donate blood. Please consult a doctor or Update fitness state.\033[0m"<<endl;
    } else {
        cout << "\033[3;32mYou are fit to donate blood!\033[0m"<<endl;
        cout << "Collect your token number: " << cust.donationToken << "\n";
        cout << "Please move to Ward 23 and wait for your turn.\n";
    
        // Update stock
        int *bg = stock.getRef(cust.bloodGroup);
        if(bg){ (*bg)++;}

        // Generate a new donation token for the next donation
        cust.donationToken = randomToken();
        cust.Transactionstatus = true;
        cout << "\033[3;33mThank you for donating blood! Your one drop of blood is their future!\033[0m"<<endl;
    }

    }

    else if(choice==2){

    // Blood groups
    string bloodGroups[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    double rates[] = {320,1000,400,600,300,1800,540,970};

    // Display rates
    cout << "Blood Packet Rates:\n";
    cout << "--------------------\n";

    for(int i=0; i<8; i++) {
        cout << bloodGroups[i] << " : Rs. " << rates[i] << "\n";
    }

    cout<<endl;cout<<endl;

        string BG; cout<<"Reenter your blood group for confirmation"<<endl; cin>>BG;

        int n; cout<<"Enter the required number of blood packets"<<endl; cin>>n;
        double pay;
        
        int *bg=stock.getRef(cust.bloodGroup);

        if(bg && ((*bg)-n)>=0){
            *bg = *bg - n; cust.receptionToken=randomToken();

            for(int i=0; i<8; i++) {
        if(bloodGroups[i] == BG) {
            pay = rates[i] * n;
            break;
        }
        
    }
           cout << "You will have to make a payment of Rs. "<< pay <<endl;
           cout<<endl;

        // After payment
        cust.bill = pay;
        cout << "Payment cleared."<<endl;
        cout<<"\033[3;33mBlood packet issued successfully!\033[0m"<<endl;
        }

         else {
    char response;
    cout<<"Sorry, requested number of blood packets are not available.\n";
    cout<<"Would you like to take less number of packets as per availability (Y/N) ?"<<endl;
    cin>>response;

        switch(response){

            case 'Y': {cout<<"Sorry you could only get "<<*bg<<" packets"<<endl;

                for(int i=0; i<8; i++) {
                if(bloodGroups[i] == BG) {
                n = (*bg);
                pay = rates[i]*n;
                break;}
            }
                cout << "You will have to make a payment of Rs. "<<pay<<endl;cout<<endl;

                // After payment
                cust.bill = pay;
                cout << "Payment cleared."<<endl;
                cout<<"\033[3;33mBlood packet issued successfully!\033[0m"<<endl;
                    *bg = 0;
                    break; }

            case 'N': {cout<<"\033[3;33mSorry for the inconvenience\033[0m"<<endl;
                break;}
            }
            
    }

}
    else if(choice==3){
    cout<<"Enter contact: ";cin>>cust.contact; cout<<"Enter fitness state (1=fit,0=unfit): "; cin>>cust.fitness;
    cout<<"Hospital ID and Blood Group kept same.\n";
    }

    // update vector
    bool updated=false;
    for(auto &c:customers){if(c.name==cust.name){c=cust;updated=true;break;}}
    if(!updated)customers.push_back(cust);

    overwriteFile(filename,stock,customers);

    cout<<"\033[3;33mDetails have been updated on our database.\033[0m"<<endl;
    cout<<"\033[3;33mCheck the updated database!\033[0m"<<system("start \"\" \"bloodbank.csv\"");

}
