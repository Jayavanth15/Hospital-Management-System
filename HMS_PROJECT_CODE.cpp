#include <stdio.h>
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <conio.h>
#include <string.h>
#include <time.h>

using namespace std;

class PERSON{
    private:
    char Name[50];
	char Gender[10],City[50],Country[50],State[50],Blood_g[5];;
    int Age,Date,Month,Year;
    long int PhoneNum;
    int ZipCode,PersonID;
public:
    void Person_Info()
    {
        cout<<"Enter Name :";
        cin.clear();
        cin.ignore();
        cin.getline(Name,50);
        cout<<"Enter Gender :";
        cin>>Gender;
        cout<<"Enter Age :";
        cin>>Age;
        cout<<"Enter Address :";
        cin>>Country;
        cout<<"Enter Blood group:";
        cin>>Blood_g;
    }

    void Display_info()
    {
        cout<<"Name: "<<Name<<endl;
        cout<<"Gender: "<<Gender<<endl;
        cout<<"Age: "<<Age<<endl;
        cout<<"Address: "<<this->Country<<endl;
        cout<<"Blood Group:"<<Blood_g<<endl;
    }
};

class STAFF:public PERSON
           {
           int Salary;
           char Time_from[30],Time_to[30];

    public:

          void staff_info()
          {
              Person_Info();
              cout<<"Enter salary:";cin>>Salary;
              cout<<"Enter Duty time:"; 
              cout<<"From:";
              cin>>Time_from;
              cout<<"To:";
              cin>>Time_to;
          }

           void show_staff()
           {
                cout<<"\nSalary: "<<Salary;
                cout<<"\nDuty Time: "<<Time_from<<"--"<<Time_to<<endl;
                Display_info();
           }
};


class patient: public PERSON{
    int Reg_no;
    char Occupation[30];
    char Date_admit[30];
    char Date_discharge[30];
    int Bill,Total;

public:
    char Medicine[100];
    void patient_bill();
    void getdata(); //function to accept data from user
    void showdata(); //function to show data on screen
    int retidno();
    void modify_medicine(int n);
    void write_patient(); //write the record in file
    void display_all(); //read all records from file
    void display_p(int n); //accept reg_no and read record from file
    void modify_patient(int n); //accept reg_no and update record of file
    void delete_patient(int n); //accept reg_no and delete selected records from file
};


void patient::patient_bill()  //using scope resolution operator to define function outside class
{
    system("CLS");
    cout << "________________________________________________________________________________";
    cout << "\n\n\t\t\t\tPatient Fee Charge\n\n ";
    cout << "________________________________________________________________________________";
    cout << "\nHospital Care Charges                      :\t  50";
    cout << "\nHospital Maintaince Charges                :\t  50";
    cout << "\nPatient Individual  Charges                :\t " << Bill;
    Total = 50 + 50 + Bill;
    cout << "\nTotal Fee Charge                           :\t"  << Total<<"\n";
    cout << "________________________________________________________________________________";
}

void patient::getdata(){
    Person_Info();
    cout<<"\nEnter The registration number of the patient: ";
    cin>>Reg_no;
    cout<<"\nEnter The occupation of the patient: ";
    cin>>Occupation;
    cout<<"\nEnter The bill of the patient:";
    cin>>Bill;
    cout<<"\nEnter The date admitted(dd/mm/yyyy):";
    cin>>Date_admit;
    cout<<"\nEnter The date discharged(dd/mm/yyyy):";
    cin>>Date_discharge;
    patient_bill();
    strncpy(Medicine, "null", sizeof(Medicine) - 1);
    Medicine[sizeof(Medicine) - 1] = 0;
}

void patient::showdata(){
    cout<<"\nRegistration number of patient: "<<Reg_no<<"\n";
    Display_info();
    cout<<"\nOccupation : "<<Occupation;
    cout<<"\nAdmit date : "<<Date_admit;
    cout<<"\nDischarhge date :"<<Date_discharge;
    cout<<"\nBill :"<<Total;
    cout<<"\nPrescribed Medicine: "<<Medicine;  
}

int  patient::retidno(){ return Reg_no; }

void patient::modify_medicine(int n){
    bool found=false;
    patient p;
    fstream File;
    File.open("patient.dat",ios::binary|ios::in|ios::out);
    if(!File){
    cout<<"File could not be open !! Press any Key...";
    cin.ignore();
    cin.get();
    return;
}
    while(!File.eof() && found==false){
    File.read(reinterpret_cast<char *> (&p), sizeof(patient));
    if(p.retidno()==n){
    p.showdata();
    cout<<"\n\nPlease Enter The Medicine of patient"<<endl;
                cin>>p.Medicine;
    int pos=(-1)*static_cast<int>(sizeof(p));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&p), sizeof(patient));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
    File.close();
    if(found==false)
    cout<<"\n\n Record Not Found ";
    cin.ignore();
    cin.get();
}


void patient::write_patient(){  // writing into file
    patient p;
    ofstream outFile;
    outFile.open("patient.dat",ios::binary|ios::app);
    p.getdata();
    outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
    outFile.close();
    cout<<"\n\nPatient record Has Been Created ";
    cin.ignore();
    cin.get();
}

void patient::display_all()  {
    patient p;
    ifstream inFile;
    inFile.open("patient.dat",ios::binary);
    if(!inFile)
    {
    cout<<"File could not be open !! Press any Key...";
    cin.ignore();
    cin.get();
    return;
}
    cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
    while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
    p.showdata();
    cout<<"\n\n________________________________________________________________________________\n";
}
    inFile.close();
    cin.ignore();
    cin.get();
}

void patient::display_p(int n){ //reading specific file
    patient p;
    ifstream inFile;
    inFile.open("patient.dat",ios::binary);
    if(!inFile)
    {
    cout<<"File could not be open !! Press any Key...";
    cin.ignore();
    cin.get();
    return;
    }
    bool flag=false;
    while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
    {
        if(p.retidno()==n)
        {
        p.showdata();
        flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    cout<<"\n\nrecord not exist";
    cin.ignore();
    cin.get();
}


void patient:: modify_patient(int n)   //modifying patient details
{
    bool found=false;
    patient p;
    fstream File;
File.open("patient.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&p), sizeof(patient));
if(p.retidno()==n)
{
p.showdata();
cout<<"\n\nPlease Enter The New Details of patient"<<endl;
                p.getdata();
    int pos=(-1)*static_cast<int>(sizeof(p));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&p), sizeof(patient));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void patient:: delete_patient(int n)  //deleting a particular file
{
patient p;
ifstream inFile;
inFile.open("patient.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
ofstream outFile;
outFile.open("Temp.dat",ios::out);
inFile.seekg(0,ios::beg);
while(inFile.read(reinterpret_cast<char *> (&p), sizeof(patient)))
{
if(p.retidno()!=n)
{
outFile.write(reinterpret_cast<char *> (&p), sizeof(patient));
}
}
outFile.close();
inFile.close();
remove("patient.dat");
rename("Temp.dat","patient.dat");
cout<<"\n\n\tRecord Deleted ..";
cin.ignore();
cin.get();
}


class doctor: public STAFF
{
    int Doc_ID;
    patient p;
    char Spz[500];

public:
     bool CheckRegNo(int n)
      {

      bool found=false;
 doctor d;
 fstream File;
 File.open("Doctor.dat",ios::binary|ios::in);
 if(!File)
 {
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
 }
    while(!File.eof() && found==false)
        {

File.read(reinterpret_cast<char *> (&d), sizeof(doctor));
if(d.Doc_ID==n)
{
    found=true;
}
        }
        File.close();
        return found;
        cin.ignore();
        cin.get();


      }
    void DoctorInfo()
    {
        staff_info();
        id:
        cout<<"Enter Doctor ID(1200-1299):";
        int m;
        cin>>m;
        if(CheckRegNo(m)==false)
        {
            Doc_ID=m;
        }
        else
        {
            cout<<"ID already taken\n";
            goto id;
        }


        cout<<"Enter Doctor Specialize :";
        cin>>Spz;
        system("pause");
    }

    void show_doctor()
    {
        cout<<"Doctor ID: "<<Doc_ID;
        show_staff();

        cout<<"\nDoctor Specialize: "<<Spz;
    }

    int  retDid()
   {
return Doc_ID;
   }

    void Prescribe_Medicine()
    {
        int n;
        cout<<"\n\n\tEnter Reg Number Of patient : "; cin>>n;
        p.modify_medicine(n);
    }


    void write_doctor()
   {
doctor d;
ofstream outFile;
outFile.open("Doctor.dat",ios::binary|ios::app);
d.DoctorInfo();
outFile.write(reinterpret_cast<char *> (&d), sizeof(doctor));

    cout<<"\n\nDoctor record Has Been Created ";
outFile.close();
cin.ignore();
   }


   void display_all_Doctor()
{
doctor d;
ifstream inFile;
inFile.open("Doctor.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&d), sizeof(doctor)))
{
d.show_doctor();
cout<<"\n\n________________________________________________________________________________\n";
}
inFile.close();
cin.ignore();
cin.get();
}


void display_d(int n)
{
doctor d;
ifstream inFile;
inFile.open("Doctor.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&d), sizeof(doctor)))
{
if(d.Doc_ID==n)
{
  d.show_doctor();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}

void modify_doctor(int n)
{
bool found=false;
doctor d;
fstream File;
File.open("Doctor.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&d), sizeof(doctor));
if(d.Doc_ID==n)
{
   d.show_doctor();
   cout<<"\n\nPlease Enter The New Details:"<<endl;
                d.DoctorInfo();
    int pos=(-1)*static_cast<int>(sizeof(d));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&d), sizeof(doctor));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void Doctor_choice()
{
    char ch;
do{
int n;
system("cls");

        cout<<"\n\n\t01. Prescribe Medicine for patient ";
cout<<"\n\n\t02. Search DOCTOR ";
cout<<"\n\n\t03. To exit.....";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        cin>>ch;

    switch(ch){
        case '1': Prescribe_Medicine();
            break;
        case '2':
            cout<<"Enter Doctor ID :";cin>>n;
                      display_d(n);
                      break;
        case '3':break;
        default :cout<<"\b";
    }
    }while(ch!='3');

}
   void Doctor_menu()
{
    char ch;
do
{
int n;
system("cls");
cout<<"\n\n\t01. INSERT DOCTOR DATA";
cout<<"\n\n\t02. Search DOCTOR ";
cout<<"\n\n\t03. ALL DOCTOR ";
cout<<"\n\n\t04. MODIFY DOCTOR DATA";
cout<<"\n\n\t05. TO EXIT............";
cout<<"\n\n\tPlease Select Your Option (1-5) ";
cin>>ch;
        system("cls");
switch(ch)
{
case '1': write_doctor();
     break;
case '2':
         cout<<"Enter Doctor ID :";cin>>n;
                      display_d(n);
                      break;
case '3':
        display_all_Doctor();
    break;
case '4':
        cout<<"Enter Doctor ID :";cin>>n;
        modify_doctor(n);
        break;
}
    }while(ch!='5');
}
};

class Nurse: public STAFF
{
    int Nurse_ID;
    char Charge_Room [50];
    patient p;
public:
       void GetNurse_Info()
    {

       cout<<"--------------------------------"<<endl;
       staff_info();
       cout<<"Enter Nurse ID:";
       cin>>Nurse_ID;
       cout<<"Enter Nurse Duty Room :";
       cin>>Charge_Room;
    }


    void Display_Nurse_Info()
    {
        cout<<"--------------------------------"<<endl;
        cout<<"Nurse ID :"<<Nurse_ID;
        show_staff();

        cout<<"\n"<<"Nurse in charge Room :"<<Charge_Room;
        cout<<endl;


    }

    void Write_Nurse_Info()
{
    Nurse n;
ofstream outFile;
outFile.open("NurseInfo.dat",ios::binary|ios::app);
n.GetNurse_Info();

outFile.write(reinterpret_cast<char *> (&n), sizeof(Nurse));
outFile.close();
    cout<<"\n\nrecord Has Been Created ";
cin.ignore();
cin.get();
}
    void display_n(int m)
{
Nurse n;
ifstream inFile;
inFile.open("NurseInfo.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&n), sizeof(Nurse)))
{
if(n.Nurse_ID==m)
{
  n.Display_Nurse_Info();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord does not exist";
cin.ignore();
cin.get();
}

  void modify_Nurse(int m)
{
bool found=false;
Nurse n;
fstream File;
File.open("NurseInfo.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&n), sizeof(Nurse));
if(n.Nurse_ID==m)
{
n.Display_Nurse_Info();
cout<<"\n\nPlease Enter The New Details of nurse"<<endl;
                n.GetNurse_Info();
    int pos=(-1)*static_cast<int>(sizeof(n));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&n), sizeof(Nurse));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record does Not Found ";
cin.ignore();
cin.get();
}

void display_all_Nurse()
{
Nurse n;
ifstream inFile;
inFile.open("NurseInfo.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&n), sizeof(Nurse)))
{
n.Display_Nurse_Info();
cout<<"\n\n________________________________________________________________________________\n";
}
inFile.close();
cin.ignore();
cin.get();
}

void Nurse_menu()
{
    char ch;

do
{
int n;
system("cls");
cout<<"\n\n\t01. INSERT NURSE DATA";
cout<<"\n\n\t02. Search NURSE ";
cout<<"\n\n\t03. ALL NURSE ";
cout<<"\n\n\t04. MODIFY NURSE DATA";
cout<<"\n\n\t05. To EXIT..........";
cout<<"\n\n\tPlease Select Your Option (1-5) ";
cin>>ch;

switch(ch)
{
case '1': Write_Nurse_Info();
     break;
case '2':
         cout<<"Enter NURSE_ID :";cin>>n;
                      display_n(n);
                      break;

case '3':

        display_all_Nurse();
    break;
case '4':
        cout<<"Enter Nurse_ID :";cin>>n;
        modify_Nurse(n);
        break;

}
    }while(ch!='5');

}

};


class Receptionist:public STAFF
{
    patient p;
    int RecID;

public:
  void RecInfo()
    {
        staff_info();
        cout<<"Enter Receptionist ID :";
        cin>>RecID;
    }
    void show_receptionist()
    {
        show_staff();
        cout<<"Receptionist ID: "<<RecID;
    }

void entry_Patient()
{
char ch;
int num;
do{
system("cls");
cout<<"\n\n\n\tENTRY MENU";
cout<<"\n\n\t1.CREATE PATIENT RECORD";
cout<<"\n\n\t2.DISPLAY ALL PATIENTS RECORDS";
cout<<"\n\n\t3.SEARCH PATIENT RECORD ";
cout<<"\n\n\t4.MODIFY PATIENT RECORD";
cout<<"\n\n\t5.DELETE PATIENT RECORD";
cout<<"\n\n\t6.TO EXIT";
cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
cin>>ch;
system("cls");

switch(ch)
{
case '1': p.write_patient();break;
case '2': p.display_all(); break;
case '3': cout<<"\n\n\tPlease Enter The reg  number "; cin>>num;
   p.display_p(num);break;
case '4': cout<<"\n\n\tPlease Enter The reg number "; cin>>num;
   p.modify_patient(num);break;
case '5': cout<<"\n\n\tPlease Enter The reg number "; cin>>num;
   p.delete_patient(num);break;

}
}while(ch!='6');
}

 void write_receptionist()
   {
Receptionist r;
ofstream outFile;
outFile.open("Receptionist.dat",ios::binary|ios::app);
r.RecInfo();
outFile.write(reinterpret_cast<char *> (&r), sizeof(Receptionist));
outFile.close();
    cout<<"\n\nReceptionist record Has Been Created ";
cin.ignore();
cin.get();
   }


   void display_all_Receptionist()
{
Receptionist r;
ifstream inFile;
inFile.open("Receptionist.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&r), sizeof(Receptionist)))
{
r.show_receptionist();
cout<<"\n\n________________________________________________________________________________\n";
}
inFile.close();
cin.ignore();
cin.get();
}


void display_r(int n)
{
Receptionist r;
ifstream inFile;
inFile.open("Receptionist.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&r), sizeof(Receptionist)))
{
if(r.RecID==n)
{
  r.show_receptionist();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}

void modify_receptionist(int n)
{
bool found=false;
Receptionist r;
fstream File;
File.open("Receptionist.dat",ios::binary|ios::in|ios::out);
if(!File)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
    while(!File.eof() && found==false)
{

File.read(reinterpret_cast<char *> (&r), sizeof(Receptionist));
if(r.RecID==n)
{
   r.show_receptionist();
   cout<<"\n\nPlease Enter The New Details "<<endl;
    r.RecInfo();
    int pos=(-1)*static_cast<int>(sizeof(r));
    File.seekp(pos,ios::cur);
    File.write(reinterpret_cast<char *> (&r), sizeof(Receptionist));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
File.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}


void Receptionist_menu()
{
    char ch;

do
{
int n;
system("cls");
cout<<"\n\n\t01. INSERT Receptionist DATA";
cout<<"\n\n\t02. Search Receptionist ";
cout<<"\n\n\t03. ALL Receptionist ";
cout<<"\n\n\t04. MODIFY Receptionist DATA";
cout<<"\n\n\t05. To EXIT..........";
cout<<"\n\n\tPlease Select Your Option: ";
cin>>ch;
switch(ch){
case '1': write_receptionist();
     break;
case '2':
         cout<<"Enter Receptionist ID :";cin>>n;
                      display_r(n);
                      break;
case '3':
        display_all_Receptionist();
    break;
case '4':
        cout<<"Enter Receptionist ID :";cin>>n;
        modify_receptionist(n);
        break;

}
    }while(ch!='5');
}
};

class store_manager:public STAFF
{
    private:
        string product_Name;
        string supplier_Name;
        int unit;
        int bill;
        int SID;

    public:

       void SInfo()
    {
        staff_info();
        cout<<"Enter Receptionist ID :";
        cin>>SID;
    }

    void show_StoreManager()
    {
        show_staff();
        cout<<"Store Manager ID: "<<SID;

    }

       void orderproducts()
       {
         cout<<"\n\n|----------- ORDER Products & SUPPLIES ----------|"<<endl<<endl;

         cout<<"Enter Product Name: ";
         cin>>product_Name;
         cout<<"\nEnter Supplier's Name: ";
         cin>>supplier_Name;
         cout<<"\nEnter Number of Unit: ";
         cin>>unit;
         cout<<"\nEnter Total bill: ";
         cin>>bill;
         ofstream fout;
         fout.open("Products&Supplies.txt",ios::app);
        fout<<"Product Name: "<< product_Name<<endl;
        fout<<"Supplier's Name: "<< supplier_Name<<endl;
        fout<<"Number of Unit: "<< unit<<endl;
        fout<<"Total Bill: "<< bill<<endl<<endl;
         fout.close();
        cout<<"\n\nPRODUCT ORDERED SUCCESSFULLY!!"<<endl<<endl;
        int choice;
        cout<<"Do you want to order more?"<<endl;
        cout<<"(1) Yes"<<endl;
        cout<<"(2) No"<<endl<<endl<<endl;
        cin>>choice;

    if(choice==1)
    {
        system("cls");
        orderproducts();
    }
    else
    {
        return;
    }
}

  void readFromFile()
{
    ifstream fin;
    fin.open("Products&Supplies.txt");

    string str;
    if(!fin)
    {
        cout<<"\nERROR LOADING FILE!!"<<endl;
        return;
    }
    else
    {
        while(!fin.eof())
        {
            getline(fin,str);
            cout<<str;
            cout<<endl;
        }
    }
    cout<<endl<<endl<<endl;
    fin.close();
    cin.get();
    system("pause");
}


void write_store_manager()
   {
store_manager s;
ofstream outFile;
outFile.open("StoreManager.dat",ios::binary|ios::app);
s.SInfo();
outFile.write(reinterpret_cast<char *> (&s), sizeof(store_manager));
outFile.close();
    cout<<"\n\nrecord Has Been Created ";
cin.ignore();
cin.get();
   }

   void display_all_storeManager()
{
store_manager s;
ifstream inFile;
inFile.open("StoreManager.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
while(inFile.read(reinterpret_cast<char *> (&s), sizeof(store_manager)))
{
s.show_StoreManager();
cout<<"\n\n________________________________________________________________________________\n";
}
inFile.close();
cin.ignore();
cin.get();
}

void display_s(int n)
{
store_manager s;
ifstream inFile;
inFile.open("StoreManager.dat",ios::binary);
if(!inFile)
{
cout<<"File could not be open !! Press any Key...";
cin.ignore();
cin.get();
return;
}
bool flag=false;
while(inFile.read(reinterpret_cast<char *> (&s), sizeof(store_manager)))
{
if(s.SID==n)
{
  s.show_StoreManager();
flag=true;
}
}
inFile.close();
if(flag==false)
cout<<"\n\nrecord not exist";
cin.ignore();
cin.get();
}

void store_manager_choice()
{

    char ch;

    do
{
int n;
system("cls");

        cout<<"\n\n\t01. Order Products ";
cout<<"\n\n\t02. Show Order Products & Bills ";
cout<<"\n\n\t03. To exit.....";
        cout<<"\n\n\tPlease Select Your Option (1-3) ";
        cin>>ch;

switch(ch)
{
case '1':
         orderproducts();
     break;
case '2':
         readFromFile();
                      break;
            case '3':break;
default :cout<<"\b";
}
    }while(ch!='3');


}

void store_manager_menu()
{
    char ch;

do
{
int n;
system("cls");

cout<<"\n\n\t01. INSERT STORE MANAGER DATA";
cout<<"\n\n\t02. Search STORE MANAGER ";
cout<<"\n\n\t03. ALL STORE MANAGER ";
cout<<"\n\n\t04. To exit this menu";
cout<<"\n\n\tPlease Select Your Option: ";
cin>>ch;

switch(ch)
{
case '1': write_store_manager();
     break;
case '2':
         cout<<"Enter STORE MANAGER ID :";cin>>n;
                      display_s(n);
                      break;

case '3':

        display_all_storeManager();
    break;

case '4':break;
default :cout<<"\b";
}
    }while(ch!='4');

}

};

class Admin
{
  doctor d;
  patient p;
  Receptionist r;
  store_manager s;
  Nurse n;

  public:
    void staff_menu()
    {
        char ch;
        do{
system("cls");
cout<<"\n\n\tStaff Menu";
cout<<"\n\n\t1.Doctor";
cout<<"\n\n\t2.Nurse";
cout<<"\n\n\t3.Receptionist";
cout<<"\n\n\t4.Store Manger";
cout<<"\n\n\t5.TO EXIT";
cout<<"\n\n\tPlease Enter Your Choice (1-4) ";
cin>>ch;
system("cls");

switch(ch)
 {
  case '1': d.Doctor_menu();break;
  case '2': n.Nurse_menu(); break;
  case '3':    r.Receptionist_menu();break;
  case '4':    s.store_manager_menu();break;

 }
}while(ch!='5');

    }

};

int main()
{
cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t============================================\n";
cout<<"\t\t\t\t\t _______________________________________________________________ \n";
cout<<"\t\t\t\t\t||                                            		       ||\n";
cout<<"\t\t\t\t\t||                                           		       ||\n";
cout<<"\t\t\t\t\t||                                           		       ||\n";
cout<<"\t\t\t\t\t||                                           		       ||\n";
cout<<"\t\t\t\t\t||                                           		       ||\n";
cout<<"\t\t\t\t\t||                               WELCOME TO                    ||\n";
cout<<"\t\t\t\t\t||                              IIITDM KURNOOL                 ||\n";
cout<<"\t\t\t\t\t||                           HOSPITAL MANAGEMENT SYSTEM        ||\n";
cout<<"\t\t\t\t\t||                                                             ||\n";
cout<<"\t\t\t\t\t||                                                             ||\n";
cout<<"\t\t\t\t\t||                                                             ||\n";
cout<<"\t\t\t\t\t||                                                             ||\n";
cout<<"\t\t\t\t\t================================================================\n\n\n\n\t\t\t\t\t";
system("pause");
system("cls");

    Admin a;
    Receptionist r;
    doctor d;
    store_manager s;
    int ch;
    char pass[15];
    do{
    cout<<"\t\t____________________________\n";
    cout<<"\t\t1.Admin\n";
    cout<<"\t\t2.Receptionist\n";
    cout<<"\t\t3.Doctor\n";
    cout<<"\t\t4.Store Manager\n";
    cout<<"\t\t5.Exit From The SYSTEM\n";
    cout<<"\t\t____________________________\n";

    cin>>ch;
    switch(ch){
        case 1:
                 login1:
                 cout<<"Enter ADMIN password: ";
                 cin>>pass;
                 if(strcmp(pass,"admin")==0)
                 {
                   a.staff_menu();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    goto login1;
                 }
                 break;
        case 2:
                 login2:
                 cout<<"Enter Receptionist password: ";

                 cin>>pass;

                 if(strcmp(pass,"receptionist")==0)
                 {
                   r.entry_Patient();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    goto login2;
                 }
                break;
        case 3:

                 login3:
                 cout<<"Enter Doctor password: ";

                 cin>>pass;

                 if(strcmp(pass,"doctor")==0)
                 {
                   d.Doctor_choice();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    goto login3;
                 }
                 break;
        case 4:
                 login4:
                 cout<<"Enter STORE MANAGER password: ";

                 cin>>pass;
                 if(strcmp(pass,"store")==0)
                 {
                   s.store_manager_choice();
                 }
                 else
                 {
                    cout<<"WRONG PASSWORD!!!\n";
                    goto login4;
                 }
                 break;
            }
    }while(ch!=5);
}
