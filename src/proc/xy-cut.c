#include "xy-cut.h"

void HXYCut (uchar *data, size_t X, size_t Y, size_t min, size_t x, size_t y,\
        struct coorList *l)
{
    printf("[INFO] HXYCut()\n");
    if ( X < min && Y < min) {
        uchar *carac = malloc(sizeof(uchar) * X * Y);
        size_t i = 0, j = 0;
        while (i<X && j<Y) {
            carac[i + i*j] = data[(x+i) + (x+i)*(y+j)];
            if (i == X) {
                ++j;
                i = 0;
            }
            else {
                ++i;
            }
        }
        listAdd(l, carac, X, Y);
        return;
    }
    size_t *tmp = getTab(data, (char)0, X, Y, x, y, calloc(Y, sizeof(size_t)));
    size_t i = y, aux;
    while (i < y+Y) {
        //Goes to the first line with at least 1 black pixel
        while (i < y+Y && tmp[i] == 255 * X)
            ++i;
        printf("%zu\n", i);
        aux = i;
        //Goes to the last line with at least 1 black pixel
        while (aux < y+Y && tmp[aux] < 255 * X)
            ++aux;
        if (aux > i) {
            VXYCut(data, X, aux - i, min, x, i, l);
        }
    }
    free(tmp);
}

void VXYCut (uchar *data, size_t X, size_t Y, size_t min, size_t x, size_t y,\
        struct coorList *l)
{
    printf("[INFO] VXYCut launched\n");
    if ( X < min && Y < min) {
        uchar *carac = malloc(sizeof(uchar) * X * Y);
        size_t i = 0, j = 0;
        while (i<X && j<Y) {
            carac[i + i*j] = data[(x+i) + (x+i)*(y+j)];
            if (i == X) {
                ++j;
                i = 0;
            }
            else {
                ++i;
            }
        }
        listAdd(l, carac, X, Y);
        return;
    }
    size_t *tmp = getTab(data, (char)1, X, Y, x, y, calloc(X, sizeof(size_t)));
    size_t i = x, aux;
    while (i < x+X) {
        //Goes to the first column with at least 1 black pixel
        while (i < x+X && tmp[i] == 255 * Y)
            ++i;
        aux = i;
        //Goes to the last column with at least 1 black pixel
        while (aux < x+X && tmp[aux] < 255 * Y)
            ++aux;
        if (aux > i) {
            HXYCut(data, aux - i, Y, min, i, y, l);
        }
    }
    free(tmp);
}

void listAdd(struct coorList *l, uchar *data, size_t X, size_t Y)
{
    printf("[INFO] listAdd()\n");
    while(l->next != NULL)
        l = l->next;
    l->data = data;
    l->X = X;
    l->Y = Y;
}

size_t* getTab(uchar* img, char vert, size_t X, size_t Y, size_t x, size_t y,\
        size_t *tmp) {
    if (!vert) {
        for (size_t j = y; j < Y+y; ++j) {
            for (size_t i = i; i < X+x; ++i) {
                tmp[j - y] += img[i+i*j];
            }
        }
    }
    else {
        for (size_t i = x; i < X+x; ++i) {
            for (size_t j = y; j < Y+y; ++j) {
                tmp[i - x] += img[i+i*j];
            }
        }
    }
    printf("[INFO] tmp[44] == %zu\n", tmp[44]);
    return tmp;
}
