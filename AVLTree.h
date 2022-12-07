#ifndef EX1_AVLTREE_H
#define EX1_AVLTREE_H

#include <iostream>

template<class T, class Comparison>
class AVLTree {
public:
    struct BinNode {
        BinNode *m_right;
        BinNode *m_left;
        BinNode *m_father;
        int m_height;
        T m_data;
    };

    // Constructors, Destructor, Assignment
    /**
     * C'tor of the AVLTree, creates and empty tree
     */
    AVLTree();


    /**
     * opertor= for AVLTree
     * copies the given tree to this tree
     * @param tree tree to be assigned to this one
     * @return new AVLTree
     */
    AVLTree &operator=(const AVLTree<T, Comparison> &tree);

    /**
     * destructor of tree, remove and delete every node in the tree
     */
    ~AVLTree();

    // Interface Functions

    /**
     * The function inserts a new value to tree, maintains the order and
     * the height of every node.
     * Updates the minimum and the maximum of the tree when needed.
     * @param data a value to insert to the tree
     */
    void insert(T data);

    /**
     * Finds and returns the node that contains the given data in the tree
     * return nullptr if not exists
     * @tparam S type of the given data
     * @param data data to find
     * @return
     */
    template<class S>
    BinNode * find(const S &data);

    /**
     * remove the node that contains the given data
     * @tparam S type of the given data
     * @param data data to find and remove its node
     */
    template<class S>
    void remove(const S &data);

    /**
     * @return the number of elements in the tree
     */
    int getSize() const;

    /**
     * @return the root of the tree
     */
    BinNode* getRoot() const;

    /**
     * remove and delete all the nodes in the tree
     */
    void emptyTree();

    /**
     * @return true if there aren't any elements in the tree, else false
     */
    bool isEmpty() const;

    void printD(BinNode *node, int space);

    /**
     * @return the minimum value in the tree (according to the sort function of the tree)
     */
    T getMinValueInTree() const;

    /**
     * @return  the maximum value in the tree (according to the sort function of the tree)
     */
    T getMaxValueInTree() const;

    /**
     * Creates a new array that sorted according to the sort function of the tree -
     * go over the tree by inorder traversal
     * @return the new array
     */
    T* inOrderArray();

    /**
     * helper function of inOrderArray that recursively do the inorder traversal
     * @param array an empty array to save the result to it
     * @param node the current node the recursion goes over it in this round
     * @param size the size of the array
     * @param position the position in the array to where the next new data should be inserted to
     * @return
     */
    int auxInOrder(T* array, BinNode* node, int size, int position);

    /**
      * creates a new node with the given data
      * @param data
      * @return the new noed
      */
    static BinNode *initNode(T data);

    void setRoot(AVLTree<T, Comparison>::BinNode* newRoot);


private:
    //Tree fields
    BinNode *m_root;
    BinNode *m_minValueNode; // in order to find the minimum value in tree in O(1)
    BinNode *m_maxValueNode; // in order to find the maximum value in tree in O(1)
    int m_size;

     //Node Functions

     /**
      * the function does the needed rotations in order to maintain the tree as a AVL tree
      * @param node
      * @return
      */
     BinNode *balanceTree(BinNode *node);

     /**
      * insert a new node to the tree
      * @param newNode node to add to tree
      * @param currentNode the node from which the newNode is sought
      * @param father the father node of the current node
      * @return the next node to search from
      */
     BinNode *insertNode(BinNode *newNode, BinNode *currentNode, BinNode *father);

    /**
     * remove a node from the tree
     * @param currentNode the node from which the newNode is sought
     * @param nodeToDelete the node that should be found and deleted
     * @return the next node to search from
     */
    BinNode *removeNode(BinNode *currentNode, BinNode *nodeToDelete);

     /**
      * Helper function of find, recursively does the search
      * @tparam S the type of the data that should be found
      * @param node the node from which the newNode is sought
      * @param data the data that should be found
      * @return the next node to search from
      */
    template<class S>
    BinNode *findNode(BinNode *node, const S &data);

    /**
     * @param node
     * @return the height's difference of the given node
     */
    int getBalanceFactor(BinNode *node) const;

    /**
     * @param node
     * @return the height of the given node
     */
    int height(const BinNode *node) const;

    /**
     * find the new height of node according to its sons nodes
     * @param node
     * @return the new height
     */
    int findNewHeight(const BinNode *node) const;

    // Rotation Functions
    BinNode *leftLeftRotation(BinNode *node);

    BinNode *leftRightRotation(BinNode *node);

    BinNode *rightLeftRotation(BinNode *node);

    BinNode *rightRightRotation(BinNode *node);

    // Constructor, Destructor helper functions
    BinNode* copyNode(BinNode *node);

    /**
     * helper function for emptyTree function
     * @param node from which to do the removal and deletion
     */
    void emptyAux(BinNode *node);


    // finds the minimum/ maximum values in the sub-tree starts from node
    // (according to the tree's sorted function)
    BinNode* findMin(BinNode* node) const;

    BinNode* findMax(BinNode* node) const;

};


// Functions implementation

template<class T,class Comparison>
void AVLTree<T, Comparison>::setRoot(AVLTree<T, Comparison>::BinNode* newRoot)
{
    this->m_root = newRoot;
}

template<class T,class Comparison>
T* AVLTree<T, Comparison>::inOrderArray()
{
    T* array = new T[m_size];
    auxInOrder(array, m_root, m_size, 0);
    return array;
}

template<class T, class Comparison>
int AVLTree<T, Comparison>::auxInOrder(T* array, AVLTree<T, Comparison>::BinNode* node, int size, int position)
{
    if(node==nullptr){
        return position;
    }
    position = auxInOrder(array, node->m_left, size, position);
    if(position>=size){
        return position;
    }

    *(array+position)= node->m_data;
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

template<class T, class Comparison>
void AVLTree<T, Comparison>::insert(T data) {
    if (&data == nullptr) {
        return;
    }
    if (findNode(m_root, data) != nullptr) {
        return;
    }

    auto *node = initNode(data);

    m_root = insertNode(node, m_root, nullptr);
    // update minimum and maximum tree nodes
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size++;
}

template<class T, class Comparison>
template<class S>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::find(const S& data){
    BinNode* node = findNode(m_root, data);
    if(node == nullptr){
        return nullptr;
    }
    return node;
}

template<class T, class Comparison>
template <class S>
void AVLTree<T, Comparison>::remove(const S& data) {
    if (isEmpty() || &data == nullptr) {
        return;
    }
    BinNode* node_to_remove = findNode(m_root, data);

    if (node_to_remove == nullptr) {
        return;
    }

    // call the recursive function
    m_root = removeNode(node_to_remove, m_root);
    // update minimum and maximum tree nodes
    m_minValueNode = findMin(m_root);
    m_maxValueNode = findMax(m_root);
    m_size--;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::emptyAux(AVLTree<T, Comparison>::BinNode* node) {
    if(node == nullptr){
        return;
    }

    if(node->m_left){
        emptyAux(node->m_left);
    }
    if(node->m_right){
        emptyAux(node->m_right);
    }

    delete node;
}

template<class T, class Comparison>
void AVLTree<T, Comparison>::emptyTree() {
    if(m_size > 0){
        emptyAux(m_root);
        m_root = nullptr;
        m_minValueNode = nullptr;
        m_maxValueNode = nullptr;
        m_size = 0;
    }
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

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::getRoot() const {
    return m_root;
}

template<class T, class Comparison>
typename AVLTree<T, Comparison>::BinNode *AVLTree<T, Comparison>::initNode(T data) {
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
    if(Comparison::lessThan(newNode->m_data, currentNode->m_data)){
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
    if (Comparison::equalTo(node->m_data, data)) {
        return node;
    } else {
        if(Comparison::lessThan(node->m_data, data)){
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
        if (Comparison::lessThan(currentNode->m_data,nodeToDelete->m_data)) {
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