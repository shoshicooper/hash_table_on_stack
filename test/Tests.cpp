#include "Tests.h"
#include <iostream>
#include <sstream>
#include <functional>
#include <gtest/gtest.h>
#include <cmath>

// (c) 2022 Shoshi (Sharon) Cooper.  No duplication is permitted for commercial use.  Any significant changes made must be
// stated explicitly and the original source code, if used, must be available and credited to Shoshi (Sharon) Cooper.



void Tests::_create_useful_error(struct ErrorData *error_info){
    std::stringstream streamed;
    std::string test_name;
    streamed << "AssertionError:\n";

    streamed << "   " << "Test Name: " << error_info -> test_name << "\n";

    if (error_info -> message != ""){
        streamed << "   " << error_info -> message << "\n";
    }
    streamed << "   " << "Expected: " << error_info -> expected << "\n";
    streamed << "   " << "Actual: " << error_info -> actual << "\n";
    if (error_info -> user_added_message != ""){
        streamed << "   " << error_info -> user_added_message << "\n";
    }

    // throw the error
    ASSERT_TRUE(false) << streamed.str();
};


void Tests::assembleError(std::string expected, std::string actual, 
    std::string msg, std::string test_name, std::string other_message){
        // create the error data and send it off to create an error message
        struct ErrorData AssertionError = {expected, actual, 
                                           other_message, test_name, msg};
        _create_useful_error(&AssertionError);
}

void Tests::assertEqual(bool expected, bool actual, std::string msg, 
    std::string test_name){
        Comparisons<bool> compare = {expected, actual};
        if(!compare.is_equal()){
            assembleError(compare.to_string_exp(), compare.to_string_exp(), 
            msg, test_name);
        }
    }

void Tests::assertEqual(int expected, int actual, std::string msg, 
    std::string test_name){
        Comparisons<int> compare = {expected, actual};
        if(!compare.is_equal()){
            assembleError(compare.to_string_exp(), compare.to_string_exp(), 
            msg, test_name);
        }
    }

void Tests::assertEqual(double expected, double actual, std::string msg, 
    std::string test_name){
        Comparisons<double> compare = {expected, actual};
        if(!compare.is_equal()){
            assembleError(compare.to_string_exp(), compare.to_string_exp(), 
            msg, test_name);
        }
    }

void Tests::assertEqual(long expected, long actual, std::string msg, 
    std::string test_name){
        Comparisons<long> compare = {expected, actual};
        if(!compare.is_equal()){
            assembleError(compare.to_string_exp(), compare.to_string_exp(), 
            msg, test_name);
        }
    }

void Tests::assertEqual(size_t expected, size_t actual, std::string msg, 
    std::string test_name){
        Comparisons<size_t> compare = {expected, actual};
        if(!compare.is_equal()){
            assembleError(compare.to_string_exp(), compare.to_string_exp(), 
            msg, test_name);
        }
    }

void Tests::assertEqual(std::string expected, std::string actual, std::string msg, 
    std::string test_name){
        Comparisons<std::string> compare = {expected, actual};
        if(!compare.is_equal()){
            assembleError(compare.to_string_exp(), compare.to_string_exp(), 
            msg, test_name);
        }
    }


template<typename T>
void Tests::compareIterablesFunc(T& expected, T& actual, std::string msg, std::string test_name){
    std::stringstream act("{"), exp("{"), where_bad;
    size_t bigger = (expected.size() > actual.size()) ? expected.size(): actual.size();
    bool do_raise_error = false;

    for(size_t i=0; i<bigger; i++){
        std::string extra = (i + 1 == bigger) ? "": ", ";

        if(i >= expected.size() && actual.size() > i){
            do_raise_error = true;
            exp << "* *" << extra;
            act << actual[i] << extra;
            where_bad << i << extra;
        }
        else if (i >= actual.size() && expected.size() > i){
            do_raise_error = true;
            act << "* *" << extra;
            exp << expected[i] << extra;
            where_bad << i << extra;
        }
        else if (actual[i] == expected[i]){
            exp << expected[i] << extra;
            act << actual[i] << extra;
        }else{
            exp << "*" << expected[i] << "*" << extra;
            act << "*" << actual[i] << "*" << extra;
            where_bad << i << extra;
            do_raise_error = true;
        }
        i++;
    }

    if (do_raise_error == true){
        // create the error data and send it off to create an error message
        _RaiseVectorError(exp.str() + '}', act.str() + '}', 
            "", where_bad.str(), test_name, msg);
    }
}

void Tests::assertVectorEqual(std::vector<std::string>& expected, 
    std::vector<std::string>& actual, std::string msg, std::string test_name){
        compareIterablesFunc<>(expected, actual, msg, test_name);
    }

void Tests::assertVectorEqual(std::vector<int>& expected, 
    std::vector<int>& actual, std::string msg, std::string test_name){
        compareIterablesFunc<>(expected, actual, msg, test_name);
}   

void Tests::assertVectorEqual(std::vector<double>& expected, std::vector<double>& actual, 
    std::string msg, std::string test_name){
        compareIterablesFunc<>(expected, actual, msg, test_name);
}

void Tests::assertVectorEqual(std::vector<long>& expected, std::vector<long>& actual, 
    std::string msg, std::string test_name){
        compareIterablesFunc<>(expected, actual, msg, test_name);
}

void Tests::assertVectorEqual(std::vector<size_t>& expected, std::vector<size_t>& actual, 
    std::string msg, std::string test_name){
        compareIterablesFunc<>(expected, actual, msg, test_name);
}


void Tests::assertNoStringDifferences(std::string expected, std::string actual, std::string msg, 
    std::string test_name){
        compareIterablesFunc<>(expected, actual, msg, test_name);
    }


void Tests::assertNotEqual(bool expected, bool actual, std::string msg, std::string test_name){
    Comparisons<bool> compare = {expected, actual};
    if (!compare.is_not_equal()){
        assembleError(compare.to_string_exp(), compare.to_string_exp(), msg, test_name, "Should not have been equal");
    }
}

void Tests::assertNotEqual(int expected, int actual, std::string msg, std::string test_name){
    Comparisons<int> compare = {expected, actual};
    if (!compare.is_not_equal()){
        assembleError(compare.to_string_exp(), compare.to_string_exp(), msg, test_name, "Should not have been equal");
    }
}
void Tests::assertNotEqual(std::string expected, std::string actual, std::string msg, std::string test_name){
    Comparisons<std::string> compare = {expected, actual};
    if (!compare.is_not_equal()){
        assembleError(compare.to_string_exp(), compare.to_string_exp(), msg, test_name, "Should not have been equal");
    }
}

void Tests::assertNotEqual(size_t expected, size_t actual, std::string msg, std::string test_name){
    Comparisons<size_t> compare = {expected, actual};
    if (!compare.is_not_equal()){
        assembleError(compare.to_string_exp(), compare.to_string_exp(), msg, test_name, "Should not have been equal");
    }
}

void Tests::assertNotEqual(long expected, long actual, std::string msg, std::string test_name){
    Comparisons<long> compare = {expected, actual};
    if (!compare.is_not_equal()){
        assembleError(compare.to_string_exp(), compare.to_string_exp(), msg, test_name, "Should not have been equal");
    }
}

void Tests::assertNotEqual(double expected, double actual, std::string msg, std::string test_name){
    Comparisons<double> compare = {expected, actual};
    if (!compare.is_not_equal()){
        assembleError(compare.to_string_exp(), compare.to_string_exp(), msg, test_name, "Should not have been equal");
    }
}

// vectors
void Tests::_RaiseVectorError(std::string expected, std::string actual, std::string message, 
    std::string where_bad, std::string test_name, std::string user_message){
        struct ErrorData AssertionError;

        AssertionError.actual = actual;
        AssertionError.expected = expected;

        if(message != "" && where_bad != ""){
            message = message + "\n";
        }
        message += "Indices where Vectors did not match: " + where_bad;

        AssertionError.message = message;
        AssertionError.test_name = test_name;
        AssertionError.user_added_message = user_message;

        _create_useful_error(&AssertionError);
}

double Tests::round_double(double the_double, int round_digits){
    return std::floor(the_double*pow(10,round_digits)+0.5)/pow(10,round_digits);
}




