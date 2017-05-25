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
    th_pic(instance.Pic_grey, instance.Pic_th);
    HSV_pic(instance.Pic_color, instance.Pic_HSV);

    v_data.push_back(instance);
  }
}

Sign_Detection::~Sign_Detection()
{

}

int Sign_Detection::load_templates(const int& argc, char* argv[]) {   // TO-IMPROVE

    static int n_pic=0;

    for(int i=1; i<argc; ++i)
    {
      ++n_pic;

      if(argc < n_pic+1) {
        std::cout<<"Missing picture name"<<std::endl;
        return -1;
      }

      Mat pic= imread( argv[n_pic], CV_LOAD_IMAGE_UNCHANGED);

      if( pic.empty())  {
        std::cout<<"Error opening picture file "<<argv[n_pic]<<std::endl;
        return -1;
      }
      else
        v_templates.push_back(pic);

      char chpicName[CHL];
      strcpy(chpicName, argv[n_pic]);
      std::string picName(chpicName);

      int n= picName.find("templates/");
      picName.erase(picName.begin(), picName.begin() + n + 10);
      v_picNames.push_back(picName);
    }
    return 0;
  }

void Sign_Detection::extract_red_HSV(Data_pic& data)  {
  Mat red_hue;

  Mat red_hue_upper;
  cv::inRange(data.Pic_HSV, RED_HSV_UPPER_LOW, RED_HSV_UPPER_HIGH, red_hue_upper);
  Mat red_hue_lower;
  cv::inRange(data.Pic_HSV, RED_HSV_LOWER_LOW, RED_HSV_LOWER_HIGH, red_hue_lower);

  red_hue=(red_hue_lower | red_hue_upper);
  th_pic(red_hue, red_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);
  data.Pic_HSV_red= red_hue;

  // show_pic(red_hue, "HSV red th");
}

void Sign_Detection::extract_blue_HSV(Data_pic& data) {
  Mat blue_hue;

  cv::inRange(data.Pic_HSV, BLUE_HSV_LOW, BLUE_HSV_HIGH, blue_hue);
  th_pic(blue_hue, blue_hue, 125, CV_THRESH_BINARY | CV_THRESH_OTSU);
  data.Pic_HSV_blue= blue_hue;

  // show_pic(blue_hue, "HSV blue th");
}

void Sign_Detection::filter_red_contours(Data_pic& data)
{
  Mat Pic= data.Pic_color.clone();

  std::vector<Mat> v_Pic_roi;
  std::vector<RotatedRect>  v_rotated_rect;
  std::vector<RotatedRect>  v_ellipse;
  v_rotated_rect.reserve(data.v_red_contours.size());
  v_ellipse.reserve(data.v_red_contours.size());
  v_Pic_roi.reserve(data.v_red_contours.size());
  double min_area= 0.1 * sqrt(static_cast<double>(data.Pic_HSV_red.rows) * static_cast<double>(data.Pic_HSV_red.cols));
  // std::cout<<min_area<<std::endl;    // TO-CHECK
  const double coef_x= 0.5, coef_y= 0.5;
  const double min_circularity= 0.70;
  const double acceptable_circularity= 0.50;

  for(int index=0; index<data.v_red_contours.size(); ++index)
  {
    auto contour= data.v_red_contours[index];
    auto rotated_rect= minAreaRect(contour);

    double area= contourArea(contour, false);
    double perimeter= arcLength(contour, true);
    double circularity= 4*PI*area/(perimeter*perimeter);

    if(area > min_area && rotated_rect.size.height > coef_y*min_area && rotated_rect.size.width > coef_x*min_area)
    {
        std::cout<<"Circularity: "  << circularity << std::endl;

      std::vector<cv::Point> poly;
      cv::approxPolyDP(Mat(contour), poly, arcLength(Mat(contour), true) * 0.01, true);

      cv::approxPolyDP(contour, poly, 0.02*perimeter, true);

      std::cout<<"Lados: "<<poly.size()<<std::endl;

      // switch(poly.size());

      if(circularity>min_circularity || poly.size()==3 || poly.size()==8)
      {
        if(circularity>min_circularity)
        {
          Sign found;
          found.color= Color::red;
          found.shape= Shape::circular;
          minEnclosingCircle((Mat)contour, found.center, found.radius);
          found.roi= boundingRect(contour);

          if(poly.size()==8)        // TO-CHECK: demasiado común
            found.sign_type= Sign_type::stop;

          data.v_signs.push_back(found);
        }
        else if(circularity>acceptable_circularity && poly.size()==3)
        {
          Sign found;
          found.color= Color::red;
          found.shape= Shape::triangular;

          data.v_signs.push_back(found);
        }


        // for(int i=0; i<poly.size(); ++i)            // DEBUG
        // {
        //   line(Pic, poly[i], poly[i+1], GREEN, 1);
        //   if(i==poly.size()-1)
        //     line(Pic, poly[i], poly[0], GREEN, 1);
        // }
        // show_pic(Pic, "poly");

        // v_ellipse.push_back(fitEllipse(contour));   // DEBUG
        // v_rotated_rect.push_back(rotated_rect);
        //
        // drawContours(Pic, data.v_red_contours, index, GREEN, 1);        // Debug
        // ellipse(Pic, v_ellipse.back(), YELLOW, 1);                    // Debug
        // Point2f rect_points[4]; rotated_rect.points(rect_points);     // Debug
        // draw_rectangle(Pic, rect_points, BLUE);                       // Debug
        //
        // show_pic(Pic, "contours");
        // waitKey();
      }
    }
  }
  // destroyAllWindows();
}

void Sign_Detection::filter_blue_contours(Data_pic& data)
{

}
