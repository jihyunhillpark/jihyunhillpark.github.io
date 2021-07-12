---
title: "스프링 기본 핵심원리 (객체 지향 원리 적용) - 부제:프레임워크없이 스프링 동작 만들어보기"
categories: SpringFramework
toc : true
tags:
  - TIL
  - Backend
  - SpringFramework
  - ObjectOriented
---

이전 글에서 좋은 객체지향의 5가지 원칙에 대한 글을 썼다. 이번에는 전번글에서 다뤘던 예시와 비슷한 사례를 가져와 좋은 객체지향원리를 적용해 보도록 하겠다.(이전 글에서 Spring을 사용하는 중요한 이유 중 하나가 좋은 객체지향을 구현하기 위해서라는 것도 기억해보자!)    
     
먼저 아래와 같은 클래스 관계를 구현하기 위해 다음과 같은 코드를 짰다고 하자.
![/assets/Spring/spring-basic-1.png](/assets/Spring/spring-basic-1.png)

```java
//EX1
public class RepairServiceImpl implements RepairService {
  private final Car car = new gasolineCar();
}
```
    
그런데 이 때 RepairServiceImpl에서 가솔린차가 아닌 전기차를 사용하고자 한다면 어떤 일이 벌어질까? 
```java
public class RepairServiceImpl implements RepairService {
  // private final Car car = new gasolineCar();
  private final Car car = new electricCar();
}
```
구현 객체를 바꿔줘야하기 때문에 RepairSerivceImpl을 고쳐야만 한다(OCP위반). 이는 달리 말하면 클라이언트(RepairServiceImpl)가 인터페이스(Car)뿐만이 아니라 구체 클래스(gasolineCar 혹은 electricCar)에도 의존하고 있다는 것이다(DIP위반). 따라서 우리가 구현하고자 한 설계는 처음에 본 다이어그램을 지향했다면, 실제로 그려지는 클래스들의 의존관계는 아래와 같이 된다.    
    
![/assets/Spring/spring-basic-2.png](/assets/Spring/spring-basic-2.png)    

간단히 말하자면 가장 첫 번째의 코드는 아래와 같은 문제점으로 좋은 객체지향 원칙을 준수하지 못했다.
1. OCP를 위반 - 구체 클래스 변경시 클라이언트 코드도 변경해야 함
2. DIP를 위반 - 추상, 구체 모두에게 의존하고 있다.

_그렇다면 어떻게 해야할까?_      
간단하다. DIP와 OCP를 위반하지 않도록 구체클래스에는 영향을 받지 않도록 __인터페이스에만 의존하도록 설계하면된다.__

```java
// EX2
public class RepairServiceImpl implements RepairService {
  private Car car;
}
```
EX1의 코드를 EX2의 코드처럼 인터페이스에만 의존하도록 바꾸었다. 그런데 구현클래스를 없앴으니 껍데기에 해당하는 인터페이스만 가지고는 실질적으로 코드를 실행할 수 없다(NullPointerException). 

_그렇다면 어떻게 해야할까?_     
간단하다. __무엇인가가 클라이언트(RepairServiceImpl)에 구현객체(electricCar)를 대신해서 생성하고 주입__ 하면 된다.     

그런데 현재 클라이언트가 구현 객체를 생성하고 사용할 수 있게 주입하고, 또 실행하는 등 다양한 책임을 지고 있다. 여기서 우리는 클라이언트가 '실행'에만 집중하고 의존관계를 외부에서 처리하게끔 하고자 한다. 즉 책임단위로 클래스를 분리하여 클래스들의 응집도를 높이고자 한다(high cohesion). 이 작업을 '관심사의 분리'라고 부르겠다.(김영한님의 아주 좋은 표현이시다!)

## 괌심사의 분리 - 대리자 AppConfig
대리자인 AppConfig 클래스를 만들어서 앱 전체의 동작 방식을 구성 및 설정(cofig)하는 역할을 부여하자. 마치 관리자, 오거나이저와 같다고 생각하면 좋겠다. 이 구성 과정에 __구체 클래스로 부터 객체들을 생성하고, 객체들을 연결__ 하는 일이 포함된다. 이렇게 역할을 분리함으로써 구성 및 설정과 담당한 일은 AppConfig클래스가 도맡아 하게되고, 클라이언트(RepariServiceImpl)은 오롯이 지원하는 기능을 실행하면 된다. 

```java
public class AppConfig{
  public RepairService repairService(){
    return new RepairServiceImpl(new electricCar()); //1. 구현객체(electricCar) 생성 2. 생성한 객체 레퍼런스(electricCar)를 생성자를 통해서 주입(연결) 
  }
}
```
```java
public class RepairServiceImpl{
  public RepairServiceImpl(Car car){
    this.car = car; //어떤 구현 객체가 오는지 신경 안씀
  }
}
```
```java
public class RepairApp{
  public static void main(String[] args){
    AppConfig appConfig = new AppConfig(); 
    RepairService repairService = appConfig.repairService();
    ...
  }
}
```
결과적으로 RepairServiceImpl는 추상 클래스인 Car에만 의존할 뿐, 더이상 구체 클래스(electricCar 나 gasolineCar)를 의존하지 않게 되었다. (DIP충족)    
당연히 RepairServiceImpl은 더이상 어떤 구현 객체가 주입되는지에 대해 책임을 질 필요가 없어지게 되었고, 외주를 받은 AppConfig만이 이 일을 수행한다. (SRP충족)    

![/assets/Spring/spring-basic-3.png](/assets/Spring/spring-basic-3.png)    

정리하자면 괌심사의 분리로 
1. 설계가 DIP를 충족하게 되었다.
2. 객체를 생성하고 연결하는 역할(config)과 실행하는 역할(execute), 두 가지로 클래스의 역할이 분리되었다. (= 구성과 사용의 분리)  

_AppConfig클래스에서 구현객체를 생성하기 위해서는, 해당 구현 클래스에 생성자 코드를 작성해 놓은 상태여야 한다는 것을 잊지말자!_

## IoC, DI, 컨테이너
### IoC란? 
제어의 역전을 말한다. 전에 클라이언트 구현 객체(RepairServiceImpl)가 스스로 필요한 서버 구현 객체를 생성하고, 연결하고, 실행까지 다 했다. 그런데 AppConfig가 등장하면서 구현 객체는 실행만을 담당하고 프로그램 제어의 흐름(구현 객체 생성, 연결)은 AppConfig가 맡게 되었다. 즉, 이말은 RepairServiceImple이 인터페이스 호출을 하지만 어떤 구현 객체가 실해될지 모른다는 말이다.
이처럼 __프로그램의 제어 흐름을 직접 제어하는 것이 아니라 외부에서 관리하는 것을 제어의 역전(IoC)이다.__

### DI(의존성 주입)
클라이언트(RepairServiceImpe)가 인터페이스(Car)에 의존하지만 실제 어떤 구현 객체가 사용될지 모른다. DI는 애플리케이션 실행 시점(런타임)때 실제로 생성된 객체의 참조가 연결된 의존관계이다. 

### 컨테이너
AppConfig 처럼 객체를 생성하고 관리하면서 의존관계를 연결해 주는 것을 IoC/DI 컨테이너라고 한다. 
이번에 다룬 세 개념을 적용하여 애플리케이션을 만들면 다음과 같은 형태가 된다. 이로써 스프링을 쓰지 않으면서 스프링 컨테이너와 같은 효과를 내고 스프링 동작원리에 따르는 애플리케이션을 만들어보았다.

__정리__
1. 클라이언트가 구현객체와 인터페이스를 모두 의존하지 못하도록한다.(인터페이스만 의존하도록 함)
2. AppConfig라는 객체 생성 및 의존 관계 주입을 담당하는 대리자 생성
3. AppConfig는 컨테이너 역할 -> 5가지의 원칙과 IoC, DI를 만족시키는 앱 __(스프링 동작원리와 같음)__     
    
## 스프링으로 전환하기
기존에는 AppConfig를 이용해서 개발자가 직접 객체를 생성하고 의존성 주입(DI)를 했었다. 자, 이제는 __ApplicationContext__ 라는 스프링 컨테이너를 사용하여 스프링으로 전환해보자.


먼저 기존에는 AppConfig를 통해 직접 객체들을 생성하고 DI를 했지만, 스플이 컨테이너를 통해 __자동으로 객체들을 생성하고 DI할 수 있다.__     
   
1. AppConfig에 @Configuration 애노테이션 추가 -> 설정 정보로 사용
2. 각 메서드에 @Bean 애노테이션 추가 -> 스프링 컨테이너가 해당 메서드 모두 호출하여 반환객체 빈으로 등록
3. ApplicationContext - 찐 스프링 컨테이너 사용

```java
@Configuration
public class AppConfig{
  @Bean // 기본값으로 메서드 명을 Bean이름으로 사용 cf) Bean(name=)
  public RepairService repairService(){
    return new RepairServiceImpl(new electricCar()); 
  }
}
```
```java
public class RepairServiceImpl{
  public RepairServiceImpl(Car car){
    this.car = car; //어떤 구현 객체가 오는지 신경 안씀
  }
}
```
```java
public class RepairApp{
  public static void main(String[] args){
    ApplicationContext applicationContext = new AnnotationConfigApplicationContext(AppConfig.class);
    RepairService repairService = applicationContext.getBean("repairService", repairService); 
    ...
  }
}
```

결과
|Before|After|
|---|---|
|개발자가 필요한 객체를 AppConfig를 통해 직접 조회| applicationContext.getBean()메서드를 통해 조회|
|개발자가 직접 자바코드로 설정, 실행 구현|스프링 컨테이너에 객체를 스프링 빈으로 등록, 스프링 컨테이너에서 스프링 빈 조회 및 사용|      
      
     

**본 게시글은 인프런 김영한님의 "스프링 핵심원리 - 기본편" 강의의 Section 3를 학습하고 참고하였습니다.*