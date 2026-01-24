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

    return groups;
}

int main(){
    return 0;
}
                             