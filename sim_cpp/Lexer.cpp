//
// Created by Ark on 2019/5/17.
//
#include "Lexer.h"
#include <regex>
#include <iostream>
#include <sstream>
#include <map>
#include <iomanip>

/**
 * replace rule:
 * an unit is a keyword, an symbol, a variable, a string, or a number
 * $unit type,option$
 * unit type:
 * 1: keyword, 2: symbol, 3: variable, 4: string, 5: number
 * */

Lexer::Lexer(const string& filename) {
    kw = new keyword();
    sybs = new symbols();
    var = new variate();
    ifile.open(filename + ".c");
    ofile.open(filename + "_output.c");
}

Lexer::~Lexer() {
    delete(kw);
    delete (sybs);
    delete (var);
    ifile.close();
    ofile.close();
}

void Lexer::analyse() {
    string line;
    int line_num = 0;
    bool inComment = false;
    while (getline(ifile, line)) {
        if (line.length() > 0) {
            cout << ++line_num << ' ' << line << endl;
            if (inComment) inComment = !hasCommentEnd(line);
            if (inComment) continue;
            else inComment = hasCommentStart(line);
            preprocessing(line);
            if (line.length() == 0) continue;
            cout << "\t" << line << endl;
            replaceunit(line, line_num);
            if (line.length() == 0) continue;
            cout << "\t" << line << endl;
            if (line.length() > 0) ofile << line << endl;
        }
    }
}

void Lexer::preprocessing(string &line) {
    int i;
    line = regex_replace(line, regex("\r"), "");
    line = regex_replace(line, regex("//.*"), "");
    if (line.length() == 0) return;
    line = regex_replace(line, regex("\".*\""), "$$4,    $$");
    line = regex_replace(line, regex("\'.*\'"), "$$5,    $$");
    for (i = 0; i < sybs->gap_sybs_num; ++i) {
        ostringstream replacesyb;
        replacesyb << ' ' << sybs->gap_sybs[i][sybs->gap_sybs[i].length() - 1] << ' ';
        line = regex_replace(line, regex(sybs->gap_sybs[i]), replacesyb.str());
    }

    for (i = 0; i < sybs->del_sybs_num; ++i)
        line = regex_replace(line, regex(sybs->del_sybs[i]), " ");
}

bool Lexer::hasCommentStart(string &line) {
    bool hasStart = regex_search(line, regex("/\\*"));
    if (hasStart) {
        if (regex_search(line, regex("\\*/"))) {
            line = regex_replace(line, regex("/\\*.*\\*/"), "");
            hasStart = false;
        } else line = regex_replace(line, regex("/\\*.*"), "");
    }
    return hasStart;
}

bool Lexer::hasCommentEnd(string &line) {
    bool hasEnd = regex_search(line, regex("\\*/"));
    if (hasEnd) line = regex_replace(line, regex(".*\\*/"), "");
    return hasEnd;
}

void Lexer::replaceunit(string &line, int linenum) {
    istringstream linestream(line);
    ostringstream replacestream;
    string unit;
    bool ismacro = false;
    bool replaced = false;
    while (linestream >> unit) {
        // macro
        if (unit == "#") {
            ismacro = true;
            continue;
        }
        if (ismacro) {
            if (unit == "define") {
                string key, val;
                linestream >> key >> val;
                var->addmacro(key, val);
            }
            line = "";
            return;
        }

        if (unit[0] == '$' && unit[unit.length()-1] == '$') goto outputreplace;
        replaced = var->getmacrovalue(unit);
        replaced = replaced || kw->replacekeyword(unit);
        replaced = replaced || sybs->replacesymbol(unit, linenum);
        replaced = replaced || replacenum(unit);
        if (!replaced) {
            var->replacevar(unit);
        }
        outputreplace:
            if (unit.length() > 0) replacestream << unit;
    }
    line = replacestream.str();
}

bool Lexer::replacenum(string &num) {
    int intnum = 0;
    for (char i : num) {
        if (i > '9' || i < '0')
            return false;
        intnum = intnum * 10 + (i-'0');
    }
    ostringstream numstream;
    numstream << "$5," << setw(4) << setfill('0') << intnum << "$";
    num = numstream.str();
    return true;
}
