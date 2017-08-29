# fsm-c-style-  FSM을 사용하는 이유
> 
FSM은 유한상태기계(Finite State Machine)의 약자이다. 
말 자체는 어렵게 느껴지지만 목적은 “우리가 만드는 프로그램의 모든 상황과 이벤트를 하나의 Logic으로 관리하자”이다.
 
왜 이런 것이 필요하게 되었을까?
이유는 간단하다. 

>
“사람이 알아보기 편하게 하기 위해서”이다. 

우리가 흔히 말하는 “라면코드”로 만들지 못할 프로그램은 없다. 라면코드는 “..라면”의 뜻을 가진 if 문을 무식하게 발라대는 코드를 말한다. 그러나 라면 코드의 최강의 문제점은 프로그램의 기능이 추가되면 추가될 수록, 개발자의 고통도 추가된다는 것이다.

![image](https://user-images.githubusercontent.com/31234716/29800396-cc2a26fa-8ca4-11e7-8fb6-fdb66003be38.png)

 
### FSM이 주로 사용되는 곳
 
- 동기적 API 사용이 불가능(이벤트와 핸들러)한 “임베디드 S/W”
- 각종 통신 프로토콜 S/W
- 많은 로직이 구현되는 게임시스템
 
### 구현로직
이 예제는 FSM을 구현하는 방법에서 Table을 이용하여 Event와 State를 관리하는 방법을 설명한다.

![](http://postfiles12.naver.net/20110827_11/adsloader_13144399807078MELr_PNG/1.PNG?type=w2)

- Table을 이용하여 Event와 State를 관리 
- 각 상황에 따른 핸들러 작성

### makefile
~~~makefile
OBJECTS = main.o fsm.o main_fsm.o
SRCS = main.c fsm.c main_fsm.c
 
CC = gcc
CFLAGS = -g -c
 
TARGET =fsm 
 
$(TARGET) : $(OBJECTS)
	$(CC) -o $(TARGET) -g $(OBJECTS)
 
clean : 
	rm -f $(OBJECTS) $(TARGET)
~~~
![](/data/make.gif)

### debugging
![](/data/fsm_debug.gif)



[원본블로그](http://blog.naver.com/adsloader/50119456326)
