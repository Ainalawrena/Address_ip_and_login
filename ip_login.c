#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ip_login.h"

void formulaire(FILE *fic)
{   
    char nom[100];
    char mdp[100];
    printf("entrer votre nom : ");
    scanf("%s",nom);
    printf("entrer votre mot de passe : ");
    scanf("%s",mdp);
    fprintf(fic,"\n%s:%s\n",nom,mdp);
    fclose(fic);
    printf("inscription avec succee! \n");
}

void choix()
{   
    char *chaine=allocation();
    int a,b,c,d;
    FILE* fic=fopen("list.txt","a+");
    if(fic==NULL)
    {
        printf("erreur de l'ouverture du fichier\n");
    }
    int ch;
    printf("==> entrer votre choix :\n");
    printf("1-se connecter\n");
    printf("2-creer un nouveau compte\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1:
        connecter(fic);
        break;
        case 2:
        formulaire(fic);
        execution(fic,a,b,c,d,chaine);
        break;
        default:
        break;
    }
}

void connecter(FILE *fic)
{   
    char nom[100];
    char mdp[100];
    printf("entrer votre nom :");
    scanf("%s",nom);
    printf("entrer votre mot de passe :");
    scanf("%s",mdp);
    recherche(fic,nom,mdp);
}

void recherche(FILE *fic,char *nom,char *mdp)
{   
    char *chaine=allocation();
    int a,b,c,d,rep;
    char line[100];
    char *name;
    char *mot;
    int i;
    while(fgets(line,sizeof(line),fic)!=NULL)
    {   
        line[strcspn(line,"\n")]=0;  
        char *token=strtok(line,":");
        if(token != NULL)
        {
            name=token;
            token=strtok(NULL,":");
            if(token!=NULL)
            {
                mot=token;
                if(strcmp(nom,name)==0 && strcmp(mdp,mot)==0)
                {
                    printf("connection avec succees\n");
                    i=1;
                    execution(fic,a,b,c,d,chaine);
                    exit(1);
                }
            }
        }    
    }
    if(i!=1 || strcmp(nom,name)!=0 && strcmp(mdp,mot)!=0)
    {
            printf("mot de passe ou login incorrect\n");
            printf("reessayez ou quitter ?(1/0) : ");
            scanf("%d",&rep);
            if(rep==1)
            {   
                rewind(fic);
                connecter(fic);
            }
            else
                exit(1);
    }
        fclose(fic);
}

void getip(char *chaine)
{
    printf("Entrer l'addresse ip : ");
    scanf("%s",chaine);
}

char *allocation()
{
    char *chaine=malloc(100*sizeof(char));
    if(chaine == NULL)
    {
        printf("erreur de l'allocation !\n");
        exit(1);
    }
    return chaine;
}

void traitement(char *chaine)
{   
    int a,b,c,d;
    char *token=strtok(chaine,".");
    if(token != NULL)
    {
        a=atoi(token);   
    }
    token=strtok(NULL,".");
    if(token != NULL)
    {
        b=atoi(token);    
    }
    token=strtok(NULL,".");
    if(token != NULL)
    {
        c=atoi(token);  
    }
    token=strtok(NULL,".");
    if(token != NULL)
    {
        d=atoi(token);
    }
    condition_vraie(a);
}

void deconnect()
{   
    char rep[10];
    FILE *fic=fopen("lis.txt","r");
    printf("vous voulez deconnecter (oui/non) ? : ");
    scanf("%s",rep);
    if(strcmp(rep,"oui")==0)
        exit(1);
    else if(strcmp(rep,"non")==0)
       connecter(fic);
    else
        exit(1);
}
void condition_vraie(int a)
{   

    if(a>0 && a<=127)
    {
        printf("==> votre adresse ip et de classe A\n");
        deconnect();
        exit(1);
    }
    if(a>127&& a<=191)
    {
        printf("==> votre adresse ip et de classe B\n");
        deconnect();
        exit(1);
    }
    if(a>191 && a<=223)
    {
        printf("==> votre adresse ip et de classe C\n");
        deconnect();
        exit(1);
    }
    if(a>223 && a<=239)
    {
        printf("==> votre adresse ip et de classe D\n");
        deconnect();
        exit(1);
    }
    if(a>239 && a<=255)
    {
        printf("==> votre adresse ip et de classe E\n");
        deconnect();
        exit(1);
    }
}

void condition_faux(FILE *fic,int a,int b,int c,int d,char *chaine)
{   
    int choix;
    printf("ce n'est pas un adresse!\n");
    printf("Vous voulez quoi?\n");
    printf("1.se deconnecter\n");
    printf("2.quitter\n");
    printf("==> votre choix :");
    scanf("%d",&choix);
    if(choix==1)
    {   
        connecter(fic);
        getip(chaine);
        traitement(chaine);
    }
    else
        exit(1);     
}

void execution(FILE *fic,int a,int b,int c,int d,char *chaine)
{   
    getip(chaine);
    traitement(chaine);
    if(!(a<0 || b<0 || c<0 || d<0 || a>255 || b>255 || c>255 || d<255))
        condition_vraie(a);
    
    else
        condition_faux(fic,a,b,c,d,chaine);
    
}
