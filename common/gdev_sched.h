/*
 * Copyright 2012 Shinpei Kato
 *
 * University of California, Santa Cruz
 * Systems Research Lab.
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __GDEV_SCHED_H__
#define __GDEV_SCHED_H__

#include "gdev_device.h"

struct gdev_sched_entity {
	struct gdev_device *gdev; /* associated Gdev (virtual) device */
	void *task; /* private task structure */
	gdev_ctx_t *ctx; /* holder context */
	int prio; /* general priority */
	int rt_prio; /* real-time priority */
	struct gdev_list list_entry_com; /* entry to compute scheduler list */
	struct gdev_list list_entry_mem; /* entry to memory scheduler list */
	int launch_instances;
	int memcpy_instances;
};

int gdev_init_scheduler(struct gdev_device *gdev);
void gdev_exit_scheduler(struct gdev_device *gdev);

struct gdev_sched_entity *gdev_sched_entity_create(struct gdev_device *gdev, gdev_ctx_t *ctx);
void gdev_sched_entity_destroy(struct gdev_sched_entity *se);

void gdev_schedule_launch(struct gdev_sched_entity *se);
void gdev_schedule_launch_post(struct gdev_device *gdev);
void gdev_schedule_memcpy(struct gdev_sched_entity *se);
void gdev_schedule_memcpy_post(struct gdev_device *gdev);

/**
 * export the pointers to the scheduling entity.
 */
extern struct gdev_sched_entity *sched_entity_ptr[GDEV_CONTEXT_MAX_COUNT];

#endif
