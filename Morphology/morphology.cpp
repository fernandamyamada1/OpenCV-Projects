/*
 Programa criado para a remoção de ruídos através de operações morfológicas de erosões e dilatações.
 São oferecidas três opções ao usuário:
 1- Execução de operações morfológicas de acordo com valores definidos pelo usuário através das trackbars.
 2- À princípio, a imagem apresentada é a palavra "stop" sem ruídos. Se o usuário apertar qualquer tecla, será apresentada ao lado da imagem original, uma imagem contendo apenas o ruído (decorrente da subtração imagem sem ruídos da imagem original).
 3-Novamente, apertando qualquer tecla, é possível ver os passos para a obtenção do contorno da palavra.
 
Para criar o executável, basta ir à pasta na qual estão os arquivos e digitar o comando: make. 
 
Exemplo de comando para executar o programa: ./morphology stop.jpeg 3.
*/

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

using namespace cv;
using namespace std;


Mat src;
Mat dst, temp;

char* op;

int Nerosions = 0;
int Ndilations = 0;
int Esize = 1;
int Dsize = 1;
int const max_Nerosions = 20;
int const max_Ndilations = 20;
int const max_Esize = 11;
int const max_Dsize = 11;


char* window_name = "Morphology";

void Morphology(int, void*){
    int i;
    Mat Element = getStructuringElement( MORPH_RECT,
                                        Size( 2*Esize + 1, 2*Esize+1 ),
                                        Point( Esize, Esize ) );
    
    Mat Element2 = getStructuringElement( MORPH_RECT,
                                         Size( 2*Dsize + 1, 2*Dsize+1 ),
                                         Point( Dsize, Dsize ) );
    
    
    temp = src.clone();
    dst = src.clone();
    
    
    
    if(strcmp(op,"1")==0){
        for(i=0;i<Ndilations;i++){
            dilate(temp, dst, Element2);
            temp = dst.clone();
        }
        for(i=0;i<Nerosions;i++){
            erode( temp, dst, Element);
            temp = dst.clone();
        }
        
    }
    if(strcmp(op,"2")==0){
        Dsize = 1;
        Esize = 1;
        Element2 = getStructuringElement( MORPH_RECT,
                                         Size( 2*Dsize + 1, 2*Dsize+1 ),
                                         Point( Dsize, Dsize ) );
        Element = getStructuringElement( MORPH_RECT,
                                        Size( 2*Esize + 1, 2*Esize+1 ),
                                        Point( Esize, Esize ) );
        erode(temp,dst,Element);
        dilate(dst,dst,Element2);
        dilate(dst,dst,Element2);
        erode(dst,dst,Element);
        imshow(window_name, dst);
        subtract(src,dst,dst);
        waitKey(0);
        
    }
    if(strcmp(op,"3")==0){
        Dsize = 1;
        Esize = 1;
        Element2 = getStructuringElement( MORPH_RECT,
                                         Size( 2*Dsize + 1, 2*Dsize+1 ),
                                         Point( Dsize, Dsize ) );
        Element = getStructuringElement( MORPH_RECT,
                                        Size( 2*Esize + 1, 2*Esize+1 ),
                                        Point( Esize, Esize ) );
        
        
        erode(temp,dst,Element);
        dilate(dst,dst,Element2);
        dilate(dst,dst,Element2);
        erode(dst,dst,Element);
        imshow(window_name, dst);
        waitKey(0);
        erode(temp,temp,Element);
        dilate(temp,temp,Element2);
        dilate(temp,temp,Element2);
        erode(temp,temp,Element);
        dilate(temp,temp,Element2);
        imshow(window_name, temp);
        waitKey(0);
        erode(dst,dst,Element);
        subtract(temp,dst,dst);
        imshow(window_name, dst);
        waitKey(0);
        
    }
    
    hconcat (src, dst, dst);
    
    imshow(window_name, dst);
}

int main(int argc, char** argv){
    
    src = imread( argv[1] );
    op=argv[2];
    
    if( !src.data ){
        cout<<"Error!"<<endl;
        
        return -1;
    }
    
    /// Create a window
    namedWindow(window_name, WINDOW_NORMAL );
    
    
    if(strcmp(op,"1")==0){
        createTrackbar( "Erosions:", window_name, &Nerosions, max_Nerosions, Morphology );
        createTrackbar( "Dilations:", window_name, &Ndilations, max_Ndilations, Morphology );
        createTrackbar( "Dilation Kernel Size:", window_name, &Dsize, max_Dsize, Morphology );
        createTrackbar( "Erosion Kernel Size:", window_name, &Esize, max_Esize, Morphology );
        
    }
    
    
    Morphology(0, 0);
    
    waitKey(0);
    return 0;
}