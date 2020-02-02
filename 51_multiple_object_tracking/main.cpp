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

    const auto windowName = "VideoFeed";

    video.read( frame );

    cv::Ptr< cv::MultiTracker > tracker = cv::MultiTracker::create( );
    std::vector< cv::Rect > trackingBoxes;
    cv::selectROIs( windowName, frame, trackingBoxes, false );

    if ( trackingBoxes.empty( ) )
    {
        return 0;
    }

    for ( const auto& box : trackingBoxes )
    {
        tracker->add( cv::TrackerKCF::create( ), frame, box );
    }

    cv::namedWindow( windowName, cv::WINDOW_FREERATIO );
    cv::moveWindow( windowName, 100, 100 );

    while ( video.read( frame ) )
    {
        tracker->update( frame );

        for ( const auto& object : tracker->getObjects( ) )
        {
            cv::rectangle( frame, object, cv::Scalar( 255, 0, 0 ), 2, 8 );
        }

        cv::imshow( windowName, frame );

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
