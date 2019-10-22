#include <stdio.h>
#include <string.h>
#define MAX 1024
#define MIN 9
#define TRUE 1

void mostrarAyuda();

int main(int argc, char* argv[])
{
	FILE* entrada;
	FILE* salida=stdout;
	char buffer[MAX];
 	char hexadecimal[MIN];
	const char* fileName=NULL;
	unsigned char shellcode=0, uppercase=0;
	unsigned short int bytes;
	unsigned long long int bytesRestantes;


	//Checking command line arguments

	for (unsigned short int i=1; i<argc; i++)
	{
		if ((!strcmp(argv[i],"-h")) || (!strcmp(argv[i],"--help")))
		{
			mostrarAyuda();
			return 0;
		}

		if ((!strcmp(argv[i],"-v")) || (!strcmp(argv[i],"--version")))
		{
			puts("Hexexe 1.0 (October 22 2019 17:48:54)\n\nWritten by Xtrem\n");
			return 0;
		}

		if (((!strcmp(argv[i],"-s")) || (!strcmp(argv[i],"--shellcode"))) && (!shellcode))
		{
			shellcode=TRUE;
			continue;
		}

		if (((!strcmp(argv[i],"-u")) || (!strcmp(argv[i],"--uppercase"))) && (!uppercase))
		{
			uppercase=TRUE;
			continue;
		}

		if ((!strcmp(argv[i],"-o")) && (salida==stdout) && (i!=argc-1))
		{
			i++;
			salida=fopen(argv[i],"wt");
			continue;
		}

		if (fileName==NULL)
		{
			fileName=argv[i];
			continue;
		}

		printf("Error: Invalid argument %s",argv[i]);
		return -1;
	}

	if (fileName==NULL)
	{
		puts("ERROR: File not specified.");
		return -1;
	}

	if ((entrada=fopen(fileName,"rb"))==NULL)
	{
		printf("File not found: %s\n",fileName);
		return -1;
	}

	if (salida==NULL)
	{
		puts("Error creating output file.");
		return -1;
	}

	fseek(entrada,0,SEEK_END);
	bytesRestantes=ftell(entrada);
	rewind(entrada);
	
	while (bytesRestantes>0)
	{
		memset(buffer,0,sizeof(buffer));
		
		if (bytesRestantes<MAX)
			bytes=fread(buffer,1,bytesRestantes,entrada);
		else
			bytes=fread(buffer,1,MAX,entrada);

		for (unsigned short int i=0; i<bytes; i++)
		{
			if (uppercase)
		 		sprintf(hexadecimal,"%X",buffer[i]);
			else
				sprintf(hexadecimal,"%x",buffer[i]);

			if (shellcode)
				fprintf(salida,"\\x");

			if (strlen(hexadecimal)==1)
				fprintf(salida,"0%c",hexadecimal[0]);
			else if (strlen(hexadecimal)==2)
				fprintf(salida,"%c%c",hexadecimal[0],hexadecimal[1]);
			else
				fprintf(salida,"%c%c",hexadecimal[6],hexadecimal[7]);

			if (!shellcode)
				fputc(' ',salida);
		}

		bytesRestantes-=bytes;
	}

	fclose(entrada);
	fclose(salida);
	return 0;
}

void mostrarAyuda()
{
	puts("Usage: hexexe [OPTIONS] FILE\nOptions:");
	puts("  -h  --help         Display this information.");
	puts("  -o <FILE>          Place the output into a file.");
	puts("  -s  --shellcode    Print the output in shellcode format. (Ex: \\0x0b\\0xd4)");
	puts("  -u  --uppercase    Print the output in uppercase. (Ex: 0B D4)");
	puts("  -v  --version      Display the version information.");
	puts("\nYou can combinate the options -s and -u for a customize output.");
}
