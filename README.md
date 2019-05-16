# Wheeler(마우스 휠버튼을 이용한 화면 캡쳐프로그램)

## 프로그램 다운로드

[Wheeler_Install.exe](https://sdr1982.tistory.com/attachment/cfile6.uf@1767E8504D0DF7A0388199.exe)

## 소개
### 1. 소개

* 제작자 : 신동렬(Ryan)
* 홈페이지 : http://sdr1982.tistory.com
* 이메일 : 1982sdr@hanmail.net

### 2. 제작동기

저는 주로 웹 브라이저로 구글 크롬(Google Chrome)을 사용합니다. 크롬을 사용하다 보니 마우스 휠버튼(가운데버튼)의 활용도가 높았습니다. 마우스 휠버튼으로 탭을 닫을 수 있다던가 새창으로 주소를 열수 있다던가 하는 기능었습니다.  처음엔 윈도우 자체도 프로그램을 휠버튼으로 실행하거나 종료할 수 있으면 좋겠다 생각하여 제작하게 되었습니다.

그리고 휠버튼을 이용한 화면캡쳐 기능이 있으면 좋겠다는 의견을 듣고 바로 기능을 추가하였습니다. 개인적으로 만들고 싶은 기능이나 수정하고 싶은 부분들이 더 있는데 언제 시간이 날 지는 모르겠습니다. 건의사항이 있거나 궁금한 사항이 있으시면 블로그를 방문하시거나 이메일을 보내주세요.

### 3. 사용한 보조 프로그램 및 라이브러리
#### (1) CxImage

이 프로그램을 제작하면서 사용한 라이브러리 입니다. JPG 파일과 PNG 파일 저장기능을 구현하기 위해 CxImage 라이브러리를 포함하여 컴파일 및 링크를 하였습니다.

관련 주소 : http://www.codeproject.com/KB/graphics/cximage.aspx

## 기능

마우스 휠(가운데) 버튼을 클릭함으로서 다양한 기능을 수행합니다.

### 1. 화면 캡쳐
### 2. 화면 캡쳐의 부가기능
#### (1) 프로그램 실행
#### (2) 파일로 저장
### 3. 더블 클릭 효과
### 4. 프로그램 닫기/종료 효과
### 5. 프로그램 최소화 효과
### 6. 마우스 제스처 기능

## 화면캡쳐
### 1. 화면캡쳐
#### (1) 땔 때

마우스 휠(가운데) 버튼을 드래그하여 화면을 캡쳐합니다.

마우스를 드롭(누르던 버튼을 땔 때)할 때 만들어진 사각형 화면 크기만큼 캡쳐됩니다.

마우스를 드래그하는 중에 ESC버튼이나 마우스 오른쪽 버튼을 누르면 캡쳐가 취소됩니다.

#### (2) 토글모드

마우스 휠(가운데)버튼을 누르면 캡쳐를 할 수 있는 화면 상태가 됩니다.

마우스 왼쪽 버튼으로 사각형을 그려 캡쳐 영역을 지정합니다.

원하는 캡쳐 영역을 지정했다면 마우스 휠 버튼을 또 누르면 그 영역이 캡쳐됩니다.

반면, 이 상태에서 마우스 오른쪽 버튼을 누르면 캡쳐를 취소할 수 있습니다.

#### (3) 윈도우

마우스 휠(가운데)버튼을 누르면 해당 윈도우가 캡쳐가 됩니다.

Alt+PrintScreen 키 대신 사용하실 수 있습니다.

### 2. 부가기능

#### (1) 프로그램 실행

캡쳐를 한 후 지정된 프로그램을 수행합니다. 기본적으로 '그림판' 프로그램이 자동으로 실행됩니다.

'그림판'이 실행되면 자동으로 그 그림판에 캡쳐한 화면을 자동으로 붙여 넣게 됩니다.
 - '하나만 실행' : 지정된 프로그램의 윈도우에서만 캡쳐한 화면을 자동으로 보여줍니다.
 - '프로그램 선택' : 자동 붙여넣기 기능을 수행할 수 있도록 그림판 이외의 프로그램을 지정합니다.

#### (2) 파일로 저장

캡쳐를 한 후 그 이미지를 파일로 저장합니다. 기본적으로 프로그램이 설치된 디렉터리에 파일이 저장됩니다.

저장할 때마다 1,2, 3, ... 방식으로 파일 이름이 증가합니다.
 - 'JPEG','PNG' : 원하시는 파일 확장자로 이미지 파일이 저장이 됩니다. 
 - '폴더 저장' : 원하시는 폴더에 그림파일을 저장합니다. (프로그램 실행 때마다 재설정 해야 함.) 

