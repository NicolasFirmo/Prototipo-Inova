#include <opencv2/opencv.hpp>
#include <iostream>

static const std::string p_video = "./src/videos/";

static float horizontal[] = {-1, 0, 1,
                             -2, 0, 2,
                             -1, 0, 1};
static float vertical[] = {-1, -2, -1,
                           0, 0, 0,
                           1, 2, 1};

int main(int argc, char const *argv[])
{
  cv::VideoCapture cap(p_video + "VID_20191205_145120.mp4");
  cv::Mat mask(3, 3, CV_32F, vertical);
  cv::Mat video;

  if (!cap.isOpened())
  {
    std::cout << "Camera não abriu\n";
    return -1;
  }

  bool play = true;

  while (true)
  {
    if (play)
      cap >> video;
    auto key = cv::waitKey(10);
    if (key == 27)
      break;
    if (key == 'p')
      play = !play;

    std::cout << "(int)key: " << key << ", (char)key: " << (char)key << '\n';

    cv::imshow("Prototipo", video);
  }

  return 0;
}
