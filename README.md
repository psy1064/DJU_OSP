# DJU_OSP
2019 대전대학교가 주최하는 Open Source Project 경진대회에 제출하는 작품입니다.

# 프로젝트 소개

- 프로젝트명 : 라즈베리파이를 이용한 스마트홈 및 원격관리 어플리케이션
- 개발기간 : 19.10.01 ~ 19.12.05
- 개발인원 : 박세용

## 작품 기능

- 라즈베리파이를 이용해 스마트홈 구축
  - 실시간으로 일정주기(10초)마다 실내 환경 정보(온도, 습도, 미세먼지) 데이터 수집 및 어플리케이션에 전송
  - 인체감지센서를 통해 사람이 인식되는것을 감지 후 어플리케이션에 전송
  - Qt Programming과 터치식 LCD를 이용해 GUI 환경 구축
  - 적외선 Pi camera를 이용해 CCTV 영상 촬영
  - 서보모터로 전등 스위치 ON / OFF
- 안드로이드 어플리케이션으로 실시간 모니터링 및 제어
  - 라즈베리파이에서 수집, 전송한 데이터를 실시간 모니터링
  - Pi camera로 촬영한 영상을 실시간 스트리밍
  - 원격으로 전등 스위치에 부착된 서보모터를 조작해 ON / OFF 가능
  - 알람을 설정하여 원하는 시간에 전등스위치를 켜주고 알람소리 재생
  - 어플 내 감시모드 활성화 시 인체감지센서에 사람이 감지되었을 때 Push 알람

## 작품 구조도

![structure.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/structure.png?raw=true)





## 실행화면

![execute1.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/execute1.png?raw=true)

![execute2.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/execute2.png?raw=true)