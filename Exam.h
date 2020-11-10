#include <string>

using namespace std;

enum ExamType
{
    EXAM_PRACTICE,
    EXAM_EXERCISE,
};

class Exam
{
public:
    Exam();
    Exam(ExamType type, string description, string hint,string command, string answer);
    
    ExamType getType();
    string getDes();
    string getHint();
    string getCommand();
    string getAnswer();

    void setType(ExamType type);
    void setDes(string des);
    void setHint(string hint);
    void setCommand(string command);
    void setAnswer(string answer);

private:
    ExamType type;
    string description;
    string hint;
    string command;
    string answer;
};