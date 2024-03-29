// gcc -g -o mqrcv mqrcv.c

#include "mq.h"

void mqview(int v_qid)
{
	struct msqid_ds mqstat;

	int rval = msgctl(v_qid, IPC_STAT, &mqstat);
	if(rval < 0)
	{
		perror("msgctl");
		exit(-1);
	};

	fprintf(stdout, "cbytes=%lu, qnum=%lu, qbytes=%lu\n", 
		mqstat.msg_cbytes, mqstat.msg_qnum, mqstat.msg_qbytes);
};

int main()
{
	int qid = msgget(key, IPC_CREAT | 0666);
	if(qid < 0)
	{
		perror("msgget");
		return -1;
	};

	stmsgbuf *pbuf = 0L;
	size_t bsz = INIT_BUFSZ;

	while(1)
	{
		pbuf = (stmsgbuf *) malloc(sizeof(stmsgbuf) + bsz);

		ssize_t rsz = msgrcv(qid, pbuf, bsz, 0, IPC_NOWAIT);

		if(rsz < 0)
		{
			switch(errno)
			{
				case E2BIG	: 
					free(pbuf);
					bsz += INIT_BUFSZ; 
					continue;

				case EAGAIN	: 
					break;

				dafault		: 
					free(pbuf);
					perror("msgrcv");
					exit(-1);
			};
		}
		else
		{
			fprintf(stdout, "%03ld [%s]\n", rsz, pbuf->m_text);
			mqview(qid);
			bsz = INIT_BUFSZ;
		};

		free(pbuf);

		//sleep(1);

		usleep(1000);
	};
};
