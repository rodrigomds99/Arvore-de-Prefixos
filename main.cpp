// Copyright [2024] <Rodrigo Martins dos Santos>
// Copyright [2024] <Lucas Pastre de Souza>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class TreeNode {
private:
    TreeNode* letters[26];
    bool isWord;
    int start;
    int length;
        
public:
    TreeNode() {
        isWord = false;
        start = -1;
        length = 0;
        for (int i = 0; i < 26; i++) {
            letters[i] = nullptr;
        }
    }
    
    ~TreeNode() {
        for (int i = 0; i < 26; i++) {
            delete letters[i];
        }
    }
    
    void insert(const string& word, int startPos, int len) {
        TreeNode* current = this;
        for (size_t i = 0; i < word.length(); i++) {
            char c = word[i];  // c é o caractere atual da palavra
            int index = c - 'a';
            if (current->letters[index] == nullptr) {
                current->letters[index] = new TreeNode();
            }
            current = current->letters[index];
        }
        current->isWord = true;
        current->start = startPos;
        current->length = len;
    }
    
    bool find(const string& word, int& startPos, int& len) {
        TreeNode* current = this;
        for (size_t i = 0; i < word.length(); i++) {
            char c = word[i];  // c é o caractere atual da palavra
            int index = c - 'a';
            if (current->letters[index] == nullptr) {
                return false;
            }
            current = current->letters[index];
        }
        if (current->isWord == true) {
            startPos = current->start;
            len = current->length;
            return true;
        }
        return false;
    }
    
    int countPrefix(const string& word) {
        TreeNode* current = this;
        for (size_t i = 0; i < word.length(); i++) {
            char c = word[i];  // c é o caractere atual da palavra
            int index = c - 'a';
            if (current->letters[index] == nullptr) {
                return 0;
            }
            current = current->letters[index];
        }
        return countWords(current);
    }

private:
    int countWords(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        int count = 0;
        if (node->isWord == true) {
            count = 1;
        }
        for (int i = 0; i < 26; i++) {
            count += countWords(node->letters[i]);
        }
        return count;
    }
    
};
    

int main() {

    string filename;
    cin >> filename;  // entrada

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }
    
    TreeNode root;
    string line;
    int position = 0;
    
    // Construindo a Árvore com o arquivo
    while (getline(file, line)) {
        size_t startPos = line.find('[') + 1;
        size_t endPos = line.find(']');
        string word = line.substr(startPos, endPos - startPos);
        root.insert(word, position, line.length());
        position += line.length() + 1;  // Inclui o caractere de nova linha
    }
    file.close();
    
    // Lendo as palavras de entrada
    string word;
    while (cin >> word && word != "0") {
        int prefixCount = root.countPrefix(word);
        if (prefixCount > 0) {
            cout << word << " is prefix of " << prefixCount << " words" << endl;
            int startPos, len;
            if (root.find(word, startPos, len)) {
                cout << word << " is at (" << startPos << "," << len << ")" << endl;
            }
        } else {
            cout << word << " is not prefix" << endl;
        }
    }
    return 0;
}
