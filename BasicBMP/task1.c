#include <stdio.h>
#include <string.h>
#include "bmp_header.h"
#include <stdlib.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef struct
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
} bmp_bgr;

void draw(bmp_bgr ***matrice, int y1, int x1, int y2, int x2, bmp_bgr culoare, int width, int height_matrice, int width_matrice)
{
    if (abs(x2 - x1) < abs(y2 - y1))
    {
        for (int i = min(y1, y2); i <= max(y1, y2); i++)
        {
            int x = (((i - y1) * (x2 - x1)) + x1 * (y2 - y1)) / (y2 - y1);
            for (int j = max(x - width / 2, 0); j < min(x + 1 + width / 2, height_matrice); j++)
                for (int t = max(i - width / 2, 0); t < min(i + 1 + width / 2, width_matrice); t++)
                    (*matrice)[j][t] = culoare;
        }
    }
    else
    {
        for (int i = min(x1, x2); i <= max(x1, x2); i++)
        {
            int y = (((i - x1) * (y2 - y1)) + y1 * (x2 - x1)) / (x2 - x1);
            for (int j = max(i - width / 2, 0); j < min(i + 1 + width / 2, height_matrice); j++)
                for (int t = max(y - width / 2, 0); t < min(y + 1 + width / 2, width_matrice); t++)
                    (*matrice)[j][t] = culoare;
        }
    }
}

void fill(bmp_bgr ***matrice, int y, int x, bmp_bgr culoare_finala, bmp_bgr culoare_initiala, int height, int width)
{
    if (((*matrice)[x][y].R == culoare_initiala.R) && ((*matrice)[x][y].G == culoare_initiala.G) && ((*matrice)[x][y].B == culoare_initiala.B))
    {
        (*matrice)[x][y].R = culoare_finala.R;
        (*matrice)[x][y].G = culoare_finala.G;
        (*matrice)[x][y].B = culoare_finala.B;
        // aici nu mergea o egalitate de structuri. nu inteleg de ce, dar daca asa merge aia e, sry

        if (y > 0)
            fill(matrice, y - 1, x, culoare_finala, culoare_initiala, height, width);
        if (y < width - 1)
            fill(matrice, y + 1, x, culoare_finala, culoare_initiala, height, width);
        if (x > 0)
            fill(matrice, y, x - 1, culoare_finala, culoare_initiala, height, width);
        if (x < height - 1)
            fill(matrice, y, x + 1, culoare_finala, culoare_initiala, height, width);
    }
    else
    {
        return;
    }
}

int main()
{
    int width_line;
    bmp_fileheader fileheader;
    bmp_infoheader infoheader;
    bmp_bgr **matrice;
    bmp_bgr draw_color;

    while (1)
    {
        int alocare_check = 0, dim_max = 1, dim_actuala = 0;
        char *comanda, *comenzi, *temp, caracter;

        // alocare dinamica
        comanda = (char *)calloc(dim_max, sizeof(char));

        if (comanda == NULL)
        {
            printf("Unde e memoria boss???");
            // exit(0);
        }

        while (alocare_check == 0)
        {
            if (dim_actuala >= dim_max)
            {
                dim_max *= 2;
                temp = realloc(comanda, dim_max);
                if (temp == NULL)
                {
                    printf("Unde e memoria, boss???");
                    break;
                }
                else
                {
                    comanda = temp;
                }
            }

            scanf("%c", &caracter);

            if (caracter == '\n')
            {
                caracter = '\0';
                alocare_check = 1;
            }
            else
            {
                comanda[dim_actuala] = caracter;
            }

            dim_actuala++;
        }
        //==========================

        comenzi = strtok(comanda, " ");

        FILE *imagine_input, *imagine_output;

        if (!strcmp(comenzi, "edit"))
        {
            printf("1");
            comenzi = strtok(NULL, " ");

            imagine_input = fopen(comenzi, "rb");
            fread(&fileheader, sizeof(bmp_fileheader), 1, imagine_input);
            fread(&infoheader, sizeof(bmp_infoheader), 1, imagine_input);

            matrice = (bmp_bgr **)calloc(infoheader.height, sizeof(bmp_bgr *));
            if (matrice == NULL)
            {
                printf("Unde e memoria boss???");
                // exit(0);
            }
            for (int i = 0; i < infoheader.height; i++)
            {
                matrice[i] = (bmp_bgr *)calloc(infoheader.width, sizeof(bmp_bgr));
                if (matrice[i] == NULL)
                {
                    for (int j = 0; j < i; j++)
                        free(matrice[j]);
                    free(matrice);
                    printf("Unde e memoria boss???");
                    // exit(0);
                }

                for (int j = 0; j < infoheader.width; j++)
                {
                    fread(&matrice[i][j], sizeof(bmp_bgr), 1, imagine_input);
                }
                if ((3 * infoheader.width) % 4 != 0)
                    fseek(imagine_input, 4 - (3 * (infoheader.width) % 4), SEEK_CUR);
            }
            fclose(imagine_input);
        }
        else if (!strcmp(comenzi, "save"))
        {
            int zero = 0;
            comenzi = strtok(NULL, " ");

            imagine_output = fopen(comenzi, "wb");
            fwrite(&fileheader, 1, sizeof(bmp_fileheader), imagine_output);
            fwrite(&infoheader, 1, sizeof(bmp_infoheader), imagine_output);
            for (int i = 0; i < infoheader.height; i++)
            {
                for (int j = 0; j < infoheader.width; j++)
                    fwrite(&matrice[i][j], 1, sizeof(bmp_bgr), imagine_output);

                if ((3 * infoheader.width) % 4 != 0)
                    fwrite(&zero, 1, 4 - (3 * (infoheader.width) % 4), imagine_output);
            }
            fclose(imagine_output);
        }
        else if (!strcmp(comanda, "insert"))
        {
            int y, x;
            bmp_fileheader fileheader_insert;
            bmp_infoheader infoheader_insert;
            comenzi = strtok(NULL, " ");
            y = atoi(strtok(NULL, " "));
            x = atoi(strtok(NULL, " "));

            imagine_input = fopen(comenzi, "rb");
            fread(&fileheader_insert, sizeof(bmp_fileheader), 1, imagine_input);
            fread(&infoheader_insert, sizeof(bmp_infoheader), 1, imagine_input);

            for (int i = 0; i < infoheader_insert.height; i++)
            {
                if (i + x > infoheader.height - 1)
                    break;
                for (int j = 0; j < infoheader_insert.width; j++)
                {
                    if (j + y > infoheader.width - 1)
                    {
                        fseek(imagine_input, 3 * (infoheader_insert.width - j), SEEK_CUR);
                        break;
                    }
                    fread(&matrice[i + x][j + y], sizeof(bmp_bgr), 1, imagine_input);
                }
                if ((3 * infoheader_insert.width) % 4 != 0)
                {
                    fseek(imagine_input, 4 - (3 * (infoheader_insert.width) % 4), SEEK_CUR);
                }
            }
            fclose(imagine_input);
        }
        else if (!strcmp(comanda, "set"))
        {
            comenzi = strtok(NULL, " ");
            if (!strcmp(comenzi, "draw_color"))
            {
                draw_color.R = atoi(strtok(NULL, " "));
                draw_color.G = atoi(strtok(NULL, " "));
                draw_color.B = atoi(strtok(NULL, " "));
            }
            else if (!strcmp(comenzi, "line_width"))
            {
                char *temp = strtok(NULL, " ");
                if (temp != NULL)
                    width_line = atoi(temp);
                else
                    width_line = 1;
            }
        }
        else if (!strcmp(comanda, "draw"))
        {
            comenzi = strtok(NULL, " ");
            if (!strcmp(comenzi, "line"))
            {
                int y1, x1, y2, x2;
                y1 = atoi(strtok(NULL, " "));
                x1 = atoi(strtok(NULL, " "));
                y2 = atoi(strtok(NULL, " "));
                x2 = atoi(strtok(NULL, " "));

                draw(&matrice, y1, x1, y2, x2, draw_color, width_line, infoheader.height, infoheader.width);
            }
            else if (!strcmp(comenzi, "rectangle"))
            {
                int y1, x1, width, height;
                y1 = atoi(strtok(NULL, " "));
                x1 = atoi(strtok(NULL, " "));
                width = atoi(strtok(NULL, " "));
                height = atoi(strtok(NULL, " "));

                draw(&matrice, y1, x1, y1 + width, x1, draw_color, width_line, infoheader.height, infoheader.width);
                draw(&matrice, y1 + width, x1, y1 + width, x1 + height, draw_color, width_line, infoheader.height, infoheader.width);
                draw(&matrice, y1 + width, x1 + height, y1, x1 + height, draw_color, width_line, infoheader.height, infoheader.width);
                draw(&matrice, y1, x1 + height, y1, x1, draw_color, width_line, infoheader.height, infoheader.width);
            }
            else if (!strcmp(comenzi, "triangle"))
            {
                int y1, x1, y2, x2, y3, x3;
                y1 = atoi(strtok(NULL, " "));
                x1 = atoi(strtok(NULL, " "));
                y2 = atoi(strtok(NULL, " "));
                x2 = atoi(strtok(NULL, " "));
                y3 = atoi(strtok(NULL, " "));
                x3 = atoi(strtok(NULL, " "));

                draw(&matrice, y1, x1, y2, x2, draw_color, width_line, infoheader.height, infoheader.width);
                draw(&matrice, y2, x2, y3, x3, draw_color, width_line, infoheader.height, infoheader.width);
                draw(&matrice, y3, x3, y1, x1, draw_color, width_line, infoheader.height, infoheader.width);
            }
        }
        else if (!strcmp(comanda, "fill"))
        {
            int y, x;
            y = atoi(strtok(NULL, " "));
            x = atoi(strtok(NULL, " "));

            fill(&matrice, y, x, draw_color, matrice[x][y], infoheader.height, infoheader.width);
        }
        else if (!strcmp(comanda, "quit"))
        {
            for (int i = 0; i < infoheader.height; i++)
            {
                free(matrice[i]);
            }
            free(matrice);
            free(comanda);
            break;
        }
        free(comanda);
    }

    return 0;
}
