#include <stdio.h>
#include <string.h>
#include <ctype.h>
char *cercaRegexp(char *src, char *regexp);
int TypeRegExp(char c);
int isEqual(char *src, char *regexp);
int isBetweenCharacters(char *listOfCharacters, char Character);
int Search(char *src, char *regexp);


int main() {
    char *s = cercaRegexp("Totofoto", "\\Ao[^r]o");
    printf("%s", s);
    return 0;
}
char *cercaRegexp(char *src, char *regexp){
    int found = 0;
    char *savedSrc;
    char *savedRegExp = regexp; //i use this pointer to save the start of the regexp because if the isEqual doens't return true I need to reuse the start of the expression

    while(*src != '\0' && found == 0){
        while(!isEqual(src, regexp)){  //  I scroll until i find the same char
            src++; regexp = savedRegExp;
        }
        savedSrc = src;

        regexp = savedRegExp;
        found = Search(src, regexp);
        src++;
    }

    if (found)
        return savedSrc;
    return NULL;
}

int Search(char *src, char *regexp){  // This function return 1 if the string are compatible
    char *savedSrc = src;
    while(isEqual(src, regexp) && *regexp != '\0'){
        src++;
        if(*regexp == '[')  //I have to "delete" the char between parenthesis -> another way to do this is by using a pointer
            while (*regexp != ']')
                regexp++;
        if(*regexp == '\\')
            regexp++;
        regexp++;
    }

    if(*regexp == '\0'){
        src = savedSrc;
        return 1;
    }
    return 0;
}

int TypeRegExp(char c){
    if (c == '.')
        return 1;
    if (c == '[')
        return 2;
    if (c == '\\')
        return 3;

        return 0;
}

int isEqual(char *src, char *regexp){
    int type = TypeRegExp(*regexp);
    switch(type){
        case 0:
            if (*src == *regexp)
                return 1;
            return 0;
        case 1:
            return 1;
        case 2:
            if (*(++regexp) == '^'){ //control if the next character is an ^, in this case I have to return 1 if the characters between parenthesis aren't the src char
                if (isBetweenCharacters(regexp, *src))
                    return 0;
                return 1;
            }else{
                regexp--;  //I have to consider the first char because there isn't the ^
                if(isBetweenCharacters(regexp, *src))
                    return 1;
                return 0;
            }

        case 3:
            if (islower(*(++regexp)) == islower(*src))
                return 1;
            return 0;


    }
}

int isBetweenCharacters(char *listOfCharacters, char Character){
    while(*listOfCharacters != ']'){
        if(*listOfCharacters == Character)
            return 1;
        listOfCharacters++;
    }
    return 0;
}