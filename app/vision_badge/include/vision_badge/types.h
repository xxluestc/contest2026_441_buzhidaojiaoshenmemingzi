/* SPDX-License-Identifier: Apache-2.0 */

#ifndef CONTEST2026_441_VISION_BADGE_TYPES_H
#define CONTEST2026_441_VISION_BADGE_TYPES_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum vision_badge_stage_e
{
  VISION_BADGE_STAGE_IDLE = 0,
  VISION_BADGE_STAGE_CAPTURE,
  VISION_BADGE_STAGE_QUERY,
  VISION_BADGE_STAGE_FEEDBACK,
  VISION_BADGE_STAGE_DONE,
  VISION_BADGE_STAGE_ERROR
};

enum vision_badge_image_format_e
{
  VISION_BADGE_IMAGE_JPEG = 0
};

struct vision_badge_probe_s
{
  bool available;
  int error_code;
};

struct vision_badge_image_s
{
  uint8_t *data;
  size_t capacity;
  size_t size;
  uint16_t width;
  uint16_t height;
  enum vision_badge_image_format_e format;
};

struct vision_badge_result_s
{
  char *text;
  size_t capacity;
  size_t length;
  int direction_hint;
};

struct vision_badge_context_s
{
  enum vision_badge_stage_e stage;
  int last_error;
};

#endif /* CONTEST2026_441_VISION_BADGE_TYPES_H */
