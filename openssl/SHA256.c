// g++ -o SHA256 -I/home/leegs/com_vender/openssl/include -L/home/leegs/com_vender/openssl/lib -l crypto SHA256.c base64.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include "base64.h"

unsigned char *SHA256
(
	const unsigned char *v_indata, 
	int v_indatalen
)
{
	unsigned char *retbuf = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);

	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, v_indata, v_indatalen);
	SHA256_Final(retbuf, &ctx);

	return retbuf;
}


unsigned char *SHA256SP
(
	const unsigned char *v_indata, 
	int v_indatalen
)
{
	unsigned char *retbuf = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
	
	int tt_len = SHA256_DIGEST_LENGTH/2;
	char tt[tt_len];

	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	
	memcpy(tt, &v_indata[0], tt_len);
	SHA256_Update(&ctx, tt, tt_len);
	
	memcpy(tt, &v_indata[tt_len], tt_len);
	SHA256_Update(&ctx, tt, tt_len);
	
	SHA256_Final(retbuf, &ctx);

	return retbuf;
}


int main()
{
	const char *p = "Base64 Test ! 34534rgdfsgdfg5546456gdfgdsfg453456654dfgdfgasdfgdasa sefsdfsdaf 44343t A";

	unsigned char *encsha = SHA256((const unsigned char *)p, strlen(p));

	char *encb64 = enc_base64(encsha, SHA256_DIGEST_LENGTH);
	
	fprintf(stdout,
		"   plant text [%s]\n"
		"SHA256 encode [%s]\n",
		p, encb64
		);

	free(encb64);
	free(encsha);

	unsigned char *encshasp = SHA256SP((const unsigned char *)p, strlen(p));

	encb64 = enc_base64(encshasp, SHA256_DIGEST_LENGTH);
	
	fprintf(stdout,
		"      plant text [%s]\n"
		"SHA256 SP encode [%s]\n",
		p, encb64
		);

	free(encb64);
	free(encshasp);

	return 0;
}

