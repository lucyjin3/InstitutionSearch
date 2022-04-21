#pragma once
#ifndef HELLOSFML_BUTTON_H
#define HELLOSFML_BUTTON_H
#endif //HELLOSFML_BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

class Button {
private:
    sf::RectangleShape button;
    sf::Text text;
    bool toggled = false;

public:
    Button() { };
    Button(std::string t, sf::Vector2f size, int charSize, sf::Color bgcolor, sf::Color tcolor) {
        text.setString(t);
        text.setColor(tcolor);
        text.setCharacterSize(charSize);

        button.setSize(size);
        button.setFillColor(bgcolor);
    }

    void setFont(sf::Font &font) {
        text.setFont(font);
    }

    void setBackColor(sf::Color color) {
        button.setFillColor(color);
    }

    void setTextColor(sf::Color color) {
        text.setColor(color);
    }

    void setPosition(sf::Vector2f pos) {
        button.setPosition(pos);
        //want text to follow button
        float xPos = (pos.x + button.getGlobalBounds().width/4.0f) - (text.getGlobalBounds().width/2);
        float yPos = (pos.y + button.getGlobalBounds().height/4.0f) - (text.getGlobalBounds().height/2);
        text.setPosition(xPos, yPos);
    }
    float getPositionX() {
        return button.getPosition().x;
    }

    float getPositionY() {
        return button.getPosition().y;
    }

    float getBoundsX() {
        return button.getGlobalBounds().width;
    }

    float getBoundsY() {
        return button.getGlobalBounds().height;
    }

    void toggleBtn() {
        toggled = !toggled;
        if (!toggled)
            setBackColor(sf::Color::Magenta);
        else
            setBackColor(sf::Color::Cyan);
    }

    bool isToggled() {
        return toggled;
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(button);
        window.draw(text);
    }

    bool isMouseOver(sf::RenderWindow &window) {
        float mouseX = sf::Mouse::getPosition(window).x;
        float mouseY = sf::Mouse::getPosition(window).y;

        float btnPosX = button.getPosition().x;
        float btnPosY = button.getPosition().y;

        float btnXposWidth = button.getPosition().x + button.getLocalBounds().width;
        float btnYposHeight = button.getPosition().y + button.getLocalBounds().height;

        //if mouse is within the button
        if(mouseX < btnXposWidth && mouseX > btnPosX && mouseY < btnYposHeight && mouseY > btnPosY) {
            return true;
        }
        return false;
    }
};