#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// test indexes function
char* indexes(const char* path)
{
    // TODO
// path for html if found
    char* ret_path_html = malloc(strlen(path) + strlen("/index.html") + 1);
    strcpy(ret_path_html, path);
    strcat(ret_path_html, "/index.html");
   
    // path for php
    char* ret_path_php = malloc(strlen(path) + strlen("/index.php") + 1);
    strcpy(ret_path_php, path);
    strcat(ret_path_php, "/index.php");
    
    printf("%s\n", ret_path_html);
    printf("%s\n", ret_path_php);
    
    if(access(ret_path_html, F_OK ) != -1 ) 
    {
        
        // html file exists
        free(ret_path_php);
        return ret_path_html;
    }
    else if(access(ret_path_php, F_OK ) != -1)  
    {
        // php file exists
        free(ret_path_html);
        return ret_path_php;
    }
    else 
    {
        // file doesn't exist
        return NULL;
    }
}
int main(void)
{
    int result;
    const char *filename = "/index.html";
    result = access (filename, F_OK);
    printf("%d\n", result);
    //printf("%s\n", indexes("~/workspace"));   
}