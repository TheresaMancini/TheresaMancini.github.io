#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//subimage() e copyTo para fazer o troca regiões

int main(int, char**){
  Mat image,trocada;
  Mat prim,seg,terc,quart;
  //trocar 1 com 4 e 3 com 2 

  image= imread("biel.png",CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "nao abriu biel.png" << endl;

  namedWindow("janela",WINDOW_AUTOSIZE);
  image.copyTo(trocada);

  prim= image(Rect(0,image.cols/2,image.rows/2,image.cols/2));
  seg= image(Rect(0,0,image.rows/2,image.cols/2));
  terc= image(Rect(image.rows/2,0,image.rows/2,image.cols/2));
  quart=  image(Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2));

  prim.copyTo(trocada(Rect(image.rows/2,0,image.rows/2,image.cols/2)));
  seg.copyTo(trocada(Rect(image.rows/2,image.cols/2,image.rows/2,image.cols/2)));
  terc.copyTo(trocada(Rect(0,image.cols/2,image.rows/2,image.cols/2)));
  quart.copyTo(trocada(Rect(0,0,image.rows/2,image.cols/2)));
    
  imshow("janela", image);
  waitKey();
  imshow("janela",trocada);
  waitKey();
  return 0;
}
