#include <string>
#include <string.h>
using namespace std;

#define MAX_NAME_LEN 32

class Exam
{
public:
    Exam();
    Exam(int num, string description, string hint, string answer);
    
    int getNum();
    string getDes();
    string getHint();
    string getAnswer();

    
    void setNum(int num);
    void setDes(string desc);
    void setHint(string hint);
    void setAnswer(string answer);
    void printExam(void);

private:
    int num;
    char description[MAX_NAME_LEN+1];
    char hint[MAX_NAME_LEN+1];
    char answer[MAX_NAME_LEN+1];
};