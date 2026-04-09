#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    cout << "Сколько элементов? ";
    cin >> n;

    vector<string> data;

    for (int i = 0; i < n; i++) {
        string x;
        cin >> x;
        data.push_back(x);
    }

    cout << "Обратный порядок:\n";

    for (auto it = data.rbegin(); it != data.rend(); it++) {
        cout << *it << " ";
    }

    return 0;
}