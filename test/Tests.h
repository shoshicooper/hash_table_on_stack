#ifndef Tests_h
#define Tests_h
#include <iostream>
#include <vector>
#include <sstream>
#include <exception>
#include <tuple>

/**
 * (c) 2022 Shoshi (Sharon) Cooper.  No duplication is permitted for commercial use.  Any significant changes made must be
 * stated explicitly and the original source code, if used, must be available and credited to Shoshi (Sharon) Cooper.
 *
 * This is the group of tests and assertions that I wrote for myself so I
 * could properly test all my C++ code.
 * 
 * I wrote it before using the Google Tests.  Now, I use it as a supplement
 * to the google tests, since it sometimes has more information in the error
 * messages.
 * 
 **/

struct AssertionError : public std::exception
{
   std::string s;
   AssertionError(std::string ss) : s(ss) {}
   ~AssertionError() throw () {}
   const char* what() const throw() { return s.c_str(); }
};


template<typename AnyType>
struct Comparisons {
        AnyType expected, actual;
    private:
        std::string convert_to_string(AnyType item){
            std::stringstream mystream;
            mystream << item;
            return mystream.str();
        }
    public:
        std::string to_string_exp(){return convert_to_string(expected);}
        std::string to_string_act(){return convert_to_string(actual);}
        bool is_equal(){return expected == actual;}
        bool is_not_equal(){return expected != actual;}
        bool is_less_than(){return expected < actual;}
        bool is_greater_than(){return expected > actual;}
};




class Tests{
    public:
        // bool, string, int, double, etc.
        static void assertEqual(bool expected, bool actual, std::string msg="", 
            std::string test_name="");
        static void assertEqual(int expected, int actual, std::string msg="", 
            std::string test_name="");
        static void assertEqual(std::string expected, std::string actual, 
            std::string msg="", std::string test_name="");
        static void assertEqual(size_t expected, size_t actual, std::string msg="", 
            std::string test_name="");
        static void assertEqual(long expected, long actual, std::string msg="", 
            std::string test_name="");
        static void assertEqual(double expected, double actual, std::string msg="", 
            std::string test_name="");
        
        // Gives you a detailed error message on how/where the strings are different, if they are
        static void assertNoStringDifferences(std::string expected, std::string actual, std::string msg="", 
            std::string test_name="");
        static void assertStringNotEqual(std::string expected, std::string actual, std::string msg="", 
            std::string test_name="");

        // not equal
        static void assertNotEqual(bool expected, bool actual, std::string msg="", std::string test_name="");
        static void assertNotEqual(int expected, int actual, std::string msg="", std::string test_name="");
        static void assertNotEqual(std::string expected, std::string actual, std::string msg="", std::string test_name="");
        static void assertNotEqual(size_t expected, size_t actual, std::string msg="", std::string test_name="");
        static void assertNotEqual(long expected, long actual, std::string msg="", std::string test_name="");
        static void assertNotEqual(double expected, double actual, std::string msg="", std::string test_name="");


        // vectors
        static void assertVectorEqual(std::vector<std::string>& expected, std::vector<std::string>& actual, 
            std::string msg="", std::string test_name="");
        static void assertVectorEqual(std::vector<int>& expected, std::vector<int>& actual, 
            std::string msg="", std::string test_name="");
        static void assertVectorEqual(std::vector<double>& expected, std::vector<double>& actual, 
            std::string msg="", std::string test_name="");
        static void assertVectorEqual(std::vector<long>& expected, std::vector<long>& actual, 
            std::string msg="", std::string test_name="");
        static void assertVectorEqual(std::vector<size_t>& expected, std::vector<size_t>& actual, 
            std::string msg="", std::string test_name="");
        static void assertVectorEqual(std::vector<std::tuple<std::string, int>>& expected, std::vector<std::tuple<std::string, int>>& actual, 
            std::string msg="", std::string test_name="");

        template<typename T>
        static void compareIterablesFunc(T& expected, T& actual, std::string msg="", std::string test_name="");

        // These used to be private, but I decided it was more important to have access to them.
        static void _create_useful_error(struct ErrorData *error_info);
        static void _RaiseVectorError(std::string expected, std::string actual, 
            std::string message, std::string where_bad, std::string test_name,
            std::string user_message);
        static void assembleError(std::string expected, std::string actual, 
            std::string msg="", std::string test_name="", std::string other_message="");
        static double round_double(double the_double, int round_digits);

};

struct ErrorData{
    std::string expected, actual, message, test_name, user_added_message;    
};

#endif /* Tests_h */


