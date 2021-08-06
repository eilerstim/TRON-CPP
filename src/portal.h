#ifndef PORTAL_H
#define PORTAL_H
#include <random>
#include <vector>
#include "SDL.h"

class Portal {
    public:
        Portal(int grid_width, int grid_height) : 
            p_grid_width(grid_width), 
            p_grid_height(grid_height),
            random_w(0.0, static_cast<float>(grid_width - 1)),
            random_h(0.0, static_cast<float>(grid_height - 1))  {
                pos_x = p_grid_width / 2;
                pos_y = p_grid_height / 2;

                SDL_Point p1 {static_cast<int>(pos_x -1), static_cast<int>(pos_y + 1)};
                border.push_back(p1);
                SDL_Point p2{static_cast<int>(pos_x), static_cast<int>(pos_y + 1)};
                border.push_back(p2);
                SDL_Point p3{static_cast<int>(pos_x + 1), static_cast<int>(pos_y + 1)};
                border.push_back(p3);
                SDL_Point p4{static_cast<int>(pos_x + 1), static_cast<int>(pos_y)};
                border.push_back(p4);
                SDL_Point p5{static_cast<int>(pos_x + 1), static_cast<int>(pos_y -1)};
                border.push_back(p5);
                SDL_Point p6 {static_cast<int>(pos_x), static_cast<int>(pos_y -1)};
                border.push_back(p6);
                SDL_Point p7 {static_cast<int>(pos_x - 1), static_cast<int>(pos_y - 1)};
                border.push_back(p7);
                SDL_Point p8 {static_cast<int>(pos_x - 1), static_cast<int>(pos_y)};
                border.push_back(p8);
            }


        float pos_x;
        float pos_y;
        // Contains all points around the portal to draw a white outline around it
        std::vector<SDL_Point> border;

        //Random number generating engine
        std::random_device dev {};
        std::mt19937 engine{dev()};
        std::uniform_real_distribution<float> random_w;
        std::uniform_real_distribution<float> random_h;
    private:
        int p_grid_width;
        int p_grid_height;
};
#endif