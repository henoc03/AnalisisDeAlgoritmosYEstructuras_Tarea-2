#include "controller.h"

Controller::Controller() {

}
Controller::~Controller(){

}

void Controller::menu(){
    system("cls");
    int option = 0;
    cout<<"========================================================="<<endl
        <<"        TAREA 2 ALGORITMOS Y ESTRUCTURAS DE DATOS        "<<endl
        <<"_________________________________________________________"<<endl
        <<"                         MENU                            "<<endl
        <<"                  1> Listas con nodo centinela           "<<endl
        <<"                  2> Arboles binarios                    "<<endl
        <<"                  3> Arboles Rojinegros                  "<<endl
        <<"                  4> Tablas de dispersion                "<<endl
        <<"                  5> Salir                               "<<endl
        <<"_________________________________________________________"<<endl
        <<"                  >> ";
    cin >>option;
    switch (option)
    {
    case 1:
        this->testListSearchs();
        this->menu();
        break;
    case 2:
        this->testBTreeSearchs();
        this->menu();
        break;
    case 3:
        this->testRBTreeSearchs();
    case 4:
        this->testHashTables();
        break;
    case 5:
        break;
    default:
        this->menu();
        break;
    }

}
void Controller::shuffleArray(int n){
    /*
    LLena el arreglo de llaves que luego son insertadas en las estructuras de datos
    n = 1 para un arreglo de llaves aleatorias en el rango de [0, 2000000]
    n = 0 para un arreglo con llaves ordenadas de [0 999999]
    */

    if (n == 1) {

        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        seed_seq seed_sequence{static_cast<unsigned int>(seed)};
        
        mt19937 gen(seed_sequence);
        
        uniform_int_distribution<> distribution(0, 1999999);

        for (int i = 0; i < 1000000; ++i) { 
            this->Keys[i] = distribution(gen);
        }
    }
    if (n == 0) {
        for (int i = 0; i < 1000000; ++i) {
            this->Keys[i] = i; 
        }
    }

    
}
void Controller::insertList(){
    for (int i = 0; i < 1000000; ++i) {
        llnode<int>* newNode = new llnode<int>(Keys[i]);
        this->list.Insert(newNode);
    }


}

void Controller::testListSearchs(){
    system("cls");
    int option = 0;
    cout<<"========================================================="<<endl
        <<"                   Listas con nodo centinela             "<<endl
        <<"_________________________________________________________"<<endl
        <<"               Seleccione el tipo de insercion           "<<endl
        <<"               1> Llaves aleatorias en [0, 2000000]      "<<endl
        <<"               2> Llaves ordenadas en [0, 999999]        "<<endl
        <<"               3> Salir                                  "<<endl
        <<"_________________________________________________________"<<endl
        <<"               >> ";
        cin >> option;
        switch (option)
        {
        case 1:
            shuffleArray(1);
            break;
        case 2:
            shuffleArray(0);
            break;
        case 3:
            menu();
            break;
        default:
            cout<<"       Opcion invalida, intenta de nuevo         "<<endl
                <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            this->testListSearchs();
        }

    this->insertList();

    int randKey = 0;
    int failed = 0;
    int reached = 0;

    const int secondsTime = 10;

    auto startTime = std::chrono::high_resolution_clock::now();

    while (true) {
        auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
        seed_seq seed_sequence{static_cast<unsigned int>(seed)};
        
        mt19937 gen(seed_sequence);
        
        uniform_int_distribution<> distribution(0, 1999999);

        //Corre durante 10s y luego se detiene;
        auto currentTime = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
        if (duration.count() >= secondsTime) {
            break;
        }
        
        randKey =  distribution(gen); 
        llnode<int>* found = this->list.Search(randKey);
        if (found != this->list.nil) {
            ++reached;
        }else {
            ++failed;
        }
    }
    cout<<"_________________________________________________________"<<endl
        << "Busquedas realizadas en 10s: "<<reached+failed<<endl
        << "Fallidas: "<<failed<<endl
        << "_________________________________________________________"<<endl
        << "borrando..."<<endl;
    this->list.~llist();
 
    cout <<"presione cualquier tecla para continuar"<<endl;
    cin.ignore();
    cin.ignore();
    this->testListSearchs();
}

void Controller::insertBTree() {
    for (int i = 0; i < 1000000; ++i) {
        bstnode<int>* newNode = new bstnode<int>(Keys[i]);
        this->binaryTree.Insert(newNode);
    }
}

void Controller::testBTreeSearchs(){
    system("cls");
    int option = 0;
    cout<<"========================================================="<<endl
        <<"                      Arboles binarios                   "<<endl
        <<"_________________________________________________________"<<endl
        <<"               Seleccione el tipo de insercion           "<<endl
        <<"               1> Llaves aleatorias en [0, 2000000]      "<<endl
        <<"               2> Llaves ordenadas en [0, 999999]        "<<endl
        <<"               3> Salir                                  "<<endl
        <<"_________________________________________________________"<<endl
        <<"               >> ";
        cin >> option;
        switch (option)
        {
        case 1: {
            shuffleArray(1);
            this->insertBTree();
            int randKey = 0;
            int failed = 0;
            int reached = 0;
            const int secondsTime = 10;
            auto startTime = std::chrono::high_resolution_clock::now();
            while (true) {
                auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                seed_seq seed_sequence{static_cast<unsigned int>(seed)};
                
                mt19937 gen(seed_sequence);
                
                uniform_int_distribution<> distribution(0, 1999999);

                
                //Corre durante 10s y luego se detiene;
                auto currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
                if (duration.count() >= secondsTime) {
                    break;
                }
                //2000000.1 da hasta 2000000 cerrado, pero 2000000.0 da hasta 1999999
                randKey =  distribution(gen);
                bstnode<int>* found = this->binaryTree.Search(this->binaryTree.root, randKey);
                if (found != nullptr) {
                    ++reached;
                }else {
                    ++failed;
                }
            }
            cout<<"_________________________________________________________"<<endl
                << "Busquedas realizadas en 10s: "<<reached+failed<<endl
                << "Fallidas: "<<failed<<endl
                << "_________________________________________________________"<<endl
                << "borrando..."<<endl;
            this->binaryTree.~bstree();
 
            cout <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            cin.ignore();
                    
        }
            break;
        case 2:{
            this->binaryTree.orderedTree();
            int randKey = 0;
            int failed = 0;
            int reached = 0;
            const int secondsTime = 10;
            auto startTime = std::chrono::high_resolution_clock::now();
            while (true) {
                auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                seed_seq seed_sequence{static_cast<unsigned int>(seed)};
                
                mt19937 gen(seed_sequence);
                
                uniform_int_distribution<> distribution(0, 1999999);

                //Corre durante 10s y luego se detiene;
                auto currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
                if (duration.count() >= secondsTime) {
                    break;
                }
                //2000000.1 da hasta 2000000 cerrado, pero 2000000.0 da hasta 1999999
                randKey =  distribution(gen);
                bstnode<int>* found = this->binaryTree.IterativeSearch(this->binaryTree.root, randKey);
                if (found != nullptr) {
                    ++reached;
                }else {
                    ++failed;
                }
            }
            cout<<"_________________________________________________________"<<endl
                << "Busquedas realizadas en 10s: "<<reached+failed<<endl
                << "Fallidas: "<<failed<<endl
                << "_________________________________________________________"<<endl
                << "borrando..."<<endl;
            this->binaryTree.~bstree();
 
            cout <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            cin.ignore();
        }
            break;
        case 3:
            menu();
            break;
        default:
            cout<<"       Opcion invalida, intenta de nuevo         "<<endl
                <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            this->testBTreeSearchs();
        }

    
    

    this->testBTreeSearchs();

}

void Controller::insertRBTree() {
    for (int i = 0; i < 1000000; ++i) {
        rbtnode<int>* newNode = new rbtnode<int>(Keys[i]);
        this->redBlackTree.Insert(newNode);
    }
}

void Controller::testRBTreeSearchs() {
    system("cls");
    int option = 0;
    cout<<"========================================================="<<endl
        <<"                      Arboles rojinegros                 "<<endl
        <<"_________________________________________________________"<<endl
        <<"               Seleccione el tipo de insercion           "<<endl
        <<"               1> Llaves aleatorias en [0, 2000000]      "<<endl
        <<"               2> Llaves ordenadas en [0, 999999]        "<<endl
        <<"               3> Salir                                  "<<endl
        <<"_________________________________________________________"<<endl
        <<"               >> ";
        cin >> option;
        switch (option)
        {
        case 1: {
            shuffleArray(1);
            this->insertRBTree();
            int randKey = 0;
            int failed = 0;
            int reached = 0;
            const int secondsTime = 10;
            auto startTime = std::chrono::high_resolution_clock::now();
            while (true) {
                auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                seed_seq seed_sequence{static_cast<unsigned int>(seed)};
                
                mt19937 gen(seed_sequence);
                
                uniform_int_distribution<> distribution(0, 1999999);
                
                //Corre durante 10s y luego se detiene;
                auto currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
                if (duration.count() >= secondsTime) {
                    break;
                }
                //2000000.1 da hasta 2000000 cerrado, pero 2000000.0 da hasta 1999999
                randKey =  distribution(gen);
                rbtnode<int>* found = this->redBlackTree.Search(this->redBlackTree.root, randKey);
                if (found != this->redBlackTree.nil) {
                    ++reached;
                }else {
                    ++failed;
                }
            }
            cout<<"_________________________________________________________"<<endl
                << "Busquedas realizadas en 10s: "<<reached+failed<<endl
                << "Fallidas: "<<failed<<endl
                << "_________________________________________________________"<<endl
                << "borrando..."<<endl;
            this->redBlackTree.~rbtree();
            //No delete function
 
            cout <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            cin.ignore();
                    
        }
            break;
        case 2:{
            shuffleArray(0);
            this->insertRBTree();
            int randKey = 0;
            int failed = 0;
            int reached = 0;
            const int secondsTime = 10;
            auto startTime = std::chrono::high_resolution_clock::now();
            while (true) {
                auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                seed_seq seed_sequence{static_cast<unsigned int>(seed)};
                
                mt19937 gen(seed_sequence);
                
                uniform_int_distribution<> distribution(0, 1999999);

                //Corre durante 10s y luego se detiene;
                auto currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
                if (duration.count() >= secondsTime) {
                    break;
                }
                
                randKey = distribution(gen); 
                rbtnode<int>* found = this->redBlackTree.Search(this->redBlackTree.root, randKey);
                if (found != this->redBlackTree.nil) {
                    ++reached;
                }else {
                    ++failed;
                }
            }
            cout<<"_________________________________________________________"<<endl
                << "Busquedas realizadas en 10s: "<<reached+failed<<endl
                << "Fallidas: "<<failed<<endl
                << "_________________________________________________________"<<endl
                << "borrando..."<<endl;
            this->redBlackTree.~rbtree();
 
            cout <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            cin.ignore();
        }
            break;
        case 3:
            menu();
            break;
        default:
            cout<<"       Opcion invalida, intenta de nuevo         "<<endl
                <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            this->testRBTreeSearchs();
        }

    
    

    this->testRBTreeSearchs();
}

void Controller::insertHashTable() {
    for (int i = 0; i < 1000000; ++i) {
        this->hashTable.Insert(Keys[i]);
    }
}

void Controller::testHashTables() {
    system("cls");
    int option = 0;
    cout<<"========================================================="<<endl
        <<"                         Tablas hash                     "<<endl
        <<"_________________________________________________________"<<endl
        <<"               Seleccione el tipo de insercion           "<<endl
        <<"               1> Llaves aleatorias en [0, 2000000]      "<<endl
        <<"               2> Llaves ordenadas en [0, 999999]        "<<endl
        <<"               3> Salir                                  "<<endl
        <<"_________________________________________________________"<<endl
        <<"               >> ";
        cin >> option;
        switch (option)
        {
        case 1: {
            shuffleArray(1);
            this->insertHashTable();
            int randKey = 0;
            int failed = 0;
            int reached = 0;
            const int secondsTime = 10;
            auto startTime = std::chrono::high_resolution_clock::now();
            while (true) {
                auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                seed_seq seed_sequence{static_cast<unsigned int>(seed)};
                
                mt19937 gen(seed_sequence);
                
                uniform_int_distribution<> distribution(0, 1999999);
                
                //Corre durante 10s y luego se detiene;
                auto currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
                if (duration.count() >= secondsTime) {
                    break;
                }
                //2000000.1 da hasta 2000000 cerrado, pero 2000000.0 da hasta 1999999
                randKey = distribution(gen);
                int* found = this->hashTable.Search(randKey);
                if (found != nullptr) {
                    ++reached;
                }else {
                    ++failed;
                }
            }
            cout<<"_________________________________________________________"<<endl
                << "Busquedas realizadas en 10s: "<<reached+failed<<endl
                << "Fallidas: "<<failed<<endl
                << "_________________________________________________________"<<endl
                << "borrando..."<<endl;
            this->hashTable.~chtable();
            //this->hashTable = chtable<int>(1000000);
 
            cout <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            cin.ignore();
                    
        }
            break;
        case 2:{
            shuffleArray(0);
            this->insertHashTable();
            int randKey = 0;
            int failed = 0;
            int reached = 0;
            const int secondsTime = 10;
            auto startTime = std::chrono::high_resolution_clock::now();
            while (true) {
                auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
                seed_seq seed_sequence{static_cast<unsigned int>(seed)};
                
                mt19937 gen(seed_sequence);
                
                uniform_int_distribution<> distribution(0, 1999999);
                
                //Corre durante 10s y luego se detiene;
                auto currentTime = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
                if (duration.count() >= secondsTime) {
                    break;
                }
                //2000000.1 da hasta 2000000 cerrado, pero 2000000.0 da hasta 1999999
                randKey = distribution(gen);
                int* found = this->hashTable.Search(randKey);
                if (found != nullptr) {
                    ++reached;
                }else {
                    ++failed;
                }
            }
            cout<<"_________________________________________________________"<<endl
                << "Busquedas realizadas en 10s: "<<reached+failed<<endl
                << "Fallidas: "<<failed<<endl
                << "_________________________________________________________"<<endl
                << "borrando..."<<endl;
            this->hashTable.~chtable();
           // this->hashTable = chtable<int>(1000000);
 
            cout <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            cin.ignore();
        }
            break;
        case 3:
            menu();
            break;
        default:
            cout<<"       Opcion invalida, intenta de nuevo         "<<endl
                <<"presione cualquier tecla para continuar"<<endl;
            cin.ignore();
            this->testHashTables();
        }

    
    

    this->testHashTables();
}