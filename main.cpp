#include <SFML/Graphics.hpp>
#include "iostream"
using namespace std;
using namespace sf;

class object{
private:
    double x_;
    double y_;
//    double w_;
//    double h_;
    Image image_;
    Texture texture_;
    Sprite sprite_;
public:
    object(double x, double y/*, double w, double h*/, string FILEPath){
        image_.loadFromFile(FILEPath);
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);
        sprite_.setPosition(x, y);
        x_ = x;
        y_ = y;
//        w_ = w;
//        h_ = h;
        //Also we can change type of sprite(texture) based on type of img;
    }
    void update(double speed, double time, vector<int> direction){ // direction[0] - 0/1/-1 - direction of opbject by Ox?. Same for direction[1];
        x_ += speed * time * direction[0];
        y_ += speed * time * direction[1];
        sprite_.setPosition(x_, y_);
    }
    Sprite GetSprite(){
        return sprite_;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Catch the Hilter");
    object ilnur(0, 0, "images/ilnur.jpg");
    Clock clock;
    double speed = 0.5;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        double time = clock.restart().asMicroseconds();
        time /= 1000;
        cout << time << '\n';
        vector<int> direction(2, 0);
        if(Keyboard::isKeyPressed(Keyboard::W)){
            ilnur.update(speed, time, {0, -1});
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
            ilnur.update(speed, time, {-1, 0});
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            ilnur.update(speed, time, {0, 1});
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            ilnur.update(speed, time, {1, 0});
        }
        window.clear();
        window.draw(ilnur.GetSprite());
        window.display();
    }

    return 0;
}