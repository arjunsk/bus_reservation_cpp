#include <iostream>
#include <fstream>
#include <string.h>



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
};


istream& operator >>(istream &din, passenger &p) {
        din>>p.phonenumber;
        din>>p.name;
        din>>p.from;
        din>>p.gender;
        din>>p.age;
        din>>p.cordX;
        din>>p.cordY;
    }


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


string phone;
cout<<"**********Booked users********\n\n";
cout<<"Enter the phone number : ";
cin>>phone;
int flag=0;
cout<<"\n\n";

char seats[9][4];

memset( seats, 'N', sizeof(char)*36 );

  for(int j=0;j<i;j++)
  {
      if(phone.compare(pass[j].phonenumber)==0)
      {
          pass[j].disp();
          seats[pass[j].cordX ][pass[j].cordY]='B';
          cout<<"\n\n";
          flag=1;
      }
  }

  if(flag==0)
    cout<<"\n\nNo user Found\n\n";
   else{
            cout<<"\n    E F   G H\n\n";
            cout<<"    C       D\n";

            for(int i=0;i<9;i++)
            {
                    cout<<"\n";
                    //system("color 4");
                    cout<<i+1<<"   "<<seats[i][0]<<" "<<seats[i][1]<<"   "<<seats[i][2]<<" "<<seats[i][3]<<"\n";

            }
            cout<<"\n N= May or May not be Available\n B= Your Booked Seats\n D= driver\n C= conductor\n\n\n";
 }




  return 0;
}
