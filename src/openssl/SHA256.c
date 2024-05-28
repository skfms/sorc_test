// g++ -o SHA256  SHA256.c base64.c -l crypto -l ssl

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/sha.h>

#include "base64.h"

unsigned char *SHA256
(
	const unsigned char *v_indata, 
	int v_indatalen,
	const char *v_salt
)
{
	unsigned char *retbuf = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);

	
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	
	if(v_salt != 0L) SHA256_Update(&ctx, v_salt, syrlen(v_salt));
	
	SHA256_Update(&ctx, v_indata, v_indatalen);
	SHA256_Final(retbuf, &ctx);

	return retbuf;
}



int main()
{
	const char *p = "Base64 Test ! 34534rgdfsgdfg5546456gdfgdsfg453456654dfgdfgasdfgdasa sefsdfsdaf 44343t A               dfsdfsdfsdfsdfsdf";

	unsigned char *encsha = SHA256((const unsigned char *)p, strlen(p), "");

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

