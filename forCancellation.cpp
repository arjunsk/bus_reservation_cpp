#include <iostream>
#include <fstream>
#include <string.h>


#include <windows.h>


using namespace std;

class passenger{

    public:
    string phonenumber;
    string name;
    string from;
    char gender;
    int age;

    int cordX;
    int cordY;


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

        cout<<"Gender: "<<gender<<"\n";

        cout<<"Age: "<<age<<"\n";

        cout<<"Seat Position: "<<cordX+1<<char(cordY+'E')<<"\n";


    }


    friend istream& operator >>(istream &din, passenger &p);

    friend ostream& operator <<(ostream &din, passenger &p);

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



istream& operator >>(istream &din, passenger &p) {
        din>>p.phonenumber;
        din>>p.name;
        din>>p.from;
        din>>p.gender;
        din>>p.age;
        din>>p.cordX;
        din>>p.cordY;
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



    void unbook(int a,int b){
       seats[a][b].unbookit();
    }

};











int main () {


//cout<<"lol";
//system("color 1"); // the colours are from 1 to 15.
//cout<<"Coloured text! yay";


//http://stackoverflow.com/questions/9262270/color-console-output-with-c-in-windows?rq=1

    // opening the file
  ifstream data("Passengers");


  passenger *pass=new  passenger[10];
  int i=0;
  while(data>>pass[i])
  {
      i++;
  }
data.close();


string phone;
cout<<"**********Booked users********\n\n";
cout<<"Enter the phone number : ";
cin>>phone;
int flag=0;
cout<<"\n\n";

char seats[9][4];

memset( seats, 'N', sizeof(char)*36 );



// cancel

kanToSabarimala bus;
ifstream fp("Database");
fp.read((char *)&bus,sizeof(bus));
fp.close();



char cancel;


ofstream passToDisk("tPassengers");

  for(int j=0;j<i;j++)
  {
      if(phone.compare(pass[j].phonenumber)==0)
      {
          pass[j].disp();

          cout<<"\nCancel there ticket? (y/n) : ";
          cin>>cancel;

          cout<<"\n";

          if(cancel =='Y'|| cancel=='y')
          {
              bus.unbook(pass[j].cordX,pass[j].cordY);
          }

          else{
            passToDisk<<pass[j];
          }

          //seats[pass[j].cordX ][pass[j].cordY]='B';
          //cout<<"\n\n";
          flag=1;
      }
  }



ofstream fp2("Database");
fp2.write((char *)&bus,sizeof(bus));
fp2.close();

passToDisk.close();

  if(flag==0)
    cout<<"\n\nNo user Found\n\n";


   remove("Passengers");

   rename("tPassengers","Passengers");




  return 0;
}
