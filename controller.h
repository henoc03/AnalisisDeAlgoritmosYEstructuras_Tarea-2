#ifndef Controller_h
#define Controller_h
#include "llist.h"
#include "bstree.h"
//@libreries
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
class Controller{
    private: 
    int* Keys = new int [1000000];
    llist<int> list;
    bstree<int> binaryTree;
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


};
#endif