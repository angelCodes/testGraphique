// ****************************************************************************
// *                                     	                                    *
// *                     		GESTIONNAIRE DE CONTACT                         *
// *                                                                            *
// * Projet D'ETUDE Premier Semestre || Les Fichiers || DJIBRIL SOW || L2IGBTS 
// *					
// *	                     ISI -- JANVIER 2017                                *
// 
//****************************************************************************||
// 

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>

struct contact
{
	long ph;
	char name[20],add[20],email[30];
}list;

char nomCherche[20],name[20];
FILE *fp, *ft;
int i,n,ch,l,trouve;

int main()
{

	main:
	system("cls");    /* ************Menu Principal ***********************  */
	printf("\n\t **** Welcome to  contact Manager ****");
	printf("\n\n\n\t\t\tMAIN MENU\n\t\t=====================\n\t\t[1] Ajouter un Nouveau Contact\n\t\t[2] Lister Contacts\n\t\t[3] Rechercher contact\n\t\t[4] Modifier  Contact\n\t\t[5] Supprimer  Contact\n\t\t[0] Quitter\n\t\t=================\n\t\t");
	printf("Faites Votre Choix:");
	scanf("%d",&ch);

	switch(ch)
	{
		case 0:
			printf("\n\n\t\tEtes-Vous sur de Vouloir Quitter");
			break;
		/* *********************Ajout Nouveaux Contacts************  */
		case 1:

			system("cls");
			fp=fopen("contact.dll","a");
			for (;;)
			{ 
				fflush(stdin);
				printf("Pour quitter tapez espace ' '\nNom (Caracteres Identiques!!!):");
				scanf("%[^\n]",&list.name);

				if(stricmp(list.name,"")==0 || stricmp(list.name," ")==0)
					break;
				fflush(stdin);

				printf("Phone:");
				scanf("%ld",&list.ph);
				fflush(stdin);
				printf("address:");
				scanf("%[^\n]",&list.add);
				fflush(stdin);
				printf("email:");
				gets(list.email);
				printf("\n");
				fwrite(&list,sizeof(list),1,fp);
			}
			fclose(fp);
			break;

		/* *********************Liste contacts*************************  */
		case 2:
			system("cls");
			printf("\n\t\t================================\n\t\t\tListe contacts\n\t\t================================\n\nName\t\tPhone No\t    Address\t\tE-mail ad.\n=================================================================\n\n");

			for(i=97;i<=122;i++)
			{

				fp=fopen("contact.dll","r");
				fflush(stdin);
				trouve=0;
				while(fread(&list,sizeof(list),1,fp)==1)
				{
					if(list.name[0]==i || list.name[0]==i-32)
					{
						printf("\nName\t: %s\nPhone\t: %ld\nAddress\t: %s\nEmail\t: %s\n",list.name,
						list.ph,list.add,list.email);
						trouve++;
					}
				}
				if(trouve!=0)
				{
				    printf("=========================================================== [%c]-(%d)\n\n",i-32,trouve);
				    getch();

				}
				fclose(fp);

			}

			break;



		/* *******************Recherche contacts**********************  */
		case 3:
			system("cls");
			do
			{
				trouve=0;
				printf("\n\n\t..::Recherche de Contact\n\t===========================\n\t..::Nom du Contact a rechercher: ");
				fflush(stdin);
				scanf("%[^\n]",&nomCherche);
				l=strlen(nomCherche);
				fp=fopen("contact.dll","r");

				system("cls");
				printf("\n\n..::Resultat de la Recherche pour: '%s' \n===================================================\n",nomCherche);
				while(fread(&list,sizeof(list),1,fp)==1)
				{
					for(i=0;i<=l;i++)
					name[i]=list.name[i];
					name[l]='\0';
					if(stricmp(name,nomCherche)==0)
					{
						printf("\n..::Name\t: %s\n..::Phone\t: %ld\n..::Address\t: %s\n..::Email\t:%s\n",list.name,list.ph,list.add,list.email);
						trouve++;
						if (trouve%4==0)
						{
							printf("..::Appuyez une touche pour continuer...");
							getch();
						}
					}
				}

				if(trouve==0)
					printf("\n..::Aucun Contact trouve!");
				else
					printf("\n..::%d Contact(s) trouve(s)!",trouve);
				fclose(fp);

				printf("\n ..::Reessayez?\n\n\t[1] Oui\t\t[0] Non\n\t");
				scanf("%d",&ch);
			}while(ch==1);
			break;


		/* *********************Modifier Contacts************************/
		case 4:
			system("cls");
			fp=fopen("contact.dll","r");
			ft=fopen("temp.dat","w");
			fflush(stdin);
			printf("..::Modifier contact\n===============================\n\n\t..::Nom du Contact a Modifier:");
			scanf("%[^\n]",name);

			while(fread(&list,sizeof(list),1,fp)==1)
			{
				if(stricmp(name,list.name)!=0)
				fwrite(&list,sizeof(list),1,ft);
			}

			fflush(stdin);

			printf("\n\n..::Modifier '%s'\n\n",name);

			printf("..::Nom(Caracteres Identiques!!!):");
			scanf("%[^\n]",&list.name);
			fflush(stdin);

			printf("..::Phone:");
			scanf("%ld",&list.ph);
			fflush(stdin);

			printf("..::address:");
			scanf("%[^\n]",&list.add);
			fflush(stdin);

			printf("..::email address:");
			gets(list.email);
			printf("\n");

			fwrite(&list,sizeof(list),1,ft);
			fclose(fp);
			fclose(ft);

			remove("contact.dll");
			rename("temp.dat","contact.dll");
			break;


		/* ********************Supprimer contacts**********************/
		case 5:
			system("cls");
			fflush(stdin);
			printf("\n\n\t..::Supprimer  CONTACT\n\t==========================\n\t..::Nom du Contact a Supprimer:");
			scanf("%[^\n]",&name);

			fp=fopen("contact.dll","r");
			ft=fopen("temp.dat","w");

			while(fread(&list,sizeof(list),1,fp)!=0)
		    if (stricmp(name,list.name)!=0)
			fwrite(&list,sizeof(list),1,ft);
			fclose(fp);
			fclose(ft);
			remove("contact.dll");
			rename("temp.dat","contact.dll");
			break;

		default:
			printf("Choix Indisponible!");
			break;
	}


	printf("\n\n\n..::Faites Votre Choix:\n\n\t[1] Menu Principal\t\t[0] Quitter\n");
	scanf("%d",&ch);
	switch (ch)
	{
		case 1:
			goto main;


		case 0:
			break;

		default:
			printf("Choix Indisponible!");
			break;
	}

	return 0;
}