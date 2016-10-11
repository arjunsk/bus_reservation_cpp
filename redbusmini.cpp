#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <queue>


using namespace std;
/*
     E F    G H

     C        D
1    A A    B A
2    A A    A A
3    A A    B B
4    A A    B A
5    A A    A A
6    A A    B B
7    A A    B A
8    A A    A A
9    A A    B B


A= available
B= booked
D= driver
C= conductor


*/


class passenger{

    public:
    string phonenumber;
    string name;
    string from;
    char gender;
    int age;

    int cordX;
    int cordY;

    friend ostream& operator <<(ostream &din, passenger &p);

    void enterDetail(){

        cout<<"Enter Name: ";
        cin>>name;

        cout<<"Phone number: ";
        string tmp;
        cin>>tmp;

    // Data validation

        while(tmp.length()!=10)
        {
            cout<<"Wrong Entry...  Enter again \n";
            cin>>tmp;
        }

        phonenumber=tmp;

        char tmp2;

        cout<<"Gender(M/F): ";
        cin>>tmp2;

        // Data validation
        while(tmp2 !='M' && tmp2!='F' && tmp2!='m' && tmp2!='f')
        {
            cout<<"Wrong Entry... Enter again\n";
            cin>>tmp2;
        }

        gender=tmp2;

        cout<<"Age: ";
        cin>>age;


    }


    void disp(){
        cout<<"Name: "<<name<<"\n";

        cout<<"Phone number: "<<phonenumber<<"\n";

        cout<<"Gender: "<<gender<<"\n";

        cout<<"Age: "<<age<<"\n";
    }


};


    ostream& operator <<(ostream &din, passenger &p) {
        din<<p.phonenumber<<"\n";
        din<<p.name<<"\n";
        din<<p.from<<"\n";
        din<<p.gender<<"\n";
        din<<p.age<<"\n";
        din<<p.cordX<<"\n";
        din<<p.cordY<<"\n";
    }




class seat{
public:
    bool availability;
    char icon;



    seat(){
        availability= true;
        icon='A';

    }
   void  bookit(){
        availability= false;
        icon='B';
    }

   void unbookit(){
        availability= true;
        icon='A';
    }

};

class kanToSabarimala{  // this is the main class bus ie buskanToSabarimala

    public:
        seat seats[9][4];


    // Display the  seat layout
    void disp(){
         cout<<"\n    E F   G H\n\n";
         cout<<"    C       D\n";

        for(int i=0;i<9;i++)
        {
                cout<<"\n";

                cout<<i+1<<"   "<<seats[i][0].icon<<" "<<seats[i][1].icon<<"   "<<seats[i][2].icon<<" "<<seats[i][3].icon<<"\n";

        }

        cout<<"\n A= available\n B= booked\n D= driver\n C= conductor\n\n\n";

    }
    // to book the seat ie Seat from A to B
    void book(int a,char b){

            seats[a-1][b-'E'].bookit();
    }



    void unbook(){
    // should have user login
    }

};

int main () {

        // setting bus1 ---> kannur to kayamkulam
        kanToSabarimala bus;

        string inbetween[10];   // to store inbetween stops in the journey


        inbetween[0]="kannur";
        inbetween[1]="thalassery";
        inbetween[2]="mahe";
        inbetween[3]="vadakara";
        inbetween[4]="kozhikod";
        inbetween[5]="tirur";
        inbetween[6]="guruvayur";
        inbetween[7]="aluva";
        inbetween[8]="thodupusha";
        inbetween[9]="sabarimala";

        int fares[]={800,800,800,800,700,600,500,400,300,0};    // fares is the price for the trip

        //fares={800,800,800,800,700,600,500,400,300,0};




// reading the database if it earlier formed
ifstream infile("Database");
infile.read ( (char *)(&bus), sizeof(bus) ) ;
infile.close();


cout<<" ****** Welcome to mini Red bus [ Seasonal for Sabarimala ] ********** \n\n\n\n";

cout<<"Step 1   >>Enter the journey details << \n\n";
cout<<"--------------------------------------\n\n";


// For storing the passenger booking positions  for later use
queue <pair<int ,char> > q;

string s;

cout<<"From:--> [ you can choose from the below list ]\n\n";
for(int  i=0;i<10;i++)
{
    cout<<i+1<<". "<<inbetween[i]<<"  \n";
}

cout<<"\n\nFrom: ";
cin>>s;







int finalfare=0; // stores the net fare for the journey

for(int i=0;i<10;i++)
{
    if( s.compare(inbetween[i])==0)    // checks if the user entered a valid boarding point
    {
        finalfare=fares[i];
    }
}



cout<<"\n\n\nStep 2   >>Select your seat in the bus << \n\n";
cout<<"----------------------------------------\n\n\n";

bus.disp();

int x;
char y,option;

int noPassengers=0;

// book tickets via cordinates
do{

    cout<<"\n\nEnter the cordinates to Book";
    cout<<"\nFor Eg:- 1 F\n";

    cin>>x;
    cin>>y;

    if(y>='E' && y<='H' && x>0 && x<10)
    {
       if(bus.seats[x-1][y-'E'].icon=='A')
       {
        bus.book(x,y);
        q.push(make_pair(x,y));
        noPassengers++;
       }
       else{
        cout<<"\n\nAlready booked by some other\n\n";
       }
    }
    else{
        cout<<"\n\nInvalid input\n\n";
    }


    cout<<"\nBook another? Y/N ";
    cin>>option;

}while(option=='y'or option=='Y');



cout<<"\n\n\nStep 3   >>Current Seat Availability in the Bus  << \n\n";
cout<<"----------------------------------------\n\n";

bus.disp();


cout<<"\n\n\nStep 4   >>Enter more details about the passenger << \n\n";
cout<<"----------------------------------------\n\n";

passenger *pass=new passenger[noPassengers];


 int t1;
 char t2;

for(int i=0;i<noPassengers;i++)
{
    cout<<"\n\nEnter Passenger"<<i+1<<" Details\n";
    pass[i].enterDetail();
    pass[i].from=s;

            t1=q.front().first;
            t2=q.front().second;
            q.pop();

    pass[i].cordX=t1-1;
    pass[i].cordY=t2-'E';
}



cout<<"\n\n\n\n\############ SUMMARY  #############\n\n\n";
cout<<"Journey From  "<<s<<" To  "<<"Sabarimala"<<"\n\n";
cout<<"-------------------------------------\n\n";


cout<<"Passenger Details : \n\n";

for(int i=0;i<noPassengers;i++)
{
    cout<<"Passenger "<<i+1<<" Details "<<"\n";
    pass[i].disp();

    cout<<"\n\n";
}

cout<<"\n\nTotal Fare:   "<<noPassengers*finalfare<<"\n";


cout<<"\n\n\nStep 5   >>Proceed To Payment << \n\n";
cout<<"----------------------------------------\n\n";

int success;

cin>>success;

if(success==1)
{
    // saving the data to a database;
    ofstream savetoDisk;
    savetoDisk.open("Database");
    savetoDisk.write ( (char *)(&bus), sizeof(bus) );
    savetoDisk.close();


    // saving passengers details
    ofstream passToDisk;
    passToDisk.open("Passengers",ios::app);

    for(int i=0;i<noPassengers;i++)
    passToDisk<<pass[i];


    passToDisk.close();

}

  return 0;
}
