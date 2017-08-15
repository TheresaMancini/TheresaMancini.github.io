#include <iostream>
#include <opencv2/opencv.hpp> 

using namespace cv;
using namespace std;

int main(int argc, char** argv){
  Mat image;
  Vec3b val;
  Point2i P1,P2; 
  
  image= imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  if(!image.data)
    cout << "a imagem não foi carregada" << endl;
   cout <<"altura da imagem " << image.rows <<endl;
	cout <<"largura da imagem " << image.cols <<endl;
  namedWindow("janela",WINDOW_AUTOSIZE);
  imshow("janela",image);
 
	cout << "Digite os pontos P1 e P2 ." << endl;
	do{
		cout << "P1: ";
		cin >>  P1.x;
		cin >> P1.y;
		cout << "P1 = (" << P1.x << "," <<P1.y << ")" << endl;
		if (P1.x<0 || P1.x< image.cols || P1.y <0 || P1.y < image.rows)
			cout << " Ponto fora da imagem" << endl;
	}while(P1.x<0 || P1.x > image.cols || P1.y <0 || P1.y > image.rows);
	
	do{
		cout << "P2: ";
		cin >>  P2.x;
		cin >> P2.y;
		cout << "P2 = (" << P2.x << "," <<P2.y << ")" << endl;
		if (P2.x<0 || P2.x>image.cols || P2.y <0 || P2.y > image.rows)
			cout << " Ponto fora da imagem" << endl;
	}while(P2.x<0 || P2.x > image.cols || P2.y <0 || P2.y > image.rows);
  
  
  if (P1.x > P2.x){
	 int aux;
	 aux=P1.x;
	 P1.x=P2.x;
	 P2.x=aux;
	}
	
  if (P1.y > P2.y){
	 int aux;
	 aux=P1.y;
	 P1.y=P2.y;
	 P2.y=aux;
	}
	
	  
  imshow("janela", image);
  waitKey(); 
  
  for(int i=P1.y;i<P2.y;i++){
    for(int j=P1.x;j<P2.x;j++){
      image.at<uchar>(i,j)=255-image.at<uchar>(i,j);
    }
  }

  imshow("janela", image);  
  waitKey();
  return 0;
}
