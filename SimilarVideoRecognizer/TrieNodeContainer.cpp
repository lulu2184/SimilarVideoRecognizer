#include "stdafx.h"
#include "TrieNodeContainer.h"
#include <cassert>

//template <typename T> 
//const size_t TrieNodeContainer<T>::SizeOfEachArray;

template <class Type> TrieNodeContainer<Type>::TrieNodeContainer()
{
	m_CurrentArray = m_vec.begin();
	m_size = 0;
}

template <class Type> TrieNodeContainer<Type>::~TrieNodeContainer()
{
}

template <class Type> void TrieNodeContainer<Type>::Insert(const Type &Item)
{
	if (m_size % SizeOfEachArray == 0)
	{
		//		Expand();
		m_vec.emplace_back();
	}
	m_vec[m_size / SizeOfEachArray][m_size % SizeOfEachArray] = Item;
	++m_size;
	return m_size - 1;
}

template <class Type> int TrieNodeContainer<Type>::add()
{
	if (m_size % SizeOfEachArray == 0)
	{
		//		Expand();
				m_vec.emplace_back();
		//m_vec.resize(m_size / SizeOfEachArray + 1);
	}
	++m_size;
	return m_size - 1;
}

template <class Type> void TrieNodeContainer<Type>::Expand()
{
	m_vec.emplace_back();
	if (m_size > 0)
	{
		++m_CurrentArray;
	}
	else
	{
		m_CurrentArray = m_vec.begin();
	}
}

template <class Type> int TrieNodeContainer<Type>::Size() const
{
	return m_size;
}

template <class Type> Type& TrieNodeContainer<Type>::operator[] (const int index)
{
	assert(index >= 0 && index < m_size);
	return m_vec[index / SizeOfEachArray][index % SizeOfEachArray];
}

template <class Type> const Type& TrieNodeContainer<Type>::operator[](const int index) const
{
	assert(index >= 0 && index < m_size);
	return m_vec[index / SizeOfEachArray][index % SizeOfEachArray];
}