#include "stdafx.h"
#include "SampleExtracter.h"
#include <direct.h>
#include <iostream>
#include <sstream>


SampleExtracter::SampleExtracter(const std::string &filepath, int gaplength)
{
	m_VideoCapture.open(filepath);
	assert(m_VideoCapture.isOpened());
	m_LengthOfGap = gaplength;
}


SampleExtracter::~SampleExtracter()
{

}

LPCWSTR SampleExtracter::StringToLPCWSTR(const std::string &str)
{
	int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, str.size());
	WCHAR *tmp = new WCHAR[len];
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, tmp, str.size());
	return tmp;
}

bool SampleExtracter::IsValidOutputPath(const std::string &outputpath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	LPCWSTR path = StringToLPCWSTR(outputpath);
	hFind = FindFirstFile(path, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		if (_mkdir(outputpath.c_str()) < 0)
		{
			std::cout << "Failed to create the directory" << std::endl;
			return false;
		}
		return true;
	}
	else
	{
		char ch;
		std::cout << "The Directory exists. If there is a conflict, do you want to cover the old one?" << std::endl;
		std::cout << "y or n?" << std::endl;
		std::cin >> ch;
		return ch == 'y';
	}
}

void SampleExtracter::SaveSampleImageAsFile(const std::string &outputpath, TypeOfGettingSample sampleType)
{
	if (!IsValidOutputPath(outputpath)) return;
	std::vector <cv::Mat> sampleVector = GetSampleImageVector(sampleType);
	int count = 0;
	for (auto it = sampleVector.cbegin(); it != sampleVector.cend(); ++it)
	{
		++count;
		imwrite(outputpath + '\\' + std::to_string(count) + ".jpg", *it);
	}
}

void SampleExtracter::SetLengthOfGap(int gaplength)
{
	m_LengthOfGap = gaplength;
}

std::vector <int> SampleExtracter::GetSampleFrameNumberVector(TypeOfGettingSample sampleType)
{
	int totalFrameNumber = (int)m_VideoCapture.get(CV_CAP_PROP_FRAME_COUNT);
	int sampleNumber = (totalFrameNumber - 1) / m_LengthOfGap + 1;
	std::vector <int> ret(sampleNumber);
	int bias = 0;
	for (int i = 0; i < sampleNumber; ++i)
	{
		if (Randomly == sampleType)
		{
			bias = rand() % min(m_LengthOfGap, (totalFrameNumber - m_LengthOfGap * i));
		}
		ret.push_back(m_LengthOfGap * i + bias);
	}
	return std::move(ret);
}

void SampleExtracter::ChangeBrightnessOfImage(cv::Mat &image, double rate)
{
	assert(rate > 0);
	auto iter = image.begin<cv::Vec3b>();
	while (iter != image.end<cv::Vec3b>())
	{
		//double tmp = min(255, *iter * rate);
		//*iter = (uchar)tmp;
		++iter;
	}

	/*for (int i = 0; i < image.rows; ++i)
	{
		uchar *p = image.ptr<uchar>(i);
		for (int j = 0; j < image.cols * image.channels(); ++j)
		{
			double tmp = min(255, p[j] * rate);
			p[j] = (uchar)tmp;
		}
	}*/
}



std::vector <cv::Mat> SampleExtracter::GetSampleImageVector(TypeOfGettingSample sampleType)
{
	m_VideoCapture.set(CV_CAP_PROP_POS_MSEC, 0);

	std::vector <int> SampleFrameVector = GetSampleFrameNumberVector(sampleType);
	std::vector <cv::Mat> ret(SampleFrameVector.size());
	auto it = SampleFrameVector.begin();
	cv::Mat image;
	int count = 0;

	while (m_VideoCapture.read(image))
	{
		//imwrite( "D:\\files\\output\\d"+  std::to_string(count) + ".jpg", image);
		if (SampleFrameVector.end() != it && count == *it)
		{
			ret.push_back(image.clone());
//			ChangeBrightnessOfImage(image, 0.5);
		//	imwrite( "D:\\files\\output\\"+  std::to_string(count/25) + ".jpg", image);
			++it;
		}
		++count;
	}
	count = 0;
	for (auto it = ret.cbegin(); it != ret.cend(); ++it)
	{
		++count;
		imwrite( "D:\\files\\output\\" + std::to_string(count) + ".jpg", *it);
	}
 	return std::move(ret);
}
