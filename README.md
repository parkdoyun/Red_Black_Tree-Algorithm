# Red_Black_Tree-Algorithm

<h2>1.	개요</h2>
<h3>1)	설계 목적</h3>
# 알고리즘 수업 시간에 배운 Red-Black Tree를 활용하여 앱스토어에 등록된 애플리케이션들을 효율적으로 관리합니다.
<br><br>
<h3>2)	요구사항</h3>
#	애플리케이션에 삽입되는 정보는 1. ID, 2. 이름, 3. 용량, 4. 가격 순이고, 각 정보들은 차례로 공백으로 구분되어 저장됩니다.<br>
#	수행할 기능들은 등록, 검색, 업데이트, 할인 4가지가 있습니다.<br>
#	각 기능들은 명령어 구분 기호 I[등록], F[검색], R[업데이트], D[할인] 중 하나를 입력하여 수행됩니다.<br>
#	[등록] 애플리케이션 정보(ID, 이름, 용량, 가격)를 입력 받아 Red-Black Tree에 해당 정보를 담은 새로운 node를 삽입하고 그 node의 depth를 출력합니다. 만약, 이미 애플리케이션이 등록되어 있다면 등록하지 않고 node의 depth만 출력합니다.<br>
#	[검색] 애플리케이션 ID를 입력 받아 Red-Black Tree를 탐색합니다. 만약 애플리케이션이 존재하면 해당 정보를 출력하고 존재하지 않으면 “NULL”을 출력합니다.<br>
#	[업데이트] 애플리케이션 정보(ID, 이름, 용량, 가격)를 입력 받아 Red-Black Tree를 ID를 이용하여 탐색한 후 존재하면 입력 받은 정보를 업데이트하고, 해당 node의 depth를 출력합니다. 만약 존재하지 않으면 “NULL”을 출력합니다.<br>
#	[할인] 범위 x와 y, 할인율 P를 입력 받아 [x, y] 범위 내의 ID를 가진 애플리케이션을 모두 탐색하여 각 애플리케이션의 가격에 P%의 할인율을 적용합니다.<br>
<br><br>
<h3>3)	개발 환경</h3>
#	Microsoft Visual Studio 2017 (C++)
<br><br>

<h2>2.	필요한 자료구조 및 기능</h2>
<h3>1)	필요한 자료구조</h3>
<img width = "30%" src="https://user-images.githubusercontent.com/60337066/141210811-82225e03-bd4f-425a-932a-6aa81a11f755.png">
#	<string> 라이브러리를 사용하여 node의 이름 필드를 string형으로 설정하였습니다.<br>
#	Tree를 구성하는 node 구조체입니다. 각 node들은 포인터(node *parent, node *left, node *right)로 연결되도록 구현하였습니다.<br>
<img width = "50%" src="https://user-images.githubusercontent.com/60337066/141210933-5e37851f-4878-4b7d-aca7-db73f6ce4d66.png">
# Root를 가리키는 포인터를 설정해주었습니다. Leaf node가 NULL값이 아닌 하나의 빈 node이기 때문에 root = new node;로 초기화하였습니다.<br>
<img width = "20%" src = "https://user-images.githubusercontent.com/60337066/141211010-4ba71a0e-43b0-440b-a063-a584b0d7eedf.png">
<img width = "30%" src = "https://user-images.githubusercontent.com/60337066/141211016-a2babb6a-bb5c-4dca-89a6-14bad042af10.png">
<br><br>
 
<h3>2)	기능</h3>
#	검색<br>
- ID를 입력 받아 재귀 함수를 이용하여 이진 탐색을 수행합니다.<br>
- Node가 없다면 “NULL”를 출력합니다.<br>
- Node가 있다면 정보(depth, 이름, 용량, 가격)를 출력합니다.<br><br>
#	등록<br>
- 이진 탐색 함수를 이용하여 입력 받은 ID를 가진 node가 있는지 확인합니다.<br>
- Node가 없다면 입력 받은 정보로 새로운 node를 tree에 삽입하고 해당 node의 depth를 출력합니다.<br>
- 삽입 시 double red를 검사하여 restructuring이나 recoloring을 수행합니다.<br>
- Node가 있다면 삽입하지 않고 해당 node의 depth만 출력합니다.<br><br>
#	업데이트<br>
- 이진 탐색 함수를 이용하여 입력 받은 ID를 가진 node가 있는지 확인합니다.<br>
- Node가 없다면 “NULL”를 출력합니다.<br>
- Node가 있다면 해당 node의 정보를 입력 받은 정보로 갱신합니다.<br><br>
#	할인<br>
- tree 전체를 순회하면서 해당 node의 ID가 입력 받은 범위 [x, y]에 부합한다면 해당 node의 가격을 입력 받은 할인율 P%만큼 할인합니다.<br><br>
<br><br>
  
<h2>3.	인터페이스 및 사용법</h2>
 <h3>1)	사용법</h3>
  
<img width = "35%" src="https://user-images.githubusercontent.com/60337066/141211296-271ae005-aee6-4f45-9707-1b38079f79dd.png">
<h4>
#	먼저 명령어의 개수(ex. 20)를 입력합니다.<br>
# 명령어의 개수를 입력 후 해당 개수만큼 명령어를 입력합니다. 명령어는 명령어 구분 기호 (‘I’, ‘F’, ‘R’, ‘D’) + 입력 인자로 구성되어 있습니다.<br>
#	해당 명령어에 대해 수행하고 출력 값이 있다면 출력됩니다. <br>
# 명령어의 개수만큼 명령어가 수행되면 프로그램이 종료됩니다. <br>
  <br><br></h4>
  
  <h2>4.	평가 및 개선 방향</h2>
  <h3>1)	구현한 알고리즘의 장점</h3>
#	전처리 지시자 #define을 통해 좀 더 코드가 직관적으로 보일 수 있도록 하였습니다. (BLACK, RED, FOUND, NOT_FOUND)<br>
#	이진 탐색 함수 binary_search() 하나로 등록, 검색, 업데이트 세 가지 기능에 모두 범용성 있게 사용할 수 있게끔 구현하였습니다.<br>
#	각각 주요 기능별로 함수를 나눠서 (모듈화) 직관성을 높이고 구현이 쉽도록 하였습니다.<br><br><br>
  <h3>2)	구현한 알고리즘의 단점</h3>
#	Restructure() 함수가 다소 직관적이지 않습니다.<br>
#	할인 기능을 수행하기 위해 traversal() 함수로 tree 순회를 하는 과정에서 id 값이 범위 [x, y]를 벗어나는 node가 있을 때에도 모든 node를 순회해야 합니다.<br><br><br>
  <h3>3)	향후 개선 방향</h3>
#	Restructure() 함수를 좀 더 명확하게 구현하는 방법을 고안해야 할 것 같습니다.<br>
#	Traversal() 함수가 범위 밖을 벗어나는 node들은 순회하지 않도록 하는 방법을 고안해야 할 것 같습니다.<br>

  


