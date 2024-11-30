#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;

void SetConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetConsoleCursorPosition(int x, int y) {
    COORD coord = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int GetRandomColor() {
    return rand() % 15 + 1;
}

int main() {
    string text = "Hello World!";
    int centerX = 40;
    int centerY = 12;

    srand(time(0));

    vector<pair<int, int>> letterPositions;
    vector<int> letterColors;

    for (size_t i = 0; i < text.length(); i++) {
        int offsetY = rand() % 7 + 1;
        letterPositions.push_back({ centerX + i, centerY - offsetY });
        letterColors.push_back(GetRandomColor());
    }

    for (int i = 0; i < 20; i++) {
        system("cls");

        for (size_t j = 0; j < text.length(); j++) {
            SetConsoleColor(letterColors[j]);
            SetConsoleCursorPosition(letterPositions[j].first, letterPositions[j].second);
            cout << text[j];
        }

        this_thread::sleep_for(chrono::milliseconds(1000));

        for (size_t j = 0; j < text.length(); j++) {
            if (letterPositions[j].second < centerY) {
                letterPositions[j].second++;
            }
            else if (letterPositions[j].second > centerY) {
                letterPositions[j].second--;
            }
        }
    }

    system("cls");
    for (size_t j = 0; j < text.length(); j++) {
        SetConsoleColor(letterColors[j]);
        SetConsoleCursorPosition(centerX + j, centerY);
        cout << text[j];
    }

    SetConsoleColor(7);

    return 0;
}
