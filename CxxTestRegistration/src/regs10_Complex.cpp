

#include "reg_ids.h"
#include "reg_decls.h"

#include "Complex.h"


namespace regs10::fn {
    void init(std::vector<rtl::Function>& fns) {

        fns.push_back(rtl::type().function(cxx::fn::complex::getMagnitude::id)
                                 .build(&complex::getMagnitude));

        fns.push_back(rtl::type().function(cxx::fn::complex::setReal::id)
                                 .build(&complex::setReal));

        fns.push_back(rtl::type().function(cxx::fn::complex::setImaginary::id)
                                 .build(&complex::setImaginary));

        fns.push_back(rtl::type().function(cxx::fn::getComplexNumAsString::id)
                                 .build(&getComplexNumAsString));
    }
}

