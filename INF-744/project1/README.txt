NOME: VANESSA MARQUES



1. To generate private and public keys, use:

openssl genrsa -out private.pem 2048

openssl rsa -in private.pem -outform PEM -pubout -out public.pem



2. To compile the image encryption tool, use:

gcc pk_encrypt_image.c ppm.c -o pk_encrypt_image -lcrypto



3. To encrypt image, use:

./pk_encrypt_image -e -RSA public.pem tux.ppm tux_enc.ppm



4. To decrypt image, use:

./pk_encrypt_image -d -RSA private.pem tux_enc.ppm tux_dec.ppm



Notes: After many attempts, it was not possible to conclude 100% the project. The biggest problem was in decrypt step and use the OpenSSL functions.