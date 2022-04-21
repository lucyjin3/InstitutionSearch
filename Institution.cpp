#include <iostream>
#include <vector>
#include <string>
#include "Institution.h"

using namespace std;

//Constructors & Destructors
Institution::Institution() {
    name = "";
    institutionalRank = -1;
    state = "";
    avgGPA_lower = -1;
    avgGPA_upper = -1;
    tuition_inState = -1;
    tuition_outOfState = -1;
}

//create from file
Institution::Institution(vector<string> v) {
    //0.NAME, 1.CITY, 2.STATE, 3.ADM_RATE, 4.SAT_READ_LOW, 5.SAT_READ_HIGH,
    // 6.SAT_MATH_LOW, 7.SAT_MATH_HIGH, 8.SAT_AVG, 9.TUITION_IN, 10.TUITION_OUT
    name = v.at(0);
    city = v.at(1);
    state = v.at(2);
    admission_rate = v.at(3);
    //avgGPA_lower = ?              //**GPA??
    //avgGPA_upper = ?
    if (v.at(4) == "NULL" || v.at(6) == "NULL")
        SAT_lower = 0;
    else
        SAT_lower = stoi(v.at(4)) + stoi(v.at(6));

    if (v.at(5) == "NULL" || v.at(7) == "NULL")
        SAT_higher = 0;
    else
        SAT_higher = stoi(v.at(5)) + stoi(v.at(7));

    if (v.at(8) == "NULL")
        SAT_average = 0;
    else
        SAT_average = stoi(v.at(8));

    if (v.at(9) == "NULL")
        tuition_inState = 0;
    else
        tuition_inState = stoi(v.at(9));

    if (v.at(10) == "NULL\r" || v.at(10) == "NULL")
        tuition_outOfState = 0;
    else
        tuition_outOfState = stoi(v.at(10));

    institutionalRank = -1;
}

Institution::~Institution() {

}

//Statistic Retrieval Functions
string Institution::getName() {
    return name;
}

int Institution::getRank() {
    return institutionalRank;
}

string Institution::getState() {
    return state;
}

double Institution::getGPAlower() {
    return avgGPA_lower;
}

double Institution::getGPAupper() {
    return avgGPA_upper;
}

int Institution::getTuitionInState() {
    return tuition_inState;
}

int Institution::getTuitionOutOfState() {
    return tuition_outOfState;
}

int Institution::getSATAverage(){
    return SAT_average;
}

vector<string> Institution::getStats() {
    vector<string> stats;
    stats.push_back(name);
    stats.push_back(to_string(institutionalRank));
    stats.push_back(state);
    stats.push_back(to_string(avgGPA_lower));
    stats.push_back(to_string(avgGPA_upper));
    stats.push_back(to_string(tuition_inState));
    stats.push_back(to_string(tuition_outOfState));

    return stats;
}

void Institution::printStats() {
    cout << name << "\n\t";
    cout << city << ", " << state << "\n\t";
    if (admission_rate != "NULL")
        cout << (stof(admission_rate) * 100) << "% admission rate" << "\n\t";
    if (SAT_lower != 0 && SAT_higher != 0)
        cout << "Average SAT Acceptance Range: " << SAT_lower << " - " << SAT_higher << "\n\t";

    //Adding commas to Tuition
    if (tuition_inState != 0) {
        string s = to_string(tuition_inState);
        for (int i = s.size()-3; i > 0; i--) {
            s.insert(i, ",");
            i -= 2;
        }
        cout << "In-State Tuition: $" << s;
    }
    if (tuition_outOfState != 0) {
        string o = to_string(tuition_outOfState);
        for (int j = o.size()-3; j > 0; j--) {
            o.insert(j, ",");
            j -= 2;
        }
    cout << "\n\tOut-Of-State Tuition: $" << o << "\n\t";
    }
    cout << endl;
}

string Institution::stringStats() {
    string result = name + "\n\t" + city + ", " + state + "\n\t";
    if (admission_rate != "NULL")
        result += to_string(stof(admission_rate) * 100) + "% admission rate" + "\n\t";
    if (SAT_lower != 0 && SAT_higher != 0)
        result + "Average SAT Acceptance Range: " + to_string(SAT_lower) + " - " + to_string(SAT_higher) + "\n\t";

    //Adding commas to Tuition
    if (tuition_inState != 0) {
        string s = to_string(tuition_inState);
        for (int i = s.size()-3; i > 0; i--) {
            s.insert(i, ",");
            i -= 2;
        }
        result += "In-State Tuition: $" + s;
    }
    if (tuition_outOfState != 0) {
        string o = to_string(tuition_outOfState);
        for (int j = o.size()-3; j > 0; j--) {
            o.insert(j, ",");
            j -= 2;
        }
        result += "\n\tOut-Of-State Tuition: $" + o + "\n\t";
    }
    result += "\n";
    return result;
}


