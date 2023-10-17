/*Name: Suman Kafle
  CS 241
  Project 5 
  convert.c*/

/*Project Description:
I have completed this project taking help from the tuttor as well as I am taken idea from the githubs too most of the function are different 
however some ideas might be little bit similar*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*function to print the usage*/
void usage() {
  printf("usage:\n");
  printf("convert IN OUT SIZE NUMBER\n");
  printf("  IN:\n");
  printf("    -inB  NUMBER is binary.\n");
  printf("    -inD  NUMBER is decimal.\n");
  printf("    -inH  NUMBER is hexadecimal.\n");
  printf("\n  OUT:\n");
  printf("    -outB Output will be in binary.\n");
  printf("    -outD Output will be in decimal.\n");
  printf("    -outH Output will be in hexadecimal.\n");
  printf("\n  SIZE:\n");
  printf("    -8    input is an unsigned 8-bit integer.\n");
  printf("    -16   input is an unsigned 16-bit integer.\n");
  printf("    -32   input is an unsigned 32-bit integer.\n");
  printf("    -64   input is an unsigned 64-bit integer.\n");
  printf("\n  NUMBER:\n");
  printf("    number to be converted.\n");
}

/*function return long reduced number after cutting the bits*/
unsigned long reducedNumber(unsigned long value, char* bits)
{
  /*to remove the left part bits if ther are more than 8 bits */
  if (strcmp(bits, "-8") == 0 )
    {
      value &= 0xFF;
    }

  /*to remove the left part bits if ther are more than 16 bits */
  else if (strcmp(bits, "-16") == 0 )
    {
      value &= 0xFFFF;
    }

  /*to remove the left part bits if ther are more than 32 bits */
  else if (strcmp(bits, "-32") == 0 )
    {
      value &= 0xFFFFFFFF;
    }

  /*to remove the left part bits if ther are more than 64 bits */
  else if (strcmp(bits, "-64") == 0 )
    {
      value &= 0xFFFFFFFFFFFFFFFF;
    }
  return value;
}


/*function to print the binary numbers*/
void binary(unsigned long value, int size)
{
  int i;
  for (i = size - 1; i >= 0; i--)
    {
      /*to print the binary number as per the size of bits */
      printf("%lu", (value >> i) & 1);
      if (i % 4 == 0)
	{
	  printf(" ");
	}
    }
}

/*function to print the hexadecimal numbers*/
void hexadecimal(unsigned long value, int size)
{
  int numBytes = (size + 7) / 8;
  int i;
  for (i = numBytes - 1; i >= 0; i--)
    {
      printf("%02lx", (value >> (i * 8)) & 0xFF);
      if (i != 0)
	{
	  printf(" ");
	}
    }
}


void decimal(unsigned long value, int numBits)
{
  int numSpace;
  int len;
  int i;
  int j;
  int numDigit;
  int numCommas;
  char array[100];
  /* to store the value in array */
  sprintf(array, "%lu", value);
  len = strlen(array);

  /* calculate the number of digits required*/
  numDigit = (numBits + 2) / 3;
  /* calculate the number of commas required*/
  numCommas = (len - 1) / 3;
  /*  to calculate the number of spaces required for different cases using the withch operator*/
  switch (numBits)
    {
      /*  to calculate the number of spaces required for 8 bits*/
    case 8:
      numSpace = 3-len-numCommas;
      break;

      /*  to calculate the number of spaces required for 16 bits*/
    case 16:
      numSpace = 6-len-numCommas;
      break;

      /* to calculate the number of spaces required for 32 bits*/
    case 32:
      numSpace = 13-len-numCommas;
      break;

      /*  to calculate the number of spaces required for 64 bits*/
    case 64:
      numSpace = 26-len-numCommas;
    }

  /*  to provide space*/
  for (i = 0; i < numSpace; i++)
    {
      printf(" ");
    }

  /*  to provide comma after every 3 decimal numbers*/
  for (j = 0; j < len; j++)
    {
      printf("%c", array[j]);
      if ((len - j - 1) % 3 == 0 && j != len - 1 && numDigit > 3)
	{
	  printf(",");
	}
    }
}

int main(int argc, char** argv)
{
  int i;
  int j;
  int k;
  char* inputType;
  char* outputType;
  char* bitsSize;
  char* inputNumber;
  unsigned long finalNumber;

  /*to check if there are 5 arguments or not, if not throw error*/
  if (argc != 5)
    {
      printf("\nERROR: incorrect number of arguments\n");
      usage();
      return 0;
    }
  inputType = argv[1];
  outputType = argv[2];
  bitsSize = argv[3];
  inputNumber = argv[4];

  /*to check if argv[1] are whether binary or decimal or hexadecimal, if not throw error*/
  if (strcmp(argv[1], "-inB") != 0 && strcmp(argv[1], "-inD") != 0 && strcmp(argv[1], "-inH") != 0)
    {
      printf("\nERROR: argument 1 must be -inB | -inD | -inH\n");
      usage();
      return 1;
    }

  /*to check if argv[2] are whether binary or decimal or hexadecimal, if not throw error*/
  else if (strcmp(argv[2], "-outB") != 0 && strcmp(argv[2], "-outD") != 0 && strcmp(argv[2], "-outH") != 0)
    {
      printf("\nERROR: argument 2 must be -outB | -outD | -outH\n");
      usage();
      return 1;
    }

  /*to check if argv[3] are whether 8 or 16 or 32 or 64 bits, if not throw error*/
  else if (strcmp(argv[3], "-8") != 0 && strcmp(argv[3], "-16") != 0 && strcmp(argv[3], "-32") != 0 && strcmp(argv[3], "-64") != 0)
    {
      printf("\nERROR: argument 3 must be: -8 | -16 | -32 | -64\n");
      usage();
      return 1;
    }

  if (strcmp(inputType, "-inB") == 0)
    {
      /*to check of the input number is binary*/
      for (i = 0; inputNumber[i] != '\0'; i++)
	{
	  if (inputNumber[i] != '0' && inputNumber[i] != '1')
	    {
	      /*to throw error if the input number  is not a binary*/
	      printf("\nERROR: argument 4 is not a binary integer\n");
	      usage();
	      return 1;
	    }
	}
      finalNumber = strtoul(inputNumber, NULL, 2);
    }

  else if (strcmp(inputType, "-inD") == 0)
    {
      /*to check of the input number is decimal*/
      for (k = 0; inputNumber[k] != '\0'; k++)
	{
	  if (!isdigit(inputNumber[k]))
	    {
	      /*to throw error if the input number  is not a decimal*/
	      printf("\nERROR: argument 4 is not a decimal integer\n");
	      usage();
	      return 1;
	    }
	}
      finalNumber = strtoul(inputNumber, NULL, 10);
    }

  else if (strcmp(inputType, "-inH") == 0)
    {
      /*to check of the input number is  hexadecimal*/
      for (j = 0; inputNumber[j] != '\0'; j++)
	{
	  if (!isxdigit(inputNumber[j]))
	    {
	      /*to throw error if the input number  is not a hexadecimal*/
	      printf("\nERROR: argument 4 is not a hexadecimal integer\n");
	      usage();
	      return 1;
	    }
	}
      finalNumber = strtoul(inputNumber, NULL, 16);
    }

  finalNumber = reducedNumber( finalNumber, bitsSize);

  /*to print the binary  number if the output type is of binary*/
  if (strcmp(outputType, "-outB") == 0)
    {
      binary(finalNumber, atoi(bitsSize + 1));
    }

  /*to print the decimal number if the output type is of decimal*/
  else if (strcmp(outputType, "-outD") == 0)
    {
      decimal(finalNumber, atoi(bitsSize+1));
    }

  /*to print the hexadecimal number if the output type is of hexadecimal*/
  else if (strcmp(outputType, "-outH") == 0)
    {
      hexadecimal(finalNumber, atoi(bitsSize + 1));
    }

  printf("\n");
  return 1;
}
