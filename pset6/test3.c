#include <string.h> /* for strchr() */
#include <stdio.h>

int main(void){
        char address[] = "10.10.10\r\n.10/10";
        //printf("%c\n", address[11]);
        //char *p = strchr(address, '.');
        //if (!p) /* deal with error: / not present" */;
        
        char *pchar = strchr(address, '.');
        char *p = strstr(address, "\r\n");
        char ad[p-pchar-1];
        strncpy(ad,pchar+1,p-pchar-1);
        ad[p-pchar] = '\0';
        printf("%s\n",ad);
        
        // char ad[p-address];
        // //printf("p-address = %ld\n", p-address);
        // strncpy(ad,address,p-address);
        // ad[p-address] = '\0';
        // printf("first: %s\n",ad);
        
        // char *first_dot = strchr(p+1, '.');
        // char after[first_dot-p-1];
        // strncpy(after,p+1, first_dot-p-1);
        // after[first_dot-p] = '\0';
        // printf("after = %s\n", after);
        
        // char *second_dot = strchr(first_dot+1, '.');
        // char third_domain[second_dot-first_dot-1];
        // strncpy(third_domain, first_dot+1, second_dot-first_dot-1);
        // third_domain[second_dot-first_dot] = '\0';
        // printf("third domain = %s\n", third_domain);
        
        // //printf("%s\n", ad);
        return 0;
}