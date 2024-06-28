#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class CLO {
private:
    string description;

public:
    CLO(string description) : description(description) {}

    string getDescription() const {
        return description;
    }

    bool operator==(const CLO& other) const {
        return description == other.description;
    }
};

class PLO {
private:
    string description;

public:
    PLO(string desc) : description(desc) {}

    string getDescription() const {
        return description;
    }
};

class Evaluation {
private:
    string question;
    vector<CLO> testedCLOs;

public:
    Evaluation(string question) : question(question) {}

    void addTestedCLO(const CLO& clo) {
        testedCLOs.push_back(clo);
    }

    const string& getQuestion() const {
        return question;
    }

    const vector<CLO>& getTestedCLOs() const {
        return testedCLOs;
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "Question: " << question << endl;
            file << "Tested CLOs:" << endl;
            for (const auto& clo : testedCLOs) {
                file << "- " << clo.getDescription() << endl;
            }
            file << endl;
            file.close();
            cout << "Evaluation saved to file: " << filename << endl;
        }
        else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
};

class Course {
private:
    string name;
    string course_code;
    vector<PLO> plos;
    vector<CLO> clos;
    vector<Evaluation> evaluations;

public:

    Course(string name, string course_code) : name(name), course_code(course_code) {}

    string getName() const {
        return name;
    }

    string getCourseCode() const {
        return course_code;
    }

    void addPLO(const PLO& plo) {
        plos.push_back(plo);
    }

    void addCLO(const CLO& clo) {
        clos.push_back(clo);
    }

    void addEvaluation(const Evaluation& evaluation) {
        evaluations.push_back(evaluation);
    }

    void add_to_file(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            file << course_code << " " << name << endl;
            file.close();
            cout << "Course details saved in file : " << filename << endl;
        }
        else {
            cerr << "Unable to open file : " << filename << endl;
        }
    }

    void savePLOsToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& plo : plos) {
                file << plo.getDescription() << endl;
            }
            file.close();
            cout << "PLOs saved to file: " << filename << endl;
        }
        else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void saveCLOsToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto& clo : clos) {
                file << clo.getDescription() << endl;
            }
            file.close();
            cout << "CLOs saved to file: " << filename << endl;
        }
        else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    vector<CLO> getCLOs() const {
        return clos;
    }
};

class Teacher {
public:
    vector<Evaluation> evaluations;

    void addEvaluation(const Evaluation& evaluation);
};

void Teacher::addEvaluation(const Evaluation& evaluation) {
    evaluations.push_back(evaluation);
}

class AcademicOfficer {
public:

    vector <Course> courses;

    void addCourse(Course& newCourse);
    void addToCourseFile(const Course& course, const string& filename);
    void removeCourse(const string& courseName);
    void updateCourse(const string& courseName);
};

void AcademicOfficer::addCourse(Course& newCourse) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.getName() == newCourse.getName();
        });

    if (it == courses.end()) {
        courses.push_back(newCourse);
        cout << "Course '" << newCourse.getName() << "' added successfully." << endl;
    }
    else {
        cout << "Course '" << newCourse.getName() << "' already exists." << endl;
    }
}

void AcademicOfficer::removeCourse(const string& courseName) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.getName() == courseName;
        });

    if (it != courses.end()) {
        courses.erase(it);
        cout << "Course '" << courseName << "' removed successfully." << endl;
    }
    else {
        cout << "Course '" << courseName << "' not found." << endl;
    }
}

void AcademicOfficer::updateCourse(const string& courseName) {
    auto it = find_if(courses.begin(), courses.end(), [&](const Course& c) {
        return c.getName() == courseName;
        });

    if (it != courses.end()) {
        // Add logic to update the course here.
        cout << "Course '" << courseName << "' updated successfully." << endl;
    }
    else {
        cout << "Course '" << courseName << "' not found." << endl;
    }
}

void AcademicOfficer::addToCourseFile(const Course& course, const string& filename) {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << course.getName() << " " << course.getCourseCode() << endl;
        file.close();
        cout << "Course '" << course.getName() << "' added to file: " << filename << endl;
    }
    else {
        cerr << "Unable to open file: " << filename << endl;
    }
}

int main() {
    string ask;
    cout << "Which Role You are:(Academic Officer == AO and Teacher == Teacher):  ";
    cin >> ask;
    string course_name, code;
    string clo;
    Course c1(course_name, code);
    string question;
    Evaluation eval(question);
    Teacher teacher;
    AcademicOfficer ao;

    if (ask == "AO") {
        cout << "Enter course name: " << endl;
        cin >> course_name;
        cout << "Enter Course Code: " << endl;
        cin >> code;
        Course c1(course_name, code);

        cout << "Enter the CLOs for the course (type 'done' when finished):\n";
        while (true) {
            getline(cin, clo);
            if (clo == "done") break;
            c1.addCLO(CLO(clo));
        }
        string plo;
        cout << "Enter the PLOs for the course (type 'done' when finished):\n";
        while (true) {
            getline(cin, plo);
            if (plo == "done") break;
            c1.addPLO(PLO(plo));
        }
        string u;
        cout << "you wnat to update and Remove: U::R: ";
        cin >> u;
    if (u == "R") {
        string courseToRemove;
        cout << "Enter the name of the course you want to remove: ";
        cin >> courseToRemove;
        ao.removeCourse(courseToRemove);
    }
    else if (u == "U") {
        string courseToUpdate;
        cout << "Enter the name of the course you want to update: ";
        cin >> courseToUpdate;
        ao.updateCourse(courseToUpdate);
    }
        c1.add_to_file("course.txt");
        c1.savePLOsToFile("PLOs.txt");
        c1.saveCLOsToFile("CLOs.txt");

        ao.addCourse(c1);
        ao.addToCourseFile(c1, "AcademicOfficer.txt");
    }
    else if (ask == "Teacher") {
        cout << "Enter evaluation question: " << endl;
        cin >> question;
        Evaluation eval(question);
        cout << "Enter the CLOs tested by this question (type 'done' when finished):\n";
        while (true) {
            getline(cin, clo);
            if (clo == "done") break;
            eval.addTestedCLO(CLO(clo));
        }
        eval.saveToFile("Evaluation.txt");

        vector<CLO> teacherCLOs = eval.getTestedCLOs();
        cout << "CLOs added by Teacher for evaluation: ";
        for (const auto& clo : teacherCLOs) {
            cout << clo.getDescription() << ", ";
        }
        cout << endl;

        Course c1("Teacher's Course", "TC001");
        c1.addEvaluation(eval);

        vector<CLO> aoCLOs = c1.getCLOs();
        cout << "CLOs added by Academic Officer for the course: ";
        for (const auto& clo : aoCLOs) {
            cout << clo.getDescription() << ", ";
        }
        cout << endl;

        bool cloMatch = (aoCLOs == teacherCLOs);
        if (cloMatch) {
            cout << "CLOs match!" << endl;
        }
        else {
            cout << "CLOs do not match!" << endl;
        }

        c1.add_to_file("course.txt");
        teacher.addEvaluation(eval);
    }
   

    return 0;
}
