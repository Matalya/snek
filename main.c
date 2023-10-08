#include <locale.h>
#include <stdio.h>
#include <wchar.h>
#include "circular_array.h"
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

#define fori(x) for (int i = 0; i < x; i++)

void become_fanon(struct termios *original, struct termios *modified) {
    // Get the original terminal settings
    tcgetattr(STDIN_FILENO, original);
    modified = original;

    // Disable canonical mode and echoing
    modified->c_lflag &= ~(ICANON | ECHO);

    // Set the new terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, modified);
}

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Dir;

const int BOARD_WIDTH = 91;
const int BOARD_HEIGHT = 25;

const wchar_t ESC = 0x001b;
//Block building
const wchar_t TPLF = 0x250c;
const wchar_t HORI = 0x2500;
const wchar_t TPRT = 0x2510;
const wchar_t VERT = 0x2502;
const wchar_t BTLF = 0x2514;
const wchar_t BTRT = 0x2518;
//Full black
const wchar_t FLBK = 0x2588;
//Black square
const wchar_t BLCK = 0x25A0;
const wchar_t UPPERHALFBLOCK = 0x2580;
const wchar_t BVRC = 0x25AE;
//Direction arrows
const wchar_t LFAR = 0x2190;
const wchar_t TPAR = 0x2191;
const wchar_t RTAR = 0x2192;
const wchar_t DWAR = 0x2193;

coords makecoord(int x, int y) {
    coords coord = {
        .x = x,
        .y = y,
    };
    return coord;
}

wchar_t pickArrow(Dir dir) {
    switch (dir) {
        case LEFT:
            return LFAR;
            break;
        case UP:
            return TPAR;
            break;
        case RIGHT:
            return RTAR;
            break;
        case DOWN:
            return DWAR;
            break;
    }
}

void clearGameArea() {
    //Clear the game area
    for (int col = 2; col <= BOARD_HEIGHT; col++) {
        for (int row = 2; row <= BOARD_WIDTH; row++) {
            printf("%lc[%d;%dH ", ESC, col, row);
        }
    }
}

void printBoard(Dir dir) {
    //Print score
    printf("%lc[2;1H%lc[33CScore: ??       Direction: %lc\n%lc[3;3", ESC, ESC, pickArrow(dir), ESC);

    //Print top
    printf("%lc[3;1H%lc", ESC, TPLF);
    for (int i = 2; i < BOARD_WIDTH; i++) {
        printf("%lc[3;%dH%lc", ESC, i, HORI);
    }
    printf("%lc[3;%dH%lc", ESC, BOARD_WIDTH, TPRT);

    //Print the sides
    for (int i = 4; i < BOARD_HEIGHT; i++) {
        printf("%lc[%d;1H%lc%lc[%d;%dH%lc", ESC, i, VERT, ESC, i, BOARD_WIDTH, VERT);
    }

    //Print the bottom
    printf("%lc[%d;1H%lc", ESC, BOARD_HEIGHT, BTLF);
    for (int i = 2; i < BOARD_WIDTH; i++) {
        printf("%lc[%d;%dH%lc", ESC, BOARD_HEIGHT, i, HORI);
    }
    printf("%lc[%d;%dH%lc", ESC, BOARD_HEIGHT, BOARD_WIDTH, BTRT);

    //Return cursor to final line
    printf("%lc[%d;1H", ESC, BOARD_HEIGHT+1);
}

void printSnek(coords coords, wchar_t thechar) {
    printf("%lc[%d;%dH%lc\n", ESC, coords.y, coords.x, thechar);
    printf("%lc[%d;0H", ESC, BOARD_HEIGHT + 1);
}



int gameover(coords pos) {
    int gamestate = 0;
    if ((pos.x <= 0 || pos.x >= BOARD_WIDTH) || (pos.y <= 3 || pos.y >= BOARD_HEIGHT)) {
        gamestate = 1;
    }
    return gamestate;
}

void updatePos(Dir dir, coords* pos) {
    switch (dir) {
        case UP:
            pos->y--;
            break;
        case DOWN:
            pos->y++;
            break;
        case LEFT:
            pos->x--;
            break;
        case RIGHT:
            pos->x++;
            break;
    }
}

typedef enum {
    KEY_UP = 119,
    KEY_LEFT = 97,
    KEY_DOWN = 115,
    KEY_RIGHT = 100,
} UserInput;

Dir pickDirFromInput(int input, Dir currentDir) {
    switch (input) {
        case KEY_UP:
            return UP;
            break;
        case KEY_DOWN:
            return DOWN;
            break;
        case KEY_LEFT:
            return LEFT;
            break;
        case KEY_RIGHT:
            return RIGHT;
            break;
        default:
            return currentDir;
            break;
    }
}

//Detects if a keyboard hit has occured. Returns TRUE if so.
int kbhit(void) {
    struct timeval tv;
    fd_set rdfs;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}


int main() {
    //Setting up some shit, Idk what it's doing.
    struct termios original, modified;
    become_fanon(&original, &modified);
    setlocale(LC_CTYPE, "");

    Dir snekdir = RIGHT;
    coords CENTER = makecoord(46, 13);
    coords snekpos = CENTER;

    Circle* snekBody = initCircle(1);
    enqueueItem(snekBody, snekpos);
    
    printBoard(snekdir);
    
    while (!gameover(snekpos)) {
        //Detect keystrokes and updates direction.
        if (kbhit()) {snekdir = pickDirFromInput(getchar(), snekdir);}
        clearGameArea();
        printBoard(snekdir);
        printSnek(snekpos, FLBK);
        updatePos(snekdir, &snekpos);
        enqueueItem(snekBody, snekpos);
        usleep(snekdir < 2?150000:100000);
    }
    clearGameArea();
    printBoard(snekdir);
    printSnek(snekpos, 'X');
    printf("%lc[13;41HGAME OVER%lc[26;1H", ESC, ESC);
    
    // Restore the original terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
    return 0;
}