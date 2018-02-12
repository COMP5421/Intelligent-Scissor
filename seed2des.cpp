#include <iostream>
#include <stdio.h>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "seed2des.h"

using namespace std;
using namespace cv;

bool comp(double val, imgNode const& node)
{
	return (node.totalcost>val);
}

void seed2des(int sx, int sy, int dx, int dy, Mat colorImg, bool color)
{
	vector<vector<imgNode> > allNode;
	imgNode	seed;
	imgNode* mouse;

	if(!color)
	{
		Mat grayImg;
		cvtColor(colorImg, grayImg, COLOR_BGR2GRAY);

		Rect roi;
		roi.x = (sy<dy)? sy-10: dy-10;
		roi.y = (sx<dx)? sx-10: dx-10;
		roi.width = abs(dy-sy)+20;
		roi.height = abs(dx-sx)+20;

		Mat cropImg = grayImg(roi);
		allNode = initialize(cropImg, 0);
		seed = (sx<dx)? ((sy<dy)? allNode[10][10]: allNode[10][10+sy-dy]): ((sy<dy)? allNode[10+sx-dx][10]: allNode[10+sx-dx][10+sy-dy]);
		mouse = (sx<dx)? ((sy<dy)? &allNode[10+dx-sx][10+dy-sy]: &allNode[10+dx-sx][10]): ((sy<dy)? &allNode[10][10+dy-sy]: &allNode[10][10]);

		nodeGraph(allNode, seed);

		Mat showImg(allNode.size(), allNode[0].size(), CV_8U, Scalar(255));

		while(mouse->prenode!=NULL)
		{
			showImg.at<uchar>(mouse->row, mouse->col) = 0;
			mouse = mouse->prenode;
		}
		imshow("gray scale", showImg);
		waitKey();
	}
	else
	{
		Mat rgbImg[3];
		vector<vector<imgNode> > rgbNode[3];
		double gmax = 0.0;
		double dlink[8], cost[8];
		double length[8] = {1, sqrt(2), 1, sqrt(2), 1, sqrt(2), 1, sqrt(2)};

		for(int k=0; k<3; k++)
		{
			extractChannel(colorImg, rgbImg[k], 2-k);

			Rect roi;
			roi.x = (sy<dy)? sy-10: dy-10;
			roi.y = (sx<dx)? sx-10: dx-10;
			roi.width = abs(dy-sy)+20;
			roi.height = abs(dx-sx)+20;

			Mat cropImg = rgbImg[k](roi);
			rgbNode[k] = initialize(cropImg, 1);
		}

		allNode = rgbNode[0];

		for(int i=0; i<rgbNode[0].size(); i++)
			for(int j=0; j<rgbNode[0][0].size(); j++)
			{
				vector<double> maxD;
				for(int k=0; k<8; k++)
					dlink[k] = sqrt((rgbNode[0][i][j].linkcost[k]*rgbNode[0][i][j].linkcost[k] + rgbNode[1][i][j].linkcost[k]*rgbNode[1][i][j].linkcost[k] +
						rgbNode[2][i][j].linkcost[k]*rgbNode[2][i][j].linkcost[k])/3);
				for (int k = 0; k < 8; k++)
					maxD.push_back(dlink[k]);
				sort(maxD.begin(), maxD.end());

				if(gmax<maxD[7])
					gmax=maxD[7];

				for (int k = 0; k < 8; k++)
					cost[k] = (gmax-dlink[k])*length[k];
				copy(cost, cost+8, allNode[i][j].linkcost);
			}

		seed = (sx<dx)? ((sy<dy)? allNode[10][10]: allNode[10][10+sy-dy]): ((sy<dy)? allNode[10+sx-dx][10]: allNode[10+sx-dx][10+sy-dy]);
		mouse = (sx<dx)? ((sy<dy)? &allNode[10+dx-sx][10+dy-sy]: &allNode[10+dx-sx][10]): ((sy<dy)? &allNode[10][10+dy-sy]: &allNode[10][10]);

		nodeGraph(allNode, seed);
		Mat showImg = colorImg.clone();

		while(mouse->prenode!=NULL)
		{
			showImg.at<Vec3b>(mouse->row+sx-10, mouse->col+sy-10)[0] = 0;
			showImg.at<Vec3b>(mouse->row+sx-10, mouse->col+sy-10)[1] = 0;
			showImg.at<Vec3b>(mouse->row+sx-10, mouse->col+sy-10)[2] = 255;
			mouse = mouse->prenode;
		}
		imshow("color scale", showImg);
		waitKey();
	}
}

vector<vector<imgNode> > initialize(Mat img, bool color)
{
	vector<vector<imgNode> > allNode;
	double gmax = 0.0;
	for (int j = 0; j < img.rows; j++)
	{
		allNode.push_back(vector<imgNode>());
		for (int i = 0; i < img.cols; i++)
		{
			imgNode n;
			vector<double> maxD;

			double d[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
			double dlink[8], cost[8];
			double length[8] = {1, sqrt(2), 1, sqrt(2), 1, sqrt(2), 1, sqrt(2)};

			if(j-1<0)
				d[1]=d[2]=d[3]=0;
			if(j+1>img.rows-1)
				d[5]=d[6]=d[7]=0;
			if(i-1<0)
				d[3]=d[4]=d[5]=0;
			if(i+1>img.cols-1)
				d[0]=d[7]=d[1]=0;

			if(d[0]==-1)
				d[0] = img.at<uchar>(j, i+1);
			if(d[1]==-1)
				d[1] = img.at<uchar>(j-1, i+1);
			if(d[2]==-1)
				d[2] = img.at<uchar>(j-1, i);
			if(d[3]==-1)
				d[3] = img.at<uchar>(j-1, i-1);
			if(d[4]==-1)
				d[4] = img.at<uchar>(j, i-1);
			if(d[5]==-1)
				d[5] = img.at<uchar>(j+1, i-1);
			if(d[6]==-1)
				d[6] = img.at<uchar>(j+1, i);
			if(d[7]==-1)
				d[7] = img.at<uchar>(j+1, i+1);

			dlink[0] = abs((d[2]+d[1])/2-(d[6]+d[7])/2)/2;
			dlink[1] = abs(d[0]-d[2])/sqrt(2);
			dlink[2] = abs((d[4]+d[3])/2-(d[0]+d[1])/2)/2;
			dlink[3] = abs(d[2]-d[4])/sqrt(2);
			dlink[4] = abs((d[6]+d[5])/2-(d[2]+d[3])/2)/2;
			dlink[5] = abs(d[4]-d[6])/sqrt(2);
			dlink[6] = abs((d[0]+d[7])/2-(d[4]+d[5])/2)/2;
			dlink[7] = abs(d[6]-d[0])/sqrt(2);

			for (int k = 0; k < 8; k++)
				maxD.push_back(dlink[k]);

			sort(maxD.begin(), maxD.end());

			if(gmax<maxD[7])
				gmax=maxD[7];

			for (int k = 0; k < 8; k++)
				cost[k] = (gmax-dlink[k])*length[k];
			if(!color)
				copy(cost, cost+8, n.linkcost);
			else
				copy(dlink, dlink+8, n.linkcost);
			
			n.state = INITIAL;
			n.totalcost = 1e8;
			n.prenode = NULL;
			n.col = i;
			n.row = j;
			allNode[j].push_back(n);
		}
	}
	cout<<"gmax: "<<gmax<<endl;
	return allNode;
}

void nodeGraph(vector<vector<imgNode> > &allNode, imgNode seed)
{
	int h = allNode.size();
	int w = allNode[0].size();
	vector<imgNode> pq;
	pq.push_back(seed);

	while(!pq.empty())
	{
		imgNode* leastNode = &allNode[pq.front().row][pq.front().col];
		pq.erase(pq.begin());
		int x = leastNode->row;
		int y = leastNode->col;
		leastNode->state = EXPANDED;
		leastNode->totalcost = 0;
		vector<imgNode>::iterator it;

		if(y+1<w && allNode[x][y+1].state==INITIAL)
		{
			allNode[x][y+1].prenode = &allNode[x][y];
			allNode[x][y+1].totalcost = leastNode->totalcost+leastNode->linkcost[0];
			allNode[x][y+1].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x][y+1].totalcost, comp);
			pq.insert(it, allNode[x][y+1]);
		}
		else if(y+1<w && allNode[x][y+1].state==ACTIVE)
			if(allNode[x][y+1].totalcost > leastNode->totalcost+leastNode->linkcost[0])
			{
				allNode[x][y+1].totalcost = leastNode->totalcost+leastNode->linkcost[0];
				allNode[x][y+1].prenode = &allNode[x][y];
			}
		
		if(y+1<w && x>0 && allNode[x-1][y+1].state==INITIAL)
		{
			allNode[x-1][y+1].prenode = &allNode[x][y];
			allNode[x-1][y+1].totalcost = leastNode->totalcost+leastNode->linkcost[1];
			allNode[x-1][y+1].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x-1][y+1].totalcost, comp);
			pq.insert(it, allNode[x-1][y+1]);
		}
		else if(y+1<w && x>0 && allNode[x-1][y+1].state==ACTIVE)
			if(allNode[x-1][y+1].totalcost > leastNode->totalcost+leastNode->linkcost[1])
			{
				allNode[x-1][y+1].totalcost = leastNode->totalcost+leastNode->linkcost[1];
				allNode[x-1][y+1].prenode = &allNode[x][y];
			}

		if(x>0 && allNode[x-1][y].state==INITIAL)
		{
			allNode[x-1][y].prenode = &allNode[x][y];
			allNode[x-1][y].totalcost = leastNode->totalcost+leastNode->linkcost[2];
			allNode[x-1][y].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x-1][y].totalcost, comp);
			pq.insert(it, allNode[x-1][y]);
		}
		else if(x>0 && allNode[x-1][y].state==ACTIVE)
			if(allNode[x-1][y].totalcost > leastNode->totalcost+leastNode->linkcost[2])
			{
				allNode[x-1][y].totalcost = leastNode->totalcost+leastNode->linkcost[2];
				allNode[x-1][y].prenode = &allNode[x][y];
			}

		if(y>0 && x>0 && allNode[x-1][y-1].state==INITIAL)
		{
			allNode[x-1][y-1].prenode = &allNode[x][y];
			allNode[x-1][y-1].totalcost = leastNode->totalcost+leastNode->linkcost[3];
			allNode[x-1][y-1].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x-1][y-1].totalcost, comp);
			pq.insert(it, allNode[x-1][y-1]);
		}
		else if(y>0 && x>0 && allNode[x-1][y-1].state==ACTIVE)
			if(allNode[x-1][y-1].totalcost > leastNode->totalcost+leastNode->linkcost[3])
			{
				allNode[x-1][y-1].totalcost = leastNode->totalcost+leastNode->linkcost[3];
				allNode[x-1][y-1].prenode = &allNode[x][y];
			}

		if(y>0 && allNode[x][y-1].state==INITIAL)
		{
			allNode[x][y-1].prenode = &allNode[x][y];
			allNode[x][y-1].totalcost = leastNode->totalcost+leastNode->linkcost[4];
			allNode[x][y-1].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x][y-1].totalcost, comp);
			pq.insert(it, allNode[x][y-1]);
		}
		else if(y>0 && allNode[x][y-1].state==ACTIVE)
			if(allNode[x][y-1].totalcost > leastNode->totalcost+leastNode->linkcost[4])
			{
				allNode[x][y-1].totalcost = leastNode->totalcost+leastNode->linkcost[4];
				allNode[x][y-1].prenode = &allNode[x][y];
			}

		if(y>0 && x+1<h && allNode[x+1][y-1].state==INITIAL)
		{
			allNode[x+1][y-1].prenode = &allNode[x][y];
			allNode[x+1][y-1].totalcost = leastNode->totalcost+leastNode->linkcost[5];
			allNode[x+1][y-1].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x+1][y-1].totalcost, comp);
			pq.insert(it, allNode[x+1][y-1]);
		}
		else if(y>0 && x+1<h && allNode[x+1][y-1].state==ACTIVE)
			if(allNode[x+1][y-1].totalcost > leastNode->totalcost+leastNode->linkcost[5])
			{
				allNode[x+1][y-1].totalcost = leastNode->totalcost+leastNode->linkcost[5];
				allNode[x+1][y-1].prenode = &allNode[x][y];
			}

		if(x+1<h && allNode[x+1][y].state==INITIAL)
		{
			allNode[x+1][y].prenode = &allNode[x][y];
			allNode[x+1][y].totalcost = leastNode->totalcost+leastNode->linkcost[6];
			allNode[x+1][y].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x+1][y].totalcost, comp);
			pq.insert(it, allNode[x+1][y]);
		}
		else if(x+1<h && allNode[x+1][y].state==ACTIVE)
			if(allNode[x+1][y].totalcost > leastNode->totalcost+leastNode->linkcost[6])
			{
				allNode[x+1][y].totalcost = leastNode->totalcost+leastNode->linkcost[6];
				allNode[x+1][y].prenode = &allNode[x][y];
			}

		if(y+1<w && x+1<h && allNode[x+1][y+1].state==INITIAL)
		{
			allNode[x+1][y+1].prenode = &allNode[x][y];
			allNode[x+1][y+1].totalcost = leastNode->totalcost+leastNode->linkcost[7];
			allNode[x+1][y+1].state = ACTIVE;
			it = upper_bound(pq.begin(), pq.end(), allNode[x+1][y+1].totalcost, comp);
			pq.insert(it, allNode[x+1][y+1]);
		}
		else if(y+1<w && x+1<h && allNode[x+1][y+1].state==ACTIVE)
			if(allNode[x+1][y+1].totalcost > leastNode->totalcost+leastNode->linkcost[7])
			{
				allNode[x+1][y+1].totalcost = leastNode->totalcost+leastNode->linkcost[7];
				allNode[x+1][y+1].prenode = &allNode[x][y];
			}
	}

}