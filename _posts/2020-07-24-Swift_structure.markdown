---
layout: post
title: "swift 공부 - Structure"
author: jihyunhill
categories: swift
tags: swift ios
---

### 데이터 모델링     

앱을 만들 때 필요한 정보를 어떻게 나타내는지는 참 중요한 일이다.      
앱에서 실제로 다루어지는 데이터의 타입을 두고 __모델__ 혹은 __데이터 모델링__ 이라고 한다.       
이 __모델__ 은 특정 앱에 대해서만 특정하게 존재한다.           
예를 들어 음악 앱에서 트랙, 아티스트, 앨범등을 하나로 묶어서 모델을 짜듯이 말이다.     

이번에는 그림에 대한 데이터 모델링을 해보자.    


{% highlight javascript %}
let pictureTitles = ["Kiss", "Sunflower", "Golconde"]
let artists = ["Gustav Klimt", "Vincent Van Gogh", "Rene Magritte"]
let years = [1908, 1888, 1953]
let pictures3 = "\(pictureTitles[2]) by \(artists[2]), in \(year[2])s"
{% endhighlight %}        

이처럼 세개의 어레이로 만들어서 접근할 수 있다!    
그런데 어딘가 비효율적으로 보이지 않는가?...       
이렇게 여러개의 어레이로 데이터 모델링을 할 경우, 반복문을 통한 모든 페인틍의 자동 방문은 어떻게 할 것이며, picutre에 새로운 정보 즉, 모델로서 한 부분을 추가할 때는 어떻게 하겠는가?    

### 데이터 모델로 필요한 정보들을 하나의 블락으로 묶다.

앞서 말한 번거로움의 문제점을 해결하기 위해서 데이터 모델의 필요했던 정보들을 한 곳의 모아 블락으로 만들고, 이를 하나의 type으로 만들 수 있다.     
{% highlight javascript %}
struct Picture {
    let title: String
    let artist: String
    let year: Int
}
{% endhighlight %}    
짜잔! 새로 만든 Picture 타입은 세 가지의 property를 가지게 되고, 달리 말해 세 가지 상수들의 집합이다.
그럼 새로운 Picture 타입의 작품 인스턴스를 만들어보자.
{% highlight javascript %}
let song = Song(title: "Kiss", artist: "Gustav Klimt", year: 1908)
{% endhighlight %}    

__잠깐!__ 스위프트의 모든 타입들을 적어도 하나의 initializer를 가진다. 즉, 우리가 직접 만든 structure에 대해서도 자동으로 initializer가 제공된다는 사실!기본적으로 제공되는 이 초기자(?)는 모든 property들을 지정해줘야하지만, 스트럭트 내부안에 init()을 작성함으로써 이 역시 customize할 수 있다.       

### sturct의 변형(Mutability)

이제까지 struct를 let을 사용하여 선언함으로써 상수로서(immutale)선언했다.     
그런데 여기에 museum이라는 박물관 위치를 새로운 스트럭쳐의 속성으로 넣고 싶다고 하자.     
작품이 있는 장소는 변할 수도 있기에 이에 대해 변수로 지정하고 싶다면?    
{% highlight javascript %}
struct Picture {
    let title: String
    let artist: String
    let year: Int
    var museum: String
}
{% endhighlight %}     
으로 var를 써서 선언하면 된다.      

그리고 struct의 인스턴스를 만들기 위해서 let이 아닌 var키워드를 이용해서 선언하면된다.
{% highlight javascript %}
var picture = Picture(title: "Kiss", artist: "Gustav Klimt", year: 1908, museum: "Great British")
{% endhighlight %}     
__잠깐, let 은 안되는가?__    
No!안된다! 속성이 var여서 그 값이 바뀔 수 있다는 것은 큰 집합인 struct의 값이 바뀔 수 있다는 것을 의미하기 때문!      

### 내부 계산으로 property만들어 포함시키기   
String 타입의 변수의 count 속성처럼 매번 바뀌는 속성을 만들 수 있다.      
이 속성의 타입은 다른 속성값들에 의해서 변화되기 때문에 var로 선언한다.
{% highlight javascript %}
struct Picture {
    let title: String
    let artist: String
    let year: Int
    var museum: String
    var museumStayingYear: String {
      let period = 2020 - years
      reutnr "\(period)years in \(museum)"
    }
}
var picture = Picture(title: "Kiss", artist: "Gustav Klimt", year: 1908, museum: "Great British")
picture.museumStayingYear
{% endhighlight %}    

### 함수의 인자와 리턴으로는 어떻게 사용하는가!?    
다른 타입들 처럼 사용하면된다! 그리고 스트럭쳐에 국한된 함수만 만들경우 스트럭쳐 내부에 함수(메소드라고도 한다)를 만들어서 사용하는 것이 좋다.       
