// g++ -o mutex_test mutex_test.cpp

#include <iostream>
#include <mutex>  // mutex 를 사용하기 위해 필요
#include <thread>
#include <vector>

void worker(int& result, std::mutex& m) {
  for (int i = 0; i < 10000; i++) {
    m.lock();
    result += 1;
    m.unlock();
  }
}

int main() {
  int counter = 0;
  std::mutex m;  // 우리의 mutex 객체

  std::vector<std::thread> workers;
  for (int i = 0; i < 4; i++) {
    workers.push_back(std::thread(worker, std::ref(counter), std::ref(m)));
  }

  for (int i = 0; i < 4; i++) {
    workers[i].join();
  }

  std::cout << "Counter 최종 값 : " << counter << std::endl;
}
