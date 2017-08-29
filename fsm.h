/*
    제목  : 상태관리자-FSM
    목적  : 프로그램의 한정된 흐름을 규칙적으로 제어한다.
    작성자: 박성완
    작성일: 2005.04.20
    수정일: 2005.12.13
 
 
    참고  : 1) 상태와 이벤트로 분기점을 가진다.
            2) Handler 테이블로 관리할 수 있다.
            3) 상태전이에 대한 메소드를 제공한다.
            4) 상태는 내부에서 제어한다. 이벤트는 외부 입력항목이다.
 
    모바일 환경에 맞게 C 형식으로 포팅함.
*/
#ifndef  __PSW_FSM_SNAKE
#define  __PSW_FSM_SNAKE
 
 
// State Handler의 타입
typedef void (*Action)(FSM_EVT);
 
// FSM(상태머신) Structure
typedef struct tagFSM{
 
    int      result;
    unsigned curState;
 
    unsigned MaxEvent;
    unsigned MaxState;
    Action*  HandlerTable;
 
} FSM;
 
// 이벤트와 매개변수
typedef struct tagFSM_EVT{
    unsigned EVT;
    int    lParam;    // Parameter 1
    int    wParam;    // Parameter 2
    FSM*   pOwner;     // State개체
} FSM_EVT;
 
// FSM을 초기화 한다.
extern int  DoEvent(FSM* f, FSM_EVT evt);
 
// 상태를 전이한다.
extern void SetState(FSM* f,unsigned target);
 
// 상태를 가지고 온다.
extern unsigned GetState(FSM f);
 
// 리턴 상태를 가지고 온다.
extern unsigned GetResult(FSM f);
 
// 아무것도 하지 않는다.
extern void doNothing(FSM_EVT e);
 
// FSM을 초기화한다.
extern unsigned InitStateMachine(
    FSM* f, Action* table,
    unsigned MaxEvent,
    unsigned MaxState
);
 
#endif

