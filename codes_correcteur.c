#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* conversion(int octet)
{
  int copie = octet ;
  int * bit = malloc(8*sizeof(int));
  for(int j = 0 ; j < 8 ; j++)
  {
    bit[j] = copie % 2;
    copie = copie / 2 ;
  }
  return bit ;
}

int* conversion2(int octet)
{
  int copie = octet ;
  int * bit = malloc(8*sizeof(int));
  for(int j = 0 ; j < 8 ; j++)
  {
    bit[j] = copie & 1;
    printf("%d ",bit[j]);
    copie = copie >> 1 ;
  }
  return bit ;
}

int bruite(int octet, float p , int i)
{
    int * bit = malloc(8*sizeof(int));
    bit = conversion(octet);
    //for(int t =  0 ; t < 8 ; t++)
      //printf("%d",bit[t]);
    //printf("\n");
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
    //printf("%d",bit[0]);
    int cpt = 2 ;
    for(int t =  1 ; t < 8 ; t++)
    {
      //printf("%d",bit[t]);
      nv = nv + bit[t]*cpt ;
      cpt = cpt * 2 ;
    }
    //printf("\n%d %d\n",octet,nv);
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
unsigned int hamming(int v1, int v2)
{
  int cpt = 0 ;
  int * bit1 = malloc(8*sizeof(int));
  bit1 = conversion(v1);

  int * bit2 = malloc(8*sizeof(int));
  bit2 = conversion(v2);

  for(int i = 0 ; i < 8 ; i++)
  {
    printf("%d %d\n",bit1[i],bit2[i]);
    if(bit1[i] != bit2[i])
      cpt++;
  }
  return cpt ;
}
int weight(int x)
{
	int res = 0 ;
	while(x > 0)
	{
		x&=(x-1);
		res++;
	}
	return res ;
}
unsigned int hamming2(int v1, int v2)
{
  int xo = v1 ^ v2;
  int t = weight(xo);
  printf("%d\n",t);
  return weight(xo);

}
int main(int argc, char*argv[])
{
  srand(time(NULL));
  //bruite(45,0.9,2);
  // copie(argv[1],argv[2]);
  // int x = hamming(10,4);
  // printf("%d\n",x);
  //conversion2(5);
  hamming2(1,2);

}
