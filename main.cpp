#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    Image ilnur_img;
    ilnur_img.loadFromFile("../images/ilnur.jpg");
    Texture ilnur_txt;
    ilnur_txt.loadFromImage(ilnur_img);
    Sprite ilnur;
    ilnur.setTexture(ilnur_txt);
    double speed = 0.5;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(Keyboard::isKeyPressed(Keyboard::W)){
            ilnur.move(0, -speed);
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
            ilnur.move(-speed, 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            ilnur.move(0, speed);
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            ilnur.move(speed, 0);
        }


        window.clear();
        window.draw(ilnur);
        window.display();
    }

    return 0;
}