#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <ctime>
#include <thread>
#include <chrono>


#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>

using namespace cv;
using namespace std;


string streamurl = "http://192.168.1.21:8080/video?dummy=param.mjpg";
string window_name = "This is your smile :)";


#include <dlib/image_processing/frontal_face_detector.h>

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <dlib/opencv.h> 


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;


int TAKE_PICTURE = 0;


void detect_face_dlib(cv::Mat &cv_mat, cv::vector<cv::Point> &prev, cv::vector<cv::Point> &curr) {

	prev = curr;
	curr.clear();


	dlib::array2d<dlib::rgb_pixel> img;
	dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(cv_mat));

	dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();

	// upsample image
	//dlib::pyramid_up(img);

	// Now tell the face detector to give us a list of bounding boxes
	// around all the faces it can find in the image.
	std::vector<dlib::rectangle> dets = detector(img);

	//cout << "Number of faces detected: " << dets.size() << endl;


	// Now we show the image on the screen and the face detections as
	// red overlay boxes.
	/*
	dlib::image_window win;
	win.clear_overlay();
	win.set_image(img);
	win.add_overlay(dets, dlib::rgb_pixel(255,0,0));
	*/




	//Bounding Box Centroid



	for (size_t i = 0; i < dets.size(); i++) {

		cv::Point center = cv::Point((dets[i].right() - dets[i].left()) / 2, (dets[i].bottom() - dets[i].top()) / 2);
		curr.push_back(center);

		//printf("top: %d, bottom: %d, left: %d, right:%d\n", dets[i].top(), dets[i].bottom(), dets[i].left(), dets[i].right());
		cv::rectangle(cv_mat, cv::Point(dets[i].left(), dets[i].top()), cv::Point(dets[i].right(), dets[i].bottom()), cv::Scalar(0, 0, 255),4);
	}

}

bool hog_people_detection(cv::Mat &img_clr) {


	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	vector<Rect> found, found_filtered;
	double t = (double)getTickCount();
	// run the detector with default parameters. to get a higher hit-rate
	// (and more false alarms, respectively), decrease the hitThreshold and
	// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
	hog.detectMultiScale(img_clr, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
	t = (double)getTickCount() - t;
	printf("tdetection time = %gms\n", t*1000. / cv::getTickFrequency());
	size_t i, j;
	for (i = 0; i < found.size(); i++)
	{
		Rect r = found[i];
		for (j = 0; j < found.size(); j++)
			if (j != i && (r & found[j]) == r)
				break;
		if (j == found.size())
			found_filtered.push_back(r);
	}
	for (i = 0; i < found_filtered.size(); i++)
	{
		Rect r = found_filtered[i];
		// the HOG detector returns slightly larger rectangles than the real objects.
		// so we slightly shrink the rectangles to get a nicer output.
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.07);
		r.height = cvRound(r.height*0.8);


		std::cout << "--- found face" << std::endl;
		rectangle(img_clr, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
	}

	imshow(window_name, img_clr);
	int c = waitKey(2) & 255;
	if (c == 'q' || c == 'Q') {
		return false;
	}

	return true;
}

bool haar_detection(cv::Mat &img_clr, CascadeClassifier* cascade_) {

	std::vector<Rect> bodies;
	Mat frame_gray;


	cvtColor(img_clr, frame_gray, CV_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);

	//-- Detect faces
	cascade_->detectMultiScale(frame_gray, bodies, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

	for (size_t i = 0; i < bodies.size(); i++)
	{
		rectangle(img_clr, bodies[i], Scalar(0, 0, 255));
	}
	//-- Show what you got
	imshow(window_name, img_clr);
	int c = waitKey(2) & 255;
	if (c == 'q' || c == 'Q') {
		return false;
	}

	return true;

}



CascadeClassifier* load_face_haar() {
	CascadeClassifier* upper_body_cascade = new CascadeClassifier;
	if (!upper_body_cascade->load("../../ressource/haarcascades/haarcascade_frontalface_alt2.xml")) {
		printf("--(!)Error loading\n");
		return nullptr;
	};
	return upper_body_cascade;
}

CascadeClassifier* load_upper_body_haar() {
	CascadeClassifier* upper_body_cascade = new CascadeClassifier;
	if (!upper_body_cascade->load("../../ressource/haarcascades/haarcascade_upperbody.xml")) {
		printf("--(!)Error loading\n");
		return nullptr;
	};
	return upper_body_cascade;
}

CascadeClassifier* load_eye_haar() {
	CascadeClassifier* upper_body_cascade = new CascadeClassifier;
	if (!upper_body_cascade->load("../../ressource/haarcascades/haarcascade_eye.xml")) {
		printf("--(!)Error loading\n");
		return nullptr;
	};
	return upper_body_cascade;
}

int COUNTDOWN = 0;
int OK_NR_FRAMES = 0;
string countdown_window_name = "Countdown";

void draw_countdown(cv::Mat &img) {

	string text;
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 13;
	int thickness = 15;
	cv::Scalar color(0, 0, 255);


	if (COUNTDOWN == 0) {
		fontFace = CV_FONT_HERSHEY_SIMPLEX;
		fontScale = 9;
		thickness = 12;
		text = "SNAP";
		color = Scalar(0, 255, 0);
	}
	else {
		text = std::to_string(COUNTDOWN);
	}
	int baseline = 0;
	Size textSize = getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	// center the text
	Point textOrg((img.cols - textSize.width) / 2,
		(img.rows + textSize.height) / 2);

	// then put the text itself
	putText(img, text, textOrg, fontFace, fontScale,
		color, thickness, 8);

}

long int unix_timestamp()
{
	time_t t = std::time(0);
	long int now = static_cast<long int> (t);
	return now;
}


void save_image(cv::Mat img) {
	long int now = unix_timestamp();
	cv::imwrite("../pictures/fotobox_"+ std::to_string(now)+".jpg", img);
}

void reset_cam_status() {
	TAKE_PICTURE = 0;
	COUNTDOWN = 3;
	OK_NR_FRAMES = 0;
}

int main(int argc, char** argv)
{
    VideoCapture cap;

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	cv::vector<cv::Point> FACELIST_curr;
	cv::vector<cv::Point> FACELIST_prev;
	int check_interval = 2;

	while (!cap.open(streamurl)) {
		std::cout << "Trying to open camera stream..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}


	Size size(800, 600);//the dst image size,e.g.100x100
	cv::Mat frame_clr;
	cv::Mat img_resized;

	namedWindow(window_name, WINDOW_NORMAL);// Create a window for display.

	// load cascade
	CascadeClassifier* cascade = load_face_haar();

	if (cascade == nullptr) {
		std::cout << "Failed to load cascade..." << std::endl;
		return -1;
	}

	int frame_no = 0;
	int face_offset = 6;
	bool has_not_moved = false;
	bool wait_a_sec = false;

    for(;;)
    {
          cap >> frame_clr;
          if(frame_clr.empty() ) break; // end of video stream

		  // resize
		  resize(frame_clr, img_resized, size);//resize image

		  //haar_detection(img_resized, cascade);
		  detect_face_dlib(img_resized, FACELIST_prev, FACELIST_curr);


		  wait_a_sec = false;
		  // check status
		  if (FACELIST_curr.size() == 0 
			  || FACELIST_prev.size() != FACELIST_curr.size()
			  ) {
			  std::cout << "uneven number or no faces:" << FACELIST_curr.size() << std::endl;
			  reset_cam_status();
		  }
		  else {

			  // check status
			  for (int i = 0; i<FACELIST_curr.size(); i++) {
				  cv::Point face_center_curr = FACELIST_curr[i];
				  cv::Point face_center_prev;

				  has_not_moved = false;
				  for (int j = 0; j<FACELIST_prev.size(); j++) {
					  face_center_prev = FACELIST_prev[j];
					  // find face with same center
					  if (
						  std::abs(face_center_curr.x - face_center_prev.x) < face_offset &&
						  std::abs(face_center_curr.y - face_center_prev.y)  < face_offset
						  ) {
						  has_not_moved = true;
						  break;
					  }
				  }
				  if (!has_not_moved) {
					  break;
				  } else {
					  //std::cout << "++ a face has not moved: (" << face_center_curr.x << ", "<< face_center_curr.y << ")"<< std::endl;
				  }
			  }

			  if (has_not_moved == true) {
				  TAKE_PICTURE = 1;
				  OK_NR_FRAMES++;
			  }
			  else {
				  // RESET EVERYTHING
				  reset_cam_status();
			  }
		  }

		  std::cout << "status[take_picture: " << TAKE_PICTURE << ", countdown: " << COUNTDOWN << "]" << std::endl;

		  if (TAKE_PICTURE == 1) {

			  // render countdown on every second image
			  // take picture on 6th ok frame
			  if (OK_NR_FRAMES % 2 == 0) {
				  draw_countdown(img_resized);
				  // count down from 3
				  if (COUNTDOWN == 0) {
					  // save picture
					  std::cout << "SNAAP" << std::endl;
					  //save_image(frame_clr);
					  cv::imwrite("../pictures/fotobox111.jpg", frame_clr);
					  // reset count down
					  COUNTDOWN = 3;
					  // wait 3 sec
					  wait_a_sec = true;
					  
				  }
				  else {
					  // render countdown
					  COUNTDOWN--;
				  }
			  }

		  }
		  else {
			  // do nothing
		  }


		  //hog_people_detection(img_resized);
		  // show
          cv::imshow(window_name, img_resized);
          if( waitKey(1) == 27 ) break; // stop capturing by pressing ESC 
		  frame_no++;
		  if (wait_a_sec) {
			  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		  }
	}
    // the camera will be closed automatically upon exit
    // cap.close();




    return 0;
}