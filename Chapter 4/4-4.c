#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */

void push(double);
double pop(void);
void printtop(void);            // 1st function for the exercise
void duplicatetop(void);        // 2nd function for the exercise
void swaptopelements(void);     // 3th function for the exercise
void clearstack(void);          // 4th function for the exercise
void printallstack(void);


int getop(char []);

int getch(void);
void ungetch(int);

/* reverse Polish calculator */
int main(){

    /* test cases for the new functions */
    push(2.0), push(4.0);
    printtop();             // 4 expected
    
    duplicatetop();
    push(6.0);
    swaptopelements();      

    printallstack();        // stack should now be: 2 4 6 4

    clearstack();

    push(4.0), push(2.0);
    printallstack();        // stack should now be: 4 2

    printtop();             // 4 expected


    /*
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF){
        switch (type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '%':
                op2 = pop();
                push((int) pop() % (int) op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero division\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("error: unknowkn command %s\n", s);
                break;
        }
    }
    */

    return 0;
}

#define MAXVAL 100  /* maximum depth of val stack */

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* printtop: print the top element of the stack without popping */
void printtop(void)
{
    int tmp;
    if (sp > 0){
        tmp = sp - 1;
        printf("top element of the stack: %f\n", val[tmp]);
    } else
        printf("error: stack empty\n");
}

/* duplicatetop: duplicate the top element of the stack */
void duplicatetop(void)
{
    double tmp;
    if (sp > 0){
        tmp = val[sp-1];
        val[sp++] = tmp;
    } else
        printf("error: stack empty\n");
}

/* swaptopelements: swap the two top elements of the stack */
void swaptopelements(void)
{
    double top, bottom;
    double tmp;

    if (sp > 1)
        tmp = val[sp-2], val[sp-2] = val[sp-1], val[sp-1] = tmp;
    else
        printf("error: too few elements on the stack\n");
}

/* clearstack: clear the stack */
void clearstack(void)
{
    sp = 0;
}

/* printallstack: print all the stack */
void printallstack(void)
{
    for (int i = 0; i < sp; i++)
        printf("%f ", val[i]);
    putchar('\n');
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, n;
    int sign;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';

    sign = (c == '-') ? -1 : 1;

    if (!isdigit(c) && c != '.'){
        if ( !( (c == '-' || c == '+') && isdigit(n = getch()) )  ){
            if (c != '\n')
                ungetch(n);
            return c;   /* not a number */
        }
    }
    
    if (c == '-' || c == '+'){
        c = n;
        ungetch(n);
    }
    i = 0;

    if (isdigit(c)) /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
            ;
    
    if (c == '.')   /* collect fraction part */
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    
    return NUMBER;

    /*  doppio a capo? 
        per qualche ragione se togli la riga 98 funziona giusto..
    */
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push a character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}