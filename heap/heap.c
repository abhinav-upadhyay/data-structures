#include <stdio.h>
#include <stdlib.h>

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
swim(int *h, int index)
{
    if (index == 1)
        return;

    if (h[index] < h[parent(index)]) {
        swap(h, index, parent(index));
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

int *
heap(int *a, int len)
{
    int i;
    int size = 1;
    int *heap = malloc(sizeof(int) * len + 1);
    if (heap == NULL)
        return NULL;
    for (i = 0; i < len; i++) {
        heap[size] = a[i];
        swim(heap, size++);
    }
    return heap;
}

static void
print(int *a, int l)
{
    int i;
    for (i = 1; i < l + 1; i++)
        printf("%d\n", a[i]);
}

int
main(int argc, char **argv)
{
    int a[] = {3, 1, 8, 5, 7, 4, 9};
    int *h = heap(a, sizeof(a)/sizeof(a[0]));
    print(a, sizeof(a)/sizeof(a[0]));
    return 0;
}
