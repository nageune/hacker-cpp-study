# Day 2 - 2022.10.07.

### 1. 디폴트 매개변수
#### 1.1 디폴트 매개변수 사용
```c++
#include <iostream>
using namespace std;

int TestFunc(int nParam = 10) {
  return nParam;
}

int main() {
  // 호출자가 실인수를 기술하지 않았으므로 디폴트 값을 적용한다.
  cout << TestFunc() << endl; // 10

  // 호출자가 실인수를 확정했으므로 디폴트 값을 무시한다.
  cout << TestFunc(20) << endl; // 20
  
  return 0;
}
```
- `nParam` 매개변수의 초깃값이 10임을 알 수 있다.
- `변환자료형 함수이름(매개변수자료형이름 = 디폴트값);`
- 매개변수의 디폴트 값을 '선언'한 함수는 호출자 코드에서 실인수를 생략한 채 호출
```c++
#include <iostream>
using namespace std;

int TestFunc(int = 10);

int TestFunc(int nParam) {
  return nParam;
}

int main() {
  cout << TestFunc(20) << endl;

  return 0;
}
```
- 매개변수의 이름을 기술하지 않아도 문법적으로 문제 없음
- 함수 원형 선언에서 매개변수의 이름 생략할 수 있기 때문
```c++
cout << TestFunc(10) << endl;
cout << TestFunc() << endl;
```
- 위 두 코드는 사실상 같은 코드
- "호출자의 코드만 봐선 함수 원형이 뭔지 알 수가 없다!"
- 절대 호출자의 코드만 보고 원형을 확정하면 안됨.

#### 1.2 매개변수가 두 개일 때의 디폴트 값
```c++
#include <iostream>
using namespace std;

int TestFunc(int nParam1, int nParam2 = 2) {
  return nParam1 * nParam2;
}

int main() {
  cout << TestFunc(10) << endl; // 20
  cout << TestFunc(10, 5) << endl; // 50
  
  return 0;
}
```
디폴트 매개변수 선언 주의사항
1. 피호출자 함수 **매개변수와 디폴트 값은 반드시 오른쪽 매개변수부터 기술**해야 한다.
2. 매개변수가 여러 개일 때 왼쪽 첫 번째 매개변수의 디폴트 값을 기술하려면 나머지 오른쪽 '모든' 매개변수에 대한 디폴트 값을 기술해야 한다. **절대로 중간에 빼먹으면 안된다,**
3. 호출자 함수가 피호출자 함수 매개변수의 실인수를 기술하면 이는 왼쪽부터 짝을 맞추어 적용되며, 짝이 맞지  않는 매개변수는 디폴트 값을 적용한다.

#### 1.3 잘못된 예
1. **디폴트 값이 없는 매개변수에는 호출자 함수에 반드시 실인수를 기술**해야 하는데 이를 지키지 않아 발생하는 오류
  ```c++
  int TestFunc(int nParam1, int nParam2 = 2)
  ...
    cout << TestFunc() << endl;
    // error C2660: 'TestFunc' : 함수는 0개의 매개변수를 사용하지 않습니다.
  ```
2. **디폴트 값을 오른쪽 매개변수부터 기술**해야 하는데 이를 지키지 않아 발생하는 오류
  ```c++
  int TestFunc(int nParam1 = 5, int nParam2)
  ...
    cout << TestFunc(10) << endl;
    // error C2548: 'TestFunc' : 매개변수 2에 대한 기본 매개변수가 없습니다.
    // error C2660: 'TestFunc' : 함수는 1개의 매개변수를 사용하지 않습니다.
  ```
3. **중간에 위치한 매개변수에 디폴트 값을 생략할 수 없는데** 이를 지키지 않아 발생하는 오류
   ```c++
  int TestFunc(int nParam1 = 5, int nParam2, int nParam3 = 10)
  ``` 

### 2. 함수 다중 정의
#### 2.1 다중 정의 일반
```c++
// Add() 함수의 다중 정의
#include <iostream>
using namespace std;

int Add(int a, int b, int c) {
  cout << "Add(int, int, int): ";

  return a + b + c;
}

int Add(int a, int b) {
  cout << "Add(int, int): ";

  return a + b;
}

double Add(double a, double b) {
  cout << "Add(double, double): ";

  return a + b;
}

int main() {
  cout << Add(3, 4) << endl;
  cout << Add(3, 4, 5) << endl;
  cout << Add(3.3, 4.4) << endl;

  return 0;
}

/*
result>
Add(int, int): 7
Add(int, int, int): 12
Add(double, double): 7.7
*/
```
- **'더하기'라는 한 가지 개념을 여러 가지 형태로 다양하게 구현**할 수 있다.
- `반환형식 호출규칙 함수이름(매개변수, 매개변수, ...);`
- 함수의 다중 정의에 영향을 주는 것은 '매개변수'뿐

1. 반환 형식만 다른 경우
  ```c++
  // 반환 형식만 다르다.
  int Add(int a, int b);
  double Add(int a, int b);
  ```

2. 호출 규칙만 다른 경우
  ```c++
  // 호출 규칙만 다르다.
  int _cdec1 Add(int a, int b);
  int _stdcall Add(int a, int b);
  ```

#### 2.2 다중 정의와 모호성
```c++
// 디폴트 매개변수와 다중 정의가 조합되었을 때의 모호성
#include <iostream>
using namespace std;

void TestFunc(int a) {
  cout << "TestFunc(int)" << endl;
}

void TestFunc(int a, int b = 10) {
  cout << "TestFunc(int, int)" << endl;
}

int main() {
  TestFunc(5);

  return 0;
}

// error C2668: 'TestFunc' : 오버로드된 함수에 대한 호출이 모호합니다.
// 'void TestFunc(int, int)'일 수 있습니다.
// 또는 'void TestFunc(int)'
```

#### 2.3 함수 템플릿
- **가급적 함수 다중 정의보다는 '함수 템플릿'**을 사용
  ```c++
  template <typename T>
  반환형식 함수이름(매개변수) {

  }
  ```

```c++
// 템플릿 함수
#include <iostream>
using namespace std;

template <typename T>
T TestFunc(T a) {
  cout << "매개변수 a: "<< a << endl;
  return a;
}

int main() {
  cout << "int\t" << TestFunc(3) << endl;
  cout << "double\t" << TestFunc(3.3) << endl;
  cout << "char\t" << TestFunc('A') << endl;
  cout << "char*\t" << TestFunc("TestString") << endl;
  return 0;
}

/*
result>
매개변수 a: 3
int     3
매개변수 a: 3.3
double     3.3
매개변수 a: A
char     A
매개변수 a: TestString
char*     TestString
*/
```

```c++
// 함수 템플릿으로 만든 Add() 함수
#include <iostream>
using namespace std;

template <typename T>
T Add(T a, T b) {
  return a + b;
}

int main() {
  cout << Add(3, 4) << endl; // Add<int>(3, 4) 로 변경 가능
  cout << Add(3.3, 4.4) << endl;
  return 0;
}
```
- 같은 일을 하는 코드가 여러 번 등장할 필요가 없어졌기 때문에 안정적인 구조

### 3. 인라인 함수
- 함수 호출 -> 스택 메모리 사용 증가, 매개변수로 인해 메모리 복사 발생 & 제어 흐름 이동
- 매크로 -> 관리상의 목적. 본질은 함수가 아니므로 오류 발생시키기도 함. 매개변수 형식 지정 할 수 없음
- 함수와 매크로의 장점만 한 군데 모아놓은 것

```c++
// 인라인 함수
#include <cstdio>

#define ADD(a, b)((a) + (b))

int Add(int a, int b) {
  return a + b;
}

inline int AddNew(int a, int b) {
  return a + b;
}

int main() {
  int a, b;
  scanf_s("%d%d", &a, &b);

  printf("ADD(): %d", ADD(a, b));
  printf("Add(): %d", Add(a, b));
  printf("AddNew(): %d", AddNew(a, b));

  return 0;

  /*
  result>
  3 4
  ADD(): 7
  Add(): 7
  AddNew(): 7
  */
}
```
- inline 함수는 문법적으로도 완벽한 함수
- 코드의 길이가 일정 수준 이상 길어지면 인라인 함수가 되는 것은 바람직하지 않음

### 4. 네임스페이스
- C++가 지원하는 각종 요소들(변수, 함수, 클래스 등)을 한 범주로 묶어주기 위한 문법

#### 4.1 네임스페이스
```c++
namespace 이름 {
  // 네임스페이스의 시작
  ...
  // 네임스페이스의 끝
}
```
```c++
// 네임스페이스 선언 및 정의
#include <iostream>
using namespace std;

namespace TEST {
  int g_nData = 100;
  
  void TestFunc() {
    cout << "Test::TestFunc()" << endl;
  }
}

int main() {
  Test::TestFunc();
  cout << Test::g_nData << endl;
  return 0;
}

/*
result>
TEST::TestFunc()
100
*/
```
- `g_nData` 변수와 `TestFunc()` 함수는 모두 `TEST`라는 네임스페이스에 속함

#### 4.2 using 선언
- 문법에 따라 생략할 때 사용하는 예약어 `using`
  
```c++
// 네임스페이스 선언 및 정의
#include <iostream>
// std 네임스페이스를 using 예약어로 선언한다.
using namespace std;

namespace TEST {
  int g_nData = 100;
  
  void TestFunc() {
    cout << "Test::TestFunc()" << endl;
  }
}

// TEST 네임스페이스에 using 선언을 한다.
using namespace TEST;

int main() {
  // TestFunc()이나 g_nData에도 범위 지정을 할 필요가 없다.
  TestFunc();
  cout << g_nData << endl;
  return 0;
}

/*
result>
TEST::TestFunc()
100
*/
```

#### 4.3 네임스페이스의 중첩
- 예시) 서울시::강남구::대치동::XXX로::XX길
- 네임스페이스 안에 또 다른 네임스페이스가 속할 수 있다.
```c++
// 네임스페이스의 중첩
#include <iostream>
using namespace std;

namespace TEST {
  int g_nData = 100;

  namespace DEV {
    int g_nData = 200;

    namespace WIN {
      int g_nData = 300;
    }
  }
}

int main() {
  cout << TEST::g_nData << endl;
  cout << TEST::DEV::g_nData << endl;
  cout << TEST::DEV::WIN::g_nData << endl;
  
  return 0;
}

/*
result>
100
200
300
*/
```

#### 4.4 네임스페이스와 다중 정의
```c++
// 네임스페이스를 포함한 다중 정의
#include <iostream>
using namespace std;

// 전역(개념상 무소속)
void TestFunc() {
  cout << "::TestFunc()" << endl;
}

namespace TEST {
  // TEST 네임스페이스 소속
  void TestFunc() {
    cout << "Test::TestFunc()" << endl;
  }
}

namespace MYDATA {
  // MYDATA 네임스페이스 소속
  void TestFunc() {
    cout << "DATA::TestFunc()" << endl;
  }
}

int main() {
  TestFunc(); // 묵시적 전역
  ::TestFunc(); // 명시적 전역
  TEST::TestFunc(); // 명시적 전역
  MYDATA::TestFunc(); // 명시적 전역
  
  return 0;
}

/*
result>
::TestFunc()
::TestFunc()
TEST::TestFunc()
DATA::TestFunc()
*/
```
- 모든 네임스페이스에 `void TestFunc()` 함수가 존재하므로 호출자는 **네임스페이스를 기술함으로써 각각을 구별**해 호출해야 한다.

### 5. 식별자 검색 순서
- '식별자가 선언된 위치를 검색하는 순서'

- **전역함수인 경우**
  1. 현재 블록 범위
  2. 현재 블록 범위를 포함하고 있는 상위 블록 범위(최대 적용 범위는 함수 몸체까지)
  3. 가장 최근에 선언된 전역 변수나 함수
  4. using 선언된 네임스페이스 혹은 전역 네임스페이스. 단, 두 곳에 동일한 식별자가 존재할 경우 컴파일 오류 발생!

- **클래스 메서드인 경우**
  1. 현재 블록 범위
  2. 현재 블록 범위를 포함하고 있는 상위 블록 범위(최대 적용 범위는 함수 몸체까지)
  3. 클래스의 멤버
  4. 부모 클래스의 멤버
  5. 가장 최근에 선언된 전역 변수나 함수
  6. 호출자 코드가 속한 네임스페이스의 상위 네임스페이스
  7. using 선언된 네임스페이스 혹은 전역 네임스페이스. 단, 두 곳에 동일한 식별자가 존재할 경우 컴파일 오류 발생
   

#### 5.1 현재 블록 범위
```c++
// 식별자에 접근하는 코드가 속한 블록 범위
#include <iostream>
using namespace std;

int nData(20);

int main() {
  int nData(10);

  cout << nData << endl;
  cout << argc << endl;
  return 0;
}

/*
result>
10
1
*/
```

#### 5.2 상위 블록 범위
```c++
// 범위 검색의 확장
#include <iostream>
using namespace std;

int main() {
  int nInput = 0;
  cout << "11 이상의 정수를 입력하세요" << endl;
  cin >> nInput;

  if (nInput > 10)
    cout << nInput << endl;
  else
    cout << "Error" << endl;
  
  return 0;
}

/*
result>
11 이상의 정수를 입력하세요
13
13
*/
```

#### 5.3 가장 최근에 선언된 전역 변수
- 전역 변수는 네임스페이스보다 선언 위치가 더 우선
```c++
// 네임스페이스와 전역 변수의 검색 우선권
#include <iostream>
using namespace std;

int nData = 200;

namespace TEST {
  int nData = 100;
  void TestFunc() {
    cout << nData << endl;
  }
}

int main() {
  TEST::TestFunc();

  return 0;
}

/*
result>
100
*/
```

```c++
#include <iostream>
using namespace std;

int nData = 200;

namespace TEST {
  void TestFunc() {
    cout << nData << endl;
  }
  int nData = 100;
}

int main() {
  TEST::TestFunc();

  return 0;
}

/*
result>
200
*/
```
- 전역 변수는 네임스페이스를 생각하지 말고 선언  순서를 생각해야 함.

```c++
#include <iostream>
using namespace std;

namespace TEST {
  void TestFunc() {
    cout << nData << endl;
  }
  int nData = 100;
}

int main() {
  TEST::TestFunc();

  return 0;
}
```
- 컴파일 오류가 발생한다.

#### 5.4 using 선언과 전역 변수
```c++
// using namespace 선언을 적용하기 전
#include <iostream>
using namespace std;

int nData = 100;

namespace TEST {
  int nData = 200;
}

int main() {
  cout << nData << endl;

  return 0;
}

/*
result>
100
*/
```

```c++
// TEST 네임스페이스에 using 선언 추가
#include <iostream>
using namespace std;

int nData = 100;

namespace TEST {
  int nData = 200;
}

using namespace TEST;

int main() {
  cout << nData << endl;

  return 0;
}

/*
result>
error C2872: 'nData' : 모호한 기호입니다.
int nData'일 수 있습니다.
int TEST::nData' 일 수 있습니다.
*/
```