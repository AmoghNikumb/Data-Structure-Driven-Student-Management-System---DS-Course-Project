#include <bits/stdc++.h>
using namespace std;

/* ========================================================
   STRUCTS
   ======================================================== */
struct PlacementStudent {
    string name;
    double cgpa;
    int testScore;
    int codingScore;
};

struct AdmissionStudent {
    string name;
    int boardMarks;
    int cetMarks;
    int jeeMarks;
    double priority;
    AdmissionStudent(string n = "", int board = 0, int cet = 0, int jee = 0) {
        name = n;
        boardMarks = board; cetMarks = cet; jeeMarks = jee;
        priority = (jeeMarks * 0.5) + (cetMarks * 0.3) + (boardMarks * 0.2);
    }
};

struct SubjectStudent {
    string name;
    double cgpa;
    vector<int> choices;
    string allotted = "Not Allotted";
};

/* ========================================================
   PLACEMENT FUNCTIONS
   ======================================================== */
bool comparePlacement(const PlacementStudent &a,const PlacementStudent &b){
    if (a.cgpa != b.cgpa) return a.cgpa > b.cgpa;
    else if (a.testScore != b.testScore) return a.testScore > b.testScore;
    else return a.codingScore > b.codingScore;
}
void mergePlacement(vector<PlacementStudent>&arr,int l,int m,int r){
    int n1 = m - l + 1, n2 = r - m;
    vector<PlacementStudent> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (comparePlacement(L[i], R[j])) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void mergeSortPlacement(vector<PlacementStudent>&arr,int l,int r){
    if (l < r) {
        int m = (l + r) / 2;
        mergeSortPlacement(arr, l, m);
        mergeSortPlacement(arr, m + 1, r);
        mergePlacement(arr, l, m, r);
    }
}
vector<PlacementStudent> loadPlacementFromFile(string fname){
    ifstream fin(fname);
    vector<PlacementStudent> v;
    if (!fin) { cerr << "Error opening file!\n"; return v; }
    PlacementStudent s;
    while (fin >> s.name >> s.cgpa >> s.testScore >> s.codingScore) v.push_back(s);
    return v;
}
vector<PlacementStudent> inputPlacementManual(){
    int n;
    cout << "Enter number of students: "; cin >> n;
    vector<PlacementStudent> v(n);
    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << ":\n";
        cout << "Name: "; cin >> v[i].name;
        cout << "CGPA: "; cin >> v[i].cgpa;
        cout << "Test Score: ";
        cin >> v[i].testScore;
        cout << "Coding Score: "; cin >> v[i].codingScore;
    }
    return v;
}
void runPlacement(){
    cout << "\n1. Enter data manually\n2. Load from file\nChoice: ";
    int ch; cin >> ch;
    vector<PlacementStudent> students;
    if (ch == 1) students = inputPlacementManual();
    else { string fname; cout << "Enter filename: ";
    cin >> fname; students = loadPlacementFromFile(fname); }
    if (students.empty()) { cout << "No data!\n"; return;
    }
    mergeSortPlacement(students, 0, (int)students.size() - 1);
    cout << "\n===== Placement Rankings =====\n";
    cout << left << setw(5) << "Rank" << setw(15) << "Name" << setw(6) << "CGPA"
         << setw(12) << "Test" << setw(12) << "Coding" << "\n";
    for (int i = 0; i < (int)students.size(); i++) {
        cout << setw(5) << i + 1 << setw(15) << students[i].name
             << setw(6) << fixed << setprecision(2) << students[i].cgpa
             << setw(12) << students[i].testScore
             << setw(12) << students[i].codingScore << "\n";
    }
}

/* ========================================================
   ADMISSION FUNCTIONS
   ======================================================== */
void mergeAdmission(vector<AdmissionStudent>&arr,int l,int m,int r){
    int n1 = m - l + 1, n2 = r - m;
    vector<AdmissionStudent> L, R;
    for (int i = 0; i < n1; i++) L.push_back(arr[l + i]);
    for (int j = 0; j < n2; j++) R.push_back(arr[m + 1 + j]);
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].priority >= R[j].priority) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}
void mergeSortAdmission(vector<AdmissionStudent>&arr,int l,int r){
    if (l < r) { int m = (l + r) / 2;
    mergeSortAdmission(arr, l, m);
    mergeSortAdmission(arr, m + 1, r);
    mergeAdmission(arr, l, m, r);
    }
}
vector<AdmissionStudent> loadAdmissionFromFile(string fname){
    ifstream fin(fname);
    vector<AdmissionStudent> v;
    if (!fin) { cerr << "Error opening file!\n"; return v; }
    string line;
    while (getline(fin, line)) {
        if (line.empty() || line[0] == '#') continue;
        string name;
        int b, c, j;
        stringstream ss(line);
        if (!getline(ss, name, ',')) continue;
        char comma;
        if (!(ss >> b)) continue;
        ss >> comma;
        if (!(ss >> c)) continue;
        ss >> comma;
        if (!(ss >> j)) continue;
        if (!name.empty() && name.front() == ' ') name.erase(name.begin());
        v.emplace_back(name, b, c, j);
    }
    return v;
}
vector<AdmissionStudent> inputAdmissionManual(){
    int n;
    cout << "Enter number of students: "; cin >> n;
    vector<AdmissionStudent> v;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {
        string name;
        int b, c, j;
        cout << "\nStudent " << i + 1 << ":\n";
        cout << "Name: "; getline(cin, name);
        cout << "Board Marks: "; cin >> b;
        cout << "CET Marks: "; cin >> c;
        cout << "JEE Marks: "; cin >> j;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        v.emplace_back(name, b, c, j);
    }
    return v;
}
void runAdmission(){
    cout << "\n1. Enter data manually\n2. Load from file\nChoice: ";
    int ch; cin >> ch;
    vector<AdmissionStudent> students;
    if (ch == 1) students = inputAdmissionManual();
    else { string fname; cout << "Enter filename: ";
    cin >> fname; students = loadAdmissionFromFile(fname); }
    if (students.empty()) { cout << "No data!\n"; return;
    }
    mergeSortAdmission(students, 0, (int)students.size() - 1);
    cout << "\n===== Admission Priority Ranking =====\n";
    cout << left << setw(5) << "Rank" << setw(20) << "Name"
         << setw(8) << "Board" << setw(6) << "CET"
         << setw(6) << "JEE" << setw(10) << "Priority" << "\n";
    for (int i = 0; i < (int)students.size(); i++) {
        cout << setw(5) << i + 1 << setw(20) << students[i].name
             << setw(8) << students[i].boardMarks
             << setw(6) << students[i].cetMarks
             << setw(6) << students[i].jeeMarks
             << fixed << setprecision(2) << students[i].priority << "\n";
    }
}

/* ========================================================
   SUBJECT-ALLOTMENT FUNCTIONS
   ======================================================== */
map<int,pair<string,int>> subjectMapDefault = {
    {1,{"DBMS",20}}, {2,{"OS",15}}, {3,{"CN",15}},
    {4,{"AI",10}}, {5,{"Cloud",10}}, {6,{"ML",10}}
};
int partition(vector<SubjectStudent>&arr,int low,int high){
    double pivot = arr[high].cgpa; int i = low - 1;
    for (int j = low; j < high; j++) { if (arr[j].cgpa >= pivot) { i++; swap(arr[i], arr[j]);
    } }
    swap(arr[i + 1], arr[high]); return i + 1;
}
void quickSort(vector<SubjectStudent>&arr,int low,int high){
    if (low < high) { int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1); quickSort(arr, pi + 1, high); }
}
vector<SubjectStudent> loadSubjectsFromFile(string fname){
    ifstream fin(fname); vector<SubjectStudent> v;
    if (!fin) { cerr << "Error opening file!\n"; return v; }
    int n;
    if (!(fin >> n)) return v;
    v.resize(n);
    for (int i = 0; i < n; i++) { v[i].choices.resize(3);
    fin >> v[i].name >> v[i].cgpa >> v[i].choices[0] >> v[i].choices[1] >> v[i].choices[2];
    }
    return v;
}
vector<SubjectStudent> inputSubjectsManual(){
    int n; cout << "Enter number of students: "; cin >> n;
    vector<SubjectStudent> v(n);
    for (int i = 0; i < n; i++) {
        cout << "\nStudent " << i + 1 << ":\n";
        cout << "Name: "; cin >> v[i].name;
        cout << "CGPA: "; cin >> v[i].cgpa;
        v[i].choices.resize(3);
        cout << "1st Preference: ";
        cin >> v[i].choices[0];
        cout << "2nd Preference: "; cin >> v[i].choices[1];
        cout << "3rd Preference: "; cin >> v[i].choices[2];
    }
    return v;
}
void runSubjectAllotment(){
    cout << "\nAvailable Subjects:\n";
    for (auto &s : subjectMapDefault) cout << s.first << " -> " << s.second.first << " (Capacity: " << s.second.second << ")\n";
    cout << "\n1. Enter data manually\n2. Load from file\nChoice: ";
    int ch; cin >> ch; vector<SubjectStudent> students;
    if (ch == 1) students = inputSubjectsManual();
    else { string fname; cout << "Enter filename: "; cin >> fname;
    students = loadSubjectsFromFile(fname); }
    if (students.empty()) { cout << "No data!\n"; return;
    }
    auto subjectMap = subjectMapDefault;
    quickSort(students, 0, (int)students.size() - 1);
    for (auto &s : students) {
        for (int pref : s.choices) { if (subjectMap[pref].second > 0) { s.allotted = subjectMap[pref].first;
    subjectMap[pref].second--; break; } }
    }
    cout << "\n===== Final Subject Allotment =====\n";
    cout << left << setw(12) << "Name" << setw(8) << "CGPA" << setw(20) << "Choices" << setw(15) << "Allotted" << "\n";
    for (auto &s : students) {
        cout << setw(12) << s.name << setw(8) << s.cgpa;
    string prefStr = ""; for (int c : s.choices) prefStr += to_string(c) + " ";
    cout << setw(20) << prefStr << setw(15) << s.allotted << "\n";
    }
}

/* ========================================================
   ASSIGNMENT TRACKER - PRIORITY QUEUE VERSION
   ======================================================== */

struct Assignment {
    int id;
    string name;
    string subject;
    string batch;
    string teacher;
    int deadline;
    string description;
    
    Assignment() : id(0), deadline(0) {}
    Assignment(int i, string n, string s, string b, string t, int d, string desc) 
        : id(i), name(n), subject(s), batch(b), teacher(t), deadline(d), description(desc) {}
};

struct CompareDeadline {
    bool operator()(const Assignment& a, const Assignment& b) {
        return a.deadline > b.deadline;
    }
};

priority_queue<Assignment, vector<Assignment>, CompareDeadline> assignmentPQ;
map<int, Assignment> assignmentMap;
vector<string> students;
int nextId = 1;

void addAssignment(string name, string subject, string batch, string teacher, int deadline, string desc) {
    Assignment newAssignment(nextId++, name, subject, batch, teacher, deadline, desc);
    assignmentPQ.push(newAssignment);
    assignmentMap[newAssignment.id] = newAssignment;
    cout << "Assignment added with ID: " << newAssignment.id << "\n";
}

void teacherAddAssignment() {
    cout << "\n=== ADD ASSIGNMENT ===\n";
    string name, subject, batch, teacher, desc;
    int deadline;
    
    cin.ignore();
    cout << "Assignment Name: ";
    getline(cin, name);
    cout << "Subject: ";
    getline(cin, subject);
    cout << "Batch: ";
    getline(cin, batch);
    cout << "Teacher: ";
    getline(cin, teacher);
    cout << "Days until deadline: ";
    cin >> deadline;
    cin.ignore();
    cout << "Description: ";
    getline(cin, desc);
    
    addAssignment(name, subject, batch, teacher, deadline, desc);
}

void teacherViewAll() {
    if (assignmentMap.empty()) {
        cout << "No assignments found!\n";
        return;
    }
    
    vector<Assignment> tempList;
    priority_queue<Assignment, vector<Assignment>, CompareDeadline> tempPQ = assignmentPQ;
    
    while (!tempPQ.empty()) {
        tempList.push_back(tempPQ.top());
        tempPQ.pop();
    }
    
    cout << "\n=== ALL ASSIGNMENTS (Sorted by Deadline) ===\n";
    cout << left << setw(4) << "ID" << setw(20) << "Name" << setw(12) << "Subject" 
         << setw(12) << "Batch" << setw(15) << "Teacher" << setw(12) << "Deadline" << "\n";
    cout << string(75, '-') << "\n";
    
    for (const auto& a : tempList) {
        string deadlineStr = (a.deadline == 0) ? "TODAY" : 
                           (a.deadline == 1) ? "Tomorrow" : 
                           to_string(a.deadline) + " days";
        
        cout << left << setw(4) << a.id 
             << setw(20) << a.name.substr(0, 18)
             << setw(12) << a.subject.substr(0, 10)
             << setw(12) << a.batch
             << setw(15) << a.teacher.substr(0, 13)
             << setw(12) << deadlineStr << "\n";
    }
}

void teacherDeleteAssignment() {
    if (assignmentMap.empty()) {
        cout << "No assignments to delete!\n";
        return;
    }
    
    teacherViewAll();
    cout << "Enter Assignment ID to delete: ";
    int id;
    cin >> id;
    
    if (assignmentMap.find(id) != assignmentMap.end()) {
        cout << "Delete '" << assignmentMap[id].name << "'? (y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            assignmentMap.erase(id);
            
            priority_queue<Assignment, vector<Assignment>, CompareDeadline> newPQ;
            for (const auto& pair : assignmentMap) {
                newPQ.push(pair.second);
            }
            assignmentPQ = newPQ;
            
            cout << "Assignment deleted!\n";
        }
    } else {
        cout << "Assignment not found!\n";
    }
}

void teacherMenu() {
    int choice;
    do {
        cout << "\n=== TEACHER PORTAL ===\n";
        cout << "1. Add Assignment\n";
        cout << "2. View All Assignments\n";
        cout << "3. Delete Assignment\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: teacherAddAssignment(); break;
            case 2: teacherViewAll(); break;
            case 3: teacherDeleteAssignment(); break;
            case 0: cout << "Going back...\n"; break;
            default: cout << "Invalid choice!\n"; break;
        }
    } while (choice != 0);
}

void registerStudent() {
    cout << "\n=== STUDENT REGISTRATION ===\n";
    string student;
    cin.ignore();
    cout << "Enter 'Name-Batch' (e.g., John-CS2024): ";
    getline(cin, student);
    students.push_back(student);
    cout << "Student registered: " << student << "\n";
}

void studentViewAssignments() {
    if (students.empty()) {
        cout << "No students registered!\n";
        return;
    }
    
    cout << "Enter your Name-Batch: ";
    string studentInfo;
    cin.ignore();
    getline(cin, studentInfo);
    
    size_t pos = studentInfo.find('-');
    if (pos == string::npos) {
        cout << "Invalid format! Use 'Name-Batch'\n";
        return;
    }
    
    string batch = studentInfo.substr(pos + 1);
    string name = studentInfo.substr(0, pos);
    
    bool found = false;
    for (const auto& s : students) {
        if (s == studentInfo) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "Student not registered! Please register first.\n";
        return;
    }
    
    cout << "\n=== ASSIGNMENTS FOR " << name << " (Batch: " << batch << ") ===\n";
    
    vector<Assignment> batchAssignments;
    priority_queue<Assignment, vector<Assignment>, CompareDeadline> tempPQ = assignmentPQ;
    
    while (!tempPQ.empty()) {
        Assignment a = tempPQ.top();
        tempPQ.pop();
        if (a.batch == batch) {
            batchAssignments.push_back(a);
        }
    }
    
    if (batchAssignments.empty()) {
        cout << "No assignments for your batch.\n";
        return;
    }
    
    for (const auto& a : batchAssignments) {
        cout << "\n--- " << a.name << " ---\n";
        cout << "Subject: " << a.subject << "\n";
        cout << "Teacher: " << a.teacher << "\n";
        
        if (a.deadline == 0) {
            cout << "Deadline: DUE TODAY! (URGENT)\n";
        } else if (a.deadline == 1) {
            cout << "Deadline: Due Tomorrow (URGENT)\n";
        } else if (a.deadline <= 3) {
            cout << "Deadline: " << a.deadline << " days (URGENT)\n";
        } else {
            cout << "Deadline: " << a.deadline << " days\n";
        }
        
        cout << "Description: " << a.description << "\n";
        cout << string(40, '-') << "\n";
    }
}

void studentViewUrgent() {
    if (students.empty()) {
        cout << "No students registered!\n";
        return;
    }
    
    cout << "Enter your Name-Batch: ";
    string studentInfo;
    cin.ignore();
    getline(cin, studentInfo);
    
    size_t pos = studentInfo.find('-');
    if (pos == string::npos) {
        cout << "Invalid format!\n";
        return;
    }
    
    string batch = studentInfo.substr(pos + 1);
    
    cout << "\n=== URGENT ASSIGNMENTS (3 days or less) ===\n";
    
    vector<Assignment> urgentAssignments;
    priority_queue<Assignment, vector<Assignment>, CompareDeadline> tempPQ = assignmentPQ;
    
    while (!tempPQ.empty()) {
        Assignment a = tempPQ.top();
        tempPQ.pop();
        if (a.batch == batch && a.deadline <= 3) {
            urgentAssignments.push_back(a);
        }
    }
    
    if (urgentAssignments.empty()) {
        cout << "No urgent assignments!\n";
        return;
    }
    
    for (const auto& a : urgentAssignments) {
        cout << "- " << a.name << " (" << a.subject << ")\n";
        cout << "  Teacher: " << a.teacher << "\n";
        
        if (a.deadline == 0) {
            cout << "  DUE TODAY!\n";
        } else {
            cout << "  " << a.deadline << " days left\n";
        }
        cout << "\n";
    }
}

void studentMenu() {
    int choice;
    do {
        cout << "\n=== STUDENT PORTAL ===\n";
        cout << "1. Register Student\n";
        cout << "2. View My Assignments\n";
        cout << "3. View Urgent Assignments\n";
        cout << "0. Back\n";
        cout << "Choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: registerStudent(); break;
            case 2: studentViewAssignments(); break;
            case 3: studentViewUrgent(); break;
            case 0: cout << "Going back...\n"; break;
            default: cout << "Invalid choice!\n"; break;
        }
    } while (choice != 0);
}

void saveToFile() {
    ofstream file("assignments.txt");
    for (const auto& pair : assignmentMap) {
        const Assignment& a = pair.second;
        file << a.id << "|" << a.name << "|" << a.subject << "|" 
             << a.batch << "|" << a.teacher << "|" << a.deadline << "|" 
             << a.description << "\n";
    }
    file.close();
    
    ofstream studentFile("students.txt");
    for (const auto& s : students) {
        studentFile << s << "\n";
    }
    studentFile.close();
    
    cout << "Data saved!\n";
}

void loadFromFile() {
    ifstream file("assignments.txt");
    if (file.is_open()) {
        assignmentMap.clear();
        while (!assignmentPQ.empty()) assignmentPQ.pop();
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Assignment a;
            string temp;
            
            getline(ss, temp, '|'); a.id = stoi(temp);
            getline(ss, a.name, '|');
            getline(ss, a.subject, '|');
            getline(ss, a.batch, '|');
            getline(ss, a.teacher, '|');
            getline(ss, temp, '|'); a.deadline = stoi(temp);
            getline(ss, a.description, '|');
            
            assignmentPQ.push(a);
            assignmentMap[a.id] = a;
            if (a.id >= nextId) nextId = a.id + 1;
        }
        file.close();
        cout << "Assignments loaded!\n";
    }
    
    ifstream studentFile("students.txt");
    if (studentFile.is_open()) {
        students.clear();
        string student;
        while (getline(studentFile, student)) {
            students.push_back(student);
        }
        studentFile.close();
        cout << "Students loaded!\n";
    }
}

void showStats() {
    cout << "\n=== SYSTEM STATISTICS ===\n";
    cout << "Total Assignments: " << assignmentMap.size() << "\n";
    cout << "Total Students: " << students.size() << "\n";
    
    int urgent = 0;
    for (const auto& pair : assignmentMap) {
        if (pair.second.deadline <= 3) urgent++;
    }
    cout << "Urgent Assignments: " << urgent << "\n";
    
    if (!assignmentMap.empty()) {
        cout << "\nNext 3 Most Urgent:\n";
        priority_queue<Assignment, vector<Assignment>, CompareDeadline> tempPQ = assignmentPQ;
        int count = 0;
        while (!tempPQ.empty() && count < 3) {
            Assignment a = tempPQ.top();
            tempPQ.pop();
            cout << (count + 1) << ". " << a.name << " - " << a.deadline << " days\n";
            count++;
        }
    }
}

/* ========================================================
   TIMETABLE MANAGEMENT (DLL + STACK BACKTRACKING)
   ======================================================== */
struct Exam {
    string subject;
    string date;
    string time;
    string venue;
    Exam(string s="",string d="",string t="",string v=""):subject(s),date(d),time(t),venue(v){}
};

struct Node {
    Exam data;
    Node* prev;
    Node* next;
    Node(Exam e):data(e),prev(NULL),next(NULL){}
};

class Timetable {
    Node* head;
    Node* tail;
    stack<vector<Exam>> history;

    void saveState(){
        vector<Exam> snapshot;
        Node* temp = head;
        while (temp) { snapshot.push_back(temp->data); temp = temp->next; }
        history.push(snapshot);
    }

public:
    Timetable():head(NULL),tail(NULL){}

    void addExam(string s,string d,string t,string v){
        saveState();
        Exam e(s,d,t,v);
        Node* newNode = new Node(e);
        if (!head) { head = tail = newNode;
        }
        else { tail->next = newNode; newNode->prev = tail; tail = newNode;
        }
        cout << "Exam added!\n";
    }

    void viewForward(){
        if (!head) { cout << "No exams scheduled!\n";
        return; }
        cout << "\n--- TIMETABLE (Forward) ---\n";
        Node* temp = head;
        int i = 1;
        while (temp) {
            cout << i++ << ". " << temp->data.subject << " | " << temp->data.date << " | " << temp->data.time << " | " << temp->data.venue << "\n";
        temp = temp->next;
        }
    }

    void viewBackward(){
        if (!tail) { cout << "No exams scheduled!\n";
        return; }
        cout << "\n--- TIMETABLE (Backward) ---\n";
        Node* temp = tail;
        int i = 1;
        while (temp) {
            cout << i++ << ". " << temp->data.subject << " | " << temp->data.date << " | " << temp->data.time << " | " << temp->data.venue << "\n";
        temp = temp->prev;
        }
    }

    void deleteExam(string subject){
        if (!head) { cout << "No exams to delete!\n";
        return; }
        saveState();
        Node* temp = head;
        while (temp && temp->data.subject != subject) temp = temp->next;
        if (!temp) { cout << "Exam not found!\n"; return;
        }
        if (temp == head) head = head->next;
        if (temp == tail) tail = tail->prev;
        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        delete temp;
        cout << "Exam deleted!\n";
    }

    void undo(){
        if (history.empty()) { cout << "No previous state to undo!\n";
        return; }
        vector<Exam> snapshot = history.top(); history.pop();
        while (head) { Node* tmp = head; head = head->next; delete tmp;
        }
        head = tail = NULL;
        for (auto &e : snapshot) {
            Node* newNode = new Node(e);
        if (!head) head = tail = newNode;
            else { tail->next = newNode; newNode->prev = tail; tail = newNode;
        }
        }
        cout << "Undo successful!\n";
    }

    void run(){
        int ch;
        do{
            cout << "\n=== EXAM TIMETABLE MANAGER ===\n";
            cout << "1. Add Exam\n2. View Forward\n3. View Backward\n4. Delete Exam\n5. Undo\n0. Back\nChoice: ";
            cin >> ch;
        if (ch == 1){
                string s,d,t,v;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Subject: "; getline(cin,s);
                cout << "Date (dd-mm-yyyy): "; getline(cin,d);
                cout << "Time (HH:MM): "; getline(cin,t);
            cout << "Venue: "; getline(cin,v);
                addExam(s,d,t,v);
            }
            else if (ch == 2) viewForward();
        else if (ch == 3) viewBackward();
            else if (ch == 4){
                string sub;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter subject to delete: "; getline(cin,sub);
                deleteExam(sub);
        }
            else if (ch == 5) undo();
        } while (ch != 0);
    }
};

/* ========================================================
   LIBRARY SYSTEM (STACK + LINKED LIST)
   ======================================================== */
struct Book {
    int id;
    string title;
    Book* next;
    Book(int i,string t):id(i),title(t),next(NULL){}
};

class Library {
    Book* head;
    map<string, stack<string>> history;
public:
    Library():head(NULL){}
    void addBook(int id,string title){
        Book* newBook = new Book(id,title);
        newBook->next = head;
        head = newBook;
    }
    void viewBooks(){
        if (!head) { cout << "No books in library!\n";
        return;}
        cout << "\n--- LIBRARY BOOK LIST ---\n";
        Book* temp = head;
        while (temp) {
            cout << "[" << temp->id << "] " << temp->title << "\n";
        temp = temp->next;
        }
    }
    void borrowBook(string student,int id){
        Book* temp = head, *prev = NULL;
        while (temp && temp->id != id) { prev = temp; temp = temp->next;
        }
        if (!temp) { cout << "Book not found!\n"; return;
        }
        if (prev) prev->next = temp->next;
        else head = temp->next;
        history[student].push(temp->title);
        cout << student << " borrowed \"" << temp->title << "\"\n";
        delete temp;
    }
    void returnBook(string student){
        if (history[student].empty()) { cout << "No history for " << student << "\n";
        return; }
        string title = history[student].top();
        history[student].pop();
        int newId = rand() % 1000 + 100;
        addBook(newId, title);
        cout << student << " returned \"" << title << "\"\n";
    }
    void viewHistory(string student){
        if (history[student].empty()) { cout << "No borrow history for " << student << "\n";
        return; }
        cout << "\nBorrow history for " << student << ":\n";
        stack<string> temp = history[student];
        while (!temp.empty()) { cout << "- " << temp.top() << "\n"; temp.pop();
        }
    }
    void run(){
        int ch;
        do{
            cout << "\n=== LIBRARY SYSTEM ===\n1.Add Book\n2.View Books\n3.Borrow Book\n4.Return Book\n5.View History\n0.Back\nChoice: ";
        cin >> ch;
            if (ch == 1){
                int id;
            string title;
                cout << "Book ID: "; cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << "Title: "; getline(cin,title);
                addBook(id,title);
        }
            else if (ch == 2) viewBooks();
        else if (ch == 3){
                string name;
            int id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Student Name: "; getline(cin,name);
                cout << "Book ID to borrow: "; cin >> id;
        borrowBook(name,id);
            }
            else if (ch == 4){
                string name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Student Name: "; getline(cin,name);
                returnBook(name);
            }
            else if (ch == 5){
                string name;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Student Name: "; getline(cin,name);
                viewHistory(name);
            }
        } while (ch != 0);
    }
};

/* ========================================================
   CAMPUS NAVIGATION SYSTEM - DIJKSTRA'S ALGORITHM
   ======================================================== */

#define INF 1e9

class CampusNavigation {
private:
    map<string, int> locationIndex;
    vector<string> locationNames;
    vector<vector<pair<int, int>>> adjList;
    int numLocations;

    void initializeDefaultCampus() {
        locationNames = {
            "Main_Gate", "Library", "Canteen", "Lab_Building",
            "Auditorium", "Sports_Complex", "Admin_Block", "Hostel",
            "Parking", "Medical_Center"
        };
        
        numLocations = locationNames.size();
        
        for (int i = 0; i < numLocations; i++) {
            locationIndex[locationNames[i]] = i;
        }
        
        adjList.resize(numLocations);
        
        // Add edges (location1, location2, distance in meters)
        addEdge("Main_Gate", "Parking", 50);
        addEdge("Main_Gate", "Admin_Block", 100);
        addEdge("Parking", "Library", 150);
        addEdge("Admin_Block", "Library", 120);
        addEdge("Admin_Block", "Auditorium", 80);
        addEdge("Library", "Lab_Building", 200);
        addEdge("Library", "Canteen", 100);
        addEdge("Canteen", "Lab_Building", 150);
        addEdge("Canteen", "Sports_Complex", 180);
        addEdge("Lab_Building", "Hostel", 250);
        addEdge("Auditorium", "Medical_Center", 90);
        addEdge("Sports_Complex", "Hostel", 200);
        addEdge("Medical_Center", "Hostel", 160);
        addEdge("Parking", "Medical_Center", 140);
        
        cout << "Default campus map loaded with " << numLocations << " locations.\n";
    }

    void addEdge(string loc1, string loc2, int distance) {
        int u = locationIndex[loc1];
        int v = locationIndex[loc2];
        adjList[u].push_back({v, distance});
        adjList[v].push_back({u, distance}); // Undirected graph
    }

    vector<int> dijkstra(int source) {
        vector<int> dist(numLocations, INF);
        vector<int> parent(numLocations, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto &edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }

    void printPath(int source, int dest, vector<int> parent) {
        if (dest == source) {
            cout << locationNames[source];
            return;
        }
        if (parent[dest] == -1) {
            cout << "No path exists!";
            return;
        }
        printPath(source, parent[dest], parent);
        cout << " -> " << locationNames[dest];
    }

    vector<int> getParentArray(int source) {
        vector<int> dist(numLocations, INF);
        vector<int> parent(numLocations, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            
            if (d > dist[u]) continue;
            
            for (auto &edge : adjList[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return parent;
    }

public:
    CampusNavigation() {
        numLocations = 0;
    }

    void displayLocations() {
        cout << "\n=== CAMPUS LOCATIONS ===\n";
        for (int i = 0; i < numLocations; i++) {
            cout << i + 1 << ". " << locationNames[i] << "\n";
        }
    }

    void findShortestPath() {
        if (numLocations == 0) {
            cout << "Please initialize the campus map first!\n";
            return;
        }

        displayLocations();
        
        string sourceName, destName;
        cout << "\nEnter source location: ";
        cin >> sourceName;
        cout << "Enter destination location: ";
        cin >> destName;
        
        if (locationIndex.find(sourceName) == locationIndex.end()) {
            cout << "Source location not found!\n";
            return;
        }
        if (locationIndex.find(destName) == locationIndex.end()) {
            cout << "Destination location not found!\n";
            return;
        }
        
        int source = locationIndex[sourceName];
        int dest = locationIndex[destName];
        
        vector<int> dist = dijkstra(source);
        vector<int> parent = getParentArray(source);
        
        cout << "\n=== SHORTEST PATH RESULT ===\n";
        cout << "From: " << sourceName << "\n";
        cout << "To: " << destName << "\n";
        
        if (dist[dest] == INF) {
            cout << "No path exists between these locations!\n";
        } else {
            cout << "Distance: " << dist[dest] << " meters\n";
            cout << "Path: ";
            printPath(source, dest, parent);
            cout << "\n";
        }
    }

    void showAllDistances() {
        if (numLocations == 0) {
            cout << "Please initialize the campus map first!\n";
            return;
        }

        displayLocations();
        
        string sourceName;
        cout << "\nEnter source location: ";
        cin >> sourceName;
        
        if (locationIndex.find(sourceName) == locationIndex.end()) {
            cout << "Location not found!\n";
            return;
        }
        
        int source = locationIndex[sourceName];
        vector<int> dist = dijkstra(source);
        
        cout << "\n=== DISTANCES FROM " << sourceName << " ===\n";
        cout << left << setw(20) << "Destination" << setw(15) << "Distance (m)" << "\n";
        cout << string(35, '-') << "\n";
        
        for (int i = 0; i < numLocations; i++) {
            if (i != source) {
                cout << left << setw(20) << locationNames[i];
                if (dist[i] == INF) {
                    cout << "Unreachable\n";
                } else {
                    cout << dist[i] << " m\n";
                }
            }
        }
    }

    void addCustomLocation() {
        string newLocation;
        cout << "Enter new location name (use underscore for spaces): ";
        cin >> newLocation;
        
        if (locationIndex.find(newLocation) != locationIndex.end()) {
            cout << "Location already exists!\n";
            return;
        }
        
        locationIndex[newLocation] = numLocations;
        locationNames.push_back(newLocation);
        numLocations++;
        adjList.resize(numLocations);
        
        cout << "Location added! Now add connections to existing locations.\n";
        cout << "How many connections? ";
        int n;
        cin >> n;
        
        for (int i = 0; i < n; i++) {
            string connectedTo;
            int distance;
            cout << "Connect to location: ";
            cin >> connectedTo;
            
            if (locationIndex.find(connectedTo) == locationIndex.end()) {
                cout << "Location not found! Skipping...\n";
                continue;
            }
            
            cout << "Distance (meters): ";
            cin >> distance;
            
            addEdge(newLocation, connectedTo, distance);
            cout << "Connection added!\n";
        }
    }

    void displayCampusMap() {
        if (numLocations == 0) {
            cout << "No campus map loaded!\n";
            return;
        }

        cout << "\n=== CAMPUS MAP (Adjacency List) ===\n";
        for (int i = 0; i < numLocations; i++) {
            cout << locationNames[i] << " -> ";
            for (auto &edge : adjList[i]) {
                cout << locationNames[edge.first] << "(" << edge.second << "m) ";
            }
            cout << "\n";
        }
    }

    void run() {
        int choice;
        
        cout << "\n=== CAMPUS NAVIGATION SYSTEM ===\n";
        cout << "Initializing default campus map...\n";
        initializeDefaultCampus();
        
        do {
            cout << "\n=== CAMPUS NAVIGATION MENU ===\n";
            cout << "1. Find Shortest Path between two locations\n";
            cout << "2. Show all distances from a location\n";
            cout << "3. Display all campus locations\n";
            cout << "4. Display campus map (connections)\n";
            cout << "5. Add new location\n";
            cout << "0. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> choice;
            
            switch (choice) {
                case 1: findShortestPath(); break;
                case 2: showAllDistances(); break;
                case 3: displayLocations(); break;
                case 4: displayCampusMap(); break;
                case 5: addCustomLocation(); break;
                case 0: cout << "Returning to main menu...\n"; break;
                default: cout << "Invalid choice!\n"; break;
            }
        } while (choice != 0);
    }
};

/* ========================================================
   MAIN MENU
   ======================================================== */
int main(){
    srand((unsigned)time(NULL));
    Timetable tt;
    Library lib;
    CampusNavigation cn;
    
    loadFromFile();

    int choice;
    do{
        cout << "\n========= STUDENT MANAGEMENT SYSTEM =========\n";
        cout << "1. Placement Ranking\n";
        cout << "2. Admission Ranking\n";
        cout << "3. Subject Allotment\n";
        cout << "4. Assignment Deadline Manager (Priority Queue)\n";
        cout << "5. Exam Timetable Manager\n";
        cout << "6. Library System\n";
        cout << "7. Campus Navigation (Dijkstra's Algorithm)\n";
        cout << "8. Seed sample books (for testing)\n";
        cout << "9. View Assignment Statistics\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: runPlacement(); break;
            case 2: runAdmission(); break;
            case 3: runSubjectAllotment(); break;
            case 4: 
                int subChoice;
                cout << "\n--- Assignment Manager (Priority Queue) ---\n";
                cout << "1. Teacher Portal\n";
                cout << "2. Student Portal\n";
                cout << "0. Back\n";
                cout << "Choice: ";
                cin >> subChoice;
                if (subChoice == 1) teacherMenu();
                else if (subChoice == 2) studentMenu();
                break;
            case 5: tt.run(); break;
            case 6: lib.run(); break;
            case 7: cn.run(); break;
            case 8: {
                lib.addBook(101, "Data Structures");
                lib.addBook(102, "Operating Systems");
                lib.addBook(103, "Database Systems");
                cout << "Sample books added.\n";
                break;
            }
            case 9: showStats(); break;
            case 0: 
                saveToFile();
                cout << "Exiting...\n"; 
                break;
            default: cout << "Invalid choice. Try again.\n"; break;
        }
    } while (choice != 0);

    return 0;
}