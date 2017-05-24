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

#define Pic_color instance.v_Pic_color[num_pic]
#define Pic_grey  instance.v_Pic_grey[num_pic]
#define Pic_th  instance.v_Pic_th[num_pic]

using namespace cv;
using namespace cv_lib;

int main(int argc, char* argv[])
{
  Sign_Detection instance(argc, argv);

  if(instance.get_loadStatus() < 0)
    return EXIT_FAILURE;

  show_pic(instance.v_Pic_color, instance.v_picName);

  instance.HSV_treatment();
  for(auto&x:instance.v_Pic_color)
    medianBlur(x, x, 7);

  waitKey();

  instance.HSV_treatment();
  waitKey();


  th_pic(instance.v_Pic_grey, instance.v_Pic_th);
  show_pic(instance.v_Pic_th, "OTSU thresholding");
  for(int num_pic=0; num_pic < instance.v_Pic_th.size(); ++num_pic)   // Th treatment
  {

  }


  waitKey();
  return EXIT_SUCCESS;
}
