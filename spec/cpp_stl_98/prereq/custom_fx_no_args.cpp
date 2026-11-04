#include "custom_fx_no_args.h"

custom_fx_no_args_t::custom_fx_no_args_t() {
}

std::string custom_fx_no_args_t::decode(std::string src) {
    return "_" + src + "_";
}

std::string custom_fx_no_args_t::encode(std::string src) {
    return src.substr(1, src.length() - 2);
}
