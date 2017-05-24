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


#include "../header/Sign_Detection.hpp"

using namespace cv;
using namespace cv_lib;

Sign_Detection::Sign_Detection()
{
  assert(0);
}

Sign_Detection::Sign_Detection(const int& argc, char* argv[])
{
  loadStatus= cv_lib::init_pic(argc, argv, v_picName, v_Pic_color);
  color_pic(v_Pic_color, v_Pic_color);
  grey_pic(v_Pic_color, v_Pic_grey);
  HSV_pic(v_Pic_color, v_Pic_HSV);
}

Sign_Detection::~Sign_Detection()
{

}

void Sign_Detection::HSV_treatment()
{
  for(const auto& HSV:v_Pic_HSV)
  {
    Mat red_hue, blue_hue;

    Mat red_hue_upper;
    inRange(HSV, RED_HSV_UPPER_LOW, RED_HSV_UPPER_HIGH, red_hue_upper);
    Mat red_hue_lower;
    inRange(HSV, RED_HSV_LOWER_LOW, RED_HSV_LOWER_HIGH, red_hue_lower);

    red_hue=(red_hue_lower | red_hue_upper);

    inRange(HSV, BLUE_HSV_LOW, BLUE_HSV_HIGH, blue_hue);


    show_pic(red_hue, "HSV red");
    show_pic(blue_hue, "HSV blue");

    th_pic(red_hue, red_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);
    th_pic(blue_hue, blue_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);

    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    Point anchor1 = Point(-1,-1);
    Mat Pic2;
    // dilate(red_hue, red_hue, kernel1, anchor1, 4);
    // erode(red_hue, red_hue, kernel1, anchor1, 5);

      dilate(red_hue, red_hue, kernel1, anchor1, 2);

    show_pic(red_hue, "HSV red th");
    show_pic(blue_hue, "HSV blue th");



    v_Pic_HSV_blue.push_back(blue_hue);
    v_Pic_HSV_red.push_back(red_hue);
    // cv::bitwise_and(blue_hue, HSV, result);


    waitKey();
  }

}
