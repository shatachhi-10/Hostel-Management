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
    int TotalRentCollected;

public:
    Hostel(string name, int rent, int bed)
    {
        Name = name;
        Bed = bed;
        Rent = rent;
        TotalRentCollected = 0;
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

    int getTotalRentCollected()
    {
        return TotalRentCollected;
    }

    void updateTotalRentCollected(int amount)
    {
        TotalRentCollected += amount;
    }

    bool reserve(string studentName, string rollNo)
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
            // Log rent information
            ofstream rentOut("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Rent.txt", ios::app);
            rentOut << studentName << " (" << rollNo << ") : " << Rent << endl;
            rentOut.close();

            // Update total rent collected
            updateTotalRentCollected(Rent);

            cout << "\tBed reserved successfully" << endl;
        }
        else
        {
            cout << "\tSorry, no bed available or error occurred!!" << endl;
        }
        return reserved;
    }

    bool returnBed(string rollNo)
    {
        ifstream inFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Student.txt");
        ofstream tempFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Temp.txt");

        bool found = false;
        string line, studentName;
        while (getline(inFile, line))
        {
            if (line.find(rollNo) == string::npos)
            {
                tempFile << line << endl;
            }
            else
            {
                found = true;
                int pos = line.find(':');
                studentName = line.substr(0, pos);
            }
        }
        inFile.close();
        tempFile.close();

        if (found)
        {
            remove("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Student.txt");
            rename("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Temp.txt", "C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Student.txt");

            // Increment the bed count
            Bed += 1;

            // Remove entry from Rent.txt
            ifstream rentFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Rent.txt");
            ofstream tempRentFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\TempRent.txt");

            string rentLine;
            while (getline(rentFile, rentLine))
            {
                if (rentLine.find(rollNo) == string::npos)
                {
                    tempRentFile << rentLine << endl;
                }
                else
                {
                    int pos = rentLine.find_last_of(':');
                    string rentAmountStr = rentLine.substr(pos + 2);
                    int rentAmount = stoi(rentAmountStr);
                    updateTotalRentCollected(-rentAmount);
                }
            }
            rentFile.close();
            tempRentFile.close();

            remove("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Rent.txt");
            rename("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\TempRent.txt", "C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Rent.txt");

            return true;
        }
        else
        {
            cout << "\tNot a valid student!" << endl;
            return false;
        }
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

void takeHostelComplaint()
{
    string complaint;
    cout << "\tEnter your hostel complaint: ";
    cin.ignore(); // to ignore the newline character left by previous input
    getline(cin, complaint);

    ofstream outFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Hostel Complaint.txt", ios::app);
    outFile << complaint << endl;
    outFile.close();
    cout << "\tHostel complaint recorded successfully." << endl;
}

void takeMessComplaint()
{
    string complaint;
    cout << "\tEnter your mess complaint: ";
    cin.ignore(); // to ignore the newline character left by previous input
    getline(cin, complaint);

    ofstream outFile("C:\\Users\\shata\\OneDrive\\Desktop\\HostelManagement\\Mess Complaint.txt", ios::app);
    outFile << complaint << endl;
    outFile.close();
    cout << "\tMess complaint recorded successfully." << endl;
}

int main()
{
    // Initialize number of beds
    int initialBeds = 2;
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
        cout << "\t2. Hostel Complaint" << endl;
        cout << "\t3. Mess Complaint" << endl;
        cout << "\t4. Return" << endl;
        cout << "\t5. Exit" << endl;
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

            if (h.getBed() > 0 && h.reserve(name, rollno))
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
            takeHostelComplaint();
            Sleep(3000);
        }
        else if (val == 3)
        {
            system("cls");
            takeMessComplaint();
            Sleep(3000);
        }
        else if (val == 4)
        {
            system("cls");
            string rollno;
            cout << "\tEnter Rollno of Student: ";
            cin >> rollno;

            if (h.returnBed(rollno))
            {
                cout << "\tBed returned successfully!" << endl;
            }
            else
            {
                cout << "\tReturn operation failed or student not found!" << endl;
            }
            Sleep(5000);
        }
        else if (val == 5)
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

    cout << "Total Rent Collected: " << h.getTotalRentCollected() << endl;

    return 0;
}
