/*
 * gdt.h - Header file for GDT.
 *
 * Author: Infinity Technology
 * Date: 12/25/2020
 *
 **********************************************************************
 */

#ifndef _GDT_H_
#define _GDT_H_
#pragma once

// #include "types.h"
#include <stdint.h>

#define MAX_GDT_ENTRIES 5

struct gdt_entry {
	uint16_t limit;
	uint16_t base_low;
	uint8_t base_mid;
	uint8_t access;
	uint8_t grand;
	uint8_t base_high;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry_t;

/* Reload GDT into system. */
extern void gdt_flush(uint32_t gdtr);

/* Install new GDT into system. */
extern void gdt_install(void);

#endif
