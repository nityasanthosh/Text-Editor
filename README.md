# Text-Editor

This project is a basic text editor created using C++.  
It shows how text editing and cursor movement can be handled internally.

## What this project does
- Insert characters
- Delete characters
- Move cursor left and right
- Replace characters

## Main data structure used
This project mainly uses **Stacks**.

Two stacks are used:
- One stack stores characters before the cursor
- One stack stores characters after the cursor

## Why I used stacks
Stacks make cursor movement easy because:
- Moving left and right is done using push and pop
- Operations are fast and simple
- It matches how editors handle text internally

## How to run
```
g++ texteditor.cpp -o editor.exe
.\editor.exe
```
