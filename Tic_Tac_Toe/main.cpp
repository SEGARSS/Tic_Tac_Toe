#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;


//------------------------------------------------------------------------------------
int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 600, 600 }), "SFML window");

    sf::RectangleShape rectangle1;
    rectangle1.setSize(sf::Vector2f(3, 600));
    rectangle1.setOutlineColor(sf::Color::Red);
    rectangle1.setPosition({ 200, 0 });

    sf::RectangleShape rectangle2;
    rectangle2.setSize(sf::Vector2f(3, 600));
    rectangle2.setOutlineColor(sf::Color::Red);
    rectangle2.setPosition({ 400, 0 });

    sf::RectangleShape rectangle3;
    rectangle3.setSize(sf::Vector2f(600, 3));
    rectangle3.setOutlineColor(sf::Color::Red);
    rectangle3.setPosition({ 0, 200 });

    sf::RectangleShape rectangle4;
    rectangle4.setSize(sf::Vector2f(600, 3));
    rectangle4.setOutlineColor(sf::Color::Red);
    rectangle4.setPosition({ 0, 400 });

    //------------------------------------------------------------------------------------
    struct Base
    {
        Base()
        {

        }

        sf::Vector2f getPosition()
        {
            return position;
        }

        virtual void draw(sf::RenderWindow& window) = 0;        

        sf::Vector2f position;

        sf::RectangleShape newRectangle;
        sf::RectangleShape newRectangle0;
        sf::CircleShape newCircle;
    };
    //------------------------------------------------------------------------------------
    struct Cirle : Base
    {
        Cirle(sf::Vector2f pos)
        {
            position = pos;
            newCircle.setRadius(70);
            newCircle.setOrigin({ 70, 70 });
            newCircle.setOutlineColor(sf::Color::Red);
            newCircle.setOutlineThickness(5);
            newCircle.setPosition({ pos.x, pos.y });
        }

        void draw(sf::RenderWindow& window) override
        {
            window.draw(newCircle);
        }
    };
    //------------------------------------------------------------------------------------
    struct Cross : Base
    {
        Cross(sf::Vector2f pos)
        {
            position = pos;
            newRectangle.setSize(sf::Vector2f(3, 200));
            newRectangle.setOutlineColor(sf::Color::Red);
            newRectangle.setOutlineThickness(5);
            newRectangle.setRotation(sf::degrees(45.f));
            newRectangle.setPosition({ pos.x + 70 , pos.y - 70 });

            newRectangle0.setSize(sf::Vector2f(3, 200));
            newRectangle0.setOutlineColor(sf::Color::Red);
            newRectangle0.setOutlineThickness(5);
            newRectangle0.setRotation(sf::degrees(-45.f));
            newRectangle0.setPosition({ pos.x - 70, pos.y - 70 });
        }

        void draw(sf::RenderWindow& window) override
        {
            window.draw(newRectangle);
            window.draw(newRectangle0);
        }
    };
    //------------------------------------------------------------------------------------
    std::vector<Base*> figure;

    std::vector<sf::FloatRect> fields;
    fields.push_back(sf::FloatRect({ 0, 0 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 200, 0 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 400, 0 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 0, 200 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 200, 200 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 400, 200 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 0, 400 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 200, 400 }, { 200, 200 }));
    fields.push_back(sf::FloatRect({ 400, 400 }, { 200, 200 }));

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2f pos{ static_cast<float>(mb->position.x), static_cast<float>(mb->position.y) };

                for (int i = 0; i < fields.size(); ++i)
                {
                    if (fields[i].contains(pos) == true)
                    {
                        sf::Vector2f corV = fields[i].getCenter();

                        bool find = false;

                        for (int i = 0; i < figure.size(); i++)
                        {
                            if (corV == figure[i]->getPosition())
                            {
                                find = true;
                            }
                            std::cout << figure.size() << std::endl;
                            std::cout << figure[i]->getPosition().x << " " << figure[i]->getPosition().y << std::endl;
                        }

                        if (find == false)
                        {
                            if (mb->button == sf::Mouse::Button::Right)
                            {
                                figure.push_back(new Cross(corV));
                            }
                            else if (mb->button == sf::Mouse::Button::Left)
                            {
                                figure.push_back(new Cirle(corV));
                            }
                        }
                    }
                }
            }
        }

        // Clear screen
        window.clear();

        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(rectangle4);

        for (int i = 0; i < figure.size(); i++)
        {
            figure[i]->draw(window);
        }

        // Update the window
        window.display();
    }
}