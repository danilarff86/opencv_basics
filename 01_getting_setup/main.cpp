#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int
main( int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout << "usage: DisplayImage.out <Image_Path>\n" << std::endl;
        return -1;
    }

    auto image = imread( argv[ 1 ], IMREAD_UNCHANGED );

    if ( !image.data )
    {
        std::cerr << "No image data \n" << std::endl;
        return -1;
    }

    imshow( "test", image );

    waitKey( );

    return 0;
}
