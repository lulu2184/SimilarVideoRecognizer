#include "stdafx.h"
#include "GroupOfHashValueVector.h"


GroupOfHashValueVector::GroupOfHashValueVector()
{
}


GroupOfHashValueVector::~GroupOfHashValueVector()
{
}

void GroupOfHashValueVector::GenerateHashValue(const std::vector<double> &OSIDVector)
{
	m_HashValue = HashValueGenerator::GetInstance()->GetHashValue(OSIDVector);
}

std::vector<int> GroupOfHashValueVector::GetVector(int groupID) const
{
	assert(groupID >= 0 && groupID < GroupOfHashFunction::NumberOfFunctionGroups);
	return m_HashValue[groupID];
}

std::vector<std::vector<int>> LayerOfHashValue::GetVector(int groupID) const
{
	assert(groupID >= 0 && groupID < GroupOfHashFunction::NumberOfFunctionGroups);
	std::vector<std::vector<int>> ret;
	for (auto iter = m_HashValue.cbegin(); iter != m_HashValue.cend(); ++iter)
	{
		ret.push_back(iter->GetVector(groupID));
	}
	return ret;
}

LayerOfHashValue::LayerOfHashValue()
{

}

LayerOfHashValue::~LayerOfHashValue()
{

}

void LayerOfHashValue::GenerateHashValue(const LayerOfEigenvector &eigenvector)
{
	m_HashValue.reserve(eigenvector.size());
	GroupOfHashValueVector tmp;
	std::vector<std::vector<double>> vec = eigenvector.GetVector();
	for (auto element = vec.cbegin(); element != vec.cend(); ++element)
	{
		tmp.GenerateHashValue(*element);
		m_HashValue.push_back(tmp);
	}
}

void GroupOfHashValueVector::print(std::ofstream &ofs)
{
	for (auto iter = m_HashValue.cbegin(); iter != m_HashValue.cend(); ++iter)
	{
		std::copy(iter->begin(), iter->end(), std::ostream_iterator<int>(ofs, " "));
		ofs << std::endl;
	}
	ofs << std::endl;
}

void LayerOfHashValue::print(std::ofstream &ofs)
{
	ofs << m_HashValue.size() << std::endl;
	for (auto iter = m_HashValue.begin(); iter != m_HashValue.end(); ++iter)
	{
		iter->print(ofs);
	}
}