#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

void leastRecentlyUsed(int pages[], int n , int capacity){
    unordered_set<int> s;
    unordered_map<int, int> indexes;
    int hits= 0, misses = 0;
    for(int i = 0; i< n; i++){
        if(s.find(pages[i]) == s.end()){
            //page is not in memory 
            //check if capacity is full
            if(s.size() < capacity){
                //insert in set
                s.insert(pages[i]);
              
            }
            else{
                //page has to be replaced
                int lru = INT16_MAX;
                int val ;
                for(auto it : s){
                    if(indexes[it] < lru){
                        lru = indexes[it];
                        val = it;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
            }
            misses++;
           
        }
        else {
            hits++;
        }
        indexes[pages[i]] = i;
    }
    cout<<"no of hits: "<<hits<<endl;
    cout<<"no of misses: "<<misses<<endl;

}
int main(){
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages)/sizeof(int);
    int capacity = 4;
    leastRecentlyUsed(pages, n , capacity);
    
}