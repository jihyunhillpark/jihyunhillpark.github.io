---
title: "Servlet의 lifeCycle, 상속관계"
categories: Backend
toc : true
tags:
  - TIL
  - Backend
  - Servlet
---

## Servlet이란?

- 자바를 사용하여 웹페이지를 __동적__ 으로 생성하는 서버측 프로그램 __(html in java)__
- 자바 서블릿은 웹 서버의 성능을 향상하기 위해 사용되는 java class의 일종 (확장자가 .java)
- JavaSE가 아닌 JavaEE 사양의 일부분
- 요청(request)마다 프로세스보다 가벼운 스레드(Thread)로 응답(response)

## Servlet lifeCycle

서블릿은 main 함수가 엔트리 포인트가 되어 동장하는 일반 javaSE의 class들과는 달리 servler 컨테이너에 의해 생성, 처리, 소멸된다.
생성~처리~소멸까지의 서블릿 객체의 생명주기를 이루는 __콜백함수__ 들이 있다.
<br>
![](/assets/backend/Life-Cycle-Of-Servlet.jpg)
<br>
init() : 서블릿의 코드가 수정되거나 최초에 __메모리에 로드__ 할 때 __한번__ 호출된다.<br><br>
service() : 사용자의 요청에 대한 처리하는 함수로, __매 요청마다__ 호출된다.<br><br>
destroy() : 코드가 수정되는 등 서블릿 객체가 더이상 필요없게되면 __한번__ 호출하여 메모리에서 해제해 소멸한다.

## 상속관계
자바에서 서블릿 클래스와 그에 맞는 환경을 사용하기 위한 api를 제공한다. 백엔드 동작을 위한 서블릿 클래스를 작성하기 위해서는 Servlet 패키지를 import하고, 관련 인터페이스를 구현하거나 클래스를 상속받으면 된다.<br><br>
__\* 주의! javaSE 가 아닌 javaEE 문서 보도록 한다.__ 링크첨부⬇️<br>
https://javaee.github.io/javaee-spec/javadocs/<br><br>
![](/assets/backend/servlet-api.png)
