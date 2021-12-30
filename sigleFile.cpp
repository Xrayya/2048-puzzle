#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>

using namespace std;

int field[4][4], fieldBackUp[4][4];
int score;
int kInput;
enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};
direction dir;
bool gameOver = false;
bool inGame = true;
void display (int num[4][4]) {
    system("cls");

    cout << "\n\n\n";
    for (int i = 0; i < 4; i++) {
        cout << "\t\t\t---------------------" << endl;
        cout << "\t\t\t";

        for (int j = 0; j < 4; j++) {
            if (num[i][j] == 0) {
                cout << "|    ";
            } else if (num[i][j] <= 9) {
                cout << "|  " << num[i][j] << " ";
            } else if (num[i][j] <= 99) {
                cout << "| " << num[i][j] << " ";
            } else if (num[i][j] <= 999) {
                cout << "| " << num[i][j];
            } else if (num[i][j] <= 9999) {
                cout << "|" << num[i][j];
            }
        }
        cout << "|" << endl;
    }
    cout << "\t\t\t---------------------";
}

void homeDisplay() {
    cout << "\n\n\n\n\t\t\t-----------------";
    cout << "\n\t\t\t|  WELCOME  TO  |";
    cout << "\n\t\t\t|   2048 GAME   |";
    cout << "\n\t\t\t-----------------";
    cout << "\n\n\t\t    Press any key to continue";
}

int random(int num) {
    int result;

    result = rand() % num + 0;

    return result;
}

void generateNum() {
    int x, y, randNum;

    x = random(4);
    y = random(4);
    randNum = random(20);

    if (field[y][x] != 0) {
        if (randNum < 2) {
            field[y][x] = 4;
        } else {
            field[y][x] = 2;
        }
    } else {
        generateNum();
    }
}

void setup() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            field[i][j] = 0;
        }
    }

    generateNum();
    generateNum();

    display(field);
}

void backUp() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            fieldBackUp[i][j] = field[i][j];
        }
    }
}

void undo() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            field[i][j] = fieldBackUp[i][j];
        }
    }
}

bool checkBlockMove() {
    bool move = false;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (field[i][j] != fieldBackUp[i][j]) {
                move = true;
                break;
            }
        }

        if (move == true) {
            break;
        }
    }

    return move;
}

bool checkPossMove() {
    bool emptyBlock = false;
    bool sumPoss = false;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (field[i][j] == 0) {
                emptyBlock = true;
                break;
            }
        }

        if (emptyBlock == true) {
            break;
        }
    }

    if (!emptyBlock)
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i + 1][j] == field[i][j] || field[i][j + 1] == field[i][j]) {
                    sumPoss = true;
                    break;
                }
            }

            if (sumPoss == true) {
                break;
            }
        }

    if (emptyBlock || sumPoss) {
        return true;
    } else {
        return false;
    }
}

void keyPress() {
    kInput = _getch();

    //if(kInput == 119) dir = UP;
    //if(kInput == 115) dir = DOWN;
    //if(kInput == 97) dir = LEFT;
    //if(kInput == 100) dir = RIGHT;

    if (kInput == 72) dir = UP;
    if (kInput == 80) dir = DOWN;
    if (kInput == 75) dir = LEFT;
    if (kInput == 77) dir = RIGHT;
}

void blockMove() {
    switch (dir) {
    case UP:
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {

                if (field[j][i] == 0) {
                    for (int k = j + 1; k < 4; k++) {
                        if (field[k][i] != 0) {
                            field[j][i] = field[k][i];
                            field[k][i] = 0;
                            break;
                        }
                    }
                }
            }
        }
        break;
    case DOWN:
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--) {

                if (field[j][i] == 0) {
                    for (int k = j - 1; k >= 0; k--) {
                        if (field[k][i] != 0) {
                            field[j][i] = field[k][i];
                            field[k][i] = 0;
                            break;
                        }
                    }
                }
            }
        }
        break;
    case LEFT:
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {

                if (field[i][j] == 0) {
                    for (int k = j + 1; k < 4; k++) {
                        if (field[i][k] != 0) {
                            field[i][j] = field[i][k];
                            field[i][k] = 0;
                            break;
                        }
                    }
                }
            }
        }
        break;
    case RIGHT:
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j >= 0; j--) {

                if (field[i][j] == 0) {
                    for (int k = j - 1; k >= 0; k--) {
                        if (field[i][k]) {
                            field[i][j] = field[i][k];
                            field[i][k] = 0;
                            break;
                        }
                    }
                }
            }
        }
        break;
    }
}

void sumSystem() {
    switch (dir) {
    case UP:
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[j][i] != 0 && field[j][i] == field[j + 1][i]) {
                    field[j][i] += field[j + 1][i];
                    field[j + 1][i] = 0;
                }
            }
        }
        break;
    case DOWN:
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j > 0; j--) {
                if (field[j][i] != 0 && field[j][i] == field[j - 1][i]) {
                    field[j][i] += field[j - 1][i];
                    field[j - 1][i] = 0;
                }
            }
        }
        break;
    case LEFT:
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                if (field[i][j] != 0 && field[i][j] == field[i][j + 1]) {
                    field[i][j] += field[i][j + 1];
                    field[i][j + 1] = 0;
                }
            }
        }
        break;
    case RIGHT:
        for (int i = 0; i < 4; i++) {
            for (int j = 3; j > 0; j--) {
                if (field[i][j] != 0 && field[i][j] == field[i][j - 1]) {
                    field[i][j] += field[i][j - 1];
                    field[i][j - 1] = 0;
                }
            }
        }
        break;
    }
}

void logicFlow() {
    keyPress();

    //if(kInput == 119 || kInput == 115 || kInput == 97 || kInput == 100) {
    if (kInput == 72 || kInput == 80 || kInput == 75 || kInput == 77) {
        backUp();
        blockMove();
        sumSystem();
        blockMove();
        if (checkBlockMove()) {
            generateNum();
        }
    }

    if (kInput == 117) {
        undo();
    }
}

int main() {
    homeDisplay();
    _getch();

    srand(time(NULL));
    setup();

    while (true) {
        logicFlow();
        display(field);

        if (checkPossMove())
            gameOver = true;

        if (gameOver)
            cout << endl << "true";
        else
            cout << endl << "false";
    }

    return 0;
}

