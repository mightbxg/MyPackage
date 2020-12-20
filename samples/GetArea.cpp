#include <MyPackage/MyFuncs.h>
#include <MyPackage/Version.h>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << "Usage: GetArea <image>" << endl;
        return 0;
    }
    cout << "MyPackage version: "
         << MyPackage_VERSION_MAJOR << "."
         << MyPackage_VERSION_MINOR << "."
         << MyPackage_VERSION_PATCH << endl;
    Mat image = imread(argv[1]);
    if (image.empty()) {
        cout << "Cannot load image from " << argv[1] << endl;
        return -1;
    }
    cout << "Area of image " << argv[1] << " is "
         << mine::getArea(image) << endl;

    Eigen::MatrixXd matrix = Eigen::MatrixXd::Random(10, 20);
    cout << "Area of random matrix is "
         << mine::getArea(matrix) << endl;

    return 0;
}
