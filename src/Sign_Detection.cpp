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
  fix_size(v_Pic_color);
  grey_pic(v_Pic_color, v_Pic_grey);
  HSV_pic(v_Pic_color, v_Pic_HSV);
}

Sign_Detection::Sign_Detection(const std::string relative_path)
: samples_path(relative_path)
{
  loadStatus= cv_lib::load_from_folder(samples_path, v_picName, v_Pic_color);

  color_pic(v_Pic_color, v_Pic_color);
  fix_size(v_Pic_color);
  grey_pic(v_Pic_color, v_Pic_grey);
  HSV_pic(v_Pic_color, v_Pic_HSV);
}

Sign_Detection::~Sign_Detection()
{

}

void Sign_Detection::HSV_treatment()
{
  unsigned cont=0;
  for(const auto& HSV:v_Pic_HSV)
  {
    show_pic(v_Pic_color[cont], "or");
    ++cont;
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

    v_Pic_HSV_blue.push_back(blue_hue);
    v_Pic_HSV_red.push_back(red_hue);

    show_pic(red_hue, "HSV red th");
    show_pic(blue_hue, "HSV blue th");

    Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
    Point anchor1 = Point(-1,-1);
    erode(red_hue, red_hue, kernel1, anchor1, 1); // TO-DO
    dilate(red_hue, red_hue, kernel1, anchor1, 2);


    waitKey();
  }
}
