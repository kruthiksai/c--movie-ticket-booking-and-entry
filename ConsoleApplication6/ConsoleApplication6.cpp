#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <mysql.h>// For Sleep


using namespace cv;
using namespace std;


class gettingsql {
public:void data(string k) {
    MYSQL* conn; /* pointer to connection handler */
    MYSQL_RES* res; /* holds the result set */
    MYSQL_ROW row;



    /* INITIALIZE CONNECTION HANDLER, DO NOT CHANGE */
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "admin", "testdb", 3306, NULL, 0);
    if (conn)
    {
      //  cout << "Connection Succeeded\n";
        string code = "kruthik";
        string queryText = "SELECT * FROM persons where code=('" + k + "')";
        mysql_query(conn, queryText.c_str());

        unsigned int i = 0;

        res = mysql_store_result(conn);

        unsigned int numrows = mysql_num_rows(res);



        while (((row = mysql_fetch_row(res)) != NULL))
        {
            string kk = row[4];
            if (kk == "verified") {
               
                cout << "Hi " << row[2] << " u have already used this qrcode for " << row[1] << endl;
              
            }
            else {
                cout << "Hi " << row[2] << " Welcome to " << row[1] << endl;
                updatequery(k);
            }
        }
     

        mysql_close(conn);
    }
    else
    {
        cout << "Connection Failed\n";
    }
}
public:void updatequery(string kk) {
    MYSQL* conn; /* pointer to connection handler */
    MYSQL_RES* res; /* holds the result set */
    MYSQL_ROW row;



    /* INITIALIZE CONNECTION HANDLER, DO NOT CHANGE */
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "admin", "testdb", 3306, NULL, 0);
    if (conn)
    {
        cout << "Connection Succeeded\n";
        
        string queryText = "UPDATE persons SET verified = 'verified'  where code=('" + kk + "')";
        mysql_query(conn, queryText.c_str());

        unsigned int i = 0;

        res = mysql_store_result(conn);


        mysql_close(conn);
    }
    else
    {
        cout << "Connection Failed\n";
    }

}
};

class encoding : public gettingsql{
    int ct = 0;
    char tipka;
    char filename[100]; // For filename
    int  c = 1; // For filename

public:int kk() {
        Mat frame;
        //--- INITIALIZE VIDEOCAPTURE
        VideoCapture cap;
        // open the default camera using default API
        cap.open(0);
        // OR advance usage: select any API backend
        int deviceID = 0;             // 0 = open default camera   
        int apiID = cv::CAP_ANY;      // 0 = autodetect default API
                                      // open selected camera using selected API
        cap.open(deviceID + apiID);
        // check if we succeeded
        if (!cap.isOpened()) {
            cerr << "ERROR! Unable to open camera\n";
            return -1;
        }
        //--- GRAB AND WRITE LOOP
        cout << "Start grabbing" << endl
            << "Press a to terminate" << endl;
        for (;;)
        {
            // wait for a new frame from camera and store it into 'frame'
            cap.read(frame);

            if (frame.empty()) {
                cerr << "ERROR! blank frame grabbed\n";
                break;
            }


            Sleep(5); // Sleep is mandatory - for no leg!



            // show live and wait for a key with timeout long enough to show images
            imshow("CAMERA 1", frame);  // Window name


            tipka = cv::waitKey(30);


            if (tipka == 'q') {

                sprintf_s(filename, "E:/Images/kk.png", c); // select your folder - filename is "Frame_n"
                cv::waitKey(10);

                imshow("CAMERA 1", frame);
                imwrite(filename, frame);
                cout << "Frame_" << c << endl;
                c++;
                cout << "Terminating..." << endl;

            cv:destroyAllWindows();
                break;


            }





        }
        // the camera will be deinitialized automatically in VideoCapture destructor
        return 0;
    }

    void display(Mat& im, Mat& bbox)
    {
        int n = bbox.rows;
        for (int i = 0; i < n; i++)
        {
            line(im, Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)), Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)), Scalar(255, 0, 0), 3);
        }
        imshow("Result", im);
    }


    string encode(int argc, char* argv[]) {
        Mat inputImage;
        if (argc > 1)
            inputImage = imread(argv[1]);
        else
            inputImage = imread("E:/Images/kk.png");

        QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();

        Mat bbox, rectifiedImage;

        std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
        if (data.length() > 0)
        {
            cout << "Decoded Data : " << data << endl;



            waitKey(0);
            return data;
        }
        else {

            cout << "QR Code not detected" << endl;
            return "";

        }
    }
};
void getdata() {

}
int main(int argc, char* argv[])
{
 
    string comp = "";
    string k = "";
    encoding enc;
    while (k==comp) {
        enc.kk();
        k = enc.encode(argc, argv);
    }
    if(k.length()>0){
        enc.data(k);
    }


    // Read image

}