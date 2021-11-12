#include <iostream>
#include <clocale>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#include "../External/hashtable.h"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "Label.h"    

int main()
{
    setlocale(LC_ALL, "Russian");
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "IDfinder");
    sf::Font fontas;
    if (!fontas.loadFromFile("Mostery.ttf"))
        std::cerr << "Not found";
    sf::Text text("",fontas,20);
    form::Button buttonadd(450, 30,150,30, "Add");
    form::Button buttonfind(450, 70, 150, 30, "Find");
    form::Button buttondelete(450, 110, 150, 30, "Delete");
    form::Button buttonshow(450, 150, 150, 30, "Show");
    form::Input inputkey(670, 70, 200, 30,"");
    form::Input inputstr(670, 150, 200, 30, "");
    sf::Text textkey("Enter id: ", fontas, 25);
    textkey.setPosition(670, 30);
    sf::Text textstr("Enter surname:", fontas, 25);
    textstr.setPosition(670, 110);
    form::Label label(1000, 150, "WELCOME TO SURNAME FINDER BY ID");
    text.setStyle(sf::Text::Bold);
    htable::HTable tab(4);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    if (buttonadd.select(mouse)) 
                    { 
                        int flag = 1;
                        try {
                            tab.add(stoi(inputkey.readText()), inputstr.readText());
                        }
                        catch (std::invalid_argument& ia)
                        {
                            text.setString(ia.what());
                            flag = 0;
                        }
                        catch (std::out_of_range& of)
                        {
                            text.setString(of.what());
                            flag = 0;
                        }
                        if (flag)
                            text.setString("Added");
                        
                    }
                    if (buttonfind.select(mouse))
                    {
                        int flag = 1;
                        try 
                        {
                            tab.get(stoi(inputkey.readText()));
                        }
                        catch (std::invalid_argument& ia)
                        {
                            text.setString(ia.what());
                            flag = 0;
                        }    
                        if (flag == 1)
                        {
                            std::string res = std::to_string(tab.get(stoi(inputkey.text)).get_key()) + " => " + tab.get(stoi(inputkey.text)).get_data();
                            text.setString("Found:\n"+res);
                        }                           
                    }
                    if (buttondelete.select(mouse))
                    {
                        int flag = 1;
                        try 
                        {
                            tab.remove(stoi(inputkey.readText()));
                            tab.garbage_cleaner();
                        }
                        catch (std::invalid_argument& ia)
                        {
                            text.setString(ia.what());
                            flag = 0;
                        }
                        if (flag)
                            text.setString("Deleted");
                    }
                    if (buttonshow.select(mouse))
                    {
                        text.setString(tab.print());
                    }
                    inputstr.select(mouse);
                    inputkey.select(mouse);
                }
            }

            if (event.type == sf::Event::TextEntered)
            {
                if (inputstr.select())
                    inputstr.reText(event.text.unicode);
                if (inputkey.select())
                    inputkey.reText(event.text.unicode);
            }
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                sf::Text end;
                window.clear();
                text.setString("Goodbye!");
                text.setPosition(430, 430);
                window.draw(text);
                window.display();
                window.close();
            }
        }
        window.clear();
        window.draw(label.displayText());
        window.draw(textkey);
        window.draw(textstr);
        window.draw(buttonadd.displayButton());
        window.draw(buttonadd.displayText());
        window.draw(buttonfind.displayButton());
        window.draw(buttonfind.displayText());
        window.draw(buttondelete.displayButton());
        window.draw(buttondelete.displayText());
        window.draw(buttonshow.displayButton());
        window.draw(buttonshow.displayText());
        window.draw(inputkey.displayButton());
        window.draw(inputkey.displayText());
        window.draw(inputstr.displayButton());
        window.draw(inputstr.displayText());
        window.draw(text);
        window.display();
    }
    return 0;
}
