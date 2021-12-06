#include "time.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <list>
using namespace std;


static const int INF = 100;
static enum { PLAYING, OWIN, XWIN, DRAW } state;
typedef struct {
    char symbol;
    int move;
    bool selected;
    bool win;
}
player;

void display_board();       // отображение
void get_move();                // поиск(получение) хода
void update_game();             // следующий шаг игры
bool free_square();     // проверка пустоты ячейки
void update_board();            // обновление позиций на доске
void verify_move();             // проверка валидности хода(0-8 и не занята ячейка)
void generate_moves(char _board[9], list<int> &move_list); // генерация всех ходов для minmax
void check_game_state(char board[9]);              // проверка состояния игры

int evaluate_position(char _board[9], player _player); // оценка положения
int MiniMax(char _board[9], player _player);
int MinMove(char _board[9], player _player);
int MaxMove(char _board[9], player _player);

static player player1, player2, cplayer;
static char board[9] = { 0 }; // обозначение доски для игры
static char symbol; // символ для текущего игрока
static int nmove;  // последний шаг сделанный действующим игроком

int q = 0;

int main() {
    srand((unsigned)time(NULL));

    player1.symbol = 'X';
    player2.symbol = 'O';
    state = PLAYING;

    while (state == PLAYING) {
        get_move();
        update_game();
    }

    if (state == XWIN || state == OWIN || state == DRAW) {
        if (state == XWIN)   player1.win = 1;
        else if (state == OWIN)  player2.win = 1;

        if (player1.win)                 std::cout << "Player has won the game!" << std::endl;
        else if (player2.win)                std::cout << "Computer has won the game!" << std::endl;
        else if (player1.win == 0 && player2.win == 0)   std::cout << "No winner, this game is a draw." << std::endl;
    }
    system("PAUSE");

    return 0;
}

void get_move()  {
    player1.move = -1;
    player2.move = -1;
    std::cin.sync(); //очищение буфера стандартного ввода
    if (player1.selected) {
        std::cout << std::endl;
        std::cout << " Please Enter Your Move (1-9): ";
        std::cin >> player1.move;
        nmove = player1.move;
        symbol = player1.symbol;
        cplayer = player1;
        player1.selected = 0;
        player2.selected = 1;
    }
    else if (player2.selected) {
        player2.move = MiniMax(board, player2);
        nmove = player2.move;
        symbol = player2.symbol;
        cplayer = player2;
        player1.selected = 1;
        player2.selected = 0;
        state = PLAYING;
    }

    verify_move();
    if ((state == XWIN || state == OWIN || state == DRAW)) return;
}

void update_board() {
    if (state == PLAYING) {
        if (player1.move != -1 && player2.move == -1)    board[player1.move - 1] = player1.symbol;
        else if (player2.move != -1)             board[player2.move - 1] = player2.symbol;
    }
}

void update_game() {
    update_board();
    display_board();
    check_game_state(board);
}

bool free_square()  {
    if (player1.move != -1 && player2.move == -1)
        return board[player1.move - 1] == 0;
    else if (player2.move != -1)
        return board[player2.move - 1] == 0;
    return 0;
}

void display_board()  {
    std::cout << std::endl;
    std::cout << " " << board[0] << " | " << board[1] << " | " << board[2] << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << " " << board[3] << " | " << board[4] << " | " << board[5] << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << " " << board[6] << " | " << board[7] << " | " << board[8] << std::endl;
    std::cout << std::endl;
}

void verify_move()  {
    if (!(nmove > 0 && nmove < 10) || !free_square()) {
        std::cout << "Invalid Move." << std::endl;
        player1.selected = 1;
        player2.selected = 0;
        get_move();
    }
}

void check_game_state(char board[9]) {
    if ((board[0] == symbol && board[1] == symbol && board[2] == symbol) ||
        (board[3] == symbol && board[4] == symbol && board[5] == symbol) ||
        (board[6] == symbol && board[7] == symbol && board[8] == symbol) ||
        (board[0] == symbol && board[3] == symbol && board[6] == symbol) ||
        (board[1] == symbol && board[4] == symbol && board[7] == symbol) ||
        (board[2] == symbol && board[5] == symbol && board[8] == symbol) ||
        (board[0] == symbol && board[4] == symbol && board[8] == symbol) ||
        (board[2] == symbol && board[4] == symbol && board[6] == symbol)) {
        if (symbol == 'X')   state = XWIN;
        else if (symbol == 'O')  state = OWIN;
    }
    else {
        state = DRAW;
        for (int i = 0; i < 9; i++) {
            if (board[i] == 0) {
                state = PLAYING;
                break;
            }
        }
    }
}

void generate_moves(char _board[9], std::list<int> &move_list) {
    for (int i = 0; i < 9; i++) if (_board[i] == 0) move_list.push_back(i);
}

int evaluate_position(char _board[9], player _player)  {
    check_game_state(_board);
    if ((state == XWIN || state == OWIN || state == DRAW)) {
        if ((state == XWIN && _player.symbol == 'X') || (state == OWIN && _player.symbol == 'O')) return +INF;
        else if ((state == XWIN && _player.symbol == 'O') || (state == OWIN && _player.symbol == 'X')) return -INF;
        else if (state == DRAW) return 0;
    }
    return -1;
}

int MiniMax(char _board[9], player _player)  {
    int best_val = -INF, index = 0;
    std::list<int> move_list;
    char best_moves[9] = { 0 };

    generate_moves(_board, move_list); // генерить все ходы
    while (!move_list.empty()) { // по всем
        _board[move_list.front()] = _player.symbol; // заполнение ячейки символом игрока
        symbol = _player.symbol;


        int val = MinMove(_board, _player); // поиск MinMove
        if (val > best_val) { // выбор наибольшего
            best_val = val;
            index = 0;
            best_moves[index] = 1 + move_list.front();
        }
        else if (val == best_val)
            best_moves[++index] = 1 + move_list.front(); // если несколько наибольших - тоже заносим

        printf("\nminimax: %3d(%1d) ", 1 + move_list.front(), val);
        _board[move_list.front()] = 0; // отбрасываем ход, идем далее по циклу
        move_list.pop_front();
    }
    if (index > 0) index = rand() % index; // выбираем случайный из нескольких ходов
    printf("\nminimax best: %3d(%1d) ", best_moves[index], best_val);
    printf("Steps counted: %d", q);
    q = 0;
    return best_moves[index];
}

int MinMove(char _board[9], player _player)  {
    int pos_value = evaluate_position(_board, _player); // проверить состояние игры для текущего игрока
    if (pos_value != -1) return pos_value;
    q++;
    int best_val = +INF;
    std::list<int> move_list;
    generate_moves(_board, move_list); // генерить все ходы
    while (!move_list.empty()) { // по всем
        _player.symbol == 'X' ? symbol = 'O' : symbol = 'X'; // расчет для противника
        _board[move_list.front()] = symbol; // front - ссылка на первый элемент, заполнение ячейки символом
        int val = MaxMove(_board, _player); // подсчет MaxMove
        if (val < best_val) {
            best_val = val; // выбрать с наименьшим
        }
        _board[move_list.front()] = 0;
        move_list.pop_front();
    }
    return best_val;
}

int MaxMove(char _board[9], player _player) {
    int pos_value = evaluate_position(_board, _player);
    if (pos_value != -1) return pos_value;
    q++;
    int best_val = -INF;
    std::list<int> move_list;
    generate_moves(_board, move_list);
    while (!move_list.empty()) {
        _player.symbol == 'X' ? symbol = 'X' : symbol = 'O'; // расчет для себя
        _board[move_list.front()] = symbol;
        int val = MinMove(_board, _player);
        if (val > best_val) {
            best_val = val;
        }
        _board[move_list.front()] = 0;
        move_list.pop_front();
    }
    return best_val;
}
