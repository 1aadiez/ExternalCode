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
        double y;    //���������� y

        sf::Text TXT;    //������������ �����

    public:
        Label(double _x = 0, double _y = 0, std::string _text = "Text")
        {
            font.loadFromFile("Usuallyfont.otf");      //�������� ������ ������ ���� ������

            x = _x;
            y = _y;
            text = _text;                // ��������� �����
            TXT.setFont(font);              // ��������� �����
            TXT.setCharacterSize(20);           // � ��������, � �� ������!
            TXT.setOutlineColor(sf::Color::White);          // ������������� ���� ���������� ������
            TXT.setPosition(x, y);            // ������� ������
        }
        sf::Text displayText()
        {
            TXT.setString(text);            // ��������� � ��������� ����� ����������� �����
            return TXT;
        }
    };

    class Button : public Label {
    protected:
        double width;    // ������ ������
        double height;    // ������ ������
        sf::RectangleShape BOX;  // ������� ������������� � �������� width, height
    public:
        Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, std::string _text = "������")
        {
            font.loadFromFile("Usuallyfont.otf");      //�������� ������ ������ ���� ������

            x = _x;
            y = _y;
            width = _width;
            height = _height;
            text = _text;                // ��������� �����
            TXT.setFont(font);              // ��������� �����
            TXT.setCharacterSize(20);           // � ��������, � �� ������!
            TXT.setOutlineColor(sf::Color::White);          // ������������� ���� ���������� ������
            TXT.setPosition(x, y);            // ������� ������

            BOX.setSize(sf::Vector2f(width, height));    // ������ ������
            BOX.setPosition(x, y);            // ���������� ������
            BOX.setFillColor(sf::Color(133, 133, 133));  // ���� ������
            BOX.setOutlineThickness(2);          // ������ X ��������
            BOX.setOutlineColor(sf::Color(66, 66, 66));    // ���� �������
        }
        //�������� ������� �� ������
        bool select(sf::Vector2i _mouse)
        {
            if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
                return  true;
            }
            else {
                return false;
            }
        }
        //����� ������
        sf::Text displayText()
        {
            TXT.setString(text);  // ��������� � ��������� ����� ����������� �����
            return TXT;
        }
        //����� ������
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
            text = _text;                // ��������� �����
            focus = false;                // ����� ���� �����

            TXT.setFont(font);              // ��������� �����
            TXT.setCharacterSize(20);           // � ��������, � �� ������!
            TXT.setFillColor(sf::Color::Black);          // ������������� ���� ���������� ������
            TXT.setPosition(x, y);            // ������� ������

            BOX.setSize(sf::Vector2f(width, height));    // ������ ���� �����
            BOX.setPosition(x, y);            // ���������� ���� �����
            BOX.setFillColor(sf::Color::White);  // ���� ������
        }
        //����� .resf::Text( char ) �������� ����� ������ ������ ���� ������ Input
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

        // �������� ������ Input
        bool select()
        {
            return focus;
        }
        // ��������� ������ Input
        bool select(sf::Vector2i _mouse)
        {
            if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {   //���� ����� ������ ��� �������� Input...
                focus = true;                                       // ����� true
                text += "|";                                    // � ����� ������ �������� | (��� �� �������� ��� input � ������)
            }
            else {                                        //...����� ���� ������� ��������� �� ��� ��������, ��...
                if (text.size() > 0) {                                // �������� ���������� �������(����� ��������)
                    if (text[text.size() - 1] == 124) {                          // ���� ������ | ...
                        text.erase(text.size() - 1);                            // ... �� ������� ���
                    }
                }
                focus = false;                                    // ������������� ����� false
            }
            return focus;
        }

        //����� ������
        sf::Text displayText()
        {
            TXT.setString(text);            // ��������� � ��������� ����� ����������� �����
            return TXT;
        }

        //����� ���� Input
        sf::RectangleShape displayBOX()
        {
            return BOX;
        }

        //��� ����, ��� �� ������� ����� � ���� Ipnut ���������� ���������  readsf::Text() ������� ���������� std::string
        std::string readText()
        {
            if (text[text.size() - 1] == 124) {   // ������� (���� ����) ������ |
                text.erase(text.size() - 1);
            }
            return text;
        }
    };

}
#endif

