#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>

int win();
int gameplay();
bool checkWin();
void openZeros(int xx, int yy);

const int n = 10;
const int m = 10;
int x;
int y;
int b = 10;
int pole[n + 2][m + 2];
int pole1[n + 2][m + 2];

int start() {
    std::srand(std::time(nullptr));

    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < m + 2; j++) {
            pole[i][j] = 0;
            pole1[i][j] = 0;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pole1[i][j] = -9;
        }
    }

    int mines_placed = 0;
    while (mines_placed < b) {
        int i = std::rand() % n + 1;
        int j = std::rand() % m + 1;
        if (pole[i][j] == 0) {
            pole[i][j] = -1;
            ++mines_placed;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (pole[i][j] == -1) continue;
            int cnt = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (dx == 0 && dy == 0) continue;
                    if (pole[i + dx][j + dy] == -1) cnt++;
                }
            }
            pole[i][j] = cnt;
        }
    }

    gameplay();
    return 0;
}

int gameplay() {
    while (true) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (pole1[i][j] == -9) {
                    printf("  .");
                } else if (pole1[i][j] == 0) {
                    printf("  0");
                } else {
                    printf("%3d", pole1[i][j]);
                }
            }
            printf("\n");
        }

        if (checkWin()) {
            return win();
        }

        printf("Введите через пробел номер ячейки: ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Неверный ввод\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            continue;
        }

        if (x < 1 || x > n || y < 1 || y > m) {
            printf("Координаты должны быть от 1 до %d\n", n);
            continue;
        }

        if (pole[x][y] == -1) {
            printf("Поражение\n");
            printf("Поле:\n");
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= m; j++) {
                    if (pole[i][j] == -1) {
                        printf("  *");
                    } else {
                        printf("%3d", pole[i][j]);
                    }
                }
                printf("\n");
            }
            printf("Введите 1 для перезапуска: ");
            int user_input;
            if (scanf("%d", &user_input) == 1 && user_input == 1) {
                start();
                return 0;
            }
            return 0;
        }

        if (pole[x][y] == 0) {
            openZeros(x, y);
        } else {
            pole1[x][y] = pole[x][y];
        }
    }

    return 0;
}

void openZeros(int xx, int yy) {
    if (xx < 1 || xx > n || yy < 1 || yy > m) return;
    if (pole1[xx][yy] != -9) return;
    pole1[xx][yy] = pole[xx][yy];
    if (pole[xx][yy] == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                if (dx == 0 && dy == 0) continue;
                openZeros(xx + dx, yy + dy);
            }
        }
    }
}

bool checkWin() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (pole[i][j] != -1 && pole1[i][j] == -9) return false;
        }
    }
    return true;
}

int win() {
    printf("ПЕРЕМОГА\n");
    printf("Введите 1 для перезапуска: ");
    int user_input;
    if (scanf("%d", &user_input) == 1 && user_input == 1) {
        start();
    }
    return 0;
}

int main() {
    start();
}
