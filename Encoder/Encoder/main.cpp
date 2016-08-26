#include <opencv2/opencv.hpp>
#include "ArgsParser.h"
#include "WinUtils.h"

int main(int argn, char** args)
{
	ArgsParser parser(argn, args);
	double fps = 29.97;
	double resizeScale = 1.0;
	int endFrame = -1;
	int startFrame = 0;
	int trimEnd = 0;
	std::string fourcc = "H264";
	std::string filePattern = "*.png";
	std::string inputDir;
	std::string outputFile;

	if (!parser.TryGetArgment("inputDir", inputDir))
	{
		printf("Options and default values in []:\n");
		printf("\t-inputDir (required)\n");
		printf("\t-outputFile [inputDir\\output.avi]\n");
		printf("\t-filePattern [%s]\n", filePattern.c_str());
		printf("\t-fps [%lf]\n", fps);
		printf("\t-resizeScale [%lf]\n", resizeScale);
		printf("\t-startFrame [%d]\n", startFrame);
		printf("\t-endFrame [%d]\n", endFrame);
		printf("\t-trimEnd [%d]\n", trimEnd);
		printf("\t-fourcc [%s]\n", fourcc.c_str());
		return 0;
	}
	outputFile = inputDir + "\\output.avi";
	parser.TryGetArgment("outputFile", outputFile);
	parser.TryGetArgment("filePattern", filePattern);
	parser.TryGetArgment("fps", fps);
	parser.TryGetArgment("resizeScale", resizeScale);
	parser.TryGetArgment("startFrame", startFrame);
	parser.TryGetArgment("endFrame", endFrame);
	parser.TryGetArgment("trimEnd", trimEnd);
	parser.TryGetArgment("fourcc", fourcc);
	if (fourcc.size() < 4) {
		printf("fourcc (%s) must be 4 characters.\n", fourcc.c_str());
		return 1;
	};
	if (resizeScale <= 0){
		printf("resizeScale (%lf) must be a positive value.\n", resizeScale);
		return 1;
	}
	if (fps <= 0){
		printf("fps (%lf) must be a positive value.\n", fps);
		return 1;
	}
	if (startFrame >= endFrame && endFrame >= 0){
		printf("startFrame (%d) must be larger than endFrame (%d).\n", startFrame, endFrame);
		return 1;
	}

	auto files = WinUtil::GetFiles(inputDir + "\\", filePattern);
	if (files.size() == 0) {
		printf("No matched files were found in %s\\%s.\n", inputDir.c_str(), filePattern.c_str());
		return 1;
	}
	printf("%d matched files were found.\n", (int)files.size());

	if (startFrame >= files.size()){
		printf("startFrame (%d) exceeded the total frame number.\n", startFrame);
		return 1;
	}

	if (endFrame <= 0) endFrame = files.size();
	else endFrame = std::min(endFrame, (int)files.size());

	cv::Mat img = cv::imread(inputDir + "\\" + files[0]);
	if (resizeScale != 1.0)
		cv::resize(img, img, {}, resizeScale, resizeScale);

	cv::VideoWriter vw(outputFile, CV_FOURCC(fourcc[0], fourcc[1], fourcc[2], fourcc[3]), fps, img.size(), img.channels() == 3);
	if (!vw.isOpened()){
		printf("Could not open the output file [%s].\n", outputFile.c_str());
		return 1;
	}
	for (int i = startFrame; i < endFrame - trimEnd; i++)
	{
		cv::Mat img = cv::imread(inputDir + "\\" + files[i]);
		if (resizeScale != 1.0)
			cv::resize(img, img, {}, resizeScale, resizeScale);
		vw << img;
		printf("Wrote the %d-th frame: %s\n", i, files[i]);
	}
	printf("Successfully saved as %s.\n", outputFile.c_str());

	return 0;
}