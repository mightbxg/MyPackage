#include "gtest/gtest.h"
#include <MyPackage/MyFuncs.h>

namespace {

TEST(MyFuncs, GetAreaCv)
{
    cv::Mat image = cv::imread("data/lena.jpg");
    ASSERT_FALSE(image.empty());
    const int rows = image.rows;
    const int cols = image.cols;
    EXPECT_EQ(mine::getArea(image), rows * cols);
}

TEST(MyFuncs, GetAreaEigen)
{
    const int rows = 20;
    const int cols = 30;
    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(rows, cols);
    EXPECT_EQ(mine::getArea(mat), rows * cols);
}

}
