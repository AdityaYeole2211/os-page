#include <iostream>
#include <vector>
#include<algorithm>
#include<queue>
#include<unordered_set>
using namespace std;
void fcfs(int pages[],  int n , int capacity){
    unordered_set<int> s;
    queue<int> indexes;
    int hits = 0;
    int misses = 0;

    for(int i = 0; i < n; i++){
        if(s.find(pages[i]) == s.end()){
            //page is not in memory 
            if(s.size() < capacity){
                s.insert(pages[i]);
                indexes.push(pages[i]);
                misses++;

                cout<<"pages in memory for page " <<pages[i]<<" :  ";
                for(int page : s){
                    cout<<page<<" ";
                }
                cout<<endl;
            }
            else{
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                misses++;
                cout<<"page " << val << "replaced by "<<pages[i]<<endl;
                cout<<"pages in memory for page " <<pages[i]<<" :  ";
                for(int page : s){
                    cout<<page<<" ";
                }
                cout<<endl;

            }
        }
        else{
            //page is already in memory 
            hits++;
            cout<<"pages in memory for page " <<pages[i]<<" :  ";
                for(int page : s){
                    cout<<page<<" ";
                }
                cout<<endl;
            }
    }
    cout<<"No of hits: "<<hits<<endl;
    cout<<"No of misses(fage faults): "<<misses<<endl;
    

}
int main(){
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int capacity = 4 ;
    int n = sizeof(pages)/sizeof(int);
    fcfs(pages,n, capacity);

    
}