#include "stb_image.h"
#include <iostream>

int main() {
  const char *imagePath =
      "/home/sephix/Pictures/87uh0golsrjb1.png"; // Change this to the path of
                                                 // your image

  int width, height, channels;
  unsigned char *image = stbi_load(imagePath, &width, &height, &channels, 0);

  if (!image) {
    std::cerr << "Failed to load image: " << imagePath << std::endl;
    return 1;
  }

  int numPixels = width * height;

  std::cout << "Image dimensions: " << width << " x " << height << std::endl;
  std::cout << "Number of channels: " << channels << std::endl;
  std::cout << "Total number of pixels: " << numPixels << std::endl;

  // You can perform further processing or analysis here

  stbi_image_free(image); // Don't forget to free the image data

  return 0;
}
