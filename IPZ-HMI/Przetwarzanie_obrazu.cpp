#include "Przetwarzanie_obrazu.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <SFML/Network.hpp>
#include <mutex>

#define PI 3.1415 

using namespace cv;
using namespace std;


struct Config {
	int MinAngle;
	int MaxAngle;
	int MidLeft;
	int MidRight;
	int LowHue;
	int HighHue;
	int LowSat;
	int HighSat;
	int LowVal;
	int HighVal;
	int HoughVot;
	int Fill;
	int Destr;
};


Przetwarzanie_obrazu::Przetwarzanie_obrazu()
{

	iLowH = 32;
	iHighH = 77;
	iLowS = 68;
	iHighS = 255;
	iLowV = 91;
	iHighV = 255;
	max_angle = 180;
	min_angle = 0;
	mid_angle_left = 70;
	mid_angle_right = 20;
	point_height = 2;
	cut_off = 0.5;
	houghVote_left = 60;
	houghVote_right = 60;
	size_destruct = 5;
	size_fill = 5;

	files = fopen("plik.txt", "w");
	if (!files) {
		cout << "Problem z otwaciem ";
	}

	isStarted = true;
}


Przetwarzanie_obrazu::~Przetwarzanie_obrazu()
{
	fclose(files);
}


void Przetwarzanie_obrazu::average(float Eps_rho = 8, float Eps_theta = 0.05) {
	float bufor_theta = 0, bufor_rho = 0;
	int number = 0;
	int begin = 0;
	while (begin < lines.size()) {
		bufor_rho = 0;
		bufor_theta = 0;
		number = 0;
		float rho = lines[begin][0];
		float theta = lines[begin][1];
		//std::cout << "line: (" << rho << "," << theta << ")\n";
		int i = lines.size();
		--i;
		while (i != begin) {
			float rho = lines[i][0];
			float theta = lines[i][1];
			//std::cout << "line: (" << rho << "," << theta << ")\n";
			//cout << abs((*it)[0] - (*i)[0]) << "  " << abs((*it)[1] - (*i)[1]) << endl;
			if (abs(lines[begin][0] - lines[i][0]) <= Eps_rho && abs(lines[begin][1] - lines[i][1]) <= Eps_theta) {
				bufor_rho += lines[i][0];
				bufor_theta += lines[i][1];
				number++;
				lines.erase(lines.begin() + i);
				//cout << "erase" << endl;
			}
			--i;
		}
		if (number) {
			bufor_rho = (bufor_rho + lines[begin][0]) / (number + 1);
			bufor_theta = (bufor_theta + lines[begin][1]) / (number + 1);
			cv::Vec2f bufor = { bufor_rho,bufor_theta };
			lines.erase(lines.begin() + begin);
			lines.insert(lines.begin() + begin, 1, bufor);
		}
		++begin;
	}
	//cout << lines.size() << endl;
}


void Przetwarzanie_obrazu::show(bool prze)
{
	if (prze) {
		cv::imshow("roil", roi_left);
		cv::imshow("roip", roi_right);
	}
	cv::imshow("result", result);
	//cv::imshow("hough", hough);
	//cv::imshow("image", imgOriginal);
	//cv::imshow("Contours", drawing);
	cv::imshow("Thresholded Image", imgThresholded); //show the thresholded image
													 //cv::imshow("Original", imgOriginal); //show the original image
}

cv::Mat * Przetwarzanie_obrazu::getOriginal()
{
	return &imgOriginal;
}

cv::Mat * Przetwarzanie_obrazu::getResults()
{
	return &imgResult;
}

cv::Mat* Przetwarzanie_obrazu::getThreshholded()
{
	return &imgThresholded;
}

bool Przetwarzanie_obrazu::getStarted()
{
	return isStarted;
}

void Przetwarzanie_obrazu::changeTest(bool change)
{
	isStarted = change;
}

int Przetwarzanie_obrazu::getNumber()
{
	return Number;
}


sf::Int16 Przetwarzanie_obrazu::Przetwarzanie()
{
	sf::Int16 value = 0;
	std::vector<Vec2f> lines_left;
	std::vector<Vec2f> lines_right;
	roi_left = contours1(Rect(0, 0, int(float(contours1.cols) *cut_off), imgOriginal.rows));
	roi_right = contours1(Rect(int(float(contours1.cols) *(1 - cut_off)), 0, int(float(contours1.cols)*cut_off), imgOriginal.rows));
	lines = lines_left;
	this->number_of_lines(&houghVote_left, &roi_left, min_angle, mid_angle_left, true);
	lines_left = lines;
	lines = lines_right;
	this->number_of_lines(&houghVote_right, &roi_right, mid_angle_right, max_angle, false);
	lines_right = lines;
	std::cout << "houghVote" << houghVote_left << " " << houghVote_right << "\n";
	std::cout << "lines" << lines_left.size() << "lines1" << lines_right.size() << "\n";
	std::cout << "min " << min_angle * PI / 180 << ", max" << max_angle * PI / 180 << "\n";
	//fprintf(files, "houghVote %d %d lines %d lines1 %d min %f max %f", houghVote_left, houghVote_right, lines_left.size(), lines_right.size(), min_angle * PI / 180, max_angle * PI / 180);
	imgOriginal.copyTo(result);

	if (lines_left.size() < 30) {
		lines = lines_left;
		average(10, 1.5);
		lines_left = lines;
	}
	if (lines_right.size() < 30) {
		lines = lines_right;
		average(10, 1.5);
		lines_right = lines;
	}

	unsigned __int64 begin = 0;
	Mat hough(imgOriginal.size(), CV_8U, Scalar(0));
	Vec2f closest;
	float min_distance_left = float(result.cols) / 2;
	while (begin < lines_left.size()) {

		float rho = lines_left[begin][0];   // first element is distance rho
		float theta = lines_left[begin][1]; // second element is angle theta
		float a = -(cos(theta) / sin(theta));
		float b = rho / sin(theta);
		float dist = (result.cols / 2) - ((result.rows / point_height) - b) / a;
		//cout << dist << endl;
		if (min_distance_left > dist && dist > 0) {
			min_distance_left = dist;
		}
		//cout << min_distance_left << endl;
		fprintf(files, "line: (%f,%f) \n", dist, min_distance_left);
		// point of intersection of the line with first row	
		Point pt1(int(rho / cos(theta)), 0);
		// point of intersection of the line with last row
		Point pt2(int((rho - result.rows*sin(theta)) / cos(theta)), result.rows);
		// draw a white line

		line(result, pt1, pt2, Scalar(255), 8);
		line(hough, pt1, pt2, Scalar(255), 8);
		//}
		//std::cout << "line: (" << rho << "," << theta << ")\n";
		fprintf(files, "line: (%f,%f) \n", rho, theta);

		++begin;
	}
	begin = 0;
	float min_distance_right = float(result.cols) / 2;
	while (begin < lines_right.size()) {

		float rho = lines_right[begin][0];   // first element is distance rho
		float theta = lines_right[begin][1]; // second element is angle theta
		float a = -(cos(theta) / sin(theta));
		float b = rho / sin(theta);
		float dist = (0.5f - cut_off)*contours1.cols + ((result.rows / point_height) - b) / a;
		//cout << dist << endl;
		if (min_distance_right > dist && dist > 0) {
			min_distance_right = dist;
		}
		//cout << min_distance_right << endl;
		fprintf(files, "line: (%f,%f) \n", dist, min_distance_right);

		//if (theta < 30.*PI / 180. || theta > 150.*PI / 180.) { //     filter theta angle to find lines with theta between 30 and 150 degrees (mostly vertical)

		// point of intersection of the line with first row
		Point pt1(int(rho / cos(theta) + contours1.cols*(1 - cut_off)), 0);
		// point of intersection of the line with last row
		Point pt2(int((rho - result.rows*sin(theta)) / cos(theta) + contours1.cols*(1 - cut_off)), result.rows);
		// draw a white line
		line(result, pt1, pt2, Scalar(255), 8);
		line(hough, pt1, pt2, Scalar(255), 8);
		//}
		//std::cout << "line: (" << rho << "," << theta << ")\n";
		fprintf(files, "line: (%f,%f) \n", rho, theta);
		++begin;
	}

	Point x1(result.cols / 2, 0);
	Point x2(result.cols / 2, result.rows);
	Point midle;
	line(result, x1, x2, Scalar(255), 8);
	x1 = { int((result.cols / 2) - min_distance_left),result.rows / point_height };
	x2 = { int((result.cols / 2) + min_distance_right),result.rows / point_height };
	midle = (x1 + x2) / 2;
	circle(result, midle, 10, Scalar(0, 0, 255), -1);
	line(result, x1, x2, Scalar(255), 8);
	value = midle.x - (result.cols / 2);
	std::mutex mtx;
	mtx.lock();
	update2(this->result);
	update3(this->imgThresholded);
	mtx.unlock();
	return value;
}


void Przetwarzanie_obrazu::setup()
{
	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
	namedWindow("Control1", CV_WINDOW_AUTOSIZE);
	cvCreateTrackbar("max", "Control1", &max_angle, 180); //Hue (0 - 179)
	cvCreateTrackbar("min", "Control1", &min_angle, 90);
	cvCreateTrackbar("mid_left", "Control1", &mid_angle_left, 90);
	cvCreateTrackbar("mid_right", "Control1", &mid_angle_right, 90);
	cvCreateTrackbar("fill", "Control", &size_fill, 10);
	cvCreateTrackbar("destr", "Control", &size_destruct, 10);
	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);
	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);
	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	//cvCreateTrackbar("houghVotel", "Control1", &houghVote_left, 400);
	cvCreateTrackbar("houghVoter", "Control1", &houghVote_right, 400);
	cvCreateTrackbar("fill", "Control1", &size_fill, 10);
	cvCreateTrackbar("destr", "Control1", &size_destruct, 10);
}


void Przetwarzanie_obrazu::number_of_lines(int* houghVote, cv::Mat* roi, int min, int max, bool left)
{
	if (*houghVote < 100 || lines.size() > 2) { // we lost all lines. reset
		*houghVote = 200;
	}
	else { *houghVote += 25; }
	while (lines.size() < 5 && *houghVote > 0) {
		if (left) {
			HoughLines(*roi, lines, 1, 3.1415 / 180, *houghVote, 0.0, 0.0, min*PI / 180, max*PI / 180);
		}
		else {
			HoughLines(*roi, lines, 1, 3.1415 / 180, *houghVote, 0.0, 0.0, (90 + min)*PI / 180, max*PI / 180);
		}
		*houghVote -= 5;
		if (lines.size() > 20) {
			*houghVote += 25;
		}
	}
}


bool Przetwarzanie_obrazu::zeros(float min)
{
	float zero = float(countNonZero(contours1));
	cout << "zeros: " << zero / (contours1.cols*contours1.rows) << endl;
	fprintf(files, "zeros: %f", zero / (contours1.cols*contours1.rows));
	if (zero / (contours1.cols*contours1.rows) < 0.01) {
		return true;
	}
	else {
		return false;
	}
}


void Przetwarzanie_obrazu::tresh()
{
	roi = imgOriginal(Rect(imgOriginal.cols * 1 / 10, imgOriginal.rows * 2 / 5, imgOriginal.cols * 8 / 10, imgOriginal.rows / 2));
	imgOriginal = roi;

	Mat imgHSV;
	cvtColor(roi, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
																								  //morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(size_destruct, size_destruct)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(size_destruct, size_destruct)));
	//morphological closing (fill small holes in the foreground)
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(size_fill, size_fill)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(size_fill, size_fill)));

	//--- Tworzenie konturów
	/*std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Point> contours_poly;
	cv::Rect boundRect;
	cv::Mat cont;
	imgThresholded.copyTo(cont);
	*/
	/*
	findContours(cont, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	int max = 100, i_cont = 0;
	cv::Mat drawing = cv::Mat::zeros(cont.size(), CV_8UC3);

	std::vector<int> indexes;

	for (int i = 0; i < contours.size(); i++)
	{
	if (abs(cv::contourArea(cv::Mat(contours[i]))) > max)
	{
	indexes.push_back(i);
	}
	}
	std::cout << "Ilosc: " << indexes.size() << std::endl;
	if (indexes.size() >= 0)
	{
	for (auto index : indexes) {
	approxPolyDP(cv::Mat(contours[index]), contours_poly, 3, true);
	boundRect = cv::boundingRect(cv::Mat(contours_poly));
	fillConvexPoly(imgOriginal, contours_poly, contours_poly.size());
	rectangle(imgOriginal, boundRect.tl(), boundRect.br(), cv::Scalar(125, 250, 125), 2, 8, 0);
	line(imgOriginal, boundRect.tl(), boundRect.br(), cv::Scalar(250, 125, 125), 2, 8, 0);
	line(imgOriginal, cv::Point(boundRect.x + boundRect.width, boundRect.y), cv::Point(boundRect.x, boundRect.y + boundRect.height), cv::Scalar(250, 125, 125), 2, 8, 0);
	drawContours(drawing, contours, index, cv::Scalar(125, 125, 250), 2);
	}
	}*/

	contours1 = imgThresholded;
	//Canny(imgThresholded, contours1, 50, 350);
	//Mat contoursInv;
	//threshold(drawing, contours1, 128, 255, THRESH_BINARY_INV);
}


void Przetwarzanie_obrazu::update(cv::Mat imgOriginal)
{
	this->imgOriginal = imgOriginal;
}

void Przetwarzanie_obrazu::update2(cv::Mat imgOriginal)
{
	imgResult = imgOriginal;
}

void Przetwarzanie_obrazu::update3(cv::Mat imgOriginal)
{
	imgThresh = imgOriginal;
}


int Przetwarzanie_obrazu::start(string ip, unsigned short port)
{

	//test
	sf::UdpSocket socket;
	socket.setBlocking(false);
	sf::Packet packet;
	sf::Int16 value = 0;
	packet << value;
	sf::IpAddress recipient = ip;

	VideoCapture cap(0);
	//VideoCapture cap("http://"+ip+":8080/stream/video.mjpeg"); //capture the video from web cam


	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Cannot open the web cam" << endl;
		system("pause");
		return -1;
	}
	//this->setup();
	while (true) {
		bool bSuccess = cap.read(imgOriginal); // read a new frame from video
		if (!bSuccess) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}
		//wysylanie
		this->update(imgOriginal);
		this->tresh();
		imgOriginal.copyTo(result);
		if (this->zeros(0.001f)) {
			value = 1000;
			//show(0);
		}
		else {
			value = this->Przetwarzanie();
			//show(1);
		}
		std::mutex mtx;
		mtx.lock();
		update2(this->result);
		update3(this->imgThresholded);
		mtx.unlock();


		packet.clear();
		packet << value;
		if (socket.send(packet, recipient, port) != sf::Socket::Done)
		{
			std::cout << "Some error" << std::endl;
			return 12;
		}
		//koniec wysylania

		//waitKey(0);
		if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			value = 1000;
			packet.clear();
			packet << value;
			if (socket.send(packet, recipient, port) != sf::Socket::Done)
			{
				std::cout << "Some error" << std::endl;
				return 12;
			}
			cout << "esc key is pressed by user" << endl;
			break;
			return 1;
		}
	}
}


void Przetwarzanie_obrazu::Parameters_load(struct Config p)
{
	iLowH = p.LowHue;
	iHighH = p.HighHue;
	iLowS = p.LowSat;
	iHighS = p.HighSat;
	iLowV = p.LowVal;
	iHighV = p.HighVal;
	max_angle = p.MaxAngle;
	min_angle = p.MinAngle;
	mid_angle_left = p.MidLeft;
	mid_angle_right = p.MidRight;
	houghVote_left = p.HoughVot;
	houghVote_right = p.HoughVot;
	size_destruct = p.Destr;
	size_fill = p.Fill;
}


struct Config Przetwarzanie_obrazu::Parameters_check()
{
	struct Config p;
	p.LowHue = iLowH;
	p.HighHue = iHighH;
	p.LowSat = iLowS;
	p.HighSat = iHighS;
	p.LowVal = iLowV;
	p.HighVal = iHighV;
	p.MaxAngle = max_angle;
	p.MinAngle = min_angle;
	p.MidLeft = mid_angle_left;
	p.MidRight = mid_angle_right;
	p.HoughVot = houghVote_left;
	p.Destr = size_destruct;
	p.Fill = size_fill;
	return p;
}


