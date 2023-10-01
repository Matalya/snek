#include <locale.h>
#include <stdio.h>
#include <wchar.h>

const wchar_t ESC = 0x001b;
const wchar_t TPLF = 0x250c;
const wchar_t HORI = 0x2500;
const wchar_t TPRT = 0x2510;
const wchar_t VERT = 0x2502;
const wchar_t BTLF = 0x2514;
const wchar_t BTRT = 0x2518;

void printBoard(int width, int height) {
    //Print score
    printf("%lc[42CScore: ??\n", ESC);

    //Print top
    printf("%lc", TPLF);
    for (int i = 0; i < width; i++) {
        printf("%lc", HORI);
    }
    printf("%lc\n", TPRT);

    //Print the sides
    for (int i = 0; i < height; i++) {
        printf("%lc%lc[%dC%lc\n", VERT, ESC, width, VERT);
    }

    //Print the bottom
    printf("%lc", BTLF);
    for (int i = 0; i < width; i++) {
        printf("%lc", HORI);
    }
    printf("%lc\n", BTRT);
}

int main() {
    setlocale(LC_CTYPE, "");
    printBoard(90, 19);
}