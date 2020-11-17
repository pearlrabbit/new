#include <iostream>
#include <termios.h>

int getch() {
    int ch;
    struct termios current, old;

    tcgetattr(0, &old); // 터미널 속성을 얻는다(터미널 파일 기술자, 터미널 속성을 저장할 주소)
    current = old;
    current.c_lflag &= ~(ICANON | ECHO); // local flags, (캐노니컬 입력 모드 사용 | 입력을 다시 출력)
    current.c_cc[VMIN] = 1; // blocking read until 1 character arrives, 1개의 문자열이 도착할때까지 읽기를 막음
    current.c_cc[VTIME] = 0; // inter-character timer unused, 문자간 쓰이지 않는 타이머
    tcsetattr(0, TCSAFLUSH, &current); // 터미널 속성을 설정한다(터미널 파일 기술자, 동작 선택(송수신 완료 후 변경한다), 터미널 속성을 저장할 주소)
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &old);

    return ch;
}

// 리눅스는 getch 함수가 존재하지 않아서 이를 따로 구현하였음

/*int getch_B(int is_echo) {
    int ch;
    struct termios old, current;

    tcgetattr(0, &old); // 현재 설정된 terminal i/o 값을 backup함
    current = old; // 현재의 설정된 terminal i/o에 일부 속성만 변경하기 위해 복사함
    current.c_lflag &= ~ICANON; // buffer i/o를 중단함

    if (is_echo) // 입력값을 화면에 표시할 경우
        current.c_lflag |= ECHO;
    else // 입력값을 화면에 표시하지 않을 경우
        current.c_lflag &= ~ECHO;

    // 변경된 설정값으로 설정
    tcsetattr(0, TCSAFLUSH, &current);
    ch = getchar(); // stdin에서 한 문자를 가져온다(입력받아 아스키 값으로 반환)
    tcsetattr(0, TCSAFLUSH, &old);

    return ch;
} // 인자로 0을 넣어주면 출력하지 않음
// 입력받은 것의 출력 여부를 결정하고 싶다면 이 함수를 사용할 것*/
