#include "main_fsm.h"

// 도움말
void DisplayHelp()
{
	system("clear");

    printf(">>>>> 교육용 StateMachine 예제 <<<<<<<\r\n");
    printf(">>>>> 3층까지 짐옮기기:        <<<<<<<\r\n");   
    printf("--------------------------------------\r\n");
    printf("사용법:\r\n");
    printf("--------------------------------------\r\n");
    printf("q  : 올라가기 ");
    printf("a  : 내려가기                      \r\n");
    printf("r or R: 쉬어가기 s or S: 상태보기     \r\n");
    printf("d or D: 상자놓기 ");
    printf("g or G: 상자가지기                    \r\n");    
    printf("--------------------------------------\r\n");
	printf("아무키나 누르세요\r\n");

	getchar();

}

int main()
{
    int ch;
	const int DIRECTION = 224;
	const int UP_KEY    = 'q';
	const int DOWN_KEY  = 'a';
	
    //-------------------------------------------
    // 상태머신 사용법(초기화)
    // FSM 개체만큼 상태관리가 가능하다.
    //-------------------------------------------
    FSM_EVT e;
    FSM     f;

    // StateMachine 초기화
    InitStateMachine(
        &f,                  // 초기화할 FSM 개체(개수만큼 생성 초기화해준다) 
        InitMainFSM(&f),     // MainFSM 초기화함수(FSM 마다 만들어 준다) : 상태테이블 리턴
        _MOVEMAN_MAX_EVT,    // 이벤트 개수
        _MOVEMAN_MAX_STATE   // STATE  개수
    );
    
	DisplayHelp();
	DisplayCurrent();
    
    while ( (ch = getchar()) != 'E') {

        if(ch == DIRECTION) 
			ch = getchar();
 
        //-----------------------------------------------------------------------------
        // 상태머신 이벤트 전달
        if(ch == UP_KEY          ){ e.EVT = _MOVEMAN_GO_UP;    DoEvent(&f, e); }
        if(ch == DOWN_KEY        ){ e.EVT = _MOVEMAN_GO_DOWN;  DoEvent(&f, e); }
        if(ch == 'r' || ch == 'R'){ e.EVT = _MOVEMAN_REST;     DoEvent(&f, e); } 
        if(ch == 'd' || ch == 'D'){ e.EVT = _MOVEMAN_DROP_BOX; DoEvent(&f, e); }
        if(ch == 'g' || ch == 'G'){ e.EVT = _MOVEMAN_GET_BOX;  DoEvent(&f, e); }  
        //-----------------------------------------------------------------------------
        
        if(ch == '?' || ch == '?'){ DisplayHelp();  }
        
		// UI에서 메뉴처리 
        DisplayCurrent();
        
		
        // 상수 처리 하지 않고 임의의 값 처리
        if( GetResult(f) == 100) 
           break;
   
    }
    //-------------------------------------------
    
    return 0;
}