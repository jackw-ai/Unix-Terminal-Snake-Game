# Unix C++ Snake Game
Snake Game played in the Unix terminal. Implemented using C++ and ncurses library. 

## Features
The program generates a snake game in your Unix machine terminal window. The goal is to have the snake eat the food, placed randomly on the screen. The more food the snake eats, the longer it gets and the faster it crawls, making the game more difficult. Each food is worth 10 points, which adds to your total score.

The game supports traversing through borders, as the snake can go through the borders of the window to emerge at the other end. The only cause of 'Game Over!' is the snake crawling into itself.

```sh
#############
#  ooo      #
#           #
#       x   #
#           #
#############
```

## Usage and Requirements
First generate the executable:
```sh
make snake
```
Ensure that you are running a Unix machine (Mac or Linux) with the 'g++' compiler. Windows sytems are not supported due to the usage of the ncurses library (unix equivalent of conio in windows).

## Controls
Control the snake using the arrow keys or 'A-S-D-W' keys as in most traditional video games. 

To quit the game or restart, press 'q', and follwing the prompt on the screen, press 'q' again to exit or press any other key to restart.

## Rules of the Game
The snake can traverse anywhere, in direction (up, down, left, right) provided it doesn't crawl into itself.

## Future Features
Add support for leaderboards, game pausing, more robust menusystem and possibly multiplayer? Finer tuning of difficulty and graphic design.

