/**
 * A Hash Table class that does not include the actual hash table itself.
 * Instead, it contains methods to help you to treat 3 fixed arrays as a 
 * functioning hash table.  So you create the arrays, and this class takes
 * care of all the syntax.
 * 
 * Uses the concept of split tables, used in the Python standard library
 * for their dictionaries.  Many thanks to Python creators for this.
 * 
 * A pointer to each of the arrays is passed into the constructor.  This is 
 * a raw pointer, not a smart pointer, because this entire class should not 
 * exist outside of the local scope.  It owns nothing.  It is a hollow shell
 * of a class that you use to organize a stack-allocated list.
 * 
 * Hash table is not resizable.
 * 
 * The idea is that you create stack-allocated fixed-length arrays, then 
 * use this class to do the syntax to treat them as a hash table.  Since 
 * everything is on the stack, that makes this a very fast hash table 
 * (albeit a very ephemeral one).
 *  
 **/

#ifndef SmallHash_h
#define SmallHash_h
#include <iostream>
#include <exception>
#include "Kerr.h"
#include "prime_checks.h"

/**
 * SmallHash Class Template
 * DO NOT heap allocate any pointers passed in the constructor!  
 * This object will NOT clean up after you!
 * 
 * This class owns nothing.
 * 
 **/
template<class K, class V>
class SmallHash {
    private:
        const int EMPTY = -1, DUMMY = -2, ACTIVE = 1;
        K* _keys;
        V* _values;
        int* _status;
        size_t _array_size;
        size_t _used_in_table;

        size_t _lookup(K key, size_t hashval) const noexcept;

    public:
        SmallHash(K* keysArr, V* valuesArr, int* statusArr, size_t arrSize):
            _keys(keysArr), _values(valuesArr), _status(statusArr), _array_size(arrSize){
                if (!is_prime(arrSize))
                    throw KeyError("Cannot create hash table.  array size must be prime.");
                clear();
        }
        void clear();
        V& get(K key) const;
        V* get_ptr(K& key) const noexcept;
        void set(K key, V value);
        bool contains(K key) const noexcept {return (get_ptr(key) != nullptr);}
        void discard(K key) noexcept;
        size_t size() const {return _used_in_table;}

        // brackets
        class GottenEntry{
            private:
                K _key;
                SmallHash* table;
            public:
                GottenEntry(K ky, SmallHash* hashtable): _key(ky), table(hashtable){};
                operator V(){return table->get(_key);}
                void operator=(const V& other){table->set(_key, other);}
        };
        GottenEntry operator[](K key){return GottenEntry(key, this);}
        friend class GottenEntry;
};

#endif