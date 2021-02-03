---
title: "네트워크1장3절"
author: jihyunhill
categories: ComputerNetworks
tags: computerNetworks
---

## 1.3 네트워크 코어
### 패킷 교환
패킷 : 송신 종단 시스템에서 목적지 종단 시스템으로 보내는 긴 메시지를 분할한 작은 데이터 덩어리

#### 1. 회선교환(Circuit-Switching)
circuit이란? 송신자와 수신자 간의 경로에 있는 스위치들이 해당 연결 상태를 유지해야 하는 연결

연결이 이루어지는 동안 네트워크 링크에 일정한 전송률을 예약.  일정 전송률로 데이터 보내는 것이 보장됨(guaranteed)

reserved, dedicated resources, no sharing, call setup required (like reservation of the restaurant)

##### <과정>
①	Circuit setup
②	Data Transfer
③	Circuit release(왜냐하면 여기에 있는 링크 중에서 다른 사람도 쓸 수 있으니까)

<strong> Circuit Switching의 Multiplexing : 이를 통해 하나의 링크로 여러 사용자가 사용가능!</strong>
DM(Frequency-division-multipexing),TDM(Time-division-multiplexing)

 FDM : 링크를 통해 설정된 연결은 링크의 주파수 스펙트럼을 공유. 링크는 연결되는 동안 각 연결에 대해 주파수대역을 고정 제공. Modulation을 통해서 각 채널마다 겹치지 않는 주파수대역을 할당한다.

 TDM : 시간을 일정 주기의 프레임으로 구분하고, 각 프레임을 고정된 수의 시간 슬롯으로 나눈다. (슬롯 1개가 연결에 할당되고, 그 연결은 모든 프레임에서 해당 슬롯 하나를 갖게 된다.)

#### 2.	패킷 교환(packet switching)
 하나의 라우터에서 다른 라우터로 패킷을 보내서, 링크 상에 출발지에서 목적지로 가는 경로들을 거친다.
 링크의 최대 전송 속도와 같은 속도로 각각의 통신링크상에서 전송된다. (each packet transmitted at full link capacity)
 Internet은 패킷 전달을 위해 최선을 다하지만, guarantee는 없다.
