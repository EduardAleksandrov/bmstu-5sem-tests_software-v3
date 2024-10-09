/*
    с сохранением
*/
#include <iostream>
#include <vector>
#include <cstdlib> // rand
#include <ctime>
#include <set>
#include <utility> // pair
#include <tuple> // tie

#include "three.hpp"

void initializeGame(GameState& state) {
    state.player1Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player1Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.currentPlayer = 1;
    state.turnCount = 0;
}

bool isGameOver(const GameState& state, int& who, int flag) {
    int player1Ships = 0, player2Ships = 0;
    int player1ShipsOne = 0, player2ShipsTwo = 0;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (state.player1Shots[i][j] == HIT) {
                player1Ships++;
            }
            if (state.player2Shots[i][j] == HIT) {
                player2Ships++;
            }
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (state.player1Board[i][j] == SHIP) {
                player1ShipsOne++;
            }
            if (state.player2Board[i][j] == SHIP) {
                player2ShipsTwo++;
            }
        }
    }

    // std::cout << "Player 1 ships потоплено: " << player1Ships << std::endl;
    // std::cout << "Player 2 ships потоплено: " << player2Ships << std::endl;

    // Проверка на затопление половины кораблей
    if(flag == 1)
    {
        if (player1Ships >= (player1ShipsOne / 2)) {
        who = 2; // Игрок 2 выигрывает
        return true;
        }
        if (player2Ships >= (player2ShipsTwo / 2)) {
            who = 1; // Игрок 1 выигрывает
            return true;
        }
    } else {
        if (player1Ships == player1ShipsOne) {
        who = 2; // Игрок 2 выигрывает
        return true;
        }
        if (player2Ships == player2ShipsTwo) {
            who = 1; // Игрок 1 выигрывает
            return true;
        }
    }

    return false; // Игра продолжается
}

void saveGame_t(const GameState& state, std::set<std::pair<int, int>>& player1Shots, std::set<std::pair<int, int>>& player2Shots) {
    // Сохраните состояние игры в файлы
    std::ofstream file("./saved_game.cfg", std::ios::out);
    if (file.is_open()) {
        // Сохраните доски и другие параметры
        for (const auto& row : state.player1Board) {
            for (char cell : row) {
                file << cell;
            }
            file << std::endl;
        }
        for (const auto& row : state.player2Board) {
            for (char cell : row) {
                file << cell;
            }
            file << std::endl;
        }
        file << state.turnCount << std::endl;
        file << state.currentPlayer << std::endl;

        // Сохраните выстрелы игрока 1
        file << player1Shots.size() << std::endl; // Сначала сохраняем количество выстрелов
        for (const auto& shot : player1Shots) {
            file << shot.first << " " << shot.second << std::endl; // Сохраняем координаты выстрелов
        }

        // Сохраните выстрелы игрока 2
        file << player2Shots.size() << std::endl; // Сначала сохраняем количество выстрелов
        for (const auto& shot : player2Shots) {
            file << shot.first << " " << shot.second << std::endl; // Сохраняем координаты выстрелов
        }
        file.close();
    }
}

bool loadSavedGame(GameState& state, std::set<std::pair<int, int>>& player1Shots, std::set<std::pair<int, int>>& player2Shots) {
    std::ifstream file("./saved_game.cfg");
    state.player1Board.clear();
    state.player2Board.clear();
    if (!file.is_open()) {
        std::cerr << "Could not open saved game file." << std::endl;
        return false;
    }

    // Загрузка досок
    for (int i = 0; i < SIZE; ++i) {
        std::string line;
        if (std::getline(file, line)) {
            state.player1Board.push_back(std::vector<char>(line.begin(), line.end()));
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        std::string line;
        if (std::getline(file, line)) {
            state.player2Board.push_back(std::vector<char>(line.begin(), line.end()));
        }
    }

    // Загрузка параметров игры
    file >> state.turnCount;
    file >> state.currentPlayer;

    // Загрузка выстрелов игрока 1
    size_t player1ShotsSize;
    file >> player1ShotsSize; // Считываем количество выстрелов
    for (size_t i = 0; i < player1ShotsSize; ++i) {
        int x, y;
        file >> x >> y; // Считываем координаты выстрелов
        player1Shots.insert({x, y});
    }

    // Загрузка выстрелов игрока 2
    size_t player2ShotsSize;
    file >> player2ShotsSize; // Считываем количество выстрелов
    for (size_t i = 0; i < player2ShotsSize; ++i) {
        int x, y;
        file >> x >> y; // Считываем координаты выстрелов
        player2Shots.insert({x, y});
    }

    file.close();
    return true;
}

std::pair<int, int> getRandomShot(const std::set<std::pair<int, int>>& previousShots) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (previousShots.count({x, y}) > 0); // если 1, то такое значение уже есть, крутим дальше
    return {x, y};
}

void botShoot(GameState& state, std::set<std::pair<int, int>>& previousShots) {
    int x, y;
    std::tie(x, y) = getRandomShot(previousShots); // распаковка возврата функции
    previousShots.insert({x, y});

    state.turnCount++;

    if (state.currentPlayer == 1) {
        if (state.player2Board[x][y] == SHIP) {
            state.player2Shots[x][y] = HIT;
            std::cout << "Player 1 hits at (" << x << ", " << y << ")" << std::endl;
        } else {
            state.player2Shots[x][y] = MISS;
            std::cout << "Player 1 misses at (" << x << ", " << y << ")" << std::endl;
            state.currentPlayer = 2; // Передача хода
        }
    } else {
        if (state.player1Board[x][y] == SHIP) {
            state.player1Shots[x][y] = HIT;
            std::cout << "Player 2 hits at (" << x << ", " << y << ")" << std::endl;
        } else {
            state.player1Shots[x][y] = MISS;
            std::cout << "Player 2 misses at (" << x << ", " << y << ")" << std::endl;
            state.currentPlayer = 1; // Передача хода
        }
    }
}

void runIntegrationTest() {
    srand(static_cast<unsigned int>(time(0))); // Инициализация генератора случайных чисел
    GameState state;
    initializeGame(state);

    // Пример начального расположения кораблей
    loadBoard("./newgame_player_1.cfg", state.player1Board);
    loadBoard("./newgame_player_2.cfg", state.player2Board);

    std::set<std::pair<int, int>> player1Shots; // Множество ударенных точек
    std::set<std::pair<int, int>> player2Shots;

    int who = 0;
    int flag = 1; // флаг для половины и продолжения игры
    while (true) {
        botShoot(state, state.currentPlayer == 1 ? player1Shots : player2Shots);
        
        // Проверка на затопление половины кораблей
        if (who == 1 || who == 2) {
            std::cout << "Game Over! Player " << who << " wins! " << "Steps: " << state.turnCount << std::endl;

            saveGame_t(state, player1Shots, player2Shots); // Сохранение состояния игры
            break; // Завершение игры
        }
        isGameOver(state, who, flag);
    }
    
    // Проверка, нужно ли продолжить игру
    std::cout << "Продолжить игру? 1.Да, 2.Нет" << std::endl;
    int cont;
    std::cin >> cont;
    if(cont != 1) return;

    // продолжение
    int whos = 0;
    flag = 2;
    if (who == 1 || who == 2) {
        std::cout << "Continuing the saved game..." << std::endl;
        if (loadSavedGame(state, player1Shots, player2Shots)) {
            // Продолжение игры
            while (!isGameOver(state, whos, flag)) {
                botShoot(state, state.currentPlayer == 1 ? player1Shots : player2Shots);
            }
            std::cout << "Game Over! Player " << whos << " wins! " << "Steps: " << state.turnCount << std::endl;
        } else {
            std::cerr << "Failed to load the saved game." << std::endl;
        }
    }
}

int main() {
    runIntegrationTest();
    return 0;
}