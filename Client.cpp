#include "UserData.hpp"
#include "Exam.hpp"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <vector>

#define MAX_SHM_SIZE 512

using namespace std;
char* strToChar(string str);
void signalHandler(int signum);
void inputAnswer(void);
void showExam(Exam *exam);

pid_t myPid;

key_t myKey = 0;
int msqid = 0;
char name[MAX_NAME_LEN+1];
MsgUserData userData;
MsgExamData examData;

key_t shmKey = 0;
int shmId = 0;
Exam *exam;

bool isConnected = 0;

int main(int argc, char const *argv[])
{
    myPid = getpid();
    //initial msgqueue
    myKey = ftok("userConn", 3);
    int msqid = msgget(myKey, IPC_CREAT);

    //initial sharedmem
    shmKey = ftok("examState",4);
    shmId = shmget(shmKey,MAX_SHM_SIZE,IPC_CREAT);
    exam = (Exam*)shmat(shmId, NULL, 0);

    signal(SIGUSR1, signalHandler);
    while (1)
    {
        if(!isConnected){
            cout << "닉네임을 입력해주세요 : ";
            scanf("%s", name);
            fflush(stdout);
            fflush(stdin);

            memset(&userData, 0x00, sizeof(MsgUserData));
            userData.mtype = MSG_DATA_TYPE;
            userData.pid = myPid;
            strcpy(userData.name, name);
            msgsnd(msqid, &userData, MSG_DATA_SIZE, 0);
            isConnected = 1;
            pause();
        }else{
            string str;
            getline(cin, str);
            memcpy(name, str.c_str(), MAX_NAME_LEN);
            fflush(stdout);
            fflush(stdin);
            memset(&examData, 0x00, sizeof(MsgExamData));
            examData.mtype = MSG_EXAM_TYPE;
            examData.pid = myPid;
            strcpy(examData.answer, name);
            msgsnd(msqid, &examData, MSG_DATA_SIZE, 0);
        }
    }
    return 0;
}

char* strToChar(string str){
    
    std::vector<char> writable(str.begin(), str.end());
    writable.push_back('\0');
    char* ptr = &writable[0];
    return ptr;
}
void signalHandler(int signum)
{
    if (signum == SIGUSR1)
    {   
        system("clear");
        showExam(exam);
    }
}
void inputAnswer(void){
    cout << "답: ";
    scanf("%s", name);
    fflush(stdout);
    fflush(stdin);
    cout <<"debug1"<<endl;
    memset(&examData, 0x00, sizeof(MsgExamData));
    examData.mtype = MSG_EXAM_TYPE;
    examData.pid = myPid;
    cout <<"debug2"<<endl;
    strcpy(examData.answer, name);
    msgsnd(msqid, &examData, MSG_DATA_SIZE, 0);
    cout <<"debug3"<<endl;
}
void showExam(Exam *exam){
    cout << "Num : " << exam->getNum() <<endl;
    cout << "문제 : " << exam->getDes() << endl;
    cout << "답 : " << endl;
}