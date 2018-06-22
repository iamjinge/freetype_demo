#include <ft2build.h>
#include <wchar.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include <stdio.h>  /* printf */
#include <time.h>   /* time_t, struct tm, time, localtime, strftime */
#include <locale.h> /* struct lconv, setlocale, localeconv */
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int a = -10;
    short b = a;
    printf("%d", b);
    return 0;
}
