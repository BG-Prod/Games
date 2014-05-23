#ifndef WEBCAM_H
#define WEBCAM_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Image.h>

using namespace cv;

class Webcam
{
    public:
        Webcam();
        virtual ~Webcam();

        Image * getFrame();
        int width();
        int height();

    protected:
        CvCapture *capture;
        IplImage * image;
};

#endif // WEBCAM_H
