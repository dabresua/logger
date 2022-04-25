#include <iostream>
#include <sstream>
#include <logger.h>

using namespace std;

void send(string str)
{
  cout << "[" << str[0] << "]: " << str.substr(1) << endl;
}

int main()
{  
  {
    LOG(logger::WARNING, send) << "hello";
  }

  return 0;
}