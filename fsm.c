#include "fsm.h"

// 외부 호출용임.
int DoEvent(FSM* f, FSM_EVT evt)
{
  Action act;
  unsigned const e = evt.EVT;
  if(f->MaxEvent < e) return 0;

  // EVT에 호출하는 FSM 포인터 저장
  evt.pOwner = f;

  // 해당 함수 실행
  act =  *(  (f->HandlerTable) + (f->curState * f->MaxEvent) + e);
  (*act)(evt);
  return 0;
}

// 아무것도 안하는 함수는
// 어디서나 필요하다.
void doNothing(FSM_EVT e)
{

}

// 상태를 전이한다.
void SetState(FSM* f, unsigned target)
{
   if(f->MaxState < target) return;
   f->curState = target;
}

// 상태를 가지고 온다.
unsigned GetState(FSM f)
{
   return f.curState;
}

// FSM을 초기화한다.
unsigned InitStateMachine(
   FSM* f, Action* table,
   unsigned MaxEvent,
   unsigned MaxState
   )
{
   unsigned i,  j;
   Action   act;

   f->HandlerTable = table;
   f->MaxEvent     = MaxEvent;
   f->MaxState     = MaxState;

   return 0;
}

// 리턴 상태를 가지고 온다.
extern unsigned GetResult(FSM f)
{
   return f.result;
}

