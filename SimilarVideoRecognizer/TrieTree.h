#pragma once
#include "TrieTreeLeafNode.h"
#include "TrieTreeNonleafNode.h"
#include "TrieNodeContainer.cpp"
#include "GroupOfHashValueVector.h"
#include <vector>

class TrieTree
{
	friend class TrieTreeNonleafNode;
	friend class TrieTreeLeafNode;
public:
	TrieTree();
	~TrieTree();
	void Insert(const std::vector<int> &hashvalue, int videonum);
	std::vector<int> Search(const std::vector<int> &hashvalue) const;

private:
	int GetNewNodeID(int height);
	
	TrieNodeContainer<TrieTreeLeafNode> m_LeafNodeList;
	TrieNodeContainer<TrieTreeNonleafNode> m_NonleafNodeList;

	static const int HeightOfTheTree = 40;
	int m_RootNumber;
};

