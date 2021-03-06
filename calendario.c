#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#include "calendario.h"
#include "cor.h"



COORD xy = {0, 0};

void gotoxy (int x, int y)
{
        xy.X = x; xy.Y = y; 
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

int ignoraResto(int valor)
{
    while(valor%4!=0) valor--;
    return valor/4; 
}

int codigoMes(int mes)
{
    int resultado;

    switch(mes)
    {
        case 1:
            resultado = 0; break; 
        case 2:
            resultado = 3; break;
        case 3:
            resultado = 3; break;
        case 4:
            resultado = 6; break;
        case 5:
            resultado = 1; break;
        case 6: 
            resultado = 4; break;
        case 7:
            resultado = 6; break;
        case 8:
            resultado = 2; break;
        case 9:
            resultado = 5; break;
        case 10:
            resultado = 0; break; 
        case 11:
            resultado = 3; break;
        case 12:
            resultado = 5; break;
        default:
            break;
    }
    return resultado;
}

char *diaSemana(int dia)
{
    
    switch (dia)
    {
    case 0:
        return ("segunda-feira"); 
    case 1:
        return ("terca-feira"); 
    case 2:
        return ("quarta-feira"); 
    case 3:
        return ("quinta-feira"); 
    case 4:
        return ("sexta-feira"); 
    case 5:
        return ("sabado"); 
    case 6:
        return ("domingo");
    case 7:
        return("data invalida"); 
    default:
        break;
    }
}

int calculaData(int dia, int mes, int ano)
{
    int a, b, c, d, diaSemana; //valores da fórmula 

    if(dia<1 || dia>31 || mes<1 || mes>12) return 7;
    else
    {
        a = ano - 1900;
        b = ignoraResto(a);
        if(ano==1900 || ano%4==0) b--;
        c = codigoMes(mes);
        d = dia - 1;

        diaSemana = (a+b+c+d)%7;

        return diaSemana;
    }  
}

void imprimeDiaSemana(int mes, int dia, int ano)
{
    printf("\nDia da semana:");
    DefineCores(12);
    gotoxy(17,4);
    printf("%s",diaSemana(calculaData(mes, dia, ano)));
    LimpaCores();
    gotoxy(0,8);
    DefineCores(14);
    system("pause");
    LimpaCores();
}

int qtdDiasMes(int mes, int ano)
{
    switch(mes)
    {
        case 1: 
            return 31; 
        case 2: 
            if(ano%4==0 || (ano%100==0 && ano%400!=0)) return 29;
            else return 28;
        case 3: 
            return 31;
        case 4: 
            return 30;
        case 5: 
            return 31;
        case 6: 
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10: 
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
    }
}

char *nomeMes(int mes)
{
    switch(mes)
    {
        case 1: 
            return ("Janeiro"); 
        case 2: 
            return ("Fevereiro");
        case 3: 
            return ("Marco");
        case 4: 
            return ("Abril");
        case 5: 
            return ("Maio");
        case 6: 
            return ("Junho");
        case 7:
            return ("Julho");
        case 8:
            return ("Agosto");
        case 9:
            return ("Setembro");
        case 10: 
            return ("Outubro");
        case 11:
            return ("Novembro");
        case 12:
            return ("Dezembro");
    }
}

void imprimeCalendario(int mes, int ano, TNotas n, int conf)
{
    int i, j=1, qtdDias, comecoMes;
    int x=28,y=2; //coordenadas

    if(conf==0) x=40;
    
    qtdDias = qtdDiasMes(mes, ano);
    comecoMes = calculaData(1, mes, ano); //0 é segunda, 1 é terça... 7 é erro
    if(ano%4==0 || (ano%100==0 && ano%400!=0)) comecoMes++;

    gotoxy(x,y); printf("--------------------------");
    y++; gotoxy(x+7,y); printf("%s, %d", nomeMes(mes),ano);
    y++; gotoxy(x,y); printf("--------------------------");
    y+=2; gotoxy(x,y); printf("D   S   T   Q   Q   S   S");
    y+=2; gotoxy(x,y);

    
    for(i=1;j<=qtdDias;i++)
    {   
        if(i<comecoMes+2) printf("    ");
        else
        {
            if(i==8 || i==15 || i==22 || i==29 || i==36)
            {
                y++;
                gotoxy(x,y);
            }

            if(i==8 || i==15 || i==22 || i==29 || i==36) DefineCores(11);
            else LimpaCores();

            if(confereAniversario(j,mes,n)==1) DefineCores(12);
            if(j<10) 
            {
                printf("0%d  ", j);
            }
            else 
            {
                printf("%d  ",j);
            }
            DefineCores(14);
            j++;
        }
    }

    if(conf==1)
    {
        DefineCores(14);
        y+=4; gotoxy(8,y); printf("Pressione 'p' para o proximo mes, pressione 'a' para o anterior");
        y++; gotoxy(27,y); printf("Caso deseje sair pressione 'q'");
        y++; gotoxy(4,y); printf("Datas com a cor vermelha indicam um ANIVERSARIO, pressione 'n' para ve-los");
        LimpaCores();
    }
    
}

void inicializarNotas(TNotas *notas)
{
    (*notas).qtd = 0;
}

void inserirNota(TNotas *n)
{
    printf("Digite o dia e o mes do aniversario (DD MM): ");
            scanf("%d %d", &(*n).nota[(*n).qtd].dia, &(*n).nota[(*n).qtd].mes);
            printf("\nDigite o nome do aniversariante: ");
            leString((*n).nota[(*n).qtd].nota, 30);
            (*n).qtd++;
            printf("\n\n\n\n");
            DefineCores(14);
            system("pause");
            LimpaCores();
}

void gravaNota(TNotas notas)
{
    FILE *arq;
    arq = fopen("notas.txt", "wt");

    if(arq!=NULL)
    {
        int i;
        for(i=0;i<notas.qtd; i++)
        {
            TNota n = notas.nota[i];
            if (i>0)fprintf(arq,"\n");
            fprintf(arq, "%s,%d,%d", n.nota,n.dia,n.mes);
        }
        fclose(arq);
    }
}

char *lerAte(FILE *arq, char sep, char destino[])
{
    int i = 0;
    int letra;

    while((letra=fgetc(arq))>0 && letra!=sep && i<30)
    {
        destino[i]=letra;
        i++;
    }

    destino[i]='\0';
    return destino;
}

void inserirArq(TNotas *n, TNota nota)
{
    (*n).nota[(*n).qtd]=nota;
    (*n).qtd++;
}

void leNotas(TNotas *n)
{
    FILE *arq;
    arq = fopen("notas.txt", "rt");

    if(arq!=NULL)
    {
        (*n).qtd=0;
        TNota nota;
        while(!feof(arq))
        {
            lerAte(arq,',',nota.nota);
            fscanf(arq,"%d,",&nota.dia);
            fscanf(arq,"%d\n",&nota.mes);
            inserirArq(&*n, nota);
        }
    }
}

void leString(char str[], int max)
{
    fflush(stdin);
    fgets(str,max,stdin);
    if(str[strlen(str)-1]=='\n')
        str[strlen(str)-1]='\0';
}

void imprimeAniversario(TNotas *n, int mes)
{
    int i, c=0;
    struct tm *_data_; 

    time_t segundos; time(&segundos); _data_=localtime(&segundos);

    gotoxy(0,0); printf("Aniversariantes de %s:",nomeMes(mes));

    for(i=0;i<(*n).qtd;i++)
    {
        if((*n).nota[i].mes==mes) 
        {
            gotoxy(3,3+c);
            printf("%s  --  dia %d", (*n).nota[i].nota, (*n).nota[i].dia);
            c++;
        }
    }

    if(c==0) 
    {
        gotoxy(3,3);
        printf("Nenhum aniversariante");
    }

    imprimeCalendario(mes, _data_->tm_year+1900,*n,0);

    DefineCores(14);
    gotoxy(0,15+c); 
    system("pause");
    LimpaCores();

}

void removerAniversariante(TNotas *n)
{
    char remover[30];
    char conf;
    int i, c=0; 

    printf("Dgite o nome do aniversariante que deseja retirar da lista: ");
    leString(remover,30);

    for(i=0;i<(*n).qtd;i++)
    {
        if(strstr((*n).nota[i].nota,remover))
        {
            printf("\nDeseja remover %s dos aniversariantes? [s/n]", (*n).nota[i].nota);
            conf = getch();
            if(conf=='s')
            {
                (*n).nota[i] = (*n).nota[(*n).qtd];
                (*n).qtd--;
            }
            c++;
        }
    }

    if(c==0)
    {
        printf("\n\nAniversariante nao encontrado\n\n");
        DefineCores(14);
        system("pause");
        LimpaCores();
    }
}

int confereAniversario(int dia, int mes, TNotas n)
{
    int i;

    for(i=0; i<n.qtd; i++)
    {
        if(dia==n.nota[i].dia && mes==n.nota[i].mes) return 1;
    }

    return 0;
}