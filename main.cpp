#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <vector>
#include <windows.h>

using namespace std;

class ConsoleText {
public:
    string text;
    int centerX;
    int centerY;
    vector<pair<int, int>> letterPositions;
    vector<int> letterColors;

    ConsoleText(string txt, int cx, int cy)
        : text(txt), centerX(cx), centerY(cy) {
        srand(static_cast<unsigned int>(time(0)));
        initialize();
    }

    void SetConsoleColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void SetConsoleCursorPosition(int x, int y) {
        COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        ::SetConsoleCursorPosition(hConsole, coord);
    }

    int GetRandomColor() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 15);
        return dis(gen);
    }

    void initialize() {
        for (size_t i = 0; i < text.length(); i++) {
            int offsetY = rand() % 7 + 1;
            letterPositions.push_back({ centerX + static_cast<int>(i), centerY - offsetY });
            letterColors.push_back(GetRandomColor());
        }
    }

    void render() {
        system("cls");
        for (size_t j = 0; j < text.length(); j++) {
            SetConsoleColor(letterColors[j]);
            SetConsoleCursorPosition(letterPositions[j].first, letterPositions[j].second);
            cout << text[j];
        }
    }

    void updatePositions() {
        for (size_t j = 0; j < text.length(); j++) {
            if (letterPositions[j].second < centerY) {
                letterPositions[j].second++;
            }
            else if (letterPositions[j].second > centerY) {
                letterPositions[j].second--;
            }
        }
    }

    void displayFinal() {
        system("cls");
        for (size_t j = 0; j < text.length(); j++) {
            SetConsoleColor(letterColors[j]);
            SetConsoleCursorPosition(centerX + static_cast<int>(j), centerY);
            cout << text[j];
        }
        SetConsoleColor(7);
    }
};

int main() {
    ConsoleText text("Hello World!", 40, 12);

    for (int i = 0; i < 20; i++) {
        text.render();
        this_thread::sleep_for(chrono::milliseconds(100));

        text.updatePositions();
    }

    text.displayFinal();

    return 0;
}
