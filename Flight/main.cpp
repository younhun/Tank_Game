#include "YH_game.h"

int main(void)
{
CGame game_;
game_.Run();

	return 0;
}


void setCursortype(CURSOR_TYPE c) {//마우스 커서 안보이게
     CONSOLE_CURSOR_INFO CurInfo;
     switch (c) {
     case NOCURSOR:
          CurInfo.dwSize=1;
          CurInfo.bVisible=FALSE;
          break;
     case SOLIDCURSOR:
          CurInfo.dwSize=100;
          CurInfo.bVisible=TRUE;
          break;
     case NORMALCURSOR:
          CurInfo.dwSize=20;
          CurInfo.bVisible=TRUE;
          break; 
     }
     SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
