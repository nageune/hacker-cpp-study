#include <iostream>
using namespace std;

class String {
private:
  char *str;
  int len, maxSize;

public:
  String() {
    str = new char[100];
    len = 0;
    maxSize = 100;
  }

  String(int max) {
    str = new char[max];
    len = 0;
    maxSize = max;
  }

  ~String() {
    delete[] str;
  }

  int length() {
    return len;
  }

  void append(char x) {
    if (len < maxSize) {
      str[len] = x;
      len++;
    }
  }

  bool find(char x) {
    for (int i = 0; i < len; i++) {
      if (str[i] == x) {
        return true;
      }
    }
    return false;
  }

  void replace(char x, char c) {
    for (int i = 0; i < len; i++)
      if (str[i] == x)
        str[i] = c;
  }

  void makeEmpty() {
    // Sol 1
    // len = 0;

    // Sol 2
    for (int i = 0; i < len; i++)
      str[i] = '\0';
    len = 0;
  }

  void print() {
    for (int i = 0; i < len; i++)
      cout << str[i];
  }

  String operator+(String &s) {
    String result;
    for (int i = 0; i < this->length(); i++)
      result.append(this->str[i]);
    for (int i = 0; i < s.length(); i++)
      result.append(s.str[i]);
    return result;
  }
};

int main() {
  String str1(3);
  str1.append('a');
  str1.append('b');
  str1.append('c');
  String str2(5);
  str2.append('a');
  str2.append('b');
  str2.append('c');
  str2.append('d');
  str2.append('e');
  str1.print();
  cout << '\n';
  str2.print();
  cout << '\n';
  String str3;
  str3 = str1 + str2;
  str3.print();
  return 0;
}