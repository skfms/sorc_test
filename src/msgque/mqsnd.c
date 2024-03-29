// gcc -o mqsnd mqsnd.c

#include <time.h>

#include "mq.h"


int gen_str(char ** v_outstr)
{
	int retval = 0;

	char buf[500];

	int rval = rand() % 500;

	sprintf(buf, "cat /dev/urandom | tr -dc ' a-zA-Z0-9' | head -c %d", rval);

	FILE *fp = popen(buf, "r");
	if(fp == 0L)
	{
		perror("popen");
		return -1;
	};

	int rno = fread(buf, sizeof(char), sizeof(buf), fp);
	if(rno > 0) 
	{
		char * pout = (char *)malloc(rno+1);
		memcpy(pout, buf, rno);
		pout[rno] = 0x00;

		*v_outstr = pout;
		retval = rno+1;
	}
	else
	{
		*v_outstr = 0L;
	};

	return retval;
};

int gen_str2(char ** v_outstr)
{
	static char * _T = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?! ";
	int len = strlen(_T);

	int rval = rand() % 500;

	char *pout = malloc(rval+1);
	char *pt = pout;
	for(int n=0; n<rval; n++) *pt++ = _T[rand() % len]; 
	*pt = 0x00;

	*v_outstr = pout;
	return rval+1;
};

void usage()
{
	fprintf(stdout, 
		"Usage : mqsnd <msg_type>\n"
		"    Push Message into the Message Queue.\n"
		"  Option :\n"
		"    msg_type    the numeric value of the message, greater than zero\n"
		"\n"
		);
	exit(-1);
};

int main(int v_argc, char * v_argv[])
{
	if(v_argc < 2) usage();

	int msg_type = atoi(v_argv[1]);
	if(msg_type < 1) usage();

	srand(time(0L)*getpid());

	int qid = msgget(key, IPC_CREAT | 0666);
	if(qid < 0)
	{
		perror("msgget");
		return -1;
	};

	stmsgbuf *pbuf = 0L;
	char *ranstr = 0L;

	while(1)
	{
		int rlen = gen_str2(&ranstr); 
		if(rlen < 0) 
		{
			sleep(1);
			continue;
		};

		fprintf(stdout, "%03d [%s]\n", rlen, ranstr);
		pbuf = malloc(sizeof(stmsgbuf) + rlen);
		pbuf->m_type = msg_type;
		memcpy(pbuf->m_text, ranstr, rlen);
		free(ranstr);

		int sno = msgsnd(qid, pbuf, rlen, IPC_NOWAIT);
		if(sno < 0) perror("msgsnd");

		free(pbuf);
		
		//sleep(1);
		usleep(1000000);
	};
};
