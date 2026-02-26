#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>

template <class T>
class MyPipeline {
private:
    std::vector<std::string> stepNames;
    std::vector<std::function<T(T)>> stepFunctions;

public:
    MyPipeline() {}
};

int main() {
    return 0;
}