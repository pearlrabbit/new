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
#include <vector>
#include <string>

#define MAX_SHM_SIZE 512

using namespace std;
void signalHandler(int signum);
void notifyExam(void);

key_t mqKey = 0;
int msqid = 0;
key_t shmKey = 0;
int shmId = 0;
Exam *exam;
vector<UserData> users;
vector<Exam*> exams;
int curExamNum = -1;

pid_t pid;

int main(int argc, char const *argv[])
{
    pid = getpid();
    cout << "Server pid : " << pid << endl;

    //initial exams
    Exam *initExam = new Exam(1, "현재디렉토리를 보여라.", "hint : pwd", "pwd");
    exams.push_back(initExam);
    initExam = new Exam(2, "testDir 디렉토리를 생성하시오.", "hint : mkdir <name>", "mkdir testDir");
    exams.push_back(initExam);


    //initial msgqueue
    MsgUserData userData;
    MsgExamData examData;
    mqKey = ftok("userConn", 3);
    msqid = msgget(mqKey, IPC_CREAT | 0644);

    //initial sharememory
    shmKey = ftok("examState",4);
    shmId = shmget(shmKey,MAX_SHM_SIZE,IPC_CREAT | 0644);
    exam = (Exam*)shmat(shmId, NULL, 0);

    
    // memcpy(exam, tmpExam , sizeof(Exam));


    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler);

    while (1)
    {
        if(curExamNum==-1){
            puts("Wait Client...");

            memset(&userData, 0x00, sizeof(MsgUserData));
            msgrcv(msqid, &userData, MSG_DATA_SIZE, MSG_DATA_TYPE, 0);
            if (userData.pid != 0)
            {
                UserData user(userData.pid, userData.name, 0);
                cout << "User Connect!! -> ";
                user.printData();
                users.push_back(user);
            }
        }else{
            puts("Wait Answer...");
            memset(&examData, 0x00, sizeof(MsgExamData));
            msgrcv(msqid, &examData, MSG_DATA_SIZE, MSG_EXAM_TYPE, 0);
            if (examData.pid != 0)
            {
                if(exam->getAnswer() == string(examData.answer)){
                    puts("debug1");
                    notifyExam();
                }else{
                    puts("debug2");
                    cout << exam->getAnswer() << endl;
                    cout << examData.answer << endl;
                    kill(examData.pid,SIGUSR1);
                }
            }
        }

        // int tmp;
        // scanf("%d", &tmp);
        // printf("return : %d\n",tmp);

        // memset(&msgRslt, 0x00, sizeof(MsgRslt));
        // msgRslt.mtype = MSG_TYPE_RSLT;
        // msgRslt.rslt = calculate(msgCalc.calc);
        // msgsnd(msqid, &msgRslt, MSG_SIZE_RSLT, 0);
        // printf("Send: %d\n", msgRslt.rslt);

        // fflush(stdout)
    }

    return 0;
}
void signalHandler(int signum) 
{
    if (signum == SIGINT)
    {
        msgctl(msqid, IPC_RMID, NULL);
        shmdt(exam);
        shmctl(shmId,IPC_RMID, NULL);
        exit(0);
    }else if(signum == SIGUSR1){
        notifyExam();
    }
}

void notifyExam(void){
    struct shmid_ds buf;
    Exam *tmp = exams.at(++curExamNum);
    memcpy(exam,tmp,sizeof(Exam));

    // shmctl(shmId, IPC_STAT, &buf);
    for(int i=0 ; i<users.size() ; i++){
        kill(users.at(i).getPid(), SIGUSR1);
    }
    cout << "exam send!! ";
    exam->printExam();
}
