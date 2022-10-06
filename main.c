#include<stdio.h>
#include<stdlib.h>

#define file_name "a.out"

struct elf_header{
    unsigned char e_ident[16];
    short e_type;
    short e_machine;
    int e_version;
    long e_entry;
    long e_phoff;
    long e_shoff;
    int e_flags;
    short e_ehsize;
    short e_phentsize;
    short e_phnum;
    short e_shensize;
    short e_shunm;
    short e_shstrndx;
};


int get_file_size(const char* name){

    FILE* file_ptr = fopen(file_name,"r");
    if(file_ptr==NULL) {
        printf("文件打开失败，请检查你的文件名是否输入正确\n");
        return 0;
    }
    
    if(fseek(file_ptr,0,SEEK_END)!=0){
        printf("文件指针设置错误，请仔细检查！！");
        return 0;
    }
    long file_size = ftell(file_ptr);
    fclose(file_ptr);
    return file_size;  
}
void print_elf_healert(void * elf_header){
    struct elf_header* header = (struct elf_header*)(elf_header);
    printf("e_ident:        %s\n",header->e_ident);
    printf("e_type:         %hd\n",header->e_type);
    printf("e_machine:      %hd\n",header->e_machine);
    printf("e_version:      %d\n",header->e_version);
    printf("e_entrt:        0x%lx\n",header->e_entry);
    printf("e_phoff:        0x%lx\n",header->e_phoff);
    printf("e_shoff:        0x%lx\n",header->e_shoff);
    printf("e_flags:        %d\n",header->e_flags);
    printf("e_ehsize:       %hd\n",header->e_ehsize);
    printf("e_phentsize:    %hd\n",header->e_phentsize);
    printf("e_phnum:        %hd\n",header->e_phnum);
    printf("e_shentsize     %hd\n",header->e_shensize);
    printf("e_shnum         %hd\n",header->e_shunm);
    printf("e_shstrndx      %hd\n",header->e_shstrndx);
};

int main(){
    int file_size = get_file_size(file_name);
    void *file_memo = malloc(file_size);
    FILE* file_ptr = fopen(file_name,"r");
    int ne = fread(file_memo,file_size,1,file_ptr);
    fclose(file_ptr);

    //printf("%d\n",ne);

    print_elf_healert(file_memo);

    //printf("%ld\n",sizeof(struct elf_header));
    printf("文件大小为%dbyte\n",file_size);
    free(file_memo);
    return 0;
}