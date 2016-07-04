#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 8

void print_string(char str[],char new_str[],int current_len,int n,int len);

int main(void){
    
    // char all[] = "abcd";
    // char word[3+1];
    // //int i,j;
    // int i;
    // int pointer1 = 0;
    // int pointer2 = 0;
    
    // // index for word length: from 1 to 3
    // // for (i = 1; i<=3; i++){
    // //     // TODO
        
    // // }
    // for(pointer1 = 0; pointer1<strlen(all); pointer1++){
    //     word[0] = all[pointer1];
    //     word[3] = '\0';
    //     for (pointer2 = 0; pointer2<=strlen(all)-1; pointer2++){
    //             i = 1;
    //             while(i <= 2){
    //                 word[pointer2] = all[pointer2];
    //                 i++;
    //                 //printf("%s\n", word);
                    
    //             }
    //         //for()
    //         //printf("1111\n");
    //     printf("%s\n", word);
    //     }
    //     //pointer1++;
    // }
    char set[]="abc";
    char arr[10]={0};
    print_string(set,arr,0,strlen(set),3);
    return 0;
    return 0;
}

void print_string(char str[],char new_str[],int current_len,int n,int len)
{
    /*
    str=orignal set,
    new_str=empty char array,
    current_len=0(Intially)
    n=no of elements to be used
    len=the value of p given*/
    if(current_len==len)//print string when length is equal to p
    {
        //printf("%s\n",new_str);
        return;
    }
    else
    {
        int i;
        for(i=0;i<n;i++)
        {
            new_str[current_len]=str[i];
            print_string(str,new_str,current_len+1,n,len);
        }
    }
}

