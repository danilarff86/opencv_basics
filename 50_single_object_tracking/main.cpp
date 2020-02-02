#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

int
main( )
{
    cv::VideoCapture video( 0 );

    if ( !video.isOpened( ) )
    {
        std::cerr << "Error opening video" << std::endl;
        return -1;
    }

    cv::Mat frame;

    const auto frameWidth = video.get( cv::CAP_PROP_FRAME_WIDTH );
    const auto frameHeigth = video.get( cv::CAP_PROP_FRAME_HEIGHT );

    std::cout << "frameWidth: " << frameWidth << ", frameHeigth: " << frameHeigth << std::endl;

    // cv::VideoWriter output( "output.avi", cv::VideoWriter::fourcc( 'M', 'J', 'P', 'G' ), 30,
    //                         cv::Size( frameWidth, frameHeigth ) );

    cv::Ptr< cv::Tracker > tracker = cv::TrackerKCF::create( );

    video.read( frame );
    cv::Rect2d trackingBox = cv::selectROI( frame, false );
    tracker->init( frame, trackingBox );

    cv::namedWindow( "VideoFeed", cv::WINDOW_FREERATIO );
    cv::moveWindow( "VideoFeed", 100, 100 );

    while ( video.read( frame ) )
    {
        if ( tracker->update( frame, trackingBox ) )
        {
            cv::rectangle( frame, trackingBox, cv::Scalar( 255, 0, 0 ), 2, 8 );
        }

        cv::imshow( "VideoFeed", frame );

        // output.write( frame );

        if ( cv::waitKey( 25 ) > 0 )
        {
            break;
        }
    }

    // output.release( );
    video.release( );
    cv::destroyAllWindows( );

    // cv::waitKey( );

    return 0;
}
