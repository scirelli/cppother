#include<iostream.h>
#include<string.h>
#include<cctype>

void organize(char *w[], int count)
{
	char *temp;
    for(int i=0; i<count; i++)
    {
		for(int j=0; j<count; j++)
        {
			if(toupper(*w[i])<toupper(*w[j]))
            {
				temp = w[i];
                w[i] = w[j];
                w[j] = temp;
            }//end if
        }
    }

	return;
}