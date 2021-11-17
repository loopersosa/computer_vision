#include "D:\opencv\build\include\opencv2\highgui\highgui.hpp"
#include "D:\opencv\build\include\opencv2\imgproc\imgproc.hpp"
#include "D:\opencv\build\include\opencv2\objdetect\objdetect.hpp"
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    //load cascade
    CascadeClassifier face, eye; // inintializing 2 objects

    VideoCapture capture(0); // opening camera
    Mat cap_im, gray_im;

    String win_name = "face_detection";

    vector<Rect> face, eye;




    if (!face.load("haarcascade_frontalface_default.xml"))
    {
        cout << "cannot open face" << endl;
        return 	1;

    }

    if (!eye.load("haarcascade_eye.xml"))
    {
        cout << "cannot open eye" << endl;
        return 	1;

    }

    //check camera
    if (!capture.isOpened())
    {
        cout << "Error camera" << endl;
        return 1;
    }

    namedWindow(win_name, CV_WINDOW_FREERATIO);

    while (waitKey(33)!=27)
    {
        //take fram
        capture >> cap_im;

        //convert to grayScale color
        cvtColor(cap_im, gray_im, CV_RGB2GRAY);
        //equlize Histogram
        equalizeHist(gray_im, gray_im);

        //detection
        face.detectMultiScale(gray_im, face, 1.1, 3, 0, cvSize(0, 0), cvSize(300, 300));

        if (face.size())
        {
            putText(cap_im, "Face Detected", Point(30, 30), FONT_HERSHEY_PLAIN, 1, CV_RGB(100, 100, 200), 2, CV_AA, false);

        }

        for (int i = 0; i < face.size(); i++)
        {
            Point p1(face[i].x, face[i].y);
            Point p2(face[i].x + face[i].width, face[i].y + face[i].height);

            rectangle(cap_im, p1, p2, CV_RGB(0, 0, 255), 2, 8, 0);

            Mat Eye_im = gray_im(face[i]);

            eye.detectMultiScale(Eye_im, eye, 1.1, 3, 0, cvSize(0, 0), cvSize(50, 50));

            for (int j = 0; j < eye.size(); j++)
            {
                Point p3(face[i].x + eye[j].x, face[i].y + eye[j].y);
                Point p4(face[i].x + eye[j].x + eye[j].width, face[i].y + eye[j].y + eye[j].height);

                rectangle(cap_im, p3, p4, CV_RGB(0, 255, 0), 1, 8, 0);


            }


        }



        imshow(win_name, cap_im);


    }

    return 1;
}
