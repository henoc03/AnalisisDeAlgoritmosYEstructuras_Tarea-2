//
//  llist.h
//

#ifndef llist_h
#define llist_h

// Nodos de la lista:
template <typename T>
class llnode
{
public:
    // Esta clase es para ser usada por otras clases. Por eficiencia los atributos se dejan publicos.
    T key;
    llnode<T> *prev, *next;
    
    // Constructor por omision.
    llnode() {
    };
    
    // Inicializacion de los datos miembro.
    llnode (const T& k, llnode<T> *w = nullptr, llnode<T> *y = nullptr):key(k), prev(w), next(y)  {};
    
    ~llnode() {
        this->next = nullptr;
        this->prev = nullptr;
        delete this->key;
    };
};

// Lista enlazada con nodo centinela:
template <typename T>
class llist
{
public:
    llnode<T> *nil;        // nodo centinela

    llist() {
        // Constructor (crea una lista vacia)
        nil = new llnode<T>(0, nullptr, nullptr);
        nil->next = nil;
        nil->prev = nil;
    };
    
    ~llist() {
        // Destructor (borra la lista)
    };
    
    void Insert(llnode<T>* x) {
        // Inserta el nodo x en la lista.  
        x->next = this->nil->next;
        this->nil->next->prev = x;
        this->nil->next = x;
        x->prev = this->nil;
    };

    llnode<T>* Search(const T& k) {
        // Busca la llave iterativamente. Si la encuentra, devuelve un apuntador al nodo que la contiene; sino devuelve el nodo nil (el centinela).
        llnode<T>* p = this->nil->next;
        while (p != nil && p->key != k) {
            p = p->next;
        }
        return p;
    };
        
    void Delete(llnode<T>* x) {
        llnode<int>* p = this->nil;
        while(p != this->nil && p != x) {
            p = p->next;
        }
        if (p != nil) {
            p->next->prev = p->prev;
            p->prev->next = p->next;
            delete p;
        }
       

    };    
};

#endif /* llist_h */
