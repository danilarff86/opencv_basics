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

    auto original = imread( argv[ 1 ], IMREAD_COLOR );

    Mat splitChannels[ 3 ];

    split( original, splitChannels );

    // imshow( "blue", splitChannels[ 0 ] );
    // imshow( "green", splitChannels[ 1 ] );
    // imshow( "red", splitChannels[ 2 ] );
    // imshow( "original", original );

    Mat mergedChannels;

    splitChannels[ 2 ] = Mat::zeros( splitChannels[ 2 ].size( ), CV_8UC1 );

    merge( splitChannels, 3, mergedChannels );

    imshow( "merged", mergedChannels );

    waitKey( );

    return 0;
}
