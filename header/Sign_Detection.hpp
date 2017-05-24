/*
 * Author:      Eduardo Cáceres de la Calle
 * Subject:     Visión Artificial
 * Degree:      Industrial Electronics and Autocv::Matic Control Engineering
 * University:  Universidad de Valladolid (UVa) - EII
 *
 * Code written in 2017, during my first contact with OpenCV.
 * Uploaded for educational purposes only.
 *
 */


#ifndef Sign_Detection_HPP_INCLUDED
#define Sign_Detection_HPP_INCLUDED

#include "../../Academic_ComputerVision/code/header/cv_headers.hpp"
#include "../../Academic_ComputerVision/code/header/cv_basic_operations.hpp"
#include "../../Academic_ComputerVision/code/header/cv_library.hpp"

#include "Sign_Detection_header.hpp"

class Data_pic
{
public:
  int index;
  std::string picName;
  cv::Mat Pic_color;
  cv::Mat Pic_color_high_contrast;
  cv::Mat Pic_grey;
  cv::Mat Pic_HSV;
  cv::Mat Pic_HSV_red;
  cv::Mat Pic_HSV_blue;
  cv::Mat Pic_th;
  cv::Mat Pic_final;
  std::vector<std::vector<cv::Point> >  v_contours;
};

class Sign_Detection
{
public:
  Sign_Detection();
  Sign_Detection(const std::string relative_path);
  Sign_Detection(const int& argc, char* argv[]);
  ~Sign_Detection();

  std::vector<Data_pic> get_v_data() const { return v_data; }
  bool get_loadStatus()             const { return loadStatus; }
  void HSV_treatment();
  void extract_red_HSV(Data_pic& data);
  void extract_blue_HSV(Data_pic& data);
private:
  std::vector<Data_pic> v_data;
  bool loadStatus;
  std::string samples_path;
  cv_lib::UserData user_data;



  };


#endif // Sign_Detection_HPP_INCLUDED
