/*
 * Image encryption tool.
 *
 * Usage: auth_encrypt_image [-e|-d] [-v|-a|-t] input_image output_image
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#include "ppm.h"

/* Program arguments. */
FILE *input, *output, *keyFile;

void printTag(uint8_t tag[12], char *fileName) {
	char *tagFileName = malloc(strlen(fileName) + 5);
	strcpy(tagFileName, fileName);
	strcat(tagFileName, ".tag");
	FILE *tagFile = fopen(tagFileName, "w+");
	if (!tagFile) {
		fprintf(stderr, "\nCould not write tag, file not found.\n");
	}

	int j;
	printf("Authentication tag: 0x");
	for (j = 0; j < 12; j++) {
		printf("%02x", tag[j]);
		fprintf(tagFile, "%02x ", tag[j]);
	}
	printf("\n");
}

void readTag(uint8_t tag[12], char *fileName) {
	char *tagFileName = malloc(strlen(fileName) + 5);
	strcpy(tagFileName, fileName);
	strcat(tagFileName, ".tag");
	FILE *tagFile = fopen(tagFileName, "r");
	if (!tagFile) {
		fprintf(stderr, "\nCould not read tag, file not found.\n");
		exit(1);
	}

	int j;
	for (j = 0; j < 12; j++) {
		fscanf(tagFile, "%hhx ", &(tag[j]));
	}
}

/* Main program. */
int main(int argc, char *argv[]) {
	int encrypt = 0;
	pic image;

	/* Check number of arguments. */
	if (argc != 6) {
		fprintf(stderr,
				"\nUsage: auth_encrypt_image [-e|-d] [-ECB|-CTR|-CBC|-GCM] key input_image output_image\n");
		exit(1);
	}
	/* Check mode. */
	if (argv[1][0] != '-' || strlen(argv[1]) != 2) {
		fprintf(stderr, "\nUse -e to encrypt and -d to decrypt..\n");
		exit(1);
	}
	encrypt = (argv[1][1] == 'e');
	/* Check algorithm. */
	if (argv[2][0] != '-' || strlen(argv[1]) != 2) {
		fprintf(stderr, "\nUnknown algorithm, use [-v|-a|-t].\n");
		exit(1);
	}
	/* Check files. */
	if ((keyFile = fopen(argv[3], "rb")) == NULL) {
		fprintf(stderr, "\nCould not read key, file not found.\n");
		exit(1);
	}
	if ((input = fopen(argv[4], "rb")) == NULL) {
		fprintf(stderr, "\nCould not read input, file not found.\n");
		exit(1);
	}
	if ((output = fopen(argv[5], "wb")) == NULL) {
		fprintf(stderr, "\nCould not write output, file not found.\n");
		exit(1);
	}

	if (ppm_read(input, &image) == 0) {
		fprintf(stderr, "\nCould not parse input, invalid image.\n");
		exit(1);
	}
	// create output image
	pic imageOut;
	imageOut.nx = image.nx;
	imageOut.ny = image.ny;
	imageOut.pix =
			(unsigned char *)malloc(image.nx * image.ny * 3 *
			sizeof(unsigned char));
	unsigned int imgLen = image.nx * image.ny * 3;

	//
	uint8_t tag[16];
	int outputSize = 0, success = 0;
	uint8_t key[16];
	unsigned char iv[16];
	memset(iv, 0, AES_BLOCK_SIZE);
	memset(tag, 0, sizeof(tag));

	// read key
	fread(key, sizeof(key), 1, keyFile);
	// create EVP context
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

	/* Pass control to chosen algorithm. */
	switch (argv[2][3]) {
		case 'B':				// ECB
		case 'b':
			if (encrypt) {
				EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv);
				EVP_EncryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_EncryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
			} else {
				EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv);
				EVP_DecryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_DecryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
			}
			break;
		case 'R':				// CTR
		case 'r':
			if (encrypt) {
				EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key, iv);
				EVP_EncryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_EncryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
			} else {
				EVP_DecryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key, iv);
				EVP_DecryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_DecryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
			}
			break;
		case 'C':				// CBC
		case 'c':
			if (encrypt) {
				EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
				EVP_EncryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_EncryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
			} else {
				EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);
				EVP_DecryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_DecryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
			}
			break;
		case 'M':				// GCM
		case 'm':
			if (encrypt) {
				EVP_EncryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, key, iv);
				EVP_EncryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_EncryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);

				/* Print and save tag */
				printTag(tag, argv[5]);
			} else {		

				readTag(tag, argv[4]);
				EVP_DecryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, key, iv);
				EVP_DecryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_DecryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);

				//if (success) {
				if (readTag) {
					printf("Decrypted with success!\n");
				} else {
					printf("Decryption failure!\n");
				}
			}
			break;
	}

	EVP_CIPHER_CTX_free(ctx);
	int EVP_CIPHER_CTX_ctrl(EVP_CIPHER_CTX *ctx, int type, int arg, void *ptr);

	if (ppm_write(output, &imageOut) == 0) {
		fprintf(stderr, "\nCould not write output, invalid image.\n");
		exit(1);
	}

	fclose(input);
	fclose(output);
}
