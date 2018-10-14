/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "DownCounterProgramable.h"
#include "DivFreq.h"

using namespace std;

int main()
{
    bool chEnable = true;
    bool clock100h = true;
    DownCounter clock1h(10);
    DownCounterProgramable TEuni(10);
    DownCounterProgramable TEdez(10);
    TEdez.writeData(true,'1');
    TEuni.writeData(true,'7');
    //printf("Programando TE para 17s data= %c%c\n",TEdez.readCounter(), TEuni.readCounter());
    int i = 0;
    while(i<100)
    {   //(carryIn,clk,enable)
        clock1h.decCounter(1,clock100h,1);
        TEdez.decCounter(TEuni.isCarryOut(1),clock1h.isCarryOut(1),chEnable);
        TEuni.decCounter(1,clock1h.isCarryOut(1),chEnable);

        //if(clock1h.readCounter() != '9') printf("_ ");
        //else printf("� Contagem %c%cs\n",TEdez.readCounter(), TEuni.readCounter());
        i++;

        if(TEuni.isCarryOut(1)==1 && TEdez.isCarryOut(1) == 1) break;
    }
    //cout<<"Fim do teste";

    return 0;
}
