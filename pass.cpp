#include <string.h>

void pass (char s[80], bool match)
{
     int i = 0;
     int k = 0;
     const char weird[] = "0123456789,./?><';"":[]}{\\|=+-_)(*&^%$#@!~`/";
     
	 while (s[i] != NULL && i<80)
     {
		match = false;
        for(int j=0; j < strlen(weird); j++)
			if(s[i] == weird [j] )
				match = true;
            if(!match)
            {
				s[k]= s[i];
                k++;
            }
        i++;
     }//end while

     for(i=k; i<80;i++)
               s[i] = NULL;
}