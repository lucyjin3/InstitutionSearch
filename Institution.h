#ifndef PROJECT3_INSTITUTION_H
#define PROJECT3_INSTITUTION_H
#endif //PROJECT3_INSTITUTION_H
#include <iostream>
#include <vector>
using namespace std;

class Institution {
private:
    string name, city, state, admission_rate;
    int institutionalRank;
    float avgGPA_lower;
    float avgGPA_upper;
    int SAT_lower;
    int SAT_higher;
    int SAT_average;
    int tuition_inState;
    int tuition_outOfState;

public:
    Institution();
    Institution(vector<string> v);
    Institution(string name, int institutionalRank, string state, double avgGPA_lower, double avgGPA_upper, int tuition_inState, int tuition_outOfState);
    ~Institution();

    string getName();
    int getRank();
    string getState();
    double getGPAlower();
    double getGPAupper();
    int getTuitionInState();
    int getTuitionOutOfState();
    int getSATAverage();
    void printStats();
    string stringStats();

    //returns all institution's statistics
    vector<string> getStats();

};
