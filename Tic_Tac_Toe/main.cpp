#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

/*
1. Сделать чтобы кружок оставался после нажатия в клетке.
*/

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

    std::vector<sf::CircleShape> circle;

    sf::CircleShape newCircle;
    newCircle.setRadius(70);
    newCircle.setOrigin({ 70, 70 });
    newCircle.setOutlineColor(sf::Color::Red);
    newCircle.setOutlineThickness(5);

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
                if (mb->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f pos{ static_cast<float>(mb->position.x), static_cast<float>(mb->position.y) };

                    for (int i = 0; i < fields.size(); ++i)
                    {
                        if (fields[i].contains(pos) == true)
                        {
                            sf::Vector2f corV = fields[i].getCenter();
                            newCircle.setPosition(fields[i].getCenter());
                            circle.push_back(newCircle);
                            for (int i = 0; i < circle.size(); i++)
                            {
                                if (corV.x == circle[i].getPosition().x && corV.y == circle[i].getPosition().y)
                                {

                                }
                                std::cout << circle[i].getPosition().x << " " << circle[i].getPosition().y << std::endl;
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

        for (int i = 0; i < circle.size(); i++)
        {
            window.draw(circle[i]);
        }

        // Update the window
        window.display();
    }
}