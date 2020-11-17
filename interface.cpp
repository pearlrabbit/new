#include "arrow_input.h"
#include <iostream>
#include <stdlib.h> // system 명령어 사용
#include <string.h> // strcmp 명령어 사용
#include <string>

using namespace std;

const int WIDTH = 83;  // 가로 길이
const int HEIGHT = 27; // 세로 길이

void screen_Output();
void string_Color(string content, string color = "0m", string T_F = "F");
void print_Hyphen(int print_length, string color = "0m", string T_F = "F");
void print_Blank(int num, string color = "0m", string T_F = "F");
void newLine(string T_F);
void Header();
void blank_Frame(int num);

void test_Print(string str1, string str2, string str3);
void cursor(string str1, string str2, string str3);
void check_position(int &ypos, string direction, string str1, string str2,
                    string str3);
void test_question();

int main() {
    string str1 = "테스트를 위한 문장입니다";
    string str2 = "튜토리얼 문제로 이동하게 만들 문장입니다";
    string str3 = "Enter를 누르면 종료하게 만들 문장입니다";

    screen_Output();
    test_Print(str1, str2, str3);
    cursor(str1, str2, str3);
    return 0;
}

void screen_Output() {
    system("tput clear");
    Header();
    print_Hyphen(WIDTH, "47;30m", "T");
    for (int i = 0; i < HEIGHT - 3; i++)
        blank_Frame(WIDTH - 2);
    print_Hyphen(WIDTH, "47;30m", "T");
} // 화면 초기화 및 인터페이스의 전체적인 틀 출력

void string_Color(string content, string color, string T_F) {
    string command = "echo -n \"\033[" + color + content + "\033[0m\"";
    system(command.data());
    newLine(T_F);
} // 색 있는 글자 출력("글자", "글자 색깔", "T")
// T 또는 t 입력 시 공백 출력 후 개행, 이외의 입력 혹은 입력하지 않을시 무시
// 글자 색깔은 "(배경number;색number)m" 입력 ex) "46;30m"

void print_Hyphen(int print_length, string color, string T_F) {
    string num_hyphen;
    for (int i = 0; i < print_length; i++)
        num_hyphen.append("-"); /* code */
    string_Color(num_hyphen, color);
    newLine(T_F);
} // 입력받은 숫자만큼 - 출력 후 개행 (출력할 - 갯수, "글자 색깔")
// T 또는 t 입력 시 공백 출력 후 개행, 이외의 입력 혹은 입력하지 않을시 무시

void print_Blank(int num, string color, string T_F) {
    string blank;
    for (int i = 0; i < num; i++)
        blank.append(" ");
    string_Color(blank, color);

    if (strcmp(T_F.data(), "T") == 0 || strcmp(T_F.data(), "t") == 0)
        system("echo");
    else
        system("echo -n");
} // 입력받은 숫자만큼 공백 출력 ("숫자" "(배경number;색number)m" "t")
// T 또는 t 입력 시 공백 출력 후 개행, 이외의 입력 혹은 입력하지 않을시 무시

void newLine(string T_F) {
    if (strcmp(T_F.data(), "T") == 0 || strcmp(T_F.data(), "t") == 0)
        system("echo");
    else
        system("echo -n");
} // T 또는 t 입력 시 공백 출력 후 개행, 이외의 입력은 무시
// 함수 내에서 사용자의 입력에 따라 동작하기 위한 목적으로 만든 함수

void Header() {
    string str = "Linux Tutorial";
    string_Color("Linux Tutorial", "46;30m");
    print_Blank(WIDTH - str.length(), "46;30m", "T");
} // 인터페이스의 상단 바 출력

void blank_Frame(int num) {
    string_Color("|", "47;30m");
    print_Blank(num, "47;30m");
    string_Color("|", "47;30m", "T");
} // 인터페이스에서 공간이 빈 한 줄 생성

void test_Print(string str1, string str2, string str3) {
    system("tput sc");
    system("tput cup 2 1");
    string_Color(str1, "47;30m");
    system("tput cup 3 1");
    string_Color(str2, "47;30m");
    system("tput cup 4 1");
    string_Color(str3, "47;30m");

    system("tput rc");
} // 인터페이스에 글씨 출력 테스트 함수(임시)

void cursor(string str1, string str2, string str3) {
    system("tput sc");
    system("tput cup 2 1");
    string_Color(str1, "40;37m");

    int ch, ypos = 2; // 각각 방향키, y축 위치를 입력받는 변수
    int count = 0;
    while (1) {
        ch = getch(); // 사용자로부터 키 하나를 입력받음
        if (ch == 27) { // 방향키는 총 3개를 입력받기에 3개의 if문 처리
            ch = getch();
            if (ch == 91) {
                ch = getch();
                switch (ch) {
                case 65: // 위쪽 방향키
                    count = 0;
                    check_position(ypos, "up", str1, str2, str3);
                    continue;
                case 66: // 아래쪽 방향키
                    count = 0;
                    check_position(ypos, "down", str1, str2, str3);
                    continue;
                default:
                    count = 0;
                    continue;
                }
            }
        } else if (ypos == 2) {
            if (ch == '\n') {
                system("tput sc");
                system("tput cup 25 1");
                string_Color("테스트 문장을 클릭하셨습니다!", "40;37m");
                system("tput rc");
                count++;
                if (count > 3) {
                    system("tput sc");
                    system("tput cup 25 1");
                    string_Color("...더 눌러도 아무일도 일어나지 않는다구요",
                                 "40;37m");
                    system("tput rc");
                }
            }
        } else if (ypos == 3) {
            if (ch == '\n') {
                test_question();
            }
        } else if (ypos == 4) {
            if (ch == '\n') // 엔터 입력시 종료
                break;
        }
    } // 67이 오른쪽, 68이 왼쪽  // *** 추후 필요시 추가  ***
    system("tput rc");
} // 커서를 움직이게 할 함수(임시)

void check_position(int &ypos, string direction, string str1, string str2,
                    string str3) {
    string command; // 명령어를 system에 넣기 위한 변수
    if (!direction.compare("down")) {
        if (ypos == 4)
            return;
        ypos++;
    } else if (!direction.compare("up")) {
        if (ypos == 2)
            return;
        ypos--;
    }

    if (ypos == 2) {
        screen_Output();
        test_Print(str1, str2, str3);
        command = "tput cup " + to_string(ypos) + " 1";
        system(command.data());
        string_Color(str1, "40;37m");
    } else if (ypos == 3) {
        screen_Output();
        test_Print(str1, str2, str3);
        command = "tput cup " + to_string(ypos) + " 1";
        system(command.data());
        string_Color(str2, "40;37m");
    } else if (ypos == 4) {
        screen_Output();
        test_Print(str1, str2, str3);
        command = "tput cup " + to_string(ypos) + " 1";
        system(command.data());
        string_Color(str3, "40;37m");
    }
} // ypos에 따라 화면을 출력하는 함수(임시)

void test_question() {
    string command;
    char ch;
    while (1) {
        screen_Output();
        system("tput cup 2 1");
        string_Color("현재 디렉토리 안에 있는 파일을 간단한 형태로 보여주세요", "47;30m");
        system("tput cup 3 1");
        string_Color("미구현 상태라 enter 누르면 종료합니다", "47;30m");
        /*system("read word");
        system("tput cup 3 1");
        system("echo \"$word\"");*/

        ch = getch();
        if (ch == '\n') {
            system("tput cup 27 0");
            exit(1);
        }

        /*if (!strcmp(buf, "ls")) {
            system("tput cup 3 1");
            string_Color("정답입니다", "47;30m");
            system("tput cup 4 1");
            system(buf);
            break;
        }
        else {
            system("tput cup 3 1");
            string_Color("틀렸습니다", "47;30m");
        }*/
    }
}

// c++에서 echo -e(개행문자 사용)는 인식되지 않으며 자동 적용되어있는 상태이다
// \"를 써야 따옴표가 인식된다

// 1. 인터페이스에 표시되는 문자열을 따로 관리
// 2. index값에 해당하는 문자열의 색깔을 바꿔서 출력
