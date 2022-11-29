//
// Created by User on 22/11/2022.
//

#ifndef EX1_AVLTREE_H
#define EX1_AVLTREE_H

#include <iostream>

template<class T, class Comparison>
class AVLTree {
private:
    //Tree fields
    struct BinNode {
        BinNode *m_right;
        BinNode *m_left;
        BinNode *m_father;
        int m_height;
        T m_data;
    };
    BinNode *m_root;
    BinNode *m_minValueNode; // in order to find the minimum value in tree in O(1)
    BinNode *m_maxValueNode; // in order to find the maximum value in tree in O(1)
    int m_size;
    Comparison comparisonFunction;

     //Node Functions
     BinNode *initNode(const T &data);

     BinNode *balanceTree(BinNode *node);

     BinNode *insertNode(BinNode *newNode, BinNode *currentNode, BinNode *father);

    template<class S>
    BinNode *findNode(BinNode *node, const S &data);

    BinNode *removeNode(BinNode *currentNode, BinNode *nodeToDelete);

    int getBalanceFactor(BinNode *node) const;

    int height(const BinNode *node) const;

    int findNewHeight(const BinNode *node) const;

    // Rotation Functions
    BinNode *leftLeftRotation(BinNode *node);

    BinNode *leftRightRotation(BinNode *node);

    BinNode *rightLeftRotation(BinNode *node);

    BinNode *rightRightRotation(BinNode *node);

    // Constructor, Destructor helper functions
    BinNode* copyNode(BinNode *node);

    void empty_aux(BinNode *node);

    BinNode* findMin(BinNode* node) const;

    BinNode* findMax(BinNode* node) const;

    int auxInOrder(T* array, BinNode* node, int size, int position);

    public:
    // Constructors, Destructor, Assignment
    AVLTree();

    // AVLTree(const AVLTree<T, Comparison> &tree);

    AVLTree &operator=(const AVLTree<T, Comparison> &tree);

    ~AVLTree();

    // Interface Functions
    void insert(const T &data);

    template<class S>
    BinNode * find(const S &data);

    template<class S>
    void remove(const S &data);

    int getHeight() const;

    int getSize() const;

    BinNode* getRoot() const;

    void emptyTree();

    bool isEmpty() const;

    void printH(BinNode *node, int space);

    void printD(BinNode *node, int space);

    T getMinValueInTree() const;

    T getMaxValueInTree() const;

    T* inOrderArray();


};

template<class T,class Comparison>
T* AVLTree<T, Comparison>::inOrderArray()
{
    T* array= (T*) malloc(m_size*sizeof(T*));
    auxInOrder(array, m_root, m_size, 0);
    return array;
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::auxInOrder(T*array, AVLTree<T, Comparison>::BinNode* node, int size, int position)
{
    if(node==nullptr){
        return position;
    }
    position = auxInOrder(array, node->m_left, size, position);
    if(position>=size){
        return position;
    }
    array[position]= node->m_data;
    position++;
    return auxInOrder(array, node->m_right, size, position);
}


template<class T, class Comparison>
AVLTree<T, Comparison>::AVLTree() : m_root(nullptr), m_minValueNode(nullptr), m_maxValueNode(nullptr), m_size(0) {
}

template<class T, class Comparison>
AVLTree<T, Comparison>::~AVLTree(){
    emptyTree();
}

template<class T, class Comparison>
AVLTree<T, Comparison>& AVLTree<T, Comparison>::operator=(const AVLTree<T, Comparison> &tree){
    // TODO: ADD CHECK IF SUCCEED BEFORE EMPTY
    if(&tree == this){
        return *this;
    }
    emptyTree();
    m_root = copyNode(m_root);
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size = tree.getSize();
    return *this;
}

//template<class T, class Comparison>
//AVLTree<T, Comparison>::AVLTree(const AVLTree<T, Comparison>& tree):m_root(nullptr), m_minValueNode(nullptr), m_maxValueNode(nullptr),
//                                                                    m_size(tree.getSize()){
//    // todo: check if can be added to the comprehension list
//    m_root = copyNode(m_root);
//    m_minValueNode = findMin(m_root);
//    m_maxValueNode = findMax(m_root);
//}


template<class T, class Comparison>
void AVLTree<T, Comparison>::insert(const T& data) {
    if (&data == nullptr) {
        return;
    }
    if (findNode(m_root, data) != nullptr) {
        std::cout << "throw NodeExists()";
    }

    auto *node = initNode(data);

    m_root = insertNode(node, m_root, nullptr);
    // update minimum and maximum tree nodes
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size++;
}

//template<class T, class Comparison>
//BinNode * AVLTree<T, Comparison>::find(const T& data){
//    BinNode* node = findNode(m_root, data);
//    if(node == nullptr){
//        return nullptr;
//    }
//    return node;
//}

template<class T, class Comparison>
template<class S>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::find(const S& data){
    BinNode* node = findNode(m_root, data);
    if(node == nullptr){
        return nullptr;
    }
    return node;
}

//template<class T, class Comparison>
//BinNode * AVLTree<T, Comparison>::find(int id){
//    BinNode* node = findNode(m_root, id);
//    if(node == nullptr){
//        return nullptr;
//    }
//    return node;
//}

template<class T, class Comparison>
template <class S>
void AVLTree<T, Comparison>::remove(const S& data) {
    if (isEmpty() || &data == nullptr) {
        return;
    }
    BinNode* node_to_remove = findNode(m_root, data);

    if (node_to_remove == nullptr) {
        std::cout << "throw NodeDoesntExist()";
    }

    m_root = removeNode(node_to_remove, m_root);
    // m_root = removeNode(m_root, node_to_remove);
    // update minimum and maximum tree nodes
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size--;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::empty_aux(AVLTree<T, Comparison>::BinNode* node) {
    if(node == nullptr){
        return;
    }

    if(node->m_left){
        empty_aux(node->m_left);
    }
    if(node->m_right){
        empty_aux(node->m_right);
    }
    delete node->m_data;
    delete node;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::emptyTree() {
    if(m_size > 0){
       // printD(m_root, 10);
        empty_aux(m_root);
        m_root = nullptr;
        m_minValueNode = nullptr;
        m_maxValueNode = nullptr;
        m_size = 0;
    }
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::getHeight()const{
    if (m_root == nullptr) {
        return 0;
    }
    return m_root->m_height;
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::getSize() const{
    return m_size;
}

template<class T, class Comparison>
bool AVLTree<T, Comparison>::isEmpty() const{
    return m_size == 0;
}

template <class T, class Comparison>
void AVLTree<T, Comparison>::printD(AVLTree<T, Comparison>::BinNode *node, int space){
    if(node==nullptr)
        return;
    space += 10;
    printD(node->m_right, space);
    std::cout << std::endl;
    for(int i= 10; i<space; i++){
        std::cout << " ";
    }
    std::cout << *node->m_data << "\n";
    printD(node->m_left, space);
}

template <class T, class Comparison>
void AVLTree<T, Comparison>::printH(AVLTree<T, Comparison>::BinNode *node, int space){
    if(node==nullptr)
        return;
    space += 10;
    printH(node->m_right, space);
    std::cout << std::endl;
    std::cout << *node->m_data << ": "<< node->getHeight() << "\n";
    printH(node->m_left, space);
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::getRoot() const {
    return m_root;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::initNode(const T &data) {
    BinNode* node = new BinNode();
    node->m_data=data;
    node->m_height =0;
    node->m_left = nullptr;
    node->m_right =nullptr;
    node->m_father = nullptr;
    return node;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::balanceTree(AVLTree<T, Comparison>::BinNode *node) {
    int balanceFactor = getBalanceFactor(node);
    int leftBalanceFactor = getBalanceFactor(node->m_left);
    int rightBalanceFactor = getBalanceFactor(node->m_right);

    // Left-Left imbalance
    if(balanceFactor > 1 && leftBalanceFactor > -1){
        return leftLeftRotation(node);
    }

        // Right-Right imbalance
    else if(balanceFactor < -1 && rightBalanceFactor < 1){
        return rightRightRotation(node);
    }

        // Left-Right imbalance
    else if(balanceFactor > 1 && leftBalanceFactor == -1){
        return leftRightRotation(node);
    }

        // Right-Left imbalance
    else if(balanceFactor < -1 && rightBalanceFactor == 1){
        return rightLeftRotation(node);
    }

    node->m_height = findNewHeight(node);
    return node;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::insertNode(AVLTree<T, Comparison>::BinNode  *newNode,
                                                                             AVLTree<T, Comparison>::BinNode *currentNode,
                                                                             AVLTree<T, Comparison>::BinNode *father){
    if (currentNode == nullptr) {
        newNode->m_father = father;
        return newNode;
    }
    if(comparisonFunction.lessThan(newNode->m_data, currentNode->m_data)){
        currentNode->m_left = insertNode(newNode, currentNode->m_left, currentNode);
    } else {
        currentNode->m_right = insertNode(newNode, currentNode->m_right, currentNode);
    }
    return balanceTree(currentNode);
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::findNewHeight(const AVLTree<T, Comparison>::BinNode *node) const {
    if(height(node->m_right) > height(node->m_left)){
        return height(node->m_right)+1;
    }
    return height(node->m_left)+1;
}

template<class T, class Comparison>
template <class S>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::findNode(AVLTree<T, Comparison>::BinNode *node,
                                                                           const S &data) {
    if(node == nullptr)
        return nullptr;
    if (comparisonFunction.equalTo(node->m_data, data)) {
        return node;
    } else {
        if(comparisonFunction.lessThan(node->m_data, data)){
            return findNode(node->m_right, data);
        } else {
            return findNode(node->m_left, data);
        }
    }
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::removeNode(AVLTree<T, Comparison>::BinNode *currentNode,
                                                                             AVLTree<T, Comparison>::BinNode *nodeToDelete){
    if (currentNode == nullptr) {
        return nullptr;
    }
    // Delete the node
    if (currentNode->m_data == nodeToDelete->m_data) {
        if (!nodeToDelete->m_right && !nodeToDelete->m_left) {
            // Leaf
            delete nodeToDelete;
            return nullptr;
        } else if (!nodeToDelete->m_right) {
            // Only left son
            BinNode* temp = nodeToDelete->m_left;
            nodeToDelete->m_data = temp->m_data;
            nodeToDelete->m_left = removeNode(nodeToDelete, nodeToDelete->m_left);

        } else if (!nodeToDelete->m_left) {
            // Only right son
            BinNode* temp = nodeToDelete->m_right;
            nodeToDelete->m_data = temp->m_data;
            nodeToDelete->m_right = removeNode(nodeToDelete, nodeToDelete->m_right);
        } else {
            // right and left son exist
            BinNode *temp = findMin(nodeToDelete->m_right);
            nodeToDelete->m_data = temp->m_data;
            nodeToDelete->m_right = removeNode(nodeToDelete, nodeToDelete->m_right);
        }
    }
    else{
        if (comparisonFunction.lessThan(currentNode->m_data,nodeToDelete->m_data)) {
            nodeToDelete->m_left = removeNode(currentNode, nodeToDelete->m_left);
        } else {
            nodeToDelete->m_right = removeNode(currentNode, nodeToDelete->m_right);
        }
    }

    nodeToDelete->m_height = findNewHeight(nodeToDelete);

    // Balancing the tree
    return balanceTree(nodeToDelete);
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::getBalanceFactor(BinNode *node) const {
    return node == nullptr ? -1 : (height(node->m_left) - height(node->m_right));
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::height(const BinNode* node) const{
    return node == nullptr ? -1 : node->m_height;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::leftLeftRotation(AVLTree<T, Comparison>::BinNode *node) {
    BinNode *leftSubtree = node->m_left;
    leftSubtree->m_father = node->m_father;
    node->m_father = leftSubtree;
    if(leftSubtree->m_right){
        (leftSubtree->m_right)->m_father = node;
    }
    node->m_left = node->m_father->m_right;
    (node->m_father)->m_right = node;
    node->m_height = findNewHeight(node);
    if(node->m_father) {
        (node->m_father)->m_height = findNewHeight(node->m_father);
    }
    return node->m_father;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::rightRightRotation(AVLTree<T, Comparison>::BinNode *node) {
    BinNode *subTreeRight = node->m_right;
    (node->m_right)->m_father = node->m_father;
    node->m_father = subTreeRight;
    node->m_right = node->m_father->m_left;
    if(node->m_right)
        (node->m_right)->m_father = node;
    (node->m_father)->m_left = node;

    node->m_height = findNewHeight(node);
    if(node->m_father){
        (node->m_father)->m_height = findNewHeight(node);
    }

    return node->m_father;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::rightLeftRotation(AVLTree<T, Comparison>::BinNode *node) {
    node->m_right = leftLeftRotation(node->m_right);
    return rightRightRotation(node);
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::leftRightRotation(AVLTree<T, Comparison>::BinNode *node) {
    node->m_left = rightRightRotation(node->m_left);
    return leftLeftRotation(node);
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::copyNode(AVLTree<T, Comparison>::BinNode* node) {
    if(node == nullptr){
        return nullptr;
    }
    BinNode* left = copyNode(node->m_left);
    BinNode* right = copyNode(node->m_right);

    BinNode* new_node = BinNode(node->m_data);
//    new_node->father = node->father;
    new_node->sm_left=left;
    if(new_node->m_left)
        (new_node->m_left)->m_father = new_node;
    new_node->m_right = right;
    if(new_node->m_right)
        (new_node->m_right)->m_father = new_node;
    new_node->m_height = findNewHeight(new_node);
    return new_node;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::findMin(AVLTree<T, Comparison>::BinNode* node) const{
    if (node == nullptr) {
        return nullptr;
    }
    if (!node->m_left) {
        return node;
    }

    return findMin(node->m_left);
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::findMax(AVLTree<T, Comparison>::BinNode* node) const{
    if (node == nullptr) {
        return nullptr;
    }
    if (node->m_right == nullptr) {
        return node;
    }

    return findMax(node->m_right);
}

template<class T, class Comparison>
T AVLTree<T, Comparison>::getMinValueInTree() const {
    return m_minValueNode->m_data;
}

template<class T, class Comparison>
T AVLTree<T, Comparison>::getMaxValueInTree() const {
    return m_maxValueNode->m_data;
}


#endif //EX1_AVLTREE_H