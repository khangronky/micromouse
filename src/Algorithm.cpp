#include <ArduinoSTL.h>
#include <stack>
#include <queue>

#include "Algorithm.h"
#include "Controller.h"

#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8
unsigned short bfs_map[MAZE_HEIGHT][MAZE_WIDTH];
const unsigned short INF = MAZE_WIDTH * MAZE_HEIGHT + 1;
uint8_t maze[MAZE_HEIGHT][MAZE_WIDTH];
const char directions[] = {'w', 'n', 'e', 's'};
bool surrounds[3];

void setBit(uint8_t &byte, const int pos, const bool value)
{
  byte = (byte & ~(1 << pos)) | (value << pos);
}

int x, y;
pos::pos() {};
pos::pos(const int x, const int y) : x(x), y(y) {};
pos::pos(const pos &other) : x(other.x), y(other.y) {};
bool pos::operator==(const pos &other) const
{
  return (x == other.x) && (y == other.y);
}
void pos::operator+=(const pos &other)
{
  x += other.x;
  y += other.y;
}
pos pos::operator+(const pos &other) { return pos(x + other.x, y + other.y); }

pos startPos[] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
pos goalPos[] = {{MAZE_WIDTH / 2 - 1, MAZE_HEIGHT / 2 - 1},
                 {MAZE_WIDTH / 2 - 1, MAZE_HEIGHT / 2},
                 {MAZE_WIDTH / 2, MAZE_HEIGHT / 2 - 1},
                 {MAZE_WIDTH / 2, MAZE_HEIGHT / 2}};
pos drs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

pos currPos = startPos[0];
int facing = 1; // 0: left 1: up 2: right 3: down

bool isValid(const pos &p)
{
  return ((p.x >= 0) && (p.y >= 0) &&
          (p.x < MAZE_WIDTH) && (p.y < MAZE_HEIGHT));
}

bool isGoal(const pos &p)
{
  for (const pos &goal : goalPos)
    if (p == goal)
      return true;
  return false;
}

bool isFinish()
{
  for (const pos &goal : goalPos)
    if (currPos == goal)
      return true;
  return false;
}

void bfs()
{
  std::fill(&bfs_map[0][0], &bfs_map[0][0] + MAZE_WIDTH * MAZE_HEIGHT, INF);
  pos p_front, p_temp;
  uint8_t block;
  std::queue<pos> q;

  for (const pos &p : goalPos)
  {
    bfs_map[p.y][p.x] = 0;
    q.push(p);
  }

  while (!q.empty())
  {
    p_front = q.front();
    q.pop();
    // get surrounding of a block
    block = maze[p_front.y][p_front.x];
    for (int i = 0; i < 4; ++i)
    {
      if (!(block & (1 << i)))
      {
        p_temp = p_front + drs[i];
        if (!isValid(p_temp) || bfs_map[p_temp.y][p_temp.x] != INF ||
            isGoal(p_temp))
          continue;
        bfs_map[p_temp.y][p_temp.x] = bfs_map[p_front.y][p_front.x] + 1;
        q.push(p_temp);
      }
    }
  }
}

void st_bfs()
{
  std::fill(&bfs_map[0][0], &bfs_map[0][0] + MAZE_WIDTH * MAZE_HEIGHT, INF);
  pos p_front, p_temp;
  uint8_t block;
  std::stack<pos> q;

  for (const pos &p : goalPos)
  {
    bfs_map[p.y][p.x] = 0;
    q.push(p);
  }

  while (!q.empty())
  {
    p_front = q.top();
    q.pop();
    // get surrounding of a block
    block = maze[p_front.y][p_front.x];
    for (int i = 0; i < 4; ++i)
    {
      if (!(block & (1 << i)))
      {
        p_temp = p_front + drs[i];
        if (!isValid(p_temp) || bfs_map[p_temp.y][p_temp.x] != INF ||
            isGoal(p_temp))
          continue;
        bfs_map[p_temp.y][p_temp.x] = bfs_map[p_front.y][p_front.x] + 1;
        q.push(p_temp);
      }
    }
  }
}

void updateSurrounding()
{
  int offset;
  pos p_temp;
  
  surrounds[0] = Controller::action("wallLeft") == "true";
  surrounds[1] = Controller::action("wallFront") == "true";
  surrounds[2] = Controller::action("wallRight") == "true";
  for (int i = 0; i < 3; ++i)
  {
    offset = (facing + i + 3) % 4;
    setBit(maze[currPos.y][currPos.x], offset, surrounds[i]);
    setBit(maze[currPos.y][currPos.x], offset + 4, 1);
    p_temp = currPos + drs[offset];
    if (isValid(p_temp))
    {
      setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4, surrounds[i]);
      setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4 + 4, 1);
    }
  }
}

int getBestMove()
{
  pos p_temp;
  unsigned short min = INF;
  int bestDir = -1;
  for (int i = 0; i < 4; ++i)
  {
    p_temp = currPos + drs[i];
    if (!isValid(p_temp) || maze[currPos.y][currPos.x] & (1 << i))
      continue;
    if (bfs_map[p_temp.y][p_temp.x] < min)
    {
      min = bfs_map[p_temp.y][p_temp.x];
      bestDir = i;
    }
  }
  return bestDir;
}

void move(const int dir)
{
  while (facing != dir)
  {
    int leftTurns = (facing - dir + 4) % 4;
    int rightTurns = (dir - facing + 4) % 4;
    if (leftTurns < rightTurns)
    {
      Controller::action("turnLeft");
      facing = (facing + 3) % 4;
    }
    else
    {
      Controller::action("turnRight");
      facing = (facing + 1) % 4;
    }
  }
  Controller::action("moveForward");
  currPos += drs[dir];
}

// int main(int argc, char* argv[]) {
//   std::stack<pos> path;
//   int bestDir;
//   bool exploring = true;

//   memset(maze, 0, sizeof(uint8_t) * MAZE_WIDTH * MAZE_HEIGHT);
//   while (exploring) {
//     for (int i = 0; i < 2; ++i) {
//       updateSurrounding();
//       bfs();
//       while (!isFinish()) {
//         path.push(currPos);
//         bestDir = getBestMove();
//         while (bestDir == -1) {
//           return 0;
//         }
//         move(bestDir);
//         updateSurrounding();
//         bfs();
//       }
//       if (path.size() == bfs_map[startPos[0].y][startPos[0].x]) exploring = false;
//       while (!path.empty()) path.pop();
//       std::swap_ranges(startPos, startPos + 4, goalPos);
//     }
//   }

//   updateSurrounding();
//   bfs();
//   while (!isFinish()) {
//     bestDir = getBestMove();
//     move(bestDir);
//     updateSurrounding();
//     bfs();
//   }
//   return 0;
// }
