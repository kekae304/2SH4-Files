#include <stdio.h>
#include <stdlib.h>

#include "myStringLib.h"

// [COPY AND PASTE] Copy and Paste your Lab 3 Q1 Solution Below

//  This is then your very first reusable custom C library 

int my_strlen(const char * const str1)
{
	// Returns the length of the string - the number of characters, but IGNORING the terminating NULL character

	int len1 = 0; //initializing a variable, len1. will be used to count the number of items in the string

	while(str1[len1] != '\0') //checking if the item in the string is not a null character
	{
		len1++; //incrementing the len to ccheck next item
	}

	return len1; //returning the value of len
}

int my_strcmp(const char * const str1, const char * const str2)
{
	// Return 0 if the two strings are not identical.  Return 1 otherwise.
	
	// Criteria 1: Check their lenghts.  If not the same length, not equal

	int len1 = 0; //initializing a variable, len1. will be used to enumerate item in list
	int len2 = 0; //initializing a variable, len2. will be used to enumerate item in list

	while(str1[len1] != '\0') //checking if the item in the string is not a null character
	{
		len1++; //incrementing the len1 to check next item - also being used to count the size of the string 
	}

	while(str2[len2] != '\0') //checking if the item in the string is not a null character
	{
		len2++; //incrementing the len2 to check next item - also being used to count the size of the string 
	}

	if (len1 != len2) //checking to see that the two counts are not equal
	{
		return 0; //if they are not equal, a 0 will be returned meaning they are not the same
	}

	// Criteria 2: Check their contents char-by-char.  If mismatch found, not equal

	int i = 0; //initializing a variable, i. it will be used to keep track of the position in the list

	for (i; i < len1; i++) //creating a for loop with the variable i that runs when:
						   //i is less than len1 which is the size of the first string because string 1 and 2 are equal in size
	{
		if (str1[i] != str2[i]) //checking if the item in place [i] of string 1 is not the same 
								//as the item in place [i] of string 2
		{
			return 0; //returning 0 if true -> not the same 
		}
	}

	// if passing the two criteria, strings equal
	return 1; 
}

int my_strcmpOrder(const char * const str1, const char * const str2)
{
	/*compare_str alphabetically compares two strings.
    	If str2 is alphabetically smaller than str1 (comes before str1),
    	the function returns a 1, else if str1 is smaller than str2, the
    	function returns a 0.*/

	// if two strings are completely identical in order, return -1.

	// We are NOT looking for any custom alphabetical order - just use the integer values of ASCII character
	const char *p1 = str1; //creating a pointer to the first item of string 1 
	const char *p2 = str2; //creating a pointer to the first item of string 2
	
	while (*p1 && *p2) //while loop -> while both of the pointers are pointing to valid items
	{
		if (*p1 < *p2) //checking to see if pointer of string 1 is smaller than pointer of string 2
		{
			return 0; //returning 0 because string 1 is lexicographically smaller than string 2
		}
		else if (*p1 > *p2) // checking to see if pointer of string 1 is now bigger than pointer of string 2
		{
			return 1; // returning a 1 because string 1 lexicographicsally bigger than the string 2
		}
		p1++; //moving to the next character in the string 
		p2++; //moving to the next character in the string
	}

	if (*p1 == '\0' && *p2 == '\0') //now both strings are equal in size
	{
		return -1; //returning -1 because they are identical to one another
	}
	else if (*p1 == '\0') //now string 1 is shorther than string 2
	{
		return 0; //returning 0 because string 1 is lexicographically less than string 2
	}
	else //finally string 2 is shorter than string 1
	{
		return 1; //returning 1 because string 1 is lexicographically larger than string 2
	}
}

char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;
	
	/*write your implementation here*/
	
	int len1 = 0; //initializing a variable, len1. will be used to enumerate item in list
	int len2 = 0; //initializing a variable, len2. will be used to enumerate item in list

	while(str1[len1] != '\0') //checking if the item in the string is not a null character
	{
		len1++; //incrementing the len1 to check next item - also being used to count the size of the string 
	}

	while(str2[len2] != '\0') //checking if the item in the string is not a null character
	{
		len2++; //incrementing the len2 to check next item - also being used to count the size of the string 
	}

    z = (char *)malloc(len1 + len2 + 1); //allocating memory for the linked string 
										 //also allowing for space for the null character

    if (z != NULL) //if the memory allocation isnt null meaning that is was succesful
	{
		int i = 0; //initializing a variable, i. it will be used to keep track of the position in the list

        for (i; i < len1; i++) //creating a for loop that runs when i is less than the length 1
		{					   //iterating through the characters of string 1
            z[i] = str1[i]; //copying the items at index 'i' in string 1 to corresponding position in z
        }

		int j = 0;  //initializing a variable, j. it will be used to keep track of the position in the list

        for (j; j < len2; j++) //creating a for loop that runs when j is less than the length 2
						       //iterating through the characters of string 2
		{
            z[len1 + j] = str2[j]; //copying the items at index 'j' in string 2 to the after string 1 in z
        }

        z[len1 + len2] = '\0'; //adding a null charcater to the last position of z

	}

	/* finally, return the string*/
	return z;
	// IMPORTANT!!  Where did the newly allocated memory being released?
	// THINK ABOUT MEMORY MANAGEMENT

}
