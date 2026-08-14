#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

// Constant for the data file name
const string DATA_FILE = "students.dat";

// ==========================================
// Class: Student
// Represents a student entity with all attributes
// ==========================================
class Student {
private:
    int id;
    string name;
    int age;
    string gender;
    string course;
    int semester;
    string phone;
    string email;
    double cgpa;

public:
    // Default Constructor
    Student() : id(0), age(0), semester(0), cgpa(0.0) {}

    // Parameterized Constructor
    Student(int sId, string sName, int sAge, string sGender, string sCourse, 
            int sSem, string sPhone, string sEmail, double sCgpa)
        : id(sId), name(sName), age(sAge), gender(sGender), course(sCourse),
          semester(sSem), phone(sPhone), email(sEmail), cgpa(sCgpa) {}

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGender() const { return gender; }
    string getCourse() const { return course; }
    int getSemester() const { return semester; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
    double getCgpa() const { return cgpa; }

    // Setters
    void setId(int sId) { id = sId; }
    void setName(const string& sName) { name = sName; }
    void setAge(int sAge) { age = sAge; }
    void setGender(const string& sGender) { gender = sGender; }
    void setCourse(const string& sCourse) { course = sCourse; }
    void setSemester(int sSem) { semester = sSem; }
    void setPhone(const string& sPhone) { phone = sPhone; }
    void setEmail(const string& sEmail) { email = sEmail; }
    void setCgpa(double sCgpa) { cgpa = sCgpa; }

    // Convert student object to pipe-delimited string for file storage
    string serialize() const {
        stringstream ss;
        ss << id << "|" << name << "|" << age << "|" << gender << "|"
           << course << "|" << semester << "|" << phone << "|" << email << "|" << fixed << setprecision(2) << cgpa;
        return ss.str();
    }

    // Load student object from a pipe-delimited string
    static bool deserialize(const string& line, Student& student) {
        if (line.empty()) return false;

        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 9) return false;

        try {
            student.id = stoi(tokens[0]);
            student.name = tokens[1];
            student.age = stoi(tokens[2]);
            student.gender = tokens[3];
            student.course = tokens[4];
            student.semester = stoi(tokens[5]);
            student.phone = tokens[6];
            student.email = tokens[7];
            student.cgpa = stod(tokens[8]);
            return true;
        } catch (...) {
            return false;
        }
    }

    // Display student in table row format
    void displayRow() const {
        cout << "| " << setw(6) << left << id
             << " | " << setw(18) << left << (name.length() > 18 ? name.substr(0, 15) + "..." : name)
             << " | " << setw(4) << left << age
             << " | " << setw(8) << left << gender
             << " | " << setw(12) << left << (course.length() > 12 ? course.substr(0, 9) + "..." : course)
             << " | " << setw(4) << left << semester
             << " | " << setw(12) << left << phone
             << " | " << setw(22) << left << (email.length() > 22 ? email.substr(0, 19) + "..." : email)
             << " | " << setw(5) << right << fixed << setprecision(2) << cgpa << " |\n";
    }

    // Display complete student details as a card
    void displayCard() const {
        cout << "+------------------------------------------------------+\n";
        cout << "|                  STUDENT DETAILS                     |\n";
        cout << "+------------------------------------------------------+\n";
        cout << "  Student ID   : " << id << "\n";
        cout << "  Full Name    : " << name << "\n";
        cout << "  Age          : " << age << " years\n";
        cout << "  Gender       : " << gender << "\n";
        cout << "  Course/Branch: " << course << "\n";
        cout << "  Semester     : " << semester << "\n";
        cout << "  Phone Number : " << phone << "\n";
        cout << "  Email Address: " << email << "\n";
        cout << "  CGPA         : " << fixed << setprecision(2) << cgpa << "\n";
        cout << "+------------------------------------------------------+\n";
    }
};

// ==========================================
// Helper Utility Functions for Safe Input
// ==========================================
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

int getValidInt(const string& prompt, int minVal, int maxVal) {
    string line;
    int value;
    while (true) {
        if (!prompt.empty()) cout << prompt;
        if (getline(cin, line)) {
            line = trim(line);
            if (line.empty()) continue;
            try {
                size_t pos = 0;
                value = stoi(line, &pos);
                if (pos == line.length() && value >= minVal && value <= maxVal) {
                    return value;
                }
            } catch (...) {}
            cout << "  [Error] Value must be an integer between " << minVal << " and " << maxVal << ". Please try again.\n";
        }
    }
}

double getValidDouble(const string& prompt, double minVal, double maxVal) {
    string line;
    double value;
    while (true) {
        if (!prompt.empty()) cout << prompt;
        if (getline(cin, line)) {
            line = trim(line);
            if (line.empty()) continue;
            try {
                size_t pos = 0;
                value = stod(line, &pos);
                if (pos == line.length() && value >= minVal && value <= maxVal) {
                    return value;
                }
            } catch (...) {}
            cout << "  [Error] Value must be a number between " << fixed << setprecision(2) << minVal << " and " << maxVal << ". Please try again.\n";
        }
    }
}

string getValidString(const string& prompt) {
    string input;
    while (true) {
        if (!prompt.empty()) cout << prompt;
        if (getline(cin, input)) {
            input = trim(input);
            if (!input.empty()) {
                return input;
            }
        }
        cout << "  [Error] Input cannot be empty! Please try again.\n";
    }
}

string getValidEmail(const string& prompt) {
    while (true) {
        string email = getValidString(prompt);
        size_t atPos = email.find('@');
        size_t dotPos = email.rfind('.');
        if (atPos != string::npos && dotPos != string::npos && atPos > 0 && dotPos > atPos + 1 && dotPos < email.length() - 1) {
            return email;
        }
        cout << "  [Error] Invalid email format! (Example: student@example.com)\n";
    }
}

string getValidPhone(const string& prompt) {
    while (true) {
        string phone = getValidString(prompt);
        bool valid = true;
        int digits = 0;
        for (char c : phone) {
            if (isdigit(c)) {
                digits++;
            } else if (c != '+' && c != '-' && c != ' ') {
                valid = false;
                break;
            }
        }
        if (valid && digits >= 7 && digits <= 15) {
            return phone;
        }
        cout << "  [Error] Invalid phone number! Please enter 7 to 15 digits.\n";
    }
}

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
    return str;
}

// ==========================================
// Class: StudentManager
// Manages system operations & file persistence
// ==========================================
class StudentManager {
private:
    // Check if a student ID already exists in file
    bool isDuplicateId(int checkId) {
        ifstream file(DATA_FILE);
        if (!file.is_open()) return false;

        string line;
        Student temp;
        while (getline(file, line)) {
            if (Student::deserialize(line, temp)) {
                if (temp.getId() == checkId) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
        return false;
    }

    // Read all students from file into a vector
    vector<Student> readAllStudentsFromFile() {
        vector<Student> students;
        ifstream file(DATA_FILE);
        if (!file.is_open()) return students;

        string line;
        Student temp;
        while (getline(file, line)) {
            if (Student::deserialize(line, temp)) {
                students.push_back(temp);
            }
        }
        file.close();
        return students;
    }

public:
    StudentManager() {
        // Ensure data file exists or create it
        ofstream file(DATA_FILE, ios::app);
        file.close();
    }

    // Feature 1: Add Student
    void addStudent() {
        cout << "\n======================================================\n";
        cout << "                 ADD NEW STUDENT                      \n";
        cout << "======================================================\n";

        int id;
        while (true) {
            id = getValidInt("Enter Student ID / Roll No (Positive Integer): ", 1, 999999);
            if (isDuplicateId(id)) {
                cout << "  [Error] Student ID " << id << " already exists! Duplicate IDs are not allowed.\n";
            } else {
                break;
            }
        }

        string name = getValidString("Enter Full Name        : ");
        int age = getValidInt("Enter Age (15 - 80)     : ", 15, 80);
        string gender = getValidString("Enter Gender (Male/Female/Other): ");
        string course = getValidString("Enter Course / Branch   : ");
        int semester = getValidInt("Enter Semester (1 - 12) : ", 1, 12);
        string phone = getValidPhone("Enter Phone Number      : ");
        string email = getValidEmail("Enter Email Address     : ");
        double cgpa = getValidDouble("Enter CGPA (0.00 - 10.00): ", 0.0, 10.0);

        Student newStudent(id, name, age, gender, course, semester, phone, email, cgpa);

        // Save persistently using fstream append mode
        ofstream file(DATA_FILE, ios::app);
        if (file.is_open()) {
            file << newStudent.serialize() << "\n";
            file.close();
            cout << "\n[SUCCESS] Student record added successfully!\n";
        } else {
            cout << "\n[Error] Unable to open data file for writing!\n";
        }
    }

    // Feature 2: Display All Students
    void displayAllStudents() {
        vector<Student> students = readAllStudentsFromFile();

        cout << "\n=========================================================================================================\n";
        cout << "                                         ALL REGISTERED STUDENTS                                         \n";
        cout << "=========================================================================================================\n";

        if (students.empty()) {
            cout << "\n  [Notice] No student records found in the system.\n\n";
            return;
        }

        cout << "+--------+--------------------+------+----------+--------------+------+--------------+------------------------+-------+\n";
        cout << "| ID     | Name               | Age  | Gender   | Course       | Sem  | Phone        | Email                  | CGPA  |\n";
        cout << "+--------+--------------------+------+----------+--------------+------+--------------+------------------------+-------+\n";

        for (const auto& student : students) {
            student.displayRow();
        }

        cout << "+--------+--------------------+------+----------+--------------+------+--------------+------------------------+-------+\n";
        cout << "  Total Records Found: " << students.size() << "\n\n";
    }

    // Feature 3: Search Student
    void searchStudent() {
        vector<Student> students = readAllStudentsFromFile();

        if (students.empty()) {
            cout << "\n  [Notice] No records available to search.\n";
            return;
        }

        cout << "\n======================================================\n";
        cout << "                   SEARCH STUDENT                     \n";
        cout << "======================================================\n";
        cout << "1. Search by Student ID\n";
        cout << "2. Search by Student Name\n";
        cout << "------------------------------------------------------\n";

        int choice = getValidInt("Enter your choice (1-2): ", 1, 2);

        if (choice == 1) {
            int searchId = getValidInt("Enter Student ID to search: ", 1, 999999);
            bool found = false;

            for (const auto& student : students) {
                if (student.getId() == searchId) {
                    cout << "\n[SUCCESS] Student Record Found:\n\n";
                    student.displayCard();
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "\n[Notice] Student with ID " << searchId << " not found!\n";
            }
        } else if (choice == 2) {
            string searchName = getValidString("Enter Student Name (or substring) to search: ");
            string lowerSearchName = toLowerCase(searchName);
            int matchCount = 0;

            for (const auto& student : students) {
                string lowerStudentName = toLowerCase(student.getName());
                if (lowerStudentName.find(lowerSearchName) != string::npos) {
                    if (matchCount == 0) {
                        cout << "\n[SUCCESS] Matching Student Record(s) Found:\n\n";
                    }
                    student.displayCard();
                    cout << "\n";
                    matchCount++;
                }
            }

            if (matchCount == 0) {
                cout << "\n[Notice] No student found with name matching '" << searchName << "'.\n";
            } else {
                cout << "Total Matches Found: " << matchCount << "\n";
            }
        }
    }

    // Feature 4: Update Student
    void updateStudent() {
        vector<Student> students = readAllStudentsFromFile();

        if (students.empty()) {
            cout << "\n  [Notice] No student records available to update.\n";
            return;
        }

        cout << "\n======================================================\n";
        cout << "                   UPDATE STUDENT                     \n";
        cout << "======================================================\n";

        int targetId = getValidInt("Enter Student ID to update: ", 1, 999999);
        int targetIndex = -1;

        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].getId() == targetId) {
                targetIndex = static_cast<int>(i);
                break;
            }
        }

        if (targetIndex == -1) {
            cout << "\n[Error] Student ID " << targetId << " not found!\n";
            return;
        }

        cout << "\nExisting Details:\n";
        students[targetIndex].displayCard();

        cout << "\n--- Enter New Details (Press Enter to keep existing value) ---\n";
        
        string input;

        // Name
        cout << "Enter New Name [Current: " << students[targetIndex].getName() << "]: ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            students[targetIndex].setName(input);
        }

        // Age
        cout << "Enter New Age [Current: " << students[targetIndex].getAge() << "] (Press Enter to keep): ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            try {
                int val = stoi(input);
                if (val >= 15 && val <= 80) students[targetIndex].setAge(val);
                else cout << "  [Notice] Age out of range (15-80). Keeping existing age.\n";
            } catch (...) {
                cout << "  [Notice] Invalid number. Keeping existing age.\n";
            }
        }

        // Gender
        cout << "Enter New Gender [Current: " << students[targetIndex].getGender() << "]: ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            students[targetIndex].setGender(input);
        }

        // Course
        cout << "Enter New Course/Branch [Current: " << students[targetIndex].getCourse() << "]: ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            students[targetIndex].setCourse(input);
        }

        // Semester
        cout << "Enter New Semester [Current: " << students[targetIndex].getSemester() << "] (Press Enter to keep): ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            try {
                int val = stoi(input);
                if (val >= 1 && val <= 12) students[targetIndex].setSemester(val);
                else cout << "  [Notice] Semester out of range (1-12). Keeping existing semester.\n";
            } catch (...) {
                cout << "  [Notice] Invalid number. Keeping existing semester.\n";
            }
        }

        // Phone
        cout << "Enter New Phone Number [Current: " << students[targetIndex].getPhone() << "]: ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            bool valid = true;
            int digits = 0;
            for (char c : input) {
                if (isdigit(c)) digits++;
                else if (c != '+' && c != '-' && c != ' ') { valid = false; break; }
            }
            if (valid && digits >= 7 && digits <= 15) {
                students[targetIndex].setPhone(input);
            } else {
                cout << "  [Notice] Invalid phone format. Keeping existing phone number.\n";
            }
        }

        // Email
        cout << "Enter New Email Address [Current: " << students[targetIndex].getEmail() << "]: ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            size_t atPos = input.find('@');
            size_t dotPos = input.rfind('.');
            if (atPos != string::npos && dotPos != string::npos && atPos > 0 && dotPos > atPos + 1 && dotPos < input.length() - 1) {
                students[targetIndex].setEmail(input);
            } else {
                cout << "  [Notice] Invalid email format. Keeping existing email address.\n";
            }
        }

        // CGPA
        cout << "Enter New CGPA [Current: " << fixed << setprecision(2) << students[targetIndex].getCgpa() << "] (Press Enter to keep): ";
        getline(cin, input);
        input = trim(input);
        if (!input.empty()) {
            try {
                double val = stod(input);
                if (val >= 0.0 && val <= 10.0) students[targetIndex].setCgpa(val);
                else cout << "  [Notice] CGPA out of range (0.00-10.00). Keeping existing CGPA.\n";
            } catch (...) {
                cout << "  [Notice] Invalid decimal number. Keeping existing CGPA.\n";
            }
        }

        // Write all updated records to temp file and replace
        ofstream tempFile("temp.dat");
        if (!tempFile.is_open()) {
            cout << "\n[Error] Unable to create temporary file for update!\n";
            return;
        }

        for (const auto& student : students) {
            tempFile << student.serialize() << "\n";
        }
        tempFile.close();

        remove(DATA_FILE.c_str());
        rename("temp.dat", DATA_FILE.c_str());

        cout << "\n[SUCCESS] Student record updated successfully!\n";
    }

    // Feature 5: Delete Student
    void deleteStudent() {
        vector<Student> students = readAllStudentsFromFile();

        if (students.empty()) {
            cout << "\n  [Notice] No student records available to delete.\n";
            return;
        }

        cout << "\n======================================================\n";
        cout << "                   DELETE STUDENT                     \n";
        cout << "======================================================\n";

        int deleteId = getValidInt("Enter Student ID to delete: ", 1, 999999);
        int targetIndex = -1;

        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i].getId() == deleteId) {
                targetIndex = static_cast<int>(i);
                break;
            }
        }

        if (targetIndex == -1) {
            cout << "\n[Error] Student ID " << deleteId << " not found!\n";
            return;
        }

        cout << "\nStudent Record Selected for Deletion:\n";
        students[targetIndex].displayCard();

        string confirm = getValidString("Are you sure you want to delete this record? (Y/N): ");
        if (toLowerCase(confirm) != "y" && toLowerCase(confirm) != "yes") {
            cout << "\n[Notice] Deletion cancelled by user.\n";
            return;
        }

        // Write all other records to temp file and replace
        ofstream tempFile("temp.dat");
        if (!tempFile.is_open()) {
            cout << "\n[Error] Unable to create temporary file for deletion!\n";
            return;
        }

        for (size_t i = 0; i < students.size(); ++i) {
            if (static_cast<int>(i) != targetIndex) {
                tempFile << students[i].serialize() << "\n";
            }
        }
        tempFile.close();

        remove(DATA_FILE.c_str());
        rename("temp.dat", DATA_FILE.c_str());

        cout << "\n[SUCCESS] Student ID " << deleteId << " deleted successfully!\n";
    }
};

// ==========================================
// Main Function: Console Menu Application
// ==========================================
int main() {
    StudentManager manager;
    int choice = 0;

    do {
        cout << "\n======================================================\n";
        cout << "          STUDENT MANAGEMENT SYSTEM (C++)             \n";
        cout << "======================================================\n";
        cout << "  1. Add Student\n";
        cout << "  2. Display All Students\n";
        cout << "  3. Search Student\n";
        cout << "  4. Update Student\n";
        cout << "  5. Delete Student\n";
        cout << "  6. Exit\n";
        cout << "======================================================\n";

        choice = getValidInt("Enter your choice (1-6): ", 1, 6);

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.displayAllStudents();
                break;
            case 3:
                manager.searchStudent();
                break;
            case 4:
                manager.updateStudent();
                break;
            case 5:
                manager.deleteStudent();
                break;
            case 6:
                cout << "\nThank you for using Student Management System! Goodbye.\n";
                break;
            default:
                cout << "\n[Error] Invalid choice! Please select between 1 and 6.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}
