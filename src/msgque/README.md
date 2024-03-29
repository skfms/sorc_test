# Message Queue Test

## File

  + mq.h
  + mqrcv.c
    + message queue receive program
	+ non blocking
	+ 가변 데이터 처리
  + mqsnd.c
  	+ message queue send program
	+ 가변 데이터 전송 : 문자열 자동 생성 적용

## 환경변수

	kernel.msgmni=128             # 메시지 큐의 최대 개수
	kernel.msgmnb=1048576         # 메시지 큐 크기
	kernel.msgmax=65536           # 메시지 큐 최대 개수

## 사용법

    $ mqsnd 100                   # 메시지 타입 100 을 가진 메시지 적재
	$ mqrcv 0                     # 모든 메시지를 추출

