#pragma once
#ifndef HELLOSFML_TEXTBOX_H
#define HELLOSFML_TEXTBOX_H
#endif //HELLOSFML_TEXTBOX_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
private:
    sf::Text textbox;
    std::ostringstream text;
    bool isSelected = false;
    bool hasLimit = false;
    int limit;

    void inputLogic(int charTyped) {
        //if pressing regular key
        if(charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
            text << static_cast<char>(charTyped);
        }
            //if pressing delete
        else if (charTyped == DELETE_KEY) {
            //check if there is stuff to delete
            if(text.str().length() > 0) {
                deleteLastChar();
            }
        }
        //Puts _ to show where user is (like cursor)
        textbox.setString((text.str() + "_"));
    }

    void deleteLastChar() {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length()-1; i++) {
            newT += t[i];
        }
        //remove what's there and replace w shortened string
        text.str("");
        text << newT;

        textbox.setString(text.str());
    }

public:
    Textbox() { }

    Textbox(int size, sf::Color color, bool sel) {
        textbox.setCharacterSize(size);
        textbox.setColor(color);
        isSelected = sel;

        if(sel) {
            textbox.setString("_");
        }
        else {
            textbox.setString("");
        }
    }

    //set font!
    void setFont(sf::Font &font) {
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f pos) {
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF) {
        hasLimit = ToF;
    }

    void setLimit(bool ToF, int lim) {
        hasLimit = ToF;
        limit = lim;
    }

    void setSelected(bool sel) {
        isSelected = sel;
        if (!sel) {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length(); i ++) {
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    std::string getText() {
        return text.str();
    }

    void drawTo(sf::RenderWindow &window) {
        window.draw(textbox);
    }

    void typedOn(sf::Event input) {
        if(isSelected) {
            int charTyped = input.text.unicode;
            //valid char
            if (charTyped < 128) {
                inputLogic(charTyped);
            }
        }
    }
};