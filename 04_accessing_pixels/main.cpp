#include <cstdint>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int
main( int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout << "usage: " << argv[ 0 ] << " <Image_Path>\n" << std::endl;
        return -1;
    }

#if 0

    auto original = imread( argv[ 1 ], IMREAD_GRAYSCALE );
    auto modified = imread( argv[ 1 ], IMREAD_GRAYSCALE );

    for ( int r = 0; r < modified.rows; r++ )
    {
        for ( int c = 0; c < modified.rows; c++ )
        {
            modified.at< uint8_t >( r, c ) /= 2;
        }
    }

    imshow( "original", original );
    imshow( "modified", modified );

#endif

    auto original = imread( argv[ 1 ], IMREAD_COLOR );
    auto modified = imread( argv[ 1 ], IMREAD_COLOR );

    for ( int r = 0; r < modified.rows; r++ )
    {
        for ( int c = 0; c < modified.rows; c++ )
        {
            modified.at< cv::Vec3b >( r, c ) /= 2;
        }
    }

    imshow( "original", original );
    imshow( "modified", modified );

    waitKey( );

    return 0;
}
