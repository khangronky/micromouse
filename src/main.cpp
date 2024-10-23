#include <Arduino.h>
#include <stack>

#include "Algorithm.h"
#include "Controller.h"

int state = 0;

void setup() {
  Controller::begin();
}

void loop() {
  if (state == 0) {

  }
  if (state == 1) {
    std::stack<pos> path;
    int bestDir;
    bool exploring = true;

    memset(maze, 0, sizeof(uint8_t) * MAZE_WIDTH * MAZE_HEIGHT);
    while (exploring) {
      for (int i = 0; i < 2; ++i) {
        updateSurrounding();
        bfs();
        while (!isFinish()) {
          path.push(currPos);
          bestDir = getBestMove();
          while (bestDir == -1) {
            state = 0;
          }
          move(bestDir);
          updateSurrounding();
          bfs();
        }
        if (path.size() == bfs_map[startPos[0].y][startPos[0].x]) exploring = false;
        while (!path.empty()) path.pop();
        std::swap_ranges(startPos, startPos + 4, goalPos);
      }
    }

    updateSurrounding();
    bfs();
    while (!isFinish()) {
      bestDir = getBestMove();
      move(bestDir);
      updateSurrounding();
      bfs();
    }
    state = 0;
  }
}