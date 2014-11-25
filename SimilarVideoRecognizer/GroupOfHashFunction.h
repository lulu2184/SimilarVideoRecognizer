#pragma once
#include <vector>
#include <array>
#include <functional>
#include <random>
#include <ctime>


class HashFunction;

class GroupOfHashFunction
{
public:
	GroupOfHashFunction();
	GroupOfHashFunction(const std::vector<std::vector<double>> &a, const std::vector<double> &b);
	~GroupOfHashFunction();
	void Print(std::ofstream &ofs);
	void SetParameter(const std::vector<std::vector<double>> &a, const std::vector<double> &b);
	std::vector <int> GetHashVector(const std::vector<double> &OSIDVec);

	static const int FunctionsPerGroup = 40;
	static const int NumberOfFunctionGroups = 3;

private:
	std::vector <HashFunction> m_ArrayOfFunctions;
};

class HashFunction
{
public:
	HashFunction();
	HashFunction(const std::vector <double> &a, double b);
	~HashFunction();
	void Print(std::ofstream &ofs);
	void SetParameter(const std::vector<double> &a, double b);
	int CalculateHashValue(const std::vector<double> &VariateX);

protected:
	static void diceGaussForVector(std::vector <double> &vec);

private:
	double CalculateDotProduct(const std::vector<double> &A, const std::vector<double> &B);

private:
	static std::function<double()> ms_diceGauss;
	static std::function<double()> ms_diceUniform;
	static double m_parameterW;
	std::vector <double> m_ParameterA;
	double m_ParameterB;
};
