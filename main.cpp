#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <set>
#include <unordered_set>

using namespace std;

class Student {
private:
    string fName;
    string group;
    string Zachetka;
    vector<int> grades;

public:
    Student() : grades(4, 0) {}

    Student(const string& name, const string& grp, const string& num, const vector<int>& grds)
        : fName(name), group(grp), Zachetka(num), grades(grds) {}

    Student(const Student& other)
        : fName(other.fName), group(other.group),
          Zachetka(other.Zachetka), grades(other.grades) {}

    Student(Student&& other) noexcept
        : fName(move(other.fName)), group(move(other.group)),
          Zachetka(move(other.Zachetka)), grades(move(other.grades)) {}

    Student& operator=(const Student& other) {
        if (this != &other) {
            fName = other.fName;
            group = other.group;
            Zachetka = other.Zachetka;
            grades = other.grades;
        }
        return *this;
    }

    Student& operator=(Student&& other) noexcept {
        if (this != &other) {
            fName = move(other.fName);
            group = move(other.group);
            Zachetka = move(other.Zachetka);
            grades = move(other.grades);
        }
        return *this;
    }

    double getAverage() const {
        if (grades.empty()) return 0.0;
        return accumulate(grades.begin(), grades.end(), 0.0) / grades.size();
    }
    
    bool operator==(const Student& other) const {
        return fName == other.fName &&
               group == other.group &&
               Zachetka == other.Zachetka &&
               grades == other.grades;
    }
    
    bool operator<(const Student& other) const {
        return getAverage() < other.getAverage();
    }

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << "FIO: " << student.fName
           << ", Group: " << student.group
           << ", Nomer zachetki: " << student.Zachetka
           << ", Grades: ";
        for (int grade : student.grades) {
            os << grade << " ";
        }
        os << ", Averange ball: " << student.getAverage();
        return os;
    }
    
    string getFName() const { return fName; }
    string getGroup() const { return group; }
    string getZachetka() const { return Zachetka; }
    vector<int> getGrades() const { return grades; }
};


namespace std {
    template<>
    struct hash<Student> {
        size_t operator()(const Student& s) const {
            size_t h1 = hash<string>()(s.getFName());
            size_t h2 = hash<string>()(s.getGroup());
            size_t h3 = hash<string>()(s.getZachetka());

            // Хеш для вектора оценок
            size_t h4 = 0;
            for (int grade : s.getGrades()) {
                h4 ^= hash<int>()(grade) + 0x9e3779b9 + (h4 << 6) + (h4 >> 2);
            }

            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    vector<Student> students;
    string name1, name2, name3, name, group, num;
    vector<int> grades(4);

    while (input >> name1 >> name2 >> name3 >> group >> num >> grades[0] >> grades[1] >> grades[2] >> grades[3]) {
        name = name1 + " " + name2 + " " + name3;
        students.emplace_back(name, group, num, grades);
    }

    output << "(vector):" << endl;
    for (const auto& student : students) {
        output << student << endl;
    }
    output << endl;

    sort(students.begin(), students.end());

    output << "sort (vector):" << endl;
    for (const auto& student : students) {
        output << student << endl;
    }
    output << endl;

    deque<Student> studentsDeque;
    copy(students.begin(), students.end(), back_inserter(studentsDeque));

    output << "copy (deque):" << endl;
    for (const auto& student : studentsDeque) {
        output << student << endl;
    }
    output << endl;
    
    set<Student> studentSet(students.begin(), students.end());
    output << "set (sorted by average grade):" << endl;
    for (const auto& student : studentSet) {
        output << student << endl;
    }
    output << endl;
    
    unordered_set<Student> studentUnorderedSet(students.begin(), students.end());
    output << "unordered_set (no particular order):" << endl;
    for (const auto& student : studentUnorderedSet) {
        output << student << endl;
    }

    input.close();
    output.close();

    return 0;
}
