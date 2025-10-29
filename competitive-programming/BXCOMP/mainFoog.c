#include <stdio.h>
//ocdye myw pywo, xow zobmols y aeo fymo pkvye
int main()
{
    char string[255];
    scanf("\n%[^\n]", string);
    char stringN[255];
    int end = 0;
    for(int i = 0; string[i] != '\0';i++){
        end++;
        
        if(string[i] >= 32 && string[i] <= 47) {
            stringN[i] = (char)(((int)string[i]));
            continue;
        }
        
        if(((int)string[i])-10 < 97){
            int s = 123-(97-((int)string[i]-10));
            stringN[i] = (char)s;
            continue;
        }
        stringN[i] = (char)(((int)string[i])-10);
        
    }
    stringN[end] = '\0';
    printf("%s", stringN);
    

    return 0;
}
