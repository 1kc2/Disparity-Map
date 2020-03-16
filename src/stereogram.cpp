#include "opencv2/opencv.hpp"

#include <iostream>
#include <ctime>

#define A_SIZE 512
#define B_SIZE 256
#define OFFSET 4

using namespace std;

cv::Mat A(A_SIZE, A_SIZE, CV_8UC1);
cv::Mat B(B_SIZE, B_SIZE, CV_8UC1);
cv::Mat L(A_SIZE, A_SIZE, CV_8UC1);
cv::Mat R(A_SIZE, A_SIZE, CV_8UC1);

void generate_random_dots(cv::Mat &A, cv::Mat &B)
{
	srand(time(NULL));
	for (int i = 0; i < A_SIZE; i++)
		for (int j = 0; j < A_SIZE; j++)
		{ 
			int random = rand() % 2;
			A.at<uchar>(i, j) = random * 255;
		}
	for (int i = 0; i < B_SIZE; i++)
		for (int j = 0; j < B_SIZE; j++)
		{
			int random = rand() % 2;
			B.at<uchar>(i, j) = random * 255;
		}
}

void generate_left_right(cv::Mat A, cv::Mat B, cv::Mat &L, cv::Mat &R)
{
	L = A.clone();
	R = A.clone();
	int L_start = (A_SIZE - B_SIZE) / 2 - OFFSET;
	int R_start = (A_SIZE - B_SIZE) / 2 + OFFSET;
	int mid = (A_SIZE - B_SIZE) / 2;
	for (int i = mid; i < mid + B_SIZE; i++) 
		for (int j = L_start; j < L_start + B_SIZE; j++)
			L.at<uchar>(i, j) = B.at<uchar>(i - mid, j - L_start);
	for (int i = mid; i < mid + B_SIZE; i++) 
		for (int j = R_start; j < R_start + B_SIZE; j++)
			R.at<uchar>(i, j) = B.at<uchar>(i - mid, j - R_start);
}


int main(void)
{
	generate_random_dots(A, B);
	generate_left_right(A, B, L, R);
	cv::imwrite("left.png", L);
	cv::imwrite("right.png", R);
	return 0;
}