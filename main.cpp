#include <iostream>  // Include the input-output stream library for cin, cout, etc.
#include <fstream>   // Include file stream library for file operations
#include <sstream>   // Include string stream library for string manipulation
#include <limits.h>  // Include limits library for constants like PATH_MAX
#include <unistd.h>  // Include POSIX library for getcwd function
#include <windows.h> // Include Windows library for Sleep function
using namespace std; // Use the standard namespace

// Define a class named Hostel
class Hostel
{
private:
    string Name;            // Name of the hostel
    int Rent;               // Rent per bed in the hostel
    int Bed;                // Number of available beds
    int TotalRentCollected; // Total rent collected

public:
    // Constructor to initialize the hostel data
    Hostel(string name, int rent, int bed)
    {
        Name = name;
        Bed = bed;
        Rent = rent;
        TotalRentCollected = 0;
    }

    // Getter function for hostel name
    string getName()
    {
        return Name;
    }

    // Getter function for rent
    int getRent()
    {
        return Rent;
    }

    // Getter function for number of beds
    int getBed()
    {
        return Bed;
    }

    // Setter function for number of beds
    void setBed(int bed)
    {
        Bed = bed;
    }

    // Getter function for total rent collected
    int getTotalRentCollected()
    {
        return TotalRentCollected;
    }

    // Function to update the total rent collected
    void updateTotalRentCollected(int amount)
    {
        TotalRentCollected += amount;
    }

    // Function to reserve a bed for a student and update files accordingly
    bool reserve(string studentName, string rollNo, const string &filePath)
    {
        ifstream in(filePath + "Hostel.txt"); // Open the hostel data file for reading
        ofstream out(filePath + "Temp.txt");  // Open a temporary file for writing updates

        bool reserved = false; // Flag to indicate if the reservation was successful
        string line;
        while (getline(in, line)) // Read each line of the hostel data file
        {
            int pos = line.find(Name);          // Find the position of the hostel name in the line
            if (pos != string::npos && Bed > 0) // If the hostel name is found and there are available beds
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
            out << line << endl; // Write the updated line to the temporary file
        }
        out.close();                                                                // Close the temporary file
        in.close();                                                                 // Close the hostel data file
        remove((filePath + "Hostel.txt").c_str());                                  // Remove the original hostel data file
        rename((filePath + "Temp.txt").c_str(), (filePath + "Hostel.txt").c_str()); // Rename the temporary file to the original file name

        if (reserved) // If the reservation was successful
        {
            // Log rent information to Rent.txt
            ofstream rentOut(filePath + "Rent.txt", ios::app);
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

    // Function to handle the return of rent and bed
    bool returnRent(string rollNo, const string &filePath)
    {
        ifstream inFile(filePath + "Student.txt"); // Open the student data file for reading
        ofstream tempFile(filePath + "Temp.txt");  // Open a temporary file for writing updates

        bool found = false; // Flag to indicate if the student was found
        string line, studentName;
        while (getline(inFile, line)) // Read each line of the student data file
        {
            if (line.find(rollNo) == string::npos) // If the roll number is not found in the line
            {
                tempFile << line << endl; // Write the line to the temporary file
            }
            else
            {
                found = true; // Student found
                int pos = line.find(':');
                studentName = line.substr(0, pos);
            }
        }
        inFile.close();   // Close the student data file
        tempFile.close(); // Close the temporary file

        if (found) // If the student was found
        {
            // Remove student entry from the Student.txt file
            remove((filePath + "Student.txt").c_str());
            rename((filePath + "Temp.txt").c_str(), (filePath + "Student.txt").c_str());

            // Increment the bed count in memory
            Bed += 1;

            // Update Hostel.txt file
            ifstream hostelFile(filePath + "Hostel.txt");
            ofstream tempHostelFile(filePath + "TempHostel.txt");

            while (getline(hostelFile, line))
            {
                int pos = line.find(Name);
                if (pos != string::npos)
                {
                    stringstream ss;
                    ss << Bed;
                    string strBed = ss.str();

                    int bedPos = line.find_last_of(':');
                    line.replace(bedPos + 1, string::npos, strBed);
                }
                tempHostelFile << line << endl;
            }
            hostelFile.close();
            tempHostelFile.close();

            remove((filePath + "Hostel.txt").c_str());
            rename((filePath + "TempHostel.txt").c_str(), (filePath + "Hostel.txt").c_str());

            // Remove entry from Rent.txt
            ifstream rentFile(filePath + "Rent.txt");
            ofstream tempRentFile(filePath + "TempRent.txt");

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

            remove((filePath + "Rent.txt").c_str());
            rename((filePath + "TempRent.txt").c_str(), (filePath + "Rent.txt").c_str());
            cout << "\tRent return  successfully." << endl;

            return true;
        }
        else
        {
            cout << "\tNot a valid student!" << endl;
            return false;
        }
    }
};

// Define a class named Student
class Student
{
private:
    string Name, RollNo, Address; // Student's name, roll number, and address

public:
    // Default constructor
    Student() : Name(""), RollNo(""), Address("") {}

    // Setter function for student's name
    void setName(string name)
    {
        Name = name;
    }

    // Setter function for student's roll number
    void setRollNo(string rollNo)
    {
        RollNo = rollNo;
    }

    // Setter function for student's address
    void setAddress(string address)
    {
        Address = address;
    }

    // Getter function for student's name
    string getName()
    {
        return Name;
    }

    // Getter function for student's roll number
    string getRollNo()
    {
        return RollNo;
    }

    // Getter function for student's address
    string getAddress()
    {
        return Address;
    }
};

// Function to take hostel complaints and save them to a file
void takeHostelComplaint(const string &filePath)
{
    string complaint;
    cout << "\tEnter your hostel complaint: ";
    cin.ignore();            // Ignore the newline character left by previous input
    getline(cin, complaint); // Get the complaint from user

    ofstream outFile(filePath + "HostelComplaint.txt", ios::app); // Open file for appending
    outFile << complaint << endl;                                 // Write the complaint to the file
    outFile.close();                                              // Close the file
    cout << "\tHostel complaint recorded successfully." << endl;
}

// Function to take mess complaints and save them to a file
void takeMessComplaint(const string &filePath)
{
    string complaint;
    cout << "\tEnter your mess complaint: ";
    cin.ignore();            // Ignore the newline character left by previous input
    getline(cin, complaint); // Get the complaint from user

    ofstream outFile(filePath + "MessComplaint.txt", ios::app); // Open file for appending
    outFile << complaint << endl;                               // Write the complaint to the file
    outFile.close();                                            // Close the file
    cout << "\tMess complaint recorded successfully." << endl;
}

int main()
{
    // Get the current working directory
    char temp[PATH_MAX];
    if (getcwd(temp, sizeof(temp)) == nullptr)
    {
        cerr << "Error getting current working directory" << endl;
        return 1;
    }
    string currentPath(temp);

    // Replace single backslashes with double backslashes
    for (size_t pos = 0; pos < currentPath.size(); ++pos)
    {
        if (currentPath[pos] == '\\')
        {
            currentPath.insert(pos, "\\");
            ++pos; // Move past the inserted backslash
        }
    }
    currentPath.insert(currentPath.size(), "\\");
    currentPath.insert(currentPath.size(), "\\");
    string filePath = currentPath; // Path for file operations

    // Initialize number of beds and other hostel details
    int initialBeds = 2;
    int availableBeds = initialBeds;
    string hostelName = "Sarojini";
    int rent = 5000;

    // Read the number of available beds from the file if it exists
    ifstream inFile(filePath + "Hostel.txt");
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

    // Create a Hostel object
    Hostel h(hostelName, rent, availableBeds);

    // Write hostel data to Hostel.txt
    ofstream out(filePath + "Hostel.txt");
    out << "\t" << h.getName() << " : " << h.getRent() << " : " << h.getBed() << endl;
    cout << "Hostel Data Saved" << endl;
    out.close(); // Close the file

    Student s;         // Create a Student object
    bool exit = false; // Flag to exit the loop
    while (!exit)
    {
        system("cls"); // Clear the console screen
        int val;
        cout << "\t*******************************" << endl;
        cout << "\t1. Reserve A Bed." << endl;
        cout << "\t2. HostelComplaint" << endl;
        cout << "\t3. MessComplaint" << endl;
        cout << "\t4. Refund" << endl;
        cout << "\t5. Exit" << endl;
        cout << "\tEnter Choice: ";
        cin >> val; // Get the user's choice

        if (val == 1)
        {
            system("cls"); // Clear the console screen
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

            // Reserve a bed for the student
            if (h.getBed() > 0 && h.reserve(name, rollno, filePath))
            {
                ofstream outFile(filePath + "Student.txt", ios::app); // Append student details to the file
                outFile << "\t" << s.getName() << "  :  " << s.getRollNo() << " : " << s.getAddress() << endl;
                outFile.close();
            }
            else
            {
                cout << "\tSorry, no bed available!!" << endl;
            }
            Sleep(3000); // Wait for 3 seconds
        }
        else if (val == 2)
        {
            system("cls");                 // Clear the console screen
            takeHostelComplaint(filePath); // Record hostel complaint
            Sleep(3000);                   // Wait for 3 seconds
        }
        else if (val == 3)
        {
            system("cls");               // Clear the console screen
            takeMessComplaint(filePath); // Record mess complaint
            Sleep(3000);                 // Wait for 3 seconds
        }
        else if (val == 4)
        {
            system("cls"); // Clear the console screen
            string rollNo;
            cout << "\tEnter RollNo to return bed: ";
            cin >> rollNo;
            h.returnRent(rollNo, filePath); // Process bed return and rent refund
            Sleep(3000);                    // Wait for 3 seconds
        }
        else if (val == 5)
        {
            exit = true; // Set exit flag to true to break the loop
            cout << "\tGood Luck ";
            Sleep(3000); // Wait for 3 seconds
        }
        else
        {
            cout << "\tInvalid choice! Please try again." << endl; // Invalid choice message
        }
    }
    return 0; // End of program
}
