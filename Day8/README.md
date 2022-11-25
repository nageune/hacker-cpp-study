# Day 8 - 2022.11.25.

## 1. 스택(Stack)의 이해
- 프링글스 과자 통 같은 개념
- 먼저 들어간 것이 나중에 나오는 구조
- `후입선출` 또는 `LIFO(Last-In, First-Out)` 구조의 자료구조
- `push`와 `pop`을 이용함

## 2. 예제
### 예제1
후위 표기식을 입력받고 계산 결과를 출력하는 프로그램
#### 문제
백준 [1935번 문제](https://www.acmicpc.net/problem/1935)
#### 풀이
```c++
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

int main() {
  int n;
  string str;
  cin >> n >> str;
  vector<int> num(n);
  stack<double> s;
  for (int i = 0; i < n; i++)
    cin >> num[i];
  for (char c : str) {
    
    if (c == '+') {
      double a = s.top();
      s.pop();
      double b = s.top();
      s.pop();
      s.push(a + b);
    } else if (c == '-') {
      double a = s.top();
      s.pop();
      double b = s.top();
      s.pop();
      s.push(b - a);
    } else if (c == '*') {
      double a = s.top();
      s.pop();
      double b = s.top();
      s.pop();
      s.push(a * b);
    } else if (c == '/') {
      double a = s.top();
      s.pop();
      double b = s.top();
      s.pop();
      s.push(b / a);
    } else {
      s.push(num[(int)c - 65]);
    }
  }
  cout.precision(2);
  cout << fixed << s.top();
  return 0;
}
```

### 예제2
중위 표기식을 입력받고 후위 표기식으로 변환하여 출력하는 프로그램
#### 문제
백준 [1918번 문제](https://www.acmicpc.net/problem/1918)
#### 풀이
```c++
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int getPriority(char c) {
  switch (c) {
  case '*':
  case '/':
    return 3;
  case '+':
  case '-':
    return 2;
  case '(':
    return 1;
  default:
    return -1;
  }
}

int main() {
  string str, ans = "";
  cin >> str;
  stack<char> s;
  for (char c : str) {
    switch (c) {
    case '(':
      s.push(c);
      break;
    case ')':
      while (1) {
        if (s.top() == '(') {
          s.pop();
          break;
        }
        ans += s.top();
        s.pop();
      }
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      while (!s.empty() && getPriority(c) <= getPriority(s.top())) {
        ans += s.top();
        s.pop();
      }
      s.push(c);
      break;
    default:
      ans += c;
      break;
    }
  }
  while (!s.empty()) {
    ans += s.top();
    s.pop();
  }
  cout << ans << '\n';
  return 0;
}
```