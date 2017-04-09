#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  VectorXd rmse(4);
	rmse << 0,0,0,0;

	// check the validity of the following inputs:
	//  * the estimation vector size should not be zero
	if (estimations.size() == 0) {
	    std::cout << "The estimation vector should not be zero.\n";
	    return rmse;
	}

	//  * the estimation vector size should equal ground truth vector size
	if (estimations.size() != ground_truth.size()) {
	    std::cout << "The estimation vector size should equal ground truth vector size.\n";
	    return rmse;
	}

	//accumulate squared residuals
	for(int i=0; i < estimations.size(); ++i){
	    VectorXd a = estimations[i];
	    VectorXd b = ground_truth[i];
	    VectorXd c = a - b;
	    VectorXd d = c.array() * c.array();
	    rmse = rmse + d;
	}

	//calculate the mean
	VectorXd n = VectorXd(4);
	n << estimations.size(),estimations.size(),estimations.size(),estimations.size();
	rmse = rmse.array() / n.array();

	//calculate the squared root
	rmse = rmse.array().sqrt();

	//return the result
	return rmse;

}
