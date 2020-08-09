---
layout: post
title: "swift 공부 - 간단한 앱만들기로 swift 시작하기(Intro to App Development with Swift)"
author: jihyunhill
categories: swift
tags: swift ios
---

### (5강 내용)간단한 사진 보는 간단한 앱을 만들자.

#### 1. xcode 에서 새로운 프로젝트를 생성하자.    

xcode는 iOS앱을 개발하는데 공통적으로 사용되는 템플릿들이 내장되어 있다. 예를들어 게임이나 기본적인 텝바가 있는 앱 등과 같은 템플릿 말이다. 일단 여기서는 아주아주 기본적인 템플릿을 사용할 것이다. 진짜 아주아주 기본적인 템플릿을 사용해서 사진을 보여주는 앱을 간단하게 만들 것이다. 그래서 게임, 기본 텝 앱이 아닌 Single View Application을 선택하여 열도록 한다.

__Xcode 열기 > Create a new Xcode project 클릭        
> 가장 상단텝에서 iOS고르고 > 밑에 Application텝에서 Single View Application 템플릿 선택 > Next 클릭        
> 앱이름 입력 & UserInterface를 Storyboard로 선택(직관적으로 앱 UI를 확인하기위함!~.~) > Next 클릭__         

#### 2. 한번 실행해볼까?     

자, 한번 실행 시켜보자! 왼쪽 상단에 있는 플레이 버튼을 눌러보자.
( 이 플레이 버튼은 build하고 run을 하기위한 버튼이다. 일련의 running과정은 simulator에서 이루어 지는데 이루어지는데 플레이 옆 정지버튼 옆에서 시뮬레이션 할 iOS의 기종을 선택할 수 있다.)      

\*__빌드__ 는 app을 구성하는 모든 파트를 모으는 것을 말한다.       
 __런__ 은 홈화면에서 아이콘을 텝해서 앱을 시작하는 것을 말한다.      

런!!어라!작성한 것이 없는데 돌아간다.
왜냐하면 __우리가 고른 Single View Application은 xcode에서 제공하는 템플릿이라서 자동으로 앱 개발 환경을 구축되어있기 때문이다.__      

그럼 이제 사진을 보여주는 간단한 앱을 만들어보자.            

#### 3.
