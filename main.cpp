#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;

// Функция для установки цвета текста в консоли
void SetConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Функция для установки позиции курсора в консоли
void SetConsoleCursorPosition(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Функция для генерации случайного цвета
int GetRandomColor() {
    return rand() % 15 + 1;  // Случайный цвет от 1 до 15 (не включая 0)
}

// Главная функция
int main() {
    string text = "Hello World!";  // Текст, который мы будем собирать
    int centerX = 40;  // Центр экрана по X
    int centerY = 12;  // Центр экрана по Y

    srand(time(0));  // Инициализация генератора случайных чисел

    // Массив для хранения позиций букв и их цветов
    vector<pair<int, int>> letterPositions;
    vector<int> letterColors;  // Массив для хранения цветов каждой буквы

    // Разбросаем буквы и присвоим случайный цвет каждой
    for (size_t i = 0; i < text.length(); i++) {
        int offsetY = rand() % 7 + 1;  // Смещение вверх или вниз
        letterPositions.push_back({ centerX + i, centerY - offsetY });
        letterColors.push_back(GetRandomColor());  // Присваиваем случайный цвет
    }

    // Главный цикл
    for (int i = 0; i < 20; i++) {
        system("cls");  // Очистить экран

        // Вывести все буквы на экране с их сохранённым цветом
        for (size_t j = 0; j < text.length(); j++) {
            SetConsoleColor(letterColors[j]);  // Используем сохранённый цвет
            SetConsoleCursorPosition(letterPositions[j].first, letterPositions[j].second);
            cout << text[j];
        }

        this_thread::sleep_for(chrono::milliseconds(1000));  // Пауза в 1 секунду

        // Переместим буквы в центр
        for (size_t j = 0; j < text.length(); j++) {
            if (letterPositions[j].second < centerY) {
                letterPositions[j].second++;  // Двигаем буквы вниз
            }
            else if (letterPositions[j].second > centerY) {
                letterPositions[j].second--;  // Двигаем буквы вверх
            }
        }
    }

    // Вывести итоговую строку в центре
    system("cls");
    for (size_t j = 0; j < text.length(); j++) {
        SetConsoleColor(letterColors[j]);  // Используем сохранённый цвет
        SetConsoleCursorPosition(centerX + j, centerY);
        cout << text[j];
    }

    // Установим цвет по умолчанию
    SetConsoleColor(7);

    return 0;
}
