#include <iostream>
#include <stack>
#include <cstring>

int main(int, char**);

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    return main(__argc, __argv);
}
#endif

using namespace std;

class textEditor {

private:
    stack<char> leftStack;  //Left stack
    stack<char> rightStack; //Right stack

public:
    void insertWord(char word[]);
    void insertCharacter(char character);
    bool deleteCharacter();
    bool backSpaceCharacter();
    void moveCursor(int position);
    void moveLeft(int position);
    void moveRight(int position);
    void findAndReplaceChar(char findWhat, char replaceWith);
    void examineTop();
}; //End of class

void textEditor::examineTop(){
    if(leftStack.empty())
        cout << "leftStack: empty\t";
    else
        cout << "leftStack: " << leftStack.top() << "," << leftStack.size() << "\t\t";
    if(rightStack.empty())
        cout << "rightStack: empty\n";
    else
        cout << "rightStack: " << rightStack.top() << "," << rightStack.size() << endl;
}

void textEditor::insertWord(char word[]) {
    int i=0;
    while(word[i] != '\0') {
        insertCharacter(word[i]);
        i++;
    }
}

void textEditor::insertCharacter(char character){
    leftStack.push(character);
}

bool textEditor::deleteCharacter(){
    if (rightStack.empty())
        return false;
    rightStack.pop();
    return true;
}

bool textEditor::backSpaceCharacter(){
    if (leftStack.empty())
        return false;
    leftStack.pop();
    return true;
}

void textEditor::moveCursor(int position){
    int leftSize = leftStack.size();
    if (position < leftSize)
        moveLeft(position);
    else
        moveRight(position - leftSize);
}

void textEditor::moveLeft(int position){
    int leftSize = leftStack.size();
    while(position != leftSize) {
        rightStack.push(leftStack.top());
        leftStack.pop();
        leftSize = leftStack.size();
    }
}

void textEditor::moveRight(int count){
    int rightSize = rightStack.size();
    if (count > rightSize)
        cout << "Cannot move cursor right to that position";
    else {
        for (int i = 0; i < count; i++) {
            leftStack.push(rightStack.top());
            rightStack.pop();
        }
    }
}

void textEditor::findAndReplaceChar(char findWhat, char replaceWith){
    int count = 1;
    int originalCursorPoistion = leftStack.size();

    moveCursor(0); // move everything to right stack

    while(!rightStack.empty()) {
        if (rightStack.top() == findWhat) {
            deleteCharacter();
            insertCharacter(replaceWith);
        }
        else {
            moveCursor(count);
        }
        count++;
    }
    moveCursor(originalCursorPoistion);
}

int main(int argc, char** argv){
    int i = 0;
    char text[80];
    textEditor txt;

    cout << "Enter the word to be inserted: ";
    cin.getline(text, 80);
    txt.insertWord(text);

    cout << "Inserting the word:";
    txt.examineTop();

    cout << "Enter the word to be inserted: ";
    cin.getline(text, 80);
    txt.insertWord(text);
    cout << "Inserting the word:";
    txt.examineTop();

    cout << "Move cursor to the position 14: ";
    txt.moveCursor(14);
    txt.examineTop();

    cout << "Move cursor to the position 17: ";
    txt.moveCursor(17);
    txt.examineTop();

    for(i = 0; i < 3; i++){
        if(!txt.deleteCharacter())
            cout << "Nothing to delete using DEL.";
        else
            cout << "Delete using DEL: ";
        txt.examineTop();
    }

    for(i = 0; i < 7; i++){
        if(!txt.backSpaceCharacter())
            cout << "Nothing to delete using Backspace.";
        else
            cout << "Delete using Backspace: ";
        txt.examineTop();
    }

    txt.findAndReplaceChar('t', 'T');
    cout << "Replace occurrences of t with T: ";
    txt.examineTop();

    return 0;
}
