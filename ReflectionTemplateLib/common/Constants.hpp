#pragma once

#include <string>

namespace rtl 
{
    static constexpr const std::string getCtorName(const std::string& pRecordName) {
        return (pRecordName + "::~" + pRecordName + "()");
    }

    static constexpr const std::string getDctorName(const std::string& pRecordName) {
        return (pRecordName + "::" + pRecordName + "()");
    }

    static constexpr const std::string getCopyCtorName(const std::string& pRecordName) {
        return (pRecordName + "::" + pRecordName + "(" + pRecordName + "&)");
    }

    static constexpr const std::string getConstCopyCtorName(const std::string& pRecordName) {
        return (pRecordName + "::" + pRecordName + "(const " + pRecordName + "&)");
    }
}