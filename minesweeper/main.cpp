

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include <random>
#include <ctime>
#include <queue>

using namespace std;

mt19937 random_mt(time(0));

int Random(int min, int max)
{
    uniform_int_distribution<int> dist(min, max);
    return dist(random_mt);
}

int GetNumber(int y, int x, vector<vector<int>> mineboard)
{
    int num = 0;
    int maxX = mineboard[0].size();
    int maxY = mineboard.size();
    if ((x > 0 && y > 0) && mineboard[y - 1][x - 1] == 1)
    {
        ++num;
    }
    if ((x > 0) && mineboard[y][x - 1] == 1)
    {
        ++num;
    }
    if ((x > 0 && y < maxY - 1) && mineboard[y + 1][x - 1] == 1)
    {
        ++num;
    }
    if (y < maxY - 1 && mineboard[y + 1][x] == 1)
    {
        ++num;
    }
    if ((x < maxX - 1 && y < maxY - 1) && mineboard[y + 1][x + 1] == 1)
    {
        ++num;
    }
    if ((x < maxX - 1) && mineboard[y][x + 1] == 1)
    {
        ++num;
    }
    if ((x < maxX - 1 && y > 0) && mineboard[y - 1][x + 1] == 1)
    {
        ++num;
    }
    if (y > 0 && mineboard[y - 1][x] == 1)
    {
        ++num;
    }
    return num;
}

int main()
{
    ifstream reader("boards/config.cfg");
    int col;
    int row;
    int m;
    bool debug = false;
    bool win = false;
    bool lose = false;
    reader >> col;
    reader >> row;
    reader >> m;
    int revealed = 0;
    int count = m;
    int tiles = col * row;
    vector<vector<int>> nums;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < col; ++j)
        {
            temp.push_back(0);
        }
        nums.push_back(temp);
    }
    reader.close();
    reader.open("boards/testboard1.brd");
    vector<vector<int>> test1board;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        string line;
        getline(reader, line);
        for (int j = 0; j < col; ++j)
        {
            int n = std::stoi(line.substr(j, 1));
            temp.push_back(n);
        }
        test1board.push_back(temp);
    }
    reader.close();
    reader.open("boards/testboard2.brd");
    vector<vector<int>> test2board;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        string line;
        getline(reader, line);
        for (int j = 0; j < col; ++j)
        {
            int n = std::stoi(line.substr(j, 1));
            temp.push_back(n);
        }
        test2board.push_back(temp);
    }
    reader.close();
    reader.open("boards/testboard3.brd");
    vector<vector<int>> test3board;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        string line;
        getline(reader, line);
        for (int j = 0; j < col; ++j)
        {
            int n = std::stoi(line.substr(j, 1));
            temp.push_back(n);
        }
        test3board.push_back(temp);
    }
    reader.close();
    vector<vector<sf::Sprite>> tilehsprite;
    vector<vector<sf::Sprite>> tilersprite;
    vector<vector<int>> flagboard;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < col; ++j)
        {
            temp.push_back(0);
        }
        flagboard.push_back(temp);
    }
    vector<sf::Sprite> flags;
    vector<vector<int>> mineboard;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < col; ++j)
        {
            temp.push_back(0);
        }
        mineboard.push_back(temp);
    }
    vector<sf::Sprite> mines;
    vector<sf::Sprite> fmines;
    vector<vector<int>> numberboard;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < col; ++j)
        {
            temp.push_back(0);
        }
        numberboard.push_back(temp);
    }
    vector<sf::Sprite> numbers;
    vector<vector<int>> tilerboard;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < col; ++j)
        {
            temp.push_back(0);
        }
        tilerboard.push_back(temp);
    }
    vector<sf::Sprite> tilers;
    vector<vector<int>> visited;
    for (int i = 0; i < row; ++i)
    {
        vector<int> temp;
        for (int j = 0; j < col; ++j)
        {
            temp.push_back(0);
        }
        visited.push_back(temp);
    }
    sf::RenderWindow window;
    map<string, sf::Texture> textures;
    map<int, sf::Texture> digit;
    map<int, sf::Texture> number;
    sf::Texture debugger;
    debugger.loadFromFile("images/debug.png");
    textures.emplace("debug", debugger);
    sf::Texture d0;
    d0.loadFromFile("images/digits.png", sf::IntRect(0, 0, 21, 32));
    digit.emplace(0, d0);
    sf::Texture d1;
    d1.loadFromFile("images/digits.png", sf::IntRect(21, 0, 21, 32));
    digit.emplace(1, d1);
    sf::Texture d2;
    d2.loadFromFile("images/digits.png", sf::IntRect(42, 0, 21, 32));
    digit.emplace(2, d2);
    sf::Texture d3;
    d3.loadFromFile("images/digits.png", sf::IntRect(63, 0, 21, 32));
    digit.emplace(3, d3);
    sf::Texture d4;
    d4.loadFromFile("images/digits.png", sf::IntRect(84, 0, 21, 32));
    digit.emplace(4, d4);
    sf::Texture d5;
    d5.loadFromFile("images/digits.png", sf::IntRect(105, 0, 21, 32));
    digit.emplace(5, d5);
    sf::Texture d6;
    d6.loadFromFile("images/digits.png", sf::IntRect(126, 0, 21, 32));
    digit.emplace(6, d6);
    sf::Texture d7;
    d7.loadFromFile("images/digits.png", sf::IntRect(147, 0, 21, 32));
    digit.emplace(7, d7);
    sf::Texture d8;
    d8.loadFromFile("images/digits.png", sf::IntRect(168, 0, 21, 32));
    digit.emplace(8, d8);
    sf::Texture d9;
    d9.loadFromFile("images/digits.png", sf::IntRect(189, 0, 21, 32));
    digit.emplace(9, d9);
    sf::Texture negative;
    negative.loadFromFile("images/digits.png", sf::IntRect(210, 0, 21, 32));
    textures.emplace("neg", negative);
    sf::Texture face_happy;
    face_happy.loadFromFile("images/face_happy.png");
    textures.emplace("faceh", face_happy);
    sf::Texture face_lose;
    face_lose.loadFromFile("images/face_lose.png");
    textures.emplace("facel", face_lose);
    sf::Texture face_win;
    face_win.loadFromFile("images/face_win.png");
    textures.emplace("facew", face_win);
    sf::Texture flag;
    flag.loadFromFile("images/flag.png");
    textures.emplace("flag", flag);
    sf::Texture mine;
    mine.loadFromFile("images/mine.png");
    textures.emplace("mine", mine);
    sf::Texture number_1;
    number_1.loadFromFile("images/number_1.png");
    number.emplace(1, number_1);
    sf::Texture number_2;
    number_2.loadFromFile("images/number_2.png");
    number.emplace(2, number_2);
    sf::Texture number_3;
    number_3.loadFromFile("images/number_3.png");
    number.emplace(3, number_3);
    sf::Texture number_4;
    number_4.loadFromFile("images/number_4.png");
    number.emplace(4, number_4);
    sf::Texture number_5;
    number_5.loadFromFile("images/number_5.png");
    number.emplace(5, number_5);
    sf::Texture number_6;
    number_6.loadFromFile("images/number_6.png");
    number.emplace(6, number_6);
    sf::Texture number_7;
    number_7.loadFromFile("images/number_7.png");
    number.emplace(7, number_7);
    sf::Texture number_8;
    number_8.loadFromFile("images/number_8.png");
    number.emplace(8, number_8);
    sf::Texture test_1;
    test_1.loadFromFile("images/test_1.png");
    textures.emplace("t1", test_1);
    sf::Texture test_2;
    test_2.loadFromFile("images/test_2.png");
    textures.emplace("t2", test_2);
    sf::Texture test_3;
    test_3.loadFromFile("images/test_3.png");
    textures.emplace("t3", test_3);
    sf::Texture tile_hidden;
    tile_hidden.loadFromFile("images/tile_hidden.png");
    textures.emplace("tileh", tile_hidden);
    sf::Texture tile_revealed;
    tile_revealed.loadFromFile("images/tile_revealed.png");
    textures.emplace("tiler", tile_revealed);
    for (int i = 0; i < m; ++i)
    {
        int rand1 = Random(0, row - 1);
        int rand2 = Random(0, col - 1);
        if (mineboard[rand1][rand2] == 0)
        {
            mineboard[rand1][rand2] = 1;
            sf::Sprite temp;
            temp.setTexture(mine);
            temp.setPosition(32 * rand2, 32 * rand1);
            mines.push_back(temp);
            sf::Sprite temp2;
            temp2.setTexture(flag);
            temp2.setPosition(32 * rand2, 32 * rand1);
            fmines.push_back(temp2);
        }
        else
        {
            --i;
        }
    }
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            if (mineboard[i][j] == 1)
            {
                numberboard[i][j] = 1;
            }
            else
            {
                int n = GetNumber(i, j, mineboard);
                if (n > 0)
                {
                    numberboard[i][j] = 1;
                }
                nums[i][j] = n;
            }
        }
    }
    window.create(sf::VideoMode(col * 32, 88 + row * 32), "My window");
    for (int i = 0; i < row; ++i)
    {
        vector<sf::Sprite> temp;
        for (int j = 0; j < col; ++j)
        {
            sf::Sprite s;
            s.setTexture(tile_hidden);
            s.setPosition(32 * j, 32 * i);
            temp.push_back(s);
        }
        tilehsprite.push_back(temp);
    }
    for (int i = 0; i < row; ++i)
    {
        vector<sf::Sprite> temp;
        for (int j = 0; j < col; ++j)
        {
            sf::Sprite s;
            s.setTexture(tile_revealed);
            s.setPosition(32 * j, 32 * i);
            temp.push_back(s);
        }
        tilersprite.push_back(temp);
    }
    sf::Sprite face;
    face.setTexture(face_happy);
    face.setPosition(16 * col - 32, 32 * row);
    sf::Sprite dbg;
    dbg.setTexture(debugger);
    dbg.setPosition(16 * col + 96, 32 * row);
    sf::Sprite t1;
    t1.setTexture(test_1);
    t1.setPosition(16 * col + 160, 32 * row);
    sf::Sprite t2;
    t2.setTexture(test_2);
    t2.setPosition(16 * col + 224, 32 * row);
    sf::Sprite t3;
    t3.setTexture(test_3);
    t3.setPosition(16 * col + 288, 32 * row);
    sf::Sprite neg;
    neg.setTexture(negative);
    neg.setPosition(0, 32 * row);
    sf::Sprite hund;
    hund.setTexture(digit[(count / 100)]);
    hund.setPosition(21, 32 * row);
    sf::Sprite tens;
    tens.setTexture(digit[(count % 100) / 10]);
    tens.setPosition(42, 32 * row);
    sf::Sprite ones;
    ones.setTexture(digit[count % 10]);
    ones.setPosition(63, 32 * row);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (!win && !lose)
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        if (event.mouseButton.y < 32 * row)
                        {
                            int x = event.mouseButton.x / 32;
                            int y = event.mouseButton.y / 32;
                            if (flagboard[y][x] == 0 && tilerboard[y][x] == 0)
                            {
                                flagboard[y][x] = 1;
                                sf::Sprite s;
                                s.setTexture(flag);
                                s.setPosition(x * 32, y * 32);
                                flags.push_back(s);
                                --count;
                            }
                            else if (flagboard[y][x] == 1 && tilerboard[y][x] == 0)
                            {
                                int index;
                                flagboard[y][x] = 0;
                                for (int i = 0; i < flags.size(); ++i)
                                {
                                    if (flags[i].getPosition() == sf::Vector2f(32 * x, 32 * y))
                                    {
                                        index = i;
                                    }
                                }
                                flags.erase(flags.begin() + index);
                                ++count;
                            }
                        }
                    }
                    else if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        if (event.mouseButton.y < 32 * row)
                        {
                            int x = event.mouseButton.x / 32;
                            int y = event.mouseButton.y / 32;
                            if (flagboard[y][x] == 0)
                            {
                                if (mineboard[y][x] == 1)
                                {
                                    lose = true;
                                    face.setTexture(face_lose);
                                    for (int i = 0; i < row; ++i)
                                    {
                                        for (int j = 0; j < col; ++j)
                                        {
                                            if (mineboard[i][j] == 1)
                                            {
                                                tilerboard[i][j] = 1;
                                            }
                                        }
                                    }
                                }
                                else if (tilerboard[y][x] == 0)
                                {
                                    if (nums[y][x] == 0)
                                    {
                                        queue<sf::Vector2f> q;
                                        q.push(sf::Vector2f(x, y));
                                        while (!q.empty())
                                        {
                                            sf::Vector2f temp = q.front();
                                            q.pop();
                                            if ((temp.x >= 0 && temp.x < col) && (temp.y >= 0 && temp.y < row))
                                            {
                                                if ((visited[temp.y][temp.x] == 0 && flagboard[temp.y][temp.x] == 0) && mineboard[temp.y][temp.x] == 0)
                                                {
                                                    visited[temp.y][temp.x] = 1;
                                                    if (tilerboard[temp.y][temp.x] == 0)
                                                    {
                                                        tilerboard[temp.y][temp.x] = 1;
                                                        ++revealed;
                                                    }
                                                    if (numberboard[temp.y][temp.x] == 0)
                                                    {
                                                        q.push(sf::Vector2f(temp.x - 1, temp.y));
                                                        q.push(sf::Vector2f(temp.x + 1, temp.y));
                                                        q.push(sf::Vector2f(temp.x, temp.y - 1));
                                                        q.push(sf::Vector2f(temp.x, temp.y + 1));
                                                        q.push(sf::Vector2f(temp.x - 1, temp.y + 1));
                                                        q.push(sf::Vector2f(temp.x - 1, temp.y - 1));
                                                        q.push(sf::Vector2f(temp.x + 1, temp.y + 1));
                                                        q.push(sf::Vector2f(temp.x + 1, temp.y - 1));
                                                    }
                                                    else
                                                    {
                                                        sf::Sprite s;
                                                        s.setTexture(number[nums[temp.y][temp.x]]);
                                                        s.setPosition(temp.x * 32, temp.y * 32);
                                                        numbers.push_back(s);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        if (tilerboard[y][x] == 0)
                                        {
                                            tilerboard[y][x] = 1;
                                            ++revealed;
                                        }
                                        sf::Sprite s;
                                        s.setTexture(number[nums[y][x]]);
                                        s.setPosition(x * 32, y * 32);
                                        numbers.push_back(s);
                                    }
                                    if (col * row - revealed - mines.size() == 0)
                                    {
                                        win = true;
                                        face.setTexture(face_win);
                                        count = 0;
                                    }
                                }
                            }
                        }
                        else if ((event.mouseButton.x >= 16 * col - 32 && event.mouseButton.x <= 16 * col + 32) || (event.mouseButton.x >= 16 * col + 160 && event.mouseButton.x <= 16 * col + 352))
                        {
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    visited[i][j] = 0;
                                }
                            }
                            revealed = 0;
                            hund.setTexture(digit[(count / 100)]);
                            tens.setTexture(digit[(count % 100) / 10]);
                            ones.setTexture(digit[count % 10]);
                            face.setTexture(face_happy);
                            win = false;
                            lose = false;
                            flags.clear();
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    flagboard[i][j] = 0;
                                }
                            }
                            tilers.clear();
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    tilerboard[i][j] = 0;
                                }
                            }
                            mines.clear();
                            fmines.clear();
                            if (event.mouseButton.x >= 16 * col - 32 && event.mouseButton.x <= 16 * col + 32)
                            {
                                count = m;
                                for (int i = 0; i < row; ++i)
                                {
                                    for (int j = 0; j < col; ++j)
                                    {
                                        mineboard[i][j] = 0;
                                    }
                                }
                                for (int i = 0; i < m; ++i)
                                {
                                    int rand1 = Random(0, row - 1);
                                    int rand2 = Random(0, col - 1);
                                    if (mineboard[rand1][rand2] == 0)
                                    {
                                        mineboard[rand1][rand2] = 1;
                                        sf::Sprite temp;
                                        temp.setTexture(mine);
                                        temp.setPosition(32 * rand2, 32 * rand1);
                                        mines.push_back(temp);
                                        sf::Sprite temp2;
                                        temp2.setTexture(flag);
                                        temp2.setPosition(32 * rand2, 32 * rand1);
                                        fmines.push_back(temp2);
                                    }
                                    else
                                    {
                                        --i;
                                    }
                                }
                            }
                            else if (event.mouseButton.x >= 16 * col + 160 && event.mouseButton.x <= 16 * col + 224)
                            {
                                int m1 = 0;
                                mineboard = test1board;
                                for (int i = 0; i < row; ++i)
                                {
                                    for (int j = 0; j < col; ++j)
                                    {
                                        if (mineboard[i][j] == 1)
                                        {
                                            ++m1;
                                            sf::Sprite temp;
                                            temp.setTexture(mine);
                                            temp.setPosition(32 * j, 32 * i);
                                            mines.push_back(temp);
                                            sf::Sprite temp2;
                                            temp2.setTexture(flag);
                                            temp2.setPosition(32 * j, 32 * i);
                                            fmines.push_back(temp2);
                                        }
                                    }
                                }
                                count = m1;
                            }
                            else if (event.mouseButton.x >= 16 * col + 224 && event.mouseButton.x <= 16 * col + 288)
                            {
                                int m2 = 0;
                                mineboard = test2board;
                                for (int i = 0; i < row; ++i)
                                {
                                    for (int j = 0; j < col; ++j)
                                    {
                                        if (mineboard[i][j] == 1)
                                        {
                                            ++m2;
                                            sf::Sprite temp;
                                            temp.setTexture(mine);
                                            temp.setPosition(32 * j, 32 * i);
                                            mines.push_back(temp);
                                            sf::Sprite temp2;
                                            temp2.setTexture(flag);
                                            temp2.setPosition(32 * j, 32 * i);
                                            fmines.push_back(temp2);
                                        }
                                    }
                                }
                                count = m2;
                            }
                            else if (event.mouseButton.x >= 16 * col + 288 && event.mouseButton.x <= 16 * col + 352)
                            {
                                int m3 = 0;
                                mineboard = test3board;
                                for (int i = 0; i < row; ++i)
                                {
                                    for (int j = 0; j < col; ++j)
                                    {
                                        if (mineboard[i][j] == 1)
                                        {
                                            ++m3;
                                            sf::Sprite temp;
                                            temp.setTexture(mine);
                                            temp.setPosition(32 * j, 32 * i);
                                            mines.push_back(temp);
                                            sf::Sprite temp2;
                                            temp2.setTexture(flag);
                                            temp2.setPosition(32 * j, 32 * i);
                                            fmines.push_back(temp2);
                                        }
                                    }
                                }
                                count = m3;
                            }
                            numbers.clear();
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    numberboard[i][j] = 0;
                                }
                            }
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    if (mineboard[i][j] == 1)
                                    {
                                        numberboard[i][j] = 1;
                                    }
                                    else
                                    {
                                        int n = GetNumber(i, j, mineboard);
                                        if (n > 0)
                                        {
                                            numberboard[i][j] = 1;
                                        }
                                        nums[i][j] = n;
                                    }
                                }
                            }
                        }
                        else if (event.mouseButton.x >= 16 * col + 96 && event.mouseButton.x <= 16 * col + 160)
                        {
                            if (!debug)
                                debug = true;
                            else
                                debug = false;
                        }
                    }
                }
                else
                {
                    if (event.mouseButton.y >= 32 * row && ((event.mouseButton.x >= 16 * col - 32 && event.mouseButton.x <= 16 * col + 32) || (event.mouseButton.x >= 16 * col + 160 && event.mouseButton.x <= 16 * col + 352)))
                    {
                        for (int i = 0; i < row; ++i)
                        {
                            for (int j = 0; j < col; ++j)
                            {
                                visited[i][j] = 0;
                            }
                        }
                        revealed = 0;
                        hund.setTexture(digit[(count / 100)]);
                        tens.setTexture(digit[(count % 100) / 10]);
                        ones.setTexture(digit[count % 10]);
                        face.setTexture(face_happy);
                        win = false;
                        lose = false;
                        flags.clear();
                        for (int i = 0; i < row; ++i)
                        {
                            for (int j = 0; j < col; ++j)
                            {
                                flagboard[i][j] = 0;
                            }
                        }
                        tilers.clear();
                        for (int i = 0; i < row; ++i)
                        {
                            for (int j = 0; j < col; ++j)
                            {
                                tilerboard[i][j] = 0;
                            }
                        }
                        mines.clear();
                        fmines.clear();
                        if (event.mouseButton.x >= 16 * col - 32 && event.mouseButton.x <= 16 * col + 32)
                        {
                            count = m;
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    mineboard[i][j] = 0;
                                }
                            }
                            for (int i = 0; i < m; ++i)
                            {
                                int rand1 = Random(0, row - 1);
                                int rand2 = Random(0, col - 1);
                                if (mineboard[rand1][rand2] == 0)
                                {
                                    mineboard[rand1][rand2] = 1;
                                    sf::Sprite temp;
                                    temp.setTexture(mine);
                                    temp.setPosition(32 * rand2, 32 * rand1);
                                    mines.push_back(temp);
                                    sf::Sprite temp2;
                                    temp2.setTexture(flag);
                                    temp2.setPosition(32 * rand2, 32 * rand1);
                                    fmines.push_back(temp2);
                                }
                                else
                                {
                                    --i;
                                }
                            }
                        }
                        else if (event.mouseButton.x >= 16 * col + 160 && event.mouseButton.x <= 16 * col + 224)
                        {
                            int m1 = 0;
                            mineboard = test1board;
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    if (mineboard[i][j] == 1)
                                    {
                                        ++m1;
                                        sf::Sprite temp;
                                        temp.setTexture(mine);
                                        temp.setPosition(32 * j, 32 * i);
                                        mines.push_back(temp);
                                        sf::Sprite temp2;
                                        temp2.setTexture(flag);
                                        temp2.setPosition(32 * j, 32 * i);
                                        fmines.push_back(temp2);
                                    }
                                }
                            }
                            count = m1;
                        }
                        else if (event.mouseButton.x >= 16 * col + 224 && event.mouseButton.x <= 16 * col + 288)
                        {
                            int m2 = 0;
                            mineboard = test2board;
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    if (mineboard[i][j] == 1)
                                    {
                                        ++m2;
                                        sf::Sprite temp;
                                        temp.setTexture(mine);
                                        temp.setPosition(32 * j, 32 * i);
                                        mines.push_back(temp);
                                        sf::Sprite temp2;
                                        temp2.setTexture(flag);
                                        temp2.setPosition(32 * j, 32 * i);
                                        fmines.push_back(temp2);
                                    }
                                }
                            }
                            count = m2;
                        }
                        else if (event.mouseButton.x >= 16 * col + 288 && event.mouseButton.x <= 16 * col + 352)
                        {
                            int m3 = 0;
                            mineboard = test3board;
                            for (int i = 0; i < row; ++i)
                            {
                                for (int j = 0; j < col; ++j)
                                {
                                    if (mineboard[i][j] == 1)
                                    {
                                        ++m3;
                                        sf::Sprite temp;
                                        temp.setTexture(mine);
                                        temp.setPosition(32 * j, 32 * i);
                                        mines.push_back(temp);
                                        sf::Sprite temp2;
                                        temp2.setTexture(flag);
                                        temp2.setPosition(32 * j, 32 * i);
                                        fmines.push_back(temp2);
                                    }
                                }
                            }
                            count = m3;
                        }
                        numbers.clear();
                        for (int i = 0; i < row; ++i)
                        {
                            for (int j = 0; j < col; ++j)
                            {
                                numberboard[i][j] = 0;
                            }
                        }
                        for (int i = 0; i < row; ++i)
                        {
                            for (int j = 0; j < col; ++j)
                            {
                                if (mineboard[i][j] == 1)
                                {
                                    numberboard[i][j] = 1;
                                }
                                else
                                {
                                    int n = GetNumber(i, j, mineboard);
                                    if (n > 0)
                                    {
                                        numberboard[i][j] = 1;
                                    }
                                    nums[i][j] = n;
                                }
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                window.draw(tilehsprite[i][j]);
            }
        }
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (tilerboard[i][j] == 1)
                {
                    window.draw(tilersprite[i][j]);
                }
            }
        }
        for (int i = 0; i < numbers.size(); ++i)
        {
            window.draw(numbers[i]);
        }
        for (int i = 0; i < flags.size(); ++i)
        {
            window.draw(flags[i]);
        }
        if (win)
        {
            for (int i = 0; i < fmines.size(); ++i)
            {
                window.draw(fmines[i]);
            }
        }
        if (debug || lose)
        {
            for (int i = 0; i < mines.size(); ++i)
            {
                window.draw(mines[i]);
            }
        }
        if (count >= 0)
        {
            hund.setTexture(digit[(count / 100)]);
            tens.setTexture(digit[(count % 100) / 10]);
            ones.setTexture(digit[count % 10]);
        }
        else if (count < 0)
        {
            window.draw(neg);
            hund.setTexture(digit[(-count / 100)]);
            tens.setTexture(digit[(-count % 100) / 10]);
            ones.setTexture(digit[-count % 10]);
        }
        window.draw(hund);
        window.draw(tens);
        window.draw(ones);
        window.draw(face);
        window.draw(dbg);
        window.draw(t1);
        window.draw(t2);
        window.draw(t3);
        window.display();
    }
    return 0;
}
