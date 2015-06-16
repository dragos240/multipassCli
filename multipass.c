/* Multipass 2.0 - Generates a secure password */
/* Original program located at: https://github.com/The-Overlord/multipass */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <openssl/evp.h>

int generate_pass(unsigned char *md_value);
int generate_pin(unsigned char *md_value);
int digest(char *master, char *identifier, int is_pin);

int main(int argc, char *argv[]){
	int is_pin = 0;
	char *master;
	char *identifier;

	int index;
	int c;

	if(!argv[1]){
		printf("Usage: multipass [-p] masterPassword identifier\n\n\
	-p\tOutput PIN instead of password\n");
		exit(1);
	}

	while((c = getopt(argc, argv, "cpl:")) != -1)
		switch(c){
			case 'p':
				is_pin = 1;
				printf("PIN = true\n");
				break;
			case '?':
				if(isprint(optopt))
					fprintf(stderr, "Unknown option '-%c.\n'", optopt);
				else
					fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
				return 1;
			default:
				abort();
		}

	if(!argv[optind]){
		fprintf(stderr, "No master specified");
		exit(1);}
	else if(!argv[optind+1]){
		fprintf(stderr, "No identifier specified");
		exit(1);}

	for(index = optind; index < argc; index++)
		if(index == optind){
			master = argv[index];

			printf("Master: \"%s\"\n", master);}
		else if(index == optind+1){
			identifier = argv[index];
			printf("Identifier: \"%s\"\n", identifier);}
		else
			fprintf(stderr, "Unknown option\n", argv[index]);

	digest(master, identifier, is_pin);

	return 0;
}

int digest(char *master, char* identifier, int is_pin){
	int index;
	int c;

	EVP_MD_CTX *mdctx;
	const EVP_MD *md;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	int md_len, i;
	char* space;
	space = " ";
	OpenSSL_add_all_digests();
	
	md = EVP_get_digestbyname("SHA256");
	
	mdctx = EVP_MD_CTX_create();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, master, strlen(master));
	EVP_DigestUpdate(mdctx, space, strlen(space));
	EVP_DigestUpdate(mdctx, identifier, strlen(identifier));
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_destroy(mdctx);
	
	if(is_pin == 1)
		generate_pin(md_value);
	else
		generate_pass(md_value);

	EVP_cleanup();
	return 0;
}

int generate_pin(unsigned char *md_value){
	unsigned long pin;
	pin = 0;
	int i;
	for(i = 0; i < 8; i++){
		pin += md_value[i]*(long)floor(pow(256,7-i));
	}

	printf("PIN: %lu\n", pin % 10000);
	return 0;
}

int generate_pass(unsigned char *md_value){
	int digest[9];
	printf("Digest is: Mp2!");
	int i;
	for(i = 0; i < 8; i++){
		printf("%02x", md_value[i]);
		digest[i] = md_value[i];}
	digest[8] = '\0';
	printf("\n");
	return 0;
}
