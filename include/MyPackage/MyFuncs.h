#ifndef ___MYLIB_MYFUNCS_H
#define ___MYLIB_MYFUNCS_H

#include <Eigen/Core>
#include <opencv2/opencv.hpp>

namespace mine {

int getArea(const cv::Mat& image);

int getArea(const Eigen::MatrixXd& matrix);

}

#endif // ___MYLIB_MYFUNCS_H
