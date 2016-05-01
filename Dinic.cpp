// Dinic法:最小カット,最大フローで使う
// 使い方: Dinic* dinic = new Dinic(V)で初期化(Vは頂点数)
// dinic->add_edgeまたはdinic->add_edge_bothで点をつなげてdinic->max_flowで最大フローを求める
#define NG -1
#define SZ(a) ((int)((a).size()))
class Dinic
{
public:
    Dinic(int input_maxv) : maxv(input_maxv)
    {
        G.resize(input_maxv);
        level.resize(input_maxv);
        iter.resize(input_maxv);
    }

    void add_edge_both(int from, int to, int cap)
    {
        const int rev_from  = SZ(G[from]);
        const int rev_to    = SZ(G[to]);
        G[from].push_back(edge(to,cap,rev_to));
        G[to].push_back(edge(from,cap,rev_from));
    }

    void add_edge(int from, int to, int cap)
    {
        const int rev_from  = SZ(G[from]);
        const int rev_to    = SZ(G[to]);
        G[from].push_back(edge(to,cap,rev_to));
        G[to].push_back(edge(from,0,rev_from));
    }

    int max_flow(int s, int t)
    {
        int flow = 0;
        for(;;)
        {
            bfs(s);
            if(level[t]<0) break;
            fill(iter.begin(),iter.end(),0);
            int f;
            while( (f=dfs(s,t,DINIC_INF))>0)
            {
                flow += f;
            }
        }

        return flow;
    }

    vector <bool> get_nodes_in_group(int s)
    {
        vector <bool> ret(maxv);

        queue<int> que;
        que.push(s);
        while(!que.empty())
        {
            int v = que.front();
            que.pop();
            ret[v]=true;

            for(int i=0;i<SZ(G[v]);i++)
            {
                edge &e = G[v][i];
                if(e.cap>0 && !ret[e.to])
                {
                    que.push(e.to);
                }
            }
        }
        return ret;
    }

    void disp()
    {
        for (int v = 0; v < maxv; v++)
        {
            printf("%d:",v);
            for(int i=0;i<SZ(G[v]);i++)
            {
                if(G[v][i].init_cap>0)
                {
                    printf("->%d(%d),",G[v][i].to,G[v][i].init_cap);
                }
            }
            printf("\n");
        }
    }

private:
    void bfs(int s)
    {
        fill(level.begin(),level.end(),NG);
        queue<int> que;
        level[s]=0;
        que.push(s);
        while(!que.empty())
        {
            int v = que.front();
            que.pop();
            for(int i=0;i<SZ(G[v]);i++)
            {
                edge &e = G[v][i];
                if(e.cap>0 && level[e.to]<0)
                {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    int dfs(int v, int t, int f)
    {
        if(v==t) return f;
        for (int &i=iter[v];i<SZ(G[v]);i++)
        {
            edge& e = G[v][i];
            if(e.cap>0 && level[v]<level[e.to])
            {
                int d = dfs(e.to, t, min(f, e.cap));
                if(d>0)
                {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    static const int DINIC_INF = INT_MAX;

    struct edge
    {
        edge(int input_to, int input_cap, int input_rev) : to(input_to), cap(input_cap), rev(input_rev), init_cap(input_cap) {}
        int to;
        int cap;
        int rev;
        int init_cap;
    };

    int maxv;
    vector < vector <edge> > G;
    vector < int > level;
    vector < int > iter;

};
