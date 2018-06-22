#include <stdio.h>


int main(int argc, char const *argv[])
{
    FILE *fp = fopen("c.f","ab");
    int value = 4;
    short val = (short)value;
    printf("%lu", sizeof(short));
    fwrite((const void*) & val,sizeof(short),1,fp);
    return 0;
}
