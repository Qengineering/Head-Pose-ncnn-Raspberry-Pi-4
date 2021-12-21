#include <iostream>
#include <opencv2/opencv.hpp>
#include "FaceDetector.h"

using namespace std;

int main(int argc, char **argv)
{
    float f;
    float FPS[16];
    int i, Fcnt=0;
    cv::Mat frame;
    const int max_side = 320;

    //some timing
    chrono::steady_clock::time_point Tbegin, Tend;

    for(i=0;i<16;i++) FPS[i]=0.0;

    // 3D model points.
    std::vector<cv::Point3d> model_points;
    model_points.push_back(cv::Point3d(0.0f, 0.0f, 0.0f));               // Nose tip
//    model_points.push_back(cv::Point3d(0.0f, -330.0f, -65.0f));          // reel Chin
    model_points.push_back(cv::Point3d(0.0f, -300.0f, -65.0f));          // interpolate chin
    model_points.push_back(cv::Point3d(-225.0f, 170.0f, -135.0f));       // Left eye left corner
    model_points.push_back(cv::Point3d(225.0f, 170.0f, -135.0f));        // Right eye right corner
    model_points.push_back(cv::Point3d(-150.0f, -150.0f, -125.0f));      // Left Mouth corner
    model_points.push_back(cv::Point3d(150.0f, -150.0f, -125.0f));       // Right mouth corner

    Detector detector("face.param","face.bin");

//    cv::VideoCapture cap("Norton_A.mp4");
//    if (!cap.isOpened()) {
//        cerr << "ERROR: Unable to open the camera" << endl;
//        return 0;
//    }
//    cout << "Start grabbing, press ESC on Live window to terminate" << endl;

    while(1){
        //get frame
        frame=cv::imread("Group4.jpg");  //if you want to run just one picture need to refresh frame before class detection
//      cap >> frame;
        if (frame.empty()) {
            cerr << "ERROR: Unable to grab from the camera" << endl;
            break;
        }

        // scale
        float long_side = std::max(frame.cols, frame.rows);
        float scale = max_side/long_side;
        cv::Mat img_scale;

        cv::resize(frame, img_scale, cv::Size(frame.cols*scale, frame.rows*scale));

        std::vector<bbox> boxes;

        Tbegin = chrono::steady_clock::now();

        detector.Detect(img_scale, boxes);

        Tend = chrono::steady_clock::now();

        // draw image
        for (size_t j = 0; j < boxes.size(); ++j) {
            f=(boxes[j].point[3]._y+boxes[j].point[4]._y)/2; float y=2*f-boxes[j].point[2]._y;
            // 2D image points. we need to interpolate the position of the chin
            // in order to get the needed six points for the PnP solver
            std::vector<cv::Point2d> image_points;
            image_points.push_back( cv::Point2d(cv::Point(boxes[j].point[2]._x / scale, boxes[j].point[2]._y / scale)) );    // Nose tip
            image_points.push_back( cv::Point2d(cv::Point(boxes[j].point[2]._x / scale, y / scale )) );    // Chin
            image_points.push_back( cv::Point2d(cv::Point(boxes[j].point[0]._x / scale, boxes[j].point[0]._y / scale)) );     // Left eye left corner
            image_points.push_back( cv::Point2d(cv::Point(boxes[j].point[1]._x / scale, boxes[j].point[1]._y / scale)) );    // Right eye right corner
            image_points.push_back( cv::Point2d(cv::Point(boxes[j].point[3]._x / scale, boxes[j].point[3]._y / scale)) );    // Left Mouth corner
            image_points.push_back( cv::Point2d(cv::Point(boxes[j].point[4]._x / scale, boxes[j].point[4]._y / scale)) );    // Right mouth corner

            // Camera internals
            double focal_length = frame.cols; // Approximate focal length.
            cv::Point2d center = cv::Point2d(frame.cols/2,frame.rows/2);
            cv::Mat camera_matrix = (cv::Mat_<double>(3,3) << focal_length, 0, center.x, 0 , focal_length, center.y, 0, 0, 1);
            cv::Mat dist_coeffs = cv::Mat::zeros(4,1,cv::DataType<double>::type); // Assuming no lens distortion
            // Output rotation and translation
            cv::Mat rotation_vector;          // Rotation in axis-angle form
            cv::Mat translation_vector;

            // Solve for pose
            cv::solvePnP(model_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

            // Project a 3D point onto the image plane.
            // We use this to draw a line sticking out of the nose
            vector<cv::Point3d> nose_end_point3D;
            vector<cv::Point2d> nose_end_point2D;
            nose_end_point3D.push_back(cv::Point3d(0,0,300.0));
            nose_end_point3D.push_back(cv::Point3d(0,300.0,0.0));
            nose_end_point3D.push_back(cv::Point3d(300.0,0.0,0.0));
            cv::projectPoints(nose_end_point3D, rotation_vector, translation_vector, camera_matrix, dist_coeffs, nose_end_point2D);
            cv::line(frame,image_points[0], nose_end_point2D[1], cv::Scalar(0,255,0), 2);
            cv::line(frame,image_points[0], nose_end_point2D[2], cv::Scalar(0,0,255), 2);
            cv::line(frame,image_points[0], nose_end_point2D[0], cv::Scalar(255,0,0), 2);
        }

        //calculate frame rate
        f = chrono::duration_cast <chrono::milliseconds> (Tend - Tbegin).count();
        if(f>0.0) FPS[((Fcnt++)&0x0F)]=1000.0/f;
        for(f=0.0, i=0;i<16;i++){ f+=FPS[i]; }
        cv::putText(frame, cv::format("FPS %0.2f", f/16),cv::Point(10,20),cv::FONT_HERSHEY_SIMPLEX,0.6, cv::Scalar(0, 0, 255));

        //show output
        if( f/16 > 20.0) cv::imwrite("Result_4.jpg",frame); //in case you run only a jpg picture
        cv::imshow("RPi 64 OS - 1,95 GHz - 2 Mb RAM", frame);
        char esc = cv::waitKey(50);
        if(esc == 27) break;
    }

    cv::destroyAllWindows();
    return 0;
}
