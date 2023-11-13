#ifndef Controller_h
#define Controller_h
#include "llist.h"
#include "bstree.h"
#include "rbtree.h"
#include "chasht.h"
//@libreries
//#include <ctime>
//#include <cstdlib>
#include <chrono>
#include <random>
//#include <thread>
#include <iostream>

using namespace std;
class Controller{
    
private: 
    int* Keys = new int [1000000];
    llist<int> list;
    bstree<int> binaryTree;
    rbtree<int> redBlackTree;
    chtable<int> hashTable = chtable<int>(1000000);
    
public:
    Controller();
    ~Controller();
    void shuffleArray(int);
    void menu();
    void insertList();
    void testListSearchs();
    void insertBTree();
    void testBTreeSearchs();
    void insertRBTree();
    void testRBTreeSearchs();
    void testHashTables();
    void insertHashTable();


};
#endif