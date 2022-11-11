# Day 4 - 2022.11.01.

## 1. 재귀함수
- 자기 자신을 반복해서 호출하는 함수
- 팩토리얼, 피보나치 수열, 하노이의 탑이 잘 알려진 예시

```c++
// 팩토리얼
#include <iostream>
#include <cmath>
using namespace std;

int factorial(int n) {
  if (n == 1)
    return 1;
  else
    return n * factorial(n-1);
}

int main() {
  int n;
  cin >> n;
  cout << factorial(n) << '\n';
  return 0;
}
```

```c++
// 피보나치 수열
#include <iostream>
using namespace std;

void fibonacci(int n) {
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  int n;
  cin >> n;
  cout << fibonacci(n) << '\n';
  return 0;
}
```

```c++
// 하노이의 탑
#include <iostream>
#include <cmath>
using namespace std;

void hanoi(int n, int from, int by, int to) {
  if (n == 1) {
    cout << from << ' ' << to << '\n';
  } else {
    hanoi(n - 1, from, to, by);
    cout << from << ' ' << to << '\n';
    hanoi(n - 1, by, from, to);
  }
}

int main() {
  int n;
  cin >> n;
  int cnt = pow(2, n) - 1;
  cout << cnt << '\n';
  hanoi(n, 1, 2, 3);
  return 0;
}
```