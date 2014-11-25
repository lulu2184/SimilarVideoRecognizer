#include "stdafx.h"
#include "TrieTreeLeafNode.h"


TrieTreeLeafNode::TrieTreeLeafNode()
{
}


TrieTreeLeafNode::~TrieTreeLeafNode()
{
}

void TrieTreeLeafNode::Insert(int t)
{
	m_VideoList.push_back(t);
}

bool TrieTreeLeafNode::Search(int videonumber) const
{
	for (auto iter = m_VideoList.cbegin(); iter != m_VideoList.cend(); ++iter)
	{
		if (*iter == videonumber)
		{
			return true;
		}
	}
	return false;
}

std::vector <int> TrieTreeLeafNode::GetVec() const
{
	return m_VideoList;
}