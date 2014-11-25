#include "stdafx.h"
#include "TrieTreeNonleafNode.h"
#include "TrieTree.h"
#include <cassert>
#include <algorithm>

const int TrieTreeNonleafNode::NumberOfSons;
const int TrieTreeNonleafNode::LeftBoarder;
const int TrieTreeNonleafNode::RightBoarder;

TrieTreeNonleafNode::TrieTreeNonleafNode()
{
	std::fill(m_SonList.begin(), m_SonList.end(), 0);
}


TrieTreeNonleafNode::~TrieTreeNonleafNode()
{
}

int TrieTreeNonleafNode::GetIndex(int value) const
{
	if (value < LeftBoarder) value = LeftBoarder;
	if (value > RightBoarder) value = RightBoarder;
	value -= LeftBoarder;
	return value;
}

int TrieTreeNonleafNode::GetSonNode(TrieTree *tree, int value, int height)
{
	assert(tree);
	value = GetIndex(value);
	if (!m_SonList[value])
	{
		m_SonList[value] = tree->GetNewNodeID(height);
	}
	return m_SonList[value];
}

int TrieTreeNonleafNode::SonNodeQuery(int value) const
{
	value = GetIndex(value);
	return m_SonList[value];
}


