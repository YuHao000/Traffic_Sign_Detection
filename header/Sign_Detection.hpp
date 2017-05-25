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

enum class Shape {unknown_shape, triangular, circular, rectangular};

enum class Color {unknown_color, red, blue};

enum class Name {unknown_name, stop, prohibido, no_circulacion, circulacion_obligatoria, ceda, peaton, aparcamiento, paso_zebra, minusvalidos, taxi};

class Sign
{
public:
  Sign()
    :shape(Shape::unknown_shape), color(Color::unknown_color), name(Name::unknown_name)
   {

   }

  Shape shape;
  Color color;
  Name name;
};

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
  cv::Mat Pic_roi;
  cv::Mat Pic_final;
  std::vector<std::vector<cv::Point> >  v_contours;
  std::vector<std::vector<cv::Point> >  v_red_contours;
  std::vector<std::vector<cv::Point> >  v_blue_contours;

  std::vector<Sign> v_signs;
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
  void extract_red_HSV(Data_pic& data);
  void extract_blue_HSV(Data_pic& data);
  void filter_red_contours(Data_pic& data);
  void filter_blue_contours(Data_pic& data);
private:
  std::vector<Data_pic> v_data;
  bool loadStatus;
  std::string samples_path;
  cv_lib::UserData user_data;

  };


#endif // Sign_Detection_HPP_INCLUDED
