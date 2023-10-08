#include <locale.h>
#include <stdio.h>
#include <wchar.h>
#include "circular_array.h"
#include <unistd.h>
#define fori(x) for (int i = 0; i < x; i++)

typedef struct {
    int x;
    int y;
} coords;

typedef enum {
    UP,
    LEFT,
    DOWN,
    RIGHT,
} Dir;

typedef struct {
    coords head;
    Dir direction;
} snekHead;

const int BOARD_WIDTH = 91;
const int BOARD_HEIGHT = 25;

const wchar_t ESC = 0x001b;
const wchar_t TPLF = 0x250c;
const wchar_t HORI = 0x2500;
const wchar_t TPRT = 0x2510;
const wchar_t VERT = 0x2502;
const wchar_t BTLF = 0x2514;
const wchar_t BTRT = 0x2518;
const wchar_t FLBK = 0x2588;
const wchar_t BLCK = 0x25A0;
const wchar_t UPPERHALFBLOCK = 0x2580;
const wchar_t BVRC = 0x25AE;
const wchar_t LFAR = 0x2190;
const wchar_t TPAR = 0x2191;
const wchar_t RTAR = 0x2192;
const wchar_t DWAR = 0x2193;

coords* makecoord(int x, int y) {
    coords* coord = malloc(sizeof(coords));
    coord->x = x;
    coord->y = y;
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

void printBoard(Dir dir) {
    //Clear the game area
    for (int col = 2; col <= BOARD_HEIGHT; col++) {
        for (int row = 2; row <= BOARD_WIDTH; row++) {
            printf("%lc[%d;%dH ", ESC, col, row);
        }
    }
    printf("%lc[2;1H", ESC);

    //Print score
    printf("%lc[33CScore: ??       Direction: %lc\n%lc[3;3", ESC, pickArrow(dir), ESC);

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

void printSnek(coords* coords, wchar_t thechar) {
    printf("%lc[%d;%dH%lc\n", ESC, coords->y, coords->x, thechar);
    printf("%lc[24;0H", ESC);
}



int gameover(coords* pos) {
    int gamestate = 0;
    if ((pos->x == 1 || pos->x == BOARD_WIDTH + 1) || (pos->y == 1 || pos->y == BOARD_HEIGHT + 1)) {
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

int main() {
    int BOARD_WIDTH = 91;
    int BOARD_HEIGHT = 25;
    Dir snekdir = DOWN;
    coords* CENTER = makecoord(46, 13);
    coords* snekpos = CENTER;
    setlocale(LC_CTYPE, "");
    printBoard(snekdir);
    
    int game_over = gameover(snekpos);
    while (!game_over) {
        printBoard(snekdir);
        printSnek(snekpos, BVRC);
        updatePos(snekdir, snekpos);
        usleep(50000);
        game_over = gameover(snekpos);
    }
    printSnek(snekpos, ' ');
    printf("%lc[13;41HGAME OVER%lc[26;1H", ESC, ESC);
}