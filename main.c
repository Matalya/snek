#include <locale.h>
#include <stdio.h>
#include <wchar.h>

void printBoard(int width) {
    printf("%lc", 0x250c);
    for (int i = 0; i < width; i++) {
        
    }
}

int main() {
    setlocale(LC_CTYPE, "");
    printBoard(5);
}