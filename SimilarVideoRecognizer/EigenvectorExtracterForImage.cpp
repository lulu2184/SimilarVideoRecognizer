#include "stdafx.h"
#include "EigenvectorExtracterForImage.h"

int EigenvectorExtracterForImage::SizeOfBlock = SizeOfNormalizedImage.height / NumberOfRowDivision*SizeOfNormalizedImage.width / NumberOfColDivision;
int EigenvectorExtracterForImage::ElementINABin = SizeOfNormalizedImage.height * SizeOfNormalizedImage.width / NumberOfBins;
int EigenvectorExtracterForImage::HeightOfBlock = SizeOfNormalizedImage.height / NumberOfRowDivision;
int EigenvectorExtracterForImage::WidthOfBlock = SizeOfNormalizedImage.width / NumberOfColDivision;

int EigenvectorExtracterForImage::NumberOfBins = 3;
int EigenvectorExtracterForImage::NumberOfRowDivision = 3;
int EigenvectorExtracterForImage::NumberOfColDivision = 3;
CvSize EigenvectorExtracterForImage::SizeOfNormalizedImage = { 198, 198 };

EigenvectorExtracterForImage::EigenvectorExtracterForImage()
{
}


EigenvectorExtracterForImage::~EigenvectorExtracterForImage()
{
}

std::vector<int> EigenvectorExtracterForImage::TransIntoOrdinal(const cv::Mat &mat)
{
	std::vector <int> count(257, 0);
	for (auto iter = mat.begin<unsigned char>(); iter != mat.end<unsigned char>(); ++iter)
	{
		count[int(*iter) + 1]++;
	}
	for (int i = 1; i < 256; i++)
	{
		count[i] += count[i - 1];
	}
	std::vector <int> ordinalvec;
	for (auto iter = mat.begin<unsigned char>(); iter != mat.end<unsigned char>(); ++iter)
	{
		ordinalvec.push_back(count[*iter]);
		++count[*iter];
	}
	return std::move(ordinalvec);
}

int EigenvectorExtracterForImage::GetHistogramNumber(int posnumber, int ordinalnumber)
{
	return GetSpaceNumber(posnumber) * NumberOfBins + GetBinNumber(ordinalnumber);
}

int EigenvectorExtracterForImage::GetBinNumber(int ordinalnumber)
{
	return ordinalnumber / ElementINABin;;
}

int EigenvectorExtracterForImage::GetSpaceNumber(int PosNumber)
{
	int coordinateX = PosNumber / SizeOfNormalizedImage.width;
	int coordinateY = PosNumber % SizeOfNormalizedImage.width;
	return coordinateX / HeightOfBlock * NumberOfColDivision + coordinateY / WidthOfBlock;
}

std::vector <double> EigenvectorExtracterForImage::GetHistogram(const std::vector<int> &ordinalvec)
{
	std::vector <double> ret(NumberOfRowDivision*NumberOfColDivision*NumberOfBins, 0);
	int PosNumber = 0;
	for (auto iter = ordinalvec.cbegin(); iter != ordinalvec.cend(); ++iter, ++PosNumber)
	{
		ret[GetHistogramNumber(PosNumber, *iter)] += 1.0;
	}
	return std::move(ret);
}

std::vector <double> EigenvectorExtracterForImage::GetEigenvector(const cv::Mat &image)
{
	cv::Mat tmp_mat;
	image.copyTo(tmp_mat);
	Prepare(tmp_mat);
	std::vector <int> OrdinalVector;
	OrdinalVector = TransIntoOrdinal(tmp_mat);
	std::vector <double> ret = GetHistogram(OrdinalVector);
	Normalize(ret);
	return ret;
}

void EigenvectorExtracterForImage::RemoveBlackBorder(cv::Mat &image)
{
	
}

int EigenvectorExtracterForImage::OutputFrameCounter = 0;

void EigenvectorExtracterForImage::Prepare(cv::Mat &image)
{
	RemoveBlackBorder(image);
	cvtColor(image, image, CV_BGR2GRAY);
	cv::resize(image, image, SizeOfNormalizedImage);
}

void EigenvectorExtracterForImage::Normalize(std::vector<double> &Vec)
{
	for (auto iter = Vec.begin(); iter != Vec.end(); ++iter)
	{
		*iter /= (double)SizeOfBlock;
	}
}
