#include<stdio.h>
#include<stdlib.h>

struct prob //problem
{
  char question[100];
  char opt1[80];
  char opt2[80];
  char opt3[80];
  char opt4[80];
  char ans;
};

struct pattern{
  int plus;
  int minus;
};
void readLine(char *a){
  int i = 0;
  char c;
  while((c = getchar()) != '\n'){
    *(a + i) = c;
    i++;}
 a[i] = '\0';
}

int set_test()
{
  FILE *fp;
  fp = fopen("paper.txt", "w");
  if(fp == NULL){printf("Error in creating the file\n");}
  int i = 0, q;
  printf("No of question to be set =");
  scanf("%d", &q);
  getchar();
  struct pattern marks;
  printf("Marking scheme :\n marks obtained for correct answer = ");
  scanf("%d",&marks.plus);getchar();
  printf("negative marks for wrong question(give the absolute value) = ");
  scanf("%d",&marks.minus);getchar();
  fwrite(&marks,sizeof(marks),1,fp);
  while(i < q)
  {
    struct prob Q; //question
    printf("\nGive the question : ");
    readLine(Q.question);
    printf("Option a : ");
    readLine(Q.opt1);
    printf("Option b : ");
    readLine(Q.opt2);
    printf("Option c : ");
    readLine(Q.opt3);
    printf("option d : ");
    readLine(Q.opt4);
    printf("ans : ");
    scanf("%c", &Q.ans);getchar();
    fwrite(&Q,sizeof(Q),1,fp);
    i++;
  }
  fclose(fp);
  return q;
}
void printTest()
{
  int i = 1;
  FILE *fp;
  fp = fopen("paper.txt","r");
  if (fp == NULL){printf("Error in opening the file\n");}
  struct pattern M;
  fread(&M,sizeof(M),1,fp);
  printf("Marking scheme is : +%d and -%d\n\n",M.plus,M.minus);
  struct prob ques;
  while( fread(&ques,sizeof(ques),1,fp) )
  {
    printf("question %d : %s\n",i,ques.question);
    printf("option a) %s\n",ques.opt1);
    printf("option b) %s\n",ques.opt2);
    printf("option c) %s\n",ques.opt3);
    printf("option d) %s\n",ques.opt4);
    printf("Ans : %c\n",ques.ans);
    i++;
 }
 fclose(fp);
}
int takeTest(int *correct , int *wrong)
{
  int marks = 0, i = 1;
  char ans;
  FILE *fp;
  fp = fopen("paper.txt","r");
  if (fp == NULL){printf("Error in opening the file\n");}
  struct pattern M;
  fread(&M,sizeof(M),1,fp);
  printf("\nThe test is MCQ type,select correct option and Marking scheme is : +%d and -%d\n\n",M.plus,M.minus);
  struct prob ques;
  while( fread(&ques,sizeof(ques),1,fp) )
  {
    printf("question%d : %s\n",i, ques.question);
    printf("option a) %s\n",ques.opt1);
    printf("option b) %s\n",ques.opt2);
    printf("option c) %s\n",ques.opt3);
    printf("option d) %s\n",ques.opt4);
    printf("Ans : ");
    scanf("%c", &ans);getchar();
    if (ans == ques.ans) {marks += M.plus;*correct+= 1;}
    else{marks -= M.minus;*wrong += 1;}
    i++;
  }
  fclose(fp);
  return marks;
}

int main()
{
  int q, mrks_1MCQ;//marks obtained for one correct MCQ
  int marks; // total marks obtained
  char c;
  printf("(a)examiner /(b)examinee :");
  scanf("%c", &c);
  getchar();
  if (c == 'a')
   {
     char op;
     printf("(a)Set test / (b)print test : ");
     scanf("%c", &op);getchar();
     if(op == 'a')
     {
       q = set_test();
     }
     if(op == 'b')printTest();
   }

  if (c == 'b')
  {
    int correct = 0, wrong = 0;
    marks = takeTest(&correct ,&wrong);
    printf("\nMarks obtained = %d\n", marks);
    printf("Test analysis : \nNo of correct answer = %d\n,No of wrong answers = %d\n",correct, wrong);
  }
}
