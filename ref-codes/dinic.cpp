#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Dinic{
    static const int MXV = 10000;
    static const T   INF = 1e9;
    struct Edge{ 
        int v;
        T   f;
        int re; 
    };
    int n, s, t, level[MXV];
    vector<Edge> E[MXV];
    int now[MXV];
    void init(int _n, int _s, int _t){
        n = _n; s = _s; t = _t;
        for (int i=0; i<n; i++) E[i].clear();
    }
#define SZ(x) ((int)(x).size())
    void add_edge(int u, int v, T f){
        E[u].PB({v, f, SZ(E[v])  });
        E[v].PB({u, f, SZ(E[u])-1});
    }
    bool BFS(){
        fill(level, level+n, -1);
        queue<int> que;
        que.push(s); level[s] = 0;
        while (que.size()) {
            int u = que.front(); que.pop();
            for (auto it : E[u]){
                if (it.f > 0 && level[it.v] == -1){
                    level[it.v] = level[u]+1;
                    que.push(it.v);
                }
            }
        }
        return level[t] != -1;
    }
    T DFS(int u, T nf) {
        if (u == t) return nf;
        T res = 0;
        while (now[u] < SZ(E[u])){
            Edge &it = E[u][now[u]];
            if (it.f > 0 && level[it.v] == level[u]+1){
                T tf = DFS(it.v, min(nf, it.f));
                res += tf; nf -= tf; it.f -= tf;
                E[it.v][it.re].f += tf;
                if (nf == 0) return res;
            } else now[u] ++;
        }
        if (!res) level[u] = -1;
        return res;
    }
    T flow(T res=0){
        while ( BFS() ) {
            T temp;
            memset(now, 0, sizeof(now));
            while ((temp = DFS(s, INF))) {
                res += temp;
            }
        }
        return res;
    }
};
