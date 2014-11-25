#include "stdafx.h"
#include <iostream>
#include "LayerOfEigenvector.h"
#include <fstream>

int LayerOfEigenvector::NumberOfSamplesIn1stLayerVEC = 10;
int LayerOfEigenvector::MultipleOfAdjacentLayer = 2;
int LayerOfEigenvector::NumberOfLayer = 3;
int LayerOfEigenvector::SizeOfEigenvector = 27;


LayerOfEigenvector::LayerOfEigenvector(int numberOfElements)
{
	m_VEigenvector.reserve(numberOfElements);
}

LayerOfEigenvector::LayerOfEigenvector(std::vector<std::vector<double>> &vec)
{
	m_VEigenvector = vec;
}

LayerOfEigenvector::~LayerOfEigenvector()
{
}

std::vector<std::vector<double>> LayerOfEigenvector::GetVector() const
{
	return m_VEigenvector;
}

void LayerOfEigenvector::print() const
{
	std::ofstream ofs("D:\\output\\1.txt", std::ofstream::app);
	int count = 0;
	ofs << m_VEigenvector.size() << std::endl;
	for (auto iter = m_VEigenvector.begin(); iter != m_VEigenvector.end(); ++iter)
	{
		++count;
		for (auto element = iter->begin(); element != iter->end(); ++element)
		{
			if (iter->begin() != element) ofs << " ";
			ofs << *element;
		}
		ofs << std::endl;
	}
	ofs << std::endl;
}

std::vector <double> LayerOfEigenvector::DivideByCombination(const std::vector<double> &Vec)const
{
	std::vector <double> ret;
	for (auto iter = Vec.begin(); iter != Vec.end(); ++iter)
	{
		ret.push_back(*iter / m_Combination);
	}
	return std::move(ret);
}

int LayerOfEigenvector::size() const
{
	return (int)m_VEigenvector.size();
}

LayerOfEigenvector LayerOfEigenvector::GetLayer(int NumberOfCombination)
{
	assert(m_VEigenvector.size());
	m_Combination = NumberOfCombination;
	int gap = NumberOfCombination / 2;
	int NumberOfElements = this->size() / gap - 1;

	LayerOfEigenvector Ret(NumberOfElements);
	int counter = 0;
	std::vector <double> tmpvec(SizeOfEigenvector, 0);

	for (auto iter = m_VEigenvector.cbegin(), LeftCursor = m_VEigenvector.cbegin(); iter != m_VEigenvector.cend(); ++iter)
	{
		std::transform(iter->begin(), iter->end(), tmpvec.begin(), tmpvec.begin(), std::plus<double>());
		if (counter >= NumberOfCombination)
		{
			std::transform(tmpvec.begin(), tmpvec.end(), LeftCursor->begin(), tmpvec.begin(), std::minus<double>());
			++LeftCursor;
		}
		if ((counter + 1) % gap == 0 && counter + 1 >= NumberOfCombination)
		{
			Ret.push_back(DivideByCombination(tmpvec));
		}
		++counter;
	}
	return std::move(Ret);
}

std::vector<std::vector<double>> LayerOfEigenvector::ExportVector()const
{
	return m_VEigenvector;
}

void LayerOfEigenvector::push_back(const std::vector<double> &vec)
{
	m_VEigenvector.push_back(vec);
}