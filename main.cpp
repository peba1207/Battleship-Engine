#include <iostream>
#include "BoardState.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    for(int i = 0; i<4; i++) {
        for(int j = 0; j<4; j++) {
            BoardState *test = new BoardState();
            test->setEmpty(j, i);
            cout << "(" << j << "," << i << "): " << test->getAllBoards() << endl;
            delete test;
        }
    }

    return 0;
}
