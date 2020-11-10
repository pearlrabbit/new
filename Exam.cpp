#include "Exam.h"

Exam::Exam()
{
    this->answer = "";
    this->command = "";
    this->description = "";
}

Exam::Exam(ExamType type, string description, string hint, string command, string answer)
{
    this->type = type;
    this->description = description;
    this->command = command;
    this->hint = hint;
    this->answer = answer;
}

void Exam::setType(ExamType type)
{
    this->type = type;
}
void Exam::setDes(string des)
{
    this->description = des;
}
void Exam::setHint(string hint)
{
    this->hint = hint;
}
void Exam::setCommand(string command)
{
    this->command = command;
}
void Exam::setAnswer(string answer)
{
    this->answer = answer;
}

ExamType Exam::getType()
{
    return type;
}
string Exam::getDes()
{
    return description;
}
string Exam::getHint()
{
    return hint;
}
string Exam::getCommand()
{
    return command;
}
string Exam::getAnswer()
{
    return answer;
}