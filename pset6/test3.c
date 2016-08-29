#include <string.h> /* for strchr() */
#include <stdio.h>

int main(void){
        char address[] = "10.10.10.10/10";
        char *p = strchr(address, '/');
        //if (!p) /* deal with error: / not present" */;
        
        char ad[p-address];
        printf("p-address = %ld\n", p-address);
        strncpy(ad,address,p-address);
        ad[p-address] = '\0';
        
        printf("%s\n", ad);
        return 0;
}