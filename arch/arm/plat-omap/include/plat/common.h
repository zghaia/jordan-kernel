/*
 * arch/arm/plat-omap/include/mach/common.h
 *
 * Header for code common to all OMAP machines.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 * NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You should have received a copy of the  GNU General Public License along
 * with this program; if not, write  to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __ARCH_ARM_MACH_OMAP_COMMON_H
#define __ARCH_ARM_MACH_OMAP_COMMON_H

#include <linux/i2c.h>

struct sys_timer;

/* used by omap-smp.c and board-4430sdp.c */
extern void __iomem *gic_cpu_base_addr;

extern void omap_map_common_io(void);
extern struct sys_timer omap_timer;
#if defined(CONFIG_I2C_OMAP) || defined(CONFIG_I2C_OMAP_MODULE)
extern int omap_register_i2c_bus(int bus_id, u32 clkrate,
				 struct i2c_board_info const *info,
				 unsigned len);
#else
static inline int omap_register_i2c_bus(int bus_id, u32 clkrate,
				 struct i2c_board_info const *info,
				 unsigned len)
{
	return 0;
}
#endif

extern void omap_reserve(void);

/*
 * IO bases for various OMAP processors
 * Except the tap base, rest all the io bases
 * listed are physical addresses.
 */
struct omap_globals {
	u32		class;		/* OMAP class to detect */
	void __iomem	*tap;		/* Control module ID code */
	void __iomem	*sdrc;		/* SDRAM Controller */
	void __iomem	*sms;		/* SDRAM Memory Scheduler */
	void __iomem	*ctrl;		/* System Control Module */
	void __iomem	*prm;		/* Power and Reset Management */
	void __iomem	*cm;		/* Clock Management */
};

void omap2_set_globals_242x(void);
void omap2_set_globals_243x(void);
void omap2_set_globals_343x(void);
void omap2_set_globals_443x(void);

/* These get called from omap2_set_globals_xxxx(), do not call these */
void omap2_set_globals_tap(struct omap_globals *);
void omap2_set_globals_sdrc(struct omap_globals *);
void omap2_set_globals_control(struct omap_globals *);
void omap2_set_globals_prcm(struct omap_globals *);

/**
 * omap_test_timeout - busy-loop, testing a condition
 * @cond: condition to test until it evaluates to true
 * @timeout: maximum number of microseconds in the timeout
 * @index: loop index (integer)
 *
 * Loop waiting for @cond to become true or until at least @timeout
 * microseconds have passed.  To use, define some integer @index in the
 * calling code.  After running, if @index == @timeout, then the loop has
 * timed out.
 */
#define omap_test_timeout(cond, timeout, index)			\
({								\
	for (index = 0; index < timeout; index++) {		\
		if (cond)					\
			break;					\
		udelay(1);					\
	}							\
})

#endif /* __ARCH_ARM_MACH_OMAP_COMMON_H */
