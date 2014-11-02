#include "stdafx.h"
#include "SampleExtracter.h"
#include <iostream>
#include <sstream>
#include <windows.h>
#include <tchar.h>


SampleExtracter::SampleExtracter(const std::string &filepath, int gaplength)
{
	m_VideoCapture.open(filepath);
	assert(m_VideoCapture.isOpened());
	m_LengthOfGap = gaplength;
}


SampleExtracter::~SampleExtracter()
{

}

TCHAR *SampleExtracter::str2pTCHAR(const std::string &str)
{
	TCHAR *ret = new TCHAR[str.size() + 1];
//	lstrcpy(ret, str.GetBuffer(str.size()));
//	str.ReleaseBuffer();
	return ret;
}

bool SampleExtracter::IsValidOutputPath(const std::string &outputpath)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
//	TCHAR *tpath = str2pTCHAR(outputpath);
	LPCWSTR path = (LPCWSTR) outputpath.c_str();
	hFind = FindFirstFile(path, &FindFileData);
	if (INVALID_HANDLE_VALUE == hFind)
	{
		std::cout << CreateDirectory(path, NULL) << std::endl;
		return true;
	}
	else
	{
		char ch;
		std::cout << "The Directory exists. If there is a conflict in it, do you want to cover the old one." << std::endl;
		std::cout << "y or n?" << std::endl;
		std::cin >> ch;
		return ch == 'y';
	}
}

std::string SampleExtracter::Num2Str(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

void SampleExtracter::SaveSampleImageAsFile(const std::string &outputpath, TypeOfGettingSample sampleType)
{
	if (!IsValidOutputPath(outputpath)) return;
	std::vector <cv::Mat> sampleVector = GetSampleImageVector(sampleType);
	std::vector <cv::Mat>::iterator it;
	int count = 0;
	imwrite(outputpath + '\\' + "begin.jpg", sampleVector[0]);
	for (it = sampleVector.begin(); it != sampleVector.end(); ++it)
	{
		++count;
		imwrite(outputpath + '\\' + Num2Str(count) + ".jpg", *it);
	}
}

void SampleExtracter::SetLengthOfGap(int gaplength)
{
	m_LengthOfGap = gaplength;
}

std::vector <int> SampleExtracter::GetSampleFrameNumberVector(TypeOfGettingSample sampleType)
{
	int totalFrameNumber = (int)m_VideoCapture.get(CV_CAP_PROP_FRAME_COUNT);
	std::vector <int> ret;
	int sampleNumber = (totalFrameNumber - 1) / m_LengthOfGap + 1;
	int bias = 0;
	for (int i = 0; i < sampleNumber; ++i)
	{
		if (sampleType == Randomly)
		{
			bias = rand() % min(m_LengthOfGap, (totalFrameNumber - m_LengthOfGap * i));
		}
		ret.push_back(m_LengthOfGap * i + bias);
	}
	return ret;
}

std::vector <cv::Mat> SampleExtracter::GetSampleImageVector(TypeOfGettingSample sampleType)
{
	m_VideoCapture.set(CV_CAP_PROP_POS_MSEC, 0);

	std::vector <cv::Mat> ret;
	std::vector <int> SampleFrameVector = GetSampleFrameNumberVector(sampleType);
	std::vector <int>::iterator it = SampleFrameVector.begin();
	cv::Mat image;
	int count = 0;

	while (m_VideoCapture.read(image))
	{
		if (SampleFrameVector.end() != it && count == *it)
		{
			ret.push_back(image.clone());
			++it;
		}
		++count;
	}
	return ret;
}
