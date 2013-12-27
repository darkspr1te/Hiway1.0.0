/****************************************************************************
#	 	spcav4l v4l library. 				            #
#This package work with the spca5xx based webcam with the raw jpeg feature. #
#All the decoding is in user space with the help of libjpeg.                #
#.                                                                          #
# 		Copyright (C) 2003 2004 2005 Michel Xhaard                  #
#                                                                           #
# This program is free software; you can redistribute it and/or modify      #
# it under the terms of the GNU General Public License as published by      #
# the Free Software Foundation; either version 2 of the License, or         #
# (at your option) any later version.                                       #
#                                                                           #
# This program is distributed in the hope that it will be useful,           #
# but WITHOUT ANY WARRANTY; without even the implied warranty of            #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
# GNU General Public License for more details.                              #
#                                                                           #
# You should have received a copy of the GNU General Public License         #
# along with this program; if not, write to the Free Software               #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA #
#                                                                           #
****************************************************************************/

#ifndef SPCAV4L_H
#define SPCAV4L_H 

/* V4L1 extension API */
#define VIDEO_PALETTE_JPEG  21
/* in case default setting */
#define WIDTH 352
#define HEIGHT 288
#define BPPIN 8
#define OUTFRMNUMB 4
/* ITU-R-BT.601 PAL/NTSC */
#define MASQ 1
#define VGA MASQ
#define PAL (MASQ << 1)
#define SIF (MASQ << 2)
#define CIF (MASQ << 3)
#define QPAL (MASQ << 4)
#define QSIF (MASQ << 5)
#define QCIF (MASQ << 6)
/* fourcc palette check in preference order*/
#define JPG MASQ
#define YUV420P (MASQ << 1)
#define RGB24 (MASQ << 2)
#define RGB565 (MASQ << 3)
#define RGB32 (MASQ << 4)
/* our own ioctl */
struct video_param {
	int chg_para;
#define CHGABRIGHT 1
#define CHGQUALITY 2
#define CHGLIGHTFREQ 3
#define CHGTINTER  4
	__u8 autobright;
	__u8 quality;
	__u16 time_interval;
	__u8 light_freq;
};/* Our private ioctl */
#define SPCAGVIDIOPARAM _IOR('v',BASE_VIDIOCPRIVATE + 1,struct video_param)
#define SPCASVIDIOPARAM _IOW('v',BASE_VIDIOCPRIVATE + 2,struct video_param)


/* specific for the spca5xx webcam */
enum {
	BRIDGE_SPCA505 = 0,
        BRIDGE_SPCA506,
	BRIDGE_SPCA501,
	BRIDGE_SPCA508,
	BRIDGE_SPCA504,
	BRIDGE_SPCA500,
	BRIDGE_SPCA504B,
	BRIDGE_SPCA533,
	BRIDGE_SPCA504C,
	BRIDGE_SPCA561,
	BRIDGE_SPCA536,
	BRIDGE_SONIX,
	BRIDGE_ZR364XX,
	BRIDGE_ZC3XX,
	BRIDGE_CX11646,
	BRIDGE_TV8532,
	BRIDGE_ETOMS,
	BRIDGE_SN9CXXX,
	BRIDGE_MR97311,
	BRIDGE_UNKNOW,
	MAX_BRIDGE,
};
enum {
	JPEG = 0,
	YUVY,
	YYUV,
	YUYV,
	GREY,
	GBRG,
	SN9C,
	GBGR,
	UNOW,
};

struct palette_list {
	int num;
	const char *name;
};

struct bridge_list {
	int num;
	const char *name;
};
	
typedef struct vdIn {
	int fd;
	char *videodevice ;
	struct video_mmap vmmap;
	struct video_capability videocap;
	int mmapsize;
	struct video_mbuf videombuf;
	struct video_picture videopict;
	struct video_window videowin;
	struct video_channel videochan;
	struct video_param videoparam;	
	int cameratype ;
	char *cameraname;
	char bridge[9];
	int sizenative; // available size in jpeg
	int sizeothers;	// others palette 
	int palette; // available palette
	int norme ; // set spca506 usb video grabber
	int channel ; // set spca506 usb video grabber
	int grabMethod ;
	unsigned char *pFramebuffer;
	unsigned char *ptframe[4];
	int framelock[4];
	pthread_mutex_t grabmutex;
	int framesizeIn ;
	volatile int frame_cour;
	int bppIn;
	int  hdrwidth;
	int  hdrheight;
	int  formatIn;

	} T_VIDEOIN;
	
extern int sb_init_videoIn (struct vdIn *vd, int width, int height, int format);
extern int sb_close_videoIn (struct vdIn *vd);
extern int sb_grab (struct vdIn *vd);
extern int sb_GetVideoPict (struct vdIn *vd);
extern int sb_PauseVideo (struct vdIn *vd);
extern int sb_ResumeVideo (struct vdIn *vd);
extern int sb_save_jpg(char* pfilename, struct vdIn *vd);
extern int sb_get_jpg_size(struct vdIn *vd);
extern int ms_time (void);
#endif /* SPCAV4L_H */
