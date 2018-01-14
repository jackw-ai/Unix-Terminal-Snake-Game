// full fledged snake game played in terminal
// (c) 2017 Tingda Wang

#include "snake.h"
#include <unistd.h>
using namespace std;

snakeBody::snakeBody(int row, int column) {
    x = row;
    y = column;
}

snakeBody::snakeBody() {
    x = 0;
    y = 0;
}

SnakeClass::SnakeClass() {
    initscr();
    nodelay(stdscr,true); // continue without key
    keypad(stdscr,true); // initialize keyboard
    noecho(); // don't echo input
    curs_set(0); // cursor invisible
    getmaxyx(stdscr,maxHeight,maxWidth);
    
    // char design
    bodyPart = 'o';
    edge = (char)254;
    foo = 'x';
}

SnakeClass::~SnakeClass(){
    nodelay(stdscr, false);
    getch();
    endwin();
}

// setup new game
void SnakeClass::gameSet(){
    clear(); // clear screen
    
    // reset snake
    for(int i = 0; i < 2; i++)
        snake.push_back(snakeBody(100 + i, 10));
    
    //reset variables
    score = 0;
    difficulty = 120000;
    get = false;
    dir = 'l';
    
    srand(time(0)); //init rng
    placeFood();
    printBoard();

    // print entire snake
    for(int i = 0; i < snake.size(); i++){
        move(snake[i].y, snake[i].x);
        addch(bodyPart);
    }

    // print score
    move(maxHeight - 1, 0);
    printw("Score: %d", score);

    // print food
    move(food.y, food.x);
    addch(foo);
    refresh(); //refreshes screen
}

// print edges of the board
void SnakeClass::printBoard(){

    // top
    for(int i = 0; i < maxWidth - 1; i++){
        move(0,i);
        addch(edge);
    }
    // bottom
    for(int i = 0; i < maxWidth - 1; i++){
        move(maxHeight - 2,i);
        addch(edge);
    }
    // right
    for(int i = 0; i < maxHeight - 1; i++){
        move(i, maxWidth - 2);
        addch(edge);
    }
    // left
    for(int i = 0; i < maxHeight - 1; i++){
        move(i, 0);
        addch(edge);
    }
    refresh();
}

// generate new food on random location on board
void SnakeClass::placeFood(){
    bool _set = false;
    while(!_set){
        int _x = rand() % maxWidth + 1;
        int _y = rand() %maxHeight + 1;
        if(_x >= maxWidth - 2 || _y >= maxHeight - 3) continue; // try again
        for(int i = 0; i < snake.size(); i++) 
            if(snake[i].x == _x && snake[i].y == _y) continue; // try again
        food.x = _x;
        food.y = _y;
        _set = true;
    }
    move(food.y, food.x);
    addch(foo);
    refresh();
}

// the snake hit itself or the food
bool SnakeClass::hit(){ 
   
    // BAD: hit itself, can't hit 2nd or 3rd body part
    for(int i = 3; i < snake.size(); i++){
        if((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y)) 
            return true;
    }

    // GOOD: reached the food
    if(snake[0].x == food.x && snake[0].y == food.y){
        get = true; //gotcha
        placeFood(); // here comes the new food

        score += 10; // + 10 score, yahoo! 
        move(maxHeight - 1, 0);
        printw("Score: %d", score);
        
        //getting harder, less delay now
        if(score > 10) difficulty -= 5000; 
    
    }else 
        get = false; //didn't get it yet

    return false;
}

void SnakeClass::moveSnake(){
    
    //keyboard command
    int _tmp = getch();
    switch(_tmp){
    case KEY_LEFT:
    case 'a':
        if(dir != 'r') dir = 'l';
        break;
    case KEY_RIGHT:
    case 'd':
        if(dir != 'l') dir = 'r';
        break;
    case KEY_UP:
    case 'w':
        if(dir != 'd') dir = 'u';
        break;
    case KEY_DOWN:
    case 's':
        if(dir != 'u') dir = 'd';
        break;
    case 'q':
        dir = 'q';
        break;
    }

    if(!get){
        move(snake[snake.size() - 1].y, snake[snake.size() - 1].x);
        printw(" "); // addch(" ")
        refresh();
        snake.pop_back(); // delete tail
    }

    if(dir == 'l') {  
        if(snake[0].x == 0) // left edge
            snake.insert(snake.begin(), snakeBody(maxWidth - 2, snake[0].y));
        else            
            snake.insert(snake.begin(), snakeBody(snake[0].x - 1, snake[0].y));
    }else if(dir == 'r'){
        if(snake[0].x == maxWidth - 1) // right edge
            snake.insert(snake.begin(), snakeBody(1, snake[0].y));
        else            
            snake.insert(snake.begin(), snakeBody(snake[0].x + 1, snake[0].y));
    }else if(dir == 'u'){
        if(snake[0].y == 0) // top edge
            snake.insert(snake.begin(), snakeBody(snake[0].x, maxHeight - 3));
        else            
            snake.insert(snake.begin(), snakeBody(snake[0].x, snake[0].y - 1));
    }else if(dir == 'd'){
        if(snake[0].y == maxHeight - 2) // bottom edge
            snake.insert(snake.begin(), snakeBody(snake[0].x, 1));
        else            
            snake.insert(snake.begin(), snakeBody(snake[0].x, snake[0].y + 1));
    }
    
    printBoard();

    //advance by 1
    move(snake[0].y, snake[0].x);
    addch(bodyPart);
    refresh();
}

// continue or give up?
void SnakeClass::gameEnd(){
    nodelay(stdscr,false);
    getch();
    move(maxHeight / 2 - 1, maxWidth / 2 - 11);
    printw("Game Over, Try Again?");
    move(maxHeight / 2, maxWidth / 2 - 20);
    printw("(Press any key to continue or q to quit)");
    refresh();
    timeout(500000);
    char _tmp = getchar();
    // restart game
    if(_tmp != 'q'){
        snake.clear();
        nodelay(stdscr,true);
        gameSet();
        start();
    }
}

// facilitates game
void SnakeClass::start(){
    bool gameOver = false;
    while(!gameOver){

        // hit something
        if(hit()){
            gameEnd();
            gameOver = true;
        }
        
        moveSnake();

        // quitter's interface
        if(dir == 'q'){
            move(maxHeight / 2 - 1, maxWidth / 2 - 18);
            printw("Are you sure you want to quit?");
            move(maxHeight / 2, maxWidth / 2 - 25);
            printw("(Press any key to restart or q to quit)");
            refresh();
            char _tmp = getchar();
            if(_tmp != 'q'){
                snake.clear();
                gameSet();
            }else 
                return;
        }else if(dir == 'u' || dir == 'd') 
            usleep(difficulty + 36000);
        else 
            usleep(difficulty);
    }
}
