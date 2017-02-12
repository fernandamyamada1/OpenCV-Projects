/*
Implementação do algoritmo Canny Double Threshold, no qual é possível alterar os valores dos dois thresholds e do número de vezes que a imagem é borrada para a indentificação dos contornos.
 
 Para criar o executável, basta ir à pasta na qual estão os arquivos e digitar o comando: make.
 
 Exemplo de comando para executar o programa: ./canny casa_rio.jpg.

 */


#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;


Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold=1;
int const max_lowThreshold = 100;
int highThreshold=1;
int const max_highThreshold = 100;
int kernel_size = 3;
int gaussianBlur=1;
int const max_blur= 10;
char* window_name = "Edge Map";

void CannyThreshold(int, void*)
{
  int i;
  blur( src_gray, detected_edges, Size(3,3) );
  for(i=1;i<gaussianBlur;i++)
  blur( detected_edges, detected_edges, Size(3,3) );

  Canny( detected_edges, detected_edges, lowThreshold, highThreshold, kernel_size );

  
  dst = Scalar::all(0);

  src.copyTo( dst, detected_edges);
  imshow( window_name, detected_edges );
 }


int main( int argc, char** argv )
{
  src = imread( argv[1] );

  if( !src.data )
  { return -1; }
  dst.create( src.size(), src.type() );
  cvtColor( src, src_gray, CV_BGR2GRAY );
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );
  createTrackbar( "Threshold1:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  createTrackbar( "Threshold2:", window_name, &highThreshold, max_highThreshold, CannyThreshold );
  createTrackbar( "Gaussian Blur:", window_name, &gaussianBlur, max_blur, CannyThreshold );
  
  CannyThreshold(0, 0);
  waitKey(0);

  return 0;
  }

