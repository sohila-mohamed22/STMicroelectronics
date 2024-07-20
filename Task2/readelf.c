#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <elf.h>
#define FILE_PATH "/home/vboxuser/Desktop/task2"

void  parse_elf_header()
{
	 //read the file
        printf("ELF Header: \n");
        FILE* elfFile = fopen(FILE_PATH, "r");
        Elf64_Ehdr elfHeader ;
        fread(&elfHeader , sizeof(elfHeader) , 1 , elfFile ) ;
	//print magic
        printf("\tMagic:     ");
        for(int i = 0 ; i < EI_NIDENT ; i++)
        {
                printf("%02x ", elfHeader.e_ident[i] ) ;
        }
        printf("\n");

        //print class
	   switch (elfHeader.e_ident[EI_CLASS])
        {
                case ELFCLASS32 :
                        printf("\tClass:                             ELF32\n");
                        break ;
                case ELFCLASS64 :
                        printf("\tClass:                             ELF64\n");
                        break ;
                 default :
                        break ;
        }

        //print data
        switch(elfHeader.e_ident[EI_DATA])
        {
                case ELFDATANONE:
                printf("\tData:                              unknown data format\n");
                break ;
                case ELFDATA2LSB:
                printf("\tData:                              Two's complement, little-endian\n");
                break ;
                case ELFDATA2MSB:
                printf("\tData:                              Two's complement, big-endian\n");
                break ;
                default :
                break ;
        }
        
	//print version
	switch(elfHeader.e_ident[EI_VERSION])
        {
                case EV_NONE :
                        printf("\tVersion:                           %d (Invalid version)\n",elfHeader.e_ident[EI_VERSION]);
                        break ;
                case EV_CURRENT :
                        printf("\tVersion:                           %d (Current)\n",elfHeader.e_ident[EI_VERSION]);
                        break ;
                default :
                        break ;
        }
        
	//print operation system
         switch(elfHeader.e_ident[EI_OSABI])
        {
                 case ELFOSABI_SYSV  :
                        printf("\tOS/ABI:                            UNIX - System V\n");
                        break ;
                 case  ELFOSABI_HPUX :
                        printf("\tOS/ABI:                            HP - UX\n");
                        break ;
                 case  ELFOSABI_NETBSD :
                        printf("\tOS/ABI:                            NetBSD\n");
                        break ;
                 case  ELFOSABI_LINUX :
                        printf("\tOS/ABI                             Linux - GNU\n");
                        break ;
                case  ELFOSABI_SOLARIS :
                        printf("\tOS/ABI:                            Solaris\n");
                        break ;
                 case  ELFOSABI_IRIX :
                        printf("\tOS/ABI:                            IRIX\n");
                        break ;
                case  ELFOSABI_FREEBSD :
                        printf("\tOS/ABI:                            FreeBSD\n");
                        break ;
                case  ELFOSABI_TRU64 :
                        printf("\tOS/ABI:                            TRU64\n");
                        break ;
                case  ELFOSABI_ARM :
                        printf("\tOS/ABI:                            ARM\n");
                        break ;
                case  ELFOSABI_STANDALONE :
                        printf("\tOS/ABI:                            Standalone App\n");
                        break ;
                default :
                        break ;
        }
        
	 //print ABI version
	  printf("\tABI Version:                       %d\n", elfHeader.e_ident[EI_ABIVERSION]);
          
          //print type
	  switch(elfHeader.e_type)
        {
                case ET_REL :
                       printf("\tType:                              Relocatable file\n");
                       break ;
                case ET_EXEC :
                       printf("\tType:                              EXEC (Executable file)\n");
                       break ;
                case ET_DYN :
                       printf("\tType:                              Shared object file\n");
                       break ;
                case ET_CORE :
                       printf("\tType:                              Core file\n");
                       break ;
                default :
                       break ;
        }
        
	//print machine
	 switch(elfHeader.e_machine)
        {
        case EM_NONE:
            printf("\tMachine:                          No machine\n");
            break;
        case EM_M32:
            printf("\tMachine:                          AT&T WE 32100\n");
            break;
        case EM_SPARC:
            printf("\tMachine:                          SPARC\n");
            break;
        case EM_386:
            printf("\tMachine:                          Intel 80386\n");
            break;
        case EM_68K:
            printf("\tMachine:                          Motorola 68000\n");
            break;
        case EM_88K:
            printf("\tMachine:                          Motorola 88000\n");
            break;
        case EM_860:
            printf("\tMachine:                          Intel 80860\n");
            break;
        case EM_MIPS:
            printf("\tMachine:                           MIPS R3000 (big-endian only)\n");
            break;
        case EM_PARISC:
            printf("\tMachine:                           HP/PA\n");
            break;
        case EM_SPARC32PLUS:
            printf("\tMachine:                           SPARC with enhanced instruction set\n");
            break;
        case EM_PPC:
            printf("\tMachine:                           PowerPC\n");
            break;
        case EM_PPC64:
            printf("\tMachine:                           PowerPC64\n");
            break;
        case EM_S390:
            printf("\tMachine:                           IBM S390\n");
            break;
        case EM_ARM:
            printf("\tMachine:                           ARM\n");
            break;
        case EM_SH:
            printf("\tMachine:                           SuperH\n");
            break;
        case EM_SPARCV9:
            printf("\tMachine:                           SPARC v9\n");
            break;
        case EM_IA_64:
            printf("\tMachine:                           Intel Itanium\n");
            break;
        case EM_X86_64:
            printf("\tMachine:                           Advanced Micro Devices X86-64\n");
            break;
        case EM_VAX:
            printf("\tMachine:                           Digital VAX\n");
            break;
        default:
            printf("\tMachine:               Unknown (0x%x)\n",elfHeader.e_machine);
            break;
        }
        
	 //print version in hexa
	  switch (elfHeader.e_ident[EI_VERSION])
        {
        case EV_NONE:
            printf("\tVersion:                           None\n");
            break;
        case EV_CURRENT:
            printf("\tVersion:                           0x1\n");
            break;
        default:
            printf("\tVersion:                           Unknown (0x%x)\n", elfHeader.e_ident[EI_VERSION]);
            break;
        }
        
	//print entry address
	printf("\tEntry Point address:               0x%lx\n", elfHeader.e_entry);

	//print start of header
	printf("\tStart of program headers:          %ld (bytes into file)\n",elfHeader.e_phoff);
        printf("\tStart of section headers:          %lu (bytes into file)\n",elfHeader.e_shoff);

	//print flag
	printf("\tFlags:                             0x%x\n", elfHeader.e_flags);

	//print header information
	 printf("\tSize of this header:               %d (bytes)\n",elfHeader.e_ehsize);
        printf("\tSize of program headers:           %d (bytes)\n",elfHeader.e_phentsize);
        printf("\tNumber of program headers:         %d\n",elfHeader.e_phnum);

	//print section information
	printf("\tSize of section headers:           %d (bytes)\n",elfHeader.e_shentsize);
        printf("\tNumber of section headers:         %d \n",elfHeader.e_shnum);
        printf("\tSection header string table index: %d\n",elfHeader.e_shstrndx);
	fclose(elfFile);
}

//section header
void parse_section_headers(void)
{
   printf("This section is still in progress and has not been finalized yet\n") ;
}        

int main (int argc , char** argv)
{
        int opt;
        int header_flag = 0;
        int section_flag = 0;
         // Pars
	 // e command line options
    while ((opt = getopt(argc, argv, "hs")) != -1)
    {
        switch (opt) {
            case 'h':
                header_flag = 1;
                break;
            case 's':
                section_flag = 1 ;
                break;
            default:
                fprintf(stderr, "Usage: %s [-h] [-s] <elf-file>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if(header_flag)
    {
          parse_elf_header();
    }
    if(section_flag)
    {
        parse_section_headers();
    }
    if (!header_flag && !section_flag) 
    {
        fprintf(stderr, "Usage: %s [-h] [-s] <elf-file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}
