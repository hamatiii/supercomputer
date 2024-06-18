#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAX_N = 40009;
const int MAX_Q = 3000;

ifstream ifs("qual_random_01.in"); 
ofstream ofs("result.in", ios::app);

int main() {
    if (!ifs.is_open() || !ofs.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    clock_t start = clock();
    vector<pair<int, int>> G[MAX_N];

    int N;
    ifs >> N;
    int map[2 * N - 1][N] = {0};

    for (int i = 0; i < 2 * N - 1; ++i) {
        bool isEven = (i % 2 == 0);
        for (int j = 0; j < (isEven ? N - 1 : N); ++j) {
            ifs >> map[i][j];
            if (isEven) {
                G[j + (i / 2) * N].push_back(make_pair(j + ((i / 2) * N) + 1, map[i][j]));
                G[j + ((i / 2) * N) + 1].push_back(make_pair(j + (i / 2) * N, map[i][j]));
            } else {
                G[j + ((i + 1) / 2) * N].push_back(make_pair(j + (((i + 1) / 2) - 1) * N, map[i][j]));
                G[j + (((i + 1) / 2) - 1) * N].push_back(make_pair(j + ((i + 1) / 2) * N, map[i][j]));
            }
        }
    }

    int Q;
    ifs >> Q;
    int Qlist[MAX_Q][4] = {0};
    for (int i = 0; i < Q; i++) {
        for (int j = 0; j < 4; j++) {
            ifs >> Qlist[i][j];
        }
    }

    vector<vector<int>> ruiseki(N + 1, vector<int>(N + 1, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ruiseki[i + 1][j + 1] += ruiseki[i + 1][j] + ruiseki[i][j + 1] - ruiseki[i][j];
            if (i + 1 != 1) ruiseki[i + 1][j + 1] += map[2 * i - 1][j];
            if (j + 1 != 1) ruiseki[i + 1][j + 1] += map[2 * i][j - 1];
        }
    }

    // 基準となる経路のコストを計算
    int baseX = Qlist[0][1], baseY = Qlist[0][0], destX = Qlist[0][3], destY = Qlist[0][2];
    int baseCost = ruiseki[destX + 1][destY + 1] + ruiseki[baseX][baseY] - ruiseki[destX][baseY] - ruiseki[baseX][destY];

    for (int i = 0; i < Q; i++) {
        int X[2] = {Qlist[i][1], Qlist[i][0]};
        int Y[2] = {Qlist[i][3], Qlist[i][2]};
        int queryCost;
        if (X[0] > Y[0]) swap(X, Y);
        if (X[1] < Y[1]) {
            queryCost = ruiseki[Y[0] + 1][Y[1] + 1] + ruiseki[X[0]][X[1]] - ruiseki[Y[0]][X[1]] - ruiseki[X[0]][Y[1]];
        } else {
            queryCost = ruiseki[Y[0] + 1][X[1] + 1] + ruiseki[X[0]][Y[1]] - ruiseki[X[0]][X[1]] - ruiseki[Y[0]][Y[1]];
        }

        int base = X[1] + (X[0] * N);
        int distination = Y[1] + (Y[0] * N);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pri;
        long long cur[40000];
        fill(cur, cur + 40000, 2000000000000000);
        bool kakutei[40000];
        fill(kakutei, kakutei + 40000, false);
        cur[base] = 0;
        pri.push(make_pair(cur[base], base));

        bool foundBetterRoute = false;
        while (!pri.empty()) {
            int pos = pri.top().second; pri.pop();
            if (kakutei[pos]) continue;
            kakutei[pos] = true;
            for (const auto& edge : G[pos]) {
                int nex = edge.first;
                int cost = edge.second;
                if (cur[nex] > cur[pos] + cost) {
                    cur[nex] = cur[pos] + cost;
                    if (cur[nex] + baseCost >= queryCost) {
                        foundBetterRoute = true;
                        break;
                    }
                    pri.push(make_pair(cur[nex], nex));
                }
            }
            if (foundBetterRoute) break;
        }

        if (foundBetterRoute) {
            ofs << cur[distination] << endl;
        } else {
            // 基準経路のコストより高い場合に別経路で探索
            fill(cur, cur + 40000, 2000000000000000);
            fill(kakutei, kakutei + 40000, false);
            cur[base] = 0;
            pri.push(make_pair(cur[base], base));

            while (!pri.empty()) {
                int pos = pri.top().second; pri.pop();
                if (kakutei[pos]) continue;
                kakutei[pos] = true;
                for (const auto& edge : G[pos]) {
                    int nex = edge.first;
                    int cost = edge.second;
                    if (cur[nex] > cur[pos] + cost) {
                        cur[nex] = cur[pos] + cost;
                        pri.push(make_pair(cur[nex], nex));
                    }
                }
            }
            ofs << cur[distination] << endl;
        }
    }

    clock_t end = clock();
    cout << end - start << endl;
    return 0;
}
