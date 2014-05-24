#include "red_black_tree.h"

/*===========================================================================*
 *                  Definition for internal functions                        *
 *===========================================================================*/
#define NODE_COLOR_RED      0
#define NODE_COLOR_BLACK    1

#define DIRECTION_LEFT      0
#define DIRECTION_RIGHT     1

/**
 * This function traverses all the nodes and releases the allocated memory space.
 *
 * @param pNull     The pointer to the dummy node.
 * @param curr      The pointer to the node currently traversed.
 * @param func      The pointer to the function which describes the memory deallocation strategy.
 */
void _RBTreeDeinit(RedBlackNode *pNull, RedBlackNode *curr, void (*func) (void*));


/**
 * This function makes the left rotation for the designated node "curr".
 * After rotation, "curr" will be the left child of its original right child.
 *
 * @param self      The pointer to the RedBlackTree structure.
 * @param curr      The pointer to the node which is to be rotated.
 */
void _RBTreeLeftRotate(RedBlackTree *self, RedBlackNode *curr);


/**
 * This function makes the right rotation for the designated node "curr".
 * After rotation, "curr" will be the right child of its original left child.
 *
 * @param self      The pointer to the RedBlackTree structure.
 * @param curr      The pointer to the node which is to be rotated.
 */
void _RBTreeRightRotate(RedBlackTree *self, RedBlackNode *curr);


/**
 * This function is called after node insertion to adjust the tree structure to maintain the red black attributes.
 *
 * @param self      The pointer to the RedBlackTree structure.
 * @param curr      The pointer to the node which is the origin for cascading adjustments.
 */
void _RBTreeInsertFixup(RedBlackTree *self, RedBlackNode *curr);


/**
 * This function is called after node deletion to adjust the tree structure to maintain the red black attributes.
 *
 * @param self      The pointer to the RedBlackTree structure.
 * @param curr      The pointer to the node which is the origin for cascading adjustments.
 */
void _RBTreeDeleteFixup(RedBlackTree *self, RedBlackNode *curr);


/**
 * This function locates the node containing minimal key within the subtree rooted by the
 * specified node.
 *
 * @param curr      The pointer to the root node for minimal key traversal.
 *
 * @return          Non-Sentinel: The pointer to the target node.
 *                  Sentinel    : The subtree is empty.
 */
RedBlackNode* _RBTreeMinimal(RedBlackTree *self, RedBlackNode *curr);


/**
 * This function locates the node containing maximal key within the subtree rooted by the
 * specified node.
 *
 * @param curr      The pointer to the root node for maximal key traversal.
 *
 * @return          Non-Sentinel: The pointer to the target node.
 *                  Sentinel    : The subtree is empty.
 */
RedBlackNode* _RBTreeMaximal(RedBlackTree *self, RedBlackNode *curr);


/**
 * This function locates the successor of the specified node.
 *
 * @param curr      The pointer to the node for successor search.
 *
 * @return          Non-Sentinel: The pointer to the target node.
 *                  Sentinel    : The size of the tree is less than two.
 */
RedBlackNode* _RBTreeSuccessor(RedBlackTree *self, RedBlackNode *curr);


/**
 * This function locates the predecessor of the specified node.
 *
 * @param curr      The pointer to the node for predecessor search.
 *
 * @return          Non-Sentinel: The pointer to the target node.
 *                  Sentinel    : The size of the tree is less than two.
 */
RedBlackNode* _RBTreePredecessor(RedBlackTree *self, RedBlackNode *curr);


/*===========================================================================*
 *               Implementation for exported functions                       *
 *===========================================================================*/
void RBTreeInit(RedBlackTree *self) {
    
    /* Create a dummy node representing the "NULL" pointer of the red black tree. */
    self->pNull = (RedBlackNode*)malloc(sizeof(RedBlackNode));
    self->pNull->bColor = NODE_COLOR_BLACK;
    self->pNull->pItem = NULL;
    self->pNull->pParent = self->pNull;
    self->pNull->pRight = self->pNull;
    self->pNull->pLeft = self->pNull;

    /* Let the initial root point to the dummy node. */
    self->pRoot = self->pNull;

    /* Let the function pointers pointing to the appropriate functions. */
    self->compare = RBTreeNodeCompare;
    self->destroy = RBTreeNodeDestroy;

    self->insert = RBTreeInsert;
    self->delete = RBTreeDelete;
    self->search = RBTreeSearch;

    self->maximum = RBTreeMaximum;
    self->minimum = RBTreeMinimum;
    self->successor = RBTreeSuccessor;
    self->predecessor = RBTreePredecessor;
    
    return;
}


void RBTreeDeinit(RedBlackTree *self) {

    _RBTreeDeinit(self->pNull, self->pRoot, self->destroy);
    free(self->pNull);
    return;
}


/**
 * RBTreeNodeCompare(): The default comparison strategy for red black node comparison.
 * Note: It considers source and target items as primitive data and compares their values directly.
 */
int RBTreeNodeCompare(const void *pSrc, const void *pTge) {
    
    if ((size_t)pSrc == (size_t)pTge)
        return 0;
    else {
        if ((size_t)pSrc > (size_t)pTge)
            return 1;
        else
            return -1;    
    }
}


/**
 * RBTreeNodeDestroy(): The default strategy for item deallocation.
 * Note: By default, the item is a primitive data, and thus no further operations are required.
 */
void RBTreeNodeDestroy(void *pItem) {

    return;
}


/*
 * RBTreeMinimum(): Locate the node containing the minimum key of the tree.
 */
RedBlackNode* RBTreeMinimum(RedBlackTree *self) {
    RedBlackNode *tge;

    tge = _RBTreeMinimal(self, self->pRoot);
    if (tge == self->pNull)
        tge = NULL;
    
    return tge;
}


/*
 * RBTreeMaximum(): Locate the node containing the maximum key of the tree.
 */
RedBlackNode* RBTreeMaximum(RedBlackTree *self) {
    RedBlackNode *tge;
    
    tge = _RBTreeMaximal(self, self->pRoot);
    if (tge == self->pNull)
        tge = NULL;
    
    return tge;
}


/*
 * RBTreeSuccessor(): Locate the successor of the designated node.
 */
RedBlackNode* RBTreeSuccessor(RedBlackTree *self, RedBlackNode *pCurNode) {
    RedBlackNode *tge;
    
    tge = _RBTreeSuccessor(self, pCurNode);
    if (tge == self->pNull)
        tge = NULL;
    
    return tge;    
}


/*
 * RBTreePredecessor(): Locate the predecessor of the designated node.
 */
RedBlackNode* RBTreePredecessor(RedBlackTree *self, RedBlackNode *pCurNode) {
    RedBlackNode *tge;
    
    tge = _RBTreePredecessor(self, pCurNode);
    if (tge == self->pNull)
        tge = NULL;
    
    return tge;
}


/**
 * RBTreeInsert(): Insert the new red black node to the appropriate location of the tree.
 * Note: Tree structure adjustment is necessary to maintain the attributes of red black tree.
 */
RedBlackNode* RBTreeInsert(RedBlackTree *self, void *pItem) {
    int             rc;    
    bool            direction;
    RedBlackNode    *new, *curr, *parent;

    /* Allocate the space for the new node. */
    new = (RedBlackNode*)malloc(sizeof(RedBlackNode));
    if (new == NULL)
        return new;

    new->pItem = pItem;
    new->bColor = NODE_COLOR_RED;
    new->pLeft = self->pNull;
    new->pRight = self->pNull;

    /* Search for the appropriate location for the new node. */
    curr = self->pRoot;
    parent = self->pNull;
    while (curr != self->pNull) {
        parent = curr;        
        rc = self->compare(pItem, curr->pItem);

        if (rc == 1) {
            curr = curr->pRight;
            direction = DIRECTION_RIGHT;        
        }        
        else if (rc == -1) {
            curr = curr->pLeft;
            direction = DIRECTION_LEFT;        
        }
        else {
            /* The conflict occurs. The new node will replace the existing one. */
            new->pLeft = curr->pLeft;
            new->pRight = curr->pRight;
            new->pParent = curr->pParent;
            new->bColor = curr->bColor;

            if (curr->pLeft != self->pNull)
                curr->pLeft->pParent = new;

            if (curr->pRight != self->pNull)
                curr->pRight->pParent = new;

            if (curr->pParent != self->pNull) {
                if (curr == curr->pParent->pLeft)
                    curr->pParent->pLeft = new;
                else
                    curr->pParent->pRight = new;            
            } else
                self->pRoot = new;

            self->destroy(curr->pItem);
            free(curr);
            return new;
        }
    }

    /* Arrivate at the appropriate location. */
    new->pParent = parent;
    if (parent != self->pNull) {
        if (direction == DIRECTION_LEFT)
            parent->pLeft = new;
        else      
            parent->pRight = new;
    } else
        self->pRoot = new;

    /* Maintain the attributes of red black tree. */
    _RBTreeInsertFixup(self, new);

    return new;
}


/**
 * RBTreeDelete(): Delete the specified red black node from the tree and adjust the tree structure.
 * Note: Tree structure adjustment is necessary to maintain the attributes of red black tree.
 */
void RBTreeDelete(RedBlackTree *self, RedBlackNode *pNode) {
    bool            bColor;
    RedBlackNode    *child, *succ;
    
    /* The specified node has no child. */
    if ((pNode->pLeft == self->pNull) && (pNode->pRight == self->pNull)) {
        if (pNode->pParent != self->pNull) {        
            if (pNode == pNode->pParent->pLeft)
                pNode->pParent->pLeft = self->pNull;
            else
                pNode->pParent->pRight = self->pNull;
        } else
            self->pRoot = self->pNull;
        
        bColor = pNode->bColor;
        child = self->pNull;
        child->pParent = pNode->pParent;        
        self->destroy(pNode->pItem);
        free(pNode);
    } else {
        /* The specified node has two children. */
        if ((pNode->pLeft != self->pNull) && (pNode->pRight != self->pNull)) {
            succ = _RBTreeSuccessor(self, pNode);
        
            child = succ->pLeft;
            if (child == self->pNull)
                child = succ->pRight;

            child->pParent = succ->pParent;

            if (succ == succ->pParent->pLeft)
                succ->pParent->pLeft = child;
            else
                succ->pParent->pRight = child;

            bColor = succ->bColor;
            self->destroy(pNode->pItem);
            pNode->pItem = succ->pItem;
            free(succ);
        } 
        /* The specified node has one child. */
        else {
            child = pNode->pLeft;
            if (child == self->pNull)
                child = pNode->pRight;

            child->pParent = pNode->pParent;

            if (pNode->pParent != self->pNull) {
                if (pNode == pNode->pParent->pLeft)
                    pNode->pParent->pLeft = child;
                else
                    pNode->pParent->pRight = child;
            } else
                self->pRoot = child;
            
            bColor = pNode->bColor;
            self->destroy(pNode->pItem);
            free(pNode);
        }
    }

    /* Maintain the attributes of red black tree. */
        
    if (bColor == NODE_COLOR_BLACK)
        _RBTreeDeleteFixup(self, child);
    
    return;
}


/*
 * RBTreeSearch(): Check whethere the tree has the designated item.
 */
bool RBTreeSearch(RedBlackTree *self, void *pItem) {
    int             rc;
    RedBlackNode    *curr;    
    
    curr = self->pRoot;
    while (curr != self->pNull) {
        rc = self->compare(pItem, curr->pItem);
        if (rc == 0)
            return true;
        else {
            if (rc > 0)
                curr = curr->pRight;
            else
                curr = curr->pLeft;
        }    
    }

    return false;
}


/*===========================================================================*
 *               Implementation for internal functions                       *
 *===========================================================================*/
void _RBTreeDeinit(RedBlackNode *pNull, RedBlackNode *curr, void (*func) (void*)) {

    if (curr != pNull) {
        _RBTreeDeinit(pNull, curr->pLeft, func);
        _RBTreeDeinit(pNull, curr->pRight, func);
        func(curr->pItem);
        free(curr);
    }

    return;
}


void _RBTreeLeftRotate(RedBlackTree *self, RedBlackNode *curr) {
    RedBlackNode *child;

    child = curr->pRight;

    /* Let "curr" handle the left child of its original right child, and
       the left child should point to "curr" if it is not dummy node. */    
    curr->pRight = child->pLeft;
    if (child->pLeft != self->pNull)
        child->pLeft->pParent = curr;

    /* Let "curr"'s original right child point to "curr"'s parent,
       and "curr"'s parent should point to the original right child if the parent is not dummy node. */
    child->pParent = curr->pParent;
    if (curr->pParent != self->pNull) {
        if (curr == curr->pParent->pLeft)
            curr->pParent->pLeft = child;
        else
            curr->pParent->pRight = child;
    } else {
        self->pRoot = child;
    }

    /* Adjust the direct relation between "curr" and its original right child. */
    curr->pParent = child;
    child->pLeft = curr;

    return;
}


void _RBTreeRightRotate(RedBlackTree *self, RedBlackNode *curr) {
    RedBlackNode *child;

    child = curr->pLeft;

    /* Let "curr" handle the right child of its original left child, 
       and the right child should point to "curr" if it is not dummy node. */
    curr->pLeft = child->pRight;
    if (child->pRight != self->pNull)
        child->pRight->pParent = curr;

    /* Let "curr"'s original left child point to "curr"'s parent,
       and "curr"'s parent should point to the original left child if it is not dummy node. */
    child->pParent = curr->pParent;
    if (curr->pParent != self->pNull) {
        if (curr == curr->pParent->pLeft)
            curr->pParent->pLeft = child;
        else
            curr->pParent->pRight = child;
    } else {
        self->pRoot = child;
    }

    /* Adjust the direction relation between "curr" and its original left child. */
    curr->pParent = child;
    child->pRight = curr;

    return;
}


void _RBTreeInsertFixup(RedBlackTree *self, RedBlackNode *curr) {
    RedBlackNode *uncle;    
    
    while (curr->pParent->bColor == NODE_COLOR_RED) {
        /* "curr"'s parent is its grand parent's left child. */        
        if (curr->pParent == curr->pParent->pParent->pLeft) {
            uncle = curr->pParent->pParent->pRight;            
        
            /* Case 1: The color of uncle node is also red. */            
            if (uncle->bColor == NODE_COLOR_RED) {
                curr->pParent->bColor = NODE_COLOR_BLACK;
                uncle->bColor = NODE_COLOR_BLACK;
                curr->pParent->pParent->bColor = NODE_COLOR_RED;                
                curr = curr->pParent->pParent;
            } else {
                /* Case 2: The color of uncle node is black, and "curr" is its parent's right child. */
                if (curr == curr->pParent->pRight) {
                    curr = curr->pParent;
                    _RBTreeLeftRotate(self, curr);                       
                }
                /* Case 3: The color of uncle node is black, and "curr" is its parent's left child. */
                curr->pParent->bColor = NODE_COLOR_BLACK;
                curr->pParent->pParent->bColor = NODE_COLOR_RED;
                _RBTreeRightRotate(self, curr->pParent->pParent);
            }
        } 
        /* "curr"'s parent is its grand parent's right child. */
        else {
            uncle = curr->pParent->pParent->pLeft;

            /* Case 1: The color of uncle node is also red. */    
            if (uncle->bColor == NODE_COLOR_RED) {
                curr->pParent->bColor = NODE_COLOR_BLACK;
                uncle->bColor = NODE_COLOR_BLACK;
                curr->pParent->pParent->bColor = NODE_COLOR_RED;
                curr = curr->pParent->pParent;
            } else {
                /* Case 2: The color of uncle node is black, and "curr" is its parent's left child. */
                if (curr == curr->pParent->pLeft) {
                    curr = curr->pParent;
                    _RBTreeRightRotate(self, curr);
                }
                /* Case 3: The color of uncle node is black, and "curr" is its parent's right child. */
                curr->pParent->bColor = NODE_COLOR_BLACK;
                curr->pParent->pParent->bColor = NODE_COLOR_RED;
                _RBTreeLeftRotate(self, curr->pParent->pParent);
            }
        }
    }

    self->pRoot->bColor = NODE_COLOR_BLACK;
    return;
}


void _RBTreeDeleteFixup(RedBlackTree *self, RedBlackNode *curr) {
    RedBlackNode *brother;

    while ((curr != self->pRoot) && (curr->bColor == NODE_COLOR_BLACK)) {
        /* "curr" is its parent's left child. */        
        if (curr == curr->pParent->pLeft) {    
            brother = curr->pParent->pRight;
            
            /* Case 1: The color of brother node is red. */
            if (brother->bColor == NODE_COLOR_RED) {
                brother->bColor = NODE_COLOR_BLACK;
                curr->pParent->bColor = NODE_COLOR_RED;
                _RBTreeLeftRotate(self, curr->pParent);
                brother = curr->pParent->pRight;
            }
            /* Case 2: The color of brother node is black, and both of its children are also black. */
            if ((brother->pLeft->bColor == NODE_COLOR_BLACK) && (brother->pRight->bColor == NODE_COLOR_BLACK)) {
                brother->bColor = NODE_COLOR_RED;
                curr = curr->pParent;
            } else {
                /* Case 3: The color of brother node is black. Its left child is red, and its right child is black. */
                if (brother->pRight->bColor == NODE_COLOR_BLACK) {                
                    brother->pLeft->bColor = NODE_COLOR_BLACK;
                    brother->bColor = NODE_COLOR_RED;
                    _RBTreeRightRotate(self, brother);            
                    brother = curr->pParent->pRight;
                }
                /* Case 4: The color of brother node is black, and its right child is red. */
                brother->bColor = curr->pParent->bColor;
                curr->pParent->bColor = NODE_COLOR_BLACK;
                brother->pRight->bColor = NODE_COLOR_BLACK;
                _RBTreeLeftRotate(self, curr->pParent);
                curr = self->pRoot;
            }           
        }
        /* "curr" is its parent's right child. */
        else {
            brother = curr->pParent->pLeft;
            
            /* Case 1: The color of brother node is red. */
            if (brother->bColor == NODE_COLOR_RED) {
                brother->bColor = NODE_COLOR_BLACK;
                curr->pParent->bColor = NODE_COLOR_RED;
                _RBTreeRightRotate(self, curr->pParent);
                brother = curr->pParent->pLeft;
            }
            /* Case 2: The color of brother node is black, and both of its children are also black. */
            if ((brother->pLeft->bColor == NODE_COLOR_BLACK) && (brother->pRight->bColor == NODE_COLOR_BLACK)) {
                brother->bColor = NODE_COLOR_RED;
                curr = curr->pParent;
            } else {
                /* Case 3: The color of brother node is black. Its right child is red, and its left child is black. */
                if (brother->pLeft->bColor == NODE_COLOR_BLACK) {                
                    brother->pRight->bColor = NODE_COLOR_BLACK;
                    brother->bColor = NODE_COLOR_RED;
                    _RBTreeLeftRotate(self, brother);            
                    brother = curr->pParent->pLeft;
                }
                /* Case 4: The color of brother node is black, and its right child is red. */
                brother->bColor = curr->pParent->bColor;
                curr->pParent->bColor = NODE_COLOR_BLACK;
                brother->pLeft->bColor = NODE_COLOR_BLACK;
                _RBTreeRightRotate(self, curr->pParent);
                curr = self->pRoot;
            }         
        }
    }

    curr->bColor = NODE_COLOR_BLACK;
    return;
}


RedBlackNode* _RBTreeMinimal(RedBlackTree *self, RedBlackNode *curr) {
    RedBlackNode *parent;
    
    parent = self->pNull;
    while (curr != self->pNull) {
        parent = curr;
        curr = curr->pLeft;
    }
    
    return parent;
}


RedBlackNode* _RBTreeMaximal(RedBlackTree *self, RedBlackNode *curr) {
    RedBlackNode *parent;
    
    parent = self->pNull;
    while (curr != self->pNull) {
        parent = curr;
        curr = curr->pRight;
    }

    return parent;
}


RedBlackNode* _RBTreePredecessor(RedBlackTree *self, RedBlackNode *curr) {

    if (curr != self->pNull) {
        /* Case 1: The maximal node of the non-empty left subtree. */
        if (curr->pLeft != self->pNull)
            curr = _RBTreeMaximal(self, curr->pLeft);
        
        /* Case 2: The ancestor which considers the designated node as the minimal node of 
           its right subtree. */
        else {
            while ((curr->pParent != self->pNull) && (curr == curr->pParent->pLeft)) 
                curr = curr->pParent;
            curr = curr->pParent;
        }
    }

    return curr;
}


RedBlackNode* _RBTreeSuccessor(RedBlackTree *self, RedBlackNode *curr) {

    if (curr != self->pNull) {
        /* Case 1: The minimal node of the non-empty right subtree. */
        if (curr->pRight != self->pNull)
            curr = _RBTreeMinimal(self, curr->pRight);
    
        /* Case 2: The ancestor which considers the designated node as the maximal node of
           its left subtree. */
        else {
            while ((curr->pParent != self->pNull) && (curr == curr->pParent->pRight))
                curr = curr->pParent;
            curr = curr->pParent;
        }
    }

    return curr;
}
