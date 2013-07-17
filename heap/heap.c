#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    size_t size;
} heap;

static void
swap(int *a, int x, int y)
{
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

static int
parent(int x) {
    if (x == 1)
        return 1;
    return x/2;
}

static int
left(int x)
{
    return 2*x;
}

static int
right(int x)
{
    return 2 * x + 1;
}

static void
swim(heap *h, int index)
{
    if (index == 1)
        return;

    if (h->data[index] < h->data[parent(index)]) {
        swap(h->data, index, parent(index));
        swim(h, parent(index));
    }
}

static void
sink(int *h, int index, int size)
{
    if (2 * index < size)
        return ;
    int l = left(index);
    int r = right(index);
    int min = h[l] > h[r]? l: r;
    if (h[index] > h[min]) {
        swap(h, index, min);
        sink(h, min, size);
    }
}

void
insert(heap *h, int x)
{
    h->data[h->size + 1] = x;
    h->size++;
    swim(h, h->size);
}


heap *
build_heap(int *a, int len)
{
    int i;
    int size = 1;
    heap *h = malloc(sizeof(heap));
    if (h == NULL)
        return NULL;
    h->data = malloc(sizeof(int) * len + 1);
    if (h->data == NULL) {
        free(h);
        return NULL;
    }
    h->size = 0;
        
    for (i = 0; i < len; i++) {
        insert(h, a[i]);
    }
    return h;
}

static void
print(heap *h)
{
    int i;
    for (i = 1; i < h->size + 1; i++)
        printf("%d\n", h->data[i]);
}

int
main(int argc, char **argv)
{
    int a[] = {3, 1, 8, 5, 7, 4, 9};
    heap *h = build_heap(a, sizeof(a)/sizeof(a[0]));
    print(h);
    return 0;
}
