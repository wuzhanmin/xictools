
/*========================================================================*
 *                                                                        *
 *  Distributed by Whiteley Research Inc., Sunnyvale, California, USA     *
 *                       http://wrcad.com                                 *
 *  Copyright (C) 2017 Whiteley Research Inc., all rights reserved.       *
 *  Author: Stephen R. Whiteley, except as indicated.                     *
 *                                                                        *
 *  As fully as possible recognizing licensing terms and conditions       *
 *  imposed by earlier work from which this work was derived, if any,     *
 *  this work is released under the Apache License, Version 2.0 (the      *
 *  "License").  You may not use this file except in compliance with      *
 *  the License, and compliance with inherited licenses which are         *
 *  specified in a sub-header below this one if applicable.  A copy       *
 *  of the License is provided with this distribution, or you may         *
 *  obtain a copy of the License at                                       *
 *                                                                        *
 *        http://www.apache.org/licenses/LICENSE-2.0                      *
 *                                                                        *
 *  See the License for the specific language governing permissions       *
 *  and limitations under the License.                                    *
 *                                                                        *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,      *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES      *
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-        *
 *   INFRINGEMENT.  IN NO EVENT SHALL WHITELEY RESEARCH INCORPORATED      *
 *   OR STEPHEN R. WHITELEY BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER     *
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE       *
 *   USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 *                                                                        *
 *========================================================================*
 *               XicTools Integrated Circuit Design System                *
 *                                                                        *
 * IMSAVE Image Dump Facility
 *                                                                        *
 *========================================================================*
 $Id:$
 *========================================================================*/

/*------------------------------------------------------------------------*
 *
 * IMSAVE -- Screen Dump Utility
 *
 * S. R. Whiteley (stevew@wrcad.com)
 *------------------------------------------------------------------------*
 * Borrowed extensively from Imlib-1.9.8
 *
 * This software is Copyright (C) 1998 By The Rasterman (Carsten
 * Haitzler).  I accept no responsability for anything this software
 * may or may not do to your system - you use it completely at your
 * own risk.  This software comes under the LGPL and GPL licences.
 * The library itself is LGPL (all software in Imlib and gdk_imlib
 * directories) see the COPYING and COPYING.LIB files for full legal
 * details.
 *
 * (Rasterdude :-) <raster@redhat.com>)
 *------------------------------------------------------------------------*/

#include "imsave.h"
#include <stdio.h>
#include <string.h>
#include <setjmp.h>


bool
Image::savePPM(const char *file, SaveInfo*)
{
    FILE *f = fopen(file, "wb");
    if (!f)
        return (false);

    const char *ext = strrchr(file, '.');
    if (!ext) {
        fclose(f);
        return (false);
    }
    ext++;
    if (strcmp(ext, "pgm") == 0){
        if (!fprintf(f, "P5\n# %s\n%i %i\n255\n", image_string,
                rgb_width, rgb_height)) {
            fclose(f);
            return (false);
        }
        unsigned char *ptr = rgb_data;
        for (int y = 0; y < rgb_height; y++) {
            for (int x = 0; x < rgb_width; x++) {
                int v = (int)(*ptr++);
                v += (int)(*ptr++);
                v += (int)(*ptr++);
                unsigned char val = (unsigned char)(v / 3);
                if (!fwrite(&val, 1, 1, f)) {
                    fclose(f);
                    return (false);
                }
            }
        }
    }
    else {
        if (!fprintf(f, "P6\n# %s\n%i %i\n255\n", image_string,
                rgb_width, rgb_height)) {
            fclose(f);
            return (false);
        }
        if (!fwrite(rgb_data, 1, (rgb_width * rgb_height * 3), f)) {
            fclose(f);
            return (false);
        }
    }
    fclose(f);
    return (true);
}

