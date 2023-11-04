//
//  rbtree.h
//

#ifndef rbtree_h
#define rbtree_h

#include <iostream>

enum colors {RED, BLACK};

// Nodos del arbol:
template <typename T>
class rbtnode
{
public:
    // Esta clase es usada por la clase rbtree. Por eficiencia se hacen los atributos publicos.
    T key;
    rbtnode<T> *p, *left, *right;
    enum colors color;
    
    // Constructor por omision.
    rbtnode() {
    };
    
    //Inicializacion de datos miembro.
    rbtnode (const T& k, rbtnode<T> *w = nullptr, rbtnode<T> *y = nullptr, rbtnode<T> *z = nullptr, enum colors c = RED): key(k), p(w), left(y), right(z), color(c) {};
    
    ~rbtnode() {
    };
};

// Arbol rojinegro:
template <typename T>
class rbtree {
private:
    void rightRot(rbtnode<T>* x) {
        rbtnode<T>* leftSon = x->left;
        x->left = leftSon->right;
        if (leftSon->right != this->nil) {
            leftSon->right->p = x;
        }
        leftSon->p = x->p;
        if (x->p == nullptr) {
            this->root = leftSon;
        } else if (x == x->p->right) {
            x->p->right = leftSon;
        } else {
            x->p->left = leftSon;
        }
        leftSon->right = x;
        x->p = leftSon;
    }
    void leftRot(rbtnode<T>* x) {
        rbtnode<T>* rightSon = x->right;
        x->right = rightSon->left;
        if (rightSon->left != this->nil) {
            rightSon->left->p = x;
        }
        rightSon->p = x->p;
        if (x->p == nullptr) {
            this->root = rightSon;
        } else if (x == x->p->left) {
            x->p->left = rightSon;
        } else {
            x->p->right = rightSon;
        }
        rightSon->left = x;
        x->p = rightSon;
    }

    void insertIterative(rbtnode<T>* z) {
        rbtnode<T>* current = root;
        while(true) {
            if (z->key >= current->key){
                if (current->right == this->nil) {
                    current->right = z;
                    z->p = current;
                    break;
                }else {
                    current = current->right;
                }

            }
            if (z->key < current->key) {
                if (current->left == this->nil) {
                    current->left = z;
                    z->p = current;
                    break;
                } else {
                    current = current->left;
                }
            }
        }
    }
    void fixConflicts(rbtnode<T>* z) {
        while (z->p && z->p->color == RED) {
            //caso 1 tio derecho rojo
            if (z->p == z->p->p->left) {
                rbtnode<T>* uncle = z->p->p->right;
                if(uncle != this->nil && uncle->color == RED) {
                    //cambio de color padre y abuelo
                    z->p->color = BLACK;
                    uncle->color = BLACK;
                    //cambio de color abuelo
                    z->p->p->color = RED;
                    //pasa a verificar al abuelo y bisabuelo
                    z = z->p->p;
                } else {
                    //caso 3 zigzag izquierda y luego derecha al abuelo
                    if (z == z->p->right) {
                        z = z->p;
                        this->leftRot(z);
                    }
                    //caso 3 linea recta izquierda al abuelo 
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    this->rightRot (z->p->p);
                }
            } else {
                rbtnode<T>* uncle = z->p->p->left;
                //caso 1 tio izquierdo rojo
                if (uncle != this->nil && uncle->color == RED) {
                    //cambio color padre y tio
                    z->p->color = BLACK;
                    uncle->color = BLACK;
                    //cambio color abuelo
                    z->p->p->color = RED;
                    //pasa a verificar abuelo y bisabuelo
                    z = z->p->p;
                } else  {
                    //caso 3 zigzag derecha y luego izquierda al abuelo
                    if (z == z->p->left) {
                        z = z->p;
                        this->rightRot(z);
                    }
                    //caso 2 linea recta derecha al abuelo
                    z->p->color = BLACK;
                    z->p->p->color = RED;
                    this->leftRot(z->p->p);
                }   
            }
        }
        this->root->color = BLACK;
    }
public:
    rbtnode<T> *root;    // raiz del arbol
    rbtnode<T> *nil;     // nodo nil (hoja) del arbol
    
    rbtree() {
        // Constructor (crea un arbol vacio)
        this->nil = new rbtnode<T> (0);
        this->nil->color = BLACK;
        this->root = this->nil;
    }
    ~rbtree() {
        // Destructor (borra el arbol)
    };
    
    void Insert(rbtnode<T>* z) {
        // Inserta el nodo z en la posicion que le corresponde en el arbol.
        z->left = this->nil;
        z->right = this->nil;

        if (this->root == this->nil) {
            root = z;
            root->color = colors::BLACK;
        } else {
            this->insertIterative(z);
            this->fixConflicts(z);
        }

    };
    
    void InorderWalk(rbtnode<T> *x) {
        // Recorre en orden el subarbol con raiz x, imprimiendo la llave de cada nodo en en una nueva linea de la salida estandar despues de recorrido el subarbol izquierdo y antes de recorrer el subarbol derecho.
    };
    
    rbtnode<T>* Search(rbtnode<T> *x, const T& k) {
        // Busca la llave k iterativamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve el nodo nil.
        if (x == nullptr || x->key == k) {
        return x;
        }
        
        if (k < x->key) {
            return Search(x->left, k);
        } else {
            return Search(x->right, k);
        }
    };
    
    rbtnode<T>* IterativeSearch(rbtnode<T> *x, const T& k) {
        // Busca la llave k iterativamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve el nodo nil.
        rbtnode<T>* current = x;
        while (current != nullptr) {
            if (k == current->key) {
                return current;
            } else if (k < current->key) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return nullptr;
    };
    
    rbtnode<T>* Minimum(rbtnode<T> *x) {
        // Devuelve el nodo que tiene la llave menor. Si el arbol esta vacio, devuelve el nodo nil.

    };
    
    rbtnode<T>* Maximum(rbtnode<T> *x) {
        // Devuelve el nodo que tiene la llave mayor. Si el arbol esta vacio devuelve el nodo nil.
    };
    
    rbtnode<T>* Successor(rbtnode<T> *x) {
        // Devuelve el nodo cuya llave es la que le sigue a la del nodo x. Si no existe el nodo, devuelve el nodo nil.
    };
};

#endif /* rbtree_h */
