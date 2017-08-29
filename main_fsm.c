#include "main_fsm.h"
#include <stdlib.h>
#include <stdlib.h>
 
//---------------------------------------------------------------------
// 모듈 초기화 함수 & 변수 & 정의
//---------------------------------------------------------------------
 
 
#define  MAX_BOX 10
enum BOX{
    GET_BOX_ENABLE = 0, // 박스를 가질 수 있다.
    GET_BOX_DISABLE     // 박스를 가질 수 없다.
};
 
static char szMessage[1024] = "";
 
static int m_MyStamina;
static int m_Bundle;
static int m_IsGetBox;
static int m_CurLevel;
 
// 층계올라가기
static void LevelUp(int nStep);
static void LevelDown(int nStep);
 
//---------------------------------------------------------------------
// 핸들러 선언 영역
//---------------------------------------------------------------------
static void OnL1_To_L2  (FSM_EVT e);
static void OnL2_To_L3(FSM_EVT e);
static void OnL3_To_L1(FSM_EVT e);
 
static void OnL1_To_L1  (FSM_EVT e);
static void OnL2_To_L1  (FSM_EVT e);
static void OnL3_To_L2(FSM_EVT e);
 
static void OnRest(FSM_EVT e);
static void OnWarnning(FSM_EVT e);
static void OnDropBox(FSM_EVT e);
static void OnGetBox (FSM_EVT e);
 
//---------------------------------------------------------------------
// FSM 정의 영역
//---------------------------------------------------------------------
 
// FSM 구조체와 StateHandler 테이블
// 핸들러 테이블은 "상태"와 "이벤트"를 기준으로 실행되는 함수를
// 배열관리한다(말 그대로 상태표임).
Action  table_FSM[_MOVEMAN_MAX_STATE][_MOVEMAN_MAX_EVT] = {
    // [이벤트]
    //----------------------------------------------------------|   [상태]
    //  UP          DOWN     REST    DROP BOX    GET BOX
    {OnL1_To_L2, OnL1_To_L1, OnRest, OnWarnning, OnGetBox},     // 1층 상태
    {OnL2_To_L3, OnL2_To_L1, OnRest, OnWarnning, OnWarnning},   // 2층 상태
    {OnL3_To_L1, OnL3_To_L2, OnRest, OnDropBox,  OnWarnning}    // 3층 상태
};
 
// 초기 생성시 실행
Action* InitMainFSM(FSM* f)
{
    // State 초기화
    SetState(f, _MOVEMAN_LEVEL_1);
 
    // 초기화
    m_MyStamina = 50;
    m_Bundle    = MAX_BOX;
    m_IsGetBox  = GET_BOX_ENABLE;
    m_CurLevel  = 1;
 
    return table_FSM;
}
 
//---------------------------------------------------------------------
// 내부함수 영역
//---------------------------------------------------------------------
 
// 메시지 저장하기
static void AddMessage(char* msg)
{
    sprintf(szMessage, "\r\n%s", msg);
}
 
// 층 올라가기
static void LevelUp(int nStep)
{
    m_CurLevel+= nStep;
}
 
// 층 내려가기
static void LevelDown(int nStep)
{
    m_CurLevel-= nStep;
}
 
// 체력보강
static void StaminaUp(int nStep)
{
    m_MyStamina+= nStep;
}
 
// 체력감소
static void StaminaDown(int nStep)
{
    m_MyStamina-= nStep;
}
 
// 체력체크
static int CheckStaminaLow()
{
    // 체력이 다했다면...
    if(m_MyStamina < 0) {
        AddMessage("[경고] 더이상 움질일 수 없습니다. \r\n");
        return 1;
    }
    return 0;
}
 
// 박스 가지기
static void GetBox()
{
    m_IsGetBox  = GET_BOX_DISABLE;
}
 
// 박스 내려놓기
static void DropBox()
{
    m_IsGetBox  = GET_BOX_ENABLE;
}
 
// 박스 채크하기
static int IsGetBox()
{
    return m_IsGetBox;
}
 
 
 
// 모듈외부로 Extern되는 함수
void DisplayCurrent()
{
    // 10개 BOX
    char LEV_BOXES[MAX_BOX + 1] = "##########";
    char MOVE_MAN;
    int notmove_box;
 
    system("clear");
 
    MOVE_MAN  = '&';
    notmove_box = MAX_BOX - m_Bundle;
    if( IsGetBox() ) notmove_box++;
 
    printf("체력: %d\r\n남은 상자:%d\r\n가진상자: %d\r\n위치: %d층\r\n",
             m_MyStamina, m_Bundle, m_IsGetBox, m_CurLevel
    );
 
    printf("__________________________________________________\r\n");
    printf("| 3층|   %c  %s     \r\n",  (m_CurLevel == 3) ? MOVE_MAN: ' ',   &LEV_BOXES[m_Bundle]);
    printf("|-------| |---------------------------------------\r\n");
    printf("| 2층|   %c         \r\n",  (m_CurLevel == 2) ? MOVE_MAN: ' '  );
    printf("|-------| |---------------------------------------\r\n");
    printf("| 1층|   %c  %s     \r\n",  (m_CurLevel == 1) ? MOVE_MAN: ' ',   &LEV_BOXES[notmove_box]);
    printf("|_______|_|_______________________________________\r\n");
    printf("        | |                                       \r\n");
    printf("        Exit            press [?] for help        \r\n");
 
    // 메시지 출력하기
    printf (szMessage);
 
}
 
//---------------------------------------------------------------------
// 핸들러 구현 영역
//---------------------------------------------------------------------
 
// 1층에서 2층 올라가는 경우, 핸들러
static void OnL1_To_L2(FSM_EVT e)
{
 
    if(CheckStaminaLow()) return;
    AddMessage("--> 1층에서 2층으로 올라갑니다.\r\n");
 
    // 층이동
    LevelUp(1);
 
    // 체력감소
    StaminaDown(2);
 
    SetState(e.pOwner, _MOVEMAN_LEVEL_2);
}
 
// 2층에서 3층 올라가는 경우, 핸들러
static void OnL2_To_L3(FSM_EVT e)
{
    if(CheckStaminaLow()) return;
    AddMessage("--> 2층에서 3층으로 올라갑니다.\r\n");
 
    // 층이동
    LevelUp(1);
 
    // 체력감소
    StaminaDown( 2 );
 
    SetState(e.pOwner, _MOVEMAN_LEVEL_3);
}
 
// 3층에서 1층 떨어지는 경우, 핸들러
static void OnL3_To_L1(FSM_EVT e)
{
    // 현재 상태 출력
    AddMessage(
        "-->1층으로 점프했습니다.\r\n" 
        "-->5정도의 체력손실을 입었습니다.\r\n" 
    );
 
    // 층이동
    LevelDown(2);
 
    // 체력감소
    StaminaDown( 5 );
 
    SetState(e.pOwner, _MOVEMAN_LEVEL_1);
}
 
// 1층에서 나가려는 경우(Down요청),  핸들러
static void OnL1_To_L1(FSM_EVT e)
{
    if(m_Bundle < 1) {
        AddMessage("**** ---------------------------------------.****\r\n" 
                   "**** OOO 집에 가시면 됩니다.다음에 봅시다.OO ****\r\n" 
                   "**** ---------------------------------------.****\r\n");
 
        // 상수값을 선언하면 좋다.
        // 지금은 구조에 대한 설명이므로 임의의 값을 저장한다.
        e.pOwner->result = 100;
        return;
 
    } else {
        AddMessage("**** 임무가 완료되지 않았으므로 돌아갈 수 없습니다 ****\r\n");
    }
 
}
 
// 2층에서 1층 내려가는 경우, 핸들러
static void OnL2_To_L1(FSM_EVT e)
{
    if(CheckStaminaLow()) return;
    AddMessage("->2층에서 1층으로 내려갔습니다.\r\n");
 
    // 층이동
    LevelDown(1);
 
    // 체력감소
    StaminaDown(1);
 
    SetState(e.pOwner, _MOVEMAN_LEVEL_1);
}
 
// 3층에서 2층 내려가는 경우, 핸들러
static void OnL3_To_L2(FSM_EVT e)
{
    if(CheckStaminaLow()) return;
    AddMessage("->3층에서 2층으로 내려갔습니다.\r\n");
 
    // 층이동
    LevelDown(1);
 
    // 체력감소
    StaminaDown(1);
 
    SetState(e.pOwner, _MOVEMAN_LEVEL_2);
}
 
// 쉬는 경우, 핸들러
static void OnRest(FSM_EVT e)
{
    StaminaUp( 5 );
 
    AddMessage("--> 쉬면서 체력을 5+만큼 회복했습니다. \r\n");
    //printf("<체력: %d 짐:%d> \r\n", m_MyStamina, m_Bundle);
}
 
// 경고 핸들러
static void OnWarnning(FSM_EVT e)
{
   if(e.EVT == _MOVEMAN_DROP_BOX){
       if(IsGetBox()){
           AddMessage("-->3층까지 간 후에, 상자를 놓아주십시오 \r\n");
       } else {
           AddMessage("-->가지고 있는 박스가 없습니다.\r\n");
       }
 
   } else if (e.EVT == _MOVEMAN_GET_BOX){
       AddMessage("-->상자는 1층에서만 가질 수 있습니다. \r\n");
   }
}
 
// 박스내려놓을 경우, 핸들러
static void OnDropBox(FSM_EVT e)
{
    char msg[1024];
 
    if(CheckStaminaLow()) return;
 
    // 상자를 놓는다.
    if(m_Bundle > 0 && IsGetBox() != 0){
        m_Bundle--;
 
     sprintf(msg, "--> 상자를 놓습니다. 현재 상자 개수는 %d 입니다.\r\n", m_Bundle);
        AddMessage(msg);
 
        DropBox();
 
    }else{
        AddMessage("--> 어떤 상자를 놓겠다는 말인가요? 가진 것이 없는데 말입니다.\r\n");
    }
}
 
// 박스 가질 경우, 핸들러
static void OnGetBox (FSM_EVT e)
{
    if(m_Bundle > 0 && IsGetBox() == GET_BOX_ENABLE){
        AddMessage("--> 상자 1개를 가지셨습니다.\r\n");
        GetBox();
    } else if (m_Bundle > 0 && IsGetBox() == GET_BOX_DISABLE){
        AddMessage("--> 이미 상자 1개를 가지셨습니다.\r\n");
    } else {
        AddMessage("--> 상자를 모두 옮기셨으니 나가주십시오.\r\n");
    }
}
