//
// Created by jerry on 2024/7/13.
//

#ifndef AVL_H
#define AVL_H
#include <iostream>
using namespace std;
#include <stack>
namespace mycode {
    template <class T>
    struct TreeNode {
        T _val;
        int _height = 0;
        TreeNode<T>* _left;
        TreeNode<T>* _right;
        explicit TreeNode(const T& val,TreeNode<T>* left = nullptr,\
            TreeNode<T>* right = nullptr):_val(val),_left(left),_right(right)\
    {}
    };
    template <class T>
    class AVLTree {
    public:
        int height(TreeNode<T>* node){return node == nullptr ? -1 : node->_height;}
        void updateHeight(TreeNode<T>* node) {
            node->_height = std::max(height(node->_left),height(node->_right)) + 1;
        }
        int balanceFactor(TreeNode<T>* node) {
            if(node == nullptr) return 0;
            return height(node->_left) - height(node->_right);
        }
        TreeNode<T>* rightRotate(TreeNode<T>* node) {//AVL树的右旋
            TreeNode<T>* child = node->_left;
            TreeNode<T>* grandChild = child->_right;
            //以child为根,将node进行右旋
            child->_right = node;
            node->_left = grandChild;
            //更新节点的高度
            updateHeight(node);
            updateHeight(child);
            return child;
        }
        TreeNode<T> *leftRotate(TreeNode<T> *node) {
            TreeNode<T>* child = node->_right;
            TreeNode<T>* grandChild = child->_left;
            // 以 child 为原点，将 node 向左旋转
            child->_left = node;
            node->_right = grandChild;
            // 更新节点高度
            updateHeight(node);
            updateHeight(child);
            // 返回旋转后子树的根节点
            return child;
        }
        /* 执行旋转操作，使该子树重新恢复平衡 */
        TreeNode<T>* rotate(TreeNode<T> *node) {
            // 获取节点 node 的平衡因子
            const int _balanceFactor = balanceFactor(node);
            // 左偏树
            if (_balanceFactor > 1) {
                if (balanceFactor(node->_left) >= 0) {
                    // 右旋
                    return rightRotate(node);
                } else {
                    // 先左旋后右旋
                    node->_left = leftRotate(node->_left);
                    return rightRotate(node);
                }
            }
            // 右偏树
            if (_balanceFactor < -1) {
                if (balanceFactor(node->_right) <= 0) {
                    // 左旋
                    return leftRotate(node);
                } else {
                    // 先右旋后左旋
                    node->_right = rightRotate(node->_right);
                    return leftRotate(node);
                }
            }
            // 平衡树，无须旋转，直接返回
            return node;
        }
        /////////////////////////////////////////////
        TreeNode<T>* insertHelper(TreeNode<T>* node,const T& val) {
            if(node == nullptr) return new TreeNode(val);
            if(val < node->_val)
                node->_left = insertHelper(node->_left,val);
            else if(val > node->_val)
                node->_right = insertHelper(node->_right,val);
            else
                return node;
            updateHeight(node);
            return rotate(node);
        }
        void insert(const T& val) {
            _head = insertHelper(_head,val);
        }
        TreeNode<T>* removeHelper(TreeNode<T>* node,const T& val,bool& flag) {
            if(node == nullptr)
                return nullptr;
            if(val < node->_val)
                node->_left = removeHelper(node->_left,val,flag);
            else if(val > node->_val)
                node->_right = removeHelper(node->_right,val,flag);
            else {
                if(node->_left == nullptr || node->_right == nullptr) {
                    TreeNode<T>* child = node->_left != nullptr ? node->_left : node->_right;
                    if(child == nullptr) {
                        delete node;
                        flag = true;
                        return nullptr;
                    }
                    else {
                        flag = true;
                        delete node;
                        node = child;
                    }
                }else {
                    TreeNode<T>* tmp = node->_right;
                    while(tmp->_left != nullptr) {
                        tmp = tmp->_left;
                    }
                    int tmpval = tmp->_val;
                    node->_right = removeHelper(node->_right,tmp->_val,flag);
                    node->_val = tmpval;
                }
            }
            updateHeight(node);
            node = rotate(node);
            return node;
        }
        bool remove(const T& val) {
            bool flag = false;
            _head = removeHelper(_head,val,flag);
            return flag;
        }
    private:
        TreeNode<T>* _head = nullptr;
    };
}
#endif //AVL_H
