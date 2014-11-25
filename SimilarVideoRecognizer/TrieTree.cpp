#include "stdafx.h"
#include "TrieTree.h"
#include <cassert>

const int TrieTree::HeightOfTheTree;

TrieTree::TrieTree()
{
	m_NonleafNodeList.add();
	m_RootNumber = 0;
}


TrieTree::~TrieTree()
{
}

void TrieTree::Insert(const std::vector<int> &hashvalue, int videonum)
{
	assert(hashvalue.size() == HeightOfTheTree);
	int node = m_RootNumber;
	int height = 0;
	for (auto iter = hashvalue.cbegin(); iter != hashvalue.cend(); ++iter)
	{
		node = m_NonleafNodeList[node].GetSonNode(this, *iter, height + 1);
		++height;
	}
	m_LeafNodeList[node].Insert(videonum);
}

std::vector <int> TrieTree::Search(const std::vector<int> &hashvalue) const
{
	assert(hashvalue.size() == HeightOfTheTree);
	int node = m_RootNumber;
	int height = 0;
	std::vector<int> emp;
	for (auto iter = hashvalue.cbegin(); iter != hashvalue.cend(); ++iter)
	{
		node = m_NonleafNodeList[node].SonNodeQuery(*iter);
		if (node <= 0) return emp;
		++height;
	}
	return m_LeafNodeList[node].GetVec();
}

int TrieTree::GetNewNodeID(int height)
{
	if (height == HeightOfTheTree) return m_LeafNodeList.add();
	else return m_NonleafNodeList.add();
}
