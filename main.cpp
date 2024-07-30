// #include <iostream>
// #include <fstream>
// #include <windows.h>
// #include <sstream>
// using namespace std;

// class Hostel
// {
// private:
//     string Name;
//     int Rent, Bed;

// public:
//     Hostel(string name, int rent, int bed)
//     {
//         Name = name;
//         Bed = bed;
//         Rent = rent;
//     }
//     string getName(){
//         return Name;
//     }
//     int getRent(){
//         return Rent;
//     }
//     int getBed(){
//         return Bed;
//     }
//     void reserve(){
//         ifstream in("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
//         ofstream out("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Temp.txt");

//         string line;
//         while(getline(in,line)){
//             int pos=line.find("Sarojini");
//             if(pos !=string::npos){
//                 int bed = bed-1;
//                 Bed=bed;
//                 stringstream ss;
//                 ss<<bed;
//                 string strBed= ss.str();
//                 int bedPos=line.find_last_of(':');
//                 line.replace(bedPos+1, string::npos, strBed);

//             }
//             out<<line<<endl;
//         }
//         out.close();
//         in.close();
//         remove("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
//         rename("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Temp.txt", "C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
//         cout<<"\tBed reserved successfully"<<endl;
//     }
// };

// class Student{
//    private:
//     string Name, RollNo, Address;
//     public:
//     Student():Name(""),RollNo(""),Address(""){  }
//      void setName(string name){
//      Name=name;
//     }
//     void setRollNo(string rollNo){
//         RollNo=rollNo;
//     }
//     void setAddress(string address){
//         Address=address;
//     }
//     string getName(){
//         return Name;
//     }
//     string getRollNo(){
//         return RollNo;
//     }
//     string getAddress(){
//         return Address;
//     }
// };

// int main(){
//    Hostel h("Sarojini", 5000, 2);
//    ofstream out("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");

//    out<<"\t"<<h.getName()<<" : "<<h.getRent()<<" : "<<h.getBed()<<endl;
//    cout<<"Hostel Data Saved"<<endl;
//    out.close();// for closing file

//    Student s;
//    bool exit=false;
//    while(!exit){
//      system("cls");
//      int val;
//      cout<<"\t*******************************"<<endl;
//      cout<<"\t1.Reserve A Bed."<<endl;
//      cout<<"\t2.Exit"<<endl;
//      cout<<"\tEnter Choice: ";
//      cin>>val;

//      if(val==1){
//         system("cls");// for hiding previous output;
//         string name, rollno, address;
//         cout<<"\tEnter name of Student:";
//         cin>>name;
//         s.setName(name);
//         cout<<"\tEnter Rollno of Student";
//         cin>>rollno;
//         s.setRollNo(rollno);
//         cout<<"\t Enter Address of student";
//         cin>>address;
//         s.setAddress(address);

//         if(h.getBed()>0){
//             h.reserve();
//         }
//         else if(h.getBed()==0){
//             cout<<"\tSorry, no bed available!!"<<endl;

//         }
//         ofstream outFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Student.txt", ios::app);
//         outFile<<"\t"<<s.getName()<<"  :  "<<s.getRollNo()<<" : "<<s.getAddress()<<endl;
//         Sleep(5000);
//      }
//      else if(val==2){
//         system("cls");
//         exit=true;
//         cout<<"Good luck"<<endl;
//         Sleep(3000);
//      }
//    }
// }


#include <iostream>
#include <fstream>
#include <windows.h>
#include <sstream>
using namespace std;

class Hostel
{
private:
    string Name;
    int Rent, Bed;

public:
    Hostel(string name, int rent, int bed)
    {
        Name = name;
        Bed = bed;
        Rent = rent;
    }

    string getName()
    {
        return Name;
    }

    int getRent()
    {
        return Rent;
    }

    int getBed()
    {
        return Bed;
    }

    void setBed(int bed)
    {
        Bed = bed;
    }

    bool reserve()
    {
        ifstream in("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
        ofstream out("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Temp.txt");

        bool reserved = false;
        string line;
        while (getline(in, line))
        {
            int pos = line.find(Name);
            if (pos != string::npos && Bed > 0)
            {
                // Decrement the bed count
                Bed -= 1;
                stringstream ss;
                ss << Bed;
                string strBed = ss.str();

                // Find the position of the last ':' and replace the bed count
                int bedPos = line.find_last_of(':');
                line.replace(bedPos + 1, string::npos, strBed);
                reserved = true;
            }
            out << line << endl;
        }
        out.close();
        in.close();
        remove("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
        rename("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Temp.txt", "C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");

        if (reserved)
        {
            cout << "\tBed reserved successfully" << endl;
        }
        else
        {
            cout << "\tSorry, no bed available or error occurred!!" << endl;
        }
        return reserved;
    }
};

class Student
{
private:
    string Name, RollNo, Address;

public:
    Student() : Name(""), RollNo(""), Address("") {}

    void setName(string name)
    {
        Name = name;
    }

    void setRollNo(string rollNo)
    {
        RollNo = rollNo;
    }

    void setAddress(string address)
    {
        Address = address;
    }

    string getName()
    {
        return Name;
    }

    string getRollNo()
    {
        return RollNo;
    }

    string getAddress()
    {
        return Address;
    }
};

int main()
{
    // Initialize number of beds
    int initialBeds = 3;
    int availableBeds = initialBeds;
    string hostelName = "Sarojini";
    int rent = 5000;

    // Read the number of available beds from the file if it exists
    ifstream inFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
    if (inFile.is_open())
    {
        string line;
        if (getline(inFile, line))
        {
            int pos = line.find_last_of(':');
            if (pos != string::npos)
            {
                string bedCount = line.substr(pos + 1);
                availableBeds = stoi(bedCount);
            }
        }
        inFile.close();
    }

    Hostel h(hostelName, rent, availableBeds);

    ofstream out("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
    out << "\t" << h.getName() << " : " << h.getRent() << " : " << h.getBed() << endl;
    cout << "Hostel Data Saved" << endl;
    out.close(); // for closing file

    Student s;
    bool exit = false;
    while (!exit)
    {
        system("cls");
        int val;
        cout << "\t*******************************" << endl;
        cout << "\t1. Reserve A Bed." << endl;
        cout << "\t2. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls"); // for hiding previous output;
            string name, rollno, address;
            cout << "\tEnter name of Student: ";
            cin >> name;
            s.setName(name);
            cout << "\tEnter Rollno of Student: ";
            cin >> rollno;
            s.setRollNo(rollno);
            cout << "\tEnter Address of student: ";
            cin >> address;
            s.setAddress(address);

            if (h.getBed() > 0 && h.reserve())
            {
                ofstream outFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Student.txt", ios::app);
                outFile << "\t" << s.getName() << "  :  " << s.getRollNo() << " : " << s.getAddress() << endl;
                outFile.close();
            }
            else
            {
                cout << "\tSorry, no bed available!!" << endl;
            }
            Sleep(5000);
        }
        else if (val == 2)
        {
            system("cls");
            exit = true;
            cout << "Good luck" << endl;
            Sleep(3000);
        }
    }

    // Update the file with the final number of beds before exiting
    ofstream finalOut("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel.txt");
    finalOut << "\t" << h.getName() << " : " << h.getRent() << " : " << h.getBed() << endl;
    finalOut.close();

    return 0;
}
