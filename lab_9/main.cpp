#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct GroupInfo{
    int key;
    int count;
    int minElem;
    int maxElem;
    double sum;
    double avg;
};

template<typename T1, typename TKey, typename TValue>
vector<GroupInfo> groupStats(T1 arr[], int n,
                             TKey (*keyFunc)(T1),
                             TValue (*valueFunc)(T1)){
    vector<GroupInfo> groups;

    for (int i = 0; i < n; i++)(
        T1 elem = arr[i];
        TKey key = keyFunc(elem);
        TValue value = valueFunc(elem);
    )

    return groups;
}

int main(){
    return 0;
}
                             