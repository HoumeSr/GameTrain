#include <SFML/Graphics.hpp>
#include "map.h"
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
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Catch the Hilter");
    sf::RenderWindow window_clone(sf::VideoMode(1000, 1000), "Catch the Hilter 2 player");
    object ilnur(0, 0, "images/ilnur.jpg");
    object cat(5, 5, "images/cat_s.png");
    object mouse(5, 5, "images/mouse_s.png");
    Clock clock;
    double speed = 0.5;
    View view, view_clone;
    vector<string> map = createMap(200, 4200);

    sf::RenderTexture renderTexture;
    renderTexture.create(200 * 5, 200 * 5);
    Texture map_t;
    map_t.loadFromFile("images/map1.jpg");
    sf::Sprite tile;
    tile.setTexture(map_t);

    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < 200; j++) {
            switch (map[i][j]) {
                case ' ':
                    tile.setTextureRect(IntRect(10, 0, 5, 5));
                    break;
                case 'W':
                    tile.setTextureRect(IntRect(5, 0, 5, 5));
                    break;
                case 'w':
                    tile.setTextureRect(IntRect(5, 5, 5, -5));
                    break;
                case 'H':
                    tile.setTextureRect(IntRect(5, 0, 5, 5));
                    tile.rotate(-90);
                    break;
                case 'h':
                    tile.setTextureRect(IntRect(5, 0, 5, 5));
                    tile.rotate(90);
                    break;
                case 'j':
                    tile.setTextureRect(IntRect(15, 0, 5, 5));
                    break;
                case 'Q':
                    tile.setTextureRect(IntRect(0, 0, 5, 5));
                    break;
                case 'q':
                    tile.setTextureRect(IntRect(0, 0, 5, 5));
                    tile.rotate(90);
                    break;
                case 'G':
                    tile.setTextureRect(IntRect(0, 0, 5, 5));
                    tile.rotate(-90);
                    break;
                case 'g':
                    tile.setTextureRect(IntRect(0, 0, 5, 5));
                    tile.rotate(180);
                    break;
            }
            tile.setPosition(j * 5, i * 5);
            renderTexture.draw(tile);
        }
    }

    renderTexture.display();

    sf::Sprite mapSprite;
    mapSprite.setTexture(renderTexture.getTexture());

    while (window.isOpen() || window_clone.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Event event1;
        while (window_clone.pollEvent(event1))
        {
            if (event1.type == sf::Event::Closed)
                window_clone.close();
        }
        double time = clock.restart().asMicroseconds();
        time /= 1000;
        cout << time << '\n';
        if(Keyboard::isKeyPressed(Keyboard::W)){
            cat.update(speed, time, {0, -1});
            view.move(0, speed * time * -1);
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
            cat.update(speed, time, {-1, 0});
            view.move(speed * time * -1, 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            cat.update(speed, time, {0, 1});
            view.move(0, speed * time * 1);
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            cat.update(speed, time, {1, 0});
            view.move(speed * time * 1, 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::Up)){
            mouse.update(speed, time, {0, -1});
            view_clone.move(0, speed * time * -1);
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            mouse.update(speed, time, {-1, 0});
            view_clone.move(speed * time * -1, 0);
        }
        if(Keyboard::isKeyPressed(Keyboard::Down)){
            mouse.update(speed, time, {0, 1});
            view_clone.move(0, speed * time * 1);
        }
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            mouse.update(speed, time, {1, 0});
            view_clone.move(speed * time * 1, 0);
        }
        window.setView(view);
        window.clear();
        window.draw(mapSprite);
        window.draw(cat.GetSprite());
        window.draw(mouse.GetSprite());
        window.display();

        window_clone.setView(view_clone);
        window_clone.clear();
        window_clone.draw(mapSprite);
        window_clone.draw(cat.GetSprite());
        window_clone.draw(mouse.GetSprite());
        window_clone.display();
    }

    return 0;
}