#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <SFML/Network.hpp>
#include <fstream>

class Przetwarzanie_obrazu
{
public:
	Przetwarzanie_obrazu();
	~Przetwarzanie_obrazu();
	sf::Int16 Przetwarzanie();
	void setup();
	void number_of_lines(int*, cv::Mat*, int, int, bool);
	bool zeros(float min);
	void tresh();
	void update(cv::Mat imgOriginal);
	void update2(cv::Mat imgOriginal);
	void update3(cv::Mat imgOriginal);
	int start(std::string, unsigned short);
	void Parameters_load(struct Config);
	struct Config Parameters_check();
	void show(bool);
	cv::Mat* getOriginal();
	cv::Mat* getResults();
	cv::Mat* getThreshholded();
	bool getStarted();
	void changeTest(bool change);
	int getNumber();
private:
	bool Test;
	bool isStarted;
	int Number;
	cv::Mat roi;
	cv::VideoCapture cap;
	cv::Mat imgOriginal;
	cv::Mat roi_left;
	cv::Mat roi_right;
	cv::Mat contours1;
	cv::Mat imgThresholded;
	cv::Mat result;
	cv::Mat imgResult;
	cv::Mat imgThresh;
	int iLowH;
	int iHighH;
	int iLowS;
	int iHighS;
	int iLowV;
	int iHighV;
	int max_angle;
	int min_angle;
	int mid_angle_left;
	int mid_angle_right;
	int point_height;
	float cut_off;
	int houghVote_left;
	int houghVote_right;
	int size_destruct;
	int size_fill;
	void average(float, float);
	FILE* files;
	std::vector<cv::Vec2f> lines;
};
