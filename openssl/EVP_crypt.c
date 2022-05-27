// g++ -g -o EVP_crypt -I/home/leegs/com_vender/openssl/include -L/home/leegs/com_vender/openssl/lib -l crypto EVP_crypt.c base64.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>

#include "base64.h"

#define BUF_SZ	2048

enum E_CRYPTCD { _DECRYPT=0, _ENCRYPT, _CRYPTCD_SZ, _UNSET=-1 };


void EVP_crypt
(
	E_CRYPTCD v_cryptcd,
	const unsigned char *v_indata,
	int v_indatalen,
	unsigned char **v_outdata,
	int *v_outdatalen
)
{
	unsigned char keyCipher[32];
	unsigned char iv[16];
	unsigned long err = 0;
	
	EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
	if (ctx == 0L)
	{
		err = ERR_get_error();
		printf("ERR: EVP_EncryptUpdate() - %s\n", ERR_error_string (err, 0L));
	}
	
	memset(keyCipher, 0x00, sizeof(keyCipher));
	memset(iv, 0x00, sizeof(iv));

	// xxx : 128 / 192/ 256
	// des-ede3-ecb, des-ede3-cbc, des-ede3-cfb1, des-ede3-cfb8, des-ede3-cfb64, des-ede3-ofb
	// ase -xxx- ecb, aes-xxx-cbc, aes-xxx-cfb1, aes-xxx-cfb8, aes-xxx-cfb128, aes-xxx-ofb, aes-xxx-ofb128

	const EVP_CIPHER *pCipher = EVP_get_cipherbyname("des-ede3-cfb1");
	int r = EVP_CipherInit(ctx, pCipher, keyCipher, iv, v_cryptcd);
	if(!r)
	{
		err = ERR_get_error();
		printf("ERR: EVP_CipherInit() %d - %s\n", r, ERR_error_string (err, 0L));
	}

	//EVP_CipherInit(ctx, EVP_aes_256_cbc(), keyCipher, iv, v_cryptcd);
	
	unsigned int cihper_block_size = EVP_CIPHER_CTX_block_size(ctx);
	fprintf(stderr, "cihper_bloack_size len = %d\n", cihper_block_size);
	
	int bufsz = v_indatalen + cihper_block_size;
	*v_outdata = (unsigned char *)malloc(bufsz);
	memset(*v_outdata, 0x00, bufsz);
	
	int t1 = 0, t2 = 0;
	EVP_CipherUpdate(ctx, *v_outdata, &t1, v_indata, v_indatalen);
	if(t1 < 0)
	{
		err = ERR_get_error();
		printf("ERR: EVP_CipherUpdate() %d - %s\n", t1, ERR_error_string (err, 0L));
	}
	
	EVP_CipherFinal(ctx, (*v_outdata) + t1, &t2);
	if(t2 < 0)
	{
		err = ERR_get_error();
		printf("ERR: EVP_CipherFinal() %d - %s\n", t2, ERR_error_string (err, 0L));
	};
	
	EVP_CIPHER_CTX_free(ctx);
	
	*v_outdatalen = t1 + t2;
}


int main()
{
	const char *p = "Base64 Test ! >>>>>>>> dfwer4 453453 drgdfgd  dfg55tgg dfg dgdfg <<<<<";

	unsigned char *t_enc = 0L, *t_dec = 0L;
	int t_enclen = 0, t_declen = 0;
	
	EVP_crypt(_ENCRYPT, (const unsigned char *)p, strlen(p), &t_enc, &t_enclen);
	fprintf(stderr, ">>> encode len = %d\n", t_enclen);
	
	char *encb64 = enc_base64(t_enc, t_enclen);

	EVP_crypt(_DECRYPT, t_enc, t_enclen, &t_dec, &t_declen);
	t_dec[t_declen] = 0x00;
	fprintf(stderr, ">>> decode len = %d\n", t_declen);

	fprintf(stdout,
		"  plant text [%s]\n"
		"CRYPT encode [%s]\n"
		"CRYPT decode [%s]\n",
		p, encb64, t_dec
		);

	free(encb64);
	free(t_enc);
	free(t_dec);

	return 0;
}

