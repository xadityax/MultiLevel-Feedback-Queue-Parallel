#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

char filelist[100][400];
int N = 0;


void strtolower(char arr[])
{
	for(int i = 0; i < strlen(arr); i++)
	{
		if(isupper(arr[i]) && isalpha(arr[i]))
			arr[i] = tolower((unsigned char)arr[i]); // Typecast to (unsigned char)?
	}
}

void *grep(void *s)
{
	char *temp = (char *)s;
	char search[100];
	strcpy(search, temp);
	char temp2[300];
	strtolower(search);
	for(int i = 0; i < N; i++)
	{
		strcpy(temp2, filelist[i]);
		strtolower(temp2);
		char *res = strstr(temp2, search);
		if(res != NULL)
		{
			printf("%s\n", filelist[i]);
		}
	}
	pthread_exit(NULL);
}


int main(void)
{
	int T, rc;
	pthread_t thread;
	scanf("%d", &N);
	getchar();
	for(int i = 0; i < N; i++)
	{
		scanf("%[^\n]s", filelist[i]);
		getchar();
	}
	scanf("%d", &T);
	getchar();
	for(int i = 0; i < T; i++)
	{
		char search[200];
		scanf("%[^\n]s", search);
		getchar();
		rc = pthread_create(&thread, NULL, grep, (void *)search);
		if(rc)
			printf("Error in grep thread creation : %d\n", rc);
		pthread_join(thread, NULL);
	}
	return 0;
}