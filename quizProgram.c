//ADAM BALDWIN
//R00176025
//SDH2-A


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Global variables used for counting the total questions and correct answers given
int numQs = 0;
int correctQs = 0;

//Struct that stores questions and answers
typedef struct qnaStruct{
    char *question;
    char *answer;

}qnastruct;


//Function that allows users to pick the difficulty level
int chooseDifficulty(int difficultyLevel){
    printf("Please choose a difficulty level from 1-4");
    scanf("%d", &difficultyLevel);

    return difficultyLevel;
}

//Function that allows the user to input the filepath of the file to be read in
void chooseFilepath(char* filepath){
    printf("Please enter the filepath of the question and answer file e.g. qna.txt");
    scanf("%s",  filepath );
}

//Converts word to uppercase
char* toUppercase(char *word){
    for(int i=0;i<strlen(word);i++){
        word[i] = toupper(word[i]);
    }
}

//Removes the blank spaces at the start of a character array
char* deblank(char* input)
{
    int i,j;
    j = 0;
    char *word=input;
    for (i = 0; i<strlen(input); i++,j++)
    {
        if (input[i]!=' ' && input[i]!='\n')
            word[j]=input[i];
        else
            j--;
    }
    word[j]=0;
    return word;
}

//Reads the data from a file and adds it to a qnastruct
qnastruct *read_array_from_file(char* filepath){
    FILE *file;
    int i;
    char fileArray[500];


    qnastruct *qna ;
    qna = malloc(sizeof(qna));
    if ((file = fopen(filepath, "r")) == NULL) return NULL;
        while ((i = getc(file)) != EOF) {
            fscanf(file, "%[^\n]", fileArray);
            qna = realloc(qna, sizeof(struct qnaStruct)*(numQs+1));


            const char s[4] = "?";
            char *q;
            char *an;

            q = strtok(fileArray, s);
            an = strtok(NULL, s);
            deblank(an);
            toUppercase(an);

            qna[numQs].question = malloc(strlen(q) + 1);
            qna[numQs].answer = malloc(strlen(an) + 1);

            strcpy(qna[numQs].question, q);
            strcpy(qna[numQs].answer, an);
            numQs++;
        }

    return qna;
}

//Determines the type of clue given based on difficulty level
void cluePicker(int difficultyLevel, char *ans){
    char character = '-';
    switch(difficultyLevel){
        case 1:
            printf("Clue:\n");
            printf("?");
            printf("\n");
            break;
        case 2:
            printf("Clue:\n");
            for(int i=0;i<strlen(ans);i++){
                putchar(character);
            }
            printf("\n");
            break;
        case 3:
            printf("Clue:\n");
            printf("%c", ans[0]);
            for(int i=0;i<strlen(ans)-1;i++){
                putchar(character);
            }
            printf("%c", ans[strlen(ans)-1]);
            printf("\n");
            break;
        case 4:
            break;
    }
}

//Prints each question and asks the user for the answer.
//Calls the other appropriate functions to make program work
void quiz(qnastruct *qna, int difficultyLevel){
    char *ans;
    char userAns[45];


    for(int i=0;i<numQs;i++){
        ans = qna[i].answer;

        printf("Question: %s?\n", qna[i].question);

        cluePicker(difficultyLevel, ans);

        printf("Please Enter Your Answer: ");
        scanf("%s", userAns);

        deblank(userAns);
        toUppercase(userAns);

        if(strcmp(ans, userAns) == 0){
            printf("Correct!");
            correctQs++;
        }
        else{
            printf("Incorrect!!!");
            printf("\n%s", userAns);
            printf("\n%s", ans);

        }
        printf("\n");
    }


}


//Writes a string of data to a file
void writeToFile(char *filepath, int correctQs, int numQs, int difficultyLevel){
    FILE *out = fopen("quiz_history.txt", "a");
    fprintf(out,"File: %s, Correct Answers: %d, Total Questions: %d, Difficulty Level: %d", filepath, correctQs, numQs, difficultyLevel);
    fclose(out);
}


int main() {
    qnastruct *qna;
    char filepath[512];
    int difficultyLevel;
    chooseFilepath(filepath);
    difficultyLevel = chooseDifficulty(difficultyLevel);
    qna = read_array_from_file(filepath);
    printf("Number of questions: %d\n", numQs);
    quiz(qna, difficultyLevel);
    writeToFile(filepath, correctQs, numQs, difficultyLevel);

    printf("Number of correct answers: %d\n", correctQs);


}
