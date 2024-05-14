#include <iostream>
#include <algorithm>
using namespace std;

void optimalPageReplacement(int pages[], int n , int capacity){
    int frames[capacity];
    fill_n(frames,capacity, -1);
    int hits = 0;
    int misses = 0;
    
    for(int i = 0; i < n; i++){
        if(i<capacity){
          if(find(frames, frames + capacity, pages[i]) == frames + capacity ){
            //page is not in mememory - insert
            cout<<"Page "<<frames[i]<<" replaced by "<<pages[i]<<endl;
            frames[i] = pages[i];
            misses++;
            
            cout<<"status of frame: "<<endl;
            for(int i = 0; i < capacity; i++){
                cout<<frames[i]<<" ";
            }
            cout<<endl;
          }
          else {
            hits++;
          }
        }
        else{
            if(find(frames, frames + capacity, pages[i]) == frames+capacity){
                //find page to replace 
                int farthest = i, replace = 0;
                for(int j = 0; j < capacity; j++){
                    int k ;
                    for(k = i+1; k < n; k++){
                        if(frames[j] == pages[k]){
                            if(k>farthest){
                                farthest = k;
                                replace = j;
                            }
                            break;
                        }

                    }
                    if(k==n){
                        //page is not found again in memory ->best to replace 
                        replace = j;
                        break;
                    }
                }
                misses++;
                cout<<"Page "<<frames[replace]<<" replaced by page "<<pages[i]<<endl;
                frames[replace] = pages[i];
                
                cout<<"Status of frame: "<<endl;
                for(int i = 0; i < capacity; i++){
                   cout<<frames[i]<<" ";
                }
                cout<<endl;
            }
            else{
                hits++;
            }

        }

    }
    cout<<"No of hits : "<<hits<<endl;
    cout<<"No of misses(page faults) : "<<misses<<endl;


}
int main(){
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages)/sizeof(int);
    int capacity = 4;
    optimalPageReplacement(pages, n , capacity);

    
}