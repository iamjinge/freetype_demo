#include <stdio.h>
#include <ft2build.h>
#include <stdlib.h>
#include <png.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers;

void write_png_file(char *filename);
void process_png_file(FT_Bitmap *bitmap, int h, int w);

int main()
{
    FT_Library library; // 声明了Lib
    FT_Face face;
    FT_Glyph glyph;
    FT_UInt glyph_index;

    FT_Error error = FT_Init_FreeType(&library); // 初始化 返回0为成功
    if (error)
    {
        printf("error occured\n");
        exit(-1);
    }

    error = FT_New_Face(library, "fonts/WXxiari.ttf", 0, &face);
    if (error == FT_Err_Unknown_File_Format)
    {
        printf("unknown file format");
    }
    else if (error)
    {
        printf("some erorr occured\n");
    }

    error = FT_Set_Pixel_Sizes(face, 0, 16);

    char c = 'M';
    glyph_index = FT_Get_Char_Index(face, c);
    error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
    error = FT_Get_Glyph(face->glyph, &glyph);
    error = FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, NULL, 1);

    FT_BitmapGlyph bit = (FT_BitmapGlyph)glyph;

    int h = bit->bitmap.rows;
    int w = bit->bitmap.width;

    process_png_file(&bit->bitmap, h, w);
    write_png_file("test1.png");

    // FT_Load_Char(face, c, FT_LOAD_RENDER);
    // FT_GlyphSlot slot = face->glyph;

    // int h = slot->bitmap.rows;
    // int w = slot->bitmap.width;

    // printf("%d, %d\n", slot->bitmap.rows, slot->bitmap.width);

    // process_png_file(&slot->bitmap, h, w);
    // write_png_file("test1.png");

    printf("hello world\n");
    // printf("%s", typeof(slot->bitmap));
    return 0;
}

void process_png_file(FT_Bitmap *bitmap, int h, int w)
{
    width = w;
    height = h;
    printf("start process\n");
    printf("start height is %d, width is %d", h, w);
    row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * h);

    for (int y = 0; y < h; y++)
    {
        row_pointers[y] = (png_byte *)malloc(4 * 2 * w);
    }

    for (int y = 0; y < h; y++)
    {
        printf("start row %d: \t", y);
        png_bytep row = row_pointers[y];
        for (int x = 0; x < w; x++)
        {
            printf("%d,%d:%d;", y, x, bitmap->buffer[y * w + x]);
            png_bytep px = &(row[x * 4]);
            row[x * 4] = 255;
            row[x * 4 + 1] = 255;
            row[x * 4 + 2] = 255;
            row[x * 4 + 3] = bitmap->buffer[y * w + x];
            // Do something awesome for each pixel here...
            //printf("%4d, %4d = RGBA(%3d, %3d, %3d, %3d)\n", x, y, px[0], px[1], px[2], px[3]);
        }
        printf("\n");
    }
}

void write_png_file(char *filename)
{
    int y;

    FILE *fp = fopen(filename, "wb");
    if (!fp)
        abort();

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
        abort();

    png_infop info = png_create_info_struct(png);
    if (!info)
        abort();

    if (setjmp(png_jmpbuf(png)))
        abort();

    png_init_io(png, fp);

    // Output is 8bit depth, RGBA format.
    png_set_IHDR(
        png,
        info,
        width, height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png, info);

    // To remove the alpha channel for PNG_COLOR_TYPE_RGB format,
    // Use png_set_filler().
    //png_set_filler(png, 0, PNG_FILLER_AFTER);

    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    for (int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }
    free(row_pointers);

    fclose(fp);
}
