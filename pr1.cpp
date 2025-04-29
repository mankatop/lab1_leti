#include <iostream>
#include <fstream>
using namespace std;




struct Student {
    int id;
    string fullname;
    string sex;
    unsigned int group;
    int marksForExamsAndTests[8];
    int get(void) {
        return 4;
    }
};

void studentDataWriteToFile(const Student *writeStudent, int opt = 0) {
    ofstream fileToWriteInto("data.txt", ios::app);
            if (fileToWriteInto.is_open()) {
                fileToWriteInto << writeStudent->fullname << '\n';
                fileToWriteInto << writeStudent->sex << '\n';
                fileToWriteInto << writeStudent->group << '\n';
                for (int grade = 0; grade < 8; grade++) {
                    fileToWriteInto << writeStudent->marksForExamsAndTests[grade] << ' ';
                }
                fileToWriteInto << '\n';
                fileToWriteInto.close();
            }
            else {
                cout << "Could not open the file, check if it exists." << endl;
            }
    
}


void createRecord(void) {
    bool isBadStudent = false;
    Student newStudent;
    cin.clear();
    getline(cin, newStudent.fullname);
    getline(cin, newStudent.sex); 
    cin >> newStudent.group;
    for (int gradePos = 0; gradePos < 8; gradePos++) {
        cin >> newStudent.marksForExamsAndTests[gradePos];
        if (newStudent.marksForExamsAndTests[gradePos] <= 2 || newStudent.marksForExamsAndTests[gradePos] > 5) {
            isBadStudent = true;
        }
    }
    if (!isBadStudent) {
        studentDataWriteToFile(&newStudent);
    }
    else {
        cout << "Unfortuantely, this student is getting expelled" << endl;
        if (newStudent.sex == "Male") { 
            cout << "Welcome to the Russian army!" << endl;
        }
    }
};

int findNumberOfStudents(void) {
    int numberOfStudents = 0;
    string studentRecord;
    ifstream fileReadFrom("data.txt");
    if (fileReadFrom.is_open()) {
        while (getline(fileReadFrom, studentRecord)) {
            numberOfStudents++;
        }

        fileReadFrom.close();
        return numberOfStudents / 4;
    }
    else {
        return -1;
    }
}


// здесь будет все: тотальные костыли, нереальные утечки памяти, полное осознание ущербности кода

void changeRecord(void) {
    string studentNameToChange;
    cout << "What student record would you like to change?" << endl;
    cin.clear();
    getline(cin, studentNameToChange);
    int studentArraySize = findNumberOfStudents();
    vector<Student> studentList(studentArraySize);

    ifstream fileToReadFrom("data.txt");    
    for (int studentNumber = 0; studentNumber < studentArraySize; studentNumber++) {
        getline(fileToReadFrom, studentList[studentNumber].fullname);
        cout << studentList[studentNumber].fullname << endl;

        getline(fileToReadFrom, studentList[studentNumber].sex);
        cout << studentList[studentNumber].sex << endl;

        fileToReadFrom >> studentList[studentNumber].group;
        fileToReadFrom.ignore();
        //cout << studentList[studentNumber].group << endl;

        for (int grade = 0; grade < 8; grade++) {
            fileToReadFrom >> studentList[studentNumber].marksForExamsAndTests[grade];
            fileToReadFrom.ignore();
            //cout << studentList[studentNumber].marksForExamsAndTests[grade] << endl;
        }    
        fileToReadFrom.ignore();
    }
    fileToReadFrom.close();


    bool foundStudent = false;

    for(int studentIter = 0; studentIter < studentArraySize; studentIter++) {
        if (studentList[studentIter].fullname == studentNameToChange) {
            foundStudent = true;
            cin >> studentList[studentIter].sex;
            cin >> studentList[studentIter].group;
            for (int newGrade = 0; newGrade < 8; newGrade++) {
                cin >> studentList[studentIter].marksForExamsAndTests[newGrade];
            }
        }
    }

    if (foundStudent) {
        ofstream fileToWriteInto("data.txt", ios::trunc);
        fileToWriteInto.close();
        for (int numberOfRecord = 0; numberOfRecord < studentArraySize; numberOfRecord++) {
            studentDataWriteToFile(&studentList[numberOfRecord]);
        }
    }
};

void showAllStudents(void) {
    ifstream fileToGetAllData("data.txt");
    if (fileToGetAllData.is_open()) {
        string dataToExtract;
        while (getline(fileToGetAllData, dataToExtract)) {
            cout << dataToExtract << endl;
        }
    }
    fileToGetAllData.close();
}

void showStudentOfGroupN() {
    int groupNumber;
    cin.clear();
    cin >> groupNumber;
    int studentArraySize = findNumberOfStudents();
    vector<Student> studentList(studentArraySize);
    ifstream fileToReadFrom("data.txt");
    for (int studentNumber = 0; studentNumber < studentArraySize; studentNumber++) {
        getline(fileToReadFrom, studentList[studentNumber].fullname);
        //cout << studentList[studentNumber].fullname << endl;

        getline(fileToReadFrom, studentList[studentNumber].sex);
        //cout << studentList[studentNumber].sex << endl;

        fileToReadFrom >> studentList[studentNumber].group;
        fileToReadFrom.ignore();
        //cout << studentList[studentNumber].group << endl;

        for (int grade = 0; grade < 8; grade++) {
            fileToReadFrom >> studentList[studentNumber].marksForExamsAndTests[grade];
            fileToReadFrom.ignore();
            //cout << studentList[studentNumber].marksForExamsAndTests[grade] << endl;
        }    
        fileToReadFrom.ignore();
        if (studentList[studentNumber].group == groupNumber) {
            cout << studentList[studentNumber].fullname << endl;
            cout << studentList[studentNumber].sex << endl;
            cout << studentList[studentNumber].group << endl;
            for (int grade = 0; grade < 8; grade++) {
                cout << studentList[studentNumber].marksForExamsAndTests[grade] << ' ';
            }
            cout << endl;
            cout << endl;
        }
    }
    fileToReadFrom.close();
}

void sortStructureByGrade(vector<Student> &sortedStudents, int arraySize) {
    for (int i = 0; i < arraySize - 1; i++) {
        for (int j = 0; j < arraySize - i - 1; j++) {
            double sumGradeStud1 = 0, sumGradeStud2 = 0;
            for (int grade = 0; grade < 8; grade++) {
                sumGradeStud1 += sortedStudents[j].marksForExamsAndTests[grade];
                sumGradeStud2 += sortedStudents[j + 1].marksForExamsAndTests[grade];
            }
            double average1 = sumGradeStud1 / 8;
            double average2 = sumGradeStud2 / 8;

            if (average1 < average2) {
                swap(sortedStudents[j], sortedStudents[j + 1]);
            }
        }
    }
}


void showTopStudents() {
    int studentArraySize = findNumberOfStudents();
    vector<Student> studentList(studentArraySize);
    ifstream fileToReadFrom("data.txt");
    for (int studentNumber = 0; studentNumber < studentArraySize; studentNumber++) {
        getline(fileToReadFrom, studentList[studentNumber].fullname);
        //cout << studentList[studentNumber].fullname << endl;

        getline(fileToReadFrom, studentList[studentNumber].sex);
        //cout << studentList[studentNumber].sex << endl;

        fileToReadFrom >> studentList[studentNumber].group;
        fileToReadFrom.ignore();
        //cout << studentList[studentNumber].group << endl;

        for (int grade = 0; grade < 8; grade++) {
            fileToReadFrom >> studentList[studentNumber].marksForExamsAndTests[grade];
            fileToReadFrom.ignore();
            //cout << studentList[studentNumber].marksForExamsAndTests[grade] << endl;
        }    
        fileToReadFrom.ignore();
    }
    sortStructureByGrade(studentList, studentArraySize);
    for (int studentPos = 0; studentPos < studentArraySize; studentPos++) {
        double averageGrade = 0;
        for (int grade = 0; grade < 8; grade++) {
            averageGrade += studentList[studentPos].marksForExamsAndTests[grade];
        }
        averageGrade /= 8;
        cout << "Average grade of the student:  " <<studentList[studentPos].fullname << " is: " << averageGrade << endl;

    }

}


void countByGender() {
    int maleStudents = 0, femaleStudents = 0;
    int studentArraySize = findNumberOfStudents();
    vector<Student> studentList(studentArraySize);
    ifstream fileToReadFrom("data.txt");
    for (int studentNumber = 0; studentNumber < studentArraySize; studentNumber++) {
        getline(fileToReadFrom, studentList[studentNumber].fullname);
        //cout << studentList[studentNumber].fullname << endl;

        getline(fileToReadFrom, studentList[studentNumber].sex);
        //cout << studentList[studentNumber].sex << endl;

        fileToReadFrom >> studentList[studentNumber].group;
        fileToReadFrom.ignore();
        //cout << studentList[studentNumber].group << endl;

        for (int grade = 0; grade < 8; grade++) {
            fileToReadFrom >> studentList[studentNumber].marksForExamsAndTests[grade];
            fileToReadFrom.ignore();
            //cout << studentList[studentNumber].marksForExamsAndTests[grade] << endl;
        }    
        fileToReadFrom.ignore();
    }
    fileToReadFrom.close();
    for (int studentIter = 0; studentIter < studentArraySize; studentIter++) {
        if (studentList[studentIter].sex == "Male") {
            maleStudents++;
        }
    }
    cout << "Number of male students: " << maleStudents << endl;
    cout << "Number of female students: " << studentArraySize - maleStudents << endl;
}


void rangeStudentsByPerformance(int option) {

    int maleStudents = 0, femaleStudents = 0;
    int studentArraySize = findNumberOfStudents();
    vector<Student> studentList(studentArraySize);
    ifstream fileToReadFrom("data.txt");
    for (int studentNumber = 0; studentNumber < studentArraySize; studentNumber++) {
        getline(fileToReadFrom, studentList[studentNumber].fullname);
        //cout << studentList[studentNumber].fullname << endl;

        getline(fileToReadFrom, studentList[studentNumber].sex);
        //cout << studentList[studentNumber].sex << endl;

        fileToReadFrom >> studentList[studentNumber].group;
        fileToReadFrom.ignore();
        //cout << studentList[studentNumber].group << endl;

        for (int grade = 0; grade < 8; grade++) {
            fileToReadFrom >> studentList[studentNumber].marksForExamsAndTests[grade];
            fileToReadFrom.ignore();
            //cout << studentList[studentNumber].marksForExamsAndTests[grade] << endl;
        }    
        fileToReadFrom.ignore();
    }
    fileToReadFrom.close();
    for (int studentIter = 0; studentIter < studentArraySize; studentIter++) {
        bool hasThree = false;
        bool hasFour = false;
    
        for (int grade = 0; grade < 8; grade++) {
            if (studentList[studentIter].marksForExamsAndTests[grade] == 3) {
                hasThree = true;
            }
            if (studentList[studentIter].marksForExamsAndTests[grade] == 4) {
                hasFour = true;
            }
        }
        if (hasThree) {
            cout << studentList[studentIter].fullname << " is not on scholarship" << endl;
        } else if (hasFour) {
            cout << studentList[studentIter].fullname << " is an OK student" << endl;
        } else {
            cout << studentList[studentIter].fullname << " is a perfect student" << endl;
        }
    }
}

void showStudentN() {
    int studentID;
    cout << "Enter student number: ";
    cin >> studentID;
    cin.clear();
    cin.ignore();
    int studentArraySize = findNumberOfStudents();
    vector<Student> studentList(studentArraySize);
    ifstream fileToReadFrom("data.txt");
    for (int studentNumber = 0; studentNumber < studentArraySize; studentNumber++) {
        getline(fileToReadFrom, studentList[studentNumber].fullname);
        //cout << studentList[studentNumber].fullname << endl;

        getline(fileToReadFrom, studentList[studentNumber].sex);
        //cout << studentList[studentNumber].sex << endl;

        fileToReadFrom >> studentList[studentNumber].group;
        fileToReadFrom.ignore();
        //cout << studentList[studentNumber].group << endl;

        for (int grade = 0; grade < 8; grade++) {
            fileToReadFrom >> studentList[studentNumber].marksForExamsAndTests[grade];
            fileToReadFrom.ignore();
            //cout << studentList[studentNumber].marksForExamsAndTests[grade] << endl;
        }    
        fileToReadFrom.ignore();
        if (studentID == (studentNumber + 1)) {
            cout << "Student's data: " << endl;
            cout << "Fullname: " << studentList[studentNumber].fullname << endl;
            cout << "Sex: " << studentList[studentNumber].sex << endl;
            cout << "Group: " << studentList[studentNumber].group << endl;
            for (int grade = 0; grade < 8; grade++) {
                cout << "Grade " << grade + 1 << ": " << studentList[studentNumber].marksForExamsAndTests[grade] << endl;
            }
        }
        if (studentNumber > studentArraySize) {
            cout << "No student with such number" << endl;
        }

    }
    fileToReadFrom.close();

}





int main(void) {
    cout << sizeof(Student) << endl;
    int subactionForPeformance;
    while (true) {
        system("clear");
        puts("1:(Create new record), 2:(Change existing record), 3:(Show all data), 4: (Show all strudent of grouo N, 5:(Show top students)), ");
        puts("6:(Number of female/male students), 7:(Students on scholarship, good stud., perfect stud., 8:(Find by ID.))");
        int action;
        cin >> action;
        cin.clear();
        cin.ignore();
        switch (action) {
            case 1:
                system("clear");
                cout << "Input data: " << endl;
                cin.clear();
                createRecord();
                getchar();
                getchar();
                break;
            case 2:
                system("clear");
                changeRecord();
                system("pause");
                break;
            case 3:
                system("clear");
                cout << "Whole data: " << endl;
                showAllStudents();
                getchar();
                break;
            case 4:
                system("clear");
                showStudentOfGroupN();
                getchar();
                getchar();
                break;
            case 5:
                system("clear");
                showTopStudents();
                getchar();
                break;
            case 6:
                system("clear");
                countByGender();
                getchar();
                break; 
            case 7:
                {
                    int option = 0;
                    //cout << "What students would you like to see?" << endl;
                    //cin >> option;
                    //cin.clear();
                    rangeStudentsByPerformance(option);
                    getchar();
                }
                break;
            case 8:
                system("clear");
                showStudentN();
                getchar();
                break;
            case 9:
                system("clear");
                return 0;
            default:
                cout << "Invalid option, please try again." << endl;
        }
    }
    
    return 0;
}