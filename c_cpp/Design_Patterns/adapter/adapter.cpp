/* TODO:  <02-06-21, zw> */
#include <iostream>
#include <string>
#include <vector>

typedef int Voltage;
struct hello {
  int a;
  int b;
};
int ss;
void a();
class Voltage220v {
public:
  Voltage220v() : vtg(220){};
  virtual ~Voltage220v() {}
  virtual Voltage output220v() { return vtg; }

private:
  Voltage vtg;
};

class Voltage5v {
public:
  Voltage5v() : vtg(5) {}
  virtual ~Voltage5v() {}

private:
  Voltage vtg;
};
class phone {
public:
  void charging(Voltage input) {
    if (input == 5) {
      std::cout << "Charging start: ~~~" << std::endl;
    } else {
      std::cout << "Voltage error, please change" << std::endl;
    }
  }

private:
  /* data */
};
class adapter : public Voltage220v {
public:
  adapter() : pv5(new Voltage5v) {}
  Voltage output220v() override {
    std::cout << "Adapter: start adapter" << std::endl;
    return 5;
  }
  virtual ~adapter() { delete pv5; }

private:
  Voltage5v *pv5;
};
int main() {
  phone myIphone;
  Voltage220v *pv220 = new adapter();
  myIphone.charging(pv220->output220v());

  return 0;
}
