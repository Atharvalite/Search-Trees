#include<bits/stdc++.h>

using namespace std;

class AVL;
class Node{
    int val;
    Node* left;
    Node* right;
    int height;
public:
    friend class AVL;
    Node(){
        height = 1;
        val = 0;
        left = NULL;
        right = NULL;
    }
    Node(int x, Node* l=NULL, Node* r=NULL){
        height=1;
        val = x;
        left = l;
        right = r;
    }

};

class AVL{
public:
    Node* root;
    AVL(){
        root = NULL;
    }
    
    void insert(vector<int>vals){
        Node* a;
        for(auto v:vals){
            root = insert(root, v);
        }
        return;
    }

    int height(Node* a){
        if(a==NULL){
            return 0;

        }
        return a->height;
    }
    // z is the top node, and y is the child of z;
    Node* right(Node* y, Node* z){
        z->left = y->right;
        y->right = z;

        z->height = 1+max(height(z->right),height(z->left));
        y->height = 1+max(height(y->left), height(y->right));

        return y;
    }

    Node* left(Node* y, Node* z){
        z->right = y->left;
        y->left = z;

        z->height = 1+max(height(z->right),height(z->left));
        y->height = 1+max(height(y->left), height(y->right));
        return y;
    }

    Node* insert(Node* b, int x){
        if(b==NULL){
            Node* a = new Node(x);
            return a;
        }
        else if(x>b->val){
            b->right = insert(b->right, x);
        }
        else if(x<b->val){
            b->left = insert(b->left,x);
        }
        else{
            cout<<"Duplicates not allowed"<<endl;
            return b;
        }
        b->height = 1+max(height(b->left), height(b->right));

        int height_diff = height(b->left)-height(b->right);

        if(height_diff<=1 && height_diff>=-1){
            return b;
        }
        else{
            Node* z = b;
            Node* y;
            Node* w;
            if(x>z->val){
                y = z->right;
                if(x>y->val){
                    return left(y, z);
                }
                else{
                    w = y->left;
                    z->right = right(w, y);
                    y = z->right;
                    return left(y, z);
                }
                
            }
            else{
                y = z->left;
                if(x<y->val){
                    return right(y, z);
                }
                else{
                    w = y->right;
                    z->left = left(w, y);
                    y = z->left;
                    return right(y, z);
                }
            }
        }
    }
    Node* del(Node* root, int key){
        if(root==NULL){
            cout<<"Element already deleted"<<endl;
            return root;
        }
        if(key>root->val){
            // right sub-tree
            root->right = this->del(root->right, key);
        }
        else if(key<root->val){
            // left sub-tree
            root->left = this->del(root->left, key);
        }
        else{
            // found the node
            if(root->left==NULL || root->right==NULL){
                // if its either a leaf node, or a node with a single child;
                Node* child = NULL;
                if(root->left!=NULL){
                    child=root->left;
                }
                else if(root->right!=NULL){
                    child = root->right;
                }
                delete root;
                return child;
            }
            else{
                // find the next inorder successor
                Node* temp = root->right;
                while(temp->left!=NULL){
                    temp = temp->left;
                }
                root->val = temp->val;
                root->right = this->del(root->right, temp->val);
            }
            
        }
        root->height = 1+max(height(root->left), height(root->right));
        int diff = height(root->left)-height(root->right);
        Node* x;
        Node* y;
        Node* z;
        z = root;
        if(abs(diff)<=1){
            root->height = 1+max(height(root->left), height(root->right));
            return root;
        }
        else if(diff>1){
            y = z->left;
            if(height(y->left)>=height(y->right)){
                // LL case
                root = right(y, z);
            }
            else{
                // LR case
                x = y->right;
                z->left = left(x, y);
                y = z->left;
                root = right(y, z);
            }
        }
        else{
            y = z->right;
            if(height(y->right)>=height(y->left)){
                // RR case
                root = left(y, z);
            }
            else{
                // RL case
                x = y->left;
                z->right = right(x, y);
                y = z->right;

                root = left(y, z);
            }
        }
        return root;
        
    }
    void check_heights(Node* root){
        if(root==NULL){
            cout<<"FIN"<<endl;
        }
        else{
            cout<<"Current height: "<<root->height<<"Node value: "<<root->val<<endl;
            check_heights(root->left);
            check_heights(root->right);
        }
        return ;

    }
    void display(){
        cout<<"Preorder of this self-balanced tree is going to be: "<<endl;
        preorder(root);
        cout<<endl;
        cout<<"Inorder display of data is going to be: "<<endl;
        inorder(root);
        cout<<endl;
    }

    void inorder(Node* b){
        if(b==NULL){
            return;
        }
        else{
            inorder(b->left);
            cout<<" "<<b->val<<" ";
            inorder(b->right);
        }
    }
    void preorder(Node* b){
        if(b==NULL){
            return;
        }
        else{
            cout<<b->val<<" ";
            preorder(b->left);
            preorder(b->right);
            return;
        }
    }
};

int main(){
    int choice = 0;
    AVL obj;
    int num;

    while(choice!=-1){
        if(choice==0){
            cout<<"Number of entries to be made: ";
            cin>>num;
            vector<int> vals(num,0);
            for(int i=0;i<num;i++){
                cin>>vals[i];
            }
            obj.insert(vals);

        }
        else if(choice==1){
            // cout<<"Inorder traversal: "<<endl;
            obj.display();
        }
        else if(choice==2){
            cout<<"All node heights: "<<endl;
            obj.check_heights(obj.root);

        }
        else if(choice==3){
            cout<<"Enter the key to be deleted: "<<endl;
            cin>>num;
            obj.root = obj.del(obj.root, num);
            obj.display();
        }
        cout<<"Enter a choice: "<<endl;
        cin>>choice;
    }

    return 0;
}