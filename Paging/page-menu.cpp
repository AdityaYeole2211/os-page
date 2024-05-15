#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// Function prototypes
void fcfs(int pages[], int n, int capacity);
void leastRecentlyUsed(int pages[], int n, int capacity);
void optimalPageReplacement(int pages[], int n, int capacity);

int main() {
    int choice;
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(int);
    int capacity = 4;

    cout << "Select a page replacement algorithm:" << endl;
    cout << "1. First Come First Serve" << endl;
    cout << "2. Least Recently Used" << endl;
    cout << "3. Optimal Page Replacement" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            fcfs(pages, n, capacity);
            break;
        case 2:
            leastRecentlyUsed(pages, n, capacity);
            break;
        case 3:
            optimalPageReplacement(pages, n, capacity);
            break;
        default:
            cout << "Invalid choice. Exiting..." << endl;
            break;
    }

    return 0;
}

void fcfs(int pages[], int n, int capacity) {
    unordered_set<int> s;
    queue<int> indexes;
    int hits = 0;
    int misses = 0;

    for (int i = 0; i < n; i++) {
        if (s.find(pages[i]) == s.end()) {
            if (s.size() < capacity) {
                s.insert(pages[i]);
                indexes.push(pages[i]);
                misses++;
            } else {
                int val = indexes.front();
                indexes.pop();
                s.erase(val);
                s.insert(pages[i]);
                indexes.push(pages[i]);
                misses++;
            }
        } else {
            hits++;
        }
    }

    cout << "No of hits: " << hits << endl;
    cout << "No of misses (page faults): " << misses << endl;
}

void leastRecentlyUsed(int pages[], int n, int capacity) {
    unordered_set<int> s;
    unordered_map<int, int> indexes;
    int hits = 0, misses = 0;

    for (int i = 0; i < n; i++) {
        if (s.find(pages[i]) == s.end()) {
            if (s.size() < capacity) {
                s.insert(pages[i]);
            } else {
                int lru = INT16_MAX, val;
                for (auto it : s) {
                    if (indexes[it] < lru) {
                        lru = indexes[it];
                        val = it;
                    }
                }
                s.erase(val);
                s.insert(pages[i]);
            }
            misses++;
        } else {
            hits++;
        }
        indexes[pages[i]] = i;
    }

    cout << "No of hits: " << hits << endl;
    cout << "No of misses (page faults): " << misses << endl;
}

void optimalPageReplacement(int pages[], int n, int capacity) {
    int frames[capacity];
    fill_n(frames, capacity, -1);
    int hits = 0;
    int misses = 0;

    for (int i = 0; i < n; i++) {
        if (i < capacity) {
            if (find(frames, frames + capacity, pages[i]) == frames + capacity) {
                frames[i] = pages[i];
                misses++;
            } else {
                hits++;
            }
        } else {
            if (find(frames, frames + capacity, pages[i]) == frames + capacity) {
                int farthest = i, replace = 0;
                for (int j = 0; j < capacity; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            if (k > farthest) {
                                farthest = k;
                                replace = j;
                            }
                            break;
                        }
                    }
                    if (k == n) {
                        replace = j;
                        break;
                    }
                }
                frames[replace] = pages[i];
                misses++;
            } else {
                hits++;
            }
        }
    }

    cout << "No of hits: " << hits << endl;
    cout << "No of misses (page faults): " << misses << endl;
}
