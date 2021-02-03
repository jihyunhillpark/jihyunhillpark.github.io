---
title: "Spring - 맥북(Mac)에서 STS설치"
author: jihyunhill
categories: Java/Spring
tags: Java Spring
---

## 부제 : Failed to create the Java Virtual Machine 해결

![/assets/Spring/logo.png](/assets/Spring/logo.png)

STS(Spring Tool Suite)이란

Spring Framework을 사용한 개발을 지원하기 위한 Eclipse기반의 개발 환경이다.

프로그램을 실행시켜보면 Eclipse IDE와 비슷한 것을 볼 수 있다. Eclipse와 비슷하게 STS를 통해서 애플케이션을 실행하고 디버깅하거나 deploy할 수 있다. 언뜻 보기에 두 IDE가 비슷해보이는데 왜 나눠서 사용할까!?

먼저 Eclipse에서는 spring plugin을 기본으로 포함되지 않기 때문에 개발자가 별도로 추가해야한다. 반면 STS는 이름에서도 알 수 있듯이 spring에 특화된 것으로, 다양한 spring plugin을 지원하고 있어서 좀 더 spring 기반 개발을 할 때 편리함을 준다는 이점이 있다. 그래서 본격적으로 spring 프로젝트를 하면 해당 IDE를 쓰는게 좋을 듯 하다.

대신에 이클립스보다는 프로그램이 무겁다..;; 언제나 trade off는 있는 법!

### 맥북에서 깔려면 어떻게!?

사실 맥북에 까는 작업 자체는 easy하다.

1. Java설치 (나는 openJDK를 설치함) + 자바 환경변수설정
2. Apache tomcat 설치 (나중에 연동할 서버를 위해 설치한다.)
3. STS 설치한다 (나는 3버전을 설치함)

    현재 4까지 나왔는데 왜 3을 설치했을까? 기존 Spring Legacy Project가 3까지 지원이 되는데, 4에서는 그렇지 않아 추가적인 add-on설치가 필요하다고 한다.

### 그냥 깔고 실행시키면 되는거 아니었나!

다 설치한 후 실행시켰는데 요상한 에러가 떴다!ㅇ0ㅇ

정상적으로 설치가 되었다면 다음과 같은 로딩화면이 떠야한다.

![/assets/Spring/success_inst.png](/assets/Spring/success_inst.png)

그러나 나는 다음과 같은 에러메시지가 떴다. 은근히 맥북 쓰는 사람들 중에 이 오류를 겪는 사람이 많은 것으로 보인다.

![/assets/Spring/alert.png](/assets/Spring/alert.png)

Stackoverflow에 보니 STS앱의 .ini(응용프로그램 실행시 필요한 초기화 정보를 포함하고 있는 파일)에 가상머신에 대한 부분을 추가해주어야 한다고 한다.

[STS설치경로]/[STS프로그램].app/Contents/Eclipse/[STS프로그램].ini 을 열어

파일 가장 앞머리에

**-vm**

/**Library/Java/JavaVirtualMachines/[Java버전]/Contents/Home/bin/java**

을 추가한 뒤 빠져나온다.



나의 경우는

**(파일열기)**

**$vi /Applications/STS.app/Contents/Eclipse/STS.ini**

**(추가)**

...

**-vm**

/**Library/Java/JavaVirtualMachines/[Java버전]/Contents/Home/bin/java**

**그런데 이대로 했는데 똑같은 에러가 계속 뜰뿐 해결되지 않았다.**

그렇게 지웠다 다시 깔았다 지지고 볶다가 발견한 사실, 가상머신에 대한 부분을

**-vm**

/**Library/Java/JavaVirtualMachines/[Java버전]/Contents/Home/bin/java**

startup

**.ini 파일 중 -vmargs 앞에 넣어줘야 한다는 것이었다.**

나는 파일 맨끝에 추가했었는데...

이 글을 보는 사람들은 나와 같은 시행착오를 겪지 않길 바라며 참조한 링크를 첨부하며 총총...

[https://stackoverflow.com/questions/53110144/sts-failure-to-create-java-virtual-machine](https://stackoverflow.com/questions/53110144/sts-failure-to-create-java-virtual-machine)
