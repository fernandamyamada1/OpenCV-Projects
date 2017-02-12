
/*
 O exercício que foi dado foi o seguite:
 
 1) Implemente um código de segmentação utilizando K-Means em OpenCV.
 2) Faça com que o programa suporte as seguintes configurações:
    i) Tamanhos de K (quantidade de segmentações) diferentes.
    ii) Aplicar o filtro blur com diferentes tamanhos de kernel.
    iii) Ajustar as configurações da função kmeans (ex,: eps e tentativas).
    iv) Escolher o formato da imagem de entrada como RGB, HSV ou XYZ.
 3) Execute o programa para as quatro figuras em anexo desta atividade.
 
 Dessa forma, foram criadas trackbars para alterar as variáveis: número de segmentações, tamanho da janela de borramento, porcentagem de epsilon e número de tentativas.
 
 No momento da execução do código, é necessário inserir a imagem a ser processada e um número que indica o espaço de cor (1-RGB, 2-HSV, 3-XYZ) em que a imagem será processada.
 
 Para criar o executável, basta ir à pasta na qual estão os arquivos e digitar o comando: make.
 
 Exemplo de comando para executar o programa: ./kmeans tigre.png 2.
 
 */
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

#include <opencv2/opencv.hpp>

using namespace cv;
char* window_name = "Kmeans";
Mat src, temp;
int clusterCount = 15;
Mat labels;
int attempts = 5;
Mat centers;

int edgeThresh = 1;
int K=1;
int const max_K = 10;
int Blur=1;
int const max_Blur = 10;
int kernel_size = 1;
int EPS=1;
int const max_EPS= 100;
int t=1;
int const max_try= 10;

char* op;




void Kmeans(int, void*)
{
    
    src=temp.clone();
    if(strcmp(op,"1")==0){
        
    }
    if(strcmp(op,"2")==0){
        cvtColor( src, src, CV_BGR2HSV );
    }
    if(strcmp(op,"3")==0){
        cvtColor( src, src, CV_BGR2XYZ );
    }
    blur (src, src, cv::Size(Blur*2+1,Blur*2+1));
    
    Mat samples(src.rows * src.cols, 3, CV_32F);
    
    for( int y = 0; y < src.rows; y++ )
        for( int x = 0; x < src.cols; x++ )
            for( int z = 0; z < 3; z++)
                samples.at<float>(y + x*src.rows, z) = src.at<Vec3b>(y,x)[z];
    
    
    
    kmeans(samples, K, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, EPS/100), t, KMEANS_PP_CENTERS, centers );
    
    
    Mat new_image( src.size(), src.type() );
    for( int y = 0; y < src.rows; y++ )
        for( int x = 0; x < src.cols; x++ )
        {
            int cluster_idx = labels.at<int>(y + x*src.rows,0);
            new_image.at<Vec3b>(y,x)[0] = centers.at<float>(cluster_idx, 0);
            new_image.at<Vec3b>(y,x)[1] = centers.at<float>(cluster_idx, 1);
            new_image.at<Vec3b>(y,x)[2] = centers.at<float>(cluster_idx, 2);
        }
    imshow( window_name, new_image );
}

int main( int argc, char** argv )
{
    temp = imread( argv[1], 1 );
    op=argv[2];
   
    namedWindow( window_name, CV_WINDOW_AUTOSIZE );
    

    
    
    createTrackbar( "K:", window_name, &K, max_K, Kmeans);
    createTrackbar( "Blur size:", window_name, &Blur, max_Blur, Kmeans );
    createTrackbar( "EPS percentage:", window_name, &EPS, max_EPS, Kmeans );
    createTrackbar( "Tries:", window_name, &t, max_try, Kmeans );
    
    Kmeans(0,0);
    
    
    waitKey(0);
    
    return 0;
}

