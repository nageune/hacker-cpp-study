#include <iostream>
using namespace std;

class String {
private:
  char *str;
  int len;

public:
  String() {
    str = nullptr;
    len = 0;
  }

  String(const String &org) {
    this->len = org.len;
    str = new char[this->len];
    for (int i = 0; i < this->len; i++)
      str[i] = org.str[i];
  }

  ~String() {
    delete[] str;
  }

  int length() {
    return this->len;
  }

  void print() {
    for (int i = 0; i < len; i++)
      cout << str[i];
    cout << '\n';
  }

  void append(char a) {
    char *temp = str;
    str = new char[len + 1];
    for (int i = 0; i < len; i++)
      str[i] = temp[i];
    str[len] = a;
    delete[] temp;
    len++;
  }

  void operator=(String a) {
    this->len = a.len;
    this->str = new char[this->len];
    for (int i = 0; i < this->len; i++)
      this->str[i] = a.str[i];
  }
};

int main() {
  String a;
  a.append('a');
  a.print();
  a.append('b');
  a.print();
  a.append('c');
  a.print();
  a.append('d');
  a.print();
  a.append('e');
  a.print();
  String b;
  b = a;
  b.print();
  return 0;
}