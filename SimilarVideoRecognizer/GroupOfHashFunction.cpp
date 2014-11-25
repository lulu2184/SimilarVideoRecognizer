#include "stdafx.h"
#include "GroupOfHashFunction.h"
#include "LayerOfEigenvector.h"
#include <cassert>
#include <fstream>

std::function<double()> HashFunction::ms_diceGauss
= std::bind(
std::normal_distribution<double>(0.0f, 1.0f),
std::default_random_engine(static_cast<unsigned int>(time(nullptr)))
);

std::function<double()> HashFunction::ms_diceUniform
= std::bind(
std::uniform_real_distribution<double>(0.0f, 1.0f),
std::default_random_engine(static_cast<unsigned int>(time(nullptr)))
);

const int GroupOfHashFunction::FunctionsPerGroup;
const int GroupOfHashFunction::NumberOfFunctionGroups;

double HashFunction::m_parameterW = 3.0;

HashFunction::HashFunction()
{
	m_ParameterA.resize(LayerOfEigenvector::SizeOfEigenvector);
	std::generate(m_ParameterA.begin(), m_ParameterA.end(), std::ref(ms_diceGauss));
	m_ParameterB = ms_diceUniform(); 
}

HashFunction::HashFunction(const std::vector<double> &a, double b)
{
	m_ParameterA = a;
	m_ParameterB = b;
}

void HashFunction::SetParameter(const std::vector<double> &a, double b)
{
	m_ParameterA = a;
	m_ParameterB = b;
}

HashFunction::~HashFunction()
{

}

double HashFunction::CalculateDotProduct(const std::vector<double> &A, const std::vector<double> &B)
{
	assert(A.size() == B.size());
	double ret = 0;
	for (auto iterOfA = A.cbegin(), iterOfB = B.cbegin(); iterOfA != A.cend(); ++iterOfA, ++iterOfB)
	{
		ret += (*iterOfA) * (*iterOfB);
	}
	return ret;
}

int HashFunction::CalculateHashValue(const std::vector<double> &VariateX)
{
	return (int)((CalculateDotProduct(m_ParameterA, VariateX) + m_ParameterB) / m_parameterW);
}


GroupOfHashFunction::GroupOfHashFunction()
{
	m_ArrayOfFunctions.reserve(FunctionsPerGroup);
	for (int i = 0; i < FunctionsPerGroup; ++i)
	{
		HashFunction tmp;
		m_ArrayOfFunctions.push_back(std::move(tmp));
	}
}

GroupOfHashFunction::GroupOfHashFunction(const std::vector<std::vector<double>> &a, const std::vector<double> &b)
{
	assert(a.size() == b.size());
	m_ArrayOfFunctions.reserve(b.size());
	auto iterB = b.begin();
	for (auto iterA = a.cbegin(); iterA != a.cend(); ++iterA, ++iterB)
	{
		HashFunction tmp(*iterA, *iterB);
		m_ArrayOfFunctions.push_back(std::move(tmp));
	}
}

void GroupOfHashFunction::SetParameter(const std::vector<std::vector<double>> &a, const std::vector<double> &b)
{
	assert(a.size() == b.size() && a.size() == m_ArrayOfFunctions.size());
	m_ArrayOfFunctions.reserve(b.size());
	auto iterB = b.begin();
	auto iterfun = m_ArrayOfFunctions.begin();
	for (auto iterA = a.begin(); iterA != a.end(); ++iterA, ++iterB, ++iterfun)
	{
		iterfun->SetParameter(*iterA, *iterB);
	}
}


GroupOfHashFunction::~GroupOfHashFunction()
{
}

std::vector<int> GroupOfHashFunction::GetHashVector(const std::vector<double> &OSIDVec)
{
	std::vector<int> hashvector;
	hashvector.reserve(FunctionsPerGroup);
	for (int i = 0; i < FunctionsPerGroup; ++i)
	{
		hashvector.push_back(m_ArrayOfFunctions[i].CalculateHashValue((OSIDVec)));
	}
	return std::move(hashvector);
}

void HashFunction::diceGaussForVector(std::vector <double> &vec)
{
	std::generate(vec.begin(), vec.end(), std::ref(ms_diceGauss));
}

void GroupOfHashFunction::Print(std::ofstream &ofs)
{
	for (auto iter = m_ArrayOfFunctions.begin(); iter != m_ArrayOfFunctions.end(); ++iter)
	{
		iter->Print(ofs);
	}
}

void HashFunction::Print(std::ofstream &ofs)
{
	std::copy(m_ParameterA.begin(), m_ParameterA.end(), std::ostream_iterator<double>(ofs, " "));
	ofs << m_ParameterB << " " << m_parameterW << std::endl;
}