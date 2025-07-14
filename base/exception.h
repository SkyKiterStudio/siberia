#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include "common.h"
#include "dyn_array.h"
#include "str.h"

// 以下宏在使用时需要声明 Exception *ex;

#define TRY
#define THROW(msg) ex->raise(msg);
#define CATCH if (ex->is_error)
#define ERR_MSG (ex->get_error())

#define WARN(msg) ex->warn(msg);
#define CATCH_WARNINGS if (ex->is_warning)
#define WARNING_MSG (ex->get_warning())

namespace siberia::base {
    class Exception {
    private:
        DynamicArray<String> warnings;
        String error;
    public:
        bool is_error = false, is_warning = false;

        void raise(String msg) {
            error = msg;
            is_error = true;
        }

        void warn(String msg) {
            warnings.append(msg);
            is_warning = true;
        }

        String get_error() { return error; }
        DynamicArray<String> get_warning() { return warnings; }
    };
};

#endif