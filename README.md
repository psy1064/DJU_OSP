# DJU_OSP
2019 대전대학교가 주최하는 Open Source Project 경진대회에 제출하는 작품입니다.

# 프로젝트 소개

- 프로젝트명 : 라즈베리파이를 이용한 스마트홈 및 원격관리 어플리케이션
- 개발기간 : 19.10.01 ~ 19.12.05
- 개발인원 : 박세용

## 작품 기능

- 라즈베리파이를 이용한 스마트 홈 구축
  - 실시간 환경 정보(온도, 습도, 미세먼지) 데이터 수집
  - Qt Programming과 LCD를 이용해 GUI 형태로 출력
  - Pi camera로 CCTV 영상 촬영 및 적외선 촬영 가능
  - 서보모터로 전등 스위치 ON/OFF
  - 인체감지센서를 통해 사람 인식
- 안드로이드 어플리케이션으로 실시간 모니터링 및 제어
  - 라즈베리파이에서 수집한 데이터를 실시간 모니터링
  - Pi camera로 촬영한 영상을 실시간 스트리밍
  - CCTV 원격 ON / OFF
  - 원격으로 전등 스위치 ON / OFF 
  - 알람 기능을 활용하여 원하는 시간에 전등 스위치 ON
  - 어플 내 감시모드 활성화 시 사람이 감지되었을 때 Push 알람

## 작품 구조도

![structure.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/structure.png?raw=true)





## 라즈베리파이 실행화면

![RaspberryPi_Execute1.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/RaspberryPi_Execute1.png?raw=true) 

![RaspberryPi_Execute2.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/RaspberryPi_Execute2.png?raw=true)

## 안드로이드 어플리케이션 실행화면

![SplashActivity.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/SplashActivity.png?raw=true){: width="20%" height="20%"}

- [lodingActivity.java](https://github.com/psy1064/DJU_OSP/blob/master/Android/app/src/main/java/my/homekeeper/loadingActivity.java)
  - Splash Activity로 2초 뒤 MainActivity로 이동

![MainActivity1.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity1.png?raw=true){: width="20%" height="20%"}

![MainActivity2.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity2.png?raw=true){: width="20%" height="20%"}

![MainActivity3.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity3.png?raw=true){: width="20%" height="20%"}

![MainActivity4.png](https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity4.png?raw=true){: width="20%" height="20%"}

- [MainActivity](https://github.com/psy1064/DJU_OSP/blob/master/Android/app/src/main/java/my/homekeeper/MainActivity.java)
  - 어플리케이션의 메인화면
  - 어플 상단에는 라즈베리파이로부터 받아온 환경정보(미세먼지, 습도, 온도) 데이터 출력
  - 어플 하단에는 4가지 부가기능(전등제어, CCTV 확인, 알람, 감시모드 활성화) 버튼이 있음
  - 미세먼지 값은 등급에 따라 색과 등급을 표시해줌