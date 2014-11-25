#pragma once
#include <array>

class TrieTree;
class TrieTreeNonleafNode
{
public:
	TrieTreeNonleafNode();
	~TrieTreeNonleafNode();
	int GetSonNode(TrieTree *tree, int value, int height);
	int SonNodeQuery(int value) const;

private:
	int GetIndex(int value) const;

	static const int NumberOfSons = 8; 
	static const int LeftBoarder = -2;
	static const int RightBoarder = 5;
	std::array<int, NumberOfSons> m_SonList;
};

