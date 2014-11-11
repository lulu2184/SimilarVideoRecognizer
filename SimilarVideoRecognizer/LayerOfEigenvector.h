#pragma once
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>

const int NumberOfSamplesIn1stLayerVEC = 10;
const int MultipleOfAdjacentLayer = 2;
const int NumberOfLayer = 3;
const int SizeOfEigenvector = 27;

class LayerOfEigenvector
{
private:
	double m_Combination;
	std::vector <std::vector<double>> m_VEigenvector;
	std::vector<double> DivideByCombination(const std::vector<double> &num)const;

public:
	LayerOfEigenvector();
	LayerOfEigenvector(int numberOfElements);
	LayerOfEigenvector(std::vector<std::vector<double>> &vec);
	~LayerOfEigenvector();
	LayerOfEigenvector GetLayer(int NumberOfCombination);
	void push_back(const std::vector<double> &vec);
	std::vector<std::vector<double>> ExportVector() const;
	int size() const;
	void print() const;
};
