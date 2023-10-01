#include <locale.h>
#include <stdio.h>
#include <wchar.h>
const wchar_t ESC = 0x001b;

void printBoard(int width, int height) {
    //Print score
    printf("%lc[42CScore: ??\n", ESC);

    //Print top
    printf("%lc", 0x250c);
    for (int i = 0; i < width; i++) {
        printf("%lc", 0x2500);
    }
    printf("%lc\n", 0x2510);

    //Print the sides
    for (int i = 0; i < height; i++) {
        printf("%lc%lc[%dC%lc\n", 0x2502, ESC, width, 0x2502);
    }

    //Print the bottom
    printf("%lc", 0x2514);
    for (int i = 0; i < width; i++) {
        printf("%lc", 0x2500);
    }
    printf("%lc\n", 0x2518);
}

int main() {
    setlocale(LC_CTYPE, "");
    printBoard(90, 19);
}