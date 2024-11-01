#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <Arduino.h> // Correct include for Arduino functions and types

#define MAZE_WIDTH 3
#define MAZE_HEIGHT 10

class pos {
public:
    int x, y;
    pos();
    pos(const int x, const int y);
    pos(const pos& other);
    bool operator==(const pos& other) const;
    void operator+=(const pos& other);
    pos operator+(const pos& other);
};

extern pos currPos;
extern pos startPos; // Corrected to be a single pos object
extern pos goalPos[]; // Declared as an array
extern uint8_t maze[MAZE_HEIGHT][MAZE_WIDTH]; // Declare maze as extern
extern unsigned short bfs_map[MAZE_HEIGHT][MAZE_WIDTH]; // Declare bfs_map as extern

void updateSurrounding();
void bfs();
bool isFinish();
int getBestMove();
void move(int direction);

#endif // ALGORITHM_H