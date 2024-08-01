#include <iostream>
#include <thread>
void hi(int id) {
  for(int i =0;i<=100;++i);
  std::cout<<id<<" hi"<<std::endl;
}
int main() {
  std::thread a[15];
  for(int i = 0;i<15;++i)
    a[i] = std::thread(hi,i);
  for(int i = 0;i<15;++i)
    a[i].join();
  return 0;
}
