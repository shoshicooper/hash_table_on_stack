#include <iostream>
#include "SmallHashT.h"

// (c) 2022 Shoshi (Sharon) Cooper.  No duplication is permitted for commercial use.  Any significant changes made must be
// stated explicitly and the original source code, if used, must be available and credited to Shoshi (Sharon) Cooper.

template<class K, class V>
size_t SmallHash<K, V>::_lookup(K key, size_t hashval) const noexcept {
    size_t idx = hashval % _array_size, k = 0, count = 0;

    while (count < _array_size){
        if (_status[idx] != ACTIVE)
            return idx;
        else if (_keys[idx] == key && std::hash<K>()(key) == hashval)
            return idx;
        idx = (idx + k) % _array_size;
        k += 2;
        count++;
    }
    return _array_size;
}


template<class K, class V>
V& SmallHash<K, V>::get(K key) const {
    size_t idx = _lookup(key, std::hash<K>()(key));
    if (idx == _array_size || _status[idx] < 0)
        throw KeyError("Key not found");
    return _values[idx];
};

template<class K, class V>
V* SmallHash<K, V>::get_ptr(K& key) const noexcept{
    size_t idx = _lookup(key, std::hash<K>()(key));
    if (idx == _array_size || _status[idx] < 0)
        return nullptr;
    return &_values[idx];
};

template<class K, class V>
void SmallHash<K, V>::set(K key, V value){
    size_t idx = _lookup(key, std::hash<K>()(key));
    if (idx == _array_size)
        throw KeyError("Lookup error");
    size_t d_size = (_status[idx] < 0) ? 1: 0;

    _keys[idx] = key;
    _values[idx] = value;
    _status[idx] = ACTIVE;
    _used_in_table += d_size;
}

template<class K, class V>
void SmallHash<K, V>::discard(K key) noexcept {
    size_t idx = _lookup(key, std::hash<K>()(key));
    if (idx == _array_size || idx < 0)
        return;
    _status[idx] = DUMMY;
    _used_in_table--;
}


template<class K, class V>
void SmallHash<K, V>::clear(){
    for (size_t i = 0; i < _array_size; i++){
        _status[i] = EMPTY;
    }
    _used_in_table = 0;
}

