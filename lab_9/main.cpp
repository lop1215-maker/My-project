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

int lastDigit(int x){
    return x % 10;
}

int valueInt(int x){
    return x;
}

int getInterval(double x){
    if (x < 0) return 0;
    if (x <= 10) return 1;
    return 2;
}

double valueDouble(double x){
    return x;
}

char firstLetter(string s){
    return s[0];
}

int strLength(string s){
    return (int)s.length();
}



int main(){
    cout << "=== int ===" << endl;
    int arr1[] = {15, 23, 25, 47, 52, 38, 61};
    int n1 = 7;
    
    auto res1 = groupStats(arr1, n1, lastDigit, valueInt);
    for (auto g : res1){
        cout << g.key << ", " << g.count << ",  "
        << g.minElem << ", " << g.maxElem << ", "
        << g.sum << ", " << g.avg << endl;
    }

    cout << "\n=== double ===" << endl;
    double arr2[] = {-5, 3, 12, 0, 8, 15, -2};
    int n2 = 7;

    auto res2 = groupStats(arr2, n2, getInterval, valueDouble);
    for (auto g : res2){
        cout << g.key << ", " << g.count << ", "
        << g.minElem << ", " << g.maxElem << ", "
        << g.sum << ", " << g.avg << endl;
    }

    return 0;
}
                             