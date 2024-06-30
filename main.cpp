#include <SFML/Graphics.hpp>
#include "map.h"
using namespace std;
using namespace sf;
//ф
double fall_speed = 1; // УБРАТЬ ПОТОМ!!!!!!!!!!!
class object{
private:
    double x_;
    double y_;
    double hp_;
    Image image_;
    struct image_size{
        double x;
        double y;
    } image_size_;
    Texture texture_;
    Sprite sprite_;
    bool synergy_with_map_rect(vector<vector<int>> rectangles, double speed, double time, vector<int>& direction) { // true - right, false - left(unblocked side)
        double x = x_ + speed * time * direction[0];
        double y = y_ + speed * time * direction[1] + time * fall_speed;
        bool falling = true;
        for(size_t i = 0; i < rectangles.size(); ++i) {
            double left = rectangles[i][0], right = rectangles[i][1];
            double lower = rectangles[i][2], upper = rectangles[i][3];
            if (!(left < x - image_size_.x / 2 && x + image_size_.x / 2 < right)) {
                direction = {0, direction[1]};
            }
            if (!(lower < y - image_size_.y / 2 && y + image_size_.y / 2 < upper)) {
                falling = false;
                direction = {direction[0], 0};
            }
        }
        return falling;
    }
public:
    object(double hp, double x, double y/*, double w, double h*/, string FILEPath){
        hp_ = hp;
        image_.loadFromFile(FILEPath);
        texture_.loadFromImage(image_);
        sprite_.setTexture(texture_);
        image_size_.x = image_.getSize().x;
        image_size_.y = image_.getSize().y;
        x_ = x + image_size_.x / 2;
        y_ = y + image_size_.y / 2;
        sprite_.setPosition(x, y);
        cout << FILEPath << ": " << image_.getSize().x << ' ' << image_.getSize().y << '\n';
        //Also we can change type of sprite(texture) based on type of img;
    }
    void deal_damage(double damage){
        hp_ -= damage;
    }
    vector<double> getRect(){
        return {x_ - image_size_.x / 2, x_ + image_size_.x / 2, y_ - image_size_.y / 2, y_ + image_size_.y / 2};
    }
    bool intersects(vector<double> rectangle){
        double left = rectangle[0], right = rectangle[1];
        double lower = rectangle[2], upper = rectangle[3];
        for(int i = 0; i < 2; ++i){
            for(int j = 0; j < 2; ++j){
                if(left <= x_ + (1 - 2 * i) * image_size_.x / 2 && x_ + (1 - 2 * i) * image_size_.x / 2 <= right){
                    if(lower <= y_ + (1 - 2 * j) * image_size_.y / 2 && y_ + (1 - 2 * j) * image_size_.y / 2 <= upper){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    void update(double speed, double time, vector<int> direction, const vector<vector<int>>& rectangles){ // direction[0] - 0/1/-1 - direction of opbject by Ox?. Same for direction[1];
        bool falling = synergy_with_map_rect(rectangles, speed, time, direction);
        double dx = speed * time * direction[0];
        double dy = speed * time * direction[1] + fall_speed * time * falling;
        x_ += dx;
        y_ += dy;
        sprite_.move(dx, dy);
    }
    void update(double speed, double time, vector<int> direction, const vector<vector<int>>& rectangles, View& view){ // overloading with pinned view
        bool falling = synergy_with_map_rect(rectangles, speed, time, direction);
        double dx = speed * time * direction[0];
        double dy = speed * time * direction[1] + fall_speed * time * falling;
        x_ += dx;
        y_ += dy;
        sprite_.move(dx, dy);
        view.move(dx, dy);
    }
    Sprite GetSprite(){
        return sprite_;
    }
    double get_x(){
        return x_;
    }
    double get_y(){
        return y_;
    }
    double get_hp(){
        return hp_;
    }
    image_size get_size(){
        return image_size_;
    };
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Catch the Hilter");
    sf::RenderWindow window_clone(sf::VideoMode(1920, 1080), "Catch the Hilter 2 player");


    Clock clock;
    double speed = 5;
    View view, view_clone;
    //map's sprite's rendering
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
    view.setSize(4000,4000);
    view_clone.setSize(4000, 4000);
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
    vector<int> rectangle1 = {0 + tile_w, map_w * tile_w - tile_w, 0 + tile_h, map_h * tile_h - tile_h};
    renderTexture.display();
    sf::Sprite mapSprite;
    mapSprite.setTexture(renderTexture.getTexture());

    object ilnur(999, tile_w, tile_h, "images/ilnur.jpg");
    object cat(1, 5000, 5000, "images/samir.jpg");
    object mouse(1, tile_w, tile_h, "images/mouse_2.png");
    view.setCenter(cat.get_x(), cat.get_y());
    view_clone.setCenter(mouse.get_x(), mouse.get_y());

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
        if(mouse.intersects(cat.getRect()) || cat.intersects(mouse.getRect())){
            cat.deal_damage(time / 1000);
            cout << cat.get_hp() << '\n';
            if(cat.get_hp() <= 0){
                window_clone.close();
                window.close();
            }
        }
//        cout << time << '\n';
        vector<int> cat_direction = {0, 0};
        if(Keyboard::isKeyPressed(Keyboard::W)){
            --cat_direction[1];
        }
        if(Keyboard::isKeyPressed(Keyboard::A)){
            --cat_direction[0];
        }
        if(Keyboard::isKeyPressed(Keyboard::S)){
            ++cat_direction[1];
        }
        if(Keyboard::isKeyPressed(Keyboard::D)){
            ++cat_direction[0];
        }
        cat.update(speed, time, cat_direction, {rectangle1}, view);
        vector<int> mouse_direction = {0, 0};
        if(Keyboard::isKeyPressed(Keyboard::Up)){
            --mouse_direction[1];
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            mouse.update(speed, time, {-1, 0}, {rectangle1}, view_clone);
            --mouse_direction[0];
        }
        if(Keyboard::isKeyPressed(Keyboard::Down)){
            ++mouse_direction[1];
        }
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            ++mouse_direction[0];
        }
        mouse.update(speed, time, mouse_direction, {rectangle1}, view_clone);

        //drawing
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