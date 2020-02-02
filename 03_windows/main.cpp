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

    auto fileColor = imread( argv[ 1 ], IMREAD_COLOR );
    auto fileGray = imread( argv[ 1 ], IMREAD_GRAYSCALE );

    namedWindow( "color", WINDOW_FREERATIO );
    namedWindow( "fixed", WINDOW_AUTOSIZE );

    imshow( "color", fileColor );
    imshow( "fixed", fileGray );

    resizeWindow( "color", fileColor.cols / 2, fileColor.rows / 2 );
    resizeWindow( "fixed", fileGray.cols / 2, fileGray.rows / 2 );

    moveWindow( "color", 100, 300 );
    moveWindow( "fixed", 500, 300 );

    waitKey( );

    return 0;
}
