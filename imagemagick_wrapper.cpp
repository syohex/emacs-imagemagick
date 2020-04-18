#include "imagemagick_wrapper.h"

#include <Magick++.h>

void el_magick_initialize() {
    Magick::InitializeMagick(".");
}

void el_magick_scale(const char *src, const char *dest, const char *geo) {
    Magick::Image image;
    image.read(src);
    image.scale(geo);
    image.write(dest);
}

void el_magick_blur(const char *src, const char *dest, double radius, double sigma) {
    Magick::Image image;
    image.read(src);
    image.blur(radius, sigma);
    image.write(dest);
}

void el_magick_size(const char *src, size_t *width, size_t *height) {
    Magick::Image image;
    image.read(src);
    const Magick::Geometry geo = image.size();

    *width = geo.width();
    *height = geo.height();
}