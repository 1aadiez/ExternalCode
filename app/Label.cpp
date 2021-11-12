#include "Label.h"
namespace form {
    Label::Label(double _x, double _y, std::string _text)
    {
        font.loadFromFile("Mostery.ttf");      //передаем нашему шрифту файл шрифта
        x = _x;
        y = _y;
        text = _text;                // загружает текст
        textout.setFont(font);     
        textout.setStyle(sf::Text::Bold);
        textout.setCharacterSize(30);           // в пикселях, а не точках!
        textout.setOutlineColor(sf::Color::White);          // устанавливаем цвет выводимого текста
        textout.setPosition(x, y);            // позиция текста
    }
    Button::Button(double _x, double _y, double _width, double _height, std::string _text)
    {
        font.loadFromFile("Mostery.ttf");      //передаем нашему шрифту файл шрифта
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        text = _text;
        textout.setFont(font);
        textout.setCharacterSize(20);
        textout.setOutlineColor(sf::Color::White);
        textout.setPosition(x, y);            // позиция текстa
        rectangle.setSize(sf::Vector2f(width, height));    // размер кнопки
        rectangle.setPosition(x, y);            // координаты кнопки
        rectangle.setFillColor(sf::Color(133, 133, 133));  // цвет кнопки
        rectangle.setOutlineThickness(2);          // Контур X пикселей
        rectangle.setOutlineColor(sf::Color(66, 66, 66));    // Цвет контура
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
    Input::Input(double _x, double _y, double _width, double _height, std::string _text)
    {
        x = _x;
        y = _y;
        width = _width;
        height = _height;
        text = _text;
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
        if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {   //Если нажат клаиша над объектом Input...
            focus = true;                                       // Фокус true
            text += "|";                                    // В конец строки добаляем | (что бы понимать что input в фокусе)
        }
        else {                                        //...Иначе если нажатие произошло не над объектом, то...
            if (text.size() > 0) {                                // проверка последнего символа(иначе вылетает)
                if (text[text.size() - 1] == 124) {                          // если символ | ...
                    text.erase(text.size() - 1);                            // ... то удаляем его
                }
            }
            focus = false;                                    // устанавливаем фокус false
        }
        return focus;
    }
    std::string Input::readText()
    {
        if (!text.empty())
        {
            if (text[text.size() - 1] == 124) {   // удаляем (если есть) символ |
                text.erase(text.size() - 1);
            }
            return text;
        }
        else
            throw std::invalid_argument("Nothing was written");
    }
}