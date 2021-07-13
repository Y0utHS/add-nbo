#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>

uint32_t* readfile(char str[50]) {
    long lSize;
    uint32_t* buffer;
    size_t result;

    FILE* pFile1 = fopen(str, "rb");
    if (pFile1 == NULL)
    {
        printf("파일이 존재하지 않습니다.");
        exit(0);
    }

    fseek(pFile1, 0, SEEK_END);
    lSize = ftell(pFile1);
    rewind(pFile1);

    buffer = (uint32_t*)malloc(sizeof(uint32_t) * lSize);
    if (buffer == NULL)
    {
        printf("메모리 오류");
        exit(0);
    }

    result = fread(buffer, 1, lSize, pFile1);
    if (result != lSize){
        printf("파일 읽기 오류");
        exit(0);
    }


    fclose(pFile1);
    return buffer;
}

int main(int argc, char* argv[]) {
    char *file1 = argv[1];
    char *file2 = argv[2];

    //scanf("%s %s", file1, file2);

    uint32_t* buffer1 = readfile(file1);
    uint32_t buf1 = ntohl(*buffer1);

    uint32_t* buffer2 = readfile(file2);
    uint32_t buf2 = ntohl(*buffer2);
    
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", buf1, buf1, buf2, buf2, buf1+buf2, buf1+buf2);
}