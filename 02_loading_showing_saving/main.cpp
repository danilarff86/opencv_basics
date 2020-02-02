#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int
main( int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout << "usage: " << argv[ 0 ] << " <Image_Path>\n" << std::endl;
        return -1;
    }

    auto testColor = imread( argv[ 1 ], IMREAD_COLOR );
    auto testGray = imread( argv[ 1 ], IMREAD_GRAYSCALE );

    imshow( "color", testColor );
    imshow( "gray", testGray );

    imwrite( "outputGray.jpg", testGray );

    waitKey( );

    return 0;
}
