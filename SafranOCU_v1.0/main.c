#include <gtk/gtk.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
 GtkWidget *utilisateur,*motDePasse,*kitASup,*FQIASup,*kitATrou,*kitATrouUsr,*FQIATrou,*FQIATrouUsr,*utilisateurASup;
 GtkWidget *newUtilisateur,*newMotDePasse;
//windows names
 GtkWidget *loginScreen,*adminMenu,*userMenu,*addUserMenu,*delUserMenu,*delKitMenu,*delFQIMenu,*findKitMenu,*findFQIMenu,*findKitMenuUsr,*findFQIMenuUsr;
 //const int max_users=100;
 const char admin_log[20]="appadmin";
 const char admin_pass[20]="apppass";
 const int m=10000;
 #define max_users 100
 #define max_bdd 10000
 char *users[max_users];
 char *passwords[max_users];
 char *ref_cable[max_bdd];
 char *kit[max_bdd];
 char *refqi[max_bdd];
		char *fqi[max_bdd];
 char current_user[60]="";

 void clean_string(char* s){
 	int i=0;
 	for (i=0;i<strlen(s);i++){
 		s[i]='\0';
 	}
 }

 char *str_sub (const char *s, unsigned int start, unsigned int end)
 {
    char *new_s = NULL;

    if (s != NULL && start < end)
    {
       new_s = malloc (sizeof (*new_s) * (end - start + 2));
       if (new_s != NULL)
       {
          int i;

          for (i = start; i <= end; i++)
          {
             new_s[i-start] = s[i];
          }
          new_s[i-start] = '\0';
       }
       else
       {
          fprintf (stderr, "Memoire insuffisante\n");
          exit (EXIT_FAILURE);
       }
    }
    return new_s;
 }
 char *split1(char *ligne){
 	char *A=NULL;
 	int i=0;
 	char sep=' ';
 	while (ligne[i]!=sep)
 	{
 	    i++;
 	}
 	A=str_sub(ligne,0,i-1);
 	return A;
 }
 char *split2(char *ligne){
 	char *B=NULL;
 	int len=strlen(ligne);
 	int i=0;
 	char sep=' ';
 	while (ligne[i]!=sep)
 	{
 	    i++;
 	}
 	B=str_sub(ligne,i+1,len);
 	return B;
 }

 int get_n(){
 	int n=0;
 	char c[128]="";


 	FILE* fichier = NULL;
 	fichier = fopen("bdd.txt", "r+");
 	if (fichier != NULL){
 		fgets(c,128,fichier);
 		n=atoi(c);
 		}
 	else
 		{
 	    printf("Impossible d'ouvrir le fichier!!");
 		}
 	fclose(fichier);
 	return n;
 }
 void lire_bdd(char *ref_cable[m], char *kit[m], int k, int m){
 	//printf("\n");
 	FILE* fichier = NULL;
 	fichier = fopen("bdd.txt", "r+");
 	char c[128]="";
 	fgets(c,128,fichier);
 	int i=0;
 	for (i = 0 ; i < k ; i++)
 	{
 		char c[128]="";
 		fgets(c,128,fichier);
 		ref_cable[i]=split1(c);


 		kit[i]=split2(c);
 		int x=0;
 		for(x=0;kit[i][x]!='\0';x++)
 			     {
 			     if(kit[i][x]=='\n')
 			         {
 			          kit[i][x]='\0';
 			         }
 			      }
 	}
 	for (i = k ; i < m ; i++)
 		{


 			ref_cable[i]=NULL;
 			kit[i]=NULL;
 		}

 	fclose(fichier);
 }


 int trouver_kit2(char *e , char *k[m]){

 	int size=get_n();
  lire_bdd(ref_cable,kit,size,m);

 	int i=0;
 	int j=-1;
 	for (i=0;i<size;i++){
 			if ((strcmp(e,k[i])==0)/*&&(strcmp(s,chariots[i])==0)*/){
 				j=i;
 			}
 	}

 	if (j!=-1){
 		/*printf("Cette reference est presente a la position : ");
 		printf("%i",j);
 		printf("\n");*/
 		return j;
 	}
 	else{
 		//printf("Cette reference n'existe pas.");
 		return -1;}
 }

 int trouver_kit2f(char *e , char *k[m]){

  int size=get_n_fqi();

  int i=0;
  int j=-1;
  for (i=0;i<size;i++){
      if ((strcmp(e,k[i])==0)/*&&(strcmp(s,chariots[i])==0)*/){
        j=i;
      }
  }

  if (j!=-1){
    /*printf("Cette reference est presente a la position : ");
    printf("%i",j);
    printf("\n");*/
    return j;
  }
  else{
    //printf("Cette reference n'existe pas.");
    return -1;}
 }


 void supprimer_kit2(char *kits,char *k[m],char *r[m],int m){

 		int size=get_n();


 		size=get_n();
 		/*printf("current size is ");
 		printf("%i",size);
 				printf("\n");*/
 		lire_bdd(r,k,size,m);
 		int i=0;
 		int cmp=0;
 		for (i=0;i<size;i++){
 				if (strcmp(k[i],kits)==0){
 					*k[i]=NULL;
 					*r[i]=NULL;
 					cmp++;
 				}
 		}


 		if (cmp!=0){

 			printf("\n");
 			printf("le kit ");
 			printf("%s",kits);
 			printf(" a ete supprime avec succes ");
 			ecrire_bdd(r, k,size-cmp,m);
 		}else{
 			printf("le Kit ");
 			printf("%s",kits);
 			printf(" n'existe pas!\n");

 		}

 		fflush(stdin);


 }


 void supprimer_kit2f(char *kits,char *k[m],char *r[m],int m){

 		int size=get_n_fqi();


 		size=get_n_fqi();
 		/*printf("current size is ");
 		printf("%i",size);
 				printf("\n");*/
 		lire_fqi(r,k,size,m);
 		int i=0;
 		int cmp=0;
 		for (i=0;i<size;i++){
 				if (strcmp(k[i],kits)==0){
 					*k[i]=NULL;
 					*r[i]=NULL;
 					cmp++;
 				}
 		}


 		if (cmp!=0){

 			printf("/*/*/*/*/*/*/*/*/*/*/*/*/**\n");
 			printf("le kit ");
 			printf("%s",kits);
 			printf(" a ete supprime avec succes ");
 			ecrire_fqi(r, k,size-cmp,m);
 		}else{
 			printf("le Kit ");
 			printf("%s",kits);
 			printf(" n'existe pas!\n");

 		}

 		fflush(stdin);


 }
 int trouver_up2(char *e , char *k[m]){

 	int size=get_n_users();
 	int i=0;
 	int j=-1;
 	for (i=0;i<size;i++){
 			if ((strcmp(e,k[i])==0)/*&&(strcmp(s,chariots[i])==0)*/){
 				j=i;
 			}
 	}

 	if (j!=-1){
 		/*printf("Cette reference est presente a la position : ");
 		printf("%i",j);
 		printf("\n");*/
 		return j;
 	}
 	else{
 		//printf("Cette reference n'existe pas.");
 		return -1;}
 }

 void ajouter_user2(char *users[m], char *passwords[m], char *tempu, char *tempp, int m){


 	int s=get_n_users();
 	s=get_n_users();
 	lire_users(users,passwords,s,m);



 	if (trouver_up2(tempu,users)==-1){
 		users[s]=tempu;
 	int x=0;
 	    for(x=0;users[s][x]!='\0';x++)
 	    				     {
 	    				     if(users[s][x]=='\n')
 	    				         {
 	    				    	 users[s][x]='\0';
 	    				         }
 	    				      }
 	passwords[s]=tempp;

 	    for(x=0;passwords[s][x]!='\0';x++)
 	    				     {
 	    				     if(passwords[s][x]=='\n')
 	    				         {
 	    				    	 passwords[s][x]='\0';
 	    				         }
 	    				      }
 	    char st[128]="";
 	    			strcat(st,users[s]);
 	    			strcat(st," ");
 	    			strcat(st,passwords[s]);


 	    printf("Compte '");
 	    printf("%s",st);
 	    printf("' ");
 	    printf("ajoute!\n");
 	    ecrire_users(users, passwords, s+1, m);}else{
 	    	printf("Utilisateur existe deja");
 	    }

 	    fflush(stdin);

 }
 int trouver_user(char *e , char *users[m],char *passwords[m]){
   int size=get_n_users();
	//lire_users(users,passwords,size,m);
	int i=0;
	int j=-1;

	for (i=0;i<size;i++){

			if ((strcmp(e,users[i])==0)/*&&(strcmp(s,chariots[i])==0)*/){
				j=i;

			}
	}
;
	if (j!=-1){
		/*printf("Cette reference est presente a la position : ");
		printf("%i",j);
		printf("\n");*/
		return j;
	}
	else{
		//printf("Cette reference n'existe pas.");
		return -1;}

 }
 void supprimer_user(char *usr,char *u[m],char *p[m],int m){
   int size=get_n_users();

		size=get_n_users();
		lire_users(users,passwords,size,m);


		int pos=trouver_user(usr,users,passwords);

		if (pos!=-1){

			*users[pos]=NULL;


			*passwords[pos]=NULL;
			printf("le compte ");
			printf("%s",usr);
			printf(" a ete supprime avec succes ");
			ecrire_users(users, passwords,size-1,m);
		}else{
			printf("Compe inexistant!");
		}

		fflush(stdin);



 }

 void lire_users(char *user[m], char *password[m], int k, int max){
	//printf("\n");
	FILE* fichier = NULL;
	fichier = fopen("userslist.txt", "r+");
	char c[128]="";
	fgets(c,128,fichier);
	int i=0;
	for (i = 0 ; i < k ; i++)
	{

		char c[128]="";
		fgets(c,128,fichier);
		user[i]=split1(c);


		password[i]=split2(c);
		int x=0;
		for(x=0;password[i][x]!='\0';x++)
			     {
			     if(password[i][x]=='\n')
			         {
			    	 password[i][x]='\0';
			         }
			      }
	}
	for (i = k ; i < max ; i++)
		{


		user[i]=NULL;
		password[i]=NULL;
		}

	fclose(fichier);
}

void lire_fqi(char *refqi[m], char *fqi[m], int k, int m){
	//printf("\n");
	FILE* fichier = NULL;
	fichier = fopen("fqi.txt", "r+");
	char c[128]="";
	fgets(c,128,fichier);
	int i=0;
	for (i = 0 ; i < k ; i++)
	{
		char c[128]="";
		fgets(c,128,fichier);
		refqi[i]=split1(c);


		fqi[i]=split2(c);
		int x=0;
		for(x=0;fqi[i][x]!='\0';x++)
			     {
			     if(fqi[i][x]=='\n')
			         {
			    	 fqi[i][x]='\0';
			         }
			      }
	}
	for (i = k ; i < m ; i++)
		{


		refqi[i]=NULL;
		fqi[i]=NULL;
		}

	fclose(fichier);
}

void ecrire_users(char *user[m], char *password[m], int k, int m){

  FILE* fichier = NULL;
      fichier = fopen("userslist.txt", "w+");
      int someInt = k;
      char str[12];
      sprintf(str, "%d", someInt);
      fputs(str, fichier);
      fputs("\n", fichier);
      int i=0;
      char s[128]="";

      for (i=0;i<m;i++){
      	clean_string(s);

      	if ((user[i]!=NULL)&&(password[i]!=NULL)){



      	strcat(s,user[i]);
      	strcat(s," ");
      	strcat(s,password[i]);

      	 int x=0;
      	    for(x=0;s[x]!='\0';x++)
      	    				     {
      	    				     if(s[x]=='\n')
      	    				         {
      	    				    	 s[x]='\0';
      	    				         }
      	    				      }
      	    if (strcmp(s," ")!=0){

      	fputs(s, fichier);
      	fputs("\n", fichier);}
      	}
      }

      fclose(fichier);

}

void ecrire_bdd(char *ref_cable[m], char *kit[m], int k, int m){

    FILE* fichier = NULL;
    fichier = fopen("bdd.txt", "w+");
    int someInt = k;
    char str[12];
    sprintf(str, "%d", someInt);
    fputs(str, fichier);
    fputs("\n", fichier);
    int i=0;
    char s[128]="";

    for (i=0;i<m;i++){
    	clean_string(s);

    	if ((ref_cable[i]!=NULL)&&(kit[i]!=NULL)){



    	strcat(s,ref_cable[i]);
    	strcat(s," ");
    	strcat(s,kit[i]);

    	 int x=0;
    	    for(x=0;s[x]!='\0';x++)
    	    				     {
    	    				     if(s[x]=='\n')
    	    				         {
    	    				    	 s[x]='\0';
    	    				         }
    	    				      }
    	    if (strcmp(s," ")!=0){

    	fputs(s, fichier);
    	fputs("\n", fichier);}
    	}
    }

    fclose(fichier);

}

void ecrire_fqi(char *ref_cable[m], char *kit[m], int k, int m){

    FILE* fichier = NULL;
    fichier = fopen("fqi.txt", "w+");
    int someInt = k;
    char str[12];
    sprintf(str, "%d", someInt);
    fputs(str, fichier);
    fputs("\n", fichier);
    int i=0;
    char s[128]="";

    for (i=0;i<m;i++){
    	clean_string(s);

    	if ((ref_cable[i]!=NULL)&&(kit[i]!=NULL)){



    	strcat(s,ref_cable[i]);
    	strcat(s," ");
    	strcat(s,kit[i]);

    	 int x=0;
    	    for(x=0;s[x]!='\0';x++)
    	    				     {
    	    				     if(s[x]=='\n')
    	    				         {
    	    				    	 s[x]='\0';
    	    				         }
    	    				      }
    	    if (strcmp(s," ")!=0){

    	fputs(s, fichier);
    	fputs("\n", fichier);}
    	}
    }

    fclose(fichier);

}

 int get_n_users(){
 	int n=0;
 	char c[128]="";


 	FILE* fichier = NULL;
 	fichier = fopen("userslist.txt", "r+");
 	if (fichier != NULL){
 		fgets(c,128,fichier);
 		n=atoi(c);
 		}
 	else
 		{
 	    printf("Impossible d'ouvrir le fichier!!");
 		}
 	fclose(fichier);
 	return n;
 }
 int get_n_fqi(){
	int n=0;
	char c[128]="";


	FILE* fichier = NULL;
	fichier = fopen("fqi.txt", "r+");
	if (fichier != NULL){
		fgets(c,128,fichier);
		n=atoi(c);
		}
	else
		{
	    printf("Impossible d'ouvrir le fichier!!");
		}
	fclose(fichier);
	return n;
}


 int trouver_up(char *kits, char *ref, char *k[m],char *r[m]){

 	int s=get_n_users();


 	int i=0;
 	int j=-1;
 	for (i=0;i<s;i++){


 			if ((strcmp(kits,k[i])==0)&&(strcmp(ref,r[i])==0)){
 				j=i;
 			}
 	}

 	if (j!=-1){
 		return j;
 	}
 	else{
 		return -1;}
 }



 void login(char* u,char* p, char* us[], char* pw[], int type_session ){
 	deb:
 	printf("Veuillez introduire votre nom d'utilisateur : \n");
 	scanf("%s",u);

 	printf("Veuillez introduire votre mot de passe : \n");
 	scanf("%s",p);



 	if (strcmp(u,admin_log)==0 && strcmp(p,admin_pass)==0){
 		printf("Vous etes co admin\n");
 		type_session=1;
 	}
 	else if (trouver_up(u,p,us,pw)!=-1){
 		printf("Vous etes co utilisateur : ");
 		printf("%s",u);
 		printf("\n");
 		//type_session=0;
 	}else{
 	printf("Utilisateur ou mot de passe incorrect, Recommencer! \n");
 	goto deb;}

 }
/*//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////*/
void quick_message (GtkWidget *parent, gchar *message)
   {
    GtkWidget *dialog, *label, *content_area;
    GtkDialogFlags flags;

    // Create the widgets
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Erreur!",
                                          parent,
                                          flags,
                                          ("_Reessayer"),
                                          GTK_RESPONSE_NONE,
                                          NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 350, 50);
     gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new (message);

    // Ensure that the dialog box is destroyed when the user responds

    g_signal_connect_swapped (dialog,
                              "response",
                              G_CALLBACK (gtk_widget_destroy),
                              dialog);

    // Add the label, and show everything we’ve added

    gtk_container_add (GTK_CONTAINER (content_area), label);
    gtk_widget_show_all (dialog);
   }

   void quick_message_ok (GtkWidget *parent, gchar *message)
      {
       GtkWidget *dialog, *label, *content_area;
       GtkDialogFlags flags;

       // Create the widgets
       flags = GTK_DIALOG_DESTROY_WITH_PARENT;
       dialog = gtk_dialog_new_with_buttons ("Resultat",
                                             parent,
                                             flags,
                                             ("_Ok"),
                                             GTK_RESPONSE_NONE,
                                             NULL);
       gtk_window_set_default_size(GTK_WINDOW(dialog), 350, 50);
       gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
       content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
       label = gtk_label_new (message);

       // Ensure that the dialog box is destroyed when the user responds

       g_signal_connect_swapped (dialog,
                                 "response",
                                 G_CALLBACK (gtk_widget_destroy),
                                 dialog);

       // Add the label, and show everything we’ve added

       gtk_container_add (GTK_CONTAINER (content_area), label);
       gtk_widget_show_all (dialog);
      }


void quick_propos (GtkWindow *parent, gpointer data)
   {
    GtkWidget  *label, *content_area;
    GtkDialogFlags flags;
    GtkWindow *dialog;
    // Create the widgets
    flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_dialog_new_with_buttons ("Bonjour!",loginScreen,flags,("_OK"), GTK_RESPONSE_NONE,NULL);
    gtk_window_set_default_size(GTK_WINDOW(dialog), 350, 50);
    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    label = gtk_label_new ("Cette application a ete cree par NAFTI WASSIM\ndans le cadre d'un stage d'ete 08/2020-09/2020\nContact : w.nafti10@gmail.com");

    // Ensure that the dialog box is destroyed when the user responds

    g_signal_connect_swapped (dialog,
                              "response",
                              G_CALLBACK (gtk_widget_destroy),
                              dialog);

    // Add the label, and show everything we’ve added

    gtk_container_add (GTK_CONTAINER (content_area), label);
    gtk_widget_show_all (dialog);
   }



void deconnecter(GtkWidget *widget, gpointer data)
{
	gtk_widget_hide(adminMenu);
	gtk_widget_hide(userMenu);

	gtk_entry_set_text (motDePasse,"");
	gtk_entry_set_text (utilisateur,"");
	gtk_widget_show_all(loginScreen);
}
void verifKit(GtkWidget *widget, gpointer data)
{
  HINSTANCE chkkit = ShellExecute(
          HWND_DESKTOP, //Parent window
          "open",       //Operation to perform
          "check.exe",       //Path to program
          NULL,         //Parameters
          NULL,         //Default directory
          SW_SHOW);     //How to open

}
void verifFQI(GtkWidget *widget, gpointer data)
{
  HINSTANCE chkFQI = ShellExecute(
          HWND_DESKTOP, //Parent window
          "open",       //Operation to perform
          "check_FQI.exe",       //Path to program
          NULL,         //Parameters
          NULL,         //Default directory
          SW_SHOW);     //How to open
}
void ajouterUtilisateur(GtkWidget *widget, gpointer data)
{
  int n_users=get_n_users();
lire_users(users,passwords,n_users,max_users);
char* TDUser=(char*)gtk_entry_get_text(GTK_ENTRY(newUtilisateur));
char* TDPwd=(char*)gtk_entry_get_text(GTK_ENTRY(newMotDePasse));

if(trouver_up2(TDUser,users)==-1){
ajouter_user2(users,passwords,TDUser,TDPwd,max_users);
quick_message_ok(addUserMenu, "Compte cree avec success");
}else{
  quick_message(addUserMenu,"Utilisateur deja existant! Si vous voulez \nmodifier son mot de passe \nveuillez supprimer le compte\n et ajouter le de nouveau.");
}

}
void supprimerUtilisateur(GtkWidget *widget, gpointer data)
{
  int n_users=get_n_users();

  lire_users(users,passwords,n_users,max_users);

char* TDUser=(char*)gtk_entry_get_text(GTK_ENTRY(utilisateurASup));

if(trouver_user(TDUser,users,passwords)!=-1){

  supprimer_user(TDUser,users,passwords,max_users);

  quick_message_ok(delUserMenu, "Utilisateur supprime avec success");
}else{
  quick_message(delUserMenu,"Cet utilisateur n'existe pas!");
}



}
void supprimerKit(GtkWidget *widget, gpointer data)
{
  int n=get_n();
  lire_bdd(ref_cable,kit,n,m);
char* kitss=(char*)gtk_entry_get_text(GTK_ENTRY(kitASup));
if (trouver_kit2(kitss,kit)!=-1){

  supprimer_kit2(kitss,kit,ref_cable,m);
  char s[60]="le kit ";
  strcat(s,kitss);
  strcat(s, " a ete supprime avec success!");
  quick_message_ok(delKitMenu,s);
}else{
  quick_message(delKitMenu,"kit non trouver");
}
}
void supprimerFQI(GtkWidget *widget, gpointer data)
{

  int n_fqi=get_n_fqi();

  lire_fqi(refqi,fqi,n_fqi,m);

  char* kitss=(char*)gtk_entry_get_text(GTK_ENTRY(FQIASup));

  if (trouver_kit2f(kitss,fqi)!=-1){

    supprimer_kit2f(kitss,fqi,refqi,m);

    char s[60]="le FQI ";
    strcat(s,kitss);
    strcat(s, " a ete supprime avec success!");
    quick_message(delFQIMenu,s);
  }else{
    quick_message(delFQIMenu,"FQI non trouver");
  }


}
void trouverKit(GtkWidget *widget, gpointer data)
{
  int n=get_n();
  lire_bdd(ref_cable,kit,n,m);
  char* kitss=(char*)gtk_entry_get_text(GTK_ENTRY(kitATrou));
  if (trouver_kit2(kitss,kit)!=-1){
    char resultat[500]="";
    denumerer(kitss,resultat,kit,ref_cable);
    quick_message_ok(delFQIMenu,resultat);
  }else{
    quick_message(delFQIMenu,"Ce Kit n'existe pas");
  }

}
void trouverKitUsr(GtkWidget *widget, gpointer data)
{
  int n=get_n();
  lire_bdd(ref_cable,kit,n,m);
  char* kitss=(char*)gtk_entry_get_text(GTK_ENTRY(kitATrouUsr));
  if (trouver_kit2(kitss,kit)!=-1){
    char resultat[500]="";
    denumerer(kitss,resultat,kit,ref_cable);
    quick_message_ok(delFQIMenu,resultat);
  }else{
    quick_message(delFQIMenu,"Ce Kit n'existe pas");
  }

}


void trouverFQI(GtkWidget *widget, gpointer data)
{
  int n_fqi=get_n_fqi();

  lire_fqi(refqi,fqi,n_fqi,m);

  char* kitss=(char*)gtk_entry_get_text(GTK_ENTRY(FQIATrou));
  if (trouver_kit2f(kitss,fqi)!=-1){

    char resultat[500]="";
    denumererf(kitss,resultat,fqi,refqi);

    quick_message_ok(findFQIMenu,resultat);
  }else{
    quick_message(findFQIMenu,"Cet FQI n'existe pas");
  }
}
void trouverFQIUsr(GtkWidget *widget, gpointer data)
{
  int n_fqi=get_n_fqi();

  lire_fqi(refqi,fqi,n_fqi,m);
  char* kitss=(char*)gtk_entry_get_text(GTK_ENTRY(FQIATrouUsr));
  if (trouver_kit2f(kitss,fqi)!=-1){
    char resultat[500]="";
    denumererf(kitss,resultat,fqi,refqi);
    quick_message_ok(findFQIMenuUsr,resultat);
  }else{
    quick_message(findFQIMenuUsr,"Ce Kit n'existe pas");
  }
}



void addUser(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(adminMenu);
  gtk_widget_show_all(addUserMenu);
}
void delUser(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(adminMenu);
  gtk_widget_show_all(delUserMenu);
}
void addKit(GtkWidget *widget, gpointer data)
{
  HINSTANCE adkit = ShellExecute(
          HWND_DESKTOP, //Parent window
          "open",       //Operation to perform
          "ajout.exe",       //Path to program
          NULL,         //Parameters
          NULL,         //Default directory
          SW_SHOW);     //How to open
}
void delKit(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(adminMenu);
  gtk_widget_show_all(delKitMenu);
}
void addFQI(GtkWidget *widget, gpointer data)
{
  HINSTANCE adFQI = ShellExecute(
          HWND_DESKTOP, //Parent window
          "open",       //Operation to perform
          "ajout_fqi.exe",       //Path to program
          NULL,         //Parameters
          NULL,         //Default directory
          SW_SHOW);     //How to open
}
void delFQI(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(adminMenu);
  gtk_widget_show_all(delFQIMenu);
}

void findKit(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(adminMenu);
  gtk_widget_show_all(findKitMenu);
}
void findKitUsr(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(userMenu);
  gtk_widget_show_all(findKitMenuUsr);
}
void findFQI(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(adminMenu);
  gtk_widget_show_all(findFQIMenu);
}
void findFQIUsr(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(userMenu);
  gtk_widget_show_all(findFQIMenuUsr);
}



void goAdmin1(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(addUserMenu);
  gtk_widget_show_all(adminMenu);
  gtk_entry_set_text (newUtilisateur,"");
  gtk_entry_set_text (newMotDePasse,"");


}
void goAdmin2(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(delUserMenu);
  gtk_widget_show_all(adminMenu);
  gtk_entry_set_text (utilisateurASup,"");

}
void goAdmin3(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(delKitMenu);
  gtk_widget_show_all(adminMenu);
  gtk_entry_set_text (kitASup,"");

}
void goAdmin4(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(delFQIMenu);
  gtk_widget_show_all(adminMenu);
  gtk_entry_set_text (FQIASup,"");

}
void goAdmin5(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(findKitMenu);
  gtk_widget_show_all(adminMenu);
gtk_entry_set_text (kitATrou,"");

}
void goAdmin6(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(findFQIMenu);
  gtk_widget_show_all(adminMenu);
gtk_entry_set_text (FQIATrou,"");
}
void goAdmin7(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(findKitMenuUsr);
  gtk_widget_show_all(userMenu);
  gtk_entry_set_text (kitATrouUsr,"");

}
void goAdmin8(GtkWidget *widget, gpointer data)
{
  gtk_widget_hide(findFQIMenuUsr);
  gtk_widget_show_all(userMenu);
  gtk_entry_set_text (FQIATrouUsr,"");
}
void seConnecter(GtkWidget *widget,GtkWidget *two)
{
  int n_users=get_n_users();
  lire_users(users,passwords,n_users,max_users);
	char* usr=(char*)gtk_entry_get_text(GTK_ENTRY(utilisateur));
	char* pwd=(char*)gtk_entry_get_text(GTK_ENTRY(motDePasse));
	if ((strcmp(usr,admin_log)==0)&&(strcmp(pwd,admin_pass)==0)){
		gtk_widget_hide(loginScreen);
		gtk_widget_show_all(adminMenu);

	}else if(trouver_up(usr,pwd,users,passwords)!=-1){
    strcpy(current_user,usr);
    char s[60]="Connecte en tant que : ";
    strcat(s,usr);
    gtk_window_set_title(GTK_WINDOW(userMenu), s);
		gtk_widget_hide(loginScreen);
		gtk_widget_show_all(userMenu);

	}else{
		quick_message(loginScreen,"Nom d'utilisateur ou mot de passe incorrect");
		/*GtkWidget *t;
		GtkDialogFlags flags = GTK_DIALOG_MO/DAL | GTK_DIALOG_DESTROY_WITH_PARENT;
		t = gtk_dialog_new_with_buttons ("Utilisateur ou mot de passe incorrect!",loginScreen,flags,("OK"), GTK_RESPONSE_DELETE_EVENT,NULL);
		gtk_window_set_default_size(GTK_WINDOW(t), 600, 100);
		gtk_dialog_run (t);*/
	}
}


void denumerer(char *source,char *res , char *k[m], char *r[m]){

	int size=get_n();
	int i=0;
	char aff[500]="\n";
	for (i=0;i<size;i++){
			if ((strcmp(source,k[i])==0)){
				strcat(aff,r[i]);
				strcat(aff,"\n");
			}
	}
	strcpy(res,aff);

}

void denumererf(char *source,char *res , char *k[m], char *r[m]){

	int size=get_n_fqi();
	int i=0;
	char aff[500]="\n";
	for (i=0;i<size;i++){
			if ((strcmp(source,k[i])==0)){
				strcat(aff,r[i]);
				strcat(aff,"\n");
			}
	}
	strcpy(res,aff);

}

int main(int argc, char *argv[]) {

    printf("Lecture de nombre d'utilisateurs ...\n");
    int n_users=get_n_users();
      printf("OK!\n");
    printf("Lecture de nombre de ref ...\n");
    int n=get_n();
      printf("OK!\n");
    printf("Lecture de nombre de fqi ...\n");
    int n_fqi=get_n_fqi();
      printf("OK!\n");
    printf("Lecture de nombre d'utilisateurs ...\n");
    lire_users(users,passwords,n_users,max_users);
      printf("OK!\n");
    printf("Lecture de bdd ref ...\n");
    lire_bdd(ref_cable,kit,n,m);
      printf("OK!\n");
    printf("Lecture de bdd fqi ...\n");
    lire_fqi(refqi,fqi,n_fqi,m);
  printf("OK!\n");




  /*printf("***********************\n");
printf("%i",trouver_kit2("900",kit));
  printf("***********************\n");*/


  //containers
  GtkWidget *loginCont,*adminCont,*userCont,*addUserCont,*delUserCont,*delKitCont,*delFQICont,*findKitCont,*findKitContUsr,*findFQICont,*findFQIContUsr;

  GtkWidget *Connexion,*Deconnexion,*annulerAjout,*annulerSupUsr,*ajouter,*supprimerUsr,*supprimerKitbtn,*annulerSupKit,*annulerSupFQI,*supprimerFQIbtn;
  GtkWidget *annulerTrouverKit,*annulerTrouverKitUsr,*trouverKitbtn,*trouverKitbtnUsr,*annulerTrouverFQI,*annulerTrouverFQIUsr,*trouverFQIbtn,*trouverFQIbtnUsr;
  GtkWidget *Quitter,*aPropos;

  GtkWidget *motDePasseTXT,*verifTXT,*managUserTXT,*utilisateurTXT,*managKFTXT,*addUtilisateurTXT,*addMotDePasseTXT,*delUtilisateurTXT,*delKitTXT,*delFQITXT;
  GtkWidget *findKitTXT,*findKitTXTUsr,*findFQITXT,*findFQITXTUsr;
  GtkWidget *check_Kit,*check_FQI,*add_User,*del_User,*add_Kit,*del_Kit,*add_FQI,*del_FQI,*find_Kit,*find_Kit_Usr,*find_FQI,*find_FQI_Usr;


  //printf("%s",users[0]);
  //login(current_user,current_password,users,passwords,type_session);




  gtk_init(&argc, &argv);

/*-------------------------------------------------------------------------------------------------------------------------
 * ----------------------------------------------------------------------------------------------------------------
 * ------------------------------------------------------------------------------------------------
 */  //LOGIN SCREEN
  loginCont = gtk_fixed_new();
  loginScreen = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(loginScreen), "SAFRAN ORDER CHECKING UTILITY V1.0");
  gtk_window_set_default_size(GTK_WINDOW(loginScreen), 1024, 720);
  gtk_window_set_position(GTK_WINDOW(loginScreen), GTK_WIN_POS_CENTER);


  gtk_container_add(GTK_CONTAINER(loginScreen), loginCont);





  aPropos = gtk_button_new_with_label("A propos");
    gtk_fixed_put(GTK_FIXED(loginCont), aPropos, 800, 600);
    gtk_widget_set_size_request(aPropos,180, 60);
  g_signal_connect(G_OBJECT(aPropos), "clicked", G_CALLBACK( quick_propos), NULL);

  utilisateurTXT = gtk_label_new("Nom d'utilisateur: ");
  gtk_fixed_put(GTK_FIXED(loginCont), utilisateurTXT, 100, 100);
  gtk_widget_set_size_request(utilisateurTXT, 80, 30);
  utilisateur=gtk_entry_new();

  gtk_fixed_put(GTK_FIXED(loginCont), utilisateur, 240, 100);

  motDePasseTXT = gtk_label_new("Mot de passe: ");
  gtk_fixed_put(GTK_FIXED(loginCont), motDePasseTXT, 100, 140);
  gtk_widget_set_size_request(motDePasseTXT, 80, 30);
  motDePasse=gtk_entry_new();
  gtk_entry_set_visibility (motDePasse,FALSE);

    gtk_fixed_put(GTK_FIXED(loginCont), motDePasse, 240, 140);

    Connexion = gtk_button_new_with_label("Connexion");
     gtk_fixed_put(GTK_FIXED(loginCont), Connexion, 500, 600);
     gtk_widget_set_size_request(Connexion, 180, 60);
     g_signal_connect(G_OBJECT(Connexion), "clicked", G_CALLBACK( seConnecter ), NULL);

  g_signal_connect(G_OBJECT(loginScreen), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(loginScreen);

  /*-------------------------------------------------------------------------------------------------------------------------
   * ----------------------------------------------------------------------------------------------------------------
   * ------------------------------------------------------------------------------------------------
   */  //ADMIN MENU
  adminCont=gtk_fixed_new();
  adminMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(adminMenu), "Administrateur");
  gtk_window_set_default_size(GTK_WINDOW(adminMenu), 1024, 720);
  gtk_window_set_position(GTK_WINDOW(adminMenu), GTK_WIN_POS_CENTER);
  gtk_container_add(GTK_CONTAINER(adminMenu), adminCont);
  g_signal_connect(G_OBJECT(adminMenu), "destroy",
       G_CALLBACK(gtk_main_quit), NULL);

  verifTXT = gtk_label_new("Verification des commandes: ");
  gtk_fixed_put(GTK_FIXED(adminCont), verifTXT, 50, 50);
  gtk_widget_set_size_request(verifTXT, 80, 30);

  check_Kit = gtk_button_new_with_label("Check commande Kit");
  gtk_fixed_put(GTK_FIXED(adminCont), check_Kit, 150, 100);
  gtk_widget_set_size_request(check_Kit, 180, 60);
  g_signal_connect(G_OBJECT(check_Kit), "clicked", G_CALLBACK( verifKit ), NULL);

  check_FQI = gtk_button_new_with_label("Check commande FQI");
  gtk_fixed_put(GTK_FIXED(adminCont), check_FQI, 400, 100);
  gtk_widget_set_size_request(check_FQI, 180, 60);
  g_signal_connect(G_OBJECT(check_FQI), "clicked", G_CALLBACK( verifFQI ), NULL);

  managUserTXT = gtk_label_new("Gestion des untilisateurs: ");
    gtk_fixed_put(GTK_FIXED(adminCont), managUserTXT, 50, 175);
    gtk_widget_set_size_request(managUserTXT, 80, 30);

  add_User = gtk_button_new_with_label("Ajouter utilisateur");
  gtk_fixed_put(GTK_FIXED(adminCont), add_User, 150, 225);
  gtk_widget_set_size_request(add_User, 180, 60);
  g_signal_connect(G_OBJECT(add_User), "clicked", G_CALLBACK( addUser ), NULL);

  del_User = gtk_button_new_with_label("Supprimer utilisateur");
  gtk_fixed_put(GTK_FIXED(adminCont), del_User, 400, 225);
  gtk_widget_set_size_request(del_User, 180, 60);
  g_signal_connect(G_OBJECT(del_User), "clicked", G_CALLBACK( delUser ), NULL);

  managKFTXT = gtk_label_new("Gestion des KIT et FQI: ");
    gtk_fixed_put(GTK_FIXED(adminCont), managKFTXT, 50, 300);
    gtk_widget_set_size_request(managKFTXT, 80, 30);

  add_Kit = gtk_button_new_with_label("Ajouter Kit");
  gtk_fixed_put(GTK_FIXED(adminCont), add_Kit, 150, 350);
  gtk_widget_set_size_request(add_Kit, 180, 60);
  g_signal_connect(G_OBJECT(add_Kit), "clicked", G_CALLBACK( addKit ), NULL);

  del_Kit = gtk_button_new_with_label("Supprimer Kit");
    gtk_fixed_put(GTK_FIXED(adminCont), del_Kit, 150, 450);
    gtk_widget_set_size_request(del_Kit, 180, 60);
g_signal_connect(G_OBJECT(del_Kit), "clicked", G_CALLBACK( delKit ), NULL);

    add_FQI = gtk_button_new_with_label("Ajouter FQI");
      gtk_fixed_put(GTK_FIXED(adminCont), add_FQI, 400, 350);
      gtk_widget_set_size_request(add_FQI, 180, 60);
g_signal_connect(G_OBJECT(add_FQI), "clicked", G_CALLBACK( addFQI ), NULL);

      del_FQI = gtk_button_new_with_label("Supprimer FQI");
        gtk_fixed_put(GTK_FIXED(adminCont), del_FQI, 400, 450);
        gtk_widget_set_size_request(del_FQI, 180, 60);
        g_signal_connect(G_OBJECT(del_FQI), "clicked", G_CALLBACK( delFQI ), NULL);

        find_Kit = gtk_button_new_with_label("Trouver kit");
               gtk_fixed_put(GTK_FIXED(adminCont), find_Kit, 150, 550);
               gtk_widget_set_size_request(find_Kit, 180, 60);
        g_signal_connect(G_OBJECT(find_Kit), "clicked", G_CALLBACK( findKit ), NULL);

               find_FQI = gtk_button_new_with_label("Trouver FQI");
                      gtk_fixed_put(GTK_FIXED(adminCont), find_FQI, 400, 550);
                      gtk_widget_set_size_request(find_FQI, 180, 60);
g_signal_connect(G_OBJECT(find_FQI), "clicked", G_CALLBACK( findFQI ), NULL);


                      Deconnexion = gtk_button_new_with_label("Deconnexion");
                                            gtk_fixed_put(GTK_FIXED(adminCont), Deconnexion, 750, 550);
                                            gtk_widget_set_size_request(Deconnexion, 180, 60);
                                            g_signal_connect(G_OBJECT(Deconnexion), "clicked", G_CALLBACK(  deconnecter ), NULL);

    /*-------------------------------------------------------------------------------------------------------------------------
      * ----------------------------------------------------------------------------------------------------------------
      * ------------------------------------------------------------------------------------------------
      */  //USER MENU
       userCont=gtk_fixed_new();
     userMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);

       gtk_window_set_title(GTK_WINDOW(userMenu), "Utilisateur: ");
       gtk_window_set_default_size(GTK_WINDOW(userMenu), 1024, 720);
       gtk_window_set_position(GTK_WINDOW(userMenu), GTK_WIN_POS_CENTER);
       gtk_container_add(GTK_CONTAINER(userMenu), userCont);
       g_signal_connect(G_OBJECT(userMenu), "destroy",
           G_CALLBACK(gtk_main_quit), NULL);

       Deconnexion = gtk_button_new_with_label("Deconnexion");
       gtk_fixed_put(GTK_FIXED(userCont), Deconnexion, 750, 550);
       gtk_widget_set_size_request(Deconnexion, 180, 60);
       g_signal_connect(G_OBJECT(Deconnexion), "clicked", G_CALLBACK(  deconnecter ), NULL);




       verifTXT = gtk_label_new("Verification des commandes: ");
         gtk_fixed_put(GTK_FIXED(userCont), verifTXT, 50, 50);
         gtk_widget_set_size_request(verifTXT, 80, 30);


         check_Kit = gtk_button_new_with_label("Check commande Kit");
         gtk_fixed_put(GTK_FIXED(userCont), check_Kit, 150, 100);
         gtk_widget_set_size_request(check_Kit, 180, 60);
         g_signal_connect(G_OBJECT(check_Kit), "clicked", G_CALLBACK( verifKit ), NULL);


         check_FQI = gtk_button_new_with_label("Check commande FQI");
         gtk_fixed_put(GTK_FIXED(userCont), check_FQI, 400, 100);
         gtk_widget_set_size_request(check_FQI, 180, 60);
         g_signal_connect(G_OBJECT(check_FQI), "clicked", G_CALLBACK( verifFQI ), NULL);

         managKFTXT = gtk_label_new("Gestion des KIT et FQI: ");
            gtk_fixed_put(GTK_FIXED(userCont), managKFTXT, 50, 175);
            gtk_widget_set_size_request(managKFTXT, 80, 30);

         find_Kit_Usr = gtk_button_new_with_label("Trouver kit");
                   gtk_fixed_put(GTK_FIXED(userCont), find_Kit_Usr, 150, 225);
                   gtk_widget_set_size_request(find_Kit_Usr, 180, 60);
g_signal_connect(G_OBJECT(find_Kit_Usr), "clicked", G_CALLBACK( findKitUsr ), NULL);


                   find_FQI_Usr = gtk_button_new_with_label("Trouver FQI");
                          gtk_fixed_put(GTK_FIXED(userCont), find_FQI_Usr, 400, 225);
                          gtk_widget_set_size_request(find_FQI_Usr, 180, 60);
                          g_signal_connect(G_OBJECT(find_FQI_Usr), "clicked", G_CALLBACK( findFQIUsr ), NULL);
       /*-------------------------------------------------------------------------------------------------------------------------
          * ----------------------------------------------------------------------------------------------------------------
          * ------------------------------------------------------------------------------------------------
          */  //ADD user
          addUserCont=gtk_fixed_new();
         addUserMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
          gtk_window_set_title(GTK_WINDOW(addUserMenu), "Ajout d'utilisateur");
          gtk_window_set_default_size(GTK_WINDOW(addUserMenu), 1024, 720);
          gtk_window_set_position(GTK_WINDOW(addUserMenu), GTK_WIN_POS_CENTER);
          gtk_container_add(GTK_CONTAINER(addUserMenu), addUserCont);
          g_signal_connect(G_OBJECT(addUserMenu), "destroy",
              G_CALLBACK(gtk_main_quit), NULL);


              addUtilisateurTXT = gtk_label_new("Nom d'utilisateur a ajouter : ");
              gtk_fixed_put(GTK_FIXED(addUserCont), addUtilisateurTXT, 100, 100);
              gtk_widget_set_size_request(addUtilisateurTXT, 80, 30);
              newUtilisateur=gtk_entry_new();
              gtk_fixed_put(GTK_FIXED(addUserCont), newUtilisateur, 280, 100);

              addMotDePasseTXT = gtk_label_new("Son mot de passe : ");
              gtk_fixed_put(GTK_FIXED(addUserCont), addMotDePasseTXT, 100, 140);
              gtk_widget_set_size_request(addMotDePasseTXT, 80, 30);
              newMotDePasse=gtk_entry_new();
              gtk_fixed_put(GTK_FIXED(addUserCont), newMotDePasse, 280, 140);


              annulerAjout = gtk_button_new_with_label("Annuler");
              gtk_fixed_put(GTK_FIXED(addUserCont), annulerAjout, 750, 550);
              gtk_widget_set_size_request(annulerAjout, 180, 60);
              g_signal_connect(G_OBJECT(annulerAjout), "clicked", G_CALLBACK(  goAdmin1 ), NULL);

              ajouter = gtk_button_new_with_label("Ajouter");
              gtk_fixed_put(GTK_FIXED(addUserCont), ajouter, 450, 550);
              gtk_widget_set_size_request(ajouter, 180, 60);
              g_signal_connect(G_OBJECT(ajouter), "clicked", G_CALLBACK(  ajouterUtilisateur ), NULL);
              /*-------------------------------------------------------------------------------------------------------------------------
                 * ----------------------------------------------------------------------------------------------------------------
                 * ------------------------------------------------------------------------------------------------
                 */  //DEL user
                 delUserCont=gtk_fixed_new();
                 delUserMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                 gtk_window_set_title(GTK_WINDOW(delUserMenu), "Suppression d'utilisateur");
                 gtk_window_set_default_size(GTK_WINDOW(delUserMenu), 1024, 720);
                 gtk_window_set_position(GTK_WINDOW(delUserMenu), GTK_WIN_POS_CENTER);
                 gtk_container_add(GTK_CONTAINER(delUserMenu), delUserCont);
                 g_signal_connect(G_OBJECT(delUserMenu), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

                     annulerSupUsr = gtk_button_new_with_label("Annuler");
                     gtk_fixed_put(GTK_FIXED(delUserCont), annulerSupUsr, 750, 550);
                     gtk_widget_set_size_request(annulerSupUsr, 180, 60);
                     g_signal_connect(G_OBJECT(annulerSupUsr), "clicked", G_CALLBACK(  goAdmin2 ), NULL);


                     supprimerUsr = gtk_button_new_with_label("Supprimer");
                     gtk_fixed_put(GTK_FIXED(delUserCont), supprimerUsr, 450, 550);
                     gtk_widget_set_size_request(supprimerUsr, 180, 60);
                     g_signal_connect(G_OBJECT(supprimerUsr), "clicked", G_CALLBACK(  supprimerUtilisateur ), NULL);

                     delUtilisateurTXT = gtk_label_new("Nom d'utilisateur a supprimer : ");
                     gtk_fixed_put(GTK_FIXED(delUserCont), delUtilisateurTXT, 100, 100);
                     gtk_widget_set_size_request(delUtilisateurTXT, 80, 30);
                     utilisateurASup=gtk_entry_new();
                     gtk_fixed_put(GTK_FIXED(delUserCont), utilisateurASup, 280, 100);


                     /*-------------------------------------------------------------------------------------------------------------------------
                        * ----------------------------------------------------------------------------------------------------------------
                        * ------------------------------------------------------------------------------------------------
                        */  //DEL kit

                        delKitCont=gtk_fixed_new();
                        delKitMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                        gtk_window_set_title(GTK_WINDOW(delKitMenu), "Suppression de Kit");
                        gtk_window_set_default_size(GTK_WINDOW(delKitMenu), 1024, 720);
                        gtk_window_set_position(GTK_WINDOW(delKitMenu), GTK_WIN_POS_CENTER);
                        gtk_container_add(GTK_CONTAINER(delKitMenu), delKitCont);
                        g_signal_connect(G_OBJECT(delKitMenu), "destroy",
                            G_CALLBACK(gtk_main_quit), NULL);

                            annulerSupKit = gtk_button_new_with_label("Annuler");
                            gtk_fixed_put(GTK_FIXED(delKitCont), annulerSupKit, 750, 550);
                            gtk_widget_set_size_request(annulerSupKit, 180, 60);
                            g_signal_connect(G_OBJECT(annulerSupKit), "clicked", G_CALLBACK(  goAdmin3 ), NULL);


                            supprimerKitbtn = gtk_button_new_with_label("Supprimer");
                            gtk_fixed_put(GTK_FIXED(delKitCont), supprimerKitbtn, 450, 550);
                            gtk_widget_set_size_request(supprimerKitbtn, 180, 60);
                            g_signal_connect(G_OBJECT(supprimerKitbtn), "clicked", G_CALLBACK(  supprimerKit ), NULL);

                            delKitTXT = gtk_label_new("Kit a supprimer : ");
                            gtk_fixed_put(GTK_FIXED(delKitCont), delKitTXT, 100, 100);
                            gtk_widget_set_size_request(delKitTXT, 80, 30);
                            kitASup=gtk_entry_new();
                            gtk_fixed_put(GTK_FIXED(delKitCont), kitASup, 280, 100);








                        /*-------------------------------------------------------------------------------------------------------------------------
                           * ----------------------------------------------------------------------------------------------------------------
                           * ------------------------------------------------------------------------------------------------
                           */  //DEL FQI
                           delFQICont=gtk_fixed_new();
                          delFQIMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                          gtk_window_set_title(GTK_WINDOW(delFQIMenu), "Suppression de FQI");
                          gtk_window_set_default_size(GTK_WINDOW(delFQIMenu), 1024, 720);
                          gtk_window_set_position(GTK_WINDOW(delFQIMenu), GTK_WIN_POS_CENTER);
                          gtk_container_add(GTK_CONTAINER(delFQIMenu), delFQICont);
                          g_signal_connect(G_OBJECT(delFQIMenu), "destroy",
                              G_CALLBACK(gtk_main_quit), NULL);


                              annulerSupFQI = gtk_button_new_with_label("Annuler");
                              gtk_fixed_put(GTK_FIXED(delFQICont), annulerSupFQI, 750, 550);
                              gtk_widget_set_size_request(annulerSupFQI, 180, 60);
                              g_signal_connect(G_OBJECT(annulerSupFQI), "clicked", G_CALLBACK(  goAdmin4 ), NULL);


                              supprimerFQIbtn = gtk_button_new_with_label("Supprimer");
                              gtk_fixed_put(GTK_FIXED(delFQICont), supprimerFQIbtn, 450, 550);
                              gtk_widget_set_size_request(supprimerFQIbtn, 180, 60);
                              g_signal_connect(G_OBJECT(supprimerFQIbtn), "clicked", G_CALLBACK(  supprimerFQI ), NULL);

                              delFQITXT = gtk_label_new("FQI a supprimer : ");
                              gtk_fixed_put(GTK_FIXED(delFQICont), delFQITXT, 100, 100);
                              gtk_widget_set_size_request(delFQITXT, 80, 30);
                              FQIASup=gtk_entry_new();
                              gtk_fixed_put(GTK_FIXED(delFQICont), FQIASup, 280, 100);
                              /*-------------------------------------------------------------------------------------------------------------------------
                                 * ----------------------------------------------------------------------------------------------------------------
                                 * ------------------------------------------------------------------------------------------------
                                 */  //find kitI


                                 findKitCont=gtk_fixed_new();
                                findKitMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                                gtk_window_set_title(GTK_WINDOW(findKitMenu), "Recherche Kit");
                                gtk_window_set_default_size(GTK_WINDOW(findKitMenu), 1024, 720);
                                gtk_window_set_position(GTK_WINDOW(findKitMenu), GTK_WIN_POS_CENTER);
                                gtk_container_add(GTK_CONTAINER(findKitMenu), findKitCont);
                                g_signal_connect(G_OBJECT(findKitMenu), "destroy",
                                    G_CALLBACK(gtk_main_quit), NULL);

                                    annulerTrouverKit = gtk_button_new_with_label("Annuler");
                                    gtk_fixed_put(GTK_FIXED(findKitCont), annulerTrouverKit, 750, 550);
                                    gtk_widget_set_size_request(annulerTrouverKit, 180, 60);
                                    g_signal_connect(G_OBJECT(annulerTrouverKit), "clicked", G_CALLBACK(  goAdmin5 ), NULL);


                                    trouverKitbtn = gtk_button_new_with_label("Trouver");
                                    gtk_fixed_put(GTK_FIXED(findKitCont), trouverKitbtn, 450, 550);
                                    gtk_widget_set_size_request(trouverKitbtn, 180, 60);
                                    g_signal_connect(G_OBJECT(trouverKitbtn), "clicked", G_CALLBACK(  trouverKit ), NULL);

                                    findKitTXT = gtk_label_new("Kit a trouver : ");
                                    gtk_fixed_put(GTK_FIXED(findKitCont), findKitTXT, 100, 100);
                                    gtk_widget_set_size_request(findKitTXT, 80, 30);
                                    kitATrou=gtk_entry_new();
                                    gtk_fixed_put(GTK_FIXED(findKitCont), kitATrou, 280, 100);

                                    /*-------------------------------------------------------------------------------------------------------------------------
                                       * ----------------------------------------------------------------------------------------------------------------
                                       * ------------------------------------------------------------------------------------------------
                                       */  //find FQI
                                       findFQICont=gtk_fixed_new();
                                       findFQIMenu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                                       gtk_window_set_title(GTK_WINDOW(findFQIMenu), "Recherche FQI");
                                       gtk_window_set_default_size(GTK_WINDOW(findFQIMenu), 1024, 720);
                                       gtk_window_set_position(GTK_WINDOW(findFQIMenu), GTK_WIN_POS_CENTER);
                                       gtk_container_add(GTK_CONTAINER(findFQIMenu), findFQICont);
                                       g_signal_connect(G_OBJECT(findFQIMenu), "destroy",
                                          G_CALLBACK(gtk_main_quit), NULL);

                                          annulerTrouverFQI = gtk_button_new_with_label("Annuler");
                                          gtk_fixed_put(GTK_FIXED(findFQICont), annulerTrouverFQI, 750, 550);
                                          gtk_widget_set_size_request(annulerTrouverFQI, 180, 60);
                                          g_signal_connect(G_OBJECT(annulerTrouverFQI), "clicked", G_CALLBACK(  goAdmin6 ), NULL);


                                          trouverFQIbtn = gtk_button_new_with_label("Trouver");
                                          gtk_fixed_put(GTK_FIXED(findFQICont), trouverFQIbtn, 450, 550);
                                          gtk_widget_set_size_request(trouverFQIbtn, 180, 60);
                                          g_signal_connect(G_OBJECT(trouverFQIbtn), "clicked", G_CALLBACK(  trouverFQI ), NULL);

                                          findFQITXT = gtk_label_new("FQI a trouver : ");
                                          gtk_fixed_put(GTK_FIXED(findFQICont), findFQITXT, 100, 100);
                                          gtk_widget_set_size_request(findFQITXT, 80, 30);
                                          FQIATrou=gtk_entry_new();
                                          gtk_fixed_put(GTK_FIXED(findFQICont), FQIATrou, 280, 100);

                                          /*-------------------------------------------------------------------------------------------------------------------------
                                             * ----------------------------------------------------------------------------------------------------------------
                                             * ------------------------------------------------------------------------------------------------
                                             */  //find kitusr

                                             findKitContUsr=gtk_fixed_new();
                                            findKitMenuUsr = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                                            gtk_window_set_title(GTK_WINDOW(findKitMenuUsr), "Recherche Kit");
                                            gtk_window_set_default_size(GTK_WINDOW(findKitMenuUsr), 1024, 720);
                                            gtk_window_set_position(GTK_WINDOW(findKitMenuUsr), GTK_WIN_POS_CENTER);
                                            gtk_container_add(GTK_CONTAINER(findKitMenuUsr), findKitContUsr);
                                            g_signal_connect(G_OBJECT(findKitMenuUsr), "destroy",
                                                G_CALLBACK(gtk_main_quit), NULL);

                                                annulerTrouverKitUsr = gtk_button_new_with_label("Annuler");
                                                gtk_fixed_put(GTK_FIXED(findKitContUsr), annulerTrouverKitUsr, 750, 550);
                                                gtk_widget_set_size_request(annulerTrouverKitUsr, 180, 60);
                                                g_signal_connect(G_OBJECT(annulerTrouverKitUsr), "clicked", G_CALLBACK(  goAdmin7 ), NULL);


                                                trouverKitbtnUsr = gtk_button_new_with_label("Trouver");
                                                gtk_fixed_put(GTK_FIXED(findKitContUsr), trouverKitbtnUsr, 450, 550);
                                                gtk_widget_set_size_request(trouverKitbtnUsr, 180, 60);
                                                g_signal_connect(G_OBJECT(trouverKitbtnUsr), "clicked", G_CALLBACK(  trouverKitUsr ), NULL);

                                                findKitTXTUsr = gtk_label_new("Kit a trouver : ");
                                                gtk_fixed_put(GTK_FIXED(findKitContUsr), findKitTXTUsr, 100, 100);
                                                gtk_widget_set_size_request(findKitTXTUsr, 80, 30);
                                                kitATrouUsr=gtk_entry_new();
                                                gtk_fixed_put(GTK_FIXED(findKitContUsr), kitATrouUsr, 280, 100);












                                          /*-------------------------------------------------------------------------------------------------------------------------
                                             * ----------------------------------------------------------------------------------------------------------------
                                             * ------------------------------------------------------------------------------------------------
                                             */  //find FQIusr


                                             findFQIContUsr=gtk_fixed_new();
                                            findFQIMenuUsr = gtk_window_new(GTK_WINDOW_TOPLEVEL);
                                            gtk_window_set_title(GTK_WINDOW(findFQIMenuUsr), "Recherche FQI");
                                            gtk_window_set_default_size(GTK_WINDOW(findFQIMenuUsr), 1024, 720);
                                            gtk_window_set_position(GTK_WINDOW(findFQIMenuUsr), GTK_WIN_POS_CENTER);
                                            gtk_container_add(GTK_CONTAINER(findFQIMenuUsr), findFQIContUsr);
                                            g_signal_connect(G_OBJECT(findFQIMenuUsr), "destroy",
                                                G_CALLBACK(gtk_main_quit), NULL);

                                                annulerTrouverFQIUsr = gtk_button_new_with_label("Annuler");
                                                gtk_fixed_put(GTK_FIXED(findFQIContUsr), annulerTrouverFQIUsr, 750, 550);
                                                gtk_widget_set_size_request(annulerTrouverFQIUsr, 180, 60);
                                                g_signal_connect(G_OBJECT(annulerTrouverFQIUsr), "clicked", G_CALLBACK(  goAdmin8 ), NULL);


                                                trouverFQIbtnUsr = gtk_button_new_with_label("Trouver");
                                                gtk_fixed_put(GTK_FIXED(findFQIContUsr), trouverFQIbtnUsr, 450, 550);
                                                gtk_widget_set_size_request(trouverFQIbtnUsr, 180, 60);
                                                g_signal_connect(G_OBJECT(trouverFQIbtnUsr), "clicked", G_CALLBACK(  trouverFQIUsr ), NULL);

                                                findFQITXTUsr = gtk_label_new("FQI a trouver : ");
                                                gtk_fixed_put(GTK_FIXED(findFQIContUsr), findFQITXTUsr, 100, 100);
                                                gtk_widget_set_size_request(findFQITXTUsr, 80, 30);
                                                FQIATrouUsr=gtk_entry_new();
                                                gtk_fixed_put(GTK_FIXED(findFQIContUsr), FQIATrouUsr, 280, 100);























                          gtk_main();
                          //gtk_main_quit();
                          system("TASKKILL /T /IM check.exe /F");
                          system("TASKKILL /T /IM check_FQI.exe /F");
                          system("TASKKILL /T /IM ajout.exe /F");
                          system("TASKKILL /T /IM ajout_fqi.exe /F");
                            ///system("taskkill /F /T /IM check_.exe");

                          int z=0;
                          printf("Appuyer sur n'importe quel button puis sur entree pour fermer cette fenetre...\n");
                          scanf("%i",z);

                          system("PAUSE");


  return 0;
}
