// #include <array>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

mt19937_64 rngEngine(chrono::steady_clock::now().time_since_epoch().count());
uint64_t genRand(){
    uint64_t res = rngEngine();
    while (res == 0){
         res = rngEngine();
    }
    return res;
}

uint64_t hashVal[1000002];
bool hashGen[1000002];
vector<int> touchedHash;
int lastPosArr[1000002];
bool lastPosGen[1000002];
vector<int> touchedLast;
unordered_map<int, uint64_t> umapHash;
unordered_map<int, int> umapLast;

uint64_t getHash(int x){
    if (x >= 0 && x < 1000002){
        if (!hashGen[x]){
            hashVal[x] = genRand();
            hashGen[x] = true;
            touchedHash.push_back(x);
        }
        return hashVal[x];
    }
    if (umapHash.find(x) == umapHash.end()){
        umapHash[x] = genRand();
    }
    return umapHash[x];
}

int getLastPos(int x){
    if (x >= 0 && x < 1000002){
        if (!lastPosGen[x]){
            return -1;
        }
        return lastPosArr[x];
    }
    if (umapLast.find(x) == umapLast.end()){
        return -1;
    }
    return umapLast[x];
}

void setLastPos(int x, int pos){
    if (x >= 0 && x < 1000002){
        if (!lastPosGen[x]){
            touchedLast.push_back(x);
            lastPosGen[x] = true;
        }
        lastPosArr[x] = pos;
    } else{
        umapLast[x] = pos;
    }
}

void cleanupData(){
    for (int x : touchedHash){
        hashGen[x] = false;
    }
    touchedHash.clear();    
    for (int x : touchedLast){
        lastPosGen[x] = false;
    }
    touchedLast.clear();    
    umapHash.clear();
    umapLast.clear();
}

const int blockSize = 512;
struct Block{
    int leftid, rightid;
    uint64_t lazyXor;
    uint64_t arr[blockSize];
    uint64_t sortedArr[blockSize];    
    void buildBlock(){
        int len = rightid - leftid + 1;
        for(int i{0}; i < len; ++i){
            sortedArr[i] = arr[i];
        }
        sort(sortedArr, sortedArr + len);
    }    
    void pushLazy(){
        if (lazyXor){
            int len = rightid - leftid + 1;
            for(int i{0}; i < len; ++i){
                arr[i] ^= lazyXor;
            }
            lazyXor = 0;
        }
    }
    
    void updateRange(int qL, int qR, uint64_t xorVal){
        if (qL <= leftid && rightid <= qR){
            lazyXor ^= xorVal;
            return;
        }
        int st = max(leftid, qL) - leftid;
        int en = min(rightid, qR) - leftid;
        if (st <= en){
            pushLazy();
            for(int i = st; i <= en; ++i){
                arr[i] ^= xorVal;
            }
            buildBlock();
        }
    }
    
    int queryCount(uint64_t val){
        uint64_t target = val ^ lazyXor;
        int len = rightid - leftid + 1;
        auto [it1, it2] = equal_range(sortedArr, sortedArr + len, target);
        return it2 - it1;
    }
};

Block blocks[405];
int totalSz{0};

void appendValue(uint64_t val){
    int b = totalSz >> 9;
    int id = totalSz & 511;    
    if (id == 0){
        blocks[b].leftid = totalSz;
        blocks[b].rightid = totalSz;
        blocks[b].lazyXor = 0;
        blocks[b].arr[0] = val;
        blocks[b].sortedArr[0] = val;
    } else{
        if (blocks[b].lazyXor){
            blocks[b].pushLazy();
            blocks[b].rightid = totalSz;
            blocks[b].arr[id] = val;
            blocks[b].buildBlock();
        } else{
            blocks[b].rightid = totalSz;
            blocks[b].arr[id] = val;
            int i = id - 1;
            while (i >= 0 && blocks[b].sortedArr[i] > val){
                blocks[b].sortedArr[i + 1] = blocks[b].sortedArr[i];
                i--;
            }
            blocks[b].sortedArr[i + 1] = val;
        }
    }
    totalSz++;
}

void updateGlobalRange(int qL, int qR, uint64_t xorVal){
    if (qL > qR){
        return;
    }
    int bStart = qL >> 9;
    int bEnd = qR >> 9;
    for (int b = bStart; b <= bEnd; ++b){
        blocks[b].updateRange(qL, qR, xorVal);
    }
}

int queryGlobalAll(uint64_t val){
    int res{0};
    int numBlocks = (totalSz + blockSize - 1) >> 9;
    for (int b{0}; b < numBlocks; ++b){
        res += blocks[b].queryCount(val);
    }
    return res;
}

template<std::size_t S>
ll solve(std::array<int, S> input){
    int n = input.size();
    if (n == 0){
        return 0;
    }
    cleanupData();
    totalSz = 0;    
    vector<uint64_t> prefixXor(n + 1, 0);
    ll res{0};    
    for (int i = 1; i <= n; ++i){
        int val = input[i - 1];
        uint64_t h = getHash(val);
        prefixXor[i] = prefixXor[i - 1] ^ h;        
        appendValue(prefixXor[i - 1]);
        int prevPos = getLastPos(val);
        updateGlobalRange(prevPos + 1, i - 1, h);        
        res += queryGlobalAll(prefixXor[i]);        
        setLastPos(val, i - 1); 
    }    
    return res;
}