#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
} Point;

int compareX(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->x - p2->x);
}

int compareY(const void* a, const void* b) {
    Point* p1 = (Point*)a;
    Point* p2 = (Point*)b;
    return (p1->y - p2->y);
}

double dist(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(Point points[], int n) {
    double min = INFINITY;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dist(points[i], points[j]) < min) {
                min = dist(points[i], points[j]);
            }
        }
    }
    return min;
}

double stripClosest(Point strip[], int size, double d) {
    double min = d;
    qsort(strip, size, sizeof(Point), compareY);
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            if (dist(strip[i], strip[j]) < min) {
                min = dist(strip[i], strip[j]);
            }
        }
    }
    return min;
}

double closestUtil(Point points[], int n) {
    if (n <= 3) {
        return bruteForce(points, n);
    }

    int mid = n / 2;
    Point midPoint = points[mid];

    double dl = closestUtil(points, mid);
    double dr = closestUtil(points + mid, n - mid);

    double d = fmin(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(points[i].x - midPoint.x) < d) {
            strip[j] = points[i];
            j++;
        }
    }

    return fmin(d, stripClosest(strip, j, d));
}

double closest(Point points[], int n) {
    qsort(points, n, sizeof(Point), compareX);
    return closestUtil(points, n);
}

int main() {
    int n;
    scanf("%d", &n);
    Point points[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }

    printf("%.10f\n", closest(points, n));
    return 0;
}
