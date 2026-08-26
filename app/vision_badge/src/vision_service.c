/* SPDX-License-Identifier: Apache-2.0 */

#include <errno.h>

#include <vision_badge/services.h>

int vision_service_query(const struct vision_badge_image_s *image,
                         const char *prompt,
                         struct vision_badge_result_s *result)
{
  if (image == NULL || image->data == NULL || image->size == 0 ||
      prompt == NULL || prompt[0] == '\0' || result == NULL ||
      result->text == NULL || result->capacity == 0)
    {
      return -EINVAL;
    }

  /* HTTPS upload, MiMo request and bounded JSON parsing are implemented at M5. */

  result->length = 0;
  result->direction_hint = 0;
  return -ENOSYS;
}
