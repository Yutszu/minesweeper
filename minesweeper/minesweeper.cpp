#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <conio.h>

using namespace std;

const int inf = 1007;

int width = inf;
int height = inf;
int mine = 10;
int mine2 = mine;
bool ending = false;
bool won = false;
bool unflaggin = false;
bool flaggin = false;
bool rainbow = false;

const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[8] = {-1, 0, 1, -1 , 1 , -1, 0, 1};

int x = height/2;
int y = width/2;

vector<vector<bool>> is_mine(height, vector<bool>(width, false));
vector<vector<char>> board(height, vector<char>(width));
vector<vector<char>> revealed(height, vector<char>(width, '.'));
vector<vector<int>> miness(inf, vector<int>(3, 0));


bool inside(int x, int y)
{
    if (x < 0 || x >= height || y < 0 || y >= width)return false;
    return true;
}

int check(int x, int y)
{
    int mines = 0;
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!inside(nx, ny))continue;
        if (is_mine[nx][ny])mines++;
    }
    return mines;
}

void count()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            revealed[i][j] = '.';
            if (!is_mine[i][j])
            {
                int mines = check(i, j);
                if (mines == 0)board[i][j] = '*';
                else board[i][j] = char(mines) + '0';
            }
            else board[i][j] = 'o';
        }
    }
}


void create()
{
    mine--;
    cout << "[";
    while (mine >= 0)
    {
        srand((unsigned)time(NULL)*234456);
        int x = rand();
        srand((unsigned)time(NULL)*45612347);
        int y = rand();
        x %= height;
        y %= width;
        if (!is_mine[x][y])
        {
            cout << "=";
            is_mine[x][y] = true;
            miness[mine][0] = x;
            miness[mine][1] = y;
            mine--;
        }
    }
    cout << "]\n";
}

void victory()
{
    ending = true;
    won = true;
}

void found_mines()
{
    int sum = 0;
    for (int i = 0; i < miness.size(); i++)
    {
        sum += miness[i][2];
    }
    if (sum == mine2)victory();
}

void print()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (ending)
            {
                if (rainbow)
                {
                    srand((unsigned)time(NULL) * 456712);
                    int s = rand();
                    s %= 16;
                    if (s == 0)s += 6;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s);
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                    if (board[i][j] == 'o' && !won)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    else if (board[i][j] == 'o' && won)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                }
                cout << board[i][j] << ' ';
            }
            else
            {
                if (rainbow)
                {
                    srand((unsigned)time(NULL) * 456743);
                    int s = rand();
                    s %= 16;
                    if (s == 0)s += 6;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s);
                }
                else
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                    if (revealed[i][j] == 'F')SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                    else if (i == x && j == y)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    else if (revealed[i][j] == '.')SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                }
                cout << revealed[i][j] << ' ';
            }
        }
        cout << "\n";
    }
    if (won)
    {
        if (rainbow)
        {
            srand((unsigned)time(NULL) * 45675412);
            int s = rand();
            s %= 16;
            if (s == 0)s += 6;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s);
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
        cout << "\n CONGRATULATIONS! \n YOU WON \n";
    }
    else if (!won && ending)
    {
        if (rainbow)
        {
            srand((unsigned)time(NULL) * 4567213);
            int s = rand();
            s %= 16;
            if (s == 0)s += 6;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s);
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "\n BOOM! \n YOU LOST \n";
    }
    else
    {
        srand((unsigned)time(NULL) * 456765);
        int s = rand();
        s %= 16;
        if (s == 0)s += 6;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s);
        cout << "\n movement: W A S D\n to flag the box: F\n to unflag the box: U\n to reveal the box: R\n";
    }

    if (unflaggin)
    {
        if (rainbow)
        {
            srand((unsigned)time(NULL) * 436137);
            int s = rand();
            s %= 16;
            if (s == 0)s += 6;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s);
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        unflaggin = false;
        cout << "You can't unflag box without a flag!";
    }
    if (flaggin)
    {
        if (rainbow)
        {
            srand((unsigned)time(NULL) * 456227);
            int s = rand();
            s %= 16;
            if (s == 0)s += 6;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), s);
        }
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        flaggin = false;
        cout << "You can't flag box you have already revealed!";
    }
}

void flood(int x, int y)
{
    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!inside(nx, ny) || revealed[nx][ny] != '.')continue;
        if (!is_mine[nx][ny])
        {
            revealed[nx][ny] = board[nx][ny];
            if (board[nx][ny] == '*')flood(nx, ny);
        }
    }
}

void lose()
{
    ending = true;
}

void flag()
{
    if (revealed[x][y] == '.')
    {
        revealed[x][y] = 'F';
        if (is_mine[x][y])
        {
            for (int i = 0; i < miness.size(); i++)
            {
                if (miness[i][0] == x && miness[i][1] == y)
                {
                    miness[i][2] = 1;
                    break;
                }
            }
        }
    }
    else flaggin = true;
}

void unflag()
{
    if (revealed[x][y] == 'F')
    {
        revealed[x][y] = '.';
        if (is_mine[x][y])
        {
            for (int i = 0; i < miness.size(); i++)
            {
                if (miness[i][0] == x && miness[i][1] == y)
                {
                    miness[i][2] = 0;
                    break;
                }
            }
        }
    }
    else
    {
        unflaggin = true;
    }
}

void reveal(int x, int y)
{
    revealed[x][y] = board[x][y];
    if (board[x][y] == '*')flood(x, y);
    if (board[x][y] == 'o')lose();
    system("CLS");
    print();
}

void Go_up()
{
    if (inside(x - 1, y))
    {
        x--;
    }
}

void Go_left()
{
    if (inside(x, y - 1))
    {
        y--;
    }
}

void Go_down()
{
    if (inside(x + 1, y))
    {
        x++;
    }
}

void Go_right()
{
    if (inside(x, y + 1))
    {
        y++;
    }
}

int main()
{
    //is_mine[0][0] = true;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "Enter the Height of the board:\n";
    cin >> height;
    cout << "Enter the Width of the board:\n";
    cin >> width;
    cout << "Enter Number of mines on the board:\n";
    cin >> mine;
    mine2 = mine;

    is_mine.resize(height);
    revealed.resize(height);
    board.resize(height);
    miness.resize(mine);
    for (int i = 0; i < height; i++)
    {
        is_mine[i].resize(width);
        revealed[i].resize(width);
        board[i].resize(width);

    }

    x = height / 2;
    y = width / 2;


    create();
    count();

    while(!ending)
    {
        system("CLS");
        found_mines();
        print();
        char key = _getch();
        if (key == 'w')Go_up();
        else if (key == 'a')Go_left();
        else if (key == 's')Go_down();
        else if (key == 'd')Go_right();
        else if (key == 'r')reveal(x, y);
        else if (key == 'f')flag();
        else if (key == 'u')unflag();
        else if (key == 'p')rainbow = true;
    }
}