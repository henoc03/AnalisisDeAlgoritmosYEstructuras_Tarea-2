//
//  bstree.h
//

#ifndef bstree_h
#define bstree_h

#include <iostream>
using namespace std;
// Nodos del arbol:
template <typename T>
class bstnode
{
public:
    // Esta clase es usada por otras clases. Para mayor eficiencia, los atributos se hacen publicos.
    T key;
    bstnode<T> *p, *left, *right;
    
    // Constructor por omision
    bstnode() {
        this->p = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    };
    
    // Inicializacion de datos miembro
    bstnode(const T& k, bstnode<T> *w = nullptr, bstnode<T> *y = nullptr, bstnode<T> *z = nullptr):key(k), p(w), left(y), right(z) {};
    
    ~bstnode() {
    
    };
};

// Arbol de busqueda binario:
template <typename T>
class bstree
{
public:
    bstnode<T> *root;    // raiz del arbol

    bstree() {
        // Constructor (crea un arbol vacio)
        this->root = nullptr;
    };
    
    ~bstree() {
        while (root != nullptr) {
            Delete(root);
        }
        this->root = nullptr;
    };
    void orderedTree(){
        root = new bstnode<T>(0);
        bstnode<T>* current = root;
        for (int i = 1; i < 1000000; ++i) {
            current->right = new bstnode<T>(i);
            current->right->p = current;
            current = current->right;
        }
    }
    void Insert(bstnode<T>* z) {
        // Inserta el nodo z en la posicion que le corresponde en el arbol.
        bstnode<T>* current = root;
        if (this->root == nullptr) {
            this->root = z;
        } else {
             while(true) {
                if (z->key >= current->key){
                    if (current->right == nullptr) {
                        current->right = z;
                        z->p = current;
                        break;
                    }else {
                        current = current->right;
                    }

                }
                if (z->key < current->key) {
                    if (current->left == nullptr) {
                        current->left = z;
                        z->p = current;
                        break;
                    } else {
                        current = current->left;
                    }
                }
             }
        }

    };
    
    void InorderWalk(bstnode<T> *x) {
        // Recorre en orden el sub�arbol con raiz x, imprimiendo la llave de cada nodo en en una nueva linea de la salida estandar despues de recorrido el subarbol izquierdo y antes de recorrer el subarbol derecho.
        if (x == nullptr) {
            return;
        }
        
        InorderWalk(x->left);
        cout << x->key<<endl;
        InorderWalk(x->right); 
    };
    
    bstnode<T>* Search(bstnode<T> *x, const T& k) {
        // Busca la llave k recursivamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
        if (x == nullptr || x->key == k) {
        return x;
        }
        
        if (k < x->key) {
            return Search(x->left, k);
        } else {
            return Search(x->right, k);
        }
    };
    
    bstnode<T>* IterativeSearch(bstnode<T> *x, const T& k) {
        // Busca la llave k iterativamente en el subarbol con raiz x. Si la encuentra devuelve un apuntador al nodo que la contiene, sino devuelve nullptr.
        bstnode<T>* current = x;
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
    
    bstnode<T>* Minimum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave menor. Si el arbol esta� vacio, devuelve nullptr.
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    };
    
    bstnode<T>* Maximum(bstnode<T> *x) {
        // Devuelve el nodo que tiene la llave mayor. Si el arbol esta vacio devuelve nullptr.
        while(x->right != nullptr) {
            x = x->right;
        }
        return x;
    };
    
    bstnode<T>* Successor(bstnode<T> *x) {
        // Devuelve el nodo cuya llave es la que le sigue a la del nodo x. Si no existe el nodo, devuelve nullptr.
        if(x->right != nullptr) {
            return Minimum(x->right);
        } else {

            bstnode<T>* current = x->p;
            while (current != nullptr && x == current->right) {
                x = current;
                current = current->p;
            }
            return current;
        }
    };
    
    void Delete(bstnode<T>* z) {
        // Caso 0: Nodo sin hijos.
        if (z->left == nullptr && z->right == nullptr) {
            if(z == root) {
                delete z;
                root = nullptr;
            }else {
                if (z->p != nullptr) {
                    if (z->p->left == z) {
                        z->p->left = nullptr;
                    } else {
                        z->p->right = nullptr;
                    }
                }
                delete z;
            }
            
            
        } else if (z->left != nullptr && z->right != nullptr) {
            // Caso 2: Nodo con dos hijos
            bstnode<T>* successor = Successor(z);
            z->key = successor->key;
            Delete(successor);
        } else {
            // Caso 1: Nodo con un solo hijo
            bstnode<T>* child = nullptr; //(z->left != nullptr) ? z->left : z->right;
            if (z->left != nullptr) {
                child = z->left;
            } else {
                child = z->right;
            }
            if (z->p != nullptr) {
                if (z->p->left == z) {
                    z->p->left = child;
                } else {
                    z->p->right = child;
                }
                child->p = z->p;
            } else {
                // El nodo a eliminar es la raíz del árbol.
                // Actualiza la raíz.
                root = child;
                child->p = nullptr;
            }
            delete z;
        }
    };  
};

#endif /* bstree_h */

