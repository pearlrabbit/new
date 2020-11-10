#include <iostream>
#include <string>
#include "Exam.h"

using namespace std;

void printExam(Exam exam);

int main()
{
    system("clear");
    Exam exam1(EXAM_PRACTICE, "echo 명령어를 이용하여 hello world 를 출력하시오 ", "echo (문구) 을(를)이용하세요", "echo", "echo hello world");
    
    Exam exam2(EXAM_PRACTICE, "cat 명령어를 이용하여 sampleText 파일을 출력하시오 ", "cat (파일이름) 을(를)이용하세요", "cat", "cat sampleText");

    cout << "Practice 1" << endl;
    printExam(exam1);
    cout << endl;
    cout << endl;
    cout << "Practice 2" << endl;
    printExam(exam2);



    return 0;
}

void printExam(Exam exam){
    cout << exam.getDes() << endl;
    cout << "------------힌트------------ " << endl;
    cout << exam.getHint() << endl;
    cout << "----------실행 예시---------- " << endl;
    system(exam.getAnswer().c_str());

    while (1)
    {
        cout << endl;
        cout << "명령어 입력 : ";
        string input;
        getline(cin , input);
        const char * c = input.c_str();
        if (input == exam.getAnswer())
        {
            system(input.c_str());
            cout << "맞았습니다!!" << endl;
            break;
        }
        else
        {
            system(c);
            cout << "틀렸습니다!! 다시 입력해주세요." << endl;
            continue;
        }
    }
}