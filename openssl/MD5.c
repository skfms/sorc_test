// g++ -o MD5 -I/home/leegs/com_vender/openssl/include -L/home/leegs/com_vender/openssl/lib -l crypto MD5.c base64.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/md5.h>

#include "base64.h"

#define MD5_LEN		16

unsigned char *MD5
(
	const unsigned char *v_indata, 
	int v_indatalen
)
{
	unsigned char *retbuf = (unsigned char *)malloc(MD5_LEN);

	MD5_CTX ctx;
	MD5_Init(&ctx);
	MD5_Update(&ctx, v_indata, v_indatalen);
	MD5_Final(retbuf, &ctx);

	return retbuf;
}


int main()
{
	const char *p = "Base64 Test ! 34534rgdfsgdfg5546456gdfgdsfg453456654dfgdfgasdfgdasa sefsdfsdaf 44343t A";

	unsigned char *encmd5 = MD5((const unsigned char *)p, strlen(p));

	char *encb64 = enc_base64(encmd5, MD5_LEN);
	
	fprintf(stdout,
		"plant text [%s]\n"
		"MD5 encode [%s]\n",
		p, encb64
		);


	free(encb64);
	free(encmd5);

	return 0;
}

