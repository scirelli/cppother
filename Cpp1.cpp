#include<iostream.h>
#include<string.h>
#include<cctype>


char entry [80];
bool match = false;
int count = 0;

void pass(char s[ ], bool);
void organize (char *word[ ], int);

void main (void)
{
	char *word[40];
	const char * space = " ";
	char *pointer;

	cout<<"Please enter a statement:"<<endl;
	cin.getline(entry, 80);
	
	pass(entry, match);
	cout<<"The new reformatted statement:" << endl << endl << entry << endl << endl << endl;

	pointer = strtok (entry,  space);
	while (pointer != NULL)
	{
		match = false;
        for(int i=0; i<count; i++)
		{
             if(strcmp(word[i], pointer) == 0)
             match = true;
		}
		if(!match)
		{
			word[count] = pointer;
			count++;
		}
		pointer = strtok( NULL, space);
	}//end while

	cout<<"Number of unique words is "<< count << endl << endl;
	organize (word, count);
	cout<<"Words sorted in alphabetical order"<< endl;
	for (int i=0; i<count; i++)
      cout<< word[i] << endl;

	return;

}//end main


