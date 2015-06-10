/* Multipass 2.0 - Generates a secure password */
/* Original program located at: https://github.com/The-Overlord/multipass */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/evp.h>

int main(int argc, char *argv[]){
	int confirm = 0;
	int pin = 0;
	char *length;
	length = "20";
	char *master;
	char *identifier;

	int index;
	int c;

	EVP_MD_CTX *mdctx;
	const EVP_MD *md;
	unsigned char md_value[EVP_MAX_MD_SIZE];
	int md_len, i;
	char* space;
	space = " ";

	if(!argv[1]){
		printf("Usage: multipass [-cp] [-l length] masterPassword identifier\n\n\
	-c\tRe-prompt user for password after it is entered\n\
	-p\tOutput PIN instead of password\n\
	-l\tOutput password with specified length\n");
		exit(1);
	}

	while((c = getopt(argc, argv, "cpl:")) != -1)
		switch(c){
			case 'c':
				confirm = 1;
				printf("Confirm = true\n");
				break;
			case 'p':
				pin = 1;
				printf("PIN = true\n");
				break;
			case 'l':
				if(atoi(optarg) == 0){
					printf("Invalid length!");
					return 0;
				}
				length = optarg;
				printf("Length: %d\n", atoi(length));
				break;
			case '?':
				if(optopt == 'l')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if(isprint(optopt))
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
	
	OpenSSL_add_all_digests();
	
	md = EVP_get_digestbyname("SHA256");
	
	mdctx = EVP_MD_CTX_create();
	EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, master, strlen(master));
	EVP_DigestUpdate(mdctx, space, strlen(space));
	EVP_DigestUpdate(mdctx, identifier, strlen(identifier));
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_destroy(mdctx);

	// Password
	printf("Digest is: Mp2!");
	for(i = 0; i < 8; i++)
		printf("%02x", md_value[i]);
	printf("\n");
	

	// Pin
	for(i = 0; i < md_len; i++)
		printf("%02d", md_value[i]);
	printf("\n");
	
	EVP_cleanup();
	return 0;
}
