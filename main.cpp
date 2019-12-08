#include <opencv2/opencv.hpp>
#include <iostream>
#include "Estruturas.h"
#include "Ferramentas.h"

static const std::string p_videos = "./src/videos/";
static const std::string p_images = "./src/images/";

static float horizontal[] = {-1, 0, 1,
                             -2, 0, 2,
                             -1, 0, 1};
static float vertical[] = {-1, -2, -1,
                           0, 0, 0,
                           1, 2, 1};

class Cursor
{
private:
  cv::Point2i m_pos;
  unsigned m_soma;

public:
  Cursor(cv::Point2i pos) : m_pos(pos), m_soma(0) {}
  ~Cursor() {}
  inline void e() { m_pos = m_pos - cv::Point(1, 0); }
  inline void d() { m_pos = m_pos + cv::Point(1, 0); }
  void desenha(cv::Mat mat)
  {
    cv::line(mat, m_pos, m_pos + cv::Point(0, 10), cv::Scalar(255, 100, 0), 2);
  }
  unsigned getSoma(cv::Mat matf)
  {
    m_soma = 0;
    for (int n = 0; n < 4; n++)
      for (int i = 0; i < 10; i++)
        m_soma += matf.at<uchar>(m_pos + cv::Point2i(n, i));

    return m_soma;
  }
};

int main(int argc, char const *argv[])
{
  cv::Mat mask(3, 3, CV_32F, vertical);
  cv::Mat img;
  img = cv::imread(p_images + "IMG_20191208_123003.jpg", cv::IMREAD_ANYCOLOR); // Read the file

  cv::resize(img, img, cv::Size(), 0.35, 0.35);

  cv::Mat imgf;
  cv::bilateralFilter(img, imgf, 7, 150, 150);

  auto roi = imgf(cv::Rect(cv::Point2i(0, 0), cv::Size2i(1280, 720)));
  cv::Mat roif, roiFiltrado;

  cvtColor(roi, roif, cv::COLOR_BGR2GRAY);
  roif.convertTo(roif, CV_32F);
  filter2D(roif, roiFiltrado,
           roif.depth(), mask, cv::Point(1, 1), 0);
  roiFiltrado = abs(roiFiltrado);
  roiFiltrado.convertTo(roiFiltrado, CV_8U);

  Cursor cursor(cv::Point2i(500, 560));

  int key = 0;
  int pontoCount = 0;
  bool ponto_linha = 0;

  while (key != 27)
  {
    std::cout << "Valor: " << std::setw(4) << cursor.getSoma(roiFiltrado) << "; " << (cursor.getSoma(roiFiltrado) > 2000 ? "linha" : "ponto") << "; pontos: " << pontoCount << '\n';
    nic::Relogio<nic::milisegundos, 0, 100, 255> r;
    key = cv::waitKey(1);

    cv::copyTo(img(cv::Rect(cv::Point2i(0, 0), cv::Size2i(1280, 720))), roi, cv::Mat(roi.rows, roi.cols, CV_8UC1, cv::Scalar(255)));

    switch (key)
    {
    case 'a':
      cursor.e();
      break;
    case 'd':
      cursor.d();
      break;
    default:
      break;
    }

    if (ponto_linha != (cursor.getSoma(roiFiltrado) > 2000))
    {
      ponto_linha = cursor.getSoma(roiFiltrado) > 2000;
      if (ponto_linha)
        pontoCount++;
    }

    cursor.desenha(roi);

    cv::imshow("Prototipo", roi);
    cv::imshow("Filtro", roiFiltrado);
  }

  return 0;
}
