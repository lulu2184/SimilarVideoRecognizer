#pragma once
#include <vector>
#include <array>

const size_t SizeOfEachArray = 20; // appropriate? and how define in the class

template <class Type> class TrieNodeContainer
{
public:
	TrieNodeContainer();
	~TrieNodeContainer();
	void Insert(const Type &Item);
	int add();
	Type &operator[] (const int);
	const Type &operator[] (const int) const;
	int Size() const;

private:
	void Expand();
	std::vector<std::array<Type, SizeOfEachArray>> m_vec;
	int m_size;
	typename std::vector<std::array<Type, SizeOfEachArray>>::iterator m_CurrentArray;
//	static const size_t SizeOfEachArray = 100000; // appropiate?
};

