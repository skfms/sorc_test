// g++ -o dash_sha256 dsfn_sha256.c base64.c -l crypto

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include <string>

#include "base64.h"

using namespace std;

unsigned char *SHA256
(
	const unsigned char *v_indata, 
	const char *v_salt
)
{
	unsigned char *retbuf = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
	
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	
	string s = v_salt;
	s += (char *)v_indata;
	
	SHA256_Update(&ctx, s.c_str(), s.size());
	SHA256_Final(retbuf, &ctx);

	return retbuf;
}



int main()
{
	const char *p = "AAA";

	unsigned char *encsha = SHA256((const unsigned char *)p, "dsfn");

	char *encb64 = enc_base64(encsha, SHA256_DIGEST_LENGTH);
	
	fprintf(stdout,
		"   plant text [%s]\n"
		"SHA256 encode [%s]\n",
		p, encb64
		);

	free(encb64);
	//free(encsha);

	return 0;
}

