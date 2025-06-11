// KapralovLR3-4_Idea.h
#ifndef IDEA_H
#define IDEA_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Idea {
    string name;
    string author;
    int creationYear;
    vector<string> implementations;
    vector<double> costs;

public:
    Idea(string n, string a, int y, vector<string> impl, vector<double> c);
    Idea(const Idea &ob);
    ~Idea() {}

    void setIdea(string n, string a, int y, const vector<string>& impl, const vector<double>& c);
    void setName(string n) { name = n; }
    void setAuthor(string a) { author = a; }
    void setCreationYear(int y) { creationYear = y; }
    string getName() const { return name; }
    string getAuthor() const { return author; }
    int getCreationYear() const { return creationYear; }
    const vector<string> getImplementations() const { return implementations; }
    const vector<double> getCosts() const { return costs; }
    double calculateAverageCost() const;
    Idea operator+(const Idea& other) const;
    bool operator<(const Idea& other) const { return creationYear < other.creationYear; }
    Idea& operator++();
    Idea operator++(int);
    Idea& operator--();
    Idea operator--(int);
    const Idea& operator=(const Idea& other);
    friend ostream& operator<<(ostream& mystream, const Idea &obj);
    friend istream& operator>>(istream& mystream, Idea &obj);
};

#endif