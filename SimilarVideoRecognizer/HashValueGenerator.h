#pragma once
#include <vector>
#include <array>
#include "GroupOfHashFunction.h"

class HashValueGenerator
{
public:
	void SetHashFunctionTable(int code, const std::vector<std::vector<double>> &a, const std::vector<double> &b);
	std::vector<std::vector<int>> GetHashValue(const std::vector<double> &OSIDVec);
	static HashValueGenerator* GetInstance();
	void PrintHashFunctionTable(std::ofstream &ofs);

private:
	HashValueGenerator();
	~HashValueGenerator();
	std::vector <GroupOfHashFunction> m_HashFunctionTable;
	static HashValueGenerator* m_pInstance;
};
