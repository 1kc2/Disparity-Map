#include "opencv2/opencv.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#define OUTFILE "disparity.png"
#define OCCLUSION 3.84

using namespace std;

int read_images(cv::Mat &left, cv::Mat &right, int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "Too many argmuents - give paths of the stereo pair" << endl;
		return -1;
	}
	left = imread(argv[1], cv::IMREAD_GRAYSCALE);
	if (left.empty())
	{
		cout << "Cannot find left.png" << endl;
		return -1;
	}
	right = imread(argv[2], cv::IMREAD_GRAYSCALE);
	if (right.empty())
	{
		cout << "Cannot find right.png" << endl;
		return -1;
	}
	return 0;
}

double min(double a, double b, double c)
{
	if ( (a < b) && (a < c) ) return a;
	else if (b < c)	return b;
	else return c;
}

double sqr(double a)
{
	return a * a;
}

cv::Mat generate_map(cv::Mat left, cv::Mat right)
{
	// Assume left and right have the exact same size
	int img_width = left.cols;
	int img_height = left.rows;
	cv::Mat disparity_map(img_height, img_width, CV_8UC1);
	for (int line = 0; line < img_height; line++)
	{
		double **cost_matrix = new double *[img_width + 1];
		for (int i = 0; i < img_width+1; i++) cost_matrix[i] = new double[img_width + 1];
		
		cost_matrix[0][0] = 0.0;
		for (int i = 1; i < img_width+1; i++)
		{
			cost_matrix[i][0] = i * OCCLUSION;
			cost_matrix[0][i] = i * OCCLUSION;
		}
		for (int i = 1; i < img_width + 1; i++) 
			for (int j = 1; j < img_width + 1; j++)
			{
				int left_pixel = left.at<uchar>(line, i - 1);
				int right_pixel = right.at<uchar>(line, j - 1);
				
				double no_occlusion = cost_matrix[i - 1][j - 1] + 1.0/64 * sqr((double)(right_pixel - left_pixel));
				double i_occlusion = cost_matrix[i - 1][j] + OCCLUSION;
				double j_occlusion = cost_matrix[i][j - 1] + OCCLUSION;
				cost_matrix[i][j] = min(no_occlusion, i_occlusion, j_occlusion);
			}
		int i = img_width, j = img_width;
		int cost_val = cost_matrix[img_width][img_width];
		while ((i > 0) && (j > 0))
		{ 
			int left_pixel = left.at<uchar>(line, i - 1);
			int right_pixel = right.at<uchar>(line, j - 1);

			if (cost_matrix[i][j] == cost_matrix[i - 1][j] + OCCLUSION)
			{
				disparity_map.at<uchar>(line, i - 1) = 0;
				i--;
			}
			else if (cost_matrix[i][j] == cost_matrix[i][j - 1] + OCCLUSION) j--;
			else
			{
				disparity_map.at<uchar>(line, i - 1) = abs(i - j);	
				cost_val -= 1.0/64 * sqr((double)(right_pixel - left_pixel));
				i--;
				j--;
			}
		}
		for (int i = 0; i <= img_width; i++) delete [] cost_matrix[i];
		delete [] cost_matrix;
		
	}
	return disparity_map;
}

int main(int argc, char **argv)
{
	cv::Mat left, right;
	if (read_images(left, right, argc, argv)) return -1;
	cv::Mat disparity_img = generate_map(left, right);
	cv::normalize(disparity_img, disparity_img, 0, 255, cv::NORM_MINMAX, CV_8UC1);
	cv::fastNlMeansDenoising(disparity_img, disparity_img, 7, 7, 21);
	cv::imwrite(OUTFILE, disparity_img);
	return 0;
}