// #include "Algorithm.h"
// #include <queue>
// #include <cstring>
// #include <Arduino.h>
// #include "Controller.h" // Include Controller header

// uint8_t maze[MAZE_HEIGHT][MAZE_WIDTH];
// unsigned short bfs_map[MAZE_HEIGHT][MAZE_WIDTH];
// const unsigned short INF = MAZE_WIDTH * MAZE_HEIGHT + 1;
// const char directions[] = {'w', 'n', 'e', 's'};
// bool surrounds[3];

// pos currPos;
// pos startPos(0, 0); // Corrected to be a single pos object
// pos goalPos[] = {pos(9, 2)};
// const pos drs[] = {pos(-1, 0), pos(0, 1), pos(1, 0), pos(0, -1)};
// int facing = 1; // 0: left 1: up 2: right 3: down

// pos::pos() : x(0), y(0) {}
// pos::pos(const int x, const int y) : x(x), y(y) {}
// pos::pos(const pos& other) : x(other.x), y(other.y) {}
// bool pos::operator==(const pos& other) const {
//     return (x == other.x) && (y == other.y);
// }
// void pos::operator+=(const pos& other) {
//     x += other.x;
//     y += other.y;
// }
// pos pos::operator+(const pos& other) {
//     return pos(x + other.x, y + other.y);
// }

// bool isValid(const pos &p) {
//     return ((p.x >= 0) && (p.y >= 0) && (p.x < MAZE_WIDTH) &&
//             (p.y < MAZE_HEIGHT));
// }

// bool isGoal(const pos &p) {
//     for (const pos &goal : goalPos)
//         if (p == goal)
//             return true;
//     return false;
// }

// bool isFinish() {
//     for (const pos &goal : goalPos)
//         if (currPos == goal)
//             return true;
//     return false;
// }

// void initializeMazeData() { // Renamed from init to initializeMazeData
//     memset(maze, 0, sizeof(uint8_t) * MAZE_WIDTH * MAZE_HEIGHT);
//     return;
// }

// void bfs() {
//     std::fill(&bfs_map[0][0], &bfs_map[0][0] + MAZE_WIDTH * MAZE_HEIGHT, INF);
//     pos p_front, p_temp;
//     uint8_t block;
//     std::queue<pos> q;

//     for (const pos &p : goalPos) {
//         bfs_map[p.y][p.x] = 0;
//         q.push(p);
//     }

//     while (!q.empty()) {
//         p_front = q.front();
//         q.pop();
//         block = maze[p_front.y][p_front.x];
//         for (int i = 0; i < 4; ++i)
//             if (!(block & (1 << i))) {
//                 p_temp = p_front + drs[i];
//                 if (!isValid(p_temp) || bfs_map[p_temp.y][p_temp.x] != INF || isGoal(p_temp))
//                     continue;
//                 bfs_map[p_temp.y][p_temp.x] = bfs_map[p_front.y][p_front.x] + 1;
//                 q.push(p_temp);
//             }
//     }

//     // Debugging output for BFS map
//     Serial.println("BFS Map:");
//     for (int y = 0; y < MAZE_HEIGHT; y++) {
//         for (int x = 0; x < MAZE_WIDTH; x++) {
//             Serial.print(bfs_map[y][x]);
//             Serial.print(" ");
//         }
//         Serial.println();
//     }
// }

// void setBit(uint8_t &byte, const int pos, const bool value) {
//     byte = (byte & ~(1 << pos)) | (value << pos);
// }

// void updateSurrounding() {
//     int offset;
//     pos p_temp;
//     surrounds[0] = Controller::wallLeft();
//     surrounds[1] = Controller::wallFront();
//     surrounds[2] = Controller::wallRight();
//     for (int i = 0; i < 3; ++i) {
//         offset = (facing + i + 3) % 4;
//         setBit(maze[currPos.y][currPos.x], offset, surrounds[i]);
//         setBit(maze[currPos.y][currPos.x], offset + 4, 1);
//         p_temp = currPos + drs[offset];
//         if (isValid(p_temp)) {
//             setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4, surrounds[i]);
//             setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4 + 4, 1);
//         }
//     }

//     // Debugging output for maze data
//     Serial.println("Maze Data:");
//     for (int y = 0; y < MAZE_HEIGHT; y++) {
//         for (int x = 0; x < MAZE_WIDTH; x++) {
//             Serial.print(maze[y][x], BIN);
//             Serial.print(" ");
//         }
//         Serial.println();
//     }
// }

// int getBestMove() {
//     pos p_temp;
//     unsigned short min = INF;
//     int bestDir = -1;
//     for (int i = 0; i < 4; ++i) {
//         p_temp = currPos + drs[i];
//         if (!isValid(p_temp) || maze[currPos.y][currPos.x] & (1 << i)) continue;
//         if (bfs_map[p_temp.y][p_temp.x] < min) {
//             min = bfs_map[p_temp.y][p_temp.x];
//             bestDir = i;
//         }
//     }
//     return bestDir;
// }

// void move(int direction) {
//     switch (direction) {
//         case 0:
//             currPos += pos(-1, 0); // Move West
//             Serial.println("Move West");
//             break;
//         case 1:
//             currPos += pos(0, -1); // Move North
//             Serial.println("Move North");
//             break;
//         case 2:
//             currPos += pos(1, 0); // Move East
//             Serial.println("Move East");
//             break;
//         case 3:
//             currPos += pos(0, 1); // Move South
//             Serial.println("Move South");
//             break;
//     }
// }

// void reset() {
//     Controller::ackReset();
//     currPos = startPos;
//     facing = 1;
// }