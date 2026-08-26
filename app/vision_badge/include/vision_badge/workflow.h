/* SPDX-License-Identifier: Apache-2.0 */

#ifndef CONTEST2026_441_VISION_BADGE_WORKFLOW_H
#define CONTEST2026_441_VISION_BADGE_WORKFLOW_H

#include <vision_badge/types.h>

int vision_badge_run_once(struct vision_badge_context_s *context,
                          const char *prompt,
                          struct vision_badge_image_s *image,
                          struct vision_badge_result_s *result);

const char *vision_badge_stage_name(enum vision_badge_stage_e stage);

#endif /* CONTEST2026_441_VISION_BADGE_WORKFLOW_H */
