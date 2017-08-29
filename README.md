# fsm-c-style-  FSM을 사용하는 이유
FSM은 유한상태기계(Finite State Machine)의 약자이다. 
말 자체는 어렵게 느껴지지만 목적은 “우리가 만드는 프로그램의 모든 상황과 이벤트를 하나의 Logic으로 관리하자”이다.
 
왜 이런 것이 필요하게 되었을까?
이유는 간단하다. “사람이 알아보기 편하게 하기 위해서”이다.
 
우리가 흔히 말하는 “라면코드”로 만들지 못할 프로그램은 없다.
라면코드는 “..라면”의 뜻을 가진 if 문을 무식하게 발라대는 코드를 말한다. 그러나 라면 코드의 최강의 문제점은
 
프로그램의 기능이 추가되면 추가될수록, 개발자의 고통도 추가된다는 것이다.
 
If (이라면)
   If (이라면)
If (이라면)
 If (이라면)
 If (이라면)
                 DoWork();
…
..
..
이런 코드들은 분석하고 싶지도 않다. 오른쪽 오른쪽으로 경우의 수가 늘어나다 보면
코드를 보는 사람은 의도하지 않게 극우주의자가 된다.
 
FSM은 if 문을 사용하여 어떠한 상황을 구현을 하는 것이 아니라 상황에 따른 핸들러를 구현하는 방법으로 개발하는 방법이다. 우리가 Event Driven 방식으로 개발하는 Visual C++이나 Java의 이벤트 핸들러 방식이 이러한 것이라고 보면 된다.


 
2.     사용되는 곳
 
l  동기적 API 사용이 불가능(이벤트와 핸들러)한 “임베디드 S/W”
l  각종 통신 프로토콜 S/W
l  많은 로직이 구현되는 게임시스템
 
3.     구현로직
이 예제는 FSM을 구현하는 방법에서 Table을 이용하여 Event와 State를 관리하는 방법을 설명한다.

l  Table을 이용하여 Event와 State를 관리
l  각 상황에 따른 핸들러 작성
[출처] 상태머신(FSM)을 이용한 이벤트관리 방식|작성자 The Gamer