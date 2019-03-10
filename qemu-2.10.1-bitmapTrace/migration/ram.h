/*
 * QEMU System Emulator
 *
 * Copyright (c) 2003-2008 Fabrice Bellard
 * Copyright (c) 2011-2015 Red Hat Inc
 *
 * Authors:
 *  Juan Quintela <quintela@redhat.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef QEMU_MIGRATION_RAM_H
#define QEMU_MIGRATION_RAM_H

#include "qemu-common.h"
#include "exec/cpu-common.h"
#include "qemu/thread.h"
#include "qmp-commands.h"

extern MigrationStats ram_counters;
extern XBZRLECacheStats xbzrle_counters;

int64_t xbzrle_cache_resize(int64_t new_size);
uint64_t ram_bytes_remaining(void);
uint64_t ram_bytes_total(void);

uint64_t ram_pagesize_summary(void);
int ram_save_queue_pages(const char *rbname, ram_addr_t start, ram_addr_t len);
void acct_update_position(QEMUFile *f, size_t size, bool zero);
void ram_debug_dump_bitmap(unsigned long *todump, bool expected,
                           unsigned long pages);
void ram_postcopy_migrated_memory_release(MigrationState *ms);
/* For outgoing discard bitmap */
int ram_postcopy_send_discard_bitmap(MigrationState *ms);
/* For incoming postcopy discard */
int ram_discard_range(const char *block_name, uint64_t start, size_t length);
int ram_postcopy_incoming_init(MigrationIncomingState *mis);

void ram_handle_compressed(void *host, uint8_t ch, uint64_t size);

// dmtrs - start

struct BitmapTraceState {
    int state;
    FILE *pFile;
    int64_t current_period;
    int64_t current_iteration;
    int64_t iterations;
    int64_t time_last_bitmap_sync;     /* last time we did a full bitmap_sync */
    uint64_t num_dirty_pages_period;   /* number of dirty pages since start_time(per iteration) */
    uint64_t bitmapTrace_dirty_pages;  /* number of dirty bits in the bitmap */
    uint64_t *dirtyPages_array;
    QemuMutex bitmap_mutex; 			/* protects modification of the bitmap */
    QemuThread thread;

    bool bitmapTrace_thread_running;

    /* The last error that occurred */
    Error *error;



};

BitmapTraceState *bitmapTrace_get_current(void);
BitmapTraceState *bitmapTrace_init(void);
void BitmapTrace_set_state(int *state, int old_state, int new_state);

// dmtrs - end



#endif
