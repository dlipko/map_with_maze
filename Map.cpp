//
// Created by Дмитрий on 09.11.2017.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include "Map.h"
#include <ctime>
#include <stack>


void Map::generate(int roomsCount, int maxW, int maxH) {
    m_rooms.clear();
    srand( time(0) );
    // второй цикл предотвращает залипание, в случае если на карту уже не помещается ни одной комнаты
    for (int i = 0; i < roomsCount; ++i) for (int j = 0; j < 1000; ++j) {

            // ширина и высота комнаты в пределах [10,40]
            const int w = 1 + rand() % maxW, h = 1 + rand() % maxH;
            std::cout<<w<<" "<<h<<"\n";
            // избегаем "прилипания" комнаты к краю карты
            const Room room = {3 + rand() % (m_width - w - 6), 3 + rand() % (m_height - h - 6), w, h};

            // найдем первую комнату, из уже существующих, которая пересекается с новой
            auto intersect = std::find_if(std::begin(m_rooms), std::end(m_rooms), [&room](const Room &r){
                return room.intersect(r);
            });

            // если новая комната не имеет пересечений - добавляем ее
            if (intersect == std::end(m_rooms)) {
                m_rooms.push_back(room);
                break;
            }
        }
    // зануляем карту индексом 0
    m_data.assign(m_width * m_height, 0);
    // пространство комнат заполняем индексом 1
    for (const Room &room : m_rooms) {
        for (int x = 0; x < room.w; ++x) for (int y = 0; y < room.h; ++y) {
                m_data[(room.x + x) + (room.y + y) * m_width] = 1;
            }
    }
}

void Map::print_map(){
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            std::cout << m_data[y*m_width + x]<<" ";
        }
        std::cout<<"\n";
    }
}


void Map::add_maze(){
    srand(time(NULL));

    int startX = 1;
    int startY = 1;

    m_data[startX * m_width + startY] = 1;
    class Coordinates{
    public:
        int x = 0;
        int y = 0;
        void set(int a, int b){
            x = a;
            y = b;
        }
    };
    std::stack<Coordinates> path;
    Coordinates coord;
    coord.set(startX, startY);
    path.push(coord);
    m_data[startX * m_width + startY] = 1;



    while (!path.empty())
    {
        Coordinates coord = path.top();

        //смотрим варианты, в какую сторону можно пойти
        std::vector<Coordinates> nextStep;
        Coordinates new_coord;
        if (coord.x - 2 > 0 && !m_data[(coord.x - 2) * m_width + coord.y]) {
            new_coord.set(coord.x - 2, coord.y);
            nextStep.push_back(new_coord);
        }
        if (coord.x < m_width - 2 && !m_data[(coord.x + 2) * m_width + coord.y]){
            new_coord.set(coord.x + 2, coord.y);
            nextStep.push_back(new_coord);
        }

        if (coord.y - 2 > 0 && !m_data[coord.x * m_width + coord.y - 2]) {
            new_coord.set(coord.x, coord.y - 2);
            nextStep.push_back(new_coord);
        }
        if (coord.y < m_height - 2 && !m_data[coord.x * m_width + coord.y + 2]) {
            new_coord.set(coord.x, coord.y + 2);
            nextStep.push_back(new_coord);
        }

        if (!nextStep.empty())
        {
            //выбираем сторону из возможных вариантов
            Coordinates next = nextStep[rand() % nextStep.size()];


            //Открываем сторону, в которую пошли на ячейках
            if (next.x != coord.x)
            {
                if (coord.x - next.x > 0)
                    m_data[(next.x + 1) * m_width + next.y] = 1;
                else
                    m_data[(next.x - 1) * m_width + next.y] = 1;
            }

            if (next.y != coord.y)
            {
                if (coord.y - next.y > 0)
                    m_data[next.x * m_width + next.y + 1] = 1;

                else
                    m_data[next.x * m_width + next.y - 1] = 1;
            }

            m_data[next.x * m_width + next.y] = 1;
            path.push(next);

        }

        else
        {
            //если пойти никуда нельзя, возвращаемся к предыдущему узлу
            path.pop();
        }
    }
}
