############################################################################
# Contest 2026 team 441 vision badge - Makefile
############################################################################

include $(APPDIR)/Make.defs

PROGNAME  = vision_badge
PRIORITY  = 100
STACKSIZE = $(CONFIG_CONTEST2026_441_VISION_BADGE_STACKSIZE)
MODULE    = $(CONFIG_LVX_USE_DEMO_CONTEST2026_441_VISION_BADGE)

CFLAGS += ${INCDIR_PREFIX}$(APPDIR)/packages/demos/contest2026_441_vision_badge/include

MAINSRC = src/vision_badge_main.c
CSRCS   = src/workflow.c src/camera_service.c src/vision_service.c
CSRCS  += src/audio_service.c src/feedback_service.c

include $(APPDIR)/Application.mk
