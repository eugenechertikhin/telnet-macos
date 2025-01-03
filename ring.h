/*	$OpenBSD: ring.h,v 1.9 2014/07/20 08:12:46 guenther Exp $	*/
/*	$NetBSD: ring.h,v 1.5 1996/02/28 21:04:09 thorpej Exp $	*/

/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	from: @(#)ring.h	8.1 (Berkeley) 6/6/93
 */

/*
 * This defines a structure for a ring buffer.
 *
 * The circular buffer has two parts:
 *(((
 *	full:	[consume, supply)
 *	empty:	[supply, consume)
 *]]]
 *
 */
typedef struct {
	unsigned char	*consume;	/* where data comes out of */
	unsigned char	*supply;	/* where data comes in to */
	unsigned char	*bottom;	/* lowest address in buffer */
	unsigned char	*top;		/* highest address+1 in buffer */
	unsigned char	*mark;		/* marker (user defined) */
	int		size;		/* size in bytes of buffer */
	unsigned long	consumetime;	/* help us keep straight full, empty, etc. */
	unsigned long	supplytime;
} Ring;

/* Here are some functions and macros to deal with the ring buffer */

/* Initialization routine */
void	ring_init(Ring *ring, unsigned char *buffer, int size);

/* Data movement routines */
void	ring_supply_data(Ring *ring, unsigned char *buffer, int count);

/* Buffer state transition routines */
void	ring_supplied(Ring *ring, int count);
void	ring_consumed(Ring *ring, int count);

/* Buffer state query routines */
int	ring_empty_count(Ring *ring);
int	ring_empty_consecutive(Ring *ring);
int	ring_full_count(Ring *ring);
int	ring_full_consecutive(Ring *ring);

/* Buffer urgent data handling */
void	ring_clear_mark(Ring *);
void	ring_mark(Ring *);
int	ring_at_mark(Ring *);


