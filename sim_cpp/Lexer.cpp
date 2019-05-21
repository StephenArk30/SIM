//
// Created by Ark on 2019/5/17.
//
#include "Lexer.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <map>

Lexer::Lexer(const string& filename) {
    kw = new keyword();
    ifile.open(filename + ".c");
    ofile.open(filename + "_output.c");
}

Lexer::~Lexer() {
    delete(kw);
    ifile.close();
    ofile.close();
}

void Lexer::analyse() {
    string line;
    int line_num = 1;
    bool inComment = false;
    while (getline(ifile, line)) {
        cout << line_num++ << ' ' << line << endl;
        if(inComment) inComment = judgeCommentEnd(line);
        if(!inComment) {
            inComment = judgeCommentStart(line);
            line = preprocessing(line); // preprocessing
            line = replace_keyword(line); // replace keyword
            cout << line << endl;
            if (line.length() > 0 && line != "" && line != "\r" && line != "\n")
                ofile << line << endl;
        }
    }
}

string Lexer::replace_keyword(const string &line) {
    if(line.length() == 0)
        return line;
    int i, type;
    string pattern, replace_str, ret, segment;
    ret = "";
    stringstream linestream(line);
    bool flag;
    while (linestream >> segment) {
        for (i = 0; i < 32; i++) {
            // get keyword type
            type = kw->type[i];
            // get suffix start index and end index
            // match keywords[i] + suffix[j]
            pattern = kw->keywords[i] + kw->suffix[type];
            if (regex_match(segment, regex(pattern))) {
                // replace with $keyword, keyword_name$
                replace_str = "$$keyword, " + kw->keywords[i] + "$$";
                segment = (regex_replace(segment, regex(kw->keywords[i]), replace_str) + " ");
                break;
            }
        }
        ret += (segment + " ");
    }
    return ret;
}

string Lexer::preprocessing(const string &line) {
    if(line.length() == 0)
        return line;
    if(line[0] == '/' && line[1] == '/') return ""; // delete comment line
    // add "define" macro into map
    string ret = line;
    ret = regex_replace(ret, regex("\\("), " ( ");
    ret = regex_replace(ret, regex("\\)"), " ) ");
    ret = regex_replace(ret, regex("\\{"), " { ");
    ret = regex_replace(ret, regex("\\}"), " } ");
    ret = regex_replace(ret, regex("\\["), " [");
    ret = regex_replace(ret, regex("\\]"), "] ");
    ret = regex_replace(ret, regex(";"), "; ");
    if(line[0] == '#') {
        string reserved, variable, value;
        ret[0] = ' ';
        stringstream linestream(ret);
        linestream >> reserved >> variable >> value;
        if (reserved == "define")
            macro.insert(pair<string, string>(variable, value)); // add value to macro
        return "";
    }
    else {
        // preprocess: replace macro with value
        map<string, string>::iterator iter;
        for(iter = macro.begin(); iter != macro.end(); iter++)
            ret = regex_replace(ret, regex(iter->first), iter->second);
        // delete comment
        ret = regex_replace(ret, regex("//.*"), "");
    }
    return ret;
}

bool Lexer::judgeCommentStart(string &line) {
    bool commentStart = regex_search(line, regex("/\\*"));
    if(commentStart) {
        // judge if comment end at the same line
        bool commentEnd = regex_search(line, regex("\\*/"));

        if(!commentEnd) {
            line = regex_replace(line, regex("/\\*.*"), "");
            return true;
        } else {
            line = regex_replace(line, regex("/\\*.*\\*/"), "");
            return false;
        }
    } else return false;
}

bool Lexer::judgeCommentEnd(string &line) {
    bool commentEnd = regex_search(line, regex("\\*/"));
    if(commentEnd) {
        line = line = regex_replace(line, regex(".*\\*/"), "");
        return false;
    } else return true;
}
