---
title: "스프링 기본 핵심원리 (스프링 컨테이너와 스프링 빈)"
categories: SpringFramework
toc : true
tags:
  - TIL
  - Backend
  - SpringFramework
  - ObjectOriented
---

이전 글에서 구성과 실행의 책임을 분리하여 좋은 객체 지향 원리를 만족시킨 Spring 프레임워크의 동작 원리에 대해 간단히 알아보았다. 그리고 마지막부분에서는 스프링 컨테이너가 어떤 것인지에 대해서 간단히 알아보기도 하였는데, 이번에는 스프링 컨테이너와 컨테이너가 관리하는 스프링 빈에 대해 좀 더 알아보고자 한다.
     
## 스프링 컨테이너
이전 포스팅을 보면 스프링 컨테이너란 빈의 생명주기를 관리하는 친구이다. 
### 스프링 컨테이너의 생성
    
__스프링 컨테이너의 상속 관계__
![/assets/Spring/spring-basic-4.png](/assets/Spring/spring-basic-4.png)       
     
1. BeanFactory vs ApplicationContext      
BeanFacotry를 직접 사용하는 경우는 매우매우 드물다. 그 이유는 ApplicationContext가 BeanFactory이외에 다른 인터페이스들을 상속받으면서 더 많으 기능을 지원하기 때문에 BeanFactory 보다는 ApplicationContext를 쓰는 것이다. 즉, 개발자가 생성하는 컨테이너는 ApplicationContext라고 보면 된다.  
\*_잠깐! ApplicationContext는 인터페이스이다._    
```java
ApplicationContext applicationContext = new AnnotationConfigApplicationContext
(AppConfig.class); //ApplicationContext의 구현체로, Applconfig에 대한 객체 생성이 이루어진다.
```

2. XML vs 애노테이션 방식     
java에서 스프링 컨테이너를 생성하는 방법은 설정파일, xml방식, 그리고 애노테이션 기반의 자바 설정 클래스 방식이 있다. xml 방식은 재컴파일을 하지 않아도 된다는 장점이 있지만, 개발자 입장에서는 애노테이션 방식이 좀 더 편리성을 가지므로 애노테이션 기반의 자바 설정 클래스를 많이 사용하는 편이다.    
스프링이 이렇게 다양한 설정 방식을 지원할 수 있는 까닭은 __BeanDefinition__ 를 통한 추상화가 있기 떄문이다. 즉, 역할과 구현을 개념적으로 나눈 것으로, 설정이 xml이든 annotation기반이든지간에 최종적으로 __메타정보인 BeanDefition으로 만들고, 스프링 컨테이너는 BeanDefinition을 참고하여 스프링 Bean을 생성하는 것이다.__
![/assets/Spring/spring-basic-5.png](/assets/Spring/spring-basic-5.png)    
BeanDefinition을 생성하는 방법은 크게 두가지인데, SpringBean을 직접 등록하거나, factoryBean(ex. AppConfig)을 통해 등로하는 것이다. 그런데 전자는 거의 안 쓰인다.


### 스프링 컨테이너의 Bean 등록, 의존관계 설정
1. 스프링 Bean 등록    
스프링 컨테이너는 아까 넘겨준 설정 클래스의 정보(AppConfig)를 가지고 Bean들을 등록한다. 설정 클래스 내부를 보면 어떤 메서드들 앞에 @Bean 표시가 되어 있을 것인데, 바로 요롷게 @Bean 애노테이션을 달아주면 메소드 이름과 return 객체를 key, value 형태로 Bean을 구성해 Bean저장소에 저장한다. 여기서 저장되는 Bean의 이름은 Unique 해야한다는 것을 명심해야 한다.   

    |Bean 이름|Bean 객체|   
    |:----:|:----:|   
    |Car|electricCar|    
    ```java
    public class AppConfig{
      @Bean // 기본값으로 메서드 명을 Bean이름으로 사용 cf) Bean(name=)
      public RepairService Car(){ //key : bean 이름
        return new electricCar(); // value :  bean 객체
      }
    }
    ```
2. Bean의 의존관계 설정      
Bean들을 저장소에 저장 한 뒤, 스프링 컨테이너는 다시 설정 정보 클래스를 참고해서 알아서 촤라라라 의존관계(DI)를 주입한다.


## Bean, 도대체 넌 누구냐?
### Bean이란?
빈은 POJO(Plain Old Java Objet)로, 컨테이너에 의해 관리되는 애플리케이션의 핵심을 이루는 객체이다. Bean의 Scope나 LifeCycle까지 얘기하면 정말 할 얘기도 많고 조사할 것도 많지만 이번 글에서는 간략하게 정의와 종류에 대해서만 알아본다.
### 빈의 종류
|Bean ROLE|설명|   
|:----:|:----:|   
|ROLE_APPLICATION| 일반적으로 사용자가 내부에서 사용하는 Bean|   
|ROLE_SUPPORT| 큰 구조의 설정을 지원하는 Bean |   
|ROLE_INFRASTRUCTURE| 컨테이너의 인프라 기반 역할을 제공하는 빈|    

출처     
[https://docs.spring.io/spring-framework/docs/current/kdoc-api/spring-framework/org.springframework.context.support/-bean-definition-dsl/-role/index.html](https://docs.spring.io/spring-framework/docs/current/kdoc-api/spring-framework/org.springframework.context.support/-bean-definition-dsl/-role/index.html)     
     
[https://docs.spring.io/spring-framework/docs/3.2.x/spring-framework-reference/html/beans.html](https://docs.spring.io/spring-framework/docs/3.2.x/spring-framework-reference/html/beans.html)


*\*본 게시글은 인프런 김영한님의 "스프링 핵심원리 - 기본편" 강의의 Section 4를 학습하고 참고하였습니다.*