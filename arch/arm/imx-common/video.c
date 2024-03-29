/*
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/errno.h>
#include <asm/imx-common/video.h>

int board_video_skip(void)
{
	int i;
	int ret;
	char const *panel = getenv("panel");

// wyb display modify

	if (!panel) {
		for (i = 0; i < display_count; i++) {
			struct display_info_t const *dev = displays+i;
			if (dev->detect && dev->detect(dev)) {
				panel = dev->mode.name;
				printf("auto-detected panel %s\n", panel);
				break;
			}
		}


 // wyb  set default panel
	if (!panel) {
			// panel = displays[2].mode.name; // HDMI 1024x768
			 panel = displays[4].mode.name; // HDMI 1920x1080
			printf("No panel detected: default to %s\n", panel);
			i = 4;
		}
	} else {
		for (i = 0; i < display_count; i++) {
			if (!strcmp(panel, displays[i].mode.name))
				break;
		}
	}

// wyb
	if (i < display_count) {
		ret = ipuv3_fb_init(&displays[i].mode, 0,
				    displays[i].pixfmt);
		if (!ret) {
			if (displays[i].enable)
				displays[i].enable(displays + i);

			printf("Display: %s (%ux%u)\n",
			       displays[i].mode.name,
			       displays[i].mode.xres,
			       displays[i].mode.yres);
		} else
			printf("LCD %s cannot be configured: %d\n",
			       displays[i].mode.name, ret);
	} else {
		printf("unsupported panel %s\n", panel);
		return -EINVAL;
	}

	return 0;
}

#ifdef CONFIG_IMX_HDMI
#include <asm/arch/mxc_hdmi.h>
#include <asm/io.h>
int detect_hdmi(struct display_info_t const *dev)
{
	struct hdmi_regs *hdmi	= (struct hdmi_regs *)HDMI_ARB_BASE_ADDR;
	return readb(&hdmi->phy_stat0) & HDMI_DVI_STAT;
}
#endif
