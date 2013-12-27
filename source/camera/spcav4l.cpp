/****************************************************************************
#	 	spcav4l: v4l library.				            #
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

//#include "global.h"
#include "../precomp.h"
#include "spcav4l.h"

struct bridge_list Blist[]={

	{BRIDGE_SPCA505,"SPCA505"},
	{BRIDGE_SPCA506,"SPCA506"},
	{BRIDGE_SPCA501,"SPCA501"},
	{BRIDGE_SPCA508,"SPCA508"},
	{BRIDGE_SPCA504,"SPCA504"},
	{BRIDGE_SPCA500,"SPCA500"},
	{BRIDGE_SPCA504B,"SPCA504B"},
	{BRIDGE_SPCA533,"SPCA533"},
	{BRIDGE_SPCA504C,"SPCA504C"},
	{BRIDGE_SPCA561,"SPCA561"},
	{BRIDGE_SPCA536,"SPCA536"},
	{BRIDGE_SONIX,"SN9C102"},
	{BRIDGE_ZR364XX,"ZR364XX"},
	{BRIDGE_ZC3XX,"ZC301-2"},
	{BRIDGE_CX11646,"CX11646"},
	{BRIDGE_TV8532,"TV8532"},
	{BRIDGE_ETOMS,"ET61XX51"},
	{BRIDGE_SN9CXXX,"SN9CXXX"},
	{BRIDGE_MR97311,"MR97311"},
	{BRIDGE_UNKNOW,"UNKNOW"},
	{-1,NULL}
};
/* Camera type jpeg yuvy yyuv yuyv grey gbrg*/
struct palette_list Plist[] ={
	{JPEG,"JPEG"},
	{YUVY,"YUVY"},
	{YYUV,"YYUV"},
	{YUYV,"YUYV"},
	{GREY,"GREY"},
	{GBRG,"GBRG"},
	{SN9C,"SN9C"},
	{GBGR,"GBGR"},
	{UNOW,"UNOW"},
	{-1,NULL}
};

int init_v4l (struct vdIn *vd);

int ms_time (void)
{
  struct timeval tod;
  gettimeofday (&tod, NULL);
  return ( tod.tv_sec * 1000 + tod.tv_usec / 1000);

}

int isSpcaChip (const char *BridgeName)
{
  int i = -1;
  int find = -1;
  int size = 0;
  
  /* Spca506 return more with channel video, cut it */
  
  /* return Bridge otherwhise -1 */
  for (i = 0; i < MAX_BRIDGE -1; i++)
    {
    size = strlen (Blist[i].name) ;
    //
      if (strncmp (BridgeName, Blist[i].name, size) == 0)
	{
	find = i;
	printf("Bridge find %s number %d\n",Blist[i].name,i);
	  break;
	}
    }

  return find;
}

int GetStreamId (const char *BridgeName)
{
	int i = -1;
	int match = -1;
/* return Stream_id otherwhise -1 */
	if((match=isSpcaChip(BridgeName)) < 0){
	 printf("Not an Spca5xx Camera !!\n");
	 return match;
	 }
	switch (match) {
		case BRIDGE_SPCA505:
		case BRIDGE_SPCA506: 
			i= YYUV;
			break;
		case BRIDGE_SPCA501:
			i = YUYV;
			break;
		case BRIDGE_SPCA508:
		 	i = YUVY;
			break;
		case BRIDGE_SPCA504:
		case BRIDGE_SPCA500:
		case BRIDGE_SPCA504B:
		case BRIDGE_SPCA533:
		case BRIDGE_SPCA504C:
		case BRIDGE_SPCA536:
		case BRIDGE_ZR364XX:
		case BRIDGE_ZC3XX:
		case BRIDGE_CX11646:
		case BRIDGE_SN9CXXX:
		case BRIDGE_MR97311:
			i = JPEG;
			break;
		case BRIDGE_ETOMS:
		case BRIDGE_SONIX:
		case BRIDGE_SPCA561:
		case BRIDGE_TV8532:
			i = GBRG;
			break;
		default:
			i = -1;
			 printf("Unable to find a StreamId !!\n");
			break;
	
	}
	return i;	 
}

int GetDepth (int format)
{
  int depth;
  switch (format)
    {
   
   case VIDEO_PALETTE_JPEG:
      {
	depth = 8;		
      }
      break;
    case VIDEO_PALETTE_RAW:
      {
	depth = 8;		
      }
      break;
    case VIDEO_PALETTE_YUV420P:
      {
	depth = (8 * 3) >> 1;
      }
      break;
    case VIDEO_PALETTE_RGB565:
      depth = 16;
      break;
    case VIDEO_PALETTE_RGB24:
      depth = 24;
      break;
    case VIDEO_PALETTE_RGB32:
      {
	depth = 32;
      }
      break;
    default:
      depth = -1;
      break;
    }
  return depth;
}



/****************************************************************************
*			Public
****************************************************************************/
int sb_init_videoIn (struct vdIn *vd, int width, int height, int format)
{
  if (vd == NULL)
    return -1;
  if (width == 0 || height == 0)
    return -1;

  // check format 
  vd->videodevice = NULL;
  vd->cameraname = NULL;
  vd->videodevice = NULL;
  vd->videodevice = (char *) malloc (16);
  vd->cameraname = (char *) malloc (32);
  snprintf (vd->videodevice, 12, "/dev/video0");
  printf("video %s \n",vd->videodevice);
  memset (vd->cameraname, 0, sizeof (vd->cameraname));
  memset(vd->bridge, 0, sizeof(vd->bridge));

  vd->hdrwidth = width;
  vd->hdrheight = height;
  /*          compute the max frame size   */
  vd->formatIn = format; 
  vd->bppIn = GetDepth (vd->formatIn);
  vd->pFramebuffer = NULL;
  /* init and check all setting */
  if(init_v4l(vd) < 0)
	return -1;

  return 0;
}

int sb_close_videoIn (struct vdIn *vd)
{
  if (vd->pFramebuffer)
  {
     free(vd->pFramebuffer);
     vd->pFramebuffer = NULL;
  }

  
  if (vd->fd)
  {
     close (vd->fd);
     vd->fd = (int)NULL;
  }

  /* dealloc the whole buffers */
  if (vd->videodevice)
  {
      free (vd->videodevice);
      vd->videodevice = NULL;
  }
  if (vd->cameraname)
  {
      free (vd->cameraname);
      vd->cameraname = NULL;
  }

  printf ("close video_device\n");  
  return 0;
}

int get_jpegsize (unsigned char *buf, int insize)
{
 int i; 	
 for ( i= 1024 ; i< insize; i++) {
 	if ((buf[i] == 0xFF) && (buf[i+1] == 0xD9)) return i+10;
 }
 return -1;
}

int sb_grab (struct vdIn *vd)
{
	int len;
  
        if ( (len = read (vd->fd, vd->pFramebuffer, vd->framesizeIn)) <= 0 )
	{
	  	printf ("v4l read error\n");
	  	return -1;
	}
	
	return 0;
}

int sb_save_jpg(char* pfilename, struct vdIn *vd)
{
	char filename[64];
    	int sizein = vd->framesizeIn;
  	int sizeout = 0;
  	FILE *foutpict;
    
  	memset (filename, 0, sizeof (filename));
  	sprintf(filename,"%s",pfilename);
 
  	foutpict = fopen (filename, "wb");
  	if(foutpict == 0)
		return -1;
  
       	sizeout = get_jpegsize( vd->pFramebuffer,sizein);
//      	printf (" picture jpeg %s: sizeout = %d\n", filename, sizeout);
      	fwrite (vd->pFramebuffer, sizeof (char), sizeout, foutpict);
      	fclose (foutpict);
	
	return 0;
}

int sb_get_jpg_size(struct vdIn *vd)
{
	int sizein = vd->framesizeIn;
	return get_jpegsize( vd->pFramebuffer,sizein);
}

/*****************************************************************************
* 				Private
******************************************************************************/
int
sb_GetVideoPict (struct vdIn *vd)
{
  if (ioctl (vd->fd, VIDIOCGPICT, &vd->videopict) < 0)
    return -1;

//   printf ("VIDIOCGPICT brightnes=%d hue=%d color=%d contrast=%d whiteness=%d"
// 	  "depth=%d palette=%d\n", vd->videopict.brightness,
// 	  vd->videopict.hue, vd->videopict.colour, vd->videopict.contrast,
// 	  vd->videopict.whiteness, vd->videopict.depth,
// 	  vd->videopict.palette);

  return 0;
}

int
sb_PauseVideo (struct vdIn *vd)
{
	int i = 0;
  if (ioctl (vd->fd, VIDIOCCAPTURE, &i) < 0)
    return -1;

  return 0;
}

int
sb_ResumeVideo (struct vdIn *vd)
{
  int i = 1;
  if (ioctl (vd->fd, VIDIOCCAPTURE, &i) < 0)
    return -1;

  return 0;
}

int
SetVideoPict (struct vdIn *vd)
{
  if (ioctl (vd->fd, VIDIOCSPICT, &vd->videopict) < 0)
    return -1;

  printf ("VIDIOCSPICT brightnes=%d hue=%d color=%d contrast=%d whiteness=%d"
	  "depth=%d palette=%d\n", vd->videopict.brightness,
	  vd->videopict.hue, vd->videopict.colour, vd->videopict.contrast,
	  vd->videopict.whiteness, vd->videopict.depth,
	  vd->videopict.palette);

  return 0;
}

void spcaPrintParam (int fd, struct video_param *videoparam)
{
	if(ioctl(fd,SPCAGVIDIOPARAM, videoparam) == -1){
		printf ("wrong spca5xx device\n");
	} else 
		printf("quality %d autoexpo %d Timeframe %d \n",
			 videoparam->quality,videoparam->autobright,videoparam->time_interval);
}


int init_v4l (struct vdIn *vd)
{
  if ((vd->fd = open (vd->videodevice, O_RDWR)) == -1)
  {
     printf("ERROR opening V4L interface\n");
     return -1;
  }

  if (ioctl (vd->fd, VIDIOCGCAP, &(vd->videocap)) == -1)
  {
     printf("Couldn't get videodevice capability\n");
     return -2;
  }

  printf ("Camera found: %s \n", vd->videocap.name);
  snprintf (vd->cameraname, 32, "%s", vd->videocap.name);

  if (sb_GetVideoPict(vd) == -1)
  {
     printf("Couldn't get videodevice picture\n");
     return -3;
  }

  if (ioctl (vd->fd, VIDIOCGCHAN, &vd->videochan) == -1)
  {
     printf ("Hmm did not support Video_channel\n");
     return -4;
  }
  else
  {
     if (vd->videochan.name)
     {
	printf ("Current norm = %d: channel = %d\n", vd->videochan.norm, vd->videochan.channel);
	vd->videochan.norm = 0;
	vd->videochan.channel = 0;
	if (ioctl (vd->fd, VIDIOCSCHAN, &vd->videochan) == -1) 
	{
	   printf ("ERROR setting channel and norme \n");
	   return -5;
	}
	/************ just to be sure *************/
	if (ioctl (vd->fd, VIDIOCGCHAN, &vd->videochan) == -1) 
	{
	   printf ("wrong device\n");
	   return -6;
	}

        printf ("Bridge found: %s \n", vd->videochan.name);
        snprintf (vd->bridge, 9, "%s", vd->videochan.name);
        vd->cameratype = GetStreamId (vd->videochan.name);
	if (vd->cameratype >= 0)
	{
		printf("StreamId: %s Camera\n",Plist[vd->cameratype].name);
		/* look a spca5xx webcam try to set the video param struct */
		spcaPrintParam (vd->fd,&vd->videoparam);
	} 
	else 
	{
		printf("StreamId: %d Unknow Camera\n",vd->cameratype);
		return -7;
	} 

      }
      else
      {
          printf ("Bridge not found not a spca5xx Webcam Probing the hardware !!\n");
          vd->cameratype = UNOW;
	  return -8;
      }
  }
  
 
	vd->videopict.palette = vd->formatIn;
  	vd->videopict.depth = GetDepth (vd->formatIn);
  	vd->bppIn = GetDepth (vd->formatIn);
  
   	vd->framesizeIn = (vd->hdrwidth * vd->hdrheight * vd->bppIn) >> 3;
   
  	if( SetVideoPict (vd) < 0 )
  	{
		printf ("ERROR SetVideoPict \n");
	   	return -12;
  	}	
  
  	if( sb_GetVideoPict (vd) < 0 )
  	{
	   	printf ("ERROR sb_GetVideoPict \n");
	   	return -13;
  	}	

  	if (vd->formatIn != vd->videopict.palette || vd->bppIn != vd->videopict.depth)
  	{
      		printf("could't set video palette Abort !\n");
		return -14;
  	}

      	/* read method */
      	/* allocate the read buffer */
      	vd->pFramebuffer =(unsigned char *) malloc ((size_t) vd->framesizeIn);
      	printf (" grabbing method READ asked \n");

      	if (ioctl (vd->fd, VIDIOCGWIN, &(vd->videowin)) < 0)
      	{
		printf("VIDIOCGWIN failed \n");
		return -15;
	}
      	vd->videowin.height = vd->hdrheight;
        vd->videowin.width = vd->hdrwidth;
      	printf("width = %d:height = %d", vd->videowin.width, vd->videowin.height);
      	if (ioctl (vd->fd, VIDIOCSWIN, &(vd->videowin)) < 0)
	{
		printf("VIDIOCSWIN failed \n");
		return -16;
	}
      	printf ("VIDIOCSWIN height %d  width %d \n", vd->videowin.height, vd->videowin.width);

  	return 0;
}

