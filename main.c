/** Julia Williams
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// node struct
struct node {
    // each node contains char data
    int data;
    struct node *next;
    // token types
    enum {
        leftBrace,
        rightBrace,
        equals,
        addition,
        subtraction,
        semi,
        letter,
        digit,
        space,
        endl
    } tokenType;
};

// iterator struct
struct iterator {
    struct node *_cur;
};

void append(int ch, int count);

void printList();

void lexer();

void parser();

void erase(struct iterator *it);

char peek(struct iterator *it);

struct iterator *begin();

struct iterator *end();

void block();

void statement();


// initialize head, cur, temp, n - singly linked
struct node *head, *cur, *temp, *n;

int main(int argc, char **argv) {

    // open file, read it
    //FILE *infile = fopen(argv[1], "r");
    FILE *infile = fopen("../input.txt", "r");

    // check if there's an error when opening
    if (infile == NULL) {
        printf("Error when opening.\n");
    }

    int ch;
    int count = 0;

    while ((ch = fgetc(infile)) != EOF) {

        // print each char, testing
        //printf("%c", ch);
        // append to linked list
        append(ch, count);
        count++;

    }

    //close file
    fclose(infile);
    lexer();
    parser();
    //printList();
    return 0;
}

// append to linked-list
void append(int ch, int count) {

    // if linked list is empty
    if (count == 0) {
        // wut ?
        // using malloc to set head to size of a node struct ?
        //printf("%c", ch);
        head = (struct node *) malloc(sizeof(struct node));
        temp = (struct node *) malloc(sizeof(struct node));
        head->data = ch;
        //printf("%s", "head data\n");
        //printf("%d", head->data);
        head->next = NULL;
        temp = head;
        //printf("%s", "temp data\n");
        //printf("%d", temp->data);
    } else {
        cur = (struct node *) malloc(sizeof(struct node));
        //printf("%s %d", "temp data", temp->data);
        temp->next = cur;
        cur->data = ch;
        //printf("%d", cur->data);
        cur->next = NULL;
        temp = cur;
        //printf("%c", ch);
    }
}

// print linked list
void printList() {

    n = (struct node *) malloc(sizeof(struct node));
    n = head;
    // printf("%d", head->data);
    //printf("%d", n->next->data);
    while (n->next != NULL) {
        printf("%c", (char) n->data);
        //printf("%d ", n->data);
        n = n->next;
    }
}

void lexer() {

    // return a list and get iterator into that list
    struct node *ptr = head;
    const int line = 10;

    while (ptr != NULL) {
        // if alphanumeric
        if (isalnum((char) ptr->data)) {
            // if numeric
            if (isdigit((char) ptr->data)) {
                ptr->tokenType = digit;
            }
                // if alphabetical
                // TODO upper vs lower?
            else if (isalpha((char) ptr->data)) {
                ptr->tokenType = letter;
            }
        } else if (((char) (ptr->data)) == ';') {
            ptr->tokenType = semi;
            // if left brace
        } else if (((char) (ptr->data)) == '{') {
            ptr->tokenType = leftBrace;
            block();
            // if right brace
        } else if (((char) (ptr->data)) == '}') {
            ptr->tokenType = rightBrace;
            // if equals
        } else if (((char) (ptr->data)) == '=') {
            ptr->tokenType = equals;
            // if addition
        } else if (((char) (ptr->data)) == '+') {
            ptr->tokenType = addition;
            // if subtraction
        } else if (((char) (ptr->data)) == '-') {
            ptr->tokenType = subtraction;
            // if space
        } else if (((char) (ptr->data)) == ' ') {
            ptr->tokenType = space;
            // if newline (ascii)
        } else if ((ptr->data) == line) {
            ptr->tokenType = endl;
        } else {
            printf("%s %d", "Invalid token: ", (char) ptr->data);
        }

        ptr = ptr->next;
    }

}

// call parser function
// go to first token
// call function based on that

// top-down recursive descent, builds an output parse tree
//void parser() {
//
//
//
//
//
//}


// using an iterator to remove from the linked list
void erase(struct iterator *it) {

    struct node *nd;
    struct node *tmp = (struct node *) malloc(sizeof(struct node));

    // TODO this is definitely wrong
    if (it->_cur != NULL) {
        nd = it->_cur;
        tmp->next = nd;
        free(nd);
        tmp->next = nd->next;
    }

}

// using an iterator to peek the linked list
char peek(struct iterator *it) {

    if (it->_cur != NULL) {
        return (char) (it->_cur->data);
    }
}

// beginning of linked list
struct iterator *begin() {
    struct iterator *it;
    it->_cur = head;
    return it;
}

// end of linked-list
struct iterator *end() {

    struct node *nd = head;
    while (nd != NULL) {
        if (nd->next != NULL) {
            nd = nd->next;
        } else {
            break;
        }
    }

    struct iterator *it;
    it->_cur = nd;
    return it;

}

void block() {


}

void statement() {


}
// statement can start with letter or number
// we don

// read in a file character by character
// keep a linked list
//switch ((char) ptr->data) {
//case ';': ptr->tokenType = semi; break;
//case '{': ptr->tokenType = leftBrace; break;
//case '}': ptr->tokenType = rightBrace; break;
//case '+': ptr->tokenType = addition; break;
//case '-': ptr->tokenType = subtraction; break;
//case '=': ptr->tokenType = equals; break;
