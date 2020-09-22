#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE (2)
#define EXIT (6)

/*prototipo de função.*/
int getInt();
int Menu(void);
void write(void);
void show(void);
void record(void);
void read(void);
void initializer(void);

time_t lt;
/*Struct.*/
struct s_cardReader
{
    char service[60];
    int var;

}scardreader[SIZE];

struct s_cardReaderComp
{
    char service[100];
    int var;
}scardReaderComp;


bool binitializer = false;

int main()
{
    int type;
    initializer();
    binitializer = true;
    char str1cpy [100] = "teste";

  memcpy(scardReaderComp.service,str1cpy,sizeof(struct s_cardReaderComp)+1);
  scardReaderComp.var = 34;

  while(1)
  {
     type = Menu();

   switch(type)
   {
        case 1:
            write();
            break;
        case 2:
            show();
            break;
        case 3:
            read();
            break;
        case 4:
            record();
            break;
        case 5:
            initializer();
            break;
        case 6:
            exit(1);
            break;
       }
  }
    return 0;
}

void initializer(void)
{
    int t;
    for(t =0; t<SIZE; t++)
    {
        memset(&scardreader[t],0,sizeof(struct s_cardReader));
    }

    lt = time(NULL);
    printf("\n");
    printf(ctime(&lt));

    printf("****************************\n");
    printf("Buffer has been reset.\n");
    printf("****************************\n\n");
}

void write(void)
{
    int i;
    bool bservice = false;

    if(binitializer == false)
    {
        initializer();
    }

     binitializer = true;

    for(i =0; i<SIZE; i++)
    {
        while(1)
        {
            if((scardreader[i].service[0] == '\0')&&(bservice == false))
            {
                printf("----------------------------\n");
                printf("Service: ");
                scanf("%s",scardreader[i].service);
            }
            else
            {
                bservice = true;
            }
            if(scardreader[i].var == 0)
            {
                printf("var: ");
                scardreader[i].var = getInt();
                printf("Count: %d\n",i);
                bservice = false;
                printf("----------------------------\n");
            }else
            {
                bservice = false;
                break;
            }
        }
    }
 binitializer = false;
}

void show(void)
{
    int i;
    for(i =0; i<SIZE; i++)
    {
        if(!((scardreader[i].service[0] == '\0')&&(scardreader[i].var == 0)))
        {
            printf("****************************\n");
            printf("Service: %s\n",scardreader[i].service);
            printf("Var:     %d\n",scardreader[i].var);
            printf("Count:   %d\n",i);
            printf("****************************\n");
        }
        else{
            printf("****************************\n");
            printf("Buffer is empty\n");
            printf("****************************\n\n");
            break;
        }
    }
}

void record(void)
{


char str1[30];
int i;
binitializer = false;

    if(!((scardreader[0].service[0] == '\0')
      &&(scardreader[0].var == 0)))
    {

FILE *fp;
        printf("File name:");
        scanf("%s",str1);

        if((fp = fopen(str1,"wb"))==NULL)
        {
            printf("Could not open the file.\n");
            return;
        }

        for(i =0; i<SIZE; i++)
        {
            if(!(fwrite(&scardreader[i],sizeof(struct s_cardReader),SIZE,fp)!=SIZE))
            {
                printf("****************************\n");
                printf("Recorded data.\n");
                printf("Service: %s\n",scardreader[i].service);
                printf("var:     %d\n",scardreader[i].var);
                printf("Count:   %d\n",i);
                printf("****************************\n\n");
            }else{
                printf("Error writing to file.\n");
            }
            fclose(fp);
        }
    }else{
        printf("****************************\n");
        printf("failed to write empty buffer file.\n");
        printf("****************************\n\n");
        binitializer = true;

    }

    if(binitializer == false)
    {
        initializer();
        binitializer = true;
    }
//fclose(fp);
}

void read(void)
{
    FILE *fp;
    char str1[30];
    int i,temp_str1;

    if(binitializer == false)
        initializer();

    printf("File name:");
    scanf("%s",str1);

    if((fp=fopen(str1,"rb"))==NULL)
    {
       printf("****************************\n");
       printf("Could not open the file.\n");
       printf("****************************\n\n");
       return;
    }

    rewind(fp);

    for(i =0; i<SIZE; i++)
    {
        if(fread(&scardreader[i],sizeof(struct s_cardReader),SIZE,fp)!=1)
        {
            if(!(strcmp(scardreader[i].service,scardReaderComp.service)))
            {
                printf("****************************\n");
                printf("Buffer is equal.\n");
                printf("****************************\n\n");
            }else{
                printf("****************************\n");
                printf("Different buffers.\n");
                printf("****************************\n\n");
            }
        }else{
            printf("****************************\n");
            printf("Buffer is empty\n");
            printf("****************************\n\n");
        }
    }
    show();
    fclose(fp);
    binitializer = false;
}

int Menu(void)
{
    int type =0;

    while(1)
    {
        printf("(1) - WRITE\n" );
        printf("(2) - SHOW\n"  );
        printf("(3) - READ\n"  );
        printf("(4) - RECORD\n");
        printf("(5) - CLEAR\n" );
        printf("(6) - EXIT\n"  );

        type = getInt();

        if((!type)||(type > EXIT))
        {
            printf("\n--------------------------\n");
            printf("Enter a valid amount.\n");
            printf("--------------------------\n\n");
        }
        else
        {
            break;
        }
    }
    printf("\n");
    return type;

}

int getInt()
{
	int varInt = 0;
	char c;
	scanf("%d", &varInt);
	while((c = getchar()) != '\n' && c != EOF);
	return varInt;
}
