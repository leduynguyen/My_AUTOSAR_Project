/*
 * Copyright (c) 2011-2014, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== rsc_types.h ========
 *
 *  Include common definitions for sizes and type of resources
 *  used by the the resource table in each base image, which is
 *  read from remoteproc on host side.
 *
 */

#ifndef _RSC_TYPES_H_
#define _RSC_TYPES_H_

// We have changed the types here so no need for them
//#include <xdc/std.h>
#include <stdint.h>

/* Size constants must match those used on host: include/asm-generic/sizes.h */
#define SZ_64K                          0x00010000
#define SZ_128K                         0x00020000
#define SZ_256K                         0x00040000
#define SZ_512K                         0x00080000
#define SZ_1M                           0x00100000
#define SZ_2M                           0x00200000
#define SZ_4M                           0x00400000
#define SZ_8M                           0x00800000
#define SZ_16M                          0x01000000
#define SZ_32M                          0x02000000
#define SZ_64M                          0x04000000
#define SZ_128M                         0x08000000
#define SZ_256M                         0x10000000
#define SZ_512M                         0x20000000

/* Virtio Ids: keep in sync with the linux "include/linux/virtio_ids.h" */
#define VIRTIO_ID_CONSOLE       3 /* virtio console */
#define VIRTIO_ID_RPMSG         7 /* virtio remote processor messaging */

/* Indices of rpmsg virtio features we support */
#define VIRTIO_RPMSG_F_NS       0  /* RP supports name service notifications */
#define VIRTIO_RING_F_SYMMETRIC 30 /* We support symmetric vring */

/* Resource info: Must match include/linux/remoteproc.h: */
#define TYPE_CARVEOUT    0
#define TYPE_DEVMEM      1
#define TYPE_TRACE       2
#define TYPE_VDEV        3
#define TYPE_INTMEM      4

/* Common Resource Structure Types */
struct resource_table {
    uint32_t ver;
    uint32_t num;
    uint32_t reserved[2];
};

struct fw_rsc_carveout {
    uint32_t  type;
    uint32_t  da;
    uint32_t  pa;
    uint32_t  len;
    uint32_t  flags;
    uint32_t  reserved;
    char    name[32];
};

struct fw_rsc_intmem {
    uint32_t  type;
    uint32_t  version;
    uint32_t  da;
    uint32_t  pa;
    uint32_t  len;
    uint32_t  reserved;
    char    name[32];
};

struct fw_rsc_devmem {
    uint32_t  type;
    uint32_t  da;
    uint32_t  pa;
    uint32_t  len;
    uint32_t  flags;
    uint32_t  reserved;
    char    name[32];
};

struct fw_rsc_trace {
    uint32_t  type;
    uint32_t  da;
    uint32_t  len;
    uint32_t  reserved;
    char    name[32];
};

struct fw_rsc_vdev_vring {
    uint32_t  da; /* device address */
    uint32_t  align;
    uint32_t  num;
    uint32_t  notifyid;
    uint32_t  reserved;
};

struct fw_rsc_vdev {
    uint32_t  type;
    uint32_t  id;
    uint32_t  notifyid;
    uint32_t  dfeatures;
    uint32_t  gfeatures;
    uint32_t  config_len;
    char    status;
    char    num_of_vrings;
    char    reserved[2];
};

#endif /* _RSC_TYPES_H_ */
