#include <conio.h>

#include <iostream>

using namespace std;

int field[4][4];
int prevField[4][4];

int score = 0;

void displayField() {
    cout << "score : " << score << endl;
    cout << "---------------------" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "|";
        for (int j = 0; j < 4; j++) {
            if (!field[i][j]) {
                cout << "    |";
            } else if (field[i][j] < 10) {
                cout << "  " << field[i][j] << " |";
            } else if (field[i][j] < 100) {
                cout << " " << field[i][j] << " |";
            } else if (field[i][j] < 1000) {
                cout << " " << field[i][j] << "|";
            } else {
                cout << field[i][j] << "|";
            }
        }
        cout << endl << "---------------------" << endl;
    }
}

// void displayPrevField() {
//     cout << "---------------------" << endl;
//     for (int i = 0; i < 4; i++) {
//         cout << "|";
//         for (int j = 0; j < 4; j++) {
//             if (!prevField[i][j]) {
//                 cout << "    |";
//             } else if (prevField[i][j] < 10) {
//                 cout << "  " << prevField[i][j] << " |";
//             } else if (prevField[i][j] < 100) {
//                 cout << " " << prevField[i][j] << " |";
//             } else if (prevField[i][j] < 1000) {
//                 cout << " " << prevField[i][j] << "|";
//             } else {
//                 cout << prevField[i][j] << "|";
//             }
//         }
//         cout << endl << "---------------------" << endl;
//     }
// }

int generateRamdomNum(int number) { return (rand() % number); }

void generateNum() {
    int x = generateRamdomNum(4);
    int y = generateRamdomNum(4);

    if (field[y][x]) {
        generateNum();
        return;
    }

    int number = generateRamdomNum(5) == 0 ? 4 : 2;
    field[y][x] = number;
}

void moveNumber(char key) {
    switch (key) {
        case 'w':
        case 'W':
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (!field[j][i]) {
                        for (int k = j + 1; k < 4; k++) {
                            if (field[k][i]) {
                                field[j][i] = field[k][i];
                                field[k][i] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            break;
        case 'a':
        case 'A':
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (!field[i][j]) {
                        for (int k = j + 1; k < 4; k++) {
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
        case 's':
        case 'S':
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    if (!field[j][i]) {
                        for (int k = j - 1; k >= 0; k--) {
                            if (field[k][i]) {
                                field[j][i] = field[k][i];
                                field[k][i] = 0;
                                break;
                            }
                        }
                    }
                }
            }
            break;
        case 'd':
        case 'D':
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    if (!field[i][j]) {
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

void sumNumber(char key) {
    switch (key) {
        case 'w':
        case 'W':
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (field[j][i] && j + 1 < 4) {
                        if (field[j][i] == field[j + 1][i]) {
                            score += field[j][i] *= 2;
                            field[j + 1][i] = 0;
                        }
                    }
                }
            }
            break;
        case 'a':
        case 'A':
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (field[i][j] && j + 1 < 4) {
                        if (field[i][j] == field[i][j + 1]) {
                            score += field[i][j] *= 2;
                            field[i][j + 1] = 0;
                        }
                    }
                }
            }
            break;
        case 's':
        case 'S':
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    if (field[j][i] && j - 1 >= 0) {
                        if (field[j][i] == field[j - 1][i]) {
                            score += field[j][i] *= 2;
                            field[j - 1][i] = 0;
                        }
                    }
                }
            }
            break;
        case 'd':
        case 'D':
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    if (field[i][j] && j - 1 >= 0) {
                        if (field[i][j] == field[i][j - 1]) {
                            score += field[i][j] *= 2;
                            field[i][j - 1] = 0;
                        }
                    }
                }
            }
            break;
    }
}

bool isFull() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!field[i][j] || field[i][j] == field[i + 1][j] ||
                field[i][j] == field[i][j + 1]) {
                return false;
            }
        }
    }

    return true;
}

bool isChanged() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (field[i][j] != prevField[i][j]) {
                return true;
            }
        }
    }

    return false;
}

void updatePrevField() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            prevField[i][j] = field[i][j];
        }
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    generateNum();
    generateNum();
    updatePrevField();
    while (!isFull()) {
        system("cls");
        displayField();
        // displayPrevField();

        char key = getch();
        moveNumber(key);
        sumNumber(key);
        moveNumber(key);
        if (isChanged()) {
            generateNum();
        }

        updatePrevField();
    }
    system("sleep");

    return 0;
}
