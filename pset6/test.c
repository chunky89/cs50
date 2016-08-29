#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char* lookup(const char* path)
{
    // TODO
    // return value
    const char *ret = NULL;
    // return a string literal
    char *dot = strrchr(path, '.');
    //printf("%s\n", dot);
    
    // need a copy to process further
    char dotcopy[strlen(dot)+1];
    strcpy(dotcopy, dot); 
    //printf("dotcopy = %s\n", dotcopy);
    
    // convert all the letters to lower case except ".(dot)" character
    for(int i = 1; dotcopy[i]; i++){
        dotcopy[i] = tolower(dotcopy[i]);
    }
    
    //printf("hello\n");
    if(!strcmp(dotcopy, ".css"))
        ret = "text/css";
    else if(!strcmp(dotcopy, ".html"))
        ret = "text/html";
    else if(!strcmp(dotcopy, ".gif"))
        ret = "image/gif";
    else if(!strcmp(dotcopy, ".ico"))
        ret = "image/x-icon";
    else if(!strcmp(dotcopy, ".jpg"))
        ret = "image/jpeg";
    else if(!strcmp(dotcopy, ".js"))
        ret = "text/javascript";
    else if(!strcmp(dotcopy, ".php"))
        ret = "text/x-php";
    else if(!strcmp(dotcopy, ".png"))
        ret = "image/png";
    else 
        ret = NULL;
    return ret;
}


int main(void)
{
    printf("%s\n", lookup("/home/cat.hello"));
    return 0;
}