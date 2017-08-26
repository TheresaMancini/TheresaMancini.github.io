#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv){
  Mat image, nimage;
  int width, height;
  int nobjects;
  
  CvPoint p;
  image = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
  
  if(!image.data){
    std::cout << "imagem nao carregou corretamente\n";
    return(-1);
  }
  width=image.size().width;
  height=image.size().height;

  p.x=0;
  p.y=0;
  //pintando as bordas de branco
  for (int j=0;j<width;j++){
    image.at<uchar>(0,j)=255;
    image.at<uchar>(height-1,j)=255;
  }
  for (int i=0;i<height;i++){
    image.at<uchar>(i,0)=255;
    image.at<uchar>(i,width-1)=255;
  }
  //desaparecendo com as bolhas das bordas
  floodFill(image,p,0);
  image.copyTo(nimage);
  // diferenciando fundo:
  floodFill(image,p,254);// assumindo que a imagem tenha menos que 254 objetos, caso contrário zerar o rotulo nobjects a cada 253 objetos. 
  // rotulando objetos
  nobjects=0;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 255){
  		// achou um objeto
  		nobjects++;
  		p.x=j;
  		p.y=i;
  		floodFill(image,p,nobjects);
  	  }
  	}
  }
  //contando bolhas
  int nbolhas=1;
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      if(image.at<uchar>(i,j) == 0 && (int)image.at<uchar>(i,j-1)!=0){
  		// achou um objeto
  		nbolhas++;
  		p.x=j;
  		p.y=i;
  		floodFill(image,p,nbolhas);
  	  }
  	}
  }
  
  std:: cout << "numero de objetos" <<  nobjects << " e numero de bolhas eh " << nbolhas-1 <<std::endl; 
  imshow("nimage", nimage);
  waitKey();
  imshow("image", image);
  imwrite("labeling.png", image);
  waitKey();
  return 0;
}
