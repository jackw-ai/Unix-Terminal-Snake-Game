// header file for snake game
// (c) 2017 Tingda Wang

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <unistd.h>
#ifndef SNAKE_H
#define SNAKE_H

struct snakeBody{
    int x,y; //coord of body part
    
    // constructors
    snakeBody(int col, int row);
    snakeBody();
};

class SnakeClass{

private:    
    int score; 
    int difficulty; // how much delay, lower, harder

    bool get; // got food or not
    char dir; // direction snake is going

    // window dimensions
    int maxWidth;
    int maxHeight;

    // designs
    char bodyPart;
    char edge;
    char foo;

    snakeBody food; // the target
    std::vector<snakeBody> snake;

    void placeFood();
    bool hit();
    void printBoard();
    void moveSnake();
    void gameEnd(); 

public:
    SnakeClass(); // constructor
    ~SnakeClass(); // destructor
    void gameSet(); // creates game
    void start(); // starts the game
};

#endif
