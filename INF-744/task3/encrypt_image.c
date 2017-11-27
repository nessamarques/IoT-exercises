/*
 * Image encryption tool.
 *
 * Usage: encrypt_image [-e|-d] [-v|-a|-t] input_image output_image
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>

#include "ppm.h"

/* Program arguments. */
FILE *input, *output;

static const unsigned char key[] = {
    0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
    0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f
};

/* Main program. */
int main(int argc, char *argv[]) {
	int encrypt = 0;
	pic image;

	/* Check number of arguments. */
	if (argc != 5) {
		fprintf(stderr,
				"\nUsage: encrypt_image [-e|-d] [-ECB|-CTR|-CBC] input_image output_image\n");
		exit(1);
	}
	/* Check mode. */
	if (argv[1][0] != '-' || strlen(argv[1]) != 2) {
		fprintf(stderr,
				"\nUse -e to encrypt and -d to decrypt..\n");
		exit(1);
	}
	encrypt = (argv[1][1] == 'e');
	/* Check algorithm. */
	if (argv[2][0] != '-' || strlen(argv[1]) != 2) {
		fprintf(stderr, "\nUnknown algorithm, use [-v|-a|-t].\n");
		exit(1);
	}
	/* Check files. */
	if ((input = fopen(argv[3], "rb")) == NULL) {
		fprintf(stderr, "\nN�o � poss�vel ler arquivo de entrada.\n");
		exit(1);
	}
	if ((output = fopen(argv[4], "wb")) == NULL) {
		fprintf(stderr, "\nN�o � poss�vel gravar em arquivo de sa�da.\n");
		exit(1);
	}

	if (ppm_read(input, &image) == 0) {
		fprintf(stderr, "\nN�o � poss�vel ler image de entrada.\n");
		exit(1);
	}

    AES_KEY enc_key, dec_key;
    unsigned char counter[AES_BLOCK_SIZE] = {0};
    unsigned char ecount_buf[AES_BLOCK_SIZE] = {0};
    unsigned int num = 0, c;
    memset(ecount_buf, 0, AES_BLOCK_SIZE);
    memset(counter, 0, AES_BLOCK_SIZE);


    AES_set_encrypt_key(key, 128, &enc_key);
    AES_set_decrypt_key(key, 128, &dec_key);


    pic imageOut;
    imageOut.nx = image.nx;
	imageOut.ny = image.ny;
	imageOut.pix = (unsigned char *)malloc(image.nx * image.ny * 3 * sizeof(unsigned char));
    unsigned int imgLen = image.nx * image.ny * 3;

	/* Pass control to chosen algorithm. */
	switch (argv[2][2]) {
        case 'C': // ECB
		case 'c':
            if (encrypt){
                for(c = 0; c < imgLen; c+=16){
                    AES_ecb_encrypt(image.pix + c, imageOut.pix + c, &enc_key, AES_ENCRYPT);
                }
            }else{
                for(c = 0; c < imgLen; c+=16){
                    AES_ecb_encrypt(image.pix + c, imageOut.pix + c, &dec_key, AES_DECRYPT);
                }
            }
            break;
        case 'T': // CTR
		case 't':
            if (encrypt)
                AES_ctr128_encrypt(image.pix, imageOut.pix, imgLen, &enc_key, counter, ecount_buf, &num);
            else
                AES_ctr128_encrypt(image.pix, imageOut.pix, imgLen, &enc_key, counter, ecount_buf, &num);
            break;
        case 'B': // CBC
		case 'b':
            if (encrypt)
                AES_cbc_encrypt(image.pix, imageOut.pix, imgLen, &enc_key, counter, AES_ENCRYPT);
            else
                AES_cbc_encrypt(image.pix, imageOut.pix, imgLen, &dec_key, counter, AES_DECRYPT);
            break;
	}

	if (ppm_write(output, &imageOut) == 0) {
		fprintf(stderr, "\nNão é possível gravar image de saída.\n");
		exit(1);
	}

	fclose(input);
	fclose(output);
}
