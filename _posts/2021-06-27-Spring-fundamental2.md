---
title: "스프링 기본 핵심원리 (좋은 객체지향이란? SOLID)"
categories: SpringFramework
toc : true
tags:
  - TIL
  - Backend
  - SpringFramework
  - ObjectOriented
---

**본 게시글은 인프런 김영한님의 "스프링 핵심원리 - 기본편" 강의의 Section 1~2를 학습하고 참고하였습니다.*

지난번 포스팅에서 Spring는 **좋은 객체 지향 애플리케이션을 개발할 수 있게 도와주는 프레임워크** 라고 했다. 그렇다면 좋은 객체지향이 도대체 뭘까? 

![/assets/Spring/robertmartin.png](/assets/Spring/robertmartin.png)
![/assets/Spring/cleancode.png](/assets/Spring/cleancode.png)

클린코드의 저자 로버트 마틴은 이에 대해 SOLID라는 답을 내놓는다.

## SOLID 원칙

SOLID는 마틴이 정리한 좋은 객체 지향 설계의 5가지 원칙들의 앞글자를 딴 용어이다.

- SRP(Single responsibility principle)
- OCP(Open/closed principle)
- LSP(Liskov substitution principle)
- ISP(Interface segregation principle)
- DIP(Dependency inversion principle)

### SRP : 단일 책임 원칙

- One class - One responsibility 원칙
- 하나의 클래스에 대한 책임은 완전히 캡슐화 되어야 한다.
- 책임의 기준은 **변경** 이다. 변경시 Side Effect가 적으면 단일 책임의 원칙을 잘 따른 것이다.
- ex -  UI 변경, 객체의 생성과 사용 분리

### OCP : 개방-폐쇄 원칙

- 확장에는 open, 변경에는 close!
- 확장을 하기 위해서는 기존코드를 변경해야하는데...
- 기존 인터페이스와 이를 구현한 new 클래스를 만들어 새로운 기능을 구현한다.
- 다형성 - 역할과 구현의 분리

```java
// driver 클라이언트가 차 구현 클래스를 직접 선택 

Car car = new gasolineCar(); // 변경 전 코드
Car car = new electricCar(); // 변경 코드
```

- 하지만 위 코드는 다른 구현 객체를 사용하기 위해서는 클라이언트 코드 변경 필수 → 다형성 O, but OCP원칙 위반
- 객체의 생성, 연관관계를 관리하는 별도의 조립, 설정자 필요 (ex. 스프링 컨테이너)

### LSP : 리스코프 치환 원칙

- 프로그램의 정확성을 깨뜨리지 않으면서 하위타입의 인스턴스로 바꿀 수 있어야한다.
- 다시 말해, 인터페이스를 구현하는 하위 클래스는 인터페이스의 규약을 모두 지켜야한다.
- 그리고 하위클래스로 만들어진 인스턴스는 역할을 수행하는데 문제가 없어야 한다. - 생뚱맞게 기능을 구현하면 안 된다는 말!

### ISP : 인터페이스 분리 원칙

- 

참고 

[https://ko.wikipedia.org/wiki/단일_책임_원칙](https://ko.wikipedia.org/wiki/%EB%8B%A8%EC%9D%BC_%EC%B1%85%EC%9E%84_%EC%9B%90%EC%B9%99) 

[https://ko.wikipedia.org/wiki/개방-폐쇄_원칙](https://ko.wikipedia.org/wiki/%EA%B0%9C%EB%B0%A9-%ED%8F%90%EC%87%84_%EC%9B%90%EC%B9%99)