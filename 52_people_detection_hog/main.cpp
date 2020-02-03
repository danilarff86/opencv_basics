#include <iostream>
#include <opencv2/opencv.hpp>

void
ResizeBoxes( cv::Rect& box )
{
    box.x += cvRound( box.width * 0.1 );
    box.width = cvRound( box.width * 0.8 );
    box.y += cvRound( box.height * 0.06 );
    box.height = cvRound( box.height * 0.8 );
}

int
main( int argc, char** argv )
{
    if ( argc != 2 )
    {
        std::cout << "usage: " << argv[ 0 ] << " <Image_Path>\n" << std::endl;
        return -1;
    }

    auto image = cv::imread( argv[ 1 ], cv::IMREAD_COLOR );

    if ( image.data == nullptr )
    {
        std::cerr << "Error opening picture" << std::endl;
    }

    cv::HOGDescriptor hog;
    hog.setSVMDetector( cv::HOGDescriptor::getDefaultPeopleDetector( ) );

    std::vector< cv::Rect > detections;
    hog.detectMultiScale( image, detections, 0, cv::Size( 8, 8 ), cv::Size( 32, 32 ), 1.2, 2 );

    for ( auto& detection : detections )
    {
        // ResizeBoxes( detection );
        cv::rectangle( image, detection.tl( ), detection.br( ), cv::Scalar( 255, 0, 0 ), 2 );
    }

    cv::namedWindow( "Picture", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Picture", image );

    cv::waitKey( );

    return 0;
}
