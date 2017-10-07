#ifndef TREEMAP_H
#define TREEMAP_H

#include "tree.h"

template<typename Key, typename Value>
class KeyValuePair {
    
    public:
    
        const Key k;
        Value v;

        KeyValuePair(const Key & key);
    
        KeyValuePair(const Key & key, const Value & value);

        bool operator<(const KeyValuePair<Key,Value> & another) const;
    
    
};

//  ##  functions for KeyValuePair<Key, Value> defined below  ##  //

    template<typename Key, typename Value>
    KeyValuePair<Key,Value>::KeyValuePair(const Key & key):
    k(key){}

    template<typename Key, typename Value>
    KeyValuePair<Key,Value>::KeyValuePair(const Key & key, const Value & value):
    k(key),
    v(value){}

    template<typename Key,typename Value>
    bool KeyValuePair<Key,Value>::operator<(const KeyValuePair<Key,Value> & another) const{

        return k < another.k;
    }

//##################################################################//

template<typename Key, typename Value>
ostream & operator<< (ostream & o, const KeyValuePair<Key,Value> & kv){
    
    o << kv.k << "," << kv.v;
    
    return o;
}



template<typename Key, typename Value>
class TreeMap {
  
    private:
    
        BinarySearchTree<KeyValuePair<Key,Value> > tree;
    
    public:
    
        KeyValuePair<Key,Value> * insert(const Key & k, const Value & v) {
            return &( tree.insert( KeyValuePair<Key,Value>(k,v) )->data );
        }
    
        void write(ostream & o) const {
            tree.write(o);
        }

        KeyValuePair<Key, Value>* find(const Key & key);    
    
};

//  ##  functions for TreeMap<Key, Value> defined bellow  ##  //

    template<typename Key, typename Value>
    KeyValuePair<Key, Value>* TreeMap<Key, Value>::find(const Key & key){
        
        KeyValuePair<Key, Value> pair (key);
        TreeNode<KeyValuePair<Key, Value>>* node = tree.find(pair);

        if(!node) return nullptr;
        
        return &(node->data);
    }

//###############################################################//


// do not edit below this line

#endif
