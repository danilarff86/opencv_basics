#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>

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
    // std::cout << cv::getBuildInformation( ) << std::endl;

    if ( argc != 2 )
    {
        std::cout << "usage: " << argv[ 0 ] << " <Video_Path>\n" << std::endl;
        return -1;
    }

    cv::VideoCapture video( argv[ 1 ] );
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

    cv::HOGDescriptor hog;
    hog.setSVMDetector( cv::HOGDescriptor::getDefaultPeopleDetector( ) );

    std::vector< cv::Rect > detections;
    hog.detectMultiScale( frame, detections, 0, cv::Size( 8, 8 ), cv::Size( 32, 32 ), 1.2, 2 );

    for ( auto& detection : detections )
    {
        // ResizeBoxes( detection );
        tracker->add( cv::TrackerKCF::create( ), frame, detection );
    }

    cv::namedWindow( windowName, cv::WINDOW_FREERATIO );
    cv::moveWindow( windowName, 100, 100 );

    uint64_t frameNumber = 1;

    while ( video.read( frame ) )
    {
        ++frameNumber;

        if ( frameNumber % 15 == 0 )
        {
            detections.clear( );
            hog.detectMultiScale( frame, detections, 0, cv::Size( 8, 8 ), cv::Size( 32, 32 ), 1.2,
                                  2 );
            tracker = cv::MultiTracker::create( );
            for ( auto& detection : detections )
            {
                // ResizeBoxes( detection );
                tracker->add( cv::TrackerKCF::create( ), frame, detection );
            }
        }
        else
        {
            tracker->update( frame );
        }

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

    return 0;
}
