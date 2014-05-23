#include "Webcam.h"

using namespace std;

Webcam::Webcam()
{
    capture = cvCreateCameraCapture(CV_CAP_ANY);
    image = NULL;
    image = cvQueryFrame(capture);
}

Webcam::~Webcam()
{
    cvReleaseCapture(&capture);
    /// cvReleaseImage(&image); /// <--- semble inutile
}

Image * Webcam::getFrame()
{
    image = cvQueryFrame(capture);

    Image * retour = new Image(image->width, image->height, 0,0,0);

    for (int y = 0; y < image->height; ++y)
    {
        for (int x = 0; x < image->width; ++x)
        {
            CvScalar p = cvGet2D (image, y, x);
            /// les couleurs sont inversées dans opencv : BGR au lieu de RGB
            retour->setPixel(x,y,color(p.val[2],p.val[1],p.val[0],p.val[3]));
        }
    }

    return retour;
}

int Webcam::width()
{
    return image->width;
}

int Webcam::height()
{
    return image->height;
}

