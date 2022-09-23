#include "stuff.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "stuff.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <map>
#include <ctime>
using namespace std;

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName) {
	string path = "images/";
	path += fileName + ".png";
	textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
	if (textures.find(textureName) == textures.end()) {
		LoadTexture(textureName);
	}
	return textures[textureName];
}

void TextureManager::Clear() {
	textures.clear();
}

std::mt19937 Random::random(time(0));

int Random::Int(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}

int MinesAroundSquare(int row, int col, int index, vector<int> mineIndex) {
    int counter = 0;
    std::vector<int>::iterator it;
    if (index == 0) {
        it = std::find(mineIndex.begin(), mineIndex.end(), 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else if (index == col - 1) {
        it = std::find(mineIndex.begin(), mineIndex.end(), col - 2);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col * 2 - 2);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col * 2 - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else if (index == col * (row - 1)) {
        it = std::find(mineIndex.begin(), mineIndex.end(), col * (row - 2));
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col * (row - 2) + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col * (row - 1) + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else if (index == col * row - 1) {
        it = std::find(mineIndex.begin(), mineIndex.end(), col * row - 2);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col * (row - 1) - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), col * (row - 1) - 2);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else if (index % col == 0) {
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else if (index % col == col - 1) {
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else if (index < col) {
        it = std::find(mineIndex.begin(), mineIndex.end(), index + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else if (index > col * (row - 1)) {
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    else {
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - col - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col + 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
        it = std::find(mineIndex.begin(), mineIndex.end(), index + col - 1);
        if (it != mineIndex.end()) {
            ++counter;
        }
    }
    return counter;
}

vector<int> Board::GetAdjacent(int index, int row, int col) {
    std::vector<int>::iterator it = std::find(adj.begin(), adj.end(), index + 1);
    if (index == 0) {
        if (hiddenValues.at(index + 1) == 1 && tileValue.at(index + 1) != 9 && it == adj.end() && flagValues.at(index + 1) != 1) {
            adj.push_back(index + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col + 1);
        if (hiddenValues.at(index + col + 1) == 1 && tileValue.at(index + col + 1) != 9 && it == adj.end() && flagValues.at(index + col + 1) != 1) {
            adj.push_back(index + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col);
        if (hiddenValues.at(index + col) == 1 && tileValue.at(index + col) != 9 && it == adj.end() && flagValues.at(index + col) != 1) {
            adj.push_back(index + col);
        }
    }
    else if (index == col - 1) {
        it = std::find(adj.begin(), adj.end(), index + col);
        if (hiddenValues.at(index + col) == 1 && tileValue.at(index + col) != 9 && it == adj.end() && flagValues.at(index + col) != 1) {
            adj.push_back(index + col);
        }
        it = std::find(adj.begin(), adj.end(), index + col - 1);
        if (hiddenValues.at(index + col - 1) == 1 && tileValue.at(index + col - 1) != 9 && it == adj.end() && flagValues.at(index + col - 1) != 1) {
            adj.push_back(index + col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - 1);
        if (hiddenValues.at(index - 1) == 1 && tileValue.at(index - 1) != 9 && it == adj.end() && flagValues.at(index - 1) != 1) {
            adj.push_back(index - 1);
        }
    }
    else if (index == col * (row - 1)) {
        it = std::find(adj.begin(), adj.end(), index - col);
        if (hiddenValues.at(index - col) == 1 && tileValue.at(index - col) != 9 && it == adj.end() && flagValues.at(index - col) != 1) {
            adj.push_back(index - col);
        }
        it = std::find(adj.begin(), adj.end(), index - col + 1);
        if (hiddenValues.at(index - col + 1) == 1 && tileValue.at(index - col + 1) != 9 && it == adj.end() && flagValues.at(index - col + 1) != 1) {
            adj.push_back(index - col + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + 1);
        if (hiddenValues.at(index + 1) == 1 && tileValue.at(index + 1) != 9 && it == adj.end() && flagValues.at(index + 1) != 1) {
            adj.push_back(index + 1);
        }
    }
    else if (index == col * row - 1) {
        it = std::find(adj.begin(), adj.end(), index - col - 1);
        if (hiddenValues.at(index - col - 1) == 1 && tileValue.at(index - col - 1) != 9 && it == adj.end() && flagValues.at(index - col - 1) != 1) {
            adj.push_back(index - col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - col);
        if (hiddenValues.at(index - col) == 1 && tileValue.at(index - col) != 9 && it == adj.end() && flagValues.at(index - col) != 1) {
            adj.push_back(index - col);
        }
        it = std::find(adj.begin(), adj.end(), index - 1);
        if (hiddenValues.at(index - 1) == 1 && tileValue.at(index - 1) != 9 && it == adj.end() && flagValues.at(index - 1) != 1) {
            adj.push_back(index - 1);
        }
    }
    else if (index % col == 0) {
        it = std::find(adj.begin(), adj.end(), index - col);
        if (hiddenValues.at(index - col) == 1 && tileValue.at(index - col) != 9 && it == adj.end() && flagValues.at(index - col) != 1) {
            adj.push_back(index - col);
        }
        it = std::find(adj.begin(), adj.end(), index - col + 1);
        if (hiddenValues.at(index - col + 1) == 1 && tileValue.at(index - col + 1) != 9 && it == adj.end() && flagValues.at(index - col + 1) != 1) {
            adj.push_back(index - col + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + 1);
        if (hiddenValues.at(index + 1) == 1 && tileValue.at(index + 1) != 9 && it == adj.end() && flagValues.at(index + 1) != 1) {
            adj.push_back(index + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col + 1);
        if (hiddenValues.at(index + col + 1) == 1 && tileValue.at(index + col + 1) != 9 && it == adj.end() && flagValues.at(index + col + 1) != 1) {
            adj.push_back(index + col + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col);
        if (hiddenValues.at(index + col) == 1 && tileValue.at(index + col) != 9 && it == adj.end() && flagValues.at(index + col) != 1) {
            adj.push_back(index + col);
        }
    }
    else if (index % col == col - 1) {
        it = std::find(adj.begin(), adj.end(), index  - col - 1);
        if (hiddenValues.at(index - col - 1) == 1 && tileValue.at(index - col - 1) != 9 && it == adj.end() && flagValues.at(index - col - 1) != 1) {
            adj.push_back(index - col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - col);
        if (hiddenValues.at(index - col) == 1 && tileValue.at(index - col) != 9 && it == adj.end() && flagValues.at(index - col) != 1) {
            adj.push_back(index - col);
        }
        it = std::find(adj.begin(), adj.end(), index + col);
        if (hiddenValues.at(index + col) == 1 && tileValue.at(index + col) != 9 && it == adj.end() && flagValues.at(index + col) != 1) {
            adj.push_back(index + col);
        }
        it = std::find(adj.begin(), adj.end(), index + col - 1);
        if (hiddenValues.at(index + col - 1) == 1 && tileValue.at(index + col - 1) != 9 && it == adj.end() && flagValues.at(index + col - 1) != 1) {
            adj.push_back(index + col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - 1);
        if (hiddenValues.at(index - 1) == 1 && tileValue.at(index - 1) != 9 && it == adj.end() && flagValues.at(index - 1) != 1) {
            adj.push_back(index - 1);
        }
    }
    else if (index < col) {
        it = std::find(adj.begin(), adj.end(), index + 1);
        if (hiddenValues.at(index + 1) == 1 && tileValue.at(index + 1) != 9 && it == adj.end() && flagValues.at(index + 1) != 1) {
            adj.push_back(index + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col + 1);
        if (hiddenValues.at(index + col + 1) == 1 && tileValue.at(index + col + 1) != 9 && it == adj.end() != 9 && flagValues.at(index + col + 1) != 1) {
            adj.push_back(index + col + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col);
        if (hiddenValues.at(index + col) == 1 && tileValue.at(index + col) != 9 && it == adj.end() && flagValues.at(index + col) != 1) {
            adj.push_back(index + col);
        }
        it = std::find(adj.begin(), adj.end(), index + col - 1);
        if (hiddenValues.at(index + col - 1) == 1 && tileValue.at(index + col - 1) != 9 && it == adj.end() && flagValues.at(index + col - 1) != 1) {
            adj.push_back(index + col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - 1);
        if (hiddenValues.at(index - 1) == 1 && tileValue.at(index - 1) != 9 && it == adj.end() && flagValues.at(index - 1) != 1) {
            adj.push_back(index - 1);
        }
    }
    else if (index > col * (row - 1)) {
        it = std::find(adj.begin(), adj.end(), index - col - 1);
        if (hiddenValues.at(index - col - 1) == 1 && tileValue.at(index - col - 1) != 9 && it == adj.end() && flagValues.at(index - col - 1) != 1) {
            adj.push_back(index - col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - col);
        if (hiddenValues.at(index - col) == 1 && tileValue.at(index - col) != 9 && it == adj.end() && flagValues.at(index - col) != 1) {
            adj.push_back(index - col);
        }
        it = std::find(adj.begin(), adj.end(), index - col + 1);
        if (hiddenValues.at(index - col + 1) == 1 && tileValue.at(index - col + 1) != 9 && it == adj.end() && flagValues.at(index - col + 1) != 1) {
            adj.push_back(index - col + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + 1);
        if (hiddenValues.at(index + 1) == 1 && tileValue.at(index + 1) != 9 && it == adj.end() && flagValues.at(index + 1) != 1) {
            adj.push_back(index + 1);
        }
        it = std::find(adj.begin(), adj.end(), index - 1);
        if (hiddenValues.at(index - 1) == 1 && tileValue.at(index - 1) != 9 && it == adj.end() && flagValues.at(index - 1) != 1) {
            adj.push_back(index - 1);
        }
    }
    else {
        it = std::find(adj.begin(), adj.end(), index - col - 1);
        if (hiddenValues.at(index - col - 1) == 1 && tileValue.at(index - col - 1) != 9 && it == adj.end() && flagValues.at(index - col - 1) != 1) {
            adj.push_back(index - col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - col);
        if (hiddenValues.at(index - col) == 1 && tileValue.at(index - col) != 9 && it == adj.end() && flagValues.at(index - col) != 1) {
            adj.push_back(index - col);
        }
        it = std::find(adj.begin(), adj.end(), index - col + 1);
        if (hiddenValues.at(index - col + 1) == 1 && tileValue.at(index - col + 1) != 9 && it == adj.end() && flagValues.at(index - col + 1) != 1) {
            adj.push_back(index - col + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + 1);
        if (hiddenValues.at(index + 1) == 1 && tileValue.at(index + 1) != 9 && it == adj.end() && flagValues.at(index + 1) != 1) {
            adj.push_back(index + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col + 1);
        if (hiddenValues.at(index + col + 1) == 1 && tileValue.at(index + col + 1) != 9 && it == adj.end() && flagValues.at(index + col + 1) != 1) {
            adj.push_back(index + col + 1);
        }
        it = std::find(adj.begin(), adj.end(), index + col);
        if (hiddenValues.at(index + col) == 1 && tileValue.at(index + col) != 9 && it == adj.end() && flagValues.at(index + col) != 1) {
            adj.push_back(index + col);
        }
        it = std::find(adj.begin(), adj.end(), index + col - 1);
        if (hiddenValues.at(index + col - 1) == 1 && tileValue.at(index + col - 1) != 9 && it == adj.end() && flagValues.at(index + col - 1) != 1) {
            adj.push_back(index + col - 1);
        }
        it = std::find(adj.begin(), adj.end(), index - 1);
        if (hiddenValues.at(index - 1) == 1 && tileValue.at(index - 1) != 9 && it == adj.end() && flagValues.at(index - 1) != 1) {
            adj.push_back(index - 1);
        }
    }
    return adj;
}

Board::Board(int rowNum, int colNum, int mineNum) {
	row = rowNum;
	col = colNum;
	m = mineNum;
    gameLost = false;
    debugOn = false;
	int counter = 0;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			sf::Sprite hide(TextureManager::GetTexture("tile_hidden"));
			hidden.push_back(hide);
			hidden.at(counter).setPosition(j * 32, i * 32);
			++counter;
		}
	}
	for (int i = 0; i < m; ++i) {
		int rand = Random::Int(0, row * col - 1);
		std::vector<int>::iterator it = std::find(mineIndex.begin(), mineIndex.end(), rand);
		if (it != mineIndex.end()) {
			--i;
		}
		else {
			mineIndex.push_back(rand);
		}
	}
	for (int i = 0; i < m; ++i) {
		sf::Sprite mine(TextureManager::GetTexture("mine"));
		mines.push_back(mine);
		mines.at(i).setPosition((mineIndex.at(i) % col) * 32, (mineIndex.at(i) / col) * 32);
	}
    for (int i = 0; i < row * col; ++i) {
        std::vector<int>::iterator it = std::find(mineIndex.begin(), mineIndex.end(), i);
        if (it != mineIndex.end()) {
            tileValue.push_back(9);
        }
        else
            tileValue.push_back(MinesAroundSquare(row, col, i, mineIndex));
    }
    for (int i = 0; i < row * col; ++i) {
        flagValues.push_back(0);
        hiddenValues.push_back(1);
    }
}

Board::Board(int rowNum, int colNum, vector<int> mineFile) {
    row = rowNum;
    col = colNum;
    m = 0;
    gameLost = false;
    debugOn = false;
    int counter = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            sf::Sprite hide(TextureManager::GetTexture("tile_hidden"));
            hidden.push_back(hide);
            hidden.at(counter).setPosition(j * 32, i * 32);
            ++counter;
        }
    }
    for (int i = 0; i < mineFile.size(); ++i) {
        if (mineFile.at(i) == 1) {
            ++m;
            mineIndex.push_back(i);
        }
    }
    for (int i = 0; i < m; ++i) {
        sf::Sprite mine(TextureManager::GetTexture("mine"));
        mines.push_back(mine);
        mines.at(i).setPosition((mineIndex.at(i) % col) * 32, (mineIndex.at(i) / col) * 32);
    }
    for (int i = 0; i < row * col; ++i) {
        std::vector<int>::iterator it = std::find(mineIndex.begin(), mineIndex.end(), i);
        if (it != mineIndex.end()) {
            tileValue.push_back(9);
        }
        else
            tileValue.push_back(MinesAroundSquare(row, col, i, mineIndex));
    }
    for (int i = 0; i < row * col; ++i) {
        flagValues.push_back(0);
        hiddenValues.push_back(1);
    }
}

//dont do recursive here
void Board::Click(int index, sf::Sprite reveal, sf::Sprite one, sf::Sprite two, sf::Sprite three, sf::Sprite four, sf::Sprite five, sf::Sprite six, sf::Sprite seven, sf::Sprite eight) {
    int colLoc = index % col;
    int rowLoc = index / col;
    if (flagValues.at(index) == 0 && hiddenValues.at(index) == 1) {
        if (tileValue.at(index) == 0) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 1) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            one.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(one);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 2) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            two.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(two);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 3) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            three.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(three);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 4) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            four.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(four);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 5) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            five.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(five);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 6) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            six.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(six);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 7) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            seven.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(seven);
            hiddenValues.at(index) = 0;
        }
        else if (tileValue.at(index) == 8) {
            reveal.setPosition(colLoc * 32, rowLoc * 32);
            revealedBoard.push_back(reveal);
            eight.setPosition(colLoc * 32, rowLoc * 32);
            numBoard.push_back(eight);
            hiddenValues.at(index) = 0;
        }
        else {
            gameLost = true;
            for (int i = 0; i < mineIndex.size(); ++i) {
                int locCol = mineIndex.at(i) % col;
                int locRow = mineIndex.at(i) / col;
                if (flagValues.at(mineIndex.at(i)) == 0) {
                    reveal.setPosition(locCol * 32, locRow * 32);
                    revealedBoard.push_back(reveal);
                }
            }
        }
    }
}


vector<sf::Sprite>& Board::GetHidden() {
	return hidden;
}

vector<sf::Sprite>& Board::GetMines() {
	return mines;
}

vector<sf::Sprite>& Board::GetNumBoard() {
    return numBoard;
}

vector<sf::Sprite>& Board::GetRevealedBoard() {
    return revealedBoard;
}

vector<sf::Sprite>& Board::GetFlagBoard() {
    return flagBoard;
}

vector<int>& Board::GetMineIndex() {
	return mineIndex;
}

vector<int>& Board::GetTileValue() {
    return tileValue;
}

vector<int>& Board::GetHiddenValues() {
    return hiddenValues;
}

vector<int>& Board::GetFlagValues() {
    return flagValues;
}

vector<int>& Board::GetFlagIndex() {
    return flagIndex;
}

vector<int>& Board::GetsIndex() {
    return sIndex;
}

bool Board::GetGameLost() {
    return gameLost;
}

bool Board::GetDebug() {
    return debugOn;
}

void Board::ClearAdj() {
    adj.clear();
}

void Board::DebugOn() {
    debugOn = true;
}

void Board::DebugOff() {
    debugOn = false;
}