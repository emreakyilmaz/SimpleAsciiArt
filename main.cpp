#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


void cvrtImtoAscii(Mat& img) {
	char asciiCharMap[10];
	asciiCharMap[0] = '.';
	asciiCharMap[1] = ',';
	asciiCharMap[2] = ':';
	asciiCharMap[3] = ';';
	asciiCharMap[4] = 'o';
	asciiCharMap[5] = 'x';
	asciiCharMap[6] = '%';
	asciiCharMap[7] = '#';
	asciiCharMap[8] = '@';
	asciiCharMap[9] = '_';

	Mat img8Bit;
	img8Bit = Mat::zeros(img.rows, img.cols, CV_8UC1);
	cvtColor(img, img8Bit, COLOR_BGR2GRAY);

	resize(img8Bit, img8Bit, Size(img.rows/3, img.cols/3));

	imshow("Test", img8Bit);
	waitKey(0);

	char** asciiImage = new char*[img.rows];
	for (int i = 0; i < img.rows; i++) {
		asciiImage[i] = new char[img.cols + 1];
	}

	unsigned char* imageArray;
	for (int y = 0; y < img8Bit.rows; y++) {
		imageArray = (unsigned char*)(img8Bit.data + y * img8Bit.step);
		for (int x = 0; x < img8Bit.cols; x++) {
			asciiImage[y][x] = asciiCharMap[(255 - imageArray[x]) * 10 / 256];
		}
		asciiImage[y][img.cols + 1] = '\n';
	}

	ofstream myfile;
	myfile.open("Lenna.txt");

	for (int y = 0; y < img8Bit.rows; y++) {
		for (int x = 0; x < img8Bit.cols; x++) {
			printf("%c", asciiImage[y][x]);
			myfile << asciiImage[y][x];
		}
		printf("%c", asciiImage[y][img.cols + 1]);
		myfile << asciiImage[y][img.cols + 1];
	}

	myfile.close();
	getchar();
}


int main() {

	Mat img = imread("Lenna.jpg", IMREAD_UNCHANGED);
	cvrtImtoAscii(img);
	imshow("Test", img);
	waitKey(0);

	return 0;
}
