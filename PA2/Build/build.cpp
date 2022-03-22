#include<iostream>
using namespace std;

struct tree{
    int height = 0;
    int size = 1;
    int c_num = 0; 
    int max_right_height = 0;
    tree* first_c = NULL;
    tree* parent = NULL;
    tree* l_bro = NULL;
    tree* r_bro = NULL;
    //father?
};
int M,N;

tree* root;

void print_tree(){
	//debug
    for(int i = 0; i < N; i ++){
    	tree* temp = root[i].first_c;
    	cout<<"not "<<i + 1<<"--";
    	while(temp != NULL){
    		cout << temp - root + 1<<" ";
    		temp = temp->r_bro;
		}
    		
    		
    	cout<<endl;
	}
}

void update_parents(tree* me, int h, int change_of_size){ //height & size
	//debug
    if(me == root){
        me->height = h + 1;
        me->size += change_of_size;
        return;
    }
    int t = me->height;
    me->height = h + 1;
    me->max_right_height = h + 1;
    
    if(me->r_bro)
        me->max_right_height = max(me->height, me->r_bro->max_right_height);
    me->size += change_of_size;
    tree* temp = me; 
    if(temp->l_bro && t == temp->l_bro->max_right_height){ //
        while(temp->l_bro ){
            temp = temp->l_bro;
            temp->max_right_height = max(temp->height,temp->r_bro->max_right_height);
        }
    }
    update_parents(me->parent,me->parent->first_c->max_right_height, change_of_size);
    


}

tree* to_child(tree* me, int r){
    tree* t = me->first_c;
    if(r == 0){
        return t;
    }
    for(int i = 1; i <= r; i ++){
        if(!t->r_bro)continue;
        t = t->r_bro;
        
    }
    return t;
} //can't be nullptr

void init(tree* me){
    if(!me->first_c){
    	//cout<<me - root + 1<<endl;
        me->height = 0;
        me->size = 1;
        me->max_right_height = 0;
        me->c_num = 0;

        return;
    }
    tree* temp = me->first_c;
    while(temp->r_bro){
        temp = temp->r_bro;
    }
    init(temp);
    temp->max_right_height = temp->height;
    temp = temp->l_bro;
    while(temp){
        init(temp);
        temp->max_right_height = max(temp->height, temp->r_bro->max_right_height);
        temp = temp->l_bro;
        
    }
    me->height = me->first_c->max_right_height + 1;
    //cout<<"height "<<me - root + 1 << " "<<me->height<<endl;
    temp = me->first_c;
    while(temp){
        me->size += temp->size;
        temp = temp->r_bro;
        
    }
    //cout<<"size "<<me-root+1<<" "<<me->size<<endl;


}


void build_tree(){
    int child_num;
    int rank;
    for(int i = 0; i < N; i++){
        cin >> child_num;
        root[i].c_num = child_num;//
        if(child_num == 0){
            root[i].first_c = NULL;
        }
        else{
            cin >> rank;
            tree* temp = root + rank - 1;
            temp->parent = root + i;
            root[i].first_c = temp; //height,size;
            temp->l_bro = NULL;
            temp->r_bro = NULL;
            for(int j = 1; j < child_num; j ++){
                cin >> rank;
                temp->r_bro = root + rank - 1;
                tree* temp2 = temp;
                temp = root + rank - 1;
                temp->parent = root + i;
                temp->l_bro = temp2;
                temp->r_bro = NULL;
            
            }
        }
        
    }
    init(root);
   
    //debug
    //print_tree();
}



void delete_source(tree* source){
    if(!source->l_bro){//source->parent->first_c == source
        source->parent->first_c = source->r_bro;
        
        if(source->r_bro){
        	source->r_bro->l_bro = NULL;
        	update_parents(source->parent, source->r_bro->max_right_height, -(source->size));
		}	
        else{
        	//debug
	       	update_parents(source->parent, -1, -(source->size));
		}
        return;
    }
    else{
        if(source->l_bro)
            source->l_bro->r_bro = source->r_bro;
        if(source->r_bro){
            source->r_bro->l_bro = source->l_bro;
        }
        tree* s = source->r_bro;
        if(source->r_bro){
            while(s->l_bro && s->l_bro->max_right_height == source->height){
                s->l_bro->max_right_height = max(s->l_bro->height, s->max_right_height);
                s = s->l_bro;
            }
        }
        else{
            s = source->l_bro;
            s->max_right_height = s->height;
            s = s->l_bro;
            
            while(s && s->max_right_height == source->height){
                s->max_right_height = max(s->height, s->r_bro->max_right_height);
                s = s->l_bro;
            }
        }
        update_parents(source->parent, source->parent->first_c->max_right_height, -(source->size));
        return;
    }
}



void move_tree(){
    int step;
    int rank;
    int flag = 0;
    tree* source = root;
    cin >> step;
    for(int i = 0; i < step; i ++){
        cin >> rank;
        if(flag)continue;
        if(!source)continue;
        if(!source->first_c)continue;
        else if(source->c_num <= rank){
            flag = 1;
            continue;
        }
        source = to_child(source, rank);    
    }
    //if(!source)return;
    
    
    if(source){
        source->parent->c_num--; //
        delete_source(source);
    }
        
    
    
    
    tree* target = root;
    tree* hot;
    tree* left_bro;
    flag = 0;
    //
    cin >> step;
    for(int i = 0; i < step; i ++){
        cin >> rank;
        if(flag)continue;
        if(!target)continue;
        if(!target->first_c)continue;
        else if(target->c_num <= rank){
            flag = 1;
            continue;
        }
        target = to_child(target, rank);
        
    }
    //debug
    //cout<<"target : "<<target-root+1<<endl;


    cin >> rank;

    
    hot = target;
   
    if(rank != 0 && rank == target->c_num){
    	left_bro = to_child(target, target->c_num - 1);
    	hot = target;
    	hot->c_num++;
		source->parent = hot;
    	source->l_bro = left_bro;
    	source->r_bro = NULL;
    	source->max_right_height = source->height;
    	left_bro->r_bro = source;
    	tree* s = source->l_bro;
		while(s && source->height > s->max_right_height){
			s->max_right_height = source->height;
			s = s->l_bro;
		}
    	update_parents(hot, hot->first_c->max_right_height, source->size);
    	return;
	}
	else if(target->c_num == 0 && rank==0){
		hot = target;
    	hot->c_num++;
		source->parent = hot;
    	source->l_bro = NULL;
    	source->r_bro = NULL;
    	source->max_right_height = source->height;
    	hot->first_c = source;
    	update_parents(hot, source->max_right_height, source->size);
    	return;
	}
	else{
		hot = target;
		hot->c_num++;
		if(rank == 0){
			source->parent = hot;
			source->l_bro = NULL;
			source->r_bro = hot->first_c;
			hot->first_c->l_bro = source;
			source->max_right_height = max(hot->first_c->max_right_height, source->height);
			hot->first_c = source;
			update_parents(hot, source->max_right_height, source->size);
		}
		else{
			source->parent = hot;
			left_bro = to_child(hot, rank - 1);
			source->l_bro = left_bro;
            source->r_bro = left_bro->r_bro;
			left_bro->r_bro = source;
			source->max_right_height =  source->height; //

			//if(source->r_bro)
            source->r_bro->l_bro = source;
            //if(source->r_bro)
			 source->max_right_height = max(source->r_bro->max_right_height, source->height);
			tree* s = left_bro;
            
			while(s && source->height > s->max_right_height){
				s->max_right_height = source->height;
				s = s->l_bro;
			}
			update_parents(hot, hot->first_c->max_right_height, source->size);
			
		}
	}
}




int main(){
    std::cin >> N >> M;
    root = new tree[N];
    build_tree();
    for(int i = 0; i < M; i ++){
        int type;
        cin >> type;
        if(type == 0){
			move_tree();
            

			//debug
			//print_tree();
        }
        else if(type == 1){
            int step;
            int rank;
            tree* T = root;
            int flag = 0;
            cin >> step;
            for(int j = 0; j < step; j ++){
                cin >> rank;
                if(flag)continue;
                if(T->first_c == NULL)continue;
                else if(T->c_num <= rank){
                    flag = 1;
                    continue;
                }
                T = to_child(T,rank);
            }
            cout<<T->height<<endl;
        }
        else{
            int step;
            int rank;
            int flag = 0;
            tree* T = root;
            cin >> step;
            for(int j = 0; j < step; j ++){
                cin >> rank;
                if(flag)continue;
                if(T->first_c == NULL)continue;
                else if(T->c_num <= rank){
                    flag = 1;
                    continue;
                }
                T = to_child(T,rank);
            }
            cout<<T->size<<endl;

        }
    }
    
}