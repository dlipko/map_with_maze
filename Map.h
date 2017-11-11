//
// Created by Дмитрий on 09.11.2017.
//

#ifndef GAME_FIELD_MAP_H
#define GAME_FIELD_MAP_H

#include <vector>

class Map {
public:
    struct Room {
        int x, y, w, h;
        bool intersect(const Room &r) const {
            int distance = 5;
            return !(r.x >= (x + w + distance) || x >= (r.x + r.w + distance) || r.y >= (y + h + distance) || y >= (r.y + r.h + distance));
        }
    };

    Map(int width, int height): m_width(width), m_height(height) {
        m_data.resize(width * height, 0);
    }

    void generate(int roomsCount,  int maxW, int maxH);
    void print_map();
    void add_maze();

private:
    int m_width, m_height;     // размеры карты
    std::vector<int> m_data;   // финальные данные карты
    std::vector<Room> m_rooms; // комнаты
};


#endif //GAME_FIELD_MAP_H
