#include <Arduino.h>
#include <stack>

#include "Algorithm.h"
#include "Controller.h"

char command = 0;
int state = 0;
int micromouseStep = 0;
int explorationStep = 0;
int ready = 0;

int bestDir = -1;
std::stack<pos> path;

void setup()
{
  Serial.begin(9600);
  Controller::begin();
}

void loop()
{
  if (Serial.available() > 0)
  {
    command = Serial.read();
    if (command == 'X')
      state = 0;
    if (command == 'Y')
      state = 1;
  }

  if (state == 0)
  {
    Controller::action(command);
  }

  if (state == 1)
  {
    switch (micromouseStep)
    {
    case 0:
      memset(maze, 0, sizeof(uint8_t) * MAZE_WIDTH * MAZE_HEIGHT);
      micromouseStep++;
      break;
    case 1:
      if (explorationStep == 0 || explorationStep == 3)
      {
        updateSurrounding();
        bfs();
        explorationStep++;
      }
      if (explorationStep == 1 || explorationStep == 4)
      {
        if (!isFinish())
        {
          path.push(currPos);
          bestDir = getBestMove();
          if (bestDir == -1)
          {
            state = 0;
            micromouseStep = 0;
            return;
          }
          move(bestDir);
          updateSurrounding();
          bfs();
        }
        else
        {
          explorationStep++;
        }
      }
      if (explorationStep == 2 || explorationStep == 5)
      {
        if (path.size() == bfs_map[startPos[0].y][startPos[0].x])
          ready = 1;
        while (!path.empty())
          path.pop();
        std::swap_ranges(startPos, startPos + 4, goalPos);
        explorationStep++;
      }
      if (explorationStep == 6)
      {
        if (ready == 1)
        {
          micromouseStep++;
          ready = 0;
        }
        else
        {
          explorationStep = 0;
        }
      }
      break;
    case 2:
      updateSurrounding();
      bfs();
      micromouseStep++;
      break;
    case 3:
      if (!isFinish())
      {
        bestDir = getBestMove();
        move(bestDir);
        updateSurrounding();
        bfs();
      }
      else
      {
        state = 0;
        micromouseStep = 0;
      }
      break;
    }
  }
}