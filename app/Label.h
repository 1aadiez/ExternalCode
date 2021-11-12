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
        double x;    
        double y;    //Координата y

        sf::Text TXT;    //Отображаемый текст

    public:
        Label(double _x = 0, double _y = 0, std::string _text = "Text")
        {
            font.loadFromFile("Usuallyfont.otf");      //передаем нашему шрифту файл шрифта

            x = _x;
            y = _y;
            text = _text;                // загружает текст
            TXT.setFont(font);              // загружаем фрифт
            TXT.setCharacterSize(20);           // в пикселях, а не точках!
            TXT.setOutlineColor(sf::Color::White);          // устанавливаем цвет выводимого текста
            TXT.setPosition(x, y);            // позиция текста
        }
        sf::Text displayText()
        {
            TXT.setString(text);            // загружаем в выводимый текст загружаемый текст
            return TXT;
        }
    };

    class Button : public Label {
    protected:
        double width;    // Ширина Кнопки
        double height;    // Высота Кнопки
        sf::RectangleShape BOX;  // Создаем прямоугольник с размером width, height
    public:
        Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, std::string _text = "Кнопка")
        {
            font.loadFromFile("Usuallyfont.otf");      //передаем нашему шрифту файл шрифта

            x = _x;
            y = _y;
            width = _width;
            height = _height;
            text = _text;                // загружает текст
            TXT.setFont(font);              // загружаем фрифт
            TXT.setCharacterSize(20);           // в пикселях, а не точках!
            TXT.setOutlineColor(sf::Color::White);          // устанавливаем цвет выводимого текста
            TXT.setPosition(x, y);            // позиция текста

            BOX.setSize(sf::Vector2f(width, height));    // размер кнопки
            BOX.setPosition(x, y);            // координаты кнопки
            BOX.setFillColor(sf::Color(133, 133, 133));  // цвет кнопки
            BOX.setOutlineThickness(2);          // Контур X пикселей
            BOX.setOutlineColor(sf::Color(66, 66, 66));    // Цвет контура
        }
        //Проверка нажатия на кнопку
        bool select(sf::Vector2i _mouse)
        {
            if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
                return  true;
            }
            else {
                return false;
            }
        }
        //Вывод Текста
        sf::Text displayText()
        {
            TXT.setString(text);  // загружаем в выводимый текст загружаемый текст
            return TXT;
        }
        //Вывод кнопки
        sf::RectangleShape displayButton()
        {
            return BOX;
        }


    };

    class Input : public Button {
    protected:
        bool focus;
    public:
        Input(double _x = 0, double _y = 0, double _width = 150, double _height = 30, std::string _text = " ")
        {
            x = _x;
            y = _y;
            width = _width;
            height = _height;
            text = _text;                // загружает текст
            focus = false;                // фокус поля ввода

            TXT.setFont(font);              // загружаем фрифт
            TXT.setCharacterSize(20);           // в пикселях, а не точках!
            TXT.setFillColor(sf::Color::Black);          // устанавливаем цвет выводимого текста
            TXT.setPosition(x, y);            // позиция текста

            BOX.setSize(sf::Vector2f(width, height));    // размер поля ввода
            BOX.setPosition(x, y);            // координаты поля ввода
            BOX.setFillColor(sf::Color::White);  // цвет кнопки
        }
        //метод .resf::Text( char ) изменяет текст внутри класса Типа данных Input
        void reText(char _tmp)
        {
            text.erase(text.size() - 1);

            if (_tmp != 8) {
                text += _tmp;
            }
            else {
                if (text.size() > 0) {
                    text.erase(text.size() - 1);
                }

            }
            text += "|";
            TXT.setString(text);
        }

        // Проверка Фокуса Input
        bool select()
        {
            return focus;
        }
        // Установка Фокуса Input
        bool select(sf::Vector2i _mouse)
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

        //Вывод Текста
        sf::Text displayText()
        {
            TXT.setString(text);            // загружаем в выводимый текст загружаемый текст
            return TXT;
        }

        //Вывод фона Input
        sf::RectangleShape displayBOX()
        {
            return BOX;
        }

        //Для того, что бы считать текст с поля Ipnut необходимо применить  readsf::Text() который возвращает std::string
        std::string readText()
        {
            if (text[text.size() - 1] == 124) {   // удаляем (если есть) символ |
                text.erase(text.size() - 1);
            }
            return text;
        }
    };

}
#endif

