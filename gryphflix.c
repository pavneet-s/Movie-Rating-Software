#include "gryphflix.h"

FILE *openFileForReading(char *fileName)
{
    FILE* file_handle;
    file_handle = fopen(fileName, "r"); //file opening
    if(file_handle == NULL)
    {
        return NULL;
    }
    else
    {
       return file_handle;
    }
}

int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR])
{
    int count=0;
    if(file==NULL)
    {
        return 0;
    }
    else
    {
    for(int i=0;i<NUMBER_MOVIES;i++)
    {
        fgets(movieNames[i], 50, file); //getting movie names
        count++;
    }
    if(count != NUMBER_MOVIES)
    {
        return 0;  
    }
    else
    {
    return 1;
    }
    }
}

int readReviews( FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS])
{
    int count=0;
    if(file==NULL)
    {
        return 0;
    }
    else
    {
        for(int i=0; i<NUMBER_REVIEWERS; i++)  //getting data from the file
        {
            fscanf(file,"%s %c %c %c", reviews[i].reviewer, &feedback1[i], &feedback2[i], &feedback3[i]);
            count++;
        }
        for(int j=0;j<NUMBER_REVIEWERS;j++) //storing data
        {
            if((feedback1[j]=='Y')||(feedback1[j]=='y'))
            {
                reviews[j].feedback[0]= 1;
            }
            else if((feedback1[j]=='N')||(feedback1[j]=='n'))
            {
                reviews[j].feedback[0]= 0;
            }
            if((feedback2[j]=='Y')||(feedback2[j]=='y'))
            {
                reviews[j].feedback[1]= 1;
            }
            else if((feedback2[j]=='N')||(feedback2[j]=='n'))
            {
                reviews[j].feedback[1]= 0;
            }
            if((feedback3[j]=='Y')||(feedback3[j]=='y'))
            {
                reviews[j].feedback[2]= 1;
            }
            else if((feedback3[j]=='N')||(feedback3[j]=='n'))
            {
                reviews[j].feedback[2]= 0;
            }
        }
      if(count != NUMBER_REVIEWERS)
        {
            return 0;
        }

    return 1;
    }
}


int getMostCriticalReviewers( struct reviewStruct reviews[NUMBER_REVIEWERS],char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR])
{
    int num=0;
    int max=0;
    int arr[10];
    int count =0;
    for(int i=0; i<NUMBER_REVIEWERS; i++) //counting number of negative reviews 
    {
        count=0;
        if(reviews[i].feedback[0] == 0)
        {
            count++;
        }
        if(reviews[i].feedback[1] == 0)
        {
            count++;
        }
        if(reviews[i].feedback[2] == 0)
        {
            count++;
        }
         arr[i] = count;
    }
    int location =1; 
    for (int c = 1; c < 10; c++) //getting max value of negative reviews from all reviews
    {
    if (arr[c] > arr[location])
    {
      location = c;
    }}
    max = arr[location]; //max value

    for(int i=0; i<NUMBER_REVIEWERS; i++) //finding the most critical reviewer
    {
        count=0;
        if(reviews[i].feedback[0] == 0)
        {
            count++;
        }
        if(reviews[i].feedback[1] == 0)
        {
            count++;
        }
        if(reviews[i].feedback[2] == 0)
        {
            count++;
        }
        if(count==max) //storing the data in mostCriticalReviewers
        {
            strcpy(mostCriticalReviewers[num], reviews[i].reviewer);
            num++;
        }
    }
    return num;
}


int getMostRecommendedMovies( const char movies[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_REVIEWERS][MAX_STR])
{
    int num=0;
    int max=0;
    int nummovies=0;
    for(int i=0;i<NUMBER_MOVIES;i++) //number of movies
    {
        nummovies++;
    }
    int total[nummovies];
    for(int i=0;i<nummovies;i++)
    {
        total[i]=0;
    }
    for(int i=0; i<NUMBER_REVIEWERS; i++) //checking positive feedback on all movies
    {

        if(reviews[i].feedback[0] == 1)
        {
            total[0]++;
        }
        if(reviews[i].feedback[1] == 1)
        {
            total[1]++;
        }
        if(reviews[i].feedback[2] == 1)
        {
            total[2]++;
        }
    }
    int location =1;
    for (int c = 0; c < NUMBER_MOVIES; c++) //generating the max value of positive review
    {
    if (total[c] >= total[location])
    {
      location = c;
    }}
    max = total[location]; //max positve review
    for(int i=0;i<nummovies;i++) //checking which movies has most positive review
    {
        total[i]=0;
    }
    for(int i=0; i<NUMBER_REVIEWERS; i++)
    {

        if(reviews[i].feedback[0] == 1)
        {
            total[0]++;
        }
        if(reviews[i].feedback[1] == 1)
        {
            total[1]++;
        }
        if(reviews[i].feedback[2] == 1)
        {
            total[2]++;
        }
    }
    for(int i=0;i<nummovies;i++) //storing the data to mostRecommendedMovies
    {
        if(total[i]== max)
        {
            strcpy(mostRecommendedMovies[num], movies[i]);
            num++;
        }
    }
    return num;
}
int predictMovie(const char movie[MAX_STR])
{
    char movie1[MAX_STR];
    int points=0, words=1, i=0;
    while(movie[i]!='\0') //counting number of words of the movie
    {
        if(movie[i]==' ' || movie[i]=='\n' || movie[i]=='\t')
        {
            words++;
        }
        i++;
    }
    if(words>2) //if the title has more than 2 words
    {
        points= points-1;
    }
    if(words == 1) //if the title has only 1 word
    {
        points = points-2;
        points = points+2;
    }
    strcpy(movie1, movie); //splitting the movie name into substrings
    char* tk = strtok(movie1," ");
    char word[MAX_WORDS][MAX_STR];
    int w=0;
    while(tk!=NULL)
  {
    strcpy(word[w],tk);
    tk=strtok(NULL," ");
    w++;
  }
  for(int i=0;i<words;i++) //checking the number of character of words in the title
  {
      if(strlen(word[i])==strlen(word[i+1]))
      {
          points = points+2;
      }
  }
  int charact=0;
  if(words>1)
    {
        for(int i=0;i<words;i++)
        {
            charact =strlen(word[i])+charact;
        }
        if(charact%2==0) //if number of characters are even
        {
            printf("+1");
            points = points+1;
        }
    }
if(points<-2)
{
    return -2;
}
else if(points>2)
{
    return 2;
}
else
{
    return points;
}
}

int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS])
{
char movie1[MAX_STR];
int words=1, i=0;
while(movie[i]!='\0') //checking number of words in the title
{
    if(movie[i]==' ' || movie[i]=='\n' || movie[i]=='\t')
        {
            words++;
        }
        i++;
}
strcpy(movie1, movie); //splitting the title into substrings(words)
char* tk = strtok(movie1," ");
char word[MAX_WORDS][MAX_STR];
int w=0;
while(tk!=NULL)
{
    strcpy(word[w],tk);
    tk=strtok(NULL," ");
    w++;
}
for(int i=0;i<words;i++) //number of characters in each word
{
    charCounts[i] = strlen(word[i]);
}
return words;
}




