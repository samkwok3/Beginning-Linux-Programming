#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
typedef struct {
    int integer;
    char string[24];
} RECORD;
#define NRECORDS (100)
int main()
{
    RECORD record, *mapped;
    int i, f;
    FILE *fp;
    fp = fopen("records.dat","w+");
    for(i=0; i<NRECORDS; i++) {
        record.integer = i;
        sprintf(record.string,"RECORD-%d",i);
        fwrite(&record,sizeof(record),1,fp);
    }
    fclose(fp);
printf("dddd\n");
    fp = fopen("records.dat","r+");
    fseek(fp,43*sizeof(record),SEEK_SET);
    fread(&record,sizeof(record),1,fp);
    record.integer = 143;
    sprintf(record.string,"RECORD-%d",record.integer);
    fseek(fp,43*sizeof(record),SEEK_SET);
    fwrite(&record,sizeof(record),1,fp);
    fclose(fp);
printf("1111\n");
    f = open("records.dat",O_RDWR);
    if (f != -1) {
        mapped = (RECORD *)mmap(NULL, NRECORDS*sizeof(record),
                                PROT_READ|PROT_WRITE, MAP_SHARED, f, 0);
        if (mapped != MAP_FAILED) {
            printf("11114444++++%d\n", mapped);
            printf("11114444---%d\n", mapped[43].integer);
            mapped[43].integer = 243;
            printf("77771111\n");
            sprintf(mapped[43].string,"RECORD-%d",mapped[43].integer);

            printf("113331\n");
            msync((void *)mapped, NRECORDS*sizeof(record), MS_ASYNC);
            munmap((void *)mapped, NRECORDS*sizeof(record));
        }
        else {
            printf("mmap fail\n");
        }

        close(f);
    }
    else {
        printf("open fail\n");
    }

    exit(0);
}


