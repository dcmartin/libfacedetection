/*
By downloading, copying, installing or using the software you agree to this license.
If you do not agree to this license, do not download, install,
copy or use the software.


                  License Agreement For libfacedetection
                     (3-clause BSD License)

Copyright (c) 2018-2020, Shiqi Yu, all rights reserved.
shiqi.yu@gmail.com

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the names of the copyright holders nor the names of the contributors
    may be used to endorse or promote products derived from this software
    without specific prior written permission.

This software is provided by the copyright holders and contributors "as is" and
any express or implied warranties, including, but not limited to, the implied
warranties of merchantability and fitness for a particular purpose are disclaimed.
In no event shall copyright holders or contributors be liable for any direct,
indirect, incidental, special, exemplary, or consequential damages
(including, but not limited to, procurement of substitute goods or services;
loss of use, data, or profits; or business interruption) however caused
and on any theory of liability, whether in contract, strict liability,
or tort (including negligence or otherwise) arising in any way out of
the use of this software, even if advised of the possibility of such damage.
*/

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "facedetectcnn.h"

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000
using namespace cv;

int
face_process(int argc, char* argv[])
{
  if (argc > 1) {
   Mat image = imread(argv[1]);
  
   if (!image.empty()) {
     int* pResults = NULL;
     unsigned char* pBuffer = (unsigned char*) malloc(DETECT_BUFFER_SIZE);
     if (pBuffer) {
       TickMeter cvtm;

       cvtm.start();
       pResults = facedetect_cnn(pBuffer, (unsigned char*)(image.ptr(0)), image.cols, image.rows, (int)image.step);
       cvtm.stop();    

       printf("{\"seconds\":%g,\"count\": %d,\"results\":[", cvtm.getTimeMilli()/1000.0, (pResults ? *pResults : 0));

       for (int i = 0; i < (pResults ? *pResults : 0); i++) {
          short* p = ((short*)(pResults+1))+142*i;
          int confidence = p[0];
          int x = p[1];
          int y = p[2];
          int w = p[3];
          int h = p[4];

          if (i > 0) printf(",");
          printf("{\"confidence\":%d,\"x\":%d,\"y\":%d,\"width\":%d,\"height\":%d,\"array\":[[%d,%d],[%d,%d],[%d,%d],[%d,%d],[%d,%d]]}\n", 
            confidence, 
            x, y, w, h, 
            p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13],p[14]);
        }
        free(pBuffer);
        printf("]}\n");
      }
    }
  }
  return 0;
}

int main(int argc, char* argv[])
{
  face_process(argc, argv);
}
