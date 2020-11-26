#ifndef __USERDATA_H__
#define __USERDATA_H__

#include <unistd.h>
#include <iostream>

#define MSG_DATA_TYPE 1
#define MSG_EXAM_TYPE 2
#define MSG_DATA_SIZE (sizeof(MsgUserData) - sizeof(long))
#define MAX_NAME_LEN 32

struct __MsgUserData {
    long mtype;
    pid_t pid;
    char name[MAX_NAME_LEN+1];
};
typedef struct __MsgUserData MsgUserData;

struct __MsgExamData {
    long mtype;
    pid_t pid;
    char answer[MAX_NAME_LEN+1];
};
typedef struct __MsgExamData MsgExamData;

class UserData {
    public :
    UserData();
    UserData(pid_t pId, std::string name, int score);

    void setPid(int id);
    void setName(std::string name);
    void setScore(int score);

    int getPid(void);
    std::string getName(void);
    int getScore(void);
    void printData(void);

    private:
        pid_t pId;
        char name[MAX_NAME_LEN+1];
        int score;

};

#endif