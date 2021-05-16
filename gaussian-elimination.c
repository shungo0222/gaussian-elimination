#include <stdio.h>
#include <stdlib.h>

int n;
double **a, *b, *ans;

void input(void) {
    printf("How many unknown variables? n = ");
    scanf("%d", &n);

    a = malloc(sizeof(double *) * n);
    for (int i=0; i<n; i++) {
        a[i] = malloc(sizeof(double) * n);
    }
    b = malloc(sizeof(double) * n);
    
    printf("a =\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            scanf("%lf", &a[i][j]);
        }
    }
    printf("b =\n");
    for (int i=0; i<n; i++) {
        scanf("%lf", &b[i]);
    }
}

void release_memory(void) {
    for (int i=0; i<n; i++) {
        free(a[i]);
    }
    free(a);
    free(b);
    free(ans);
}

void get_params(void) {
    for (int i=0; i<3*n; i++) printf("-");
    printf("\n");
    
    printf("Check the parameters\n\n");
    
    printf("a =\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            printf("%lf ", a[i][j]);
        }
        printf("\n");
    }
    printf("b =\n");
    for (int i=0; i<n; i++) {
        printf("%lf ", b[i]);
    }
    printf("\n");

    for (int i=0; i<3*n; i++) printf("-");
    printf("\n");
}

void solve(void) {
    ans = malloc(sizeof(double) * n);

    // forward elimination
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            double x;
            x = -a[j][i] / a[i][i];
            for (int k=0; k<n; k++) {
                a[j][k] += a[i][k] * x;
            }
            b[j] += b[i] * x;
        }
    }

    // backward substitution
    for (int i=n-1; i>=0; i--) {
        double x = 0;
        for (int j=i+1; j<n; j++) {
            x += a[i][j] * ans[j];
        }
        x = -x + b[i];
        ans[i] = x / a[i][i];
    }
}

void get_ans(void) {
    printf("\nThe answer is\n");
    printf("x = ");
    for (int i=0; i<n; i++) {
        printf("%lf ", ans[i]);
    }
    printf("\n\n");
}

int main(void) {
    printf("Let's solve simultaneous linear equations (ax=b) with gaussian elimination!!\n");
    
    input();
    solve();
    // get_params();
    get_ans();
    release_memory();

    return 0;
}