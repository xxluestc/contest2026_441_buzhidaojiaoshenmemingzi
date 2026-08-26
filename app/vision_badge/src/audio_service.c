/* SPDX-License-Identifier: Apache-2.0 */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include <vision_badge/config.h>
#include <vision_badge/services.h>

#ifndef O_NONBLOCK
#  define O_NONBLOCK 0
#endif

int audio_service_probe(struct vision_badge_probe_s *probe)
{
  int fd;

  if (probe == NULL)
    {
      return -EINVAL;
    }

  fd = open(CONFIG_CONTEST2026_441_VISION_BADGE_AUDIO_DEVPATH,
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

int audio_service_record(void *buffer, size_t capacity, size_t *recorded)
{
  if (buffer == NULL || capacity == 0 || recorded == NULL)
    {
      return -EINVAL;
    }

  /* PCM capture is a phase-two interface; the board device path is unverified. */

  *recorded = 0;
  return -ENOSYS;
}
