#include "UserData.hpp"
#include <string.h>
#include <string>
#include <iostream>

UserData::UserData(){
    this->pId = -1;
    memset(this->name, 0x00, MAX_NAME_LEN + 1);
    this->score = -1.0;
}

UserData::UserData(pid_t pId, std::string name, int score){
    this->pId = pId;
    memcpy(this->name, name.c_str(), MAX_NAME_LEN);
    this->score = score;
}

void UserData::setPid(int id)
{
    this->pId = id;
}
void UserData::setName(std::string name)
{
    memcpy(this->name, name.c_str(), MAX_NAME_LEN);
}
void UserData::setScore(int score)
{
    this->score = score;
}

int UserData::getPid(void)
{
    return this->pId;
}
std::string UserData::getName(void)
{
    return std::string(this->name);
}
int UserData::getScore(void)
{
    return this->score;
}
void UserData::printData(void){
    std::cout << "userPid : " << this->getPid() << ", userName : " << this->getName()
        << ", userScore : " << this->getScore() << std::endl;
}
