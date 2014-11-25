#pragma once
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>

class LayerOfEigenvector
{
public:
	LayerOfEigenvector();
	explicit LayerOfEigenvector(int numberOfElements);
	LayerOfEigenvector(std::vector<std::vector<double>> &vec);
	~LayerOfEigenvector();
	LayerOfEigenvector GetLayer(int NumberOfCombination);
	void push_back(const std::vector<double> &vec);
	std::vector<std::vector<double>> ExportVector() const;
	int size() const;
	void print() const;
	std::vector<std::vector<double>> GetVector() const;

public:
	static int NumberOfSamplesIn1stLayerVEC;
	static int MultipleOfAdjacentLayer;
	static int NumberOfLayer;
	static int SizeOfEigenvector;

private:
	std::vector<double> DivideByCombination(const std::vector<double> &num)const;

private:
	std::vector <std::vector<double>> m_VEigenvector;
	double m_Combination;
};
