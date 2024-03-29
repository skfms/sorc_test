#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define INIT_BUFSZ	50

key_t key = 0xFFFF;

typedef struct msgbuf
{
	long	m_type;
	char	m_text[1];
} stmsgbuf;

