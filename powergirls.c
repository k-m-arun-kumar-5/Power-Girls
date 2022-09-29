/* ********************************************************************
FILE                   : powergirls.c

PROGRAM DESCRIPTION    : Professor does not have much time as villains will reach the laboratory soon.
He is starting the process but does not know the number of Powerpuff Girls which will be created. 
He needs your help in determining the maximum number of Powerpuff Girls which will be created with the current quantity of ingredients. 

Example:

Professor Utonium requires 3 ingredients to make Powerpuff Girls. The 3 ingredients are present in the laboratory in the given quantity:
To make a Powerpuff Girl, Professor Utonium requires:

3 units of Ingredient A

6 units of Ingredient B

10 units of Ingredient C



The maximum number of Powerpuff Girls which can be created are 3 as after 3, Professor will run out of Ingredient C.

Can you determine the maximum number?



Input Format
The first line of input consists of the number of ingredients, N

The second line of input consists of the N space-separated integers representing the quantity of each ingredient required to create a Powerpuff Girl.


The third line of input consists of the N space-separated integers representing the quantity of each ingredient present in the laboratory.



Constraints
1<= N <=10000000 (1e7)

0<= Quantity_of_ingredient <= LLONG_MAX 

Output Format
Print the required output in a separate line.

Sample TestCase 1
Input
4
2 5 6 3 
20 40 90 50 
Output
8

Time Limit(X):
0.50 sec(s) for each input.
Memory Limit:
512 MB
Source Limit:
100 KB
Allowed Languages:
C, C++, C++11, C++14, C#, Java, Java 8, Kotlin, PHP, PHP 7, Python, Python 3, Perl, Ruby, Node Js, Scala, Clojure, Haskell, Lua, Erlang, Swift, VBnet, Js, Objc, Pascal, Go, F#, D, Groovy, Tcl, Ocaml, Smalltalk, Cobol, Racket, Bash, GNU Octave, Rust, Common LISP, R, Julia, Fortran, Ada, Prolog, Icon, Elixir, CoffeeScript, Brainfuck, Pypy, Lolcode, Nim, Picolisp, Pike, pypy3

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran
	 
KNOWN BUGS            :    

NOTE                  :  Compiled and Tested in Dev-C++ on Windows 7 (32 bit) Desktop OS.
                         Read input from STDIN. Print your output to STDOUT 
                                    
CHANGE LOGS           : 

*****************************************************************************/

/* */
/*

*/

#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>

#define ERROR     1
#define SUCCESS   0
#define ARR_SIZE  20
const long long unsigned int  MIN_INGRE = 1;
const long long unsigned int MAX_INGRE = 10000000LLU;
const long long unsigned int MIN_QUAL = 0;
const long long unsigned int MAX_QUAL =  LLONG_MAX;

int Validate_Qly( long long unsigned int * const, const long long unsigned int);
int main()
{
	char ingr_str[ARR_SIZE];
	long long unsigned int *qual_req_ptr, *qual_aval_ptr, *make_power_ptr, num_ingr, cnt_ingr, min_make_power = MAX_QUAL;
	 
	fflush(stdin);
	memset(ingr_str, '\0', ARR_SIZE);
	fgets(ingr_str, ARR_SIZE, stdin);	
	for (cnt_ingr = 0; ingr_str[cnt_ingr] != '\n'; ++cnt_ingr)
	{
		if(ingr_str[cnt_ingr] < '0' || ingr_str[cnt_ingr] > '9' )
	    {
		  printf("\n ERR: non numeric input data");
		  exit(1);
	    }
	}
	num_ingr = ( long long unsigned int)strtoll(ingr_str, NULL, 10);
	if(num_ingr > MAX_INGRE || num_ingr < MIN_INGRE)
	{
		printf("\n ERR: num ingredients not within range [%llu %llu]", MIN_INGRE, MAX_INGRE);
		exit(1);
	}
    if((qual_req_ptr = ( long long unsigned int *)calloc(num_ingr, sizeof(long long unsigned int))) == NULL)
	{
		printf("\n ERR: required quality memory alloc failed");
		exit(1);
	}
	if((Validate_Qly(qual_req_ptr, num_ingr)) != SUCCESS)
	{
		free(qual_req_ptr);
		exit(1);
	}
	if((qual_aval_ptr = ( long long unsigned int *)calloc(num_ingr, sizeof( long long unsigned int))) == NULL)
	{
		printf("\n ERR: aval quality memoty alloc failed");
		free(qual_req_ptr);
		exit(1);
	}
	if((Validate_Qly(qual_aval_ptr, num_ingr)) != SUCCESS)
	{
		free(qual_req_ptr);
	    free(qual_aval_ptr);
		exit(1);
	}
    if((make_power_ptr = (unsigned long long int *)calloc(num_ingr, sizeof(unsigned long long int))) == NULL)
	{
	    printf("\n ERR: memory alloc failed");
		free(qual_req_ptr);
		free(qual_aval_ptr);
		exit(1);
	}
	for(cnt_ingr = 0; cnt_ingr < num_ingr; ++cnt_ingr)
	{
		if(*(qual_req_ptr + cnt_ingr))
		{
           *(make_power_ptr + cnt_ingr) = *(qual_aval_ptr + cnt_ingr) / *(qual_req_ptr + cnt_ingr);
           if(*(make_power_ptr + cnt_ingr) == 0)
           {
              min_make_power = 0;
              break;
           }
		}
		else
		{
		   *(make_power_ptr + cnt_ingr) = 0;
		}
		//printf("\n INFO: make_power : %llu", *(make_power_ptr + cnt_ingr));
	}
	//printf("\n");
	if(min_make_power != 0)
	{
	   min_make_power = 0;
       for (cnt_ingr = 0; cnt_ingr < num_ingr; ++cnt_ingr)
	   {
	         if(*(make_power_ptr + cnt_ingr) != 0)
	         {
	            if(min_make_power != 0)
	            {
	               if( min_make_power > *(make_power_ptr + cnt_ingr))
	               {
	                  min_make_power = *(make_power_ptr + cnt_ingr);
	               }
	             }
	             else
	             {
	                if(min_make_power < *(make_power_ptr + cnt_ingr))
	                {
		               min_make_power = *(make_power_ptr + cnt_ingr);
	                }
	             }
	         }
	    }
    }
	printf("%llu", min_make_power);
	free(qual_req_ptr);
	free(qual_aval_ptr);
	free(make_power_ptr);
	return 0;
}

int Validate_Qly(long long unsigned int *const base_ptr, const long long unsigned int num_ingr)
{
    char *scan_ptr, qual_str[ARR_SIZE];
	long long unsigned int cnt_ingr = 0, qual_val, *qual_ptr;	
	unsigned int char_pos = 0, qual_char_pos;
   	const char delimiter_char = ' ';
	
    if((scan_ptr = (char *)calloc(17 * num_ingr, sizeof(char ))) == NULL)
	{
		printf("\n ERR: memory alloc failed");
		return ERROR;
	}
	fflush(stdin);
    fgets(scan_ptr, 17 * num_ingr * sizeof(char), stdin);
    /*printf("\n INFO: Entered string : ");
    for(qual_char_pos = 0; qual_char_pos < strlen(scan_ptr); ++qual_char_pos)
    {
    	printf("%c", scan_ptr[qual_char_pos]);
	} */
	for(cnt_ingr = 0; cnt_ingr < num_ingr; ++cnt_ingr)
	{
	    memset(qual_str, '\0', ARR_SIZE);
	    for(;scan_ptr[char_pos] == delimiter_char; ++char_pos )
		{
			;
		}
	    for(qual_char_pos = 0; scan_ptr[char_pos] != delimiter_char; ++char_pos, ++qual_char_pos)
	    {
	        if( scan_ptr[char_pos] < '0' || scan_ptr[char_pos] > '9')
	        {
	            if(scan_ptr[char_pos] == '\n'  )
	            {
	                if(cnt_ingr == num_ingr - 1 )
	                {
                       if(qual_char_pos != 0)
                       {
	                      break; 
                       }
	                }
	                else
	                {
	                    printf("\n ERR: too few input datas: char_pos : %d, char: %d",char_pos, scan_ptr[char_pos] );
	                    free(scan_ptr);
	                    return ERROR;
	                }
	            }
	            printf("\n ERR: non numeric char: %d, char_pos: %u",scan_ptr[char_pos],  char_pos);
	            free(scan_ptr);
	            return ERROR;
	        }
	        qual_str[qual_char_pos] = scan_ptr[char_pos];
	    }
	    qual_str[qual_char_pos] = '\0';
		qual_val = ( long long unsigned int)strtoll(qual_str, NULL ,10);
		if(qual_val > MAX_QUAL)
	    {
	       printf("\n ERR: Quality out of range [%llu, %llu]", MIN_QUAL, MAX_QUAL);
	       free(scan_ptr);
		   return ERROR;
	    }
		qual_ptr = base_ptr + cnt_ingr;
		*qual_ptr = qual_val;
	    //printf("\n INFO: qual input taken: %llu", *qual_ptr);
		for(;scan_ptr[char_pos] == delimiter_char; ++char_pos )
		{
			;
		}
	}
	if(scan_ptr[char_pos] != '\n')
	{
	   printf("\n ERR: Excess number of input datas");
	   free(scan_ptr);
	   return ERROR;
	}
	free(scan_ptr);
	return SUCCESS;
}

