#pragma once
#include <vector>
#include "HashValueGenerator.h"
#include "LayerOfEigenvector.h"
#include <fstream>

class GroupOfHashValueVector
{
public:
	GroupOfHashValueVector();
	~GroupOfHashValueVector();
	void GenerateHashValue(const std::vector<double> &OSIDVector);
	void print(std::ofstream &ofs);
	std::vector <int> GetVector(int groupID) const;

private:
	std::vector<std::vector<int>> m_HashValue;
};

class LayerOfHashValue
{
public:
	LayerOfHashValue();
	~LayerOfHashValue();
	void GenerateHashValue(const LayerOfEigenvector &eigenvector);
	void print(std::ofstream &ofs);
	std::vector <std::vector<int>> GetVector(int groupID) const;

private:
	std::vector <GroupOfHashValueVector> m_HashValue;
};

