//------------------------------------------------------------------------
// File:   ee.c
// Author: Tony Saveski, tony@ui.com.au
//------------------------------------------------------------------------
// Copyright (c) 2003, Unicorn Interactive Pty Ltd.
// All Rights Reserved.
//------------------------------------------------------------------------
// This software (hereafter, "Software") is the property of Unicorn
// Interactive Pty Ltd (hereafter, "Unicorn"). The following conditions
// apply:
//
// * Unicorn grants you (hereafter, "Licensee") a license to use the
//   Software for academic, research and non-commercial purposes only,
//   without a fee. Licensees may distribute unmodified versions of the
//   binary and source code of the Software to third parties under the
//   terms of this license but must ensure that such distribution is under
//   the terms of this license and this license is distributed along with
//   the binaries and source.
//
// * Unicorn imposes the following restrictions on any code developed
//   using the Software:
//   - Unicorn retains a non-exclusive royalty-free license, including the
//     right of redistribution, to any modifications to the Software made
//     by the licensee.
//   - You may not distribute modified versions of the Software.
//
// * Any Licensee wishing to make commercial use of the Software should
//   contact Unicorn to negotiate an appropriate license for such
//   commercial use. Commercial use includes but is not limited to:
//   - integration of all or part of the source code into a product for
//     sale or commercial license by or on behalf of Licensee to third
//     parties, or
//   - distribution of the binary code or source code to third parties
//     that need it to utilize a commercial product sold or licensed by or
//     on behalf of Licensee, or
//   - use in an internal operational environment.
//
//   Please email info@ui.com.au for details.
//
// THIS SOFTWARE IS BEING PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT
// LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL UNICORN INTERACTIVE PTY LTD BE LIABLE FOR ANY SPECIAL,
// INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND, OR ANY
// DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY
// THEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THE SOFTWARE.
//
// Unicorn welcome comments and bug fixes related to the Software.
// Please address any queries, comments or bug fixes to the address below:
//
//   E-Mail: info@ui.com.au
//------------------------------------------------------------------------
#include "ee.h"
#include "ee_regs.h"

// TODO: wow...just looked in here for the first time since writing it. What a mess!
//       Will clean up for version 0.3 ... maybe :)

static uint32 t_count[4] = { t0_count, t1_count, t2_count, t3_count };
static uint32 t_mode[4]  = { t0_mode,  t1_mode,  t2_mode,  t3_mode  };
static uint32 t_cres[4]  = { 0, 0, 0, 0 }; 		// current clock resolution

//static uint32 t_ticks[4] = { 2500000, 156250, 9760, 262 };	// ticks per VBLANK for each resolution
static uint32 t_v_per_sec=0;

//------------------------------------------------------------------------
void ee_timer_init(int timer, int resolution)
{
//	if(timer<0 || timer>3) return;
	t_cres[timer] = resolution;
	*((volatile uint32 *)(t_mode[timer])) = T_MODE(t_cres[timer], 0, 0, 0, 0, 0, 0, 0, 0, 0);

	if(*((char *)0x1FC80000 - 0xAE) == 'E')
		t_v_per_sec = 50; // PAL
	else
		t_v_per_sec = 60; // NTSC
}

//------------------------------------------------------------------------
void ee_timer_start(int timer)
{
//	if(timer<0 || timer>3) return;
	*((volatile uint32 *)(t_count[timer])) = 0;
	*((volatile uint32 *)(t_mode[timer])) = T_MODE(t_cres[timer], 0, 0, 0, 0, 1, 0, 0, 0, 0);
}

//------------------------------------------------------------------------
void ee_timer_stop(int timer)
{
//	if(timer<0 || timer>3) return;
	*((volatile uint32 *)(t_mode[timer])) = T_MODE(t_cres[timer], 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

//------------------------------------------------------------------------
uint32 ee_timer_get_ticks(int timer)
{
//	if(timer<0 || timer>3) return(0);
	return *((volatile uint32 *)(t_count[timer]));
}
/*
//------------------------------------------------------------------------
uint32 ee_timer_get_msec(int timer)
{
	return(ee_timer_get_ticks(timer)/((t_ticks[t_cres[timer]]*t_v_per_sec)/1000));
}
*/