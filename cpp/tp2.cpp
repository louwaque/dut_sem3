#include "ColorImage.hpp"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ifstream catFile("cat_ascii.ppm", std::ios::binary);
  ColorImage *catImage = ColorImage::readPPM(catFile);
  catFile.close();

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  ofstream catSave("tp2_ascii.ppm", std::ios::binary | std::ios::out);
  catImage->writePPM(catSave);
  catSave.close();

  ofstream catSaveJPEG("cat_out.jpeg", std::ios::binary | std::ios::out);
  catImage->writeJPEG(catSaveJPEG);
  catSaveJPEG.close();

  delete catImage;
  catImage = nullptr;

  catFile.open("cat_brut.ppm", std::ios::binary);
  catImage = ColorImage::readPPM(catFile);
  catFile.close();

  catImage->rectangle(10, 10, 300, 200, ColorPixel(255, 0, 0));
  catImage->rectangle(15, 15, 280, 180, ColorPixel(0, 255, 0));
  catImage->rectangle(20, 20, 270, 170, ColorPixel(0, 0, 255));

  catImage->fillRectangle(90, 85, 40, 20, ColorPixel(234, 120, 200));
  catImage->fillRectangle(190, 87, 40, 20, ColorPixel(234, 120, 200));

  catImage->circle(109, 94, 20, ColorPixel(255, 0, 0));
  catImage->circle(212, 99, 20, ColorPixel(255, 0, 0));
  catImage->fillCircle(150, 96, 10, ColorPixel(0, 255, 0));

  catSave.open("tp2_brut.ppm", std::ios::binary | std::ios::out);
  catImage->writePPM(catSave);
  catSave.close();

  delete catImage;
  catImage = nullptr;

  catFile.open("cat_out.jpeg", std::ios::binary);
  catImage = ColorImage::readJPEG(catFile);
  catFile.close();

  catImage->fillRectangle(140, 155, 40, 20, ColorPixel(255, 28, 28));

  catSaveJPEG.open("cat_out_2.jpeg", std::ios::binary | std::ios::out);
  catImage->writeJPEG(catSaveJPEG, 100);
  catSaveJPEG.close();

  std::srand(std::time(0));
  for (unsigned int quality = 0; quality <= 100; quality += 5) {
    std::ostringstream oss; // Variable pour former le nom de chaque fichier.
    oss << "cat_out_" << std::setfill('0') << std::setw(3) << quality << ".jpg";

    ofstream save(oss.str().c_str(), std::ios::binary | std::ios::out);

    size_t x = std::rand() % catImage->width(),
           y = std::rand() % catImage->height();
    catImage->fillRectangle(
        x, y, std::rand() % (catImage->width() - x),
        std::rand() % (catImage->height() - y),
        ColorPixel(std::rand() % 255, std::rand() % 255, std::rand() % 255));
    catImage->writeJPEG(save, quality);
  }

  delete catImage;
  catImage = nullptr;

  catFile.open("little_cat.ppm", std::ios::binary);
  catImage = ColorImage::readPPM(catFile);
  catFile.close();

  ColorImage *scaleCat = catImage->simpleScale(4000, 5000);

  catSave.open("cat_simple_scale.ppm", std::ios::binary | std::ios::out);
  scaleCat->writePPM(catSave);
  catSave.close();

  delete scaleCat;

  scaleCat = catImage->bilinearScale(4000, 5000);

  catSave.open("cat_bilinear_scale.ppm", std::ios::binary | std::ios::out);
  scaleCat->writePPM(catSave);
  catSave.close();

  delete scaleCat;
  delete catImage;

  return 0;
}
