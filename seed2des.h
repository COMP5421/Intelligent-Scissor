#ifndef SEED2DES_H_
#define SEED2DES_H_

#include "opencv2/core/core.hpp"

enum State {INITIAL, ACTIVE, EXPANDED};

struct imgNode
{
	double linkcost[8];
	State state;
	double totalcost;
	imgNode *prenode;
	int col, row;
};

std::vector<std::vector<imgNode> > initialize(cv::Mat img, bool color);

void seed2des(int sx, int sy, int dx, int dy, cv::Mat img, bool color);

bool comp(double val, imgNode const& node);

void nodeGraph(std::vector<std::vector<imgNode> > &allNode, imgNode seed);

#endif