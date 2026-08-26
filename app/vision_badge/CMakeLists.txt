# SPDX-License-Identifier: Apache-2.0

if(CONFIG_LVX_USE_DEMO_CONTEST2026_441_VISION_BADGE)
  nuttx_add_application(
    NAME vision_badge
    SRCS
      src/vision_badge_main.c
      src/workflow.c
      src/camera_service.c
      src/vision_service.c
      src/audio_service.c
      src/feedback_service.c
    STACKSIZE ${CONFIG_CONTEST2026_441_VISION_BADGE_STACKSIZE}
    PRIORITY 100
    INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include)
endif()
