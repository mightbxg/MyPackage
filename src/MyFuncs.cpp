#include "MyPackage/MyFuncs.h"

namespace mine {

int getArea(const cv::Mat& image)
{
    return image.rows * image.cols;
}

int getArea(const Eigen::MatrixXd& matrix)
{
    return matrix.rows() * matrix.cols();
}

}
