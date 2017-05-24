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
    data.Pic_color.convertTo(data.Pic_color_high_contrast, -1, 2, 0);     // 2x contrast
    HSV_pic(data.Pic_color_high_contrast, data.Pic_HSV);                  // Re-write

    instance.extract_red_HSV(data);
    instance.extract_blue_HSV(data);

    show_pic(data.Pic_color);
    show_pic(data.Pic_color_high_contrast, "contrast");

    waitKey();

    Mat blurr;
    medianBlur(data.Pic_color, blurr, 7);
    show_pic(blurr, data.picName);

  waitKey();
}

  instance.HSV_treatment();
  waitKey();

  return EXIT_SUCCESS;
}
