#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <string.h>


#define MAX_BOOKS 1000
#define FILENAME "books.txt"
#define BUFSIZE 128

struct Book {
    char title[100];
    char author[50];
    int year;
    float grade;
};

struct Book *books;
int bookNumber = 0;

void saveNewBook(const char *filename, struct Book book) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка сохранения в файл!");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);

    file = fopen(filename, "a");
    if (size == 0) {
        fprintf(file, "%s,%s,%d,%f", book.title, book.author, book.year, book.grade);
    } else {
        fprintf(file, "\n%s,%s,%d,%f", book.title, book.author, book.year, book.grade);
    }
    fclose(file);
}

void loadBooks(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        return;
    }

    while (fscanf(file, " %99[^,],%49[^,],%d,%f",
                  books[bookNumber].title,
                  books[bookNumber].author,
                  &books[bookNumber].year,
                  &books[bookNumber].grade) == 4) {
        bookNumber++;
    }
    fclose(file);
}

struct Book addBook() {
    struct Book book;
    printf("Введите название книги:\n");
    system("chcp 1251 >nul");
    fgets(book.title, BUFSIZE, stdin);
    system("chcp 65001 >nul");
    book.title[strlen(book.title) - 1] = '\0';

    printf("Введите автора книги:\n");
    system("chcp 1251 >nul");
    fgets(book.author, BUFSIZE, stdin);
    system("chcp 65001 >nul");
    book.author[strlen(book.author) - 1] = '\0';

    printf("Введите год прочтение книги:\n");
    char year[BUFSIZE];
    char *endptr;
    fgets(year, BUFSIZE, stdin);
    long year_l = strtol(year, &endptr, 10);
    while (endptr == year || year_l > 9999) {
        printf("Введено некорректное значение!\nПовторите ввод:\n");
        fgets(year, BUFSIZE, stdin);
        year_l = strtol(year, &endptr, 10);
    }
    book.year = year_l;

    printf("Введите вашу оценку книги (от 0 до 10):\n");
    char grade[BUFSIZE];
    endptr = grade;
    float grade_f = 0;
    while (endptr == grade) {
        fgets(grade, BUFSIZE, stdin);
        grade_f = strtof(grade, &endptr);
        if (endptr == grade) {
            printf("Введено некорректное значение!\nПовторите ввод: ");
        }
        if (endptr != grade) {
            if (0 > grade_f || 10 < grade_f) {
                endptr = grade;
                printf("Введено некорректное значение!\nПовторите ввод: ");
            }
        }
    }
    book.grade = grade_f;

    books[bookNumber++] = book;

    saveNewBook(FILENAME, book);

    printf("Успешно добавлено!");

    return book;
}

void showStats() {
    if (bookNumber == 0) {
        printf("На данный момент нет статистики :(");
        return;
    }
    printf("\n -------- Статистика -------- \n");
    printf("Общее кол-во книг: %d\n", bookNumber);

    float sum_g = 0;
    float max_g = 0;
    char title[BUFSIZE];
    for (int i = 0; i < bookNumber; i++) {
        if (books[i].grade > max_g) {
            max_g = books[i].grade;
            strcpy(title, books[i].title);
        }
        sum_g += books[i].grade;
    }
    printf("Средняя оценка книг: %.3f\n", sum_g / bookNumber);
    printf("Высшая оценка у книги ");
    system("chcp 1251 >nul");
    printf("%s. ", title);
    system("chcp 65001 >nul");
    printf("Она равна %.2f\n", max_g);
}


void showMenu() {
    printf("\n=== Трекер книг ===\n");
    printf("1. Добавить книгу\n");
    printf("2. Показать все книги\n");
    printf("3. Показать статистику\n");
    printf("4. Выход\n");
    printf("Выберите пункт:\n");
}

void showAllBooks() {
    if (bookNumber == 0) {
        printf("Нет данных о расходах.\n");
        return;
    }
    printf("\n");
    for (int i = 0; i < 74; i++) {
        printf("-");
    }
    printf("\n");
    printf("| %-4s | %-33s | %-25s | %-8s | %-6s |\n",
           "№", "Название", "Автор", "Год", "Оценка");
    for (int i = 0; i < 74; i++) {
        printf("-");
    }
    printf("\n");
    for (int i = 0; i < bookNumber; i++) {
        books[i].author[strcspn(books[i].author, "\r\n")] = 0;
        books[i].title[strcspn(books[i].title, "\r\n")] = 0;
        system("chcp 1251 >nul");
        printf("| %-2d | %-25.25s | %-20.20s | %-5d | %-6.2f |\n",
               i + 1,
               books[i].title,
               books[i].author,
               books[i].year,
               books[i].grade);
        system("chcp 65001 >nul");
    }
    for (int i = 0; i < 74; i++) {
        printf("-");
    }
    printf("\n");
}

int main() {
    system("chcp 65001 >nul");
    // SetConsoleOutputCP(CP_UTF8);
    // SetConsoleCP(CP_UTF8);
    // system("chcp 1251 >nul");

    books = malloc(MAX_BOOKS * sizeof(struct Book));

    if (books == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    loadBooks(FILENAME);

    unsigned int choice;
    char str[2];

    do {
        showMenu();
        fgets(str, 3, stdin);
        choice = strtol(str, NULL, 10);

        switch (choice) {
            case 1:
                if (bookNumber < MAX_BOOKS) {
                    addBook();
                } else {
                    printf("Слишком много книг ;(");
                }
                break;
            case 2:
                showAllBooks();
                break;
            case 3:
                showStats();
                break;
            case 4:
                printf("\nВыход из программы\n");
                break;
            default:
                printf("\nНеверный выбор\n");
        }
    } while (choice != 4);

    free(books);
    return 0;
}
