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

class Sign_Detection
{
public:
  Sign_Detection();
  Sign_Detection(const int& argc, char* argv[]);
  ~Sign_Detection();

  // private:
    std::vector<cv::Mat> v_Pic;
    std::vector<cv::Mat> v_Pic_color;
    std::vector<cv::Mat> v_Pic_grey;
    std::vector<cv::Mat> v_Pic_HSV;
    std::vector<cv::Mat> v_Pic_HSV_red;
    std::vector<cv::Mat> v_Pic_HSV_blue;
    std::vector<cv::Mat> v_Pic_th;
    std::vector<cv::Mat> v_Pic_original;
    std::vector<cv::Mat> v_Pic_final;
    std::vector<std::string>  v_picName;
    std::vector <std::vector<std::vector<cv::Point> > > v_contours;

    cv_lib::UserData user_data;

    bool get_loadStatus()   const { return loadStatus; }

    void HSV_treatment();

  private:
    bool loadStatus;
};


#endif // Sign_Detection_HPP_INCLUDED
