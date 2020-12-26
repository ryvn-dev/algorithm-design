#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <cstring>
using namespace std;

//declare 2 structure
struct Node;
struct Edge;
struct Node
{
    int x, y, val;
    int ID;
    bool deg = false;
    bool type;
    Node *ptr = nullptr;
    Edge *pte = nullptr;
};

struct Edge
{
    Node *s, *t;
    int l, f, c;
    int edgeID;
};

//declare functions' prototype
int comp( const void *a ,const void *b);
int comp2(const void *a ,const void *b);
Edge *RAM(Edge* flow, Node* source, Node* sink, int sourceN, int sinkN);
Edge* contructres(Edge *res, Edge *flow, int totaledge);
Edge* BF2(Node* source, Node* sink, Edge *flow, Edge *res, int sourcenumber, int sinknumber, int restotaledge);
Edge* makingAG(Node* sources, Node* sinks, Node &T, Edge* res, Edge *rn, int sinkn, int sourcen, int edgenumber);
Edge* renewnetwork(Edge *flow, Edge *upres, int resedge);
int area(Edge *flow, int totaledge);

//main fuction
int main(int argc, const char * argv[]) {
    
    //input file & ouput file
    ifstream InputFile;
    InputFile.open(argv[1], ifstream::in);
    ofstream OuputFile;
    OuputFile.open(argv[2], ofstream::out);
    
    //declare # of nodes
    int NumV, NumS, NumD;
    InputFile >> NumV;
    NumS = 0;
    NumD = 0;
    
    //array of points which stored as node type
    Node *points;
    points = (Node*)malloc(sizeof(Node)*(NumV));
    
    //input all nodes
    for (int i=0; i<NumV; i++) {
        InputFile >> points[i].x;   //coordinate of x
        InputFile >> points[i].y;   //coordinate of y
        InputFile >> points[i].val; //value of node
        points[i].ID = i+1;         //ID from 1 to n
        //if value is positive then is sources, otherwise sinks
        if (points[i].val>=0) {
            points[i].type = true;
            NumS++;
        } else {
            points[i].type = false;
            NumD++;
        }
    }
    
    //array of sources & sinks which stored as node type
    Node *sources;
    sources = (Node*)malloc(sizeof(Node)*(NumS));
    Node *sinks;
    sinks = (Node*)malloc(sizeof(Node)*(NumD));
    
    //store into two arrays
    int p = 0;
    int q = 0;
    for (int i=0; i<NumV; i++) {
        //if value is positive then is sources, otherwise sinks
        if (points[i].type) {
            sources[p] = points[i];
            p++;
        } else {
            sinks[q] = points[i];
            q++;
        }
    }
    
    free(points);
    
    //max total edges is #sources*#sinks
    int TotalEdge = NumS*NumD;
    
    //edges array
    Edge *init_edge = nullptr;
    init_edge = (Edge*)malloc(sizeof(Edge)*(TotalEdge)); //生成一維指標陣列
    
    //calculate every edge
    int r = 0;
    for (int i=0; i<NumS; i++) {
        for (int j=0; j<NumD; j++) {
            init_edge[r].s = &sources[i];
            init_edge[r].t = &sinks[j];
            init_edge[r].f = 0;
            int u = sources[i].x - sinks[j].x;
            int v = sources[i].y - sinks[j].y;
            init_edge[r].l = abs(u) + abs(v);
            init_edge[r].c = min(abs(init_edge[r].s->val), abs(init_edge[r].t->val));
            init_edge[r].edgeID = r;
            r++;
        }
        
    }
    
    //initial solution constructed by method of Lin et al.(2012)
    //O(mn(m+n))
    init_edge = RAM(init_edge, sources, sinks, NumS, NumD);
    
    //res G of initial solution
    Edge *res_initial = nullptr;
    res_initial = (Edge*)malloc(sizeof(Edge)*2*TotalEdge);
    
    //convert initial solution to res G
    res_initial = contructres(res_initial, init_edge, TotalEdge);
    
    //final solution
    Edge *final_edge = nullptr;
    final_edge = (Edge*)malloc(sizeof(Edge)*(TotalEdge));
    
    
    //final solution by bellman ford negative by iterative cycle cancelling of Jiang et al.(2012)
    //rO(mn)
    final_edge = BF2(sources, sinks, init_edge, res_initial, NumS, NumD, 2*TotalEdge);
    
    //sorting the final answer = O(nlgn to n^2)
    qsort(final_edge, TotalEdge, sizeof(Edge), comp2);
   
    //output the data
    OuputFile << area(final_edge, TotalEdge) << endl;
    for (int i=0; i<TotalEdge; i++) {
        if (init_edge[i].f != 0) {
            OuputFile << final_edge[i].s->x << " " << final_edge[i].s->y << " ";
            OuputFile << final_edge[i].t->x << " " << final_edge[i].t->y << " ";
            OuputFile << final_edge[i].f << endl;
        }
    }
    cout << endl;
    
    free(final_edge);
    final_edge = nullptr;
    free(res_initial);
    res_initial = nullptr;
    free(sinks);
    sinks = nullptr;
    free(sources);
    sources = nullptr;
    
    return 0;
}

//comparing by l then c
int comp(const void *a ,const void *b)
{
    struct Edge *aa = (Edge *)a;
    struct Edge *bb = (Edge *)b;
    if (aa->l == bb->l) {
        return aa->c > bb->c ? 1 : -1;
    } else {
        return aa->l > bb->l ? 1 : -1;
    }
}

//construct the res G
Edge* contructres(Edge *res, Edge *flow, int totaledge){
    
    int resedges = 0;
    
    //put edges of res.c !=0 first
    for (int i=0; i<totaledge; i++) {
        if (flow[i].c - flow[i].f != 0) {
            res[resedges].s = flow[i].s;
            res[resedges].t = flow[i].t;
            res[resedges].f = 0;
            res[resedges].l = flow[i].l;
            res[resedges].c = flow[i].c - flow[i].f;
            res[resedges].edgeID = flow[i].edgeID;
            resedges++;
        }
        if (flow[i].f != 0) {
            res[resedges].s = flow[i].t;
            res[resedges].t = flow[i].s;
            res[resedges].f = 0;
            res[resedges].l = -flow[i].l;
            res[resedges].c = -flow[i].f;
            res[resedges].edgeID = flow[i].edgeID;
            resedges++;
        }
    }
    
    //put edges of res.c =0 then
    for (int i=0; i<totaledge; i++) {
        if (flow[i].c - flow[i].f == 0) {
            res[resedges].s = flow[i].s;
            res[resedges].t = flow[i].t;
            res[resedges].f = 0;
            res[resedges].l = flow[i].l;
            res[resedges].c = flow[i].c - flow[i].f;
            res[resedges].edgeID = flow[i].edgeID;
            resedges++;
        }
        if (flow[i].f == 0) {
            res[resedges].s = flow[i].t;
            res[resedges].t = flow[i].s;
            res[resedges].f = 0;
            res[resedges].l = -flow[i].l;
            res[resedges].c = -flow[i].f;
            res[resedges].edgeID = flow[i].edgeID;
            resedges++;
        }
    }
    
    return res;
}

//renew the network
Edge* renewnetwork(Edge *flow, Edge *upres, int resedge){
    
    for (int i=0; i<resedge; i++) {
        flow[upres[i].edgeID].f = flow[upres[i].edgeID].f + upres[i].f;
    }
    
    return flow;
}

//calculating area
int area(Edge *flow, int totaledge){
    
    int a = 0;
    
    for (int i=0; i<totaledge; i++) {
        a = a + flow[i].f*flow[i].l;
    }
    
    return a;
}

//bellman ford
Edge* BF2(Node* source, Node* sink, Edge *flow, Edge *res, int sourcenumber, int sinknumber, int restotaledge){
    
    Node T;
    T.x = 999999999;
    T.y = 999999999;
    T.ID = 0;
    T.type = false;
    T.deg = false;
    T.ptr = nullptr;
    T.pte = nullptr;
    
    int Tflowedge = sourcenumber*sinknumber;
    
    while (1) {
        
        int resedge = 0;
        
        for (int i = 0; i<restotaledge; i++) {
            if (res[i].c != 0) {
                resedge++;
            }
        }
        
        int allpoint = sourcenumber + sinknumber + 1;
        int Tedge = sourcenumber + sinknumber + resedge;
        
        Node* r;
        r = nullptr;
        
        Edge *rn = nullptr;
        rn = (Edge*)malloc(sizeof(Edge)*(Tedge)); //生成一維指標陣列
        rn = makingAG(source, sink, T, res, rn, sinknumber, sourcenumber, resedge);
        
        //initialize
        for (int i=0; i<Tedge; i++) {
            rn[i].s->ptr = nullptr;
            rn[i].s->pte = nullptr;
            rn[i].s->deg = false;
            
            rn[i].t->ptr = nullptr;
            rn[i].t->pte = nullptr;
            rn[i].t->deg = false;
        }
        
        //BF matix
        int d[allpoint+1][allpoint];
        
        //initialize
        memset(d, 0x3f3f3f3f, sizeof(d[0][0]) * allpoint * (allpoint+1));
        for (int i=0; i<allpoint+1; i++) {
            d[i][0]=0;
        }
        
        //BF form 1 to n-1 iteration
        for (int i=1; i<=allpoint-1; i++) {
            for (int k=0; k<Tedge; k++) {
                int tj = rn[k].t->ID;
                int sj = rn[k].s->ID;
                int l = rn[k].l;
                if ( d[i-1][tj] + l < d[i][sj] && d[i-1][tj] + l < d[i-1][sj]) {
                    d[i][sj] = d[i-1][tj] + l;
                    if (tj == 0) {
                        r = rn[k].s;
                    } else {
                        rn[k].s->ptr = rn[k].t;
                        rn[k].s->pte = &rn[k];
                    }
                }
                if (d[i-1][sj] <= d[i][sj]) {
                    d[i][sj] = d[i-1][sj];
                }
            }
        }

        //set a boolin to control whether to end this procedure
        bool lea = true;
        
        //BF form n iteration
        for (int k=0; k<Tedge; k++) {
            int i = allpoint;
            int tj = rn[k].t->ID;
            int sj = rn[k].s->ID;
            int l = rn[k].l;
            if ( d[i-1][tj] + l < d[i][sj] && d[i-1][tj] + l < d[i-1][sj]) {
                d[i][sj] = d[i-1][tj] + l;
                if (tj == 0) {
                    r = rn[k].s;
                } else {
                    rn[k].s->ptr = rn[k].t;
                    rn[k].s->pte = &rn[k];
                }
                lea =false;
                break;
            }
            if (d[i-1][sj] <= d[i][sj]) {
                d[i][sj] = d[i-1][sj];
            }
        }
        
        //BF controlling
        //out of this procedure
        if (lea) {
            r = nullptr;
            free(rn);
            break;
            
        //negative cycle detected
        } else {
            
            //find cycle by DSF
            while (!r->deg) {
                r->deg = true;
                r = r->ptr;
            }
            
            int firstsx, firstsy;
            int loopsx, loopsy;
            firstsx = r->x;
            firstsy = r->y;
            
            int m = 999999;
            int g;
            do {
                
                g = r->pte->c;
                g = g <0?-g : g;
                
                r = r->ptr;
                
                loopsx = r->x;
                loopsy = r->y;
                
                //renew the min of c
                if (g < m) {
                    m = g;
                }
            } while (firstsx != loopsx || firstsy != loopsy);
            
            do {
                
                //if be forward edge, then push min(c)
                if (r->pte->c > 0) {
                    r->pte->f = r->pte->f + m;
                    r = r->ptr;
                    loopsx = r->x;
                    loopsy = r->y;
                    
                //if be backward edge, then return min(c)
                } else if (r->pte->c <= 0){
                    r->pte->f = r->pte->f - m;
                    r = r->ptr;
                    loopsx = r->x;
                    loopsy = r->y;
                    
                }
            } while (firstsx != loopsx || firstsy != loopsy);
            
            r = nullptr;
            
            for (int i=0; i<resedge; i++) {
                res[i] = rn[i];
            }
            
            free(rn);
            
            flow = renewnetwork(flow, res, resedge);
            res = contructres(res, flow, Tflowedge);
            
        }
    }
    
    return flow;
}

//make augmented graph
Edge* makingAG(Node* sources, Node* sinks, Node &T, Edge* res, Edge *rn, int sinkn, int sourcen, int edgenumber){
    
    for (int i=0; i<edgenumber; i++) {
        rn[i] = res[i];
    }
    
    for (int i=0; i<sourcen; i++) {
        rn[i+edgenumber].s = &sources[i];
        rn[i+edgenumber].t = &T;
        rn[i+edgenumber].l = 0;
        rn[i+edgenumber].f = 0;
        rn[i+edgenumber].c = 999999999;
    }
    
    for (int i=0; i<sinkn; i++) {
        rn[i+edgenumber+sourcen].s = &sinks[i];
        rn[i+edgenumber+sourcen].t = &T;
        rn[i+edgenumber+sourcen].l = 0;
        rn[i+edgenumber+sourcen].f = 0;
        rn[i+edgenumber+sourcen].c = 999999999;
    }
    
    return rn;
}

//compare final answer by s.x then s.y then t.x then t.y
int comp2(const void *a ,const void *b)
{
    
    struct Edge *aa = (Edge *)a;
    struct Edge *bb = (Edge *)b;
    if (aa->s->x == bb->s->x) {
        if (aa->s->y == bb->s->y) {
            if (aa->t->x == bb->t->x) {
                return aa->t->y > bb->t->y ? 1 : -1;
            } else {
                return aa->t->x > bb->t->x ? 1 : -1;
            }
        } else {
            return aa->s->y > bb->s->y ? 1 : -1;
        }
    } else{
        return aa->s->x > bb->s->x ? 1 : -1;
    }
}

//initial solution
Edge *RAM(Edge* flow, Node* source, Node* sink, int sourceN, int sinkN){
    
    int length[sourceN][sinkN];
    int det[sourceN][sinkN];
    int U[sourceN];
    int V[sinkN];
    
    memset(det, 0, sizeof(det[0][0]) * sinkN * sourceN);
    
    for (int i=0; i<sourceN; i++) {
        for (int j=0; j<sinkN; j++) {
            int u = source[i].x - sink[j].x;
            int v = source[i].y - sink[j].y;
            length[i][j] = abs(u) + abs(v);
        }
    }
    
    memset(U, 0, sizeof(U[0]) * sourceN);
    memset(V, 0, sizeof(V[0]) * sinkN);
    
    for (int k=0; k<sourceN+sinkN; k++) {
        
        //step 1
        for (int i=0; i<sourceN; i++) {
            for (int j=0; j<sinkN; j++) {
                if (U[i] != -1 && length[i][j] > U[i]) {
                    U[i] = length[i][j];
                }
                if (V[j] != -1 && length[i][j] > V[j]) {
                    V[j] = length[i][j];
                }
            }
        }
        
        //step2
        int MIN = 99999999;
        int I = 0;
        int J = 0;
        for (int i=0; i<sourceN; i++) {
            for (int j=0; j<sinkN; j++) {
                if (U[i]!=-1 && V[j]!=-1) {
                    det[i][j] = length[i][j] - U[i] - V[j];
                    
                    if (det[i][j] < MIN) {
                        MIN = det[i][j];
                        I = i;
                        J = j;
                    }
                }
            }
        }
        
        //step3
        int a = I*sinkN + J;
        if (abs(source[I].val) !=0 || abs(sink[J].val) !=0) {
            if (abs(source[I].val) >= abs(sink[J].val)) {
                flow[a].f = abs(sink[J].val);
                source[I].val = abs(source[I].val) - abs(sink[J].val);
                sink[J].val = abs(sink[J].val) - abs(sink[J].val);
                V[J] = -1;
            } else {
                flow[a].f = abs(source[I].val);
                sink[J].val = abs(sink[J].val) - abs(source[I].val);
                source[I].val = abs(source[I].val) - abs(source[I].val);
                U[I] = -1;
            }
        }
    }
    
    return flow;
}








