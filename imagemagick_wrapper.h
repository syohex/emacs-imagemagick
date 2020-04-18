#pragma once

#include <stddef.h>

#if __cplusplus
extern "C" {
#endif

/*!
@brief Initialize ImageMagick
*/
extern void el_magick_initialize();

/*!
@brief Scale image

@param[in] src source image path
@param[in] dest destination image path
@param[in] geo geometry
*/
extern void el_magick_scale(const char *src, const char *dest, const char *geo);

/*!
@brief Blur image

@param[in] src source image path
@param[in] dest destination image path
@param[in] radius
@param[in] sigma
*/
extern void el_magick_blur(const char *src, const char *dest, double radius, double sigma);

/*!
@brief Get image size

@param[in] src source image path
@param[out] width to set image width
@param[out] height to set image height
*/
extern void el_magick_size(const char *src, size_t *width, size_t *height);

#if __cplusplus
} // extern "C"
#endif