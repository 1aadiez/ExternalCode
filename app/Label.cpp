#include "Label.h"
namespace form {
    Label::Label(double _x, double _y, std::string _text)
    {
        font.loadFromFile("Mostery.ttf");      
        x = _x;
        y = _y;
        text = _text;                
        textout.setFont(font);     
        textout.setStyle(sf::Text::Bold);
        textout.setCharacterSize(30);           
        textout.setOutlineColor(sf::Color::White);          
        textout.setPosition(x, y);            
    }
    Button::Button(double _x, double _y, double _width, double _height, std::string _text) :
        width(_width), height(_height), Label(_x,_y,_text)
    {
        font.loadFromFile("Mostery.ttf");      
        textout.setFont(font);
        textout.setCharacterSize(20);
        textout.setOutlineColor(sf::Color::White);
        textout.setPosition(x, y);            
        rectangle.setSize(sf::Vector2f(width, height));    
        rectangle.setPosition(x, y);            
        rectangle.setFillColor(sf::Color(133, 133, 133));  
        rectangle.setOutlineThickness(2);          
        rectangle.setOutlineColor(sf::Color(66, 66, 66));    
    }
   
    bool Button::select(sf::Vector2i _mouse)
    {
        if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
            return  true;
        }
        else {
            return false;
        }
    }
    Input::Input(double _x, double _y, double _width, double _height, std::string _text) :
        Button(_x, _y, _width, _height, _text)
    {
        focus = false;

        textout.setFont(font);              // setting the font
        textout.setCharacterSize(20);           // size of characters
        textout.setFillColor(sf::Color::Black); // text color
        textout.setPosition(x, y);            // text position

        rectangle.setSize(sf::Vector2f(width, height));    // size of input field
        rectangle.setPosition(x, y);            // position of input field
        rectangle.setFillColor(sf::Color::White);
    }
    void Input::reText(char _tmp)
    {
        text.erase(text.size() - 1);
        if (_tmp != 8)
        {
            text += _tmp;
        }
        else
        {
            if (text.size() > 0)
                text.erase(text.size() - 1);
        }
        text += "|";
        textout.setString(text);
    }
   
    bool Input::select(sf::Vector2i _mouse)
    {
        if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {   
            focus = true;                                       
            text += "|";                                   
        }
        else {                                        
            if (text.size() > 0) {                                
                if (text[text.size() - 1] == 124) {                         
                    text.erase(text.size() - 1);                            
                }
            }
            focus = false;                                    
        }
        return focus;
    }
    std::string Input::readText()
    {
        if (!text.empty())
        {
            if (text[text.size() - 1] == 124) {  
                text.erase(text.size() - 1);
            }
            return text;
        }
        else
            throw std::invalid_argument("Nothing was written");
    }
}
