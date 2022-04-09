// This code was sourced from Prof. Zi Bin Yang and all copyright and/or copyleft goes to him.

/** 
 * Prime checks.  
 * Used just to make sure the hash table length is prime.
 **/
#ifndef PrimeChecks_h
#define PrimeChecks_h
#include <iostream>


/**
 * Checks if n is prime.
 **/
bool is_prime(size_t n){
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;

    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (size_t i = 5; i * i <= n; i += 6){
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}


/**
 * Gets the next prime in the sequence.
 **/
size_t next_prime(size_t floor){
    if (floor < 2)
        return 2;
    if (floor < 3)
        return 3;

    size_t candidate = floor + 1;
    if (candidate % 2 == 0)
        candidate += 1;

    while (true){
        if (is_prime(candidate))
            return candidate;
        candidate += 2;
    }
}

# endif /* PrimeChecks_h */
