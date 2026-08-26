/* SPDX-License-Identifier: Apache-2.0 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <vision_badge/config.h>
#include <vision_badge/services.h>

#ifndef O_NONBLOCK
#  define O_NONBLOCK 0
#endif

int camera_service_probe(struct vision_badge_probe_s *probe)
{
  int fd;

  if (probe == NULL)
    {
      return -EINVAL;
    }

  fd = open(CONFIG_CONTEST2026_441_VISION_BADGE_CAMERA_DEVPATH,
            O_RDONLY | O_NONBLOCK);
  if (fd < 0)
    {
      probe->available = false;
      probe->error_code = errno;
      return -errno;
    }

  close(fd);
  probe->available = true;
  probe->error_code = 0;
  return 0;
}

int camera_service_capture(struct vision_badge_image_s *image)
{
  if (image == NULL || image->data == NULL || image->capacity == 0)
    {
      return -EINVAL;
    }

  /* V4L2 single-frame capture and JPEG extraction are implemented at M3/M4. */

  image->size = 0;
  return -ENOSYS;
}
