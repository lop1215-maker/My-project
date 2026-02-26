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

    int size() const {
        return (int)stepNames.size();
    }

    bool empty() const {
        return stepNames.empty();
    }

    void clear() {
        stepNames.clear();
        stepFunctions.clear();
    }
    
    template <class F>
void addStep(const std::string& name, F func) {
    if (name.empty()) {
        throw std::invalid_argument("step name is empty");
    }

    stepNames.push_back(name);
    stepFunctions.push_back(func);
}

void removeStep(int index) {
    if (index < 0 || index >= size()) {
        throw std::out_of_range("index out of range");
    }

    stepNames.erase(stepNames.begin() + index);
    stepFunctions.erase(stepFunctions.begin() + index);
}

T run(T value) const {
    for (int i = 0; i < size(); i++) {
        value = stepFunctions[i](value);
    }
    return value;
}

std::vector<T> trace(T value) const {
    std::vector<T> result;

    for (int i = 0; i < size(); i++) {
        value = stepFunctions[i](value);
        result.push_back(value);
    }

    return result;
}

friend std::ostream& operator<<(std::ostream& out, const MyPipeline<T>& pipeline) {
    out << "Steps count: " << pipeline.size() << "\n";

    for (int i = 0; i < pipeline.size(); i++) {
        out << i << ") " << pipeline.stepNames[i] << "\n";
    }

    return out;
}

};

int main() {
    return 0;
}