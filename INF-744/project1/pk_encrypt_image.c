/*
 * Image encryption tool.
 *
 * Usage: pk_encrypt_image [-e|-d] [-ECB|-CTR|-CBC|-GCM|-RSA] key input_image output_image
 *
 * Edited by: Vanessa Marques
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/pem.h>
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
				"\nUsage: pk_encrypt_image [-e|-d] [-ECB|-CTR|-CBC|-GCM|-RSA] key input_image output_image\n");
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
		fprintf(stderr, "\nUnknown algorithm.\n");
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
	imageOut.pix = (unsigned char *)malloc(image.nx * image.ny * 3 * sizeof(unsigned char));
	unsigned int imgLen = image.nx * image.ny * 3;

	uint8_t tag[12];
	int outputSize = 0, success = 0;
	uint8_t key[16];
	unsigned char iv[16];
	memset(iv, 0, AES_BLOCK_SIZE);
	memset(tag, 0, sizeof(tag));
        
	// create EVP context
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

	/* Pass control to chosen algorithm. */
	switch (argv[2][3]) {
		case 'B': // ECB
		case 'b':
			// read key
			fread(key, sizeof(key), 1, keyFile);
			if (encrypt) {
				EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv);
				EVP_EncryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_EncryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
			} else {
				EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv);
				EVP_DecryptUpdate(ctx, imageOut.pix, &outputSize, image.pix,
						imgLen);
				EVP_DecryptFinal_ex(ctx, imageOut.pix + outputSize,
						&outputSize);
			}
			break;
		case 'R': // CTR
		case 'r':
			// read key
			fread(key, sizeof(key), 1, keyFile);
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
		case 'C': // CBC
		case 'c':
			// read key
			fread(key, sizeof(key), 1, keyFile);
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
		case 'M': // GCM
		case 'm':
			// read key
			fread(key, sizeof(key), 1, keyFile);
			if (encrypt) {
				EVP_EncryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, key, iv);
				EVP_EncryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_EncryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);
				EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 12, tag);

				/* Print and save tag */
				printTag(tag, argv[5]);
			} else {
				readTag(tag, argv[4]);
				EVP_DecryptInit_ex(ctx, EVP_aes_128_gcm(), NULL, key, iv);
				EVP_DecryptUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
				EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, 12, tag);
				int success = EVP_DecryptFinal_ex(ctx, imageOut.pix + outputSize, &outputSize);

				if (success) {
					printf("Decrypted with success!\n");
				} else {
					printf("Decryption failure!\n");
				}
			}
			break;
		case 'A': // RSA
		case 'a':

			keyFile = fopen(argv[3], "rb");
			int padding = RSA_PKCS1_PADDING;
			
			// // read key
			// fread(key, sizeof(key), 1, keyFile);
		
			if(keyFile != NULL)
			{
		
				if (encrypt) {
					
					/***************************
					* Attempt 1:
					****************************/
					
					RSA *publicKey = RSA_new() ;
					publicKey = PEM_read_RSA_PUBKEY(keyFile, &publicKey, NULL, NULL);
					
					printf("[INFO] Chave publica: %s \n", argv[3]);
									
					int len = strlen(argv[4]);
					printf("[INFO] LEN: %d \n", len);
					
					int result = RSA_public_encrypt( len, argv[4], argv[5], publicKey, padding);
					
					if (result == len)
					{
						printf("[INFO] Encrypted! %d \n", result);
					}
					else
					{
						printf("[INFO] Encrypt error! %d \n", result);
					}
					
					/***************************
					* Attempt 2:
					****************************/
					
					// FILE *pemFile = NULL;							
					// EVP_PKEY* evpPublicKey = NULL;

					// fopen_s(&pemFile, argv[3], "r");
					// if (pemFile)
					// {
					   // evpPublicKey = PEM_read_RSA_PUBKEY(pemFile, 0, 0, 0);
					   // fclose(pemFile);
					// }			
				
					// unsigned char **ek = malloc(EVP_PKEY_size(evpPublicKey));;
					// int *ekl;
					// int npubk;
									
					// int EVP_SealInit(ctx, EVP_aes_256_cbc(), &ek, &ekl, iv, key, evpPublicKey);
					// int EVP_SealUpdate(ctx, imageOut.pix, &outputSize, image.pix, imgLen);
					// int EVP_SealFinal(ctx, imageOut.pix, &outputSize);
					 
					 
					/***************************
					* Attempt 3:
					****************************/
					
					// system("openssl rand -out keyfile 128");
					// system("openssl enc -e -aes-256-cbc -in tux.ppm -out tux_enc.ppm -pass file:./keyfile");
					// system("openssl rsautl -encrypt -inkey public.pem -pubin -in keyfile -out keyfile_rsa_enc");
					// system("rm keyfile");
					// system("tar cf packed.tar *rsa_enc");
					// system("openssl dgst -sha256 -sign private.pem -out signed_packed packed.tar");
					
				}
				else {

					/***************************
					* Attempt 1:
					****************************/
					
					RSA *privateKey= RSA_new() ;
					privateKey = PEM_read_RSAPrivateKey(keyFile, &privateKey,NULL, NULL);
					
					printf("[INFO] Chave privada: %s \n", argv[3]);
					
					int len = strlen(argv[4]);
					printf("[INFO] LEN: %d \n", len);

					int  result = RSA_private_decrypt( len, argv[4], argv[5], privateKey, padding);
					
					if (result == len)
					{
						printf("[INFO] Decrypted! %d \n", result);
					}
					else
					{
						printf("[INFO] Decrypt error! %d \n", result);
					}
									
					/***************************
					* Attempt 2:
					****************************/
					
					// FILE *pemFile = NULL;
					// EVP_PKEY* evpPrivateKey = NULL;

					// fopen_s(&pemFile, argv[3], "r");
					// if (pemFile)
					// {
					   // evpPrivateKey = PEM_read_PrivateKey(pemFile, 0, 0, 0);
					   // fclose(pemFile);
					// }
					
					// unsigned char **ek = malloc(EVP_PKEY_size(evpPublicKey));;
					// int *ekl;
					// int evpPrivateKey;
					
					// int EVP_OpenInit(ctx, EVP_aes_256_cbc(), unsigned char *ek, int ekl, iv, evpPrivateKey);
					// int EVP_OpenUpdate(ctx, imageOut.pix, &outputSize, image.pix, int imgLen);
					// int EVP_OpenFinal(ctx, imageOut.pix, &outputSize);
							
					/***************************
					* Attempt 3:
					****************************/
					
					// system("openssl dgst -sha256 -verify public.pem -signature signed_packed packed.tar");
					// system("tar xf packed.tar");
					// system("openssl rsautl -decrypt -inkey private.pem -in keyfile_rsa_enc -out keyfile");
					// system("openssl enc -d -aes-256-cbc -in tux_enc.ppm -out tux_dec.ppm -pass file:./keyfile");
				}
			}

		break;
	}

	EVP_CIPHER_CTX_free(ctx);

	if (ppm_write(output, &imageOut) == 0) {
		fprintf(stderr, "\nCould not write output, invalid image.\n");
		exit(1);
	}

	fclose(input);
	fclose(output);
}
