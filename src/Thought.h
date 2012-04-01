#ifndef THOUGHT_H_INCLUDED
#define THOUGHT_H_INCLUDED

#include "Word.h"
#include <fstream>

class Thought {
    private:
        std::vector<Word> words;

    public:
        enum Mood {
            Positive,
            Negative
        };

        Thought() {}
};

class ThoughtEmitter {
    private:
        std::vector<Thought> thoughts;

    public:
        static void load(const char* filename, std::vector<Thought>& emitters) {
            std::ifstream f(filename);
            while(!f.eof()) {
                std::string line;
                std::getline(f, line);
                // todo
            }
        }

        ThoughtEmitter() {}
};

#endif
