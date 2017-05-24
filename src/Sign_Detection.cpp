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
  std::vector<std::string> v_picName;
  std::vector<cv::Mat> v_loaded_pics;

  loadStatus= cv_lib::init_pic(argc, argv, v_picName, v_loaded_pics);

  for(const auto& Pic:v_loaded_pics)
  {
    Data_pic instance;
    color_pic(Pic, instance.Pic_color);
    fix_size(instance.Pic_color, instance.Pic_color);
    grey_pic(instance.Pic_color, instance.Pic_grey);
    // instance.Pic_color.convertTo(instance.Pic_color_high_contrast, -1, 2, 0);
    HSV_pic(instance.Pic_color_high_contrast, instance.Pic_HSV);
  }

}

Sign_Detection::Sign_Detection(const std::string relative_path)
: samples_path(relative_path)
{
  std::vector<std::string> v_picName;
  std::vector<cv::Mat> v_loaded_pics;
  loadStatus= cv_lib::load_from_folder(samples_path, v_picName, v_loaded_pics);

  for(unsigned i=0; i<v_loaded_pics.size(); ++i)
  {
    Data_pic instance;
    instance.index= i;
    color_pic(v_loaded_pics[i], instance.Pic_color);
    fix_size(instance.Pic_color, instance.Pic_color);
    grey_pic(instance.Pic_color, instance.Pic_grey);
    HSV_pic(instance.Pic_color, instance.Pic_HSV);

    v_data.push_back(instance);
  }
}

Sign_Detection::~Sign_Detection()
{

}

void Sign_Detection::extract_red_HSV(Data_pic& data)
{
  Mat red_hue;

  Mat red_hue_upper;
  cv::inRange(data.Pic_HSV, RED_HSV_UPPER_LOW, RED_HSV_UPPER_HIGH, red_hue_upper);
  Mat red_hue_lower;
  cv::inRange(data.Pic_HSV, RED_HSV_LOWER_LOW, RED_HSV_LOWER_HIGH, red_hue_lower);

  red_hue=(red_hue_lower | red_hue_upper);

  show_pic(red_hue, "HSV red");

  th_pic(red_hue, red_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);

  show_pic(red_hue, "HSV red th");

  data.Pic_HSV_red= red_hue;
}

void Sign_Detection::extract_blue_HSV(Data_pic& data)
{
  Mat blue_hue;

  cv::inRange(data.Pic_HSV, BLUE_HSV_LOW, BLUE_HSV_HIGH, blue_hue);
  show_pic(blue_hue, "HSV blue");
  th_pic(blue_hue, blue_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);
  show_pic(blue_hue, "HSV blue th");

  data.Pic_HSV_blue= blue_hue;

}

void Sign_Detection::HSV_treatment()
{
  Mat a;
  // extract_red_HSV(a);
  // extract_blue_HSV(a);

  unsigned cont=0;
  // for(auto& x:v_data)
  // {
  //   show_pic(x.Pic_color, "Original");
  //   ++cont;
  //   Mat red_hue, blue_hue;
  //
  //   Mat red_hue_upper;
  //   cv::inRange(x.Pic_HSV, RED_HSV_UPPER_LOW, RED_HSV_UPPER_HIGH, red_hue_upper);
  //   Mat red_hue_lower;
  //   cv::inRange(x.Pic_HSV, RED_HSV_LOWER_LOW, RED_HSV_LOWER_HIGH, red_hue_lower);
  //
  //   red_hue=(red_hue_lower | red_hue_upper);
  //
  //   cv::inRange(x.Pic_HSV, BLUE_HSV_LOW, BLUE_HSV_HIGH, blue_hue);
  //
  //
  //   show_pic(red_hue, "HSV red");
  //   show_pic(blue_hue, "HSV blue");
  //
  //   th_pic(red_hue, red_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);
  //   th_pic(blue_hue, blue_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);
  //
  //   x.Pic_HSV_blue= blue_hue;
  //   x.Pic_HSV_red= red_hue;
  //
  //   show_pic(red_hue, "HSV red th");
  //   show_pic(blue_hue, "HSV blue th");
  //
  //   // Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
  //   // Point anchor1 = Point(-1,-1);
  //   // erode(red_hue, red_hue, kernel1, anchor1, 1);       // TO-DO
  //   // dilate(red_hue, red_hue, kernel1, anchor1, 2);
  //
  //   waitKey();
  // }
}
