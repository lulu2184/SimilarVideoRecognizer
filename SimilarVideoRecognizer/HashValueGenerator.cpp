#include "stdafx.h"
#include "HashValueGenerator.h"
#include <cassert>

HashValueGenerator* HashValueGenerator::m_pInstance = new HashValueGenerator;

HashValueGenerator::HashValueGenerator()
{
	for (int i = 0; i < GroupOfHashFunction::NumberOfFunctionGroups; ++i)
	{
		GroupOfHashFunction tmp;
		m_HashFunctionTable.push_back(std::move(tmp));
	}
}


HashValueGenerator::~HashValueGenerator()
{
}

HashValueGenerator* HashValueGenerator::GetInstance()
{
	return m_pInstance;
}

std::vector <std::vector<int>> HashValueGenerator::GetHashValue(const std::vector<double> &OSIDVec)
{
	std::vector <std::vector<int>> hashvalue;
	for (int i = 0; i < GroupOfHashFunction::NumberOfFunctionGroups; ++i)
	{
		hashvalue.push_back(m_HashFunctionTable[i].GetHashVector(OSIDVec));
	}
	return std::move(hashvalue);
}

void HashValueGenerator::SetHashFunctionTable(int code, const std::vector<std::vector<double>> &a, const std::vector<double> &b)
{
	assert(code >= 0 && code <= GroupOfHashFunction::NumberOfFunctionGroups);
	m_HashFunctionTable[code].SetParameter(a, b);
}

void HashValueGenerator::PrintHashFunctionTable(std::ofstream &ofs)
{
	for (auto iter = m_HashFunctionTable.begin(); iter != m_HashFunctionTable.end(); ++iter)
	{
		iter->Print(ofs);
	}
}