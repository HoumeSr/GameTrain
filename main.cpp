#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Catch the Hilter");
    Image ilnur_img;
    ilnur_img.loadFromFile("images/adolf.jpg");
    Texture ilnur_txt, stalin_txt;
    ilnur_txt.loadFromImage(ilnur_img);
    stalin_txt.loadFromFile("images/stalin.jpg");
    Sprite ilnur, stalin;
    stalin.setTexture(stalin_txt);
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

        if(Keyboard::isKeyPressed(Keyboard::Up)){
            stalin.move(0, -speed);
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            stalin.move(-speed, 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::Down)){
            stalin.move(0, speed);
        }
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            stalin.move(speed, 0);
        }


        window.clear();
        window.draw(ilnur);
        window.draw(stalin);
        window.display();
    }

    return 0;
}