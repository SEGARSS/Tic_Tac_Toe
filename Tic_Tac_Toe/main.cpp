#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;


//------------------------------------------------------------------------------------
int main()
{
    // Настройеи игрового окна
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
        Base(sf::Vector2f pos)
        {
            //Позицию используем и в крестиках и ноликах, поэтому управляет этим базовый класс(структура)
            position = pos;
        }

        sf::Vector2f getPosition()
        {
            return position;
        }

        //Делаем виртуальный метод, и вконце прописываем 0 обезательно, иначе не будет рабоать.
        virtual void draw(sf::RenderWindow& window) = 0;        

        sf::Vector2f position;        
    };
    //------------------------------------------------------------------------------------
    struct Cirle : Base
    {
        Cirle(sf::Vector2f pos)
        : Base(pos)
        {
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

        sf::CircleShape newCircle;
    };
    //------------------------------------------------------------------------------------
    struct Cross : Base
    {
        Cross(sf::Vector2f pos)
        : Base(pos)
        {
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

        sf::RectangleShape newRectangle;
        sf::RectangleShape newRectangle0;
    };
    //------------------------------------------------------------------------------------

    /*
    Почему figure видит и крестики и нолики ? (Мы объявили vector<Base*> figure), а у Base есть доступ
    и к Cirle (нолики), Cross (крестик), из за наследования этих структур. 
    */
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

    // Запустите игровой цикл
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Закрыть окно: выход
            if (event->is<sf::Event::Closed>())
                window.close();

            //Определяем что управление в игре будет мышкой.
            if (const auto* mb = event->getIf<sf::Event::MouseButtonPressed>())
            {
                //Определяем позиция куда нажали мышкой.
                sf::Vector2f pos{ static_cast<float>(mb->position.x), static_cast<float>(mb->position.y) };

                // Проходимся по всем клетка нашего игрового поля.
                for (int i = 0; i < fields.size(); ++i) 
                {
                    // contains проверят, нажалась ли мышка в том участке (её позиция)
                    if (fields[i].contains(pos) == true)
                    {
                        //Получить цент квадратика.
                        sf::Vector2f corV = fields[i].getCenter();

                        //Заводим булевую переменную для определения, есть в квадрате уже фигура.
                        bool find = false;

                        //Проходимся по вектору всех фигур (крестики, нолики)
                        for (int i = 0; i < figure.size(); i++)
                        {
                            //Сравниваем, центр квадрата, есть ли там уже какаето фигура.
                            if (corV == figure[i]->getPosition())
                            {
                                //Если есть, права(да)
                                find = true;
                            }
                            std::cout << figure.size() << std::endl;
                            std::cout << figure[i]->getPosition().x << " " << figure[i]->getPosition().y << std::endl;
                        }

                        //Если нет в фигуры в квадрате, то в ставим фигуру (в зависимости от нажатой кнопки)
                        if (find == false)
                        {
                            if (mb->button == sf::Mouse::Button::Right)
                            {
                                figure.push_back(new Cross(corV)); //Правая кнопка, ставим крестик
                            }
                            else if (mb->button == sf::Mouse::Button::Left)
                            {
                                figure.push_back(new Cirle(corV));//Левая кнопка, ставим нолик
                            }
                        }
                    }
                }
            }
        }

        // Очистка окна
        window.clear();

        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(rectangle3);
        window.draw(rectangle4);

        for (int i = 0; i < figure.size(); i++)
        {
            //Выводим на экран наши крестики и нолики.
            figure[i]->draw(window);
        }

        // Обновление окна
        window.display();
    }
}