#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

ifstream ifs("qual_random_01.in"); 
ofstream ofs("result.in", ios::app);


int main() {

    vector<pair<int,int>> G[40000];
    //入力
    int N;
    ifs >> N; // 一辺の頂点数を読み込む

    // マップのサイズに合わせた配列を作成
    int map[2 * N - 1][N] = {0};

    // 与えられたコストをマップに格納
    for (int i = 0; i < 2 * N - 1; ++i) {
        for (int j = 0; j < ((i % 2 == 0) ? N - 1 : N); ++j) {
            ifs >> map[i][j];
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
    vector<vector<int>> ruiseki(N+1, vector<int>(N+1, 0));
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            ruiseki[i+1][j+1] += ruiseki[i+1][j] + ruiseki[i][j+1] - ruiseki[i][j];
            if(i+1 != 1) ruiseki[i+1][j+1] += map[2i-1][j];
            if(j+1 != 1) ruiseki[i+1][j+1] += map[2i][j-1];
        }
    }
    //累積和終了

    //確認用
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            ofs << ruiseki[i+1][j+1] << " ";
        }
        ofs << endl;
    }

    //ダイクストラ開始
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pri;

    

}
