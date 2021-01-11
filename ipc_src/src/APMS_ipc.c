/*********************  P r o g r a m  -  M o d u l e *******************************************/
/**
 *        \file  APMS_ipc.c
 *	   \project	APMS_dataProcess			
 *		  \date 2017
 *      \author  ade.ikhsan@lrs.co.id
 *
 *       \brief
 *
 * (c) Copyright by PT. LEN RAILWAY SYSTEM, Bandung, Indonesia
 ************************************************************************************************/
#include "APMS_ipc.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "APMS_msgdef.h"
#include "APMS_msgdef.h"
#include <unistd.h>
int tag_server_coid = -1;


int vobc_server_locate() {

	int server_coid;
	//server_coid = name_open(NAMA_SERVER, NAME_FLAG_ATTACH_GLOBAL); //QNET
	server_coid = name_open(SERVER_NAME, 0); //LOCAL
	while (server_coid == -1) {
		sleep(1);
		//server_coid = name_open(NAMA_SERVER, NAME_FLAG_ATTACH_GLOBAL); //QNET
		server_coid = name_open(SERVER_NAME, 0); //LOCAL
	}
	return server_coid;
}

int tag_server_locate() {
	printf("connecting to tag server:%s\n",TAG_SERVER_NAME);
	tag_server_coid = name_open(TAG_SERVER_NAME, 0); //LOCAL
	if (-1 == tag_server_coid){
		printf("failed to connect to tag server\n");
	}
	printf("connected to tag server data :%d\n",tag_server_coid);
	return tag_server_coid;
}
int server_locate() {


}

int getCommData(int coid, uint16_t MSG_Type, char * SvrData, size_t len){
	switch (MSG_Type) {
	case MSG_TYPE_REQ_ZC:
		printf("Requesting ZC data\n");
		break;
	case MSG_TYPE_REQ_NVTL:
		printf("Requesting CBI Non Vital data\n");
		break;
	default:
		printf("WTF is this bro?!\n");
		exit(EXIT_FAILURE);
		break;
	}
	sck_msg_t msg;
	char msg_rcv[MAX_STRING_LEN + 1];
	strcpy(msg.msg_contain,"Data Req");
	msg.mflag = -1;
	msg.type = MSG_Type;
	int status = MsgSend(coid, &msg, sizeof(msg), msg_rcv, sizeof(msg_rcv));
	if (-1 == status){ //was there an error sending to server?
		perror("MsgSend");
		exit(EXIT_FAILURE);
	}
	strncpy(SvrData,msg_rcv,len);
	SvrData[len-1]='\0';
	return EXIT_SUCCESS;
}
tag_msg_send_t get_tagData(void){
	//tag_msg_t msg_rcv = {0,0};
	tag_msg_send_t msg_rcv_tag;
	memset(&msg_rcv_tag,0,sizeof(msg_rcv_tag));
	sck_msg_t msg;
	if(-1 == tag_server_coid){
		printf("server tag not connected\n");
		int ret = tag_server_locate();
	}else{
		strcpy(msg.msg_contain,"Data Req Tag");
		msg.mflag = -1;
		msg.type = MSG_TYPE_REQ_TAG;
		printf("sending tag data request\n");
		int status = MsgSend(tag_server_coid, (void*)&msg, sizeof(msg), (void*)&msg_rcv_tag, sizeof(msg_rcv_tag));
		if (-1 == status){ //was there an error sending to server?
			perror("MsgSend");
			exit(EXIT_FAILURE);
		}
	}
	//return msg_rcv;
	return msg_rcv_tag;
}




