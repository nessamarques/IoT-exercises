/*
 * ppm: subroutines for reading PPM picture files
 *
 * Adapted from the work of Paul Heckbert and Michael Garland.
 *
 */

typedef struct {
	int nx, ny;
	unsigned char *pix;
} pic;

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

int ppm_read(FILE *fp, pic *p);
int ppm_write(FILE *fp, pic *pic);
