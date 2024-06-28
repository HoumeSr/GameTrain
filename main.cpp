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
    object cat(0, 0, "images/cat_s.png");
    object mouse(0, 0, "images/mouse_s.png");
    Clock clock;
    double speed = 0.5;
    View view, view_clone;
    int map_w = 200, map_h = 200,  tile_w = 64, tile_h = 64;
    vector<string> map = createMap(map_w, map_h);

    sf::RenderTexture renderTexture;
    renderTexture.create(map_w * tile_w, map_h * tile_w);
    Texture map_wall, map_oth;
    map_wall.loadFromFile("images/Wall.png");
    map_oth.loadFromFile("images/floor_and_obj.png");
    sf::Sprite tile_wall, tile_oth;
    tile_wall.setTexture(map_wall);
    tile_oth.setTexture(map_oth);
    view.setSize(400,400);
    view.setCenter(0, 0);
    view_clone.setSize(400, 400);
    view_clone.setCenter(0, 0);
    for (int i = 0; i < map_h; i++) {
        for (int j = 0; j < map_w; j++) {
            if(map[i][j] == ' '){
                tile_oth.setTextureRect(IntRect(0, 0, 64, 64));
                tile_oth.setPosition(j * tile_w, i * tile_h);
                renderTexture.draw(tile_oth);
            }
            else if(map[i][j] == 'j'){
                tile_oth.setTextureRect(IntRect(64, 0, 64, 64));
                tile_oth.setPosition(j * tile_w, i * tile_h);
                renderTexture.draw(tile_oth);
            }
            else{
                tile_wall.setTextureRect(IntRect(0, 0, 64, 64));
                tile_wall.setPosition(j * tile_w, i * tile_h);
                renderTexture.draw(tile_wall);
            }
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