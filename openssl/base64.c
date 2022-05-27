// g++ -o base64 -I/home/leegs/com_vender/openssl/include -L/home/leegs/com_vender/openssl/lib -l crypto base64.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>


char *enc_base64
(
	const unsigned char *input, 
	int length
)
{

	BIO *b64  = BIO_new(BIO_f_base64());
	BIO *bmem = BIO_new(BIO_s_mem());

	b64 = BIO_push(b64, bmem);

	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

	BIO_write(b64, input, length);
	BIO_flush(b64);


	BUF_MEM *bptr;
	BIO_get_mem_ptr(b64, &bptr);

	char *buffer = (char *)malloc(bptr->length+1);
	memcpy(buffer, bptr->data, bptr->length);
	buffer[bptr->length] = 0;

	BIO_free_all(b64);

	return buffer;
}


char *dec_base64
(
	unsigned char *input,
	int length
)
{
	char *buffer = (char *)malloc(length);
	memset(buffer, 0, length);

	BIO *b64  = BIO_new(BIO_f_base64());
	BIO *bmem = BIO_new_mem_buf(input, length);

	bmem = BIO_push(b64, bmem);

	BIO_set_flags(bmem, BIO_FLAGS_BASE64_NO_NL);
	BIO_read(bmem, buffer, length);

	BIO_free_all(bmem);

	return buffer;
}


/*
int main()
{
	const char *p = "Base64 Test ! 34534rgdfsgdfg5546456gdfgdsfg453456654dfgdfgasdfgdasa sefsdfsdaf 44343t ";

	char *enc = base64enc((const unsigned char *)p, strlen(p));
	char *dec = base64dec((unsigned char *)enc, strlen(enc));
	
	fprintf(stdout,
		"plant text [%s]\n"
		"    encode [%s]\n"
		"    decode [%s]\n",
		p, enc, dec
		);

	free(enc);
	free(dec);

	return 0;
}
*/

