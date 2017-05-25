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

  int loadStatus=instance.load_templates(argc, argv);
  fix_size(instance.v_templates);
  if(instance.get_loadStatus() < 0 || loadStatus<0)
    return EXIT_FAILURE;

  for(auto& data:instance.get_v_data())
  {
    data.Pic_color.convertTo(data.Pic_color_high_contrast, -1, 2, 0);     // 2x contrast
    HSV_pic(data.Pic_color_high_contrast, data.Pic_HSV);                  // Re-write

        show_pic(data.Pic_color_high_contrast, "High contrast");

    instance.extract_red_HSV(data);
        show_pic(data.Pic_HSV_red, "Red");
    create_contours(data.Pic_HSV_red, data.v_red_contours);
    instance.filter_red_contours(data);

    // show_pic(data.Pic_color, "Color");
    show_pic(data.Pic_th, "th");
    waitKey(0);

    for(auto& possible_sign:data.v_signs)
    {
      if(possible_sign.shape == Shape::circular)
      {
        unsigned index=0;
        for(const auto& circular_template:instance.v_templates)
        {
          Mat result;
          if(cv_lib::template_matching(data.Pic_HSV_red, possible_sign.roi, circular_template)==true)
          {
            int pos= instance.v_picNames[index].find("_template");
            std::string name(instance.v_picNames[index], 0, pos);
            possible_sign.name= name;
            std::cout<<"This is a "<<name<<std::endl;
            break;
          }

          ++index;
          waitKey();
        }
      }

    }
    // show_pic(data.Pic_HSV_blue, "Blue");

    // Mat closed;
    // morpho_pic(data.Pic_HSV_red, data.Pic_HSV_red, 3, MORPH_CLOSE);
    // morpho_pic(data.Pic_HSV_red, data.Pic_HSV_red, 3, MORPH_OPEN);
    //  show_pic(data.Pic_HSV_red, "closed");

    continue;
    create_contours(data.Pic_HSV_blue, data.v_blue_contours);
    instance.extract_blue_HSV(data);
    instance.filter_blue_contours(data);

    Mat result;

    // return 0;


  waitKey();
}

  waitKey();

  return EXIT_SUCCESS;
}
