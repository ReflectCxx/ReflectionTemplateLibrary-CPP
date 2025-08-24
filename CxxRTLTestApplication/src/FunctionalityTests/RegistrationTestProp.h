#pragma once

#include <string>

namespace registration_test
{
    struct Person
    {
        const std::string name;

        Person(std::string& pName) : name("ref_" + pName) {}

        Person(const std::string& pName) : name(pName) {}

        std::string getName() { return name; }

        std::string setTitle(std::string&&) { return "called_by_ref_rvalue"; }

        std::string updateAddress() { return "called_non_const_overload"; }

        std::string updateAddress() const { return "called_const_overload"; }

        std::string setProfile(std::string pProfStr) { return "called_by_val"; }

        std::string setProfile(std::string& pProfStr) { return "called_by_ref"; }

        std::string setOccupation(std::string&& pProfStr) { return "called_by_rvalue_ref"; }

        std::string setOccupation(const std::string& pProfStr) { return "called_by_ref_lvalue"; }

        static std::string getDefaults() { return std::string(); }
    };


    namespace ext {

        static std::string sendAsString(const Person pPerson) { return "sendAsString_called."; }
    }
}