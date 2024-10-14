#ifndef EXCEPTONS_H
#define EXCEPTONS_H

#include <string>

class Except_log: public std::exception
{
private:
    std::string ex;
public:
    explicit Except_log(std::string e):ex{e} {}
    std::string ex_text() const
    {
        return ex;
    }
};

class Except_pass: public std::exception
{
private:
    std::string ex;
public:
    explicit Except_pass(std::string e):ex{e} {}
    std::string ex_text() const
    {
        return ex;
    }
};

class Except_log_pass_empty: public std::exception
{
private:
    std::string ex;
public:
    explicit Except_log_pass_empty(std::string e):ex{e} {}
    std::string ex_text() const
    {
        return ex;
    }
};

class Except_log_pass: public std::exception
{
private:
    std::string ex;
public:
    explicit Except_log_pass(std::string e):ex{e} {}
    std::string ex_text() const
    {
        return ex;
    }
};

class Except_not_correct_player: public std::exception
{
private:
    std::string ex;
public:
    explicit Except_not_correct_player(std::string e):ex{e} {}
    std::string ex_text() const
    {
        return ex;
    }
};


#endif // EXCEPTONS_H