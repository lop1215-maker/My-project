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

    for (int i = 0; i < n; i++){
        T1 elem = arr[i];
        TKey key = keyFunc(elem);
        TValue value = valueFunc(elem);
        
        int groupIndex = -1;
        for (int j = 0; j < groups.size(); j++){
            if (groups[j].key == key){
                groupIndex = j;
                break;
            }
        }

        if (groupIndex == -1){
            GroupInfo g;
            g.key = key;
            g.count = 1;
            g.minElem = elem;
            g.maxElem = elem;
            g.sum = value;
            g.avg = value;
            groups.push_back(g);
        }
        else{
            groups[groupIndex].count++;

            if (elem < groups[groupIndex].minElem){
                groups[groupIndex].minElem = elem;
            }
            if (groups[groupIndex].maxElem < elem){
                groups[groupIndex].maxElem = elem;
            }

            groups[groupIndex].sum += value;
            groups[groupIndex].avg = 
                groups[groupIndex].sum / groups[groupIndex].count;
        }

    }

    return groups;
}

int main(){
    return 0;
}
                             