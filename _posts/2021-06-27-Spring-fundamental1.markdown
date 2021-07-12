---
title: "스프링 기본 핵심원리"
categories: SpringFramework
toc : true
tags:
  - TIL
  - Backend
  - SpringFramework
---

웹사이트가 점점 커지면서 엔터프라이즈급의 서비스가 필요하게 되었다. Java진영에서 새롭게 정한 표준기술 EJB(Enterprise Java Bean)가 등장하여 애플리케이션 작성의 용이함을 도모함

## EJB

엔터프라이즈 자바빈즈(Enterprise JavaBeans - EJB)는 기업환경의 시스템을 구현하기 위한 서버측 컴포넌트 모델이다. 즉, EJB는 애플리케이션의 업무 로직을 가지고 있는 서버 애플리케이션이다. EJB 사양은 Java EE의 자바 API 중 하나로, 주로 웹 시스템에서 JSP는 화면 로직을 처리하고, EJB는 업무 로직을 처리하는 역할을 한다.

EJB에는 다음 3가지 종류가 있다.

- 세션 빈 (Session Bean) : DB 연동이 필요없는 세션 관련 객체
- 엔티티 빈 (Entity Bean) : DB의 데이터를 관리하는 객체
    - 데이터베이스의 데이터를 관리하는 객체
    - Insert(삽입), Update(수정), Delete(삭제), Select(조회)
    - DB 관련 쿼리는 자동으로 만들어지고 개발자는 고급 업무 처리에 집중할 수 있음
    - DB가 수정되면 코드 수정 없이 다시 배포(설정 문서 만들어서 복사)
- 메시지 구동 빈 (Message-driven Bean)

그러나...EJB는 다음과 같은 단점을 가졌다.

1. EJB의 구조는 클래스, 인터페스, xml 등을 만들어서 jar로 디플로이 해야한다. 코드 수정시 이 번거로운 과정을 거쳐야했다. 사용이 복잡해 사용하기 어려웠기 때문에 개발의 효율성이 낮다
2. EJB스펙에 정의된 인터페이스에 따라 코드를 작성하므로 기존에 작성된 POJO를 변경해야 함
3. 컨테이너를 띄우는데 오래 걸려 개발속도가 느리며, 테스트를 하기 위해서 EJB서버가 필요하는 등 EJB의존적임
4. 설정해야하는 부분이 많다.  
(RMI를 기반으로 하는 서버 - 무거운 컨테이너)

## 로드존슨과 하이버네이트 "EJB비판, 옛날로 가자"

로드존슨

- EJB컨테이너를 대체 (경량화)
- EJB의 문제점 지적, 오늘날 Spring Framework의 모태, BeanFactory, ApplicationContext, POJO, IoC, DI 등의 주입 (AOP, DI 등 새로운 프로그래밍 방법론 등장)
- J2EE Design and Development 책 출간

하이버네이트

- EJB엔티티빈의 기술 대체. JPA(Java Persistence API) 정의
- EJB엔티티빈 → 하이버네이트(구현체) → JPA(인터페이스)

*POJO(Plain Old Java Object)
EJB이전에 사용한 특정 프레임워크나 기술에 종속, 의존적이지 않은 순수한 자바 객체. 특정한 인터페이스 구현 및 클래스 상속없이도 사용 가능. 생산성과 이식성이 좋다.


## Spring Framework의 등장

- 유겐휠러와 얀카로프와 로드 존슨이 **오픈소스 프로젝트**를 진행 (인류에 기여..감사합니다..)
- EJB를 쓰던 겨울같은 시절이 지나가고 봄이 왔다는 뜻임
- JEE지원 + AOP, DI등의 기능까지 지원

## 스프링의 역사

|스프링 버전|기반 설정|특징|출시년도|
|---|---|---|---|
|스프링 1.0|XML|설정할 거 너무 많다!|2003|
|스프링 2.0|XML|근데 이제 "편의기능"을 곁들인...|2006|
|스프링 3.0|JAVA코드|- Spring.jar파일을 여러개의 Jar파일로 분리하여 제공, Rest API 지원, OXM(Object XML Mapping)기능 추가, Java Annotation을 이용한 DI지원|2009|
|스프링 4.0|JAVA 8버전 지원|- JDK 6부터 지원, Lambda사용 가능, Optional 사용 가능, meta annotation지원, Core Container들의 기능 지원 확대|2013|
|스프링부트 1.0||- tomcat서버의 내장(배포편리), 스프링 프레임워크의 설정 편의|2014|
|스프링 5.0, 스프링부트 2.0|JAVA 8버전 표준|- Reactive Programming 지원(Node js와 같은 non-blocking형태), Core Container들의 기능 지원 확대, Kotlin 지원, JUnit5 지원|2017|
|스프링 5.3.4, 스프링부트 2.5.2|||2021 현재 최신버전|

## Spring Frame의 생태계

![](/assets/Spring/projects.png)

출처 : [https://spring.io/projects](https://spring.io/projects)
스프링 프로젝트를 여러 형태로 확장하여 개발할 수 있다. 위 사이트에서 해당 프로젝트 > Feature를 누르면 spring, spring boot에 대한 특징도 간략하게 볼 수 있다.

필수 요소

- 스프링 프레임워크 - 핵심 기술
- 스프링 부트 - 여러 스프링 기술들을 편리하게 사용

선택 요소

- 그 밖에 스프링 데이터, 스프링 세션, 스프링 시큐리티, 스프링 restDocs, 스프링 배치, 스프링 클라우드

## 스프링의 핵심 개념(특징)

스프링을 만든 근본적인 이유와 그 컨셉에 대해 알아야한다. 그렇지 않으면 spring를 사용하는 것은 그저 API를 사용하는 것에 지나지 않는다.

스프링을 사용하는 이유를 한 문장으로 말하자면 **좋은 객체 지향 애플리케이션을 개발할 수 있게 도와주는 프레임워크**이기 때문이다.

- **객체 지향 언어**의 강력한 특징을 살려냄. (기존 EJB의 경우. EJB의존 개발 → 객체 지향 장점 lost, IoC(DI)컨테이너로 객체 지향 프로그래밍(다형성) 성공)
- 그중에서도 중요한 **다형성**의 특징 (**역할과 구현의 분리 - 역할 : 인터페이스, 구현 : 클래스)**
- 새로운 기능 구현체가 등장할지라도 기존의 것들(역할, 다른 구현체들)을 바꾸지 않아도 됨. (ex. 운전자 - 자동차 예시)
- 사용자는 기능들을 사용하기 위해서 역할만 알면됨. 그리고 그 기능들의 구현체들은 언제든지 대체 할(갈아끼울) 수 있어야 함(구현을 편리하게 변경 - 오버라이딩). 즉, 스프링을 사용하면 마치 레고 블럭 조립하듯 구현을 편리하게 변경할 수 있다.
- 유연한 변경, 확장가능한 설계

## 스프링 프레임워크의 구조와 기술

개발자는 스프링 프레임워크와 설정을 덧붙여 프로젝트를 커스터마이즈 한다.

![](/assets/Spring/structure.png)

출처 : 도서 "토비의 스프링" 8-1 그림

IoC/DI

- IoC(제어의 역전) : 객체들의 의존관계를 개발자가 구현하거나 관리하는 것이 아니라 컨테이너가 하도록 한다.
- DI(의존성 주입) : XML이나 Annotation을 통해서 객체 간 의존 관계 설정. 확장 가능한 객체를 만든 뒤, 읜존관계를 외부에(XML, Annotation)서 다이나믹하게 설정

AOP (Aspect Oriented Programming - 관심 지향 프로그래밍)

- 모듈의 핵심관심 사항과 전체 공통관심 사항 기준으로 하는 프로그래밍
- 핵심 로직 개발시 시스템에 대한 공통 관심사(로깅, 보안 등)는 신경 쓸 필요가없다. 관심사의 분리를 통해 공통 모듈로 빼낸 후, 모듈을 여러 코드에 적용한다.

PSA (Portable Service Abstraction)

- 확장성이 좋은 코드
- 트랜잭션의 추상화 등 Low level에 해당하는 기술적인 구현부분과 인터페이스를 분리
- 세부기술의 변경과 상관없이 일관된 방식으로 접근 가능

## SpringFramework의 구성요소 - 스프링 프레임워크의 모듈

![](/assets/Spring/modules.png)

출처 : [https://docs.spring.io/spring-framework/docs/3.0.0.M3/reference/html/ch01s02.html](https://docs.spring.io/spring-framework/docs/3.0.0.M3/reference/html/ch01s02.html)

Core Container는 Beans, Core,Context, SpEL로 구성

여기서 가장 기반이 되는 Core Container에 속한 모듈에 대해서만 기술하고 나머지 모듈에 대해서는 설명이 잘된 아래 링크를 첨부한다

[https://m.blog.naver.com/isaac7263/221356391846](https://m.blog.naver.com/isaac7263/221356391846)

### Core와 Beans

- 프레임워크의 가장 핵심적인 기능 제공 (IoC, DI 등)
- 주 컴포넌트인 BeanFactory은 팩토리 패턴의 구현체임
- BeanFactory - IoC를 통해 실제 프로그램 로직에서 설정 및 의존성에 대한 기술을 분리(decouple) 함. (싱글톤의 필요 X)

### Context

- Core와 Beans가 프레임워크의 핵심적인 기능을 제공했다면, context는 프레임워크 방식으로 객체에 접근하는 기능
- Beans기능을 상속받아 확장
- 메시지 국제화, Application의 생명주기 이벤트, 자원로딩, 유효성 검증, 서블릿 컨테이너에 의한 context생성 등에 대한 지원

영어가 더 편한 사람들은 다음의 링크도 함께 보면 좋겠다.

[https://docs.spring.io/spring-framework/docs/4.0.x/spring-framework-reference/html/overview.html](https://docs.spring.io/spring-framework/docs/4.0.x/spring-framework-reference/html/overview.html)

## (추가) 빌드관리 툴 Gradle vs Maven

소스 코드를 컴파일, 테스팅, 정적 분석을 하고 자동으로 실행가능한 애플리케이션을 생성하는 도구 프로그램. 라이브러리를 자동으로 추가 및 관리하고 버전을 동기화한다.

Ant - 초기 JAVA 빌드도구

- 프로젝트당 개발 빌드 스크립트
- 프로젝트의 특정 타겟을 실행
- 아주 복잡한 스크립트 사용
- 스크립트 재사용 불가능
- 점진적으로 개발속도가 느림(복잡해지는 스크립트 때문 )

Maven - Ant의 불편함을 해소하기 위해 등장  

- 전체적인 프로젝트 관리
- 추상화된 빌드 lifecycle 사용
- plug-ins, repositories를 재사용
- 점진적으로 빌드속도가 빨라짐(library가 이미 있기 때문)
- xml로 라이브러리를 정의하고 활용

Gradle - Ant와 Maven의 장점을 모아 등장함

- 별도의 빌드스크립트를 통하여 사용할 어플리케이션 버전, 라이브러리등의 항목 설정
- if-else, for 등의 조건 로직 구현 가능
- 뛰어난 프로젝트 정보 제공
- 개발 가이드라인 제공
- 새로운 기능을 쉽게 설치할 수 있다. 업데이트할 수 있다.
- Java나 Groovy를 통해 개발자의 의도에 따라 설계 가능
- Groovy를 사용함으로써, 동적 빌드 호출에 용이.
- 빌드와 테스트 실행 결과가 Maven보다 속도가 빠르다(위 특징의 결과)
- 스크립트 길이와 가독성이 Maven보다 좋다

**본 게시글은 인프런 김영한님의 "스프링 핵심원리 - 기본편" 강의의 Section 1~2를 학습하고 참고하였습니다.*
