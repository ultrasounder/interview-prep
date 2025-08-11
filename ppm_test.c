#include <stdio.h>

int main(){
    int width = 3;
    int height = 2;

    printf("P3\n%d  %d\n255\n", width, height);
    for(int j = height - 1; j >= 0; j--){
        for (int i = 0; i < width; i++){
            int r = (int)(255.999 * (float)i / (width - 1));
            int g = (int)(255.999 * (float)j / (height - 1));
            int b = 0;
            printf("%d % d %d\n", r, g, b);

        }
    }
    return 0;
}