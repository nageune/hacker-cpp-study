# Day 1 - 2022.10.04.

### 1. 메모리 동적 할당

#### 1.1 new와 delete 연산자
- `new`와 `delete`는 C++에서 객체를 동적 할당하고 해제하는 연산자.
- `new` 연산자는 객체의 생성자를 호출하고, `delete` 연산자는 객체의 소멸자를 호출한다.
\n
- `형식 *변수이름 = new 형식;`
- `delete 변수이름;`
```c++
#include <iostream>
using namespace std;

int main() {
  // 인스턴스만 동적으로 생성하는 경우
  int *pData = new int;

  // 초기값을 기술하는 경우
  int *pNewData = new int(10);

  *pData = 5;
  cout << *pData << endl; // 5
  cout << *pNewData << endl; // 10

  delete pData;
  delete pNewData;
  return 0;
}
```
- 배열 형태로 동적 생성한 것은 반드시 배열 형태를 통해 삭제
- `형식 *변수이름 = new 형식[요소개수];`
- `delete[] 변수이름;`
```c++
#include <iostream>
using namespace std;

int main() {
  // 객체를 배열 형태로 동적 생성한다.
  int *arr = new int[5];
  for (int i = 0; i < 5; i++)
    arr[i] = (i + 1) * 10;

  for (int i = 0; i < 5; i++)
    cout << arr[i] << endl;
  
  delete[] arr;
  return 0;
}
```

### 2. 참조자 형식
- `형식 &이름 = 원본;`
- 상수에는 참조자를 선언할 수 없다.
```c++
int *pData = &3; // 불가능
int &rData = 3;  // 상수에 대한 참조는 불가능
int &rData;      // 참조 원본이 없으므로 불가능
```

#### 2.1 참조형 변수 선언과 정의
```c++
#include <iostream>
using namespace std;

int main() {
  int nData = 10;

  // nData 변수에 대한 참조자 선언
  int &ref = nData;

  // 참조자의 값을 변경하면 원본도 변경된다.
  ref = 20;
  cout << nData << endl; // 20

  // 포인터를 쓰는 것과 비슷하다.
  int *pnData = &nData;
  *pnData = 30;
  cout << nData << endl; // 30

  return 0;
}
```
- 덩치 큰 자료는 값이 아니라 '주소'를 전달하는 것이 효율적이다!

```c++
#include <iostream>
using namespace std;

// 매개변수가 int에 대한 참조 형식이다.
void TestFunc(int &rParam) {
  // 피호출자 함수에서 원본의 값을 변경한다.
  rParam = 100;
}

int main() {
  int nData = 0;
  TestFunc(nData);
  cout << nData << endl; // 100

  return 0;
}
```
- 매개변수가 참조자인 경우 가장 큰 문제점은 호출자 코드만 봐서는 매개변수가 참조 형식이라는 사실을 전혀 알 수 없다.

```c++
#include <iostream>
using namespace std;

// 참조 전달이므로 호출자 변수의 값을 변경할 수 있다.
void Swap(int &a, int &b) {
  int nTmp = a;
  a = b;
  b = nTmp;
}

int main() {
  int x = 10, y = 20;

  // 참조 전달이며 두 변수의 값이 교환된다.
  Swap(x, y);

  // 교환된 결과를 출력한다.
  cout << "x: " << x << endl; // x: 20
  cout << "y: " << y << endl; // y: 10

  return 0;
}
```

#### 2.2 r-value 참조
- r-value : 대입 연산자의 두 피연산자 중 오른쪽에 위치한 연산자
- `int &&rdata = 3;`
- 임시 결과는 이어지는 연산에 활용된 직후 소멸하는 r-value
- ex) 3 + 4 + 5 연산에서 3 + 4 연산의 결과를 '임시 결과'라고 한다.

```c++
#include <iostream>
using namespace std;

int TestFunc(int nParam) {
  int nResult = nParam * 2;
  return nResult;
}

int main() {
  int nInput = 0;
  cout << "Input number: ";
  cin >> nInput; // 5

  // 산술 연산으로 만들어진 임시 객체에 대한 r-value 참조
  int &&rdata = nInput + 5;
  cout << rdata << endl;  // 10

  // 함수 반환으로 만들어진 임시 객체에 대한 r-value 참조
  int &&result = TestFunc(10);

  // 값을 변경할 수 있다.
  result += 10;
  cout << result << endl; // 30

  return 0;
}
```

### 3. 범위 기반 for문
- `for (auto 요소변수 : 배열이름)`
- 반복 횟수는 배열 요소 개수에 맞춰 자동으로 결정

```c++
#include <iostream>
using namespace std;

int main() {
  int aList[5] = {10, 20, 30, 40, 50};

  // 전형적인 C 스타일 반복문
  for (int i = 0; i < 5; i++)
    cout << aList[i] << ' '; // 10 20 30 40 50

  cout << endl;

  // 범위 기반 C++11 스타일 반복문
  // 각 요소의 값을 n에 복사한다.
  for (auto n : aList)
    cout << n << ' '; // 10 20 30 40 50

  cout << endl;

  // n은 각 요소에 대한 참조다.
  for (auto &n : aList)
    cout << n << ' '; // 10 20 30 40 50

  cout << endl;

  return 0;
}
```
- 기존 for문에서 배열 요소의 개수가 5개에서 10개로 변경된다면 조건식은 반드시 수정해야함.
- 범위 기반 for문에서는 그럴 필요가 없음