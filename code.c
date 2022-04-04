#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int * afficher_bit(int octet)
{
  int copie = octet ;
  int * bit = malloc(8*sizeof(int));
  for(int j = 0 ; j < 8 ; j++)
  {
    bit[j] = copie & 1;
    copie = copie >> 1 ;
    printf("%d ",bit[j]);
  }
  printf("\n");
  return bit ;
}

int bruite(int octet, float p , int i)
{
    int * bit = malloc(8*sizeof(int));
    bit = afficher_bit(octet);
    long int seuil = p * RAND_MAX ;
    if(random() < seuil)
    {
      for(int j = 0; j < i ; j++ )
      {
        int n = rand()%8; // nombre entre 0 et 9
        if(bit[n] == 1)
          bit[n] = 0;
        else
          bit[n] = 1;
      }
    }
    int nv = bit[0] ;
    int cpt = 2 ;
    for(int t =  1 ; t < 8 ; t++)
    {
      nv = nv + bit[t]*cpt ;
      cpt = cpt * 2 ;
    }
    return nv ;
}

void copie(const char* input_file, const char* output_file)
{
  FILE* fichier = NULL;
  fichier = fopen(input_file, "r");
  FILE* fich = NULL;
  fich = fopen(output_file, "w");
  int caractereActuel = 0;
  int nv = 0 ;

    if (fichier != NULL)
    {
        // Boucle de lecture des caractères un à un
        do
        {
          caractereActuel = fgetc(fichier); // On lit le caractère
          printf("%c", caractereActuel); // On l'affiche
          nv = bruite(caractereActuel,0.9,2);
          //printf("%d\n",nv);
          fputc(nv, fich); // Écriture du caractère A

        } while (caractereActuel != EOF); // On continue tant que fgetc n'a pas retourné EOF (fin de fichier)
        fclose(fichier);
        fclose(fich);
    }
}
int poids(int*x)
{
// calcul le poids d un vecteur
    int cpt = 0 ;
    for(int i = 0 ; i < 8 ; i++)
    	if (x[i] == 1)
    		cpt ++ ;
    return cpt ;
}

int* diff(int * u, int * v)
{
    int* dif = calloc(8,sizeof(int));
    for(int i = 0 ; i < 8 ; i++)
    {
    	if( u[i] != v[i])
    		dif[i] = 1 ;
    }
    return dif ;
}

int hamming(int * u , int * v)
{
//calcule la distance (difference) entre deux vecteurs
   int * dif = calloc(8, sizeof(int));
   dif = diff(u, v);
   return poids(dif);
}

int dist_minimale(int ** tab, int n)
{
   // calcule la distance minimale d un ensemble de vecteur
    int dist = 1 ;
    for(int i = 0 ; i < n ; i++)
    {
    	for(int j = 0 ; j < n ; j++)
    	{
    	        int tmp = hamming(tab[i],tab[j]) ;
    		if ( tmp < dist && tmp != 0)
    		   dist =  tmp ;
    	}
   }
   return dist ;

}

int** mots(int k)
{
// renvoie l ensemble des mots de dimension k
  int n = pow(2,k);
  int ** tab = calloc(n,sizeof(int*));
  for(int i = 0 ; i < n ; i++)
  	tab[i] = calloc(k,sizeof(int));
  int* afficher_bit(int octet);
  for(int k = 0 ; k < n ; k++)
  	tab[k] = afficher_bit(k);
  return tab ;
}
int* vecteur(int val)
{
  int copie = val ;
  int * bit = malloc(8*sizeof(int));
  for(int j = 7 ; j >= 0 ; j--)
  {
    bit[j] = copie & 1;
    copie = copie >> 1 ;
  }
  for(int j = 0 ; j < 8 ; j++)
  {
  printf("%d ",bit[j]);
  }


  return bit ;
}

int valeurr(int* vect, int n)
{
  int nv = vect[n-1] ;
  printf(" %d\n",nv);

  int cpt = 1 ;
  for(int t =  n-2 ; t >= 0 ; t--)
  {
    nv = nv + (vect[t] << cpt) ;
    cpt = cpt + 1  ;
  }
  printf(" %d\n",nv);
  return nv ;
}

int* encode(int ** g, int* v, int k , int n )
{
  int * l = malloc(k * sizeof(int));

  for(int j = 0 ; j < k ; j++)
  {
      int s = 0;
      for(int z = 0 ; z < n ; z++)
	{	s = s ^ (g[z][j] & v[z]);
		printf("%d %d ",g[z][j], v[z]);}
      printf("\n %d \n",s);
      l[j] = s;
    }
    return l;
}


// int* encode_int(int*g, int v, int k , int n )
// {
//   int * l = malloc(k * sizeof(int));
//   int * vect = vecteur(v, k-n);
//   int ** gen = (int**) malloc(k*sizeof(int*));
//   for(unsigned int i = 0; i < k; i++){
//       gen[i] = (int*)calloc(n, sizeof(int));
//       gen[i] = vecteur(g[i]);
//   }
//
//   for(int j = 0 ; j < k ; j++)
//   {
//       int s = 0;
//       for(int z = 0 ; z < n ; z++)
//       {
//         	s = s ^ (gen[z][j] & vect[z]);
// 		      printf("%d %d ",gen[z][j], vect[z]);}
//           printf("\n %d \n",s);
//           l[j] = s;
//     }
//     return l;
// }
int* controle(int ** h, int* c, int k , int n)
{
  int * l = malloc(n*sizeof(int));
  for(int i = 0 ; i < n ; i++)
  {
      int s = 0;
      for(int j = 0 ; j < k ; j++)
	 s = s + (h[i][j]*c[j]);
      printf("%d\n",s);
      l[i] = s;
    }
	return l;
}
int main(int argc, char*argv[])
{

  srand(time(NULL));
  /* //controle
  int ** tab = calloc(3,sizeof(int*));
  for(int i = 0 ; i < 3 ; i++)
  	tab[i] = calloc(4,sizeof(int));

  tab[0][0] = 0 ;
  tab[0][1] = 3 ;
  tab[0][2] = 6 ;
  tab[0][3] = 9 ;
  tab[1][0] = 1 ;
  tab[1][1] = 4 ;
  tab[1][2] = 7 ;
  tab[1][3] = 10 ;
  tab[2][0] = 2 ;
  tab[2][1] = 5 ;
  tab[2][2] = 8 ;
  tab[2][3] = 11 ;

  int *t = calloc(4,sizeof(int));
  t[0] = 0;
  t[1] = 1;
  t[2] = 2;
  t[3] = 3;
  controle(tab,t,4,3);
  */
  //encode
  int ** tab = calloc(3,sizeof(int*));
  for(int i = 0 ; i < 3 ; i++)
  	tab[i] = calloc(4,sizeof(int));

  tab[0][0] = 0 ;
  tab[0][1] = 3 ;
  tab[0][2] = 6 ;
  tab[0][3] = 9 ;

  tab[1][0] = 1 ;
  tab[1][1] = 4 ;
  tab[1][2] = 7 ;
  tab[1][3] = 10 ;

  tab[2][0] = 2 ;
  tab[2][1] = 5 ;
  tab[2][2] = 8 ;
  tab[2][3] = 11 ;

  int *t = calloc(4,sizeof(int));
  t[0] = 0;
  t[1] = 1;
  t[2] = 1;
  t[3] = 1;

  valeurr(t, 4);

}
