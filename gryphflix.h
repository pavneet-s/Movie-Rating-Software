/*
 Student Name: Pavneet Singh
 Student ID: 1121628
 Due Date: January Friday, 2021
 Course: CIS*2500
 I have exclusive control over this submission via my password.
 By including this header comment, I certify that:
 1) I have read and understood the policy on academic integrity.
 2) I have completed Moodle's module on academic integrity.
 3) I have achieved at least 80% on the academic integrity quiz
 I assert that this work is my own. I have appropriate acknowledged
 any and all material that I have used, be it directly quoted or
 paraphrased. Furthermore, I certify that this assignment was written
 by me in its entirety.
*/
#define NUMBER_REVIEWERS 10 //This will represent the number of reviewers.
#define NUMBER_MOVIES 3 //This will represent the number of movies.
#define MAX_STR 50 //This will represent the maximum length of a string.
#define MAX_WORDS 10 //This will represent the max. number of words in a movie title.

#include<stdio.h>
#include<string.h>

struct reviewStruct {
    char reviewer[MAX_STR];
    int feedback[NUMBER_MOVIES];
};
char feedback1[31];
char feedback2[31];
char feedback3[31];
FILE *openFileForReading(char *fileName);
int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR]);
int readReviews( FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS]);
int getMostCriticalReviewers( struct reviewStruct reviews[NUMBER_REVIEWERS],char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR]);
int getMostRecommendedMovies( const char movies[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_REVIEWERS][MAX_STR]);
int predictMovie(const char movie[MAX_STR]);
int enumerateMovie( const char movie[MAX_STR], int charCounts[MAX_WORDS]);
