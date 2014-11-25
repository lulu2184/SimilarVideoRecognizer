#pragma once
#include "TrieNodeContainer.h" 
#include <vector>

class TrieTreeLeafNode
{
public:
	TrieTreeLeafNode();
	~TrieTreeLeafNode();
	void Insert(int t);
	bool Search(int videonumber) const;
	std::vector<int> GetVec() const;

private:
	std::vector <int> m_VideoList;
};

