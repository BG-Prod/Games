#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;

void traitement(IplImage *image,IplImage *pimage);

int main()
{
    // Touche clavier
    char key;
    // Image
    IplImage *base;
    IplImage *image;
    IplImage *pimage;
    // Capture vidéo
    CvCapture *capture;



    // Ouvrir le flux vidéo
    //capture = cvCreateFileCapture("/path/to/your/video/test.avi"); // chemin pour un fichier
    capture = cvCreateCameraCapture(CV_CAP_ANY);

    // Vérifier si l'ouverture du flux est ok
    if (!capture)
    {
        printf("Ouverture du flux vidéo impossible !\n");
        return 1;
    }

    // Définition de la fenêtre
    cvNamedWindow("Arvernes At War", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Ben", CV_WINDOW_AUTOSIZE);

        base = cvQueryFrame(capture);
        image = base;

    // Boucle tant que l'utilisateur n'appuie pas sur la touche q (ou Q)
    while(key != 'q' && key != 'Q' && key != 27)
    {
        // On récupère une image
        pimage = image;
        image = cvQueryFrame(capture);

        // affichage de l'image originale
        cvShowImage("Ben", pimage);

        // traitement
        traitement(image, base);

        // On affiche l'image dans une fenêtre
        cvShowImage( "Arvernes At War", image);

        // On attend 10ms
        key = cvWaitKey(10);
    }

    cvReleaseCapture(&capture);
    cvReleaseImage(&image);
    cvDestroyWindow("Arvernes At War");

    return 0;
}

void traitement(IplImage *img, IplImage *pimg)
{
  CvScalar p;
  int x, y, k;

  assert (img->depth == IPL_DEPTH_8U);

  for (y = 0; y < img->height; ++y)
  {
    for (x = 0; x < img->width; ++x)
    {
      p = cvGet2D (img, y, x);
      int tmp = 0;
      for (k = 0; k < img->nChannels-1; ++k)
      {
        tmp += p.val[k];
      }
      if((p.val[0])*2 > (p.val[2]+p.val[1])+100)
      {
          for (k = 0; k < img->nChannels; ++k)
          {
            p.val[k] = 0;
          }
          p.val[0] = 255;
          cvSet2D (img, y, x, p);
      }
      if((p.val[2])*2 > (p.val[0]+p.val[1])+100)
      {
          for (k = 0; k < img->nChannels; ++k)
          {
            p.val[k] = 0;
          }
          p.val[2] = 255;
          cvSet2D (img, y, x, p);
      }
      if((p.val[1]+p.val[2]) > (p.val[0]*2)+50)
      {
          for (k = 0; k < img->nChannels; ++k)
          {
            p.val[k] = 0;
          }
          p.val[1] = 255;
          cvSet2D (img, y, x, p);
      }/*
      else if(tmp < 200)
      {
          for (k = 0; k < img->nChannels; ++k)
          {
            p.val[k] = 0;
          }
          cvSet2D (img, y, x, p);
      }
      else if(tmp < 400)
      {
          for (k = 0; k < img->nChannels; ++k)
          {
            p.val[k] = 100;
          }
          cvSet2D (img, y, x, p);
      }
      else
      {
          for (k = 0; k < img->nChannels; ++k)
          {
            p.val[k] = 255;
          }
          cvSet2D (img, y, x, p);
      }*/
    }
  }
}


