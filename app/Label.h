#pragma once
#ifndef LABEL_H
#define LABEL_H
#include <iostream>
#include <SFML/Graphics.hpp>
namespace form {
    class Label {
    public:
        std::string text;
        sf::Font font;
    protected:
        double x;    // x coord
        double y;   //y coord
        sf::Text textout;    //output text

    public:
        Label() : x(0), y(0), text("Text") { font.loadFromFile("Mostery.ttf"); };
        Label(double, double, std::string);
        sf::Text displayText()
        {
            textout.setString(text);           
            return textout;
        }
    };

    class Button : public Label {
    protected:
        double width;    // width of the button
        double height;    // height of the button
        sf::RectangleShape rectangle;  // rectangle with some width and height
    public:
        Button() : width(150), height(30) { x = 0; y = 0; text = "Text"; };
        Button(double, double, double, double, std::string);
        bool select(sf::Vector2i); // check if the user selected the button
        sf::Text displayText() //text output
        {
            textout.setString(text);  //adding to output text input text
            return textout;
        }
        sf::RectangleShape displayButton() { return rectangle; }; // button output
    };

    class Input : public Button {
    protected:
        bool focus;
    public:
        Input() : focus(false) { x = 0; y = 0; width = 150; height = 30; text = ""; };
        Input(double, double, double, double, std::string);
        
        void reText(char); //changing text in Input
       
        bool getselect() {
            return focus; //getting focus
        };

        
        bool select(sf::Vector2i); //setting focus
        
        sf::Text displayText() //entering text
        {
            textout.setString(text);
            return textout;
        }
        sf::RectangleShape displayrectangle() { return rectangle; };
        std::string readText();
    };

}
#endif

