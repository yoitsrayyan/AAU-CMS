/*
AAU Course Manager (AAU-CMS)
BY :
[+] Rayyan Mohammad Farouq Saleh         (202510096)"
[+] Hisham Mahmoud Muhammad Al-Nassour   (202510419)"
[+] Aya Abdallah Shilpaeyh               (202420849)"
[+] Joud Raed Al-Saudi                   (202511110)"
*/
#include <iostream>
#include <string>
using namespace std;


//Main class:
class Course {
    protected:
        string courseCode, courseName;
        int maxCapacity, currentStudents;

    public:
    Course(string code, string name, int maxCap) {courseCode = code; courseName = name; maxCapacity = maxCap; currentStudents = 0; }

    bool isFull() {
        if (currentStudents >= maxCapacity) {
            return true;
        } else {
            return false;
        }
    }

    void incrementStudents() { currentStudents++; }

    void decrementStudents() { currentStudents--; }

    virtual void courseDetails() = 0; // = 0 means pure virtual so no code here and all child classes must override it
};


//Online Courses class:
class OnlineCourse : public Course {
    private:
        string meetingLink;

    public:
        OnlineCourse(string code, string name, int maxCap, string link) : Course(code, name, maxCap) { meetingLink = link; }

        void courseDetails() override { 
            cout << " Course Details: " << endl;
            cout << " Course Code: " << courseCode << endl;
            cout << " Course Name: " << courseName << endl;
            cout << " Max Capacity: " << maxCapacity << endl;
            cout << " Current Students: " << currentStudents << endl;
            cout << " Meeting Link: " << meetingLink << endl;
        }
};


//Offline Courses class:
class OfflineCourse : public Course {
    private:
        string roomNumber, buildingName;

    public:
        OfflineCourse(string code, string name, int maxCap, string building, string roomNum) : Course(code, name, maxCap) { 
            roomNumber = roomNum;
            buildingName = building;
        }

        void courseDetails() override { 
            cout << " Course Details: " << endl;
            cout << " Course Code: " << courseCode << endl;
            cout << " Course Name: " << courseName << endl;
            cout << " Max Capacity: " << maxCapacity << endl;
            cout << " Current Students: " << currentStudents << endl;
            cout << " Building Name: " << buildingName << endl;
            cout << " Room Number: " << roomNumber << endl;
        }
};


//Student Class
class Student {
    private:
        string studentID, studentName;
        Course* registeredCourses[6]; // array of pointers to hold both online and offline courses
        int courseCount; // counter to know how many courses are registered

    public:
        // Constructor
        Student(string id, string name) {
            studentID = id; 
            studentName = name; 
            courseCount = 0; // schedule starts empty
        }

        // Register a course
        
        void registerCourse(Course* course) {
            if (hasCourse(course)) {
                cout << "\nError: You are already registered in this course!\n";
                return;
            }
            if (courseCount >= 6) {
                cout << "Sorry! Your schedule is full, max 6 courses allowed!" << endl;
                return;
            }
            if (course->isFull()) {
                cout << "Sorry! This course is already full!" << endl;
                return;
            }
            
            // If everything is okay, add the course
            registeredCourses[courseCount] = course;
            courseCount++; // increment student's courses
            course->incrementStudents(); // increment course's total students
            cout << "Course registered successfully!" << endl;
        }

        // Drop a course
        void dropCourse(Course* course) {
            for (int i = 0; i < courseCount; i++) {
                if (registeredCourses[i] == course) {
                    for (int j = i; j < courseCount - 1; j++) {
                        registeredCourses[j] = registeredCourses[j + 1];
                    }
                    courseCount--; 
                    course->decrementStudents(); 
                    cout << "Course dropped successfully!" << endl;
                    return;
                }
            }
            cout << "Course not found in your schedule!" << endl;
        }

        int getCourseCount() { return courseCount; }
        Course* getRegisteredCourse(int index) { return registeredCourses[index]; }

        bool hasCourse(Course* course) {
            for (int i = 0; i < courseCount; i++) {
                if (registeredCourses[i] == course) {
                return true;
            }
        }
        return false;
        }

        // Print student schedule
        void printSchedule() {
            cout << "\n==================================================" << endl;
            cout << " Student Name: " << studentName << " | ID: " << studentID << endl;
            cout << " Registered Courses: " << courseCount << " / 6" << endl;
            cout << "==================================================" << endl;
            
            if (courseCount == 0) {
                cout << " Your schedule is empty! Go register some courses." << endl;
                return;
            }

            for (int i = 0; i < courseCount; i++) {
                // It will print online details or offline details automatically depending on the course type
                registeredCourses[i]->courseDetails();
                cout << "--------------------------------------------------" << endl;
            }
        }
};

// External Function Prototypes
void showMenu();
void handleRegistration(Student* &student, bool &isInfoHere, string &sName, string &sID, Course* availableCourses[]);
void handleDrop(Student* &student, bool &isInfoHere, string &sName, string &sID, Course* availableCourses[]);
void handlePrint(Student* &student, bool &isInfoHere, string &sName, string &sID);
void showCredit();

int main() {
    string sName, sID;
    int choice;
    bool isInfoHere = false;

    // Define a pointer for the student object initialized to nullptr
    Student* student = nullptr;

    // Array of pointers to hold 4 available university courses allocated on the Heap
    Course* availableCourses[4];
    availableCourses[0] = new OnlineCourse("CS211", "Object Oriented Programming", 150, "https://zoom.us/j/aau-oop");
    availableCourses[1] = new OfflineCourse("CS212", "Data Structures", 200, "IT Building", "Room 302");
    availableCourses[2] = new OnlineCourse("CS311", "Database Systems", 130, "https://zoom.us/j/aau-database");
    availableCourses[3] = new OfflineCourse("CS213", "Computer Graphics", 120, "Engineering Building", "Lab 101");

    // Infinite System Loop
    while (true) {
        showMenu();
        cout << "Please enter your choice (1-5): ";
        cin >> choice;

        // Input validation to prevent infinite loops when entering characters instead of integers
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nWrong Input! Please enter a number not a character :0\n";
            cout << "Press Enter to try again... ";
            cin.get();
            continue;
        }

        switch (choice) {
            case 1:
                // Call registration function passing variables by reference
                handleRegistration(student, isInfoHere, sName, sID, availableCourses);
                break;

            case 2:
                // Call course dropping function
                handleDrop(student, isInfoHere, sName, sID, availableCourses);
                break;

            case 3:
                // Call schedule printing function
                handlePrint(student, isInfoHere, sName, sID);
                break;

            case 4:
                cout << "\nThank you for using AAU-CMS! Goodbye! :P\n";
                
                // Memory Cleanup to prevent memory leaks in the Heap
                for (int i = 0; i < 4; i++) {
                    delete availableCourses[i];
                }
                if (student != nullptr) {
                    delete student;
                }
                return 0; // Terminate the program cleanly

            case 5:
                // Display developers credits
                showCredit();
                break;

            default:
                cout << "\nInvalid choice! Please enter a number between 1 and 5 :0\n";
                cout << "Press Enter to continue... ";
                cin.get();
        }
    }

    return 0;
}


// 1. Function to show the main menu for AAU
void showMenu() {
    cout << "======================================================================================================" << endl;
    cout << "" << endl;
    cout << "             mmmmmm       mmmmmm     ##    ##               mmmmmm    mmm  mmm     mmmmmm   " << endl;
    cout << "            m##\"\"##m     m##\"\"##m    ##    ##              m##\"\"\"\"    ###  ###    m##\"\"\"\"   " << endl;
    cout << "            ##    ##     ##    ##    ##    ##              ##         ########    \"####m    " << endl;
    cout << "            ########     ########    ##    ##    mmmmmm    ##         ## ## ##     \"\"\"##m   " << endl;
    cout << "            ##\"\"\"\"##     ##\"\"\"\"##    ##    ##    \"\"\"\"\"\"    ##         ## \"\" ##        \"##   " << endl;
    cout << "            ##    ##     ##    ##    \"##mm##\"              \"##mmmm    ##    ##    ##mmm##   " << endl;
    cout << "            \"\"    \"\"     \"\"    \"\"     \"\"\"\"\"\"                \"\"\"\"\"\"    \"\"    \"\"     \"\"\"\"\"    " << endl;
    cout << "======================================================================================================" << endl;
    cout << "                              ===================================                                     " << endl;
    cout << "                                 Welcome to AAU Course Manager                                        " << endl;
    cout << "                              ===================================                                     " << endl;
    cout << "                                ###############################                                       " << endl;
    cout << "                                # Type '1' to Register Course #                                       " << endl;
    cout << "                                # Type '2' to Drop Course     #                                       " << endl;
    cout << "                                # Type '3' to Show Schedule   #                                       " << endl;
    cout << "                                # Type '4' to Exit System     #                                       " << endl;
    cout << "                                # Type '5' to See credit      #                                       " << endl;
    cout << "                                ###############################                                       " << endl;
}


// 2. Function to handle student sign-in and course registration
void handleRegistration(Student* &student, bool &isInfoHere, string &sName, string &sID, Course* availableCourses[]) {    
    string choiceString;
    // Check if student info is not entered yet (runs only once)
    if (isInfoHere == false) {
        while (isInfoHere == false) {
            cout << "\n--- Student Sign In ---\n";
            cin.ignore(); // Clear buffer before using getline to prevent skipping input
            cout << "Enter Student Name: ";
            getline(cin, sName);
            cout << "Enter Student ID: ";
            cin >> sID;

            cout << "Your name is: " << sName << ", Your ID is: " << sID << ", RIGHT? (Y/N): ";

            bool InputLoopChoice = false;
            do {
                cin >> choiceString;
            if (choiceString == "Y" || choiceString == "y") { 
                student = new Student(sID, sName); // Dynamically allocate student object on the Heap
                InputLoopChoice = false;
                isInfoHere = true;
            } else if (choiceString == "N" || choiceString == "n") {
                InputLoopChoice = false;
                isInfoHere = false;
            } else {
                InputLoopChoice = true;
                isInfoHere = false;
                cout << "Wrong Input! Please type Y or N" << endl;
            }
        } while (InputLoopChoice == true);
        }
    }

    // Display available courses to the user
    bool IsUserShosing = true;
    while (IsUserShosing == true) {
        // Check if there are any courses left to display
        int availableToRegister = 0;
        for (int i = 0; i < 4; i++) {
            if (student->hasCourse(availableCourses[i]) == false) {
                availableToRegister++;
            }
        }

        // If no courses left, exit the loop automatically
        if (availableToRegister == 0) {
            cout << "\nYou have registered all available courses in AAU!";
            IsUserShosing = false;
            cout << "\nPress Enter to return to Main Menu... >>";
            cin.ignore();
            cin.get();
            break;

        }

        cout << "\n--- Available Courses in AAU ---\n";
        for (int i = 0; i < 4; i++) {
        if (student->hasCourse(availableCourses[i])) {
            continue;
        }
        cout << "[" << i+1 << "] ";
        availableCourses[i]->courseDetails(); // Polymorphism dynamically displays online or offline details
        cout << "--------------------------------------------------\n";
    }

    int chosenIndex;
    cout << "Enter the course number [1-4] to register: ";
    cin >> chosenIndex;

    // Input validation for course selection bounds
    if (cin.fail() || chosenIndex < 1 || chosenIndex > 4) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid course number! Registration failed :P" << endl;
        IsUserShosing = true;
        } else {
            student->registerCourse(availableCourses[chosenIndex-1]); // Invoke registration logic inside student class
        }

    bool InputLoopNo2 = false;
    do {
    cout << "Do you want to Enroll another course? (Y/N)";
    cin >> choiceString;

    if (choiceString == "N" || choiceString == "n") {  
        // Freeze screen mechanism inherited from last semester project
        cout << "\nPress Enter to return to Main Menu... >>";
        cin.ignore();
        cin.get();

        IsUserShosing = false;
        InputLoopNo2 = false;
        }else if (choiceString == "Y" || choiceString == "y") {
            InputLoopNo2 = false;
            IsUserShosing = true;
        } else {
            cout << "Wrong Input! Please type Y or N" << endl;
            InputLoopNo2 = true;

        }
        } while (InputLoopNo2 == true);
}
}


// 3. Function to handle course dropping safely without crashes
void handleDrop(Student* &student, bool &isInfoHere, string &sName, string &sID, Course* availableCourses[]) {
    string choiceString;
    // Null pointer protection check
    if (student == nullptr) {
        while (isInfoHere == false) {
            cout << "\n--- Student Sign In ---\n";
            cin.ignore(); // Clear buffer before using getline to prevent skipping input
            cout << "Enter Student Name: ";
            getline(cin, sName);
            cout << "Enter Student ID: ";
            cin >> sID;

            cout << "Your name is: " << sName << ", Your ID is: " << sID << ", RIGHT? (Y/N): ";

            bool InputLoopChoice = false;
            do {
            cin >> choiceString;

            if (choiceString == "Y" || choiceString == "y") { 
                student = new Student(sID, sName); // Dynamically allocate student object on the Heap
                InputLoopChoice = false;
                isInfoHere = true;
            } else if (choiceString == "N" || choiceString == "n") {
                InputLoopChoice = false;
                isInfoHere = false;
            } else {
                InputLoopChoice = true;
                isInfoHere = false;
                cout << "Wrong Input! Please type Y or N" << endl;
            }
        } while (InputLoopChoice == true);
        }
    } else {
        bool IsUserDropping = true;
        while (IsUserDropping == true) {
            if (student->getCourseCount() == 0) {
                cout << "Your schedule is empty! No courses to drop." << endl;
                IsUserDropping = false;
                break;
            } else {
                cout << "--- Your Registered Courses ---" << endl;
                for (int i = 0; i < student->getCourseCount(); i++) {
                    cout << "[" << i + 1 << "] ";
                    student->getRegisteredCourse(i)->courseDetails();
                }
                int chosenDropIndex;
                cout << "Chose one of your courses (1 ~ " << student ->getCourseCount() << "): ";
                cin >> chosenDropIndex;

                if (cin.fail() || chosenDropIndex < 1 || chosenDropIndex > student->getCourseCount()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Drop failed" << endl;
                } else {
                    student->dropCourse(student->getRegisteredCourse(chosenDropIndex - 1));
                }

            bool LoopChoice = false;
            do {
                cout << "Do you want to drop another course? (Y/N)" << endl;
                cin >> choiceString;

            if (choiceString == "Y" || choiceString == "y") { 
                LoopChoice = false;
                IsUserDropping = true;
            } else if (choiceString == "N" || choiceString == "n") {
                LoopChoice = false;
                IsUserDropping = false;
                break;
            } else {
                LoopChoice = true;
                cout << "Wrong Input! Please type Y or N" << endl;
            }
        } while (LoopChoice == true);
            
            }
        }
    }
    cout << "\nPress Enter to return to Main Menu... >>";
    cin.ignore();
    cin.get();
}


// 4. Function to display student registered schedule safely
void handlePrint(Student* &student, bool &isInfoHere, string &sName, string &sID) {
    string choiceString;
    // Null pointer protection check
    if (student == nullptr) {
    while (isInfoHere == false) {
            cout << "\n--- Student Sign In ---\n";
            cin.ignore(); // Clear buffer before using getline to prevent skipping input
            cout << "Enter Student Name: ";
            getline(cin, sName);
            cout << "Enter Student ID: ";
            cin >> sID;

            cout << "Your name is: " << sName << ", Your ID is: " << sID << ", RIGHT? (Y/N): ";

            bool InputLoopChoice = false;
            do {
            cin >> choiceString;
            if (choiceString == "Y" || choiceString == "y") { 
                student = new Student(sID, sName); // Dynamically allocate student object on the Heap
                InputLoopChoice = false;
                isInfoHere = true;
            } else if (choiceString == "N" || choiceString == "n") {
                InputLoopChoice = false;
                isInfoHere = false;
            } else {
                InputLoopChoice = true;
                isInfoHere = false;
                cout << "Wrong Input! Please type Y or N" << endl;
            }
        } while (InputLoopChoice == true);
        }
    } else {
        student->printSchedule(); // Polymorphism triggers automatically here to print mixed details
    }
    cout << "\nPress Enter to return to Main Menu... >>";
    cin.ignore();
    cin.get();
}


// 5. Function to show team developers credits
void showCredit() {
cout << "======================================================================================================" << endl;
    cout << "" << endl;
    cout << "             mmmmmm       mmmmmm     ##    ##               mmmmmm    mmm  mmm     mmmmmm   " << endl;
    cout << "            m##\"\"##m     m##\"\"##m    ##    ##              m##\"\"\"\"    ###  ###    m##\"\"\"\"   " << endl;
    cout << "            ##    ##     ##    ##    ##    ##              ##         ########    \"####m    " << endl;
    cout << "            ########     ########    ##    ##    mmmmmm    ##         ## ## ##     \"\"\"##m   " << endl;
    cout << "            ##\"\"\"\"##     ##\"\"\"\"##    ##    ##    \"\"\"\"\"\"    ##         ## \"\" ##        \"##   " << endl;
    cout << "            ##    ##     ##    ##    \"##mm##\"              \"##mmmm    ##    ##    ##mmm##   " << endl;
    cout << "            \"\"    \"\"     \"\"    \"\"     \"\"\"\"\"\"                \"\"\"\"\"\"    \"\"    \"\"     \"\"\"\"\"    " << endl;
    cout << "======================================================================================================" << endl;
    cout << "                               #   AAU COURSE MANAGER DEVELOPERS   #" << endl;
    cout << "======================================================================================================" << endl;
    cout << "    [+] Rayyan Mohammad Farouq Saleh         (202510096)\n";
    cout << "    [+] Hisham Mahmoud Muhammad Al-Nassour   (202510419)\n";
    cout << "    [+] Aya Abdallah Shilpaeyh               (202420849)\n";
    cout << "    [+] Joud Raed Al-Saudi                   (202511110)\n";
    cout << "======================================================================================================\n";

    // Freeze screen mechanism inherited from last semester project
    cout << "\nPress Enter to return to Main Menu... >>";
    cin.ignore();
    cin.get();
}