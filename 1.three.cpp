#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

const int SIZE = 10;
const char EMPTY = '0';
const char SHIP = '1';
const char HIT = 'X';
const char MISS = 'O';

struct GameState {
    std::vector<std::vector<char>> player1Board;
    std::vector<std::vector<char>> player2Board;
    std::vector<std::vector<char>> player1Shots;
    std::vector<std::vector<char>> player2Shots;
    int currentPlayer;
    int turnCount;
};

void loadBoard(const std::string& filename, std::vector<std::vector<char>>& board) {
    std::ifstream file(filename);
    if (file.is_open()) {
        board.clear(); // Очистка доски перед загрузкой
        for (int i = 0; i < SIZE; ++i) {
            std::string line;
            if (std::getline(file, line)) {
                board.push_back(std::vector<char>(line.begin(), line.end()));
            } else {
                std::cerr << "Error reading line " << i + 1 << " from " << filename << std::endl;
                break; // Прерывание, если не удалось прочитать строку
            }
        }
        file.close();
    } else {
        std::cerr << "Could not open file " << filename << std::endl;
    }
}

void saveGame(const GameState& state) {
    std::ofstream file1("lastgame_player_1.cfg", std::ios::out);
    std::ofstream file2("lastgame_player_2.cfg", std::ios::out);
    std::ofstream file3("lastgame.cfg", std::ios::out);
    std::ofstream file4("lastgame_shots_player_1.cfg", std::ios::out);
    std::ofstream file5("lastgame_shots_player_2.cfg", std::ios::out);

    for (const auto& row : state.player1Board) {
        for (char cell : row) {
            file1 << cell;
        }
        file1 << std::endl;
    }

    for (const auto& row : state.player2Board) {
        for (char cell : row) {
            file2 << cell;
        }
        file2 << std::endl;
    }

    file3 << state.turnCount << std::endl;
    file3 << state.currentPlayer << std::endl;

    for (const auto& row : state.player1Shots) {
        for (char cell : row) {
            file4 << cell;
        }
        file4 << std::endl;
    }

    for (const auto& row : state.player2Shots) {
        for (char cell : row) {
            file5 << cell;
        }
        file5 << std::endl;
    }

    file1.close();
    file2.close();
    file3.close();
    file4.close();
    file5.close();
}

void printBoard(const std::vector<std::vector<char>>& board, const std::string& title) {
    std::cout << title << std::endl;
    std::cout << "  a b c d e f g h i j" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        std::cout << i + 1 << " ";
        for (char cell : board[i]) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
}

bool isValidInput(const std::string& input) {
    return (input.length() == 2 && input[0] >= 'a' && input[0] <= 'j' && input[1] >= '1' && input[1] <= '9') ||
           (input == "exit");
}

void processTurn(GameState& state) {
    std::string input;
    int x, y;
    while (true) {
        std::cout << "Player " << state.currentPlayer << ", enter your shot (e.g., a1) or 'exit': ";
        std::cin >> input;

        if (input == "exit") {
            saveGame(state);
            std::cout << "Game saved. Exiting..." << std::endl;
            return;
        }

        if (!isValidInput(input)) {
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }

        x = input[1] - '1';
        y = input[0] - 'a';

        if (state.currentPlayer == 1) {
            if (state.player2Shots[x][y] != EMPTY) {
                std::cout << "You have already shot here. Try again." << std::endl;
                continue;
            }

            if (state.player2Board[x][y] == SHIP) {
                state.player2Shots[x][y] = HIT;
                std::cout << "Hit!" << std::endl;
            } else {
                state.player2Shots[x][y] = MISS;
                std::cout << "Miss!" << std::endl;
                state.currentPlayer = 2; // Переход хода к игроку 2
            }
        } else {
            if (state.player1Shots[x][y] != EMPTY) {
                std::cout << "You have already shot here. Try again." << std::endl;
                continue;
            }

            if (state.player1Board[x][y] == SHIP) {
                state.player1Shots[x][y] = HIT;
                std::cout << "Hit!" << std::endl;
            } else {
                state.player1Shots[x][y] = MISS;
                std::cout << "Miss!" << std::endl;
                state.currentPlayer = 1; // Переход хода к игроку 1
            }
        }

        // Проверка на победу
        bool player1Won = true;
        bool player2Won = true;

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (state.player1Board[i][j] == SHIP) {
                    player1Won = false;
                }
                if (state.player2Board[i][j] == SHIP) {
                    player2Won = false;
                }
            }
        }

        if (player1Won) {
            std::cout << "Player 2 wins!" << std::endl;
            return;
        }
        if (player2Won) {
            std::cout << "Player 1 wins!" << std::endl;
            return;
        }

        // Печать текущего статуса досок
        printBoard(state.player1Shots, "Player 1 Shots");
        printBoard(state.player2Shots, "Player 2 Shots");
    }
}

void startNewGame(GameState& state) {
    state.player1Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player1Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.currentPlayer = 1;
    state.turnCount = 0;

    loadBoard("./newgame_player_1.cfg", state.player1Board);
    loadBoard("./newgame_player_2.cfg", state.player2Board);

    std::cout << "Game started!" << std::endl;
    processTurn(state);
}

void continueGame(GameState& state) {
    state.player1Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Board.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player1Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));
    state.player2Shots.resize(SIZE, std::vector<char>(SIZE, EMPTY));

    std::ifstream file1("lastgame.cfg");

    loadBoard("./lastgame_player_1.cfg", state.player1Board);
    loadBoard("./lastgame_player_2.cfg", state.player2Board);
    loadBoard("./lastgame_shots_player_1.cfg", state.player1Shots);
    loadBoard("./lastgame_shots_player_2.cfg", state.player2Shots);

    if (file1.is_open()) {
        std::string turnCountStr, currentPlayerStr;
        std::getline(file1, turnCountStr);
        std::getline(file1, currentPlayerStr);
        state.turnCount = std::stoi(turnCountStr);
        state.currentPlayer = std::stoi(currentPlayerStr);

        file1.close();

        std::cout << "Game continued!" << std::endl;
        processTurn(state);
    } else {
        std::cout << "No saved game found. Returning to main menu." << std::endl;
    }
}

int main() {
    GameState state;
    int choice;

    while (true) {
        std::cout << "1. Start New Game" << std::endl;
        std::cout << "2. Continue Game" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.get(); // символ перевода строки, получение, для дальнейшей работы cin

        switch (choice) {
            case 1:
                startNewGame(state);
                break;
            case 2:
                continueGame(state);
                break;
            case 3:
                std::cout << "Exiting the game." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}