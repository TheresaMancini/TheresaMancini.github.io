#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath> 

using namespace cv;
using namespace std;

double alfa;
int h_slider = 0;

int p_slider = 0;

int d_slider = 0;
int d_slider_max=100;
float media[]={1,1,1,1,1,1,1,1,1};
double l1,l2;

Mat image1, image2;
Mat blended;

char TrackbarName[50];

void on_trackbar_h(int, void*){
   l1=h_slider-p_slider;
   l2=h_slider+p_slider;
}

void on_trackbar_p(int, void*){
   l1=h_slider-p_slider;
   l2=h_slider+p_slider;
}

int main(int argvc, char** argv){
  image1 = imread("teste.jpg");
  resize(image1,image1,Size(640,480));
  cout << image1.rows << endl;
  cout << image1.size().height << endl;
  image1.copyTo(image2);
  image2.convertTo(image2, CV_32F);
  
  Mat mask = Mat(3, 3, CV_32F, media);
  scaleAdd(mask, 1/9.0, Mat::zeros(3,3,CV_32F), mask);

  for (int i=0;i<10;i++)
  	filter2D(image2, image2, image2.depth(), mask, Point(1,1), 0);
  image2.convertTo(image2, CV_8U);
  
  namedWindow("addweighted", 1);
  
  sprintf( TrackbarName, "Altura %d", image1.rows );
  createTrackbar( TrackbarName, "addweighted",
				  &h_slider,
				  image1.rows,
				  on_trackbar_h );
  on_trackbar_h(h_slider, 0 );
  
  sprintf( TrackbarName, "Decaimento x %d", d_slider_max );
  createTrackbar( TrackbarName, "addweighted",
				  &d_slider,
				  d_slider_max);
   
  
  sprintf( TrackbarName, "Posição %d", image1.rows );
  createTrackbar( TrackbarName, "addweighted",
				  &p_slider,
				  image1.rows,
				  on_trackbar_p );
  on_trackbar_p(p_slider, 0 );
  blended=Mat::zeros(image1.rows,image1.cols, CV_8UC3);
  
  while (1){
        for(int i=0; i<image1.rows; i++){
           double d=(double)d_slider;
            alfa = 0.5*(tanh((i-l1)/d)-tanh((i-l2)/d));
            addWeighted(image1.row(i),alfa,image2.row(i),1-alfa,0,blended.row(i));
        }
        imshow("addweighted",blended);
        if(waitKey(30) == 27) break;
 	imwrite("resultado.jpg",blended);
  }
	imwrite("resultado.jpg",blended);

  waitKey(0);
  return 0;
}
