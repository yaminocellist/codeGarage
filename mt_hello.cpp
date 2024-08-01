#include <iostream>
#include <thread>
void hi(int id) {
  for(int i =0;i<=10;++i) {
    std::cout<<i<<" hi"<<std::endl;
  }
}
void hi2 (int id) {
  for (int i = 0; i < 10; i++) {
    std::cout << "Thread " << id << ", " << i << ", " << "hi" << std::endl;
  }
}


int main() {
  std::thread a(hi2,1);

  for (int i = 0; i < 8; i++) {
    std::cout << "Main thread: " << i << ", hello" << std::endl;
  }
  a.join();
  return 0;
}