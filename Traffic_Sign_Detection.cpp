/*
 * Author:      Eduardo Cáceres de la Calle
 * Subject:     Visión Artificial
 * Degree:      Industrial Electronics and Automatic Control Engineering
 * University:  Universidad de Valladolid (UVa) - EII
 *
 * Code written in 2017, during my first contact with OpenCV.
 * Uploaded for educational purposes only.
 *
 */


#include <opencv2/opencv.hpp>
#include "../Academic_ComputerVision/code/header/cv_basic_operations.hpp"
#include "../Academic_ComputerVision/code/header/cv_library.hpp"
#include "header/Sign_Detection.hpp"
#include <vector>
#include <string>
#include <cassert>

using namespace cv;
using namespace cv_lib;

const std::string relative_path("../samples");

int main(int argc, char* argv[])
{
  // Sign_Detection instance(argc, argv);
  Sign_Detection instance(relative_path);

  if(instance.get_loadStatus() < 0)
    return EXIT_FAILURE;

  for(auto& data:instance.get_v_data())
  {
    /// Reduce the noise so we avoid false circle detection
    Mat Pic_or= data.Pic_color.clone();
    Mat aux;
    GaussianBlur( data.Pic_grey, aux, Size(7, 7), 2, 2 );

std::vector<Vec3f> circles;

/// Apply the Hough Transform to find the circles
cv::HoughCircles( aux, circles, CV_HOUGH_GRADIENT, 1, aux.rows/8, 100, 50, 0, 500 );//Los dos ultimos param es para radio min y radio max
/// Draw the circles detected
for( size_t i = 0; i < circles.size(); i++ )
{
    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
    // circle center
    circle( Pic_or, center, 3, Scalar(0,255,0), -1, 8, 0 );
    // circle outline
    circle( Pic_or, center, radius, Scalar(0,0,255), 3, 8, 0 );
}

/// Show your results
namedWindow( "Circulos Hough", CV_WINDOW_AUTOSIZE );
imshow( "Circulos Hough", Pic_or );

    data.Pic_color.convertTo(data.Pic_color_high_contrast, -1, 2, 0);     // 2x contrast
    HSV_pic(data.Pic_color_high_contrast, data.Pic_HSV);                  // Re-write

    instance.extract_red_HSV(data);
    instance.extract_blue_HSV(data);

    // show_pic(data.Pic_color, "Color");
    show_pic(data.Pic_color_high_contrast, "High contrast");
    show_pic(data.Pic_HSV_red, "Red");





    Mat Pic_or2= data.Pic_color.clone();
    Mat aux2;
    GaussianBlur( data.Pic_grey, aux2, Size(7, 7), 2, 2 );

std::vector<Vec3f> circles2;

/// Apply the Hough Transform to find the circles
cv::HoughCircles( aux2, circles2, CV_HOUGH_GRADIENT, 1, aux2.rows/8, 100, 50, 0, 500 );//Los dos ultimos param es para radio min y radio max
/// Draw the circles detected
for( size_t i = 0; i < circles.size(); i++ )
{
    Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    int radius = cvRound(circles[i][2]);
    // circle center
    circle( Pic_or2, center, 3, Scalar(0,255,0), -1, 8, 0 );
    // circle outline
    circle( Pic_or2, center, radius, Scalar(0,0,255), 3, 8, 0 );
}

/// Show your results
namedWindow( "Circulos Hough", CV_WINDOW_AUTOSIZE );
imshow( "Circulos Hough", Pic_or2 );

    // show_pic(data.Pic_HSV_blue, "Blue");

    // Mat closed;
    // morpho_pic(data.Pic_HSV_red, data.Pic_HSV_red, 3, MORPH_CLOSE);
    // morpho_pic(data.Pic_HSV_red, data.Pic_HSV_red, 3, MORPH_OPEN);
    //  show_pic(data.Pic_HSV_red, "closed");

    create_contours(data.Pic_HSV_blue, data.v_blue_contours);
    create_contours(data.Pic_HSV_red, data.v_red_contours);

    instance.filter_red_contours(data);
    instance.filter_blue_contours(data);


  waitKey();
}

  waitKey();

  return EXIT_SUCCESS;
}
