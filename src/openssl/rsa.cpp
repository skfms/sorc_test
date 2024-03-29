// g++ -g -o rsa -I/home/leegs/com_vender/openssl/include -L/home/leegs/com_vender/openssl/lib -l crypto rsa.cpp base64.c

// openssl genrsa -out private_key.pem 1024
// openssl rsa -in private_key.pem -out pubic_key.pem -pubout

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <getopt.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <string>
#include <algorithm>

#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>

#include "base64.h"

using namespace std;

enum E_KEYTKIND  { _PRIVATE=0, _PUBLIC , _KEYKIND_SZ  , _KEYKIND_UNSET=-1   };
enum E_CRYPTKIND { _ENCRYPT=0, _DECRYPT, _CRYPTKIND_SZ, _CRYPTKIND_UNSET=-1 };

int padding = RSA_PKCS1_PADDING;

//+++++++++++++++++++++++++++++++++++++++++++++++++
void usage()
{
	fprintf	(stdout,
				"Usage :\n"
				"  rsa --private <private_key_file> --public <public_key_file>\n\n"
			);
	exit (1);
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
RSA * RSA_create
(
	E_KEYTKIND v_keykind,
	unsigned char * v_keytext
)
{
	RSA *rsa = 0L;
	BIO *keybio = BIO_new_mem_buf(v_keytext, -1);
	if (keybio == 0L)
	{
		fprintf(stderr, "Error create key ! : BIO_new_mem_buf()\n");
		exit(1);
	};
	
	switch (v_keykind)
	{
		case _PUBLIC:
			rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, 0L, 0L);
			break;

		case _PRIVATE:
			rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
			break;

		default:
		fprintf(stderr, "Error Unknown KeyKind !\n");
		exit(1);
	}
	
	return rsa;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
int RSA_crypt
(
	E_KEYTKIND 	v_keykind,
	E_CRYPTKIND	v_cryptkind,
	unsigned char *v_key,
	unsigned char *v_indata,
	int v_indatasz,
	unsigned char ** v_outdata
)
{
	int retval = -1;
	
	RSA *rsa = RSA_create(v_keykind, v_key);

	int bufsz = 4098;
	*v_outdata = (unsigned char *)malloc(bufsz);
	
	if		(v_keykind == _PRIVATE	)
	{
		if		(v_cryptkind == _ENCRYPT)
		{
			retval = RSA_private_encrypt(v_indatasz, v_indata, *v_outdata, rsa, padding);
		}
		else if(v_cryptkind == _DECRYPT)
		{
			retval = RSA_private_decrypt(v_indatasz, v_indata, *v_outdata, rsa, padding);
		}
	}
	else if(v_keykind == _PUBLIC	)
	{
		if		(v_cryptkind == _ENCRYPT)
		{
			retval = RSA_public_encrypt(v_indatasz, v_indata, *v_outdata, rsa, padding);
		}
		else if(v_cryptkind == _DECRYPT)
		{
			retval = RSA_public_decrypt(v_indatasz, v_indata, *v_outdata, rsa, padding);
		}
	}

	return retval;
};


//+++++++++++++++++++++++++++++++++++++++++++++++++
int readfile
(
	const char * v_infullpath,
	string & v_outdata
)
{
	v_outdata = "";
	
	FILE *fp;
	struct stat st;
	
	if((fp = fopen(v_infullpath, "rt")) == 0)
		return -1;
	else
	{
		fstat(fileno(fp), &st);
		char *pbuf = new char[st.st_size+1];
		memset(pbuf, 0x00, st.st_size+1);
		fread(pbuf, sizeof(char), st.st_size, fp);
		fclose(fp);
		
		v_outdata = pbuf;
		delete [] pbuf;
	};

	return 0;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++
int main
(
	int v_argc,
	char *v_argv[]
)
{
	if (v_argc < 2) usage();

	struct option opts[] =
	{
		{"private", 1, 0, '1'},
		{"public" , 1, 0, '2'},
		{0, 0, 0, 0}
	};
	
	string m_prikey_file, m_pubkey_file;

	int t_opt, t_optidx;
	while(1)
	{
		t_opt = getopt_long(v_argc, v_argv, "1:2:", opts, &t_optidx);
		if(t_opt < 0) break;

		switch(t_opt)
		{
		case '1':
			m_prikey_file = optarg;
			break;

		case '2':
			m_pubkey_file = optarg;
			break;

		case '?':
			printf("Unknown option : '%c'\n\n", optopt);
			usage();
			break;
		};
	};

	if (m_prikey_file.empty() || m_pubkey_file.empty()) usage();

	string t_prikey, t_pubkey;
	readfile(m_prikey_file.c_str(), t_prikey);
	readfile(m_pubkey_file.c_str(), t_pubkey);

	const char *plaintext = "Helow World !@#";
	unsigned char *t_outdata1, *t_outdata2;
	int retval;
	
	fprintf(stdout, "plaintext       [%s]\n", plaintext);
	
	fprintf(stdout, "*****\n");
	// Private Key Encrypt -> Public Key Decode
	retval = RSA_crypt(_PRIVATE, _ENCRYPT, 
				(unsigned char *)t_prikey.c_str(), 
				(unsigned char *)(char *)plaintext, strlen(plaintext), &t_outdata1);
	if (retval > 0)
	{
		char *encb64 = enc_base64(t_outdata1, retval);
		fprintf(stdout, "private encrypt [%s]\n", encb64);
		free(encb64);
	}

	retval = RSA_crypt(_PUBLIC, _DECRYPT, 
				(unsigned char *)t_pubkey.c_str(), t_outdata1, retval, &t_outdata2);
	if (retval > 0)
	{
		t_outdata2[retval] = 0x00;
		fprintf(stdout, "public decrypt  [%s]\n", t_outdata2);
	}
	free(t_outdata1);
	free(t_outdata2);

	fprintf(stdout, "*****\n");
	// Public Key Encrypt -> Private Key Decode
	retval = RSA_crypt(_PUBLIC, _ENCRYPT, 
				(unsigned char *)t_pubkey.c_str(), 
				(unsigned char *)(char *)plaintext, strlen(plaintext), &t_outdata1);
	if (retval > 0)
	{
		char *encb64 = enc_base64(t_outdata1, retval);
		fprintf(stdout, "public encrypt  [%s]\n", encb64);
		free(encb64);
	}

	retval = RSA_crypt(_PRIVATE, _DECRYPT, 
				(unsigned char *)t_prikey.c_str(), t_outdata1, retval, &t_outdata2);
	if (retval > 0)
	{
		t_outdata2[retval] = 0x00;
		fprintf(stdout, "private decrypt [%s]\n", t_outdata2);
	}
	free(t_outdata1);
	free(t_outdata2);

	return 0;
}

