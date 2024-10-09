#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <utility>
#include <tuple>

#include "three.hpp"

void initializeGame(GameState& state) {
    state.player1Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player1Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.currentPlayer = 1;
}

bool isGameOver(const GameState& state, int& who) {
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
    if(player2Ships == player2ShipsTwo) who = 1;
    else who = 2;
    std::cout << "Player 1 ships remaining: " << player1Ships << std::endl;
    std::cout << "Player 2 ships remaining: " << player2Ships << std::endl;

    return player1Ships == player1ShipsOne || player2Ships == player2ShipsTwo;
}

std::pair<int, int> getRandomShot(const std::set<std::pair<int, int>>& previousShots) {
    int x, y;
    do {
        x = rand() % SIZE;
        y = rand() % SIZE;
    } while (previousShots.count({x, y}) > 0);
    return {x, y};
}

void botShoot(GameState& state, std::set<std::pair<int, int>>& previousShots) {
    int x, y;
    std::tie(x, y) = getRandomShot(previousShots);
    previousShots.insert({x, y});

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

    std::set<std::pair<int, int>> player1Shots;
    std::set<std::pair<int, int>> player2Shots;

    int who;
    while (!isGameOver(state, who)) {
        botShoot(state, state.currentPlayer == 1 ? player1Shots : player2Shots);
    }

    // std::cout << "Game Over!" << std::endl;
    // if (state.player1Shots[0][0] == HIT) {
    //     std::cout << "Player 2 wins!" << std::endl;
    // } else {
    //     std::cout << "Player 1 wins!" << std::endl;
    // }
    std::cout << "Game Over!" << std::endl;
    isGameOver(state, who);
    if (who == 1) {
        std::cout << "Player 1 wins!" << std::endl;
    } else {
        std::cout << "Player 2 wins!" << std::endl;
    }
}

int main() {
    runIntegrationTest();
    return 0;
}