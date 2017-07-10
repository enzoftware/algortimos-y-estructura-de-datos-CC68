#include <cstddef>
#include <iostream>
#include <cstdlib>

using namespace std;

 class AVLTree {
    struct Node {
        int e;
        Node *l, *r;
        int h;
        Node(int e = 0,
             Node* l = NULL,
             Node* r = NULL)
            : e(e), l(l), r(r) {
            int hl = l == NULL? -1 : l->h;
            int hr = r == NULL? -1 : r->h;
            this->h = (hl > hr? hl : hr) + 1;
        }
    };
    int h(Node* n) {
        return n == NULL? -1 : n->h;
    }
    void fixH(Node* n) {
        n->h = (h(n->l) > h(n->r)? h(n->l) : h(n->r)) + 1;
    }
    void deleteAll(Node* n) {
        if (n != NULL) {
            deleteAll(n->l);
            deleteAll(n->r);
            delete n;
        }
    }
    void enOrden(Node* n)  {
        if (n != NULL) {
            enOrden(n->l);
            proc(n->e);
            enOrden(n->r);
        }
    }
    void rotarIzq(Node*& x) {
        Node* y = x->r;
        x->r = y->l;
        y->l = x;
        x = y;
        fixH(x->l);
        fixH(x);
    }
    void rotarDer(Node*& y) {
        Node* x = y->l;
        y->l = x->r;
        x->r = y;
        y = x;
        fixH(y->r);
        fixH(y);
    }
    void balancear(Node*& n) {
        if (h(n->l) - h(n->r) > 1) {
            if (h(n->l->r) > h(n->l->l)) {
                rotarIzq(n->l);
            }
            rotarDer(n);
        } else if (h(n->r) - h(n->l) > 1) {
            if (h(n->r->l) > h(n->r->r)) {
                rotarDer(n->r);
            }
            rotarIzq(n);
        }
    }
    bool insertar(int e, Node*& n) {
        bool flag = false;
        if (n == NULL) {
            n = new Node(e);
            ++len;
            return n != NULL;
        } else if (cmp(e, n->e) < 0) {
            flag = insertar(e, n->l);
        } else {
            flag = insertar(e, n->r);
        }
        if (flag) {
            balancear(n);
            fixH(n);
        }
        return flag;
    }

Node* unirNodo(Node* izq , Node* der){
  if(izq == NULL) return der;
  if(der == NULL) return izq;

  Node* centr = unirNodo(izq->r, der->l);
  izq->r = centr;
  der->l = izq;
  return der;
}

void Eliminar(Node *& nodo, int x){
  if(nodo == NULL) return;

  if(x < nodo->e) Eliminar(nodo->l,x);
  else if(x > nodo->e) Eliminar(nodo->r,x);
  else{
    Node* p = nodo;
    nodo = unirNodo(nodo->l,nodo->r);
    delete p;
  }
}

public:
    AVLTree(void (*proc)(int)): root(NULL), len(0){
      this->proc = proc;
    }
    ~AVLTree(){
      deleteAll(root);
    }
    void enOrden() {
      enOrden(root);
    }
    bool insertar(int e){
      return insertar(e, root);
    }
    int size() {
      return len;
    }
    int height() {
      return h(root);
    }

    void deleteThis(int x){
      Eliminar(root,x);
    }



private:
    Node *root;
    int len;
    void (*proc)(int);
    int  cmp(int a , int b){
      return a -b ;
    }
};


void impri(int e){ cout<<" "<<e; }
int main(int argc, char const *argv[]) {

  AVLTree *t = new AVLTree(impri);

  srand(2017);
  t->insertar(1);
    for (int i = 0; i < 10; ++i) {
        long long val = rand() % 1000;
        t->insertar(val);
    }
    t->insertar(1001);
    t->enOrden();
    //cout << "\nNumero de elementos:" << t->size() << endl;
    //cout << "Altura:" << t->height() << endl;
    cout<<endl<<endl;
    t->deleteThis(1);
    t->deleteThis(1001);
    t->enOrden();

    return 0;
  return 0;
}
