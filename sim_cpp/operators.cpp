//
// Created by Ark on 5/22/2019.
//

#include "operators.h"

operators::operators() {
    gap_opts_num = 15;
    del_opts_num = 7;

    int i;
    gap_opts = new string[gap_opts_num];
    string temp_gap_opts[] = {
            "!", "%", "^", "&", "*",
            "-", "+","=", "|", ":",
            "<", ">", ",", "/", "?"
    };
    for(i = 0; i < gap_opts_num; i++) gap_opts[i] = temp_gap_opts[i];

    del_opts = new string[del_opts_num];
    string temp_del_opts[] = {
            "(", ")", "{", "}", "[", "]", ";"
    };
    for(i = 0; i < del_opts_num; i++) del_opts[i] = temp_del_opts[i];
}

operators::~operators() {
    delete[] gap_opts;
    delete[] del_opts;
}
