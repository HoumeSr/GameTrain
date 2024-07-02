#include "iostream"
#include "vector"
#include "string"

using namespace std;
/*
MAP STANDART:
Q - Левый верхний угол
q - Правый верхний угол
G - Левый нижний угол
g - Правый нижний угол
W - Верхняя стена
w - Нижняя стена
H - Левая стена
h - Правая стена
other - Остальное
 */
std::vector<std::string> createMap(int width, int height) {
    std::vector<std::string> map(height, std::string(width, ' '));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if(i == 0 && j == 0) map[i][j] = 'Q';
            else if(i == 0 && j == width - 1) map[i][j] = 'q';
            else if(i == height - 1 && j == 0) map[i][j] = 'G';
            else if(i == height - 1 && j == width - 1) map[i][j] = 'g';
            else if (i == 0) {
                map[i][j] = 'W';
            }
            else if (j == 0){
                map[i][j] = 'H';
            }
            else if(j == width - 1){
                map[i][j] = 'h';
            }
            else if(i == height - 1){
                map[i][j] = 'w';
            }
            else {
                int randNum = rand() % 2452;
                map[i][j] = (randNum != 0) ? ' ' : 'j';
            }
        }
    }
    return map;
}