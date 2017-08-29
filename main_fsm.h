/*
    제목  : 3층 건물 상자 옮기기 -FSM
    목적  : 프로그램의 한정된 흐름을 규칙적으로 제어한다.
    작성자: 박성완
    작성일: 2005.04.20
    수정일: 2005.12.13
 
 
    참고  : 간단한 상태머신 예제
            교육용임
*/
#ifndef  __PSW_FSM_MAIN_SNAKE
#define  __PSW_FSM_MAIN_SNAKE
#include "fsm.h"
 
// Event 정의
enum EVENT_MOVEMAN
{
    _MOVEMAN_GO_UP  = 0,  // 올라가기     이벤트
    _MOVEMAN_GO_DOWN,     // 내려가기     이벤트
    _MOVEMAN_REST,        // 쉬어가기     이벤트
    _MOVEMAN_DROP_BOX,    // 상자내려놓기 이벤트
    _MOVEMAN_GET_BOX,     // 상자얻기     이벤트
    _MOVEMAN_MAX_EVT      /* 자동카운트용 */
};
 
// 상태 정의
enum STATE_MOVEMAN
{
    _MOVEMAN_LEVEL_1 = 0,
    _MOVEMAN_LEVEL_2,
    _MOVEMAN_LEVEL_3,
    _MOVEMAN_CAN_NOT_MOVE,
    _MOVEMAN_MAX_STATE    /* 자동카운트용 */
};
 
extern Action* InitMainFSM(FSM* e);
extern void    DisplayCurrent();
#endif