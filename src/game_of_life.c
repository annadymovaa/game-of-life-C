#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#define WIDTH 80
#define HEIGHT 25

int **createField();
const char *choise();
void startField(int **matrix, FILE *file);
void draw(int **matrix);
int countSosedi(int **matrix, int y, int x);
void checkSosedi(int **matrix);
void freeMatrix(int **matrix);

int main() {
    int **matrix = createField();  // выделаем память под матрицу

    int game = 1;  // флаг "игра продолжается"

    const char *file = choise();  // в этой константе теперь название файла с изначальным положением игры

    FILE *map = fopen(file, "r");  // открывает файл

    startField(matrix, map);  // создание пустого поля

    fclose(map);

    initscr();
    noecho();
    curs_set(0);

    int speed = 200;

    while (game) {
        draw(matrix);  // печать матрицы
        checkSosedi(matrix);

        timeout(speed);
        int cmd = getch();

        if (cmd == ' ' || cmd == 'q' || cmd == 'Q') {
            game = 0;
        }
        if ((cmd == 'a' || cmd == 'A') && speed > 10) {
            speed -= 10;
        }
        if ((cmd == 'z' || cmd == 'Z') && speed < 1000) {
            speed += 10;
        }
    }
    endwin();

    freeMatrix(matrix);  // освобождаем память
    matrix = NULL;

    return 0;
}

int **createField() {
    int **matrix = malloc(HEIGHT * sizeof(int *) + WIDTH * HEIGHT * sizeof(int));  // выделяем память
    if (matrix != NULL) {  // если получилось выделить
        for (int i = 0; i < HEIGHT; i++) {
            matrix[i] =
                (int *)(matrix + HEIGHT) + (i * WIDTH);  // связываем "оглавление" с адресами начала строк
        }
    }
    return matrix;
}

const char *choise() {
    const char *file;
    int number;

    printf("Выберите начальное состояние (введите число от 1 до 5):\n");

    int scan = scanf("%d", &number);

    while (scan != 1 || (number < 1 || number > 5)) {
        while (getchar() != '\n');  // очищает буффер, читает все символы до конца строки
        printf("Некорректный ввод!\n");
        printf("Выберите начальное состояние (введите число от 1 до 5):\n");
        scan = scanf("%d", &number);
    }

    switch (number) {
        case 1:
            file = "map/map_1.txt";  // выбираем 1 файл
            break;
        case 2:
            file = "map/map_2.txt";
            break;
        case 3:
            file = "map/map_3.txt";
            break;
        case 4:
            file = "map/map_4.txt";
            break;
        case 5:
            file = "map/map_5.txt";
            break;
    }
    return file;
}

void startField(int **matrix, FILE *file) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            char ch = fgetc(file);

            if (ch == '\n' || ch == '\r')
                ch = fgetc(file);  // если встретили перенос строки раньше времени, пропускаем его и берем
                                   // следующий символ

            if (ch == '0') {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = 1;
            }
        }
    }
}

void draw(int **matrix) {
    move(0, 0);  // очистка терминала
    for (int i = 0; i < HEIGHT; i++) {
        if (i > 0) printw("\n");
        for (int j = 0; j < WIDTH; j++) {
            if (matrix[i][j]) {
                printw("O");
            } else {
                printw(".");
            }
        }
    }
    refresh();
}

int countSosedi(int **matrix, int y, int x) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                count += matrix[(y + i + HEIGHT) % HEIGHT][(x + j + WIDTH) % WIDTH];
            }
        }
    }
    return count;
}

void checkSosedi(int **matrix) {
    char next[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int n = countSosedi(matrix, i, j);
            if (matrix[i][j]) {
                next[i][j] = (n == 2 || n == 3);
            } else {
                next[i][j] = (n == 3);
            }
        }
    }
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = next[i][j];
        }
    }
}

void freeMatrix(int **matrix) { free(matrix); }
