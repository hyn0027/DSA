#include <iostream>
#include <cstring>
using namespace std;

struct binNode {
    int last;
    int next;
    int father;
    int child;
    int height;
    int size;
    int maxh;
};

binNode ptree[1000001];
int n, m;


//初始化计算size
int Size(int i) {
    if (ptree[i].child == -1) {
        ptree[i].size = 1;
        return 1;
    }
    int mem = ptree[i].child;
    int record = 1;
    while (mem != -1) {
        record += Size(mem);
        mem = ptree[mem].next;
    }
    ptree[i].size = record;
    return record;
}

//初始化计算height
int Height(int i) {
    if (ptree[i].child == -1) {
        ptree[i].height = 0;
        return 0;
    }
    int mem = ptree[i].child;
    int record = 1;
    while (mem != -1) {
        int temp = Height(mem)+1;
        record = (record>temp) ? record : temp;
        mem = ptree[mem].next;
    }
    ptree[i].height = record;
    return record;

}


//初始化计算后缀子树最高高度
int Maxh(int i) {
    if (ptree[i].next == -1) {
        ptree[i].maxh = ptree[i].height;
        return ptree[i].maxh;
    }
    int mem = ptree[i].next;
    int temp = Maxh(mem);
    ptree[i].maxh = (ptree[i].height > temp) ? ptree[i].height : temp;
    return ptree[i].maxh;
}

void initial() {
    ptree[1].size=Size(1);
    ptree[1].maxh=Height(1);
    for (int i = 1; i <= n; i++) {
        if (ptree[i].child != -1) {
            Maxh(ptree[i].child);
        }
    }
}

//根据输入的路径找到相应的子树
int find() {
    int all;
    scanf("%d", &all);
    if (all == 0) {
        return 1;
    }
    int now = 1;
    int a;
    while (all!=0) {
        scanf("%d", &a);
        if (ptree[now].child == -1) {
            all--;
            while (all != 0) {
                all--;
                scanf("%d", &a);
            }
            return now;
        }
        now = ptree[now].child;
        while (a!=0) {
            if (ptree[now].next == -1) {
                all--;
                while (all != 0) {
                    all--;
                    scanf("%d", &a);
                }
                return ptree[now].father;
            }
            now = ptree[now].next;
            a--;
        }
        all--;
    }
    return now;
}

void remove_insert() {
    int start = find();

    // cout << "start" << start << endl;

    int now = start;
    int father = ptree[now].father;

    //判断高度是否需要更新
    int flag = 0;//0：未判断；1：需要；2：不需要
    
    //更新remove分支的height size maxh
    //当now=1时，last为-1，结束循环
    while (ptree[now].last != -1) {
        if (flag == 2) {
            int las = ptree[now].last;
            while (las != father) {
                ptree[las].maxh = (ptree[las].height>ptree[now].maxh)?ptree[las].height:ptree[now].maxh;
                now = las;
                las = ptree[now].last;
            }
            ptree[las].size -= ptree[start].size;
            ptree[las].height = ptree[now].maxh+1;
            now = las;
            father = ptree[now].father;
            continue;
        }
        else {
            int hei = ptree[now].height;//当前层被remove的树的起始节点的高度
            //第二层进入的时候可能不是这个判断条件
            if (ptree[now].height == (ptree[father].height-1)) {
                if (ptree[now].next!=-1) {
                    if (ptree[now].maxh>ptree[ptree[now].next].maxh) {
                        flag = 1;
                    }
                    else {
                        flag = 2;
                    }
                }
                else {
                    flag = 1;
                }
            }
            else {
                flag = 2;
            }
            //考虑被删除子树的前一个位置，此时now是删除子树的前一个位置
            int nex = now;//nex与now不同轮换
            now = ptree[now].last;
            if (now != father) {
                if (flag == 1) {
                    if (ptree[now].height >= hei) {
                        flag = 2;
                    }
                    else {
                        if (ptree[nex].next==-1) {
                            ptree[now].maxh=ptree[now].height;
                        }
                        else {
                            ptree[now].maxh=(ptree[now].height>ptree[ptree[nex].next].maxh)?ptree[now].height:ptree[ptree[nex].next].maxh;
                        }
                    }
                }
                else {
                    ptree[now].maxh=(ptree[now].height>ptree[ptree[nex].next].maxh)?ptree[now].height:ptree[ptree[nex].next].maxh;
                }
                nex = now;
                now = ptree[now].last;
            }
            
            //在同一层中向左倒序遍历，停止在第一个长子处
            while (now != father) {
                if (flag == 1) {
                    if (ptree[now].height >= hei) {                    
                        flag = 2;
                    }
                    else {
                        ptree[now].maxh = (ptree[now].height>ptree[nex].maxh)?ptree[now].height:ptree[nex].maxh;
                    }
                }
                else {
                    ptree[now].maxh = (ptree[now].height>ptree[nex].maxh)?ptree[now].height:ptree[nex].maxh;
                }
                nex = now;
                now = ptree[now].last;
            }
            //循环结束时now=father
            ptree[now].size -= ptree[start].size;
            //nex如果是要删去的值怎么办？
            if (ptree[now].child==start) {
                if (ptree[start].next==-1) {
                    ptree[now].height = 0;
                    if (ptree[now].next==-1) {
                        ptree[now].maxh = 0;
                    }
                    else {
                        ptree[now].maxh = ptree[ptree[now].next].maxh;
                    }
                }
                else {
                    ptree[now].height = ptree[ptree[start].next].maxh+1;
                    ptree[now].maxh = (ptree[now].height>ptree[ptree[now].next].maxh)?ptree[now].height:ptree[ptree[now].next].maxh;
                }
                
            }
            else {
                ptree[now].height = ptree[nex].maxh+1;
                ptree[now].maxh = (ptree[now].height>ptree[ptree[now].next].maxh)?ptree[now].height:ptree[ptree[now].next].maxh;
            }
            father = ptree[now].father;
        }
    }

    //处理remove和insert的时候的父子关系
    if (ptree[start].father == ptree[start].last) {
        ptree[ptree[start].father].child=ptree[start].next;
    }
    else {
        ptree[ptree[start].last].next = ptree[start].next;
    }
    if (ptree[start].next!=-1) {
        ptree[ptree[start].next].last=ptree[start].last;
    }
    int des = find();//des为start的新父亲
    // cout << "destination" << des << endl;
    ptree[start].father = des;
    int order;
    scanf("%d", &order);
    int obro;
    int ybro;
    if (order==0 && (ptree[des].child!=-1)) {
        int tmp=ptree[des].child;
        ptree[des].child=start;
        ptree[start].last=des;
        ptree[start].next=tmp;
        ptree[tmp].last=start;
    }
    else if (order==0 && (ptree[des].child==-1)) {
        ptree[des].child=start;
        ptree[start].last=des;
        ptree[start].next=-1;
    }
    else {
        ybro = ptree[des].child;
        while (order!=0) {
            if (ptree[ybro].next==-1) {
                obro = ybro;
                ybro = -1;
                break;
            }
            ybro = ptree[ybro].next;
            order--;
        }
        if (ybro != -1) {
            obro = ptree[ybro].last;
            ptree[ybro].last=start;
        }
        ptree[start].last=obro;
        ptree[start].next=ybro;
        ptree[obro].next=start;
    }
    if (ptree[start].next==-1) {
        ptree[start].maxh = ptree[start].height;
    }
    else {
        ptree[start].maxh = (ptree[start].height>ptree[ptree[start].next].maxh)?ptree[start].height:ptree[ptree[start].next].maxh;
    }
    

    //更新insert分支的height size maxh
    //判断高度是否需要更新
    int flag0 = 0;//0：未判断；1：需要；2：不需要
    now = start;
    father = des;
    //当now=1时，last为-1，结束循环
    while (ptree[now].last != -1) {
        //每次now上升一层时，如果flag0=2则以上层的高度都不需要被更新
        if (flag0 == 2) {
            int las = ptree[now].last;
            while (las != father) {
                ptree[las].maxh = (ptree[las].height>ptree[now].maxh)?ptree[las].height:ptree[now].maxh;
                now = las;
                las = ptree[now].last;
            }
            ptree[las].size += ptree[start].size;
            ptree[las].height = ptree[now].maxh+1;
            now = las;
            father = ptree[now].father;
            continue;
        }
        else {
            int hei = ptree[now].height;//当前层修改的树的起始节点的高度
            if (ptree[now].height > (ptree[father].height-1)) {
                flag0 = 1;
            }
            else {
                flag0 = 2;
            }
            int nex = now;//nex与now不同轮换
            now = ptree[now].last;
            while (now != father) {
                ptree[now].maxh = (ptree[now].height>ptree[nex].maxh)?ptree[now].height:ptree[nex].maxh;
                nex = now;
                now = ptree[now].last;
            }
            //出循环的时候now=father
            ptree[now].size += ptree[start].size;
            ptree[now].height = ptree[nex].maxh+1;
            ptree[now].maxh = (ptree[now].height>ptree[now].maxh)?ptree[now].height:ptree[now].maxh;
            father = ptree[now].father;
        }
    }

    // cout << "des's height" << ptree[des].height << ' ' << ptree[des].maxh << endl;

}



int main() {
    
    cin >> n >> m;

    ptree[1].father = -1;
    ptree[1].last = -1;
    ptree[1].next = -1;

    //在输入的同时记录父子兄弟关系
    for (int i = 1; i <= n; i++) {
        int children;
        scanf("%d", &children);
        if (children > 0) {
            int la;
            scanf("%d", &la);
            ptree[i].child = la;
            ptree[la].father = i;
            ptree[la].last = i;
            int ne;
            if (children > 1) {
                for (int j = 1; j < children; j++) {
                    scanf("%d", &ne);
                    ptree[la].next = ne;
                    ptree[ne].last = la;
                    ptree[ne].father = i;
                    la = ne;
                }
            }
            ptree[la].next = -1;
        }
        else {
            ptree[i].child = -1;
        }
    }

    //初始时求size及height
    initial();

    // for (int i = 1; i <= n; i++) {
    //     cout << i << ' ';
    //     cout << ptree[i].father << ' ' << ptree[i].child << ' ' << ptree[i].last << ' ' << ptree[i].next << ' ';
    //     cout << ptree[i].height << ' ' << ptree[i].size << ' ' << ptree[i].maxh << endl;
    // }

    for (int i = 0; i < m; i++) {
        int operate;
        scanf("%d", &operate);
        if (operate == 0) {
            remove_insert();
            // for (int i = 1; i <= n; i++) {
            // cout << i << ' ';
            // cout << ptree[i].father << ' ' << ptree[i].child << ' ' << ptree[i].last << ' ' << ptree[i].next << ' ';
            // cout << ptree[i].height << ' ' << ptree[i].size << ' ' << ptree[i].maxh << endl;
            // }
        }
        else if (operate == 1) {
            int rank = find();
            // cout << rank << endl;
            printf("%d\n", ptree[rank].height);
            // cout << endl;
        }
        else {
            int rank = find();
            // cout << rank << endl;
            printf("%d\n", ptree[rank].size);
            // cout << endl;
        }
    }

    return 0;
}