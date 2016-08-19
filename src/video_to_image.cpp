#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <stdio.h>      /* printf */
#include <math.h>       /* floor */

using namespace cv;
using namespace std;

int main( int argc, char** argv ){

    const char* inputFilename = 0;
    int save_rate = 10;
    int nr_frames = 0;

    for( int i = 1; i < argc; i++ )
    {
        const char* s = argv[i];
        if( strcmp( s, "-r" ) == 0 )
        {
            if( sscanf( argv[++i], "%d", &save_rate ) != 1 || save_rate <= 1 ){
        		cout << "invalid save rate" << std::endl;
        		return -1;
            }

        }
        else if( strcmp( s, "-nr" ) == 0 )
        {
            if( sscanf( argv[++i], "%d", &nr_frames ) != 1 || nr_frames <= 2 ){
        		cout << "invalid number of frames" << std::endl;
        		return -1;
            }
        }
        else if( s[0] != '-' )
        {
            inputFilename = s;
        }
        else if( strcmp( s, "-n" ) == 0 )
        {
            inputFilename = s;
        }

    }





    VideoCapture cap(inputFilename);


    if(nr_frames > 0){
    	save_rate = floor(cap.get(CV_CAP_PROP_FRAME_COUNT)/nr_frames);
    }

    FileStorage fs("image_list.yaml", FileStorage::WRITE);
    fs << "images" << "[";
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.

	if(!cap.isOpened()){
		cout << "could not open video" << std::endl;
		return -1;
	}

	int frame_nr = 0;
	int img_count = 0;
    for(;;)
    {

		Mat frame;
		cap >> frame;
		if( frame.empty() ) break; // end of video stream
		if(frame_nr%save_rate == 0){
			if(img_count > nr_frames){
				break;
			}
			imshow("Video", frame);
			if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC
			imwrite( "video_frame_"+std::to_string(img_count)+".png", frame );
			fs << "video_frame_"+std::to_string(img_count)+".png";
			img_count++;
		}
		frame_nr++;
    }
    fs << "]";

    // the camera will be closed automatically upon exit
    //cap.close();

    return 0;
}
