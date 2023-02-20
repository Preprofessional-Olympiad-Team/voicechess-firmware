#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <algorithm>
#include <iterator>

using namespace std;
class Move
{
public:
    string name;
    float params;
    Move()
    {
        name = "Right";
        params = 0;
    }
    Move(int option, float param_input)
    {
        params = param_input;
        switch (option)
        {
        case 1:
            name = "Right"; //move right or left
            break;
        case 2:
            name = "Forward"; //move forward or back
            break;
        case 3:
            name = "Up"; //90 - up; 0 - down
            break;
        }
    }
    void output()
    {
        cout << name + "(" + to_string(params) + ");\n";
    }
};
list <Move> steps;
char return_mas[10][10];

struct Position
{
    int i;
    int j;
    Position()
    {
        i = 0;
        j = 0;
    }
    Position(int i_input, int j_input)
    {
        i = i_input;
        j = j_input;
    }
    Position copy()
    {
        return Position(i, j);
    }
};

void output(Position x)
{
    cout << to_string(x.i) + " " + to_string(x.j) + "\n";
}

Position white_pawn = Position (8,0);
Position black_pawn = Position (1, 0);
Position initial_white_pawn = Position(7, 1);
Position initial_black_pawn = Position(2, 1);
bool first_white_R = true;
bool first_black_R = true;
bool first_white_N = true;
bool first_black_N = true;
bool first_white_B = true;
bool first_black_B = true;
#define R_right 8
#define R_left 1
#define N_right 7
#define N_left 2
#define B_right 6
#define B_left 3
#define Q 4
#define K 5
#define black 0
#define white 9

class Figure
{
public:
    Position position_death;
    Position initial_position;
    Position actual_position;
    char name_figure;
    Figure()
    {
        position_death = Position();
        initial_position = Position();
        name_figure = '0';
    }
    Figure(char name/*K/Q/B/N/R/P*/, bool colour /*white == true*/)
    {
        if (colour) name_figure = name;
        else name_figure = tolower(name);
        if (name == 'P')
        {
            if (colour)
            {
                position_death = white_pawn.copy();
                if (white_pawn.i == 4)
                {
                    white_pawn = Position(8, 9);
                }
                else
                {
                    white_pawn = Position(white_pawn.i-1, white_pawn.j);
                }
                initial_position = Position(initial_white_pawn.i, initial_white_pawn.j);
                initial_white_pawn = Position(initial_white_pawn.i, initial_white_pawn.j+1);
            }
            else
            {
                position_death = black_pawn.copy();
                if (black_pawn.i == 4)
                {
                    black_pawn = Position(1, 9);
                }
                else
                {
                    black_pawn = Position(black_pawn.i+1, black_pawn.j);
                }
                initial_position = Position(initial_black_pawn.i, initial_black_pawn.j);
                initial_black_pawn = Position(initial_black_pawn.i, initial_black_pawn.j+1);
            }
        }
        else if (name == 'K')
        {
            if (colour)
            {
                position_death = Position(white, K);
                initial_position = Position(white-1, K);
            }
            else
            {
                position_death = Position(black, K);
                initial_position = Position(black + 1, K);
            }
        }
        else if (name == 'Q')
        {
            if (colour)
            {
                position_death = Position(white, Q);
                initial_position = Position(white - 1, Q);
            }
            else
            {
                position_death = Position(black, Q);
                initial_position = Position(black + 1, Q);
            }
        }
        else if (name == 'R')
        {
            if (colour)
            {
                if (first_white_R)
                {
                    position_death = Position(white, R_left);
                    first_white_R = false;
                    initial_position = Position(white - 1, R_left);
                }
                else
                {
                    position_death = Position(white, R_right);
                    initial_position = Position(white - 1, R_right);
                }
            }
            else
            {
                if (first_black_R)
                {
                    position_death = Position(black, R_left);
                    first_black_R = false;
                    initial_position = Position(black + 1, R_left);
                }
                else
                {
                    position_death = Position(black, R_right);
                    initial_position = Position(black + 1, R_right);
                }
            }
        }
        else if (name == 'N')
        {
            if (colour)
            {
                if (first_white_N)
                {
                    position_death = Position(white, N_left);
                    first_white_N = false;
                    initial_position = Position(white - 1, N_left);
                }
                else
                {
                    position_death = Position(white, N_right);
                    initial_position = Position(white - 1, N_right);
                }
            }
            else
            {
                if (first_black_N)
                {
                    position_death = Position(black, N_left);
                    first_black_N = false;
                    initial_position = Position(black + 1, N_left);
                }
                else
                {
                    position_death = Position(black, N_right);
                    initial_position = Position(black + 1, N_right);
                }
            }
        }
        else //name == 'B'
        {
            if (colour)
            {
                if (first_white_B)
                {
                    position_death = Position(white, B_left);
                    first_white_B = false;
                    initial_position = Position(white - 1, B_left);
                }
                else
                {
                    position_death = Position(white, B_right);
                    initial_position = Position(white - 1, B_right);
                }
            }
            else
            {
                if (first_black_B)
                {
                    position_death = Position(black, B_left);
                    first_black_B = false;
                    initial_position = Position(black + 1, B_left);
                }
                else
                {
                    position_death = Position(black, B_right);
                    initial_position = Position(black + 1, B_right);
                }
            }
        }
        actual_position = initial_position.copy();
    }
};

class Point_actual
{
public:
    float i;
    float j;
    bool up; 
    Point_actual()
    {
        i = 0;
        j = 0;
        up = false;
    }
    Point_actual(int i_input, int j_input)
    {
        i = i_input;
        j = j_input;
        up = false;
    }
    void Right(float params)
    {
        if ((return_mas[(int)ceil(i)][(int)ceil(j)] == '0' && return_mas[(int)floor(i)][(int)ceil(j)] == '0'
            && return_mas[(int)ceil(i)][(int)floor(j)]=='0' && return_mas[(int)floor(i)][(int)floor(j)] == '0')||!up)
        {
            steps.push_back(Move(1, params));
            j += params;
        }
        else
        {
            float num_steps;
            for (int k = 1; k <= 4; k++)
            {
                if (k < 3) num_steps = 1;
                else num_steps = -1;
                Up(0);
                steps.push_back(Move(2-k%2, num_steps/2));
                Up(90);
                steps.push_back(Move(2-k%2, num_steps/2));
                Up(0);
                steps.push_back(Move(2-k%2, -1*num_steps));
            }
            Up(90);
            steps.push_back(Move(1, params));
            j += params;
            for (int k = 1; k <= 4; k++)
            {
                if (k < 3) num_steps = 1;
                else num_steps = -1;
                Up(0);
                steps.push_back(Move(2 - k % 2, num_steps));
                Up(90);
                steps.push_back(Move(2 - k % 2, -1* num_steps / 2));
                Up(0);
                steps.push_back(Move(2 - k % 2, -1 * num_steps / 2));
            }
        }
    }
    void Forward(float params)
    {
        if ((return_mas[(int)ceil(i)][(int)ceil(j)] == '0' && return_mas[(int)floor(i)][(int)ceil(j)] == '0'
            && return_mas[(int)ceil(i)][(int)floor(j)] == '0' && return_mas[(int)floor(i)][(int)floor(j)] == '0')||!up)
        {
            steps.push_back(Move(2, params));
            i += params;
        }
        else
        {
            int num_steps;
            for (int k = 1; k <= 4; k++)
            {
                if (k < 3) num_steps = 1;
                else num_steps = -1;
                Up(0);
                steps.push_back(Move(2 - k % 2, num_steps / 2));
                Up(90);
                steps.push_back(Move(2 - k % 2, num_steps / 2));
                Up(0);
                steps.push_back(Move(2 - k % 2, -1 * num_steps));
            }
            Up(90);
            steps.push_back(Move(2, params));
            i += params;
            for (int k = 1; k <= 4; k++)
            {
                if (k < 3) num_steps = 1;
                else num_steps = -1;
                Up(0);
                steps.push_back(Move(2 - k % 2, num_steps));
                Up(90);
                steps.push_back(Move(2 - k % 2, -1 * num_steps / 2));
                Up(0);
                steps.push_back(Move(2 - k % 2, -1 * num_steps / 2));
            }
        }
    }
    void Up(float params)
    {
        steps.push_back(Move(3, params));
        if (params == 90) up = true;
        else up = false;
    }
};

char Letters[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
char default_symbol = return_mas[0][0];
void Init_mas(Figure figure_mas[32])
{
    for (int i = 0; i < 32; i++)
    {
        return_mas[figure_mas[i].initial_position.i][figure_mas[i].initial_position.j] = figure_mas[i].name_figure;
    }
}

void Death_mas(Figure figure_mas[32])
{
    for (int i = 0; i < 32; i++)
    {
        return_mas[figure_mas[i].position_death.i][figure_mas[i].position_death.j] = figure_mas[i].name_figure;
    }
}

void Reformat_mas()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (return_mas[i][j] == default_symbol) return_mas[i][j] = '0';
        }
    }
}

void clean()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            return_mas[i][j] = '0';
        }
    }
}

void output(char return_mas[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << return_mas[i][j];
            cout << ' ';
        }
        cout << "\n";
    }
}

int iterator_helpme(char x)
{
    for (int i = 0; i < 8; i++)
    {
        if (Letters[i] == x) return i;
    }
    return NULL;
}

Position point_from_command(string command, int i_initial)
{
    int i = iterator_helpme(command[i_initial])+1;
    int j = (int)command[i_initial+1]-48;//c++ is not normal
    return Position(i, j);
}


Point_actual Fill_steps(Point_actual init_point, Position point_finish)
{
    init_point.Up(90);
    cout << to_string(init_point.i) + " " + to_string(init_point.j) + "\n";
    cout << to_string(point_finish.i) + " " + to_string(point_finish.j) + "\n";
    bool ideal_stolb = init_point.i == point_finish.i;
    bool ideal_string = init_point.j == point_finish.j;
    bool gorisont = init_point.j < point_finish.j;
    bool vertikal = init_point.i < point_finish.i;
    if (gorisont)
    {
        init_point.Right(0.5);
    }
    else init_point.Right(-0.5);
    while ((init_point.i < point_finish.i) == vertikal && !ideal_stolb)
    {
        if (vertikal) init_point.Forward(1);
        else init_point.Forward(-1);
    }
    if (vertikal)init_point.Forward(-0.5);
    else init_point.Forward(0.5); 
    while ((init_point.j < point_finish.j) == gorisont && !ideal_string)
    {
        if (gorisont) init_point.Right(1);
        else init_point.Right(-1);
    }
    if (gorisont) init_point.Right(-0.5);
    else init_point.Right(0.5);
    if (vertikal) init_point.Forward(0.5);
    else init_point.Forward(-0.5);
    init_point.Up(0);
    return init_point;
}

int main()
{
    //input: string_player; string_stockfish
    string command_player; //"E2-E4"
    string command_stockfish;
    cin >> command_player;
    cin >> command_stockfish;
    Figure main_mas[32];
    for (int i = 0; i < 32; i++)
    {
        if (i < 8) main_mas[i] = Figure('P', true);
        else if (i < 16) main_mas[i] = Figure('P', false);
        else if (i < 18) main_mas[i] = Figure('R', true);
        else if (i < 20) main_mas[i] = Figure('R', false);
        else if (i < 22) main_mas[i] = Figure('N', true);
        else if (i < 24) main_mas[i] = Figure('N', false);
        else if (i < 26) main_mas[i] = Figure('B', true);
        else if (i < 28) main_mas[i] = Figure('B', false);
        else if (i == 28) main_mas[i] = Figure('K', true);
        else if (i == 29) main_mas[i] = Figure('K', false);
        else if (i == 30) main_mas[i] = Figure('Q', true);
        else main_mas[i] = Figure('Q', false);
    }
    Position player_point_init = point_from_command(command_player, 0);
    Position player_point_finish = point_from_command(command_player, 3);
    Position stockfish_point_init = point_from_command(command_stockfish, 0);
    Position stockfish_point_finish = point_from_command(command_stockfish, 3);
    Point_actual magnetic_head = Point_actual(0,0);
    magnetic_head.Forward(player_point_init.i);
    magnetic_head.Right(player_point_init.j);
    cout << "Helpme";
    magnetic_head = Fill_steps(magnetic_head, player_point_finish);
    for(Move x: steps)
    {
        x.output();
    }
    return 0;
}
