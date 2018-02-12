#include <iostream>
#include <stdio.h>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "seed2des.h"

using namespace std;
using namespace cv;

int main()
{
	Mat demoImg = imread("lena_std.tif", CV_LOAD_IMAGE_COLOR);
	imshow("grayscale", demoImg);
	waitKey();
	seed2des(46, 230, 143, 344, demoImg, 1);
/*
	cout << allNode[0][0].linkcost[3] <<'\t'<< allNode[0][0].linkcost[2] <<'\t'<< allNode[0][0].linkcost[1] <<'\t'<< allNode[0][1].linkcost[3] <<'\t'<< allNode[0][1].linkcost[2] <<'\t'<< allNode[0][1].linkcost[1] <<'\t'<< allNode[0][2].linkcost[3] <<'\t'<< allNode[0][2].linkcost[2] <<'\t'<< allNode[0][2].linkcost[1] << endl;
	cout << allNode[0][0].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 0) <<'\t'<< allNode[0][0].linkcost[0] <<'\t'<< allNode[0][1].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 1) <<'\t'<< allNode[0][1].linkcost[0] <<'\t'<< allNode[0][2].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 2) <<'\t'<< allNode[0][2].linkcost[0] << endl;
	cout << allNode[0][0].linkcost[5] <<'\t'<< allNode[0][0].linkcost[6] <<'\t'<< allNode[0][0].linkcost[7] <<'\t'<< allNode[0][1].linkcost[5] <<'\t'<< allNode[0][1].linkcost[6] <<'\t'<< allNode[0][1].linkcost[7] <<'\t'<< allNode[0][2].linkcost[5] <<'\t'<< allNode[0][2].linkcost[6] <<'\t'<< allNode[0][2].linkcost[7] << endl;

	cout << allNode[1][0].linkcost[3] <<'\t'<< allNode[1][0].linkcost[2] <<'\t'<< allNode[1][0].linkcost[1] <<'\t'<< allNode[1][1].linkcost[3] <<'\t'<< allNode[1][1].linkcost[2] <<'\t'<< allNode[1][1].linkcost[1] <<'\t'<< allNode[1][2].linkcost[3] <<'\t'<< allNode[1][2].linkcost[2] <<'\t'<< allNode[1][2].linkcost[1] << endl;
	cout << allNode[1][0].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 0) <<'\t'<< allNode[1][0].linkcost[0] <<'\t'<< allNode[1][1].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 1) <<'\t'<< allNode[1][1].linkcost[0] <<'\t'<< allNode[1][2].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 2) <<'\t'<< allNode[1][2].linkcost[0] << endl;
	cout << allNode[1][0].linkcost[5] <<'\t'<< allNode[1][0].linkcost[6] <<'\t'<< allNode[1][0].linkcost[7] <<'\t'<< allNode[1][1].linkcost[5] <<'\t'<< allNode[1][1].linkcost[6] <<'\t'<< allNode[1][1].linkcost[7] <<'\t'<< allNode[1][2].linkcost[5] <<'\t'<< allNode[1][2].linkcost[6] <<'\t'<< allNode[1][2].linkcost[7] << endl;

	cout << allNode[2][0].linkcost[3] <<'\t'<< allNode[2][0].linkcost[2] <<'\t'<< allNode[2][0].linkcost[1] <<'\t'<< allNode[2][1].linkcost[3] <<'\t'<< allNode[2][1].linkcost[2] <<'\t'<< allNode[2][1].linkcost[1] <<'\t'<< allNode[2][2].linkcost[3] <<'\t'<< allNode[2][2].linkcost[2] <<'\t'<< allNode[2][2].linkcost[1] << endl;
	cout << allNode[2][0].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 0) <<'\t'<< allNode[2][0].linkcost[0] <<'\t'<< allNode[2][1].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 1) <<'\t'<< allNode[2][1].linkcost[0] <<'\t'<< allNode[2][2].linkcost[4] <<'\t'<< testImg.at<uchar>(0, 2) <<'\t'<< allNode[2][2].linkcost[0] << endl;
	cout << allNode[2][0].linkcost[5] <<'\t'<< allNode[2][0].linkcost[6] <<'\t'<< allNode[2][0].linkcost[7] <<'\t'<< allNode[2][1].linkcost[5] <<'\t'<< allNode[2][1].linkcost[6] <<'\t'<< allNode[2][1].linkcost[7] <<'\t'<< allNode[2][2].linkcost[5] <<'\t'<< allNode[2][2].linkcost[6] <<'\t'<< allNode[2][2].linkcost[7] << endl;
*/
	


/*
	for(int i=0; i<allNode.size(); i++)
		for(int j=0; j<allNode[0].size(); j++)
			if(allNode[i][j].prenode!=NULL)
				showImg.at<uchar>(allNode[i][j].prenode->row, allNode[i][j].prenode->col) -= 20;
*/

	return 0;
}