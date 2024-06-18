#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <time.h>

using namespace std;

ifstream ifs("qual_random_01.in"); 
ofstream ofs("result.in", ios::app);


int main() {
    clock_t start = clock();
    //ダイクストラ用
    vector<pair<int,int>> G[40009];

    //入力
    int N;
    ifs >> N; // 一辺の頂点数を読み込む

    // マップのサイズに合わせた配列を作成
    int map[2 * N - 1][N] = {0};

    // 与えられたコストをマップに格納
    for (int i = 0; i < 2 * N - 1; ++i) {
        for (int j = 0; j < ((i % 2 == 0) ? N - 1 : N); ++j) {
            ifs >> map[i][j];
            if(i%2 == 0){
                G[j+(i/2)*N].push_back(make_pair(j+((i/2)*N)+1,map[i][j]));
                G[j+((i/2)*N)+1].push_back(make_pair(j+(i/2)*N,map[i][j]));
            }
            if(i%2 == 1){
                G[j+((i+1)/2)*N].push_back(make_pair(j+(((i+1)/2)-1)*N,map[i][j]));
                G[j+(((i+1)/2)-1)*N].push_back(make_pair(j+((i+1)/2)*N,map[i][j]));
            }
        }
    }

    int Q;
    ifs >> Q;
    int Qlist[3000][4] = {0};
    for(int i = 0;i < Q;i++){
        for(int j = 0;j < 4;j++){
            ifs >> Qlist[i][j];
        }
    }

    /* 格納したマップを出力
    for (int i = 0; i < 2 * N - 1; ++i) {
        for (int j = 0; j < ((i % 2 == 0) ? N - 1 : N); ++j) {
            ofs << map[i][j] << " ";
        }
        ofs << endl;
    }

    for(int i = 0;i < Q;i++){
        for(int j = 0;j < 4;j++){
            ofs << Qlist[i][j] << " ";
        }
        ofs << endl;
    }

    cout << "end";

    return 0;
    */

    //累積和開始

    //累積和用
    vector<vector<int>> ruiseki(N+1, vector<int>(N+1, 0));

    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            ruiseki[i+1][j+1] += ruiseki[i+1][j] + ruiseki[i][j+1] - ruiseki[i][j];
            if(i+1 != 1) ruiseki[i+1][j+1] += map[2*i-1][j];
            if(j+1 != 1) ruiseki[i+1][j+1] += map[2*i][j-1];
        }
    }
    //累積和終了

    //確認用
    /*
    for(int i = 0;i < N+1;i++){
        for(int j = 0;j < N+1;j++){
            ofs << ruiseki[i][j] << " ";
        }
        ofs << endl;
    }
    */

    //ダイクストラ開始
    for(int i = 0;i < Q;i++){
        int X[2] = {Qlist[i][1], Qlist[i][0]};
        int Y[2] = {Qlist[i][3], Qlist[i][2]};
        int basenumber;
        if(X[0] > Y[0]) swap(X, Y);
        if(X[1] < Y[1]) basenumber = ruiseki[Y[0]+1][Y[1]+1] + ruiseki[X[0]][X[1]] - ruiseki[Y[0]][X[1]] - ruiseki[X[0]][Y[1]];
        else basenumber = ruiseki[Y[0]+1][X[1]+1] + ruiseki[X[0]][Y[1]] - ruiseki[X[0]][X[1]] - ruiseki[Y[0]][Y[1]];

        //int base = Qlist[i][0]+(Qlist[i][1]*N);
        //int distination = Qlist[i][2]+(Qlist[i][3]*N);
        int base = X[1]+(X[0]*N);
        int distination = Y[1]+(Y[0]*N);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pri;
        long long cur[40000];
        for(int j = 0;j < 40000;j++)cur[j] = 2000000000000000;
        bool kakutei[40000];
        for(int j = 0;j < 40000;j++) kakutei[j] = false;
        cur[base] = 0;
        pri.push(make_pair(cur[base],base));
        //cout << base << " " << distination << endl;
        while(!pri.empty()){
            int pos = pri.top().second; pri.pop();
            if(kakutei[pos] == true) continue;
            kakutei[pos] = true;
            for(int j = 0;j < G[pos].size();j++){
                int nex = G[pos][j].first;
                int cost = G[pos][j].second;
                //cout << nex << " " << cost << endl;
                if(cur[nex] > cur[pos] + cost){
                    cur[nex] = cur[pos] + cost;
                    pri.push(make_pair(cur[nex], nex));
                }
                else{
                    //cout << cur[pos] + cost << " " << "asd" << endl;
                }
            }
        }
        
        cout << i << endl;
        ofs << cur[distination] << endl;
        //cout << distination << endl;
    }
    clock_t end = clock();
    cout << end-start;
}
