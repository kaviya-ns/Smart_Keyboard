#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <fstream>
#define SIZE 256
using namespace std;
class TrieNode {
public:
    bool isWordComplete;
    TrieNode *next[SIZE];
    void FindStrCore(string query, vector<string> &result);

    TrieNode() {
        isWordComplete = false;
        for (int i = 0; i < SIZE; i++) {
            next[i] = NULL;
        }
    }

    ~TrieNode() {
        for (int i = 0; i < SIZE; i++) {
            if (next[i] != NULL) {
                delete next[i];
            }
        }
    }
};

class Trie : public TrieNode {
public:
    void InsertNode(string str);
    void FindStr(string query, vector<string> &result);
    void clear();
    int IsError(string query);
    void CorrectSpell(string query, vector<string> &res);
};

void Trie::InsertNode(string str) {
    TrieNode *p = this;
    for (int i = 0; i < str.size(); i++) {
        unsigned char index = (unsigned char) str[i];
        if (p->next[index] == NULL)
            p->next[index] = new TrieNode();

        p = p->next[index];
    }
    p->isWordComplete = true;
}

void TrieNode::FindStrCore(string query, vector<string> &result) {
    TrieNode *p = this;
    if (p == NULL)
        return;
    if (p->isWordComplete)
        result.push_back(query);
    for (int i = 0; i < SIZE; i++) {
        if (p->next[i] != NULL) {
            char c = (char) i;
            p->next[i]->FindStrCore(query + c, result);
        }
    }
}

void Trie::FindStr(string src, vector<string> &result) {
    TrieNode *p = this;
    int curr = 0;
    unsigned char index = (unsigned char) src[curr];

    while (curr < src.size() && p->next[index]) {
        p = p->next[index];
        ++curr;
        index = (unsigned char) src[curr];
    }
    if (curr != src.size() || p == NULL) {
        return;
    }
    p->FindStrCore(src, result);
}

int Trie::IsError(string query) {
    TrieNode *p = this;
    if (p == NULL)
        return 0;
    int curr = 0;
    unsigned char index = (unsigned char) query[curr];
    while (curr < query.size() && p->next[index]) {
        p = p->next[index];
        ++curr;
        index = (unsigned char) query[curr];
    }
    if (!p->isWordComplete)
        return curr;

    return 0;
}

void Trie::CorrectSpell(string query, vector<string> &res) {
    int index = IsError(query);
    if (index) {
        string sub = query.substr(0, index);
        FindStr(sub, res);
    }
}

void Trie::clear() {
    delete this;
}

