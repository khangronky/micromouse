#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <ArduinoSTL.h>

#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8
extern unsigned short bfs_map[MAZE_HEIGHT][MAZE_WIDTH];
extern const unsigned short INF;
extern uint8_t maze[MAZE_HEIGHT][MAZE_WIDTH];
extern const char directions[];
extern bool surrounds[3];

void setBit(uint8_t& byte, const int pos, const bool value);

struct pos {
    int x, y;
    pos();
    pos(const int x, const int y);
    pos(const pos& other);
    bool operator==(const pos& other) const;
    void operator+=(const pos& other);
    pos operator+(const pos& other);
};

extern pos startPos[4];
extern pos goalPos[4];
extern pos drs[4];

extern pos currPos;
extern int facing;

bool isValid(const pos& p);
bool isGoal(const pos& p);
bool isFinish();
void bfs();
void st_bfs();
void updateSurrounding();
int getBestMove();
void move(const int dir);

#endif