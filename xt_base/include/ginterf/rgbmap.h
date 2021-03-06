
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
 * Ginterf Graphical Interface Library                                    *
 *                                                                        *
 *========================================================================*
 $Id:$
 *========================================================================*/

// Rendering functions for in-core bitmap generation

#ifndef RGBMAP_H_INCLUDED
#define RGBMAP_H_INCLUDED

#include "ginterf/graphics.h"
#include <stdio.h>

namespace ginterf
{
    // This can be used by other drivers to add fields to the parameter
    // structs.
    struct RGBparams : public HCdraw
    {
        RGBparams(bool ps)
            {
                dev = 0;
                bytpline = 0;
                red = green = blue = 0;
                base = 0;
                curfillpatt = 0;
                text_scale = 0.0;
                fp = 0;
                linestyle = 0;
                invert_colors = ps;
            }

        void Pixel(int, int);
        void Pixels(GRmultiPt*, int);
        void Line(int, int, int, int);
        void PolyLine(GRmultiPt*, int);
        void Lines(GRmultiPt*, int);
        void Box(int, int, int, int);
        void Boxes(GRmultiPt*, int);
        void Arc(int, int, int, int, double, double);
        void Polygon(GRmultiPt*, int);
        void Zoid(int, int, int, int, int, int);
        void Text(const char*, int, int, int, int = -1, int = -1);
        void TextExtent(const char*, int*, int*);
        void SetLinestyle(const GRlineType*);
        void SetFillpattern(const GRfillType*);
        void SetColor(int);
        void DisplayImage(const GRimage*, int, int, int, int);

        void put_pixel(unsigned int, int, int);

        GRdev *dev;                // pointer to device struct
        int bytpline;              // bytes per line of image
        int red, green, blue;      // current color
        unsigned char *base;       // base of image in core (0 <-> miny)
        const GRfillType *curfillpatt; // current fillpattern, 0 solid
        double text_scale;         // scale size of text
        FILE *fp;                  // file pointer for output
        unsigned linestyle;        // linestyle storage, 0 solid
        bool invert_colors;        // true for Postscript.
    };
}

#endif

