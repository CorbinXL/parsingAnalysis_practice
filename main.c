//
//  main.c
//  编译技术实验二
//
//  Created by 抠鼻小新 on 2018/11/2.
//  Copyright © 2018年 抠鼻小新. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define TOKEN_LENGTH 100
char sym;
char Lsym;
char token[TOKEN_LENGTH];
int tokenCount = 0;

FILE * fp_src;
FILE *fp_output;
FILE *fp_err;
FILE *fp_sym;


void E(void);
void E1(void);
void T(void);
void T1(void);
void F(void);
int A(void);
int M(void);
int i(void);
void advance(void);
void erro(void);

void addToken(void);
void printToken(void);
void fprintToken(void);

int main(int argc, const char * argv[]) {
    char *soure = "source.txt";
    char *detail = "detail.txt";
    char *symtab1 = "symtab.txt";
    char *error = "error.txt";
    
    fp_src = fopen(soure, "r");
    if (fp_src == NULL) {
        printf("打开源文件失败！请确定源文件的位置！\n");
        return 0;
    }
    
    fp_output = fopen(detail, "w");
    fp_err = fopen(error, "w");
    fp_sym = fopen(symtab1, "w");
    
    printf("郑殿新-2017221103005\n\n");
    fprintf(fp_output, "郑殿新-2017221103005\n\n");
    fprintf(fp_sym, "郑殿新-2017221103005\n\n");
    fprintf(fp_err, "郑殿新-2017221103005\n\n");
    
    advance();
    E();
}

void E(void)
{
    printf("\nE -> TE'");
    printf("\nSym: %c\n", sym);
    printToken();
    
    fprintf(fp_output, "\nE -> TE'");
    fprintf(fp_output, "\nSym: %c\n", sym);
    fprintToken();
    T();
    E1();
    if(sym == '\n' || sym == EOF)
    {
        printf("\nSuccess!!");
    }
}

void E1(void)
{
    if(A())
    {
        printf("\nE' -> ATE'");
        printf("\nSym: %c\n", sym);
        printToken();
        
        fprintf(fp_output, "\nE' -> ATE'");
        fprintf(fp_output, "\nSym: %c\n", sym);
        printToken();

        printf("\nA -> %c", sym);
        printf("\nSym: %c\n", sym);
        printToken();
        
        fprintf(fp_output, "\nA -> %c", sym);
        fprintf(fp_output, "\nSym: %c\n", sym);
        printToken();
        advance();
        T();
        E1();
    }
    else
    {
        printf("\nT' -> \\0");
        printf("\nSym: %c\n", sym);
        printToken();
        
        fprintf(fp_output, "\nT' -> \\0");
        fprintf(fp_output, "\nSym: %c\n", sym);
        fprintToken();
    }
}

void T()
{
    printf("\nT-> FT'");
    printf("\nSym: %c\n", sym);
    printToken();
    
    fprintf(fp_output, "\nT-> FT'");
    fprintf(fp_output, "\nSym: %c\n", sym);
    fprintToken();

    F();
    T1();
}

void T1()
{
    if(M())
    {
        printf("\nT' -> MFT'");
        printf("\nSym: %c\n", sym);
        printToken();
        
        fprintf(fp_output, "\nT' -> MFT'");
        fprintf(fp_output, "\nSym: %c\n", sym);
        fprintToken();
        
        printf("\nM -> %c", sym);
        printf("\nSym: %c\n", sym);
        printToken();
        
        fprintf(fp_output, "\nM -> %c", sym);
        fprintf(fp_output, "\nSym: %c\n", sym);
        fprintToken();
        
        advance();
        F();
        T1();
    }
    else
    {
        printf("\nT' -> \\0");
        printf("\nSym: %c\n", sym);
        printToken();
        
        fprintf(fp_output, "\nT' -> \\0");
        fprintf(fp_output, "\nSym: %c\n", sym);
        fprintToken();
    }
}

void F()
{
    if(sym == '(')
    {
        printf("\nF -> (E)");
        printf("\nSym: %c\n", sym);
        printToken();
        
        fprintf(fp_output, "\nF -> (E)");
        fprintf(fp_output, "\nSym: %c\n", sym);
        fprintToken();
        
        advance();
        E();
        if(sym == ')')
        {
            printf("\nF -> (E)");
            printf("\nSym: %c\n", sym);
            printToken();
            
            fprintf(fp_output, "\nF -> (E)");
            fprintf(fp_output, "\nSym: %c\n", sym);
            fprintToken();

            advance();
        }
    }
    else if(i())
    {
        printf("\nF -> i");
        printf("\nSym: %c\n", Lsym);
        printToken();
        
        fprintf(fp_output, "\nF -> i");
        fprintf(fp_output, "\nSym: %c\n", Lsym);
        fprintToken();

        return;
    }
    else{
        erro();
    }
}

int A(void)
{
    if(sym == '+' || sym == '-')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int M(void)
{
    if(sym == '*' || sym == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int i(void)
{
    if(sym <= '9' && sym >= '0')
    {
        do{
            Lsym = sym;
            advance();
            if(sym == ' ')
            {
                return 1;
            }
        }while(sym <= '9' && sym >= '0');
        return 1;
    }
    else if((sym <= 'z' && sym >= 'a') || (sym <= 'Z' && sym >= 'A') || sym == '_')
    {

        do{
            fprintf(fp_sym, "%c", sym);
            Lsym = sym;
            advance();
            if(sym == ' ')
            {
                fprintf(fp_sym, "\n");
                return 1;
            }
        }while((sym <= '9' && sym >= '0') || (sym <= 'z' && sym >= 'a') || (sym <= 'Z' && sym >= 'A') || sym == '_');
        fprintf(fp_sym, "\n");

        return 1;
    }
        return 0;
}

void advance()
{
    do{
        sym = fgetc(fp_src);
        addToken();
    }while(sym == ' ');
}

void erro(void)
{
    fprintf(fp_err, "\nFound Erro!!");
    fprintf(fp_err, "\nSym: %c\n", sym);
    
    fprintf(fp_output, "\nFound Erro!!");
    fprintf(fp_output, "\nSym: %c\n", sym);

    printf("\nFound Erro!!");
    printf("\nSym: %c\n", sym);
    exit(0);
}

void addToken(void)
{
    token[tokenCount] = sym;
    ++tokenCount;
}

void printToken(void)
{
    printf("Read-in: ");
    for(int i = 0 ; i < tokenCount ; ++i)
    {
        printf("%c ", token[i]);
    }
    printf("\n\n");
}

void fprintToken(void)
{
    fprintf(fp_output, "Read-in: ");
    for(int i = 0 ; i < tokenCount ; ++i)
    {
        fprintf(fp_output, "%c ", token[i]);
    }
    fprintf(fp_output, "\n\n");

}

