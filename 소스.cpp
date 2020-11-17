#include <iostream>
#include <string>
#include "Exam.h"

using namespace std;

void printExam(Exam exam);

int main()
{
    system("clear");
   
    Exam exam1(EXAM_PRACTICE, "현재 자신이 위치하는 디렉토리를 출력하시오 ", "_rint _orking _irectory", "pwd", "pwd /home/ubuntu");

    Exam exam2(EXAM_PRACTICE, "Practice1의 디렉토리 내에서의 파일 및 폴더들을 출력하세요  ", "_ist _egments", "ls", "ls code/ game/ git/ lib/ workspace/");

    Exam exam3(EXAM_PRACTICE, "Practice2의 디렉토리 내에서, game 디렉토리로 이동하시오  ", "_hange _irectory", "cd game/", "cd game/");

    Exam exam4(EXAM_PRACTICE, "Practice3의 디렉토리에서, 다시 home 디렉토리로 이동하시오  ", "_hange _irectory ~", "cd ~", "cd ~ /home/ubuntu");

    Exam exam5(EXAM_PRACTICE, "Practice4의 디렉토리에서, dir1 디렉토리를 생성하시오  ", "_ake _irectory dir1 ", "mkdir dir1", "mkdir dir1\nls dir1/");

    Exam exam6(EXAM_PRACTICE, "Practice5에서 생성한 디렉토리 dir1에 dat 파일 file1을 생성하고 출력하시오  ", " _____ (file name).dat", "touch file1.dat ls", "ls\nfile1.dat");
    
    Exam exam7(EXAM_PRACTICE, "Practice5까지 생성한 디렉토리에서, 하위 디렉토리인 dir2 디렉토리를 생성하시오  ", "_ake _irectory -p  ", "mkdir -p dir1/dir2", "(blank)");

    Exam exam8(EXAM_PRACTICE, "Practice7까지 생성한 디렉토리 구조를 나뭇가지 형식으로 나타내시오  ", " ____ (parent directory)/ ", "tree dir1/", "dir1\nㄴ_____dir2\nㄴ__file1");

    Exam exam9(EXAM_PRACTICE, "Practice7까지 생성한 디렉토리에서 dir1을 디렉토리 삭제 명령어로 삭제하시오  ", " _move dir, 상위 디렉토리도 함께 삭제하시오 ", "rmdir -p dir1/dir2/", "rmdir: failed to remove 'dir1/dir2/': Directory not empty");

    Exam exam10(EXAM_PRACTICE, "Practice8에서 발견된 오류를 수정하고 출력하시오  ", "파일이 있는 디렉토리의 삭제 명령어를 사용하시오 ", "rm -r dir1/ ls", "$ ");

 

    cout << "Practice 1" << endl;
    printExam(exam1);
    cout << endl;
    cout << endl;
    cout << "Practice 2" << endl;
    printExam(exam2);
    cout << endl;
    cout << endl;
    cout << "Practice 3" << endl;
    printExam(exam3);
    cout << endl;
    cout << endl;
    cout << "Practice 4" << endl;
    printExam(exam4);
    cout << endl;
    cout << endl;
    cout << "Practice 5" << endl;
    printExam(exam5);
    cout << endl;
    cout << endl;
    cout << "Practice 6" << endl;
    printExam(exam6);
    cout << endl;
    cout << endl;
    cout << "Practice 7" << endl;
    printExam(exam7);
    cout << endl;
    cout << endl;
    cout << "Practice 8" << endl;
    printExam(exam8);
    cout << endl;
    cout << endl;
    cout << "Practice 9" << endl;
    printExam(exam9);
    cout << endl;
    cout << endl;
    cout << "Practice 10" << endl;
    printExam(exam10);


    return 0;
}

void printExam(Exam exam) {
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
        getline(cin, input);
        const char* c = input.c_str();
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