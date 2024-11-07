#include <bits/stdc++.h>
#include "API.h"

#define MAZE_WIDTH 8
#define MAZE_HEIGHT 8
unsigned short bfs_map[MAZE_HEIGHT][MAZE_WIDTH];
const unsigned short INF = MAZE_WIDTH * MAZE_HEIGHT + 1;
std::uint8_t maze[MAZE_HEIGHT][MAZE_WIDTH];
const char directions[] = {'w', 'n', 'e', 's'};
bool surrounds[3];

void setBit(std::uint8_t& byte, const int pos, const bool value) {
  byte = (byte & ~(1 << pos)) | (value << pos);
}

void log(const std::string& text) { std::cerr << text << std::endl; }

void debugBFS() {
  for (int y = 0; y < MAZE_HEIGHT; ++y) {
    for (int x = 0; x < MAZE_WIDTH; ++x)
      API::setText(
          x, y, (bfs_map[y][x] == INF) ? "INF" : std::to_string(bfs_map[y][x]));
  }
}

void logMap() {
  for (int y = MAZE_HEIGHT - 1; y >= 0; --y) {
    for (int x = 0; x < MAZE_WIDTH; ++x) {
      std::bitset<8> bits(maze[y][x]);
      std::cerr << bits << " ";
    }
    std::cerr << std::endl;
  }
}

void logBFS() {
  for (int y = MAZE_HEIGHT - 1; y >= 0; --y) {
    for (int x = 0; x < MAZE_WIDTH; ++x) {
      std::cerr << bfs_map[y][x] << " ";
    }
    std::cerr << std::endl;
  }
}

struct pos {
  int x, y;
  pos() {};
  pos(const int x, const int y) : x(x), y(y) {};
  pos(const pos& other) : x(other.x), y(other.y) {};
  bool operator==(const pos& other) const {
    return (x == other.x) && (y == other.y);
  }
  void operator+=(const pos& other) {
    x += other.x;
    y += other.y;
  }
  pos operator+(const pos& other) { return pos(x + other.x, y + other.y); }
};

pos startPos[] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
pos goalPos[] = {{MAZE_WIDTH / 2 - 1, MAZE_HEIGHT / 2 - 1},
                 {MAZE_WIDTH / 2 - 1, MAZE_HEIGHT / 2},
                 {MAZE_WIDTH / 2, MAZE_HEIGHT / 2 - 1},
                 {MAZE_WIDTH / 2, MAZE_HEIGHT / 2}};
pos drs[] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

pos currPos = startPos[0];
int facing = 1;  // 0: left 1: up 2: right 3: down

bool isValid(const pos& p) {
  return ((p.x >= 0) && (p.y >= 0) &&
          (p.x < MAZE_WIDTH) && (p.y < MAZE_HEIGHT));
}

bool isGoal(const pos& p) {
  for (const pos& goal : goalPos)
    if (p == goal) return true;
  return false;
}

bool isFinish() {
  for (const pos& goal : goalPos)
    if (currPos == goal) return true;
  return false;
}

void bfs() {
  std::fill(&bfs_map[0][0], &bfs_map[0][0] + MAZE_WIDTH * MAZE_HEIGHT, INF);
  pos p_front, p_temp;
  std::uint8_t block;
  std::queue<pos> q;

  for (const pos& p : goalPos) {
    bfs_map[p.y][p.x] = 0;
    q.push(p);
  }

  while (!q.empty()) {
    p_front = q.front();
    q.pop();
    // get surrounding of a block
    block = maze[p_front.y][p_front.x];
    for (int i = 0; i < 4; ++i) {
      if (!(block & (1 << i))) {
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

void st_bfs() {
  std::fill(&bfs_map[0][0], &bfs_map[0][0] + MAZE_WIDTH * MAZE_HEIGHT, INF);
  pos p_front, p_temp;
  std::uint8_t block;
  std::stack<pos> q;

  for (const pos& p : goalPos) {
    bfs_map[p.y][p.x] = 0;
    q.push(p);
  }

  while (!q.empty()) {
    p_front = q.top();
    q.pop();
    // get surrounding of a block
    block = maze[p_front.y][p_front.x];
    for (int i = 0; i < 4; ++i) {
      if (!(block & (1 << i))) {
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

void debugUpdateWalls() {
  if (surrounds[0])
    API::setWall(currPos.x, currPos.y, directions[(facing + 3) % 4]);
  if (surrounds[1]) API::setWall(currPos.x, currPos.y, directions[facing]);
  if (surrounds[2])
    API::setWall(currPos.x, currPos.y, directions[(facing + 1) % 4]);
}

void updateSurrounding() {
  int offset;
  pos p_temp;
  surrounds[0] = API::wallLeft();
  surrounds[1] = API::wallFront();
  surrounds[2] = API::wallRight();
  debugUpdateWalls();
  for (int i = 0; i < 3; ++i) {
    offset = (facing + i + 3) % 4;
    setBit(maze[currPos.y][currPos.x], offset, surrounds[i]);
    setBit(maze[currPos.y][currPos.x], offset + 4, 1);
    p_temp = currPos + drs[offset];
    if (isValid(p_temp)) {
      setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4, surrounds[i]);
      setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4 + 4, 1);
    }
  }
}

int getBestMove() {
  pos p_temp;
  unsigned short min = INF;
  int bestDir = -1;
  for (int i = 0; i < 4; ++i) {
    p_temp = currPos + drs[i];
    if (!isValid(p_temp) || maze[currPos.y][currPos.x] & (1 << i)) continue;
    if (bfs_map[p_temp.y][p_temp.x] < min) {
      min = bfs_map[p_temp.y][p_temp.x];
      bestDir = i;
    }
  }
  return bestDir;
}

void move(const int dir) {
  while (facing != dir) {
    int leftTurns = (facing - dir + 4) % 4;
    int rightTurns = (dir - facing + 4) % 4;
    if (leftTurns < rightTurns) {
      API::turnLeft();
      facing = (facing + 3) % 4;
    }
    else {
      API::turnRight();
      facing = (facing + 1) % 4;
    }
  }
  API::moveForward();
  currPos += drs[dir];
}

int main(int argc, char* argv[]) {
  std::stack<pos> path;
  int bestDir;
  bool exploring = true;

  memset(maze, 0, sizeof(std::uint8_t) * MAZE_WIDTH * MAZE_HEIGHT);
  while (exploring) {
    for (int i = 0; i < 2; ++i) {
      API::setColor(currPos.x, currPos.y, 'G');
      updateSurrounding();
      bfs();
      debugBFS();
      while (!isFinish()) {
        path.push(currPos);
        bestDir = getBestMove();
        while (bestDir == -1) {
          std::cerr << "No path found!" << std::endl;
          return 0;
        }
        move(bestDir);
        API::setColor(currPos.x, currPos.y, 'G');
        updateSurrounding();
        bfs();
        debugBFS();
      }
      if (path.size() == bfs_map[startPos[0].y][startPos[0].x]) exploring = false;
      while (!path.empty()) path.pop();
      std::swap_ranges(startPos, startPos + 4, goalPos);
    }
  }
  log("Done explore!");
  log("Run to finish!");

  API::setColor(currPos.x, currPos.y, 'B');
  updateSurrounding();
  bfs();
  debugBFS();
  while (!isFinish()) {
    bestDir = getBestMove();
    move(bestDir);
    API::setColor(currPos.x, currPos.y, 'B');
    updateSurrounding();
    bfs();
    debugBFS();
  }
  logMap();
  return 0;
}
