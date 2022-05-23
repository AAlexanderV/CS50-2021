#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    float n_size = atof (argv[1]);
    printf("n_size = %f\n", n_size);
    
    // ensure proper usage
    if (argc != 4 || n_size > 100 || n_size < 0)
    {
        printf("Error!\nUsage: resize n_size(1-100) infile outfile\n");
        return 1;
    }
    
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }
    
    // remember old sizes and padding for inptr
    int old_Width = bi.biWidth;
    int old_Height = bi.biHeight;
    int old_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //width firstly - then padding
    bi.biWidth = ceil (bi.biWidth * n_size);
    //changes image's height
    bi.biHeight = ceil (bi.biHeight * n_size);
    //changes image's size (how many bytes)
    bi.biSizeImage = abs (bi.biHeight * bi.biWidth * 3);
    //file's size is actually image size + 54 bytes of FILEHEADER
    bf.bfSize = bi.biSizeImage + 54;
    
    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf ("padding = %i\n", padding); // DELETE
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    //если картинку надо уменьшить
    if (n_size < 1)
    {
        //вычисляем коэф.: сколько пикселей в среднем прочитать, после чего 1 удалить
        float K_const = (10 - (10 * n_size)) / 10;
        //создаем переменные, в которых будем этот коэф. прибавлять после каждого считывания пикселя
        float K_width = 0;
        float K_height = 0;
        
        //уменьшаем изображение
        for (int i = 1; i <= old_Height; i++)
        {
            //добавляем коэф., пока не будет 1, сперва добавляем коеэф. потом проверка
            K_height = K_height + K_const;
            if (K_height >= 1)
            {
                //проскочить целую строку ширины+паддинг
                fseek (inptr, (old_Width*3) + old_padding, SEEK_CUR);
                //отнимаем от переменной удаленный пиксель и добавляем коэф., а к i добавляем 1, чтобы не сбиться с высоты картинки
                K_height = K_height - 1;
                i++;
            }

            //считываем строку, удаляя пиксели с учетом коэф.
            for (int j = 1; j <= old_Width; j++)
            {
                //добавляем коэф., пока не будет 1, сперва добавляем коеэф. потом проверка
                K_width = K_width + K_const;
                if (K_width >= 1) 
                {
                    //если набралась 1, skip пиксель, по факту удалить
                    fseek (inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                    //отнимаем от коэф. потраченый skip, а к j добавляем 1, чтобы не сбиться с ширины строки
                    K_width = K_width - 1;
                    j++;
                }
                //читаем, записываем пиксель
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                 fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
            // skip over padding, if any in inptr
            fseek(inptr, old_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
                {
                    fputc(0x00, outptr);
                }
        }
    }

    //если картинку надо увеличить
    if (n_size >= 1)
    {
        // iterate over infile's scanlines
        for (int i = 0; i < abs (old_Height); i++)
        {
            //makes "n_size" resized scanlines instead of one
            for (int b = 0; b < n_size; b++)
            {
                // iterate over pixels in scanline
                for (int j = 0; j < abs (old_Width); j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile n_size times
                    for (int a = 0; a < n_size; a++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
            if (b != (n_size - 1))
                {
                    // returns point-reader in file to the begining of the scanline
                    fseek(inptr, old_Width * -3, SEEK_CUR);
                }
            }
  
            // skip over padding, if any in inptr
             fseek(inptr, old_padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    //close infile
    fclose(inptr);

    //close outfile
    fclose(outptr);

    // success
    return 0;
}


   