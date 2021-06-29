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
![/assets/Spring/cleancode.png](/assets/Spring/cleancode.png){: width="30%" height="30%"}

클린코드의 저자 로버트 마틴은 이에 대해 SOLID라는 답을 내놓는다.

## SOLID 원칙

SOLID는 마틴이 정리한 좋은 객체 지향 설계의 5가지 원칙들의 앞글자를 딴 용어이다.

- SRP(Single responsibility principle)
- OCP(Open/closed principle) : 중요
- LSP(Liskov substitution principle)
- ISP(Interface segregation principle)
- DIP(Dependency inversion principle) : 중요

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

- 클라이언트와 이용하지 않는 메소드 사이에는 의존관계가 없어야 한다는 원칙
- 큰 범용 인터페이스를 구체적이고 작은 단위의 인터페이스로 분리시킴으로써, 클라이언트가 꼭 필요한 메서드들만을 쓸 수 있게 만든다.
- ex. 스마트폰 인터페이스 -> 조작 인터페이스, 수리 인터페이스로 분리 
- ex. 사용자 클라이언트 -> 사용자 클라이언트, 엔지니어 클라이언트로 분리
- 분리하면 수리 인터페이스 자체가 변해도 사용자 클라이언트에 영향을 주지 않는다.
- 명확성과 대체 가능성에 대한 장점이 있다.

### DIP : 의존관계 역전 원칙

- 프로그래머는 "추상화(인터페이스)에 의존해야지, 구체화(구현 클래스)에 의존하면 안된다." 
- 클라이언트가 구현체에 의존하게 되면 변경이 아주 어려워지므로, 인터페이스에 의존하여 유연하게 구현체를 변경해야한다. 즉, 구현이 아닌 역할(role)에 의존하게 만든다.
- 주의! __OCP에서 살펴본 Driver클라이언트 예시는 인터페이스와 구현 클래스에 동시에 의존한다.__ 
- 여기서 Driver클라이언트가 구현 클래스(gasolineCar 혹은 electricCar)를 직접 선택하는 것은 구현에 의존하는 것으로 DIP를 위반하고 있다.
- Driver클라이언트는 역할에 해당하는 인터페이스 Car만 의존해야한다.

### 다형성의 한계
1. 객체지향의 핵심인 다형성만으로는 대체가능성에 한계가 있다.(즉, 구현 객체를 변경할 때 클라이언트의 코드가 변경 됨)
2. 따라서 다형성 만으로는 OCP, DIP원칙을 온전히 지킬 수 없다.

### 보완 : 스프링과 객체지향
- 스프링은 DI기능과 DI컨테이너를 제공함으로써 __다형성 + OCP + DIP__ 를 지원한다.
- DI란, Dependency  Injection으로 의존성을 주입하는 기술을 말한다.
- 그리고 DI 컨테이너가 자바객체들간에 의존성을 주입하고 관리하는 역할을 한다.
- 결과적으로 클라이언트의 코드를 변경하지 않고 기능을 확장한다.
- 대체 가능성의 장점

### 결론
- 좋은 객체 지향 프로그램을 만들기 위해서는 __역할과 구현을 분리한 설계를 해야한다.__
- 다형성만으로는 부족하다.
- Spring이 다형성뿐만 아니라 OCP와 DIP 원칙에 의거해, 분리에 따른 유연한 변경을 가능하게 한다.


참고 

[https://ko.wikipedia.org/wiki/단일_책임_원칙](https://ko.wikipedia.org/wiki/%EB%8B%A8%EC%9D%BC_%EC%B1%85%EC%9E%84_%EC%9B%90%EC%B9%99) 

[https://ko.wikipedia.org/wiki/개방-폐쇄_원칙](https://ko.wikipedia.org/wiki/%EA%B0%9C%EB%B0%A9-%ED%8F%90%EC%87%84_%EC%9B%90%EC%B9%99)

[https://ko.wikipedia.org/wiki/개방-폐쇄_원칙]([https://ko.wikipedia.org/wiki/개방-폐쇄_원칙](https://ko.wikipedia.org/wiki/%EA%B0%9C%EB%B0%A9-%ED%8F%90%EC%87%84_%EC%9B%90%EC%B9%99))
