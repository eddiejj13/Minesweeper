#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <random>;
#include <ctime>
using namespace std;

class TextureManager {
	static unordered_map<string, sf::Texture> textures;
public:
	static void LoadTexture(string fileName);
	static sf::Texture& GetTexture(string textureName);
	static void Clear();
};

class Random {
	static std::mt19937 random;
public:
	static int Int(int min, int max);
};

class Board {
	vector<sf::Sprite> hidden;
	vector<sf::Sprite> mines;
	vector<sf::Sprite> revealedBoard;
	vector<sf::Sprite> numBoard;
	vector<sf::Sprite> flagBoard;
	vector<int> sIndex;
	vector<int> flagIndex;
	vector<int> hiddenValues;
	vector<int> flagValues;
	vector<int> tileValue;
	vector<int> mineIndex;
	vector<int> adj;
	int row;
	int col;
	int m;
	bool gameLost;
	bool debugOn;
public:
	Board(int rowNum, int colNum, int mineNum);
	Board(int rowNum, int colNum, vector<int>mines);
	vector<sf::Sprite>& GetHidden();
	vector<sf::Sprite>& GetMines();
	vector<sf::Sprite>& GetNumBoard();
	vector<sf::Sprite>& GetRevealedBoard();
	vector<sf::Sprite>& GetFlagBoard();
	void SurroundingIndex(int index, int row, int col, vector<int>& hiddenValues);
	vector<int> GetAdjacent(int index, int row, int col);
	vector<int>& GetMineIndex();
	vector<int>& GetTileValue();
	vector<int>& GetsIndex();
	vector<int>& GetHiddenValues();
	vector<int>& GetFlagValues();
	vector<int>& GetFlagIndex();
	bool GetGameLost();
	bool GetDebug();
	void ClearAdj();
	void DebugOn();
	void DebugOff();
	void Click(int index, sf::Sprite reveal, sf::Sprite one, sf::Sprite two, sf::Sprite three, sf::Sprite four, sf::Sprite five, sf::Sprite six, sf::Sprite seven, sf::Sprite eight);
};