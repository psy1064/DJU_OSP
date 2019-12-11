# DJU_OSP

2019 대전대학교가 주최하는 Open Source Project 경진대회에 제출하는 작품입니다.

# 프로젝트 소개

![applogo.png](https://github.com/psy1064/DJU_OSP/blob/master/READMEFile/applogo.png?raw=true)

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

- [lodingActivity.java](https://github.com/psy1064/DJU_OSP/blob/master/Android/app/src/main/java/my/homekeeper/loadingActivity.java)
  - Splash Activity로 2초 뒤 MainActivity로 이동

  <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/SplashActivity.png?raw=true" width="350">

- [MainActivity](https://github.com/psy1064/DJU_OSP/blob/master/Android/app/src/main/java/my/homekeeper/MainActivity.java)

  - 어플리케이션의 메인화면

  - 어플 상단에는 라즈베리파이로부터 받아온 환경정보(미세먼지, 습도, 온도) 데이터 출력

  - 어플 하단에는 4가지 부가기능(전등제어, CCTV 확인, 알람, 감시모드 활성화) 버튼이 있음

  - 미세먼지 값은 등급에 따라 색과 등급을 표시해줌

    <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity1.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity2.png?raw=true" width="350"> <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity3.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/MainActivity4.png?raw=true" width="350">

  - 실시간 데이터들은 Notification Bar에 띄워줌

    <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/Notification.png?raw=true" width="350">

  - 전등제어 이미지 버튼 클릭 시 메세지 창이 뜨게 되고 명령에 따라 전등을 ON OFF 시켜줌

    <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/LightControl.png?raw=true" width="350">

  - 감시모드 이미지 버튼 클릭 시 ''감시모드가 활성화 되었습니다''  ToastMessage 출력 후 버튼의 색 변경

  - 감시모드가 활성화 되었을 때 라즈베리파이의 인체감지센서에 사람이 감지되면 Notification Bar에 사람이 감지되었다는 알림이 생성되고 알림 클릭 시 cctvActivity로 바로 이동함

    <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/DetectModeOn.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/HumanDetect.png?raw=true" width="350">

- [cctvActivity](https://github.com/psy1064/DJU_OSP/blob/master/Android/app/src/main/java/my/homekeeper/cctvActivity.java)

  - MainActivity의 CCTV 확인의 이미지 버튼을 클릭하면 실행되는 Activity
  - CCTV ON / OFF 버튼을 클릭 시 CCTV를 원격으로 ON / OFF 할 수 있음
  - 신고하기 버튼 클릭 시 메세지 창이 뜨게되고 Yes 클릭 시 112로 전화걸수 있는 다이얼로 이동하게 됨

  <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/CCTVActivity.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/CCTV_OFF.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/CallMessage.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/Call112.png?raw=true" width="350">

- [alarmActivity](https://github.com/psy1064/DJU_OSP/blob/master/Android/app/src/main/java/my/homekeeper/AlarmActivity.java)

  - 설정한 알람시간이 되었을때 실행되는 액티비티
  - MainActivity에서 알람 ON의 이미지 버튼을 클릭하면 시간을 설정할 수 있는 창이 나옴
  - 알람을 설정하면 이미지 버튼의 색이 바뀌고 Notifcation Bar에 설정한 알람시간을 띄움
  - 알람이 울리면 상단의 시계가 실시간으로 출력되고 아래의 Swipe Button을 밀어서 해제하면 종료됨

  <img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/AlarmOn.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/AlarmOnNotification.png?raw=true" width="350"><img src="https://github.com/psy1064/DJU_OSP/blob/master/READMFile/AlarmActivity.png?raw=true" width="350">
