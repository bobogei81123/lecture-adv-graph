template<typename TF, typename TC>
struct CostFlow {
    typedef pair<TF, TC> pll;
    static const int MXN = 205;
    static const TC  INF = 1e16; //Assume TC = long long
    struct Edge {
        int v, r;
        TF f;
        TC c;
    };
    int n, s, t, prv[MXN], prvE[MXN], inq[MXN];
    TF fl;
    TC dis[MXN], cost;
    vector<Edge> E[MXN];
    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i=0; i<n; i++) E[i].clear();
        fl = cost = 0;
    }
    void add_edge(int u, int v, TF f, TC c) {
        E[u].PB({v, SZ(E[v])  , f,  c});
        E[v].PB({u, SZ(E[u])-1, 0, -c});
    }

    pll flow() {
        while (true) {
            for (int i=0; i<n; i++) {
                dis[i] = INF;
                inq[i] = 0;
            }
            dis[s] = 0;
            queue<int> que;
            que.push(s);
            while (!que.empty()) {
                int u = que.front(); que.pop();
                inq[u] = 0;
                for (int i=0; i<SZ(E[u]); i++) {
                    int v = E[u][i].v;
                    TC  w = E[u][i].c;
                    if (E[u][i].f > 0 && dis[v] > dis[u] + w) {
                        prv[v] = u; prvE[v] = i;
                        dis[v] = dis[u] + w;
                        if (!inq[v]) {
                            inq[v] = 1;
                            que.push(v);
                        }
                    }
                }
            }
            if (dis[t] == INF) break;
            TF tf = INF;
            for (int v=t, u, l; v!=s; v=u) {
                u=prv[v]; l=prvE[v];
                tf = min(tf, E[u][l].f);
            }
            for (int v=t, u, l; v!=s; v=u) {
                u=prv[v]; l=prvE[v];
                E[u][l].f -= tf;
                E[v][E[u][l].r].f += tf;
            }
            cost += tf * dis[t];
            fl += tf;
        }
        return {fl, cost};
    }
};
