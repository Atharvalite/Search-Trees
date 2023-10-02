#include<bits/stdc++.h>


using namespace std;


class BST;
class Node{
    int val;
    Node* left;
    Node* right;
public:
    friend class BST;
    Node(){
        val = 0;
        left = NULL;
        right = NULL;
    }
    Node(int x, Node* l=NULL, Node* r=NULL){
        val = x;
        left = l;
        right = r;
    }

};


class BST{
    Node* root;
public:
    BST(){
        root = NULL;
    }

    void insert(vector<int> values){
        for(int v:values){
            this->insert(v);
        }
        return;
    }
    void insert(int x){
        if(root==NULL){
            root = new Node(x);
            return;
        }
        Node* temp = root;
        Node* par = root;

        while(temp){
            if(x>=temp->val){
                par = temp;
                temp = temp->right;
            }
            else{
                par = temp;
                temp = temp->left;
            }
        }
        if(x>=par->val){
            par->right = new Node(x);
        }
        else{
            par->left = new Node(x);
        }
        return;
    }

    void display(){
        cout<<"Inorder traversal: ";
        inorder(root);
        cout<<endl;

        cout<<"Preorder Traversal: ";
        preorder(root);
        cout<<endl;

        cout<<"Postorder traversal: ";
        postorder(root);
        cout<<endl;
        return;

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
    void inorder(){
        Node* ptr = root;
        stack<Node*> s;

        while(ptr){
            s.push(ptr);
            ptr = ptr->left;
        }
        while(!s.empty()){
            ptr = s.top();
            s.pop();
            cout<<ptr->val<<" ";
            ptr = ptr->right;
            while(ptr){
                s.push(ptr);
                ptr = ptr->left;
            }
        }
        cout<<endl;
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
    void preorder(){
        Node* ptr = root;
        stack<Node*> s;
        while(ptr){
            cout<<ptr->val<<" ";
            s.push(ptr);
            ptr = ptr->left;
        }
        while(!s.empty()){
            ptr = s.top();
            s.pop();
            ptr = ptr->right;
            while(ptr){
                cout<<ptr->val<<" ";
                s.push(ptr);
                ptr = ptr->left;
            }
        }
        cout<<endl;
        return;
    }
    void postorder(Node* b){
        if(b==NULL){
            return;
        }
        else{
            postorder(b->left);
            postorder(b->right);
            cout<<b->val<<" ";
            return;
        }
    }
    void postorder(){
        Node* ptr = root;
        stack<Node*> s;
        stack<Node*> q;
        s.push(ptr);
        while(!s.empty()){
            ptr = s.top();
            s.pop();
            q.push(ptr);

            if(ptr->left){
                s.push(ptr->left);
            }
            if(ptr->right){
                s.push(ptr->right);
            }

        }

        while(!q.empty()){
            ptr = q.top();
            q.pop();
            cout<<ptr->val<<" ";
        }
    }
    void search(int x){
        Node* temp = root;
        while(temp){
            if(temp->val==x){
                cout<<"The integer "<<x<<" is present in the BST"<<endl;
                return;
            }
            else if(x>temp->val){
                temp = temp->right;
            }
            else{
                temp = temp->left;
            }
        }
        cout<<"Element not found in the BST"<<endl;
        return;
    }
    void print(){
        cout<<"Inorder: ";
        inorder();
        cout<<"Preorder: ";
        preorder();
        cout<<"Postorder: ";
        postorder();
    }

    void deleteNode(int x){
        Node* par = NULL;
        Node* temp = root;
        while(temp){
            if(temp->val==x){
                break;
            }
            else if(x>temp->val){
                par = temp;
                temp = temp->right;
            }
            else{
                par = temp;
                temp = temp->left;
            }
        }
        if(temp){
            if(!temp->left || !temp->right){
                dltnode(par, temp);
            }
            else{
                Node* t = temp->right;
                Node* p = temp;
                while(t->left){
                    p = t;
                    t = t->left;
                }
                temp->val = t->val;
                dltnode(p, t);
            }
        }
        return;
    }
    void dltnode(Node* par, Node* temp){
        Node* child=NULL;
        if(temp->left){
            child = temp->left;
        }
        else if(temp->right){
            child = temp->right;
        }

        if(par->left==temp){
            par->left = child;
        }
        else{
            par->right = child;
        }
        delete temp;
    }

};

int main(){

    int choice = 0;
    BST obj;
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
        else if(choice==3){
            cout<<"Using stack methods"<<endl;
            obj.print();
        }
        else if(choice==2){
            cout<<"Enter the element to be searched: "<<endl;
            cin>>num;
            obj.search(num);
        }
        else if(choice==4){
            cout<<"ENter element to delete: "<<endl;
            cin>>num;
            obj.deleteNode(num);
        }
        cout<<"Enter a choice: "<<endl;
        cin>>choice;
    }

    return 0;
}