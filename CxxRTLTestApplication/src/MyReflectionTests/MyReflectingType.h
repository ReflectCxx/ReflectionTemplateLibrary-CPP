#pragma once

#include <string>

namespace my_type
{
    struct Person
    {
        const std::string name;

        Person(std::string& pName) : name(pName) {}

        Person(const std::string& pName) : name(pName) {}

        std::string getName() { return name; }

        std::string setTitle(std::string&&) { return "called_by_ref_rvalue"; }

        std::string updateAddress() { return "called_non_const_overload"; }

        std::string updateAddress() const { return "called_const_overload"; }

        std::string setProfile(std::string pProfStr) { return "called_by_val"; }

        std::string setProfile(std::string& pProfStr) { return "called_by_ref"; }

        std::string setOccupation(std::string&& pProfStr) { return "called_by_rvalue_ref"; }

        std::string setOccupation(const std::string& pProfStr) { return "called_by_ref_lvalue"; }

        static std::string getDefaults() { return "Person_defaults_returned"; }
    };


    namespace ext {

        static std::string sendString(std::string pString) { return ("sent_string_" + pString); }

        static std::string sendAsString(Person pPerson) { return "sent_string_lvalue_" + pPerson.name; }

        static std::string sendAsString(Person&& pPerson) { return "sent_string_rvalue_" + pPerson.name; }

        static std::string sendAsString(const char* pCString) { return "sent_string_literal_" + std::string(pCString); }
    }
}