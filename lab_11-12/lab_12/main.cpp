#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MultiIterator {
private:
    vector<string>& first;   
    vector<string>& second;  
    int index;               

public:
    MultiIterator(vector<string>& a, vector<string>& b) : first(a), second(b) {
        index = 0;
    }

    bool hasNext() {
        return index < first.size() + second.size();
    }

    string next() {
        string result;

        if (index < first.size()) {
            result = first[index];
        } else {
            result = second[index - first.size()];
        }

        index++;
        return result;
    }
};

int main() {
    vector<string> emails;
    vector<string> phones;

    int n, m;

    cout << "Сколько email-адресов? ";
    cin >> n;

    cout << "Введите email-адреса:\n";
    for (int i = 0; i < n; i++) {
        string email;
        cin >> email;
        emails.push_back(email);
    }

    cout << "Сколько телефонных номеров? ";
    cin >> m;

    cout << "Введите номера телефонов:\n";
    for (int i = 0; i < m; i++) {
        string phone;
        cin >> phone;
        phones.push_back(phone);
    }

    MultiIterator it(emails, phones);

    cout << "\nВсе элементы по очереди:\n";
    while (it.hasNext()) {
        cout << it.next() << endl;
    }

    return 0;
}