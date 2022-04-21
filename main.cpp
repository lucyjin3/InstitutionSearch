#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Institution.h"
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include <map>

using namespace std;

vector<Institution*> readFile() {
    ifstream file;
    file.open("data.csv", ios_base::in);
    vector<Institution*> v;
    vector<string> row;
    string line, word;
    if (file.is_open()) {
        //while there is still data to read
        while(getline(file, line)) {
            row.clear();
            //read entire row of inst data
            getline(file, line);

            stringstream str(line);

            //read individual attributes
            while(getline(str,word, ',')) {
                row.push_back(word);
            }

            //create a new Institution with attributes
            Institution* inst = new Institution(row);
            v.push_back(inst);
            inst->printStats();
        }
    }
    return v;
}

map<string, vector<Institution*>> sortbystate(vector<Institution*> inst){
    map<string, vector<Institution*>> bystate;  //ordered so it should sort automatically

    for(int i=0; i<inst.size(); i++){
        Institution* chosen = inst[i];     //grab first institution
        string state = chosen->getState(); //grab the state

        bystate[state].push_back(chosen);  //add key and push back into insitution vector
    } //keep going until done looking through vector of institutions made in main

    auto it = bystate.begin();
    while (it != bystate.end()) {
        cout<<"Schools in the state of " << it->first << ":"<< endl;
        vector<Institution*> schools = it->second;

        for(int i=0; i<schools.size(); i++){
            Institution* school = schools[i];
            school->printStats();
        }
        it++;
    }
    return bystate;
};

map<int, vector<Institution*>> sortbyinstatetuition(vector<Institution*> inst){
    map<int, vector<Institution*>> byinstatetuition;  //ordered so it should sort automatically

    for(int i=0; i<inst.size(); i++){
        Institution* chosen = inst[i];     //grab first institution
        int instatetuition = chosen->getTuitionInState(); //grab the in state tuition

        byinstatetuition[instatetuition].push_back(chosen);  //add key and push back into insitution vector
    } //keep going until done looking through vector of institutions made in main

    auto it = byinstatetuition.begin();
    while (it != byinstatetuition.end()) {
        cout<<"Schools with the InState tuition of " << "$"<< it->first << ":"<< endl;
        vector<Institution*> schools = it->second;

        for(int i=0; i<schools.size(); i++){
            Institution* school = schools[i];
            school->printStats();
        }
        it++;
    }

    return byinstatetuition;
};

map<int, vector<Institution*>> sortbyoutstatetuition(vector<Institution*> inst){
    map<int, vector<Institution*>> byoutstatetuition;  //ordered so it should sort automatically

    for(int i=0; i<inst.size(); i++){
        Institution* chosen = inst[i];     //grab first institution
        int instatetuition = chosen->getTuitionInState(); //grab the in state tuition

        byoutstatetuition[instatetuition].push_back(chosen);  //add key and push back into insitution vector
    } //keep going until done looking through vector of institutions made in main

    auto it = byoutstatetuition.begin();
    while (it != byoutstatetuition.end()) {
        cout<<"Schools with the OutState tuition of " << "$"<< it->first << ":"<< endl;
        vector<Institution*> schools = it->second;

        for(int i=0; i<schools.size(); i++){
            Institution* school = schools[i];
            school->printStats();
        }
        it++;
    }

    return byoutstatetuition;
};


map<char, vector<Institution*>> sortAZ(vector<Institution*> inst){
    map<char, vector<Institution*>> AZ;  //ordered so it should sort automatically

    for(int i=0; i<inst.size(); i++){
        Institution* chosen = inst[i];     //grab first institution
        string name = chosen->getName(); //grab the name
        char firstletter = name.at(0); //grab the first letter

        AZ[firstletter].push_back(chosen);  //add key and push back into insitution vector
    } //keep going until done looking through vector of institutions made in main

    cout<<"Schools in order from A-Z"<< endl;
    auto it = AZ.begin();
    while (it != AZ.end()) {
        cout<<"Letter "<< it->first <<":"<<endl;

        vector<Institution*> schools = it->second;
        for(int i=0; i<schools.size(); i++){
            Institution* school = schools[i];
            school->printStats();
        }
        it++;
    }

    return AZ;
};


map<char, vector<Institution*>> sortZA(vector<Institution*> inst){
    map<char, vector<Institution*>> ZA;  //ordered so it should sort automatically

    for(int i=0; i<inst.size(); i++){
        Institution* chosen = inst[i];     //grab first institution
        string name = chosen->getName(); //grab the name
        char firstletter = name.at(0); //grab the first letter

        ZA[firstletter].push_back(chosen);  //add key and push back into insitution vector
    } //keep going until done looking through vector of institutions made in main

    /*cout<<"Schools in order from A-Z"<< endl;
    map<char, vector<Institution*>>::reverse_iterator it;
    for (it = ZA.rbegin(); it != ZA.rend(); it++) {
        cout<<"Letter "<< it->first <<":"<<endl;

        vector<Institution*> schools = it->second;
        for(int i=0; i<schools.size(); i++){
            Institution* school = schools[i];
            school->printStats();
        }
    }*/

    return ZA;

};

vector<Institution*> SATthreshold(vector<Institution*> inst, int score){
    vector<Institution*> threshold;
    for (int i=0; i<inst.size(); i++){
        int schoolscore = inst[i]->getSATAverage();
        if(score<schoolscore){  //if the studentscore is less than what the school asks for he/she cant get in; add to vector
            threshold.push_back(inst[i]);
        }
    }

    cout<<"Schools it would be hard for you to get into because of your SAT score: "<<endl;
    for (int i=0; i<threshold.size(); i++) {
        threshold[i]->printStats();
    }
    return threshold;
}

//SFML FUNCTIONALITY
void sfmlWindow(vector<Institution*> instituteVect) {
    //RENDER WINDOW
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(700,900), "College Data Collection", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition({2500,1000});
    window.setKeyRepeatEnabled(true);

    //RECTANGLE BACKGROUND
    sf::RectangleShape whiteBack;
    whiteBack.setSize({600, 100});
    whiteBack.setPosition({50,50});
    whiteBack.setFillColor(sf::Color::White);

    //FONT
    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    //TEXT
    sf::Text instructions;
    instructions.setString("Student SAT: ");
    instructions.setFont(arial);
    instructions.setCharacterSize(30);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition({100, 100});

    //TEXTBOX
    Textbox textbook1(30, sf::Color::Black, true);
    textbook1.setFont(arial);
    textbook1.setPosition({instructions.getGlobalBounds().width + 130, 100});

    //BUTTONS
    Button stateBtn("STATE", {300, 100}, 35, sf::Color::Magenta, sf::Color::Black);
    stateBtn.setPosition({150, 160});
    stateBtn.setFont(arial);

    Button AtoZBtn("A - Z", {300, 100}, 35, sf::Color::Magenta, sf::Color::Black);
    AtoZBtn.setPosition({150, stateBtn.getPositionY()+stateBtn.getBoundsY()+50});
    AtoZBtn.setFont(arial);

    Button ZtoABtn("Z - A", {300, 100}, 35, sf::Color::Magenta, sf::Color::Black);
    ZtoABtn.setPosition({150, AtoZBtn.getPositionY()+AtoZBtn.getBoundsY()+50});
    ZtoABtn.setFont(arial);

    Button inStateBtn("IN-STATE\nTUITION", {300, 100}, 35, sf::Color::Magenta, sf::Color::Black);
    inStateBtn.setPosition({150, ZtoABtn.getPositionY()+ZtoABtn.getBoundsY()+50});
    inStateBtn.setFont(arial);

    Button outStateBtn("OUT-OF-STATE\n\tTUITION", {300, 100}, 35, sf::Color::Magenta, sf::Color::Black);
    outStateBtn.setPosition({150, inStateBtn.getPositionY()+inStateBtn.getBoundsY()+50});
    outStateBtn.setFont(arial);

    sf::Vector2f MousePosition(sf::Mouse::getPosition(window));

    //MAIN LOOP
    while (window.isOpen())
    {
        sf::Event event;

        //Ensures no weird outputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            textbook1.setSelected(true);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            textbook1.setSelected(false);


        //EVENT LOOP
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return) {
                SATthreshold(instituteVect, stoi(textbook1.getText()));
            }


            //BUTTON CLICK
            if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                //if any buttons pressed, toggle
                if (stateBtn.isMouseOver(window)) {
                    stateBtn.toggleBtn();
                    sortbystate(instituteVect);
                }
                else if (AtoZBtn.isMouseOver(window)) {
                    AtoZBtn.toggleBtn();
                    sortAZ(instituteVect);
                }
                else if (ZtoABtn.isMouseOver(window)) {
                    ZtoABtn.setBackColor(sf::Color::Cyan);
                    sortZA(instituteVect);
                }
                else if (inStateBtn.isMouseOver(window)) {
                    inStateBtn.setBackColor(sf::Color::Cyan);
                    sortbyinstatetuition(instituteVect);
                }
                else if (outStateBtn.isMouseOver(window)) {
                    outStateBtn.setBackColor(sf::Color::Cyan);
                    sortbyoutstatetuition(instituteVect);
                }
                //else
                if (window.hasFocus())
                    textbook1.setSelected(true);
            }

            //TEXTBOX TYPING
            if (event.type == sf::Event::TextEntered)
                textbook1.typedOn(event);

            //HOVERING OVER BUTTONS
            if (event.type == sf::Event::MouseMoved) {
                //if over button && button is not already toggled
                if (stateBtn.isMouseOver(window) && !stateBtn.isToggled()) {
                    stateBtn.setBackColor(sf::Color::Cyan);
                }
                else if (AtoZBtn.isMouseOver(window) && !AtoZBtn.isToggled()) {
                    AtoZBtn.setBackColor(sf::Color::Cyan);
                }
                else if (ZtoABtn.isMouseOver(window) && !ZtoABtn.isToggled()) {
                    ZtoABtn.setBackColor(sf::Color::Cyan);
                }
                else if (inStateBtn.isMouseOver(window) && !inStateBtn.isToggled()) {
                    inStateBtn.setBackColor(sf::Color::Cyan);
                }
                else if (outStateBtn.isMouseOver(window) && !outStateBtn.isToggled()) {
                    outStateBtn.setBackColor(sf::Color::Cyan);
                }
                else {
                    if (!stateBtn.isToggled())
                        stateBtn.setBackColor(sf::Color::Magenta);
                    if (!AtoZBtn.isToggled())
                        AtoZBtn.setBackColor(sf::Color::Magenta);
                    if (!ZtoABtn.isToggled())
                        ZtoABtn.setBackColor(sf::Color::Magenta);
                    if (!inStateBtn.isToggled())
                        inStateBtn.setBackColor(sf::Color::Magenta);
                    if (!outStateBtn.isToggled())
                        outStateBtn.setBackColor(sf::Color::Magenta);
                }
            }
        }


        //CLEAR, DRAW & DISPLAY TO SCREEN
        window.clear();
        //background & basics
        window.draw(whiteBack);
        window.draw(instructions);
        textbook1.drawTo(window);

        //buttons
        stateBtn.drawTo(window);
        AtoZBtn.drawTo(window);
        ZtoABtn.drawTo(window);
        inStateBtn.drawTo(window);
        outStateBtn.drawTo(window);

        window.display();
    }
}

int main() {
    vector<Institution*> instituteVect = readFile();
    sfmlWindow(instituteVect);
    return 0;
}
