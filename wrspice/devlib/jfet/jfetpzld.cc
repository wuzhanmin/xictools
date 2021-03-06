
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
 * WRspice Circuit Simulation and Analysis Tool:  Device Library          *
 *                                                                        *
 *========================================================================*
 $Id:$
 *========================================================================*/

/***************************************************************************
JSPICE3 adaptation of Spice3f2 - Copyright (c) Stephen R. Whiteley 1992
Copyright 1990 Regents of the University of California.  All rights reserved.
Authors: 1985 Thomas L. Quarles
         1993 Stephen R. Whiteley
****************************************************************************/
/********** new in 3f2
Sydney University mods Copyright(c) 1989 Anthony E. Parker, David J. Skellern
    Laboratory for Communication Science Engineering
    Sydney University Department of Electrical Engineering, Australia
**********/

#include "jfetdefs.h"


int
JFETdev::pzLoad(sGENmodel *genmod, sCKT *ckt, IFcomplex *s)
{
    sJFETmodel *model = static_cast<sJFETmodel*>(genmod);
    for ( ; model; model = model->next()) {
        sJFETinstance *inst;
        for (inst = model->inst(); inst; inst = inst->next()) {

            double gdpr = model->JFETdrainResist * inst->JFETarea;
            double gspr = model->JFETsourceResist * inst->JFETarea;
            double gm  = *(ckt->CKTstate0 + inst->JFETgm) ;
            double gds = *(ckt->CKTstate0 + inst->JFETgds) ;
            double ggs = *(ckt->CKTstate0 + inst->JFETggs) ;
            double xgs = *(ckt->CKTstate0 + inst->JFETqgs) ;
            double ggd = *(ckt->CKTstate0 + inst->JFETggd) ;
            double xgd = *(ckt->CKTstate0 + inst->JFETqgd) ;
            *(inst->JFETdrainDrainPtr ) += gdpr;
            *(inst->JFETgateGatePtr ) += ggd+ggs;
            *(inst->JFETgateGatePtr   ) += (xgd+xgs) * s->real;
            *(inst->JFETgateGatePtr +1) += (xgd+xgs) * s->imag;
            *(inst->JFETsourceSourcePtr ) += gspr;
            *(inst->JFETdrainPrimeDrainPrimePtr ) += gdpr+gds+ggd;
            *(inst->JFETdrainPrimeDrainPrimePtr   ) += xgd * s->real;
            *(inst->JFETdrainPrimeDrainPrimePtr +1) += xgd * s->imag;
            *(inst->JFETsourcePrimeSourcePrimePtr ) += gspr+gds+gm+ggs;
            *(inst->JFETsourcePrimeSourcePrimePtr   ) += xgs * s->real;
            *(inst->JFETsourcePrimeSourcePrimePtr +1) += xgs * s->imag;
            *(inst->JFETdrainDrainPrimePtr ) -= gdpr;
            *(inst->JFETgateDrainPrimePtr ) -= ggd;
            *(inst->JFETgateDrainPrimePtr   ) -= xgd * s->real;
            *(inst->JFETgateDrainPrimePtr +1) -= xgd * s->imag;
            *(inst->JFETgateSourcePrimePtr ) -= ggs;
            *(inst->JFETgateSourcePrimePtr   ) -= xgs * s->real;
            *(inst->JFETgateSourcePrimePtr +1) -= xgs * s->imag;
            *(inst->JFETsourceSourcePrimePtr ) -= gspr;
            *(inst->JFETdrainPrimeDrainPtr ) -= gdpr;
            *(inst->JFETdrainPrimeGatePtr ) += (-ggd+gm);
            *(inst->JFETdrainPrimeGatePtr   ) -= xgd * s->real;
            *(inst->JFETdrainPrimeGatePtr +1) -= xgd * s->imag;
            *(inst->JFETdrainPrimeSourcePrimePtr ) += (-gds-gm);
            *(inst->JFETsourcePrimeGatePtr ) += (-ggs-gm);
            *(inst->JFETsourcePrimeGatePtr   ) -= xgs * s->real;
            *(inst->JFETsourcePrimeGatePtr +1) -= xgs * s->imag;
            *(inst->JFETsourcePrimeSourcePtr ) -= gspr;
            *(inst->JFETsourcePrimeDrainPrimePtr ) -= gds;

        }
    }
    return(OK);
}
