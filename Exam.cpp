#include "Exam.hpp"
#include <string.h>
#include <iostream>
using namespace std;

Exam::Exam()
{
    this->num = -1;
    memset(this->answer, 0x00, MAX_NAME_LEN + 1);
    memset(this->description, 0x00, MAX_NAME_LEN + 1);
    memset(this->hint, 0x00, MAX_NAME_LEN + 1);
}

Exam::Exam(int num, string description, string hint,string answer)
{
    this->num = num;
    memcpy(this->description, description.c_str(), MAX_NAME_LEN);
    memcpy(this->hint, hint.c_str(), MAX_NAME_LEN);
    memcpy(this->answer, answer.c_str(), MAX_NAME_LEN);
}

void Exam::setNum(int num)
{
    this->num = num;
}
void Exam::setDes(string des)
{
    memcpy(this->description, des.c_str(), MAX_NAME_LEN);
}
void Exam::setHint(string hint)
{
    memcpy(this->hint, hint.c_str(), MAX_NAME_LEN);
}
void Exam::setAnswer(string answer)
{
    memcpy(this->answer, answer.c_str(), MAX_NAME_LEN);
}
void Exam::printExam(void){
    cout << "num : " << this->num << ",description : " << this->description
    << ",answer : " << this->answer << endl;
}

int Exam::getNum(){
    return num;
}
string Exam::getDes()
{
    return std::string(this->description);
}
string Exam::getHint()
{
    return std::string(this->hint);
}
string Exam::getAnswer()
{
    return std::string(this->answer);
}