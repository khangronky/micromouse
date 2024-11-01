#include <Arduino.h>
#include <queue>
#include <stack>
#include <cstring>
#include "Controller.h" // Include the Controller header

#define MAZE_WIDTH 3
#define MAZE_HEIGHT 10

// Define a struct to represent a position in the maze
struct pos {
    int x, y;
    pos() : x(0), y(0) {} // Default constructor
    pos(const int x, const int y) : x(x), y(y) {} // Parameterized constructor
    pos(const pos& other) : x(other.x), y(other.y) {} // Copy constructor
    bool operator==(const pos& other) const { // Equality operator
        return (x == other.x) && (y == other.y);
    }
    void operator+=(const pos& other) { // Addition assignment operator
        x += other.x;
        y += other.y;
    }
    pos operator+(const pos& other) { // Addition operator
        return pos(x + other.x, y + other.y);
    }
};

// Define the maze and BFS map
uint8_t maze[MAZE_HEIGHT][MAZE_WIDTH];
unsigned short bfs_map[MAZE_HEIGHT][MAZE_WIDTH];
const unsigned short INF = MAZE_WIDTH * MAZE_HEIGHT + 1; // Define infinity as a large number
const pos drs[] = {pos(-1, 0), pos(0, 1), pos(1, 0), pos(0, -1)}; // Define directions (left, up, right, down)
bool surrounds[3]; // Declare surrounds array
int facing = 1; // Declare and initialize facing (0: left, 1: up, 2: right, 3: down)

pos currPos;
pos startPos(0, 0);
pos goalPos[] = {pos(9, 2)};
int testnotnec;
// Check if a position is valid (within maze boundaries)
bool isValid(const pos &p) {
    return ((p.x >= 0) && (p.y >= 0) && (p.x < MAZE_WIDTH) &&
            (p.y < MAZE_HEIGHT));
}

// Check if a position is a goal position
bool isGoal(const pos &p) {
    for (const pos &goal : goalPos)
        if (p == goal)
            return true;
    return false;
}

// Check if the current position is a goal position
bool isFinish() {
    for (const pos &goal : goalPos)
        if (currPos == goal)
            return true;
    return false;
}

// Initialize the maze with preset values
void initializeMaze() {
    uint8_t presetMaze[MAZE_HEIGHT][MAZE_WIDTH] = {
        {11, 1, 0},  // S with West+North walls, middle has West wall
        {9, 0, 1},   // West+South walls, right has East wall
        {8, 1, 0},   // West wall, middle has West wall
        {9, 1, 0},   // West+South walls, middle has West wall
        {8, 3, 3},   // West wall, middle and right have East+West walls
        {8, 1, 0},   // West wall, middle has West wall
        {9, 1, 0},   // West+South walls, middle has West wall
        {8, 0, 2}    // West wall, right has Goal+East wall
    };
    memcpy(maze, presetMaze, sizeof(presetMaze)); // Copy preset maze to maze array
}


// Modified BFS check needed
bool canTraverse(pos from, pos to) {
    // Get wall information
    uint8_t fromCell = maze[from.y][from.x];
    
    // Calculate direction
    int dx = to.x - from.x;
    int dy = to.y - from.y;
    int direction;
    
    if (dx == 1) direction = 2;      // East
    else if (dx == -1) direction = 0; // West
    else if (dy == 1) direction = 3;  // South
    else direction = 1;               // North
    
    // Check if wall exists in this direction
    return !(fromCell & (1 << direction));
}

// Implement the BFS algorithm to calculate Manhattan distances
void bfs() {
    std::fill(&bfs_map[0][0], &bfs_map[0][0] + MAZE_WIDTH * MAZE_HEIGHT, INF); // Initialize BFS map with infinity
    pos p_front, p_temp;
    uint8_t block;
    pos p_current;  // Define current position
    std::queue<pos> q;

     // Print goal positions being processed
    for (const pos &p : goalPos) {
        Serial.println("Processing goal at: (" + String(p.x) + "," + String(p.y) + ")");
        bfs_map[p.y][p.x] = 0;
        q.push(p);
    }

    while (!q.empty()) {
        p_front = q.front();
        p_current = q.front(); 
        q.pop();
        block = maze[p_front.y][p_front.x];  // Add this line
        Serial.println("Processing position: (" + String(p_front.x) + "," + String(p_front.y) + 
                      ") with value: " + String(bfs_map[p_front.y][p_front.x]));

        // for (int i = 0; i < 4; ++i) {
        //     if (!(block & (1 << i))) { // Check if the direction is accessible
        //         p_temp = p_front + drs[i];
        //         if (!isValid(p_temp) || bfs_map[p_temp.y][p_temp.x] != INF || isGoal(p_temp))
        //             continue;
        //         bfs_map[p_temp.y][p_temp.x] = bfs_map[p_front.y][p_front.x] + 1; // Set neighbor's value to front cell's value + 1
        //         q.push(p_temp); // Add neighbor to the queue
        //     }
        // }

        for (int dir = 0; dir < 4; dir++) {
            pos next = p_current + drs[dir];
            if (isValid(next) && canTraverse(p_current, next)) {
                if (bfs_map[next.y][next.x] == INF) {
                    bfs_map[next.y][next.x] = bfs_map[p_current.y][p_current.x] + 1;
                    q.push(next);
                }
            }
        }

    // Debugging output for BFS map
    Serial.println("Final BFS Map:");
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            Serial.print(bfs_map[y][x]);
            Serial.print(" ");
        }
        Serial.println();
    }
}}

//SourceGraph CodyTo verify step
bool verifyBfsMap() {
    bool valid = true;
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            if (bfs_map[y][x] == INF) {
                Serial.println("Warning: Cell (" + String(x) + "," + String(y) + ") unreachable");
                valid = false;
            }
        }
    }
    return valid;
}

// Set a bit in a byte
void setBit(uint8_t &byte, const int pos, const bool value) {
    byte = (byte & ~(1 << pos)) | (value << pos);
}

// Update the surrounding cells based on sensor input
void updateSurrounding() {
    int offset; // integer to store the direction offset
    pos p_temp; //p_temp: A temporary position variable used to calculate neighboring positions.

    //Sensor Input
    surrounds[0] = Controller::wallLeft();
    surrounds[1] = Controller::wallFront();
    surrounds[2] = Controller::wallRight();

//This loop iterates through the three sensor inputs (left, front, right).

    for (int i = 0; i < 3; ++i) {

        //offset: Calculates the direction offset based on the current facing direction and the sensor input index.
        offset = (facing + i + 3) % 4;

        //Update current cell

        setBit(maze[currPos.y][currPos.x], offset, surrounds[i]);   //Updates the current cell in the maze with the sensor input value.
        setBit(maze[currPos.y][currPos.x], offset + 4, 1);          //Marks the direction as visited.

        p_temp = currPos + drs[offset];                             //  Calculates the neighboring position based on the current position and the direction offset.


        if (isValid(p_temp)) {                                                  //Checks if the neighboring position is valid (within maze boundaries).
            setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4, surrounds[i]);   //Updates the neighboring cell in the maze with the sensor input value.
            setBit(maze[p_temp.y][p_temp.x], (offset + 2) % 4 + 4, 1);          //Marks the direction as visited.
        }
    }

    // Debugging output for maze data
    Serial.println("Maze Data:");
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            Serial.print(maze[y][x], BIN);
            Serial.print(" ");
        }
        Serial.println();
    }
}

// Get the best move based on the BFS map
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

// Move the mouse in the specified direction
void move(int direction) {
    switch (direction) {
        case 0:
            currPos += pos(-1, 0); // Move West
            Serial.println("Move West");
            break;
        case 1:
            currPos += pos(0, -1); // Move North
            Serial.println("Move North");
            break;
        case 2:
            currPos += pos(1, 0); // Move East
            Serial.println("Move East");
            break;
        case 3:
            currPos += pos(0, 1); // Move South
            Serial.println("Move South");
            break;
    }
}

// Reset the mouse position and facing direction
void reset() {
    Controller::ackReset();
    currPos = startPos;
    facing = 1;
}

// Calculate Manhattan distance between two positions
int manhattanDistance(pos p1, pos p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

// Global variables for main loop
char command;
int state = 0; // 0: Manual control, 1: Maze solving
int micromouseStep = 0;
int explorationStep = 0;
int ready = 0;

int bestDir = -1;
std::stack<pos> path;


// Add these at the top with other global variables
const int MAX_DEBUG_STEPS = 10;
int debugStepCount = 0;

bool validateStateTransition(int currentState, int nextState) {
    Serial.println("Validating transition: " + String(currentState) + " -> " + String(nextState));
    return true;
}

void resetState() {
    state = 0;
    micromouseStep = 0;
    explorationStep = 0;
    debugStepCount = 0;
    Serial.println("State machine reset");
}


// Debug function to initialize the maze and run BFS
void debug() {
    initializeMaze();
    Serial.println("Goal position: (" + String(goalPos[0].x) + "," + String(goalPos[0].y) + ")");
    
    // Print initial maze state
    Serial.println("Initial Maze State:");
    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            Serial.print(maze[y][x], BIN);
            Serial.print("\t");
        }
        Serial.println();
    }

    while (debugStepCount < MAX_DEBUG_STEPS) {
        Serial.print("Debug Step: ");
        Serial.println(debugStepCount);
        
        updateSurrounding();
        bfs();
        
        int direction = getBestMove();
        if (direction == -1) {
            Serial.println("No valid direction found. Stopping debug.");
            break;
        }
        
        move(direction);
        debugStepCount++;
        
        if (isFinish()) {
            Serial.println("Goal reached in debug mode!");
            break;
        }
    }
}

void setup() {
    Serial.begin(9600);
    Controller::begin();
    debug(); // Call the debug function
}

void debugState() {
    static int lastState = -1;
    static int lastMicromouseStep = -1;
    static int lastExplorationStep = -1;
    
    if (state != lastState || micromouseStep != lastMicromouseStep || 
        explorationStep != lastExplorationStep) {
        Serial.println("State Machine Status:");
        Serial.println("State: " + String(state));
        Serial.println("Micromouse Step: " + String(micromouseStep));
        Serial.println("Exploration Step: " + String(explorationStep));
        
        lastState = state;
        lastMicromouseStep = micromouseStep;
        lastExplorationStep = explorationStep;
    }
}

void loop() {
    static unsigned long lastStateChange = millis();
    const unsigned long STATE_TIMEOUT = 5000;
    
    if (millis() - lastStateChange > STATE_TIMEOUT) {
        resetState();
        lastStateChange = millis();
    }
    
    debugState();

    if (Serial.available() > 0) {
        command = Serial.read();
        Serial.print("Command received: ");
        Serial.println(command);
        if (command == 'X') {
            state = 0;
            Serial.println("State changed to 0 (Manual control)");
        }
        if (command == 'Y') {
            state = 1;
            Serial.println("State changed to 1 (Maze solving)");
        }
    }

    if (state == 0) {
        // Manual control
        Controller::manualAction(command);
    }

    if (state == 1) {
        Serial.print("Micromouse step: ");
        Serial.println(micromouseStep);
        switch (micromouseStep) {
            case 0:
                Serial.println("Entering case 0");
                initializeMaze(); // Initialize maze data
                
                micromouseStep++;
                Serial.println("Exiting case 0");
                break;

            case 1:
                Serial.println("Entering case 1");
                Serial.print("Exploration step: ");
                Serial.println(explorationStep);
                
                if (explorationStep == 0 || explorationStep == 3) {
                    updateSurrounding();
                    bfs();
                    if (!verifyBfsMap()) {
                        Serial.println("Warning: BFS map contains unreachable cells");
                    }
                    explorationStep++;
                }
                if (explorationStep == 1 || explorationStep == 4) {
                    if (!isFinish()) {
                        path.push(currPos);
                        bestDir = getBestMove();
                        if (bestDir == -1) {
                            Serial.println("No valid direction found. Stopping exploration.");
                            state = 0;
                            micromouseStep = 0;
                            return;
                        }
                        move(bestDir);
                        updateSurrounding();
                        bfs();
                    } else {
                        explorationStep++;
                    }
                }
                if (explorationStep == 2 || explorationStep == 5) {
                    if (path.size() == bfs_map[startPos.y][startPos.x]) ready = 1;
                    while (!path.empty()) path.pop();
                    std::swap_ranges(goalPos, goalPos + 1, goalPos + 1); // Corrected usage
                    explorationStep++;
                }
                if (explorationStep == 6) {
                    if (ready == 1) {
                        micromouseStep++;
                        ready = 0;
                    } else {
                        explorationStep = 0;
                    }
                }
                Serial.println("Exiting case 1");
                break;
            case 2:
                Serial.println("Entering case 2");
                updateSurrounding();
                bfs();
                micromouseStep++;
                Serial.println("Exiting case 2");
                break;
            case 3:
                Serial.println("Entering case 3");
                Serial.print("Current position: ");
                Serial.print(currPos.x);
                Serial.print(", ");
                Serial.println(currPos.y);
                int distance = manhattanDistance(currPos, goalPos[0]);
                Serial.print("Manhattan distance to goal: ");
                Serial.println(distance);
                if (!isFinish()) {
                    bestDir = getBestMove();
                    Serial.print("Best direction: ");
                    Serial.println(bestDir);
                    if (bestDir == -1) {
                        Serial.println("No valid direction found. Stopping exploration.");
                        state = 0;
                        micromouseStep = 0;
                        break;
                    }
                    move(bestDir);
                    updateSurrounding();
                    bfs();
                } else {
                    Serial.println("Goal reached!");
                    state = 0;
                    micromouseStep = 0;
                }
                Serial.println("Exiting case 3");
                break;
        }
    }
}