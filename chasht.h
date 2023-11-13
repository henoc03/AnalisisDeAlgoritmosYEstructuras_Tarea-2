//
//  chtable.h
//

#ifndef chtable_h
#define chtable_h

#include <list>
#include <vector>

using namespace std;
template <typename T>

// Tabla de dispersi�n con encadenamiento
class chtable {
public:

    chtable(){
    }
    // Constructor que especifica el tama�o de la tabla
    chtable(int sz) {
        size = sz;
        for (int i = 0; i < size;++i) {
            table.push_back(list<T>());
        }
    };
        
    // Destructor (borra la tabla)
    ~chtable() {
       for (unsigned i = 0; i < static_cast<unsigned>(size); ++i) {
            list<T> lista = table[i];
            lista.clear();
        }  
        table.clear();
    };
    
    // Inserta el elemento en la tabla
    void Insert(const T& k) {
        //static_cast<int>(k);
        unsigned i = static_cast<unsigned>(k) % static_cast<unsigned>(size);
        //i = static_cast<int>(i);
        table[i].push_front(k);
    };
    
    // Retorna un puntero a la llave o nullptr si no se encuentra
    T* Search(const T& k) {
        unsigned i = static_cast<unsigned>(k) % static_cast<unsigned>(size);
        list<T>& lista = table[i];

        for (auto ite = lista.begin(); ite != lista.end(); ++ite) {
            if (*ite == k) {
                return &(*ite);
            }
        }
        return nullptr;
    };
    
    
private:
    // N�mero de entradas en la tabla
    int size;
    
    // La tabla es un vector de listas de STL
    vector<list<T> > table;
};

#endif /* chtable_h */
