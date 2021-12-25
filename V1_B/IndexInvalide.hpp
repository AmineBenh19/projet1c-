#pragma once

#include <exception>
#include <cstring>
#include <string>


using namespace std;

class IndexInvalide : public exception {
    protected :
        string msg;
    public:
        IndexInvalide(string s) : msg(s) {}

        virtual const char *what() const noexcept override {
            return msg.c_str();

        }





};