#include <stdio.h>
#include <stdlib.h>


//affiche 2 exposant n
int pow2(unsigned int n){
    if (n == 0) return 1;

    return 2*pow2(n-1);
}


//retourne un vecteur nul de taille n
int* vecteur_vide(unsigned int n) {

    if (n <= 0) return NULL;

    return (int*)calloc(n, sizeof(int));
}


//affiche un vecteur de taille n affiché dans l'ordre decroissant vn,....,v1
void affiche_vecteur(int* v, unsigned int n) {

    printf("(");
    if ((v != NULL) && (n > 0)){
        printf("%d", v[n-1]);
        for(int i = 1; i < n; i++){
            printf(", %d", v[n-i-1]);
        }
    }
    printf(")");
}

//renvoie la representation binaire de l entier valeur
//sur n entiers

int* vecteur(unsigned int n, unsigned int valeur) {
    if (valeur >= pow2(n)){
        return NULL;
    }

    int* v = (int*)malloc(n*sizeof(int));

    for(int i=0; valeur > 0; i++){
        v[i] = valeur%2;
        valeur = valeur/2;
    }

    return v;
}

int valeurr(int* vect, int n)
{
  int nv = vect[n-1] ;
  int cpt = 1 ;
  for(int t =  n-2 ; t >= 0 ; t--)
  {
    nv = nv + (vect[t] << cpt) ;
    cpt = cpt + 1  ;
  }
  printf(" \n%d\n",nv);
  return nv ;
}
//retourne la valeur de la reprensentation binaire du vecteur v
//codé sur n entiers
int valeur(int* v, unsigned int n) {

    if ((v == NULL) || (n <= 0)) return -1;

    int val = 0;

    for(int i = n-1; i >= 0; i--){
        val = 2*val + v[i];
    }

    return val;
}

//genere 2exposant k vecteurs binaires de taille k

int** mots(unsigned int k) {
    if (k <= 0) return NULL;

    int** m = (int**)malloc(pow2(k)*sizeof(int*));

    for(unsigned int i = 0; i <= pow2(k) - 1; i++){
        m[i] = vecteur(k, i);
    }

    return m;
}

//calcule le poids d un vecteur de taille n

unsigned int poids(int* v, int n){
    if ((v == NULL) || (n <= 0)) return 0;

    unsigned int p = 0;
    for(unsigned int i = 0; i < n; i++){
        p = p + v[i];
    }

    return p;
}

//retourne le vecteur binaire difference entre deux vecteurs u et v de taille n

int* diff(int* u, int* v, int n){
    if ((u == NULL) || (v == NULL) || (n <= 0)) return NULL;

    int* d = (int*)malloc(n*sizeof(int));

    for(unsigned int i = 0; i < n; i++){
        d[i] = (u[i] == v[i]?0:1);
    }

    return d;
}

//retourne la distance de hamming entre deux vecteurs
//c est a dire le nombre de bit different entre deux vecteurs
unsigned int hamming(int* u, int* v, int n){
    if ((u == NULL) || (v == NULL) || (n <= 0)) return 0;

    return poids(diff(u, v, n), n);
}

void affiche_matrice(int** mat, unsigned int l, unsigned int c){

    if ((mat == NULL) || (l <= 0) || (c <= 0)) {
        printf("[ ]");
    } else {

        for(unsigned int i = 0; i < l; i++){
            printf("[");
            for(unsigned int j = 0; j < c; j++){
                printf(" %d", mat[i][j]);
            }

            printf(" ]\n");
        }
    }

}

//retourne c = v*G avec G la matrice generatrice et v le vecteur binaire

int* encode(int** g, int* v, unsigned int k, unsigned int n) {

    if ((g == NULL) || (v == NULL) || (k <= 0) || (n <= 0)) return NULL;

    int* c = (int*) malloc(n*sizeof(int));

    for(unsigned int j = 0; j < n; j++){
        c[j] = 0;
        for(unsigned int i = 0; i < k; i++){
            c[j] = (c[j] + v[k-i-1]*g[i][n-j-1])%2;
        }
    }

    return c;
}

int* vecteurr(int val, int k)
{
  int copie = val ;
  int * bit = malloc(k*sizeof(int));
  for(int j = k-1 ; j >= 0 ; j--)
  {
    bit[j] = copie & 1;
    copie = copie >> 1 ;
  }
  for(int j = 0 ; j < 4 ; j++)
  {
  printf("%d ",bit[j]);
  }
  printf("\n\n");
  return bit ;
}

int encode_int(int*g, int v, int k , int n )
{
  //pour ne pas faire vect = vecteurr(v) et v[i] a chaque fois on fait v >> i & 1
  //pareil au lieu de faire gen[j][z] il faut juste faire gen[j]>>z & 1
  int * l = malloc(k * sizeof(int));
  int * vect = vecteurr(v, n);
  int ** gen = (int**) malloc(k*sizeof(int*));
  for(unsigned int i = 0; i < 7; i++){
      gen[i] = (int*)calloc(4, sizeof(int));
  }
  for(unsigned int i = 0; i < 7; i++){
      gen[i] = vecteurr(g[i],4);
  }
  for(int j = 0 ; j < k ; j++)
  {
      int s = 0;
      for(int z = 0 ; z < n ; z++)
      {
        	s = s ^ (gen[j][z] & vect[z]);
      }
      l[j] = s;
      printf("\n %d \n",s);
    }
    return valeurr(l, 7);
}

int syndrome_int(int * h, int c, unsigned int k, unsigned int n) {
    if ((h == NULL) || (c == 0) || (k <= 0) || (n <= 0)) return NULL;

    int * C = vecteurr(c, k);

    int * l = malloc(k * sizeof(int));

    int ** H = (int**) malloc(k*sizeof(int*));
    for(unsigned int i = 0; i < k; i++){
        H[i] = (int*)calloc(n-1, sizeof(int));
    }
    for(unsigned int i = 0; i < k; i++){
        H[i] = vecteurr(h[i], n-1);
    }
    for(int i = 0; i < n-1; i++){
      int s = 0;
        for(unsigned int j = 0; j < k; j++)
        {
            s = s ^ (H[j][i] & C[j]) ;
        }
        l[i] = s ;
        printf("%d ",s);

    }
    printf("\n");
        return valeurr(l, k-n-1);
}

unsigned int dist_min(int** vecteurs, unsigned int n){
    if ((vecteurs == NULL) || (n <= 0)) return 0;

    unsigned int dmin = n;
    unsigned int d;
    for(unsigned int i = 0; i < n; i++){
        for(unsigned int j = i+1; j < n; j++){
            d = hamming(vecteurs[i], vecteurs[j], n);

            if (d < dmin){
                dmin = d;
            }
        }
    }

    return d;
}

//la matrice de controle offre des criteres sur la distance minimale du code

// a la reception d un mot x la matrice de controle permet de determinier si
//une alteration a ete commise.
//si tel est le cas la matrice de controle fournit une quantité appelé syndrome
// le message corrigé est egale a x-e

int* syndrome(int** h, int* c, unsigned int k, unsigned int n) {
    if ((h == NULL) || (c == NULL) || (k <= 0) || (n <= 0)) return NULL;

    int* s = vecteur_vide(n-k);
    for(int i = 0; i < n-k; i++){
        for(unsigned int j = 0; j < n; j++){
            s[n-k-i-1] = (s[n-k-i-1] + h[i][j]*c[j])%2;
        }
    }

    return s;
}



int* bruite(int* v, unsigned int n, unsigned int b){
    if ((v == NULL) || (n <=0) || (b < 0) || (b > n-1)) return NULL;

    // Copie du vecteur v dans le vecteur vb
    int* vb = (int*) malloc(n*sizeof(int));
    for(unsigned int i = 0; i < n; i++){
        vb[i] = v[i];
    }

    // Bruitage du bit b
    vb[b] = (v[b] == 1)?0:1;

    return vb;
}


//si le syndrome est nul alors ce mot appartient au code


//retourne n l’indice de la colonne de la matrice h égale au
//syndrome s de taille n-k passé en paramètre.
int indice_colonne(int* s, int** h, unsigned int k, unsigned int n){
    int indice = -1;

    if ((s == NULL) || (h == NULL) || (k <=0) || (n <= 0) || (n<k)) return indice;

    int egal;
    for(int j = 0; j < n; j++){
        egal = 1;
        for(int i = 0; i < n-k; i++){
            egal = egal && (s[n-k-i-1] == h[i][j]);
        }

        if (egal == 1){
            return j;
        }
    }

    return -1;
}


//corrige le vecteur v

int* corrige(int* v, int** h, unsigned int k, unsigned int n){
    if ((v == NULL) || (h == NULL) || (k <=0) || (n <= 0) || (n<k)) return NULL;

    // Copie du vecteur d'entre
    int* vb = (int*) malloc(n*sizeof(int));
    for(unsigned int i = 0; i < n; i++){
        vb[i] = v[i];
    }

    // Calcul du syndrome de v par h
    int* s = syndrome(h, v, k, n);

    // En cas d'erreur
    if (s == NULL) return NULL;

    // Le syndrome est de poids non nul (different de 0), le mot est donc
    // recu avec une erreur
    if (poids(s, n-k) != 0){
        int col = indice_colonne(s, h, k, n);

        if ((col >= 0) && (col < n)){
            vb[col] = (vb[col] == 1)?0:1;
        }
    }

    return vb;
}


int corrige_int(int v, int * h, unsigned int k, unsigned int n){
    if ((h == NULL) || (k <=0) || (n <= 0) || (n>k)) return NULL;

    // Calcul du syndrome de v par h
    int s = syndrome_int(h, v, n, k);
    int col = 0 ;

    // Le syndrome est de poids non nul (different de 0), le mot est donc
    // recu avec une erreur
    int res = 0 ;
    if (s != 0){
        for(int j = 0 ; j < k ; j++)
          if (s == h[j])
            col = j ;



        if ((col >= 0) && (col < n))
        {
            int x = v << col ;
            int res = v ^ x ;
      }
    }
    return res;
}

//cette fonction decode ne marche que pour l exemple du TD
//elle consiste a recuperer les ligness qui contiennent la matrice identite
//on a modifie la matrice G de tel facon on a plus la matrice generatrice avec la
//matrice identite d un seul coté bien ensemble mais on peut l avoir eparpié
//l avantage d avoir cette matrice est qu'apres on a la matrice H qui contient
//exactement dans l'ordre 1 2 3 .... codé en binaire pour apres
//dans la recherche de l'indice de la colonne identique au syndrome on ne
//s'embete pas a chercher l indice mais on fait juste une comparaison

int decode(int v ){

    int a = (v >> 2 ) &1 ;
    int b = (v >> 4 ) &1 ;
    int c = (v >> 5 ) &1 ;
    int d = (v >> 6 ) &1 ;

    int res = a + (b <<2) + (c << 3) + (d << 4) ;
    printf("\n\n\n\%d\n\n%d %d %d %d \n\n\n",res,a,b,c,d);
}

int main()
{
    unsigned int k = 4;

    unsigned int n = 7;
    int v = 85 ;
    int x = 1 << 2 ;
    printf("%d %d \n",v ^ x, x);
  //
  //   // Creation de la matrice G
  //   int** g = (int**) malloc(k*sizeof(int*));
  //   for(unsigned int i = 0; i < k; i++){
  //       g[i] = (int*)calloc(n, sizeof(int));
  //   }
  //   g[0][0] = 1; g[0][1] = 1; g[0][2] = 1; g[0][3] = 0; g[0][4] = 0; g[0][5] = 0; g[0][6] = 0;
  //   g[1][0] = 1; g[1][1] = 0; g[1][2] = 0; g[1][3] = 1; g[1][4] = 1; g[1][5] = 0; g[1][6] = 0;
  //   g[2][0] = 0; g[2][1] = 1; g[2][2] = 0; g[2][3] = 1; g[2][4] = 0; g[2][5] = 1; g[2][6] = 0;
  //   g[3][0] = 1; g[3][1] = 0; g[3][2] = 0; g[3][3] = 1; g[3][4] = 0; g[3][5] = 0; g[3][6] = 1;
  //
  //   // Creation de la matrice H
  //   int** h = (int**) malloc((n-k)*sizeof(int*));
  //   for(unsigned int i = 0; i < k; i++){
  //       h[i] = (int*)calloc(n, sizeof(int));
  //   }
  //   h[0][0] = 0; h[0][1] = 0; h[0][2] = 0; h[0][3] = 1; h[0][4] = 1; h[0][5] = 1; h[0][6] = 1;
  //   h[1][0] = 0; h[1][1] = 1; h[1][2] = 1; h[1][3] = 0; h[1][4] = 0; h[1][5] = 1; h[1][6] = 1;
  //   h[2][0] = 1; h[2][1] = 0; h[2][2] = 1; h[2][3] = 0; h[2][4] = 1; h[2][5] = 0; h[2][6] = 1;
  //
  //   int s1[3] = {h[0][0], h[1][0], h[2][0]};
  //   int s2[3] = {h[0][1], h[1][1], h[2][1]};
  //   int s3[3] = {h[0][2], h[1][2], h[2][2]};
  //   int s4[3] = {h[0][3], h[1][3], h[2][3]};
  //   int s5[3] = {h[0][4], h[1][4], h[2][4]};
  //   int s6[3] = {h[0][5], h[1][5], h[2][5]};
  //   int s7[3] = {h[0][6], h[1][6], h[2][6]};
  //
  //   int* v_vide = vecteur_vide(n);
  //
  //   int* v_min      = vecteur(n, 0);
  //   int* v_max      = vecteur(n, pow2(n) - 1);
  //   int* v_mid      = vecteur(n, (pow2(n)-1) / 2);
  //   int* v_overflox = vecteur(n, pow2(n));
  //
  //   printf("Test affichage / creation de vecteurs:\n");
  //
  //   printf("  - Vecteur vide    : ");
  //   affiche_vecteur(v_vide, n);
  //   printf(", valeur: %d", valeur(v_vide, n));
  //   printf("\n");
  //
  //   printf("  - Vecteur min     : ");
  //   affiche_vecteur(v_min, n);
  //   printf(", valeur: %d", valeur(v_min, n));
  //   printf("\n");
  //
  //   printf("  - Vecteur max     : ");
  //   affiche_vecteur(v_max, n);
  //   printf(", valeur: %d", valeur(v_max, n));
  //   printf("\n");
  //
  //   printf("  - Vecteur mid     : ");
  //   affiche_vecteur(v_mid, n);
  //   printf(", valeur: %d", valeur(v_mid, n));
  //   printf("\n");
  //
  //   printf("  - Vecteur overflow: ");
  //   affiche_vecteur(v_overflox, n);
  //   printf(", valeur: %d", valeur(v_overflox, n));
  //   printf("\n");
  //
  //   int** mots_k = mots(k);
  //   printf("\nMots de %d bits\n", k);
  //   for(unsigned int i = 0; i <= pow2(k)-1; i++){
  //       printf("  - mot %2d: ", i);
  //       affiche_vecteur(mots_k[i], k);
  //       printf(", poids: %d\n", poids(mots_k[i], k));
  //   }
  //
  //   printf("\nDistances de Hamming entre les mots de %d bits\n", k);
  //   for(unsigned int i = 0; i <= pow2(k)-1; i++){
  //       for(unsigned int j = i+1; j <= pow2(k)-1; j++){
  //           printf("  - d(");
  //           affiche_vecteur(mots_k[i], k);
  //           printf(", ");
  //           affiche_vecteur(mots_k[j], k);
  //           printf(") = %d\n", hamming(mots_k[i], mots_k[j], k));
  //       }
  //   }
  //
  //   printf("\nMatrice G:\n");
  //   affiche_matrice(g, k, n);
  //
  //
  //   printf("\nCodage des %d mots de %d bits\n", pow2(k), k);
	// int** mots_code = (int**) malloc(pow2(k)*sizeof(int*));
  //   for(unsigned int i = 0; i <= pow2(k)-1; i++){
  //
	// 	mots_code[i] = encode(g, mots_k[i], k, n);
  //
  //       printf("  - g(");
  //       affiche_vecteur(mots_k[i], k);
  //       printf(") = ");
  //       affiche_vecteur(mots_code[i], n);
  //       printf("\n");
  //   }
    //
    // int * t = calloc(7, sizeof(int));
    // t[0] = 13 ;
    // t[1] = 10 ;
    // t[2] = 8 ;
    // t[3] = 7;
    // t[4] = 4;
    // t[5] = 2;
    // t[6] = 1;
    //
    // encode_int(t, 7, 7, 4);
    //
    //
    // int * s = calloc(7, sizeof(int));
    // s[0] = 1 ;
    // s[1] = 2 ;
    // s[2] = 3 ;
    // s[3] = 4;
    // s[4] = 5;
    // s[5] = 6;
    // s[6] = 7;
    // syndrome_int(s, 47, 7, 4);



//     printf("\nDistance minimale entre les mots du code: %d\n", dist_min(mots_code, n));
//
//     printf("\nCapacite de correction du code: %d bit\n", (dist_min(mots_code, n)-1)/2);
//
//     printf("\nMatrice H:\n");
//     affiche_matrice(h, n-k, n);
//
//     printf("\nCalcul des syndromes des mots de %d bits\n", n);
//     int** mots_n = mots(n);
//
//     for(unsigned int i = 0; i <= pow2(n)-1; i++){
//
//         printf("  - h(");
//         affiche_vecteur(mots_n[i], n);
//         printf(") = ");
//         affiche_vecteur(syndrome(h, mots_n[i], k, n), n-k);
//         printf("\n");
//     }
//
//     printf("\nTest de bruit:\n");
//     int mot1[7] = {0, 0, 0, 0, 0, 0, 0};
//     int mot2[7] = {0, 0, 1, 0, 1, 1, 0};
//     int mot3[7] = {0, 1, 0, 0, 1, 1, 1};
//     int mot4[7] = {0, 1, 1, 0, 0, 0, 1};
//     int mot5[7] = {1, 0, 0, 0, 1, 0, 1};
//     int mot6[7] = {1, 0, 1, 0, 0, 1, 1};
//     int mot7[7] = {1, 1, 1, 1, 1, 1, 1};
//
//     int* bruit1 = NULL;
//     int* bruit2 = NULL;
//     int* bruit3 = NULL;
//     int* bruit4 = NULL;
//     int* bruit5 = NULL;
//     int* bruit6 = NULL;
//     int* bruit7 = NULL;
//
//     int* corrige1 = NULL;
//     int* corrige2 = NULL;
//     int* corrige3 = NULL;
//     int* corrige4 = NULL;
//     int* corrige5 = NULL;
//     int* corrige6 = NULL;
//     int* corrige7 = NULL;
//
//     int bit_erreur;
//
//     // Mot 1: (0, 0, 0, 0, 0, 0, 0)
//     bit_erreur = 0;
//     bruit1 = bruite(mot1, n, bit_erreur);
//     printf("  - bit %d: ", bit_erreur);
//     affiche_vecteur(mot1, n);
//     printf(" -> ");
//     affiche_vecteur(bruit1, n);
//     printf(" - ");
//     affiche_vecteur(syndrome(h, bruit1, k, n), n-k);
//     printf("\n");
//
//     // Mot 2: (0, 0, 0, 1, 0, 1, 1)
//     bit_erreur = 1;
//     bruit2 = bruite(mot2, n, bit_erreur);
//     printf("  - bit %d: ", bit_erreur);
//     affiche_vecteur(mot2, n);
//     printf(" -> ");
//     affiche_vecteur(bruit2, n);
//     printf(" - ");
//     affiche_vecteur(syndrome(h, bruit2, k, n), n-k);
//     printf("\n");
//
//     // Mot 3: (0, 0, 1, 1, 1, 0, 1)
//     bit_erreur = 2;
//     bruit3 = bruite(mot3, n, bit_erreur);
//     printf("  - bit %d: ", bit_erreur);
//     affiche_vecteur(mot3, n);
//     printf(" -> ");
//     affiche_vecteur(bruit3, n);
//     printf(" - ");
//     affiche_vecteur(syndrome(h, bruit3, k, n), n-k);
//     printf("\n");
//
//     // Mot 4: (0, 1, 0, 1, 1, 0, 0)
//     bit_erreur = 3;
//     bruit4 = bruite(mot4, n, bit_erreur);
//     printf("  - bit %d: ", bit_erreur);
//     affiche_vecteur(mot4, n);
//     printf(" -> ");
//     affiche_vecteur(bruit4, n);
//     printf(" - ");
//     affiche_vecteur(syndrome(h, bruit4, k, n), n-k);
//     printf("\n");
//
//     // Mot 5: (0, 1, 1, 1, 0, 1, 0)
//     bit_erreur = 4;
//     bruit5 = bruite(mot5, n, bit_erreur);
//     printf("  - bit %d: ", bit_erreur);
//     affiche_vecteur(mot5, n);
//     printf(" -> ");
//     affiche_vecteur(bruit5, n);
//     printf(" - ");
//     affiche_vecteur(syndrome(h, bruit5, k, n), n-k);
//     printf("\n");
//
//     // Mot 6: (0, 1, 1, 1, 0, 1, 0)
//     bit_erreur = 5;
//     bruit6 = bruite(mot6, n, bit_erreur);
//     printf("  - bit %d: ", bit_erreur);
//     affiche_vecteur(mot6, n);
//     printf(" -> ");
//     affiche_vecteur(bruit6, n);
//     printf(" - ");
//     affiche_vecteur(syndrome(h, bruit6, k, n), n-k);
//     printf("\n");
//
//     // Mot 7: (0, 1, 1, 1, 0, 1, 0)
//     bit_erreur = 6;
//     bruit7 = bruite(mot7, n, bit_erreur);
//     printf("  - bit %d: ", bit_erreur);
//     affiche_vecteur(mot7, n);
//     printf(" -> ");
//     affiche_vecteur(bruit7, n);
//     printf(" - ");
//     affiche_vecteur(syndrome(h, bruit7, k, n), n-k);
//     printf("\n\n");
//
//     printf("\nIndice des syndromes dans la matrice H:\n");
//     printf("  - ");
//     affiche_vecteur(s1, n-k);
//     printf(": %d\n", indice_colonne((int*)s1, h, k, n));
//
//     printf("  - ");
//     affiche_vecteur(s2, n-k);
//     printf(": %d\n", indice_colonne((int*)s2, h, k, n));
//
//     printf("  - ");
//     affiche_vecteur(s3, n-k);
//     printf(": %d\n", indice_colonne((int*)s3, h, k, n));
//
//     printf("  - ");
//     affiche_vecteur(s4, n-k);
//     printf(": %d\n", indice_colonne((int*)s4, h, k, n));
//
//     printf("  - ");
//     affiche_vecteur(s5, n-k);
//     printf(": %d\n", indice_colonne((int*)s5, h, k, n));
//
//     printf("  - ");
//     affiche_vecteur(s6, n-k);
//     printf(": %d\n", indice_colonne((int*)s6, h, k, n));
//
//     printf("  - ");
//     affiche_vecteur(s7, n-k);
//     printf(": %d\n", indice_colonne((int*)s7, h, k, n));
//
//     printf("\nCorrection de vecteur\n");
//     corrige1 = corrige(bruit1, h, k, n);
//     printf("  - ");
//     affiche_vecteur(bruit1, n);
//     printf(" -> ");
//     affiche_vecteur(corrige1, n);
//     printf(" - syndrome corrige: ");
//     affiche_vecteur(syndrome(h, corrige1, k, n), n-k);
//     printf("\n");
//
//     corrige2 = corrige(bruit2, h, k, n);
//     printf("  - ");
//     affiche_vecteur(bruit2, n);
//     printf(" -> ");
//     affiche_vecteur(corrige2, n);
//     printf(" - syndrome corrige: ");
//     affiche_vecteur(syndrome(h, corrige2, k, n), n-k);
//     printf("\n");
//
//     corrige3 = corrige(bruit3, h, k, n);
//     printf("  - ");
//     affiche_vecteur(bruit3, n);
//     printf(" -> ");
//     affiche_vecteur(corrige3, n);
//     printf(" - syndrome corrige: ");
//     affiche_vecteur(syndrome(h, corrige3, k, n), n-k);
//     printf("\n");
//
//     corrige4 = corrige(bruit4, h, k, n);
//     printf("  - ");
//     affiche_vecteur(bruit4, n);
//     printf(" -> ");
//     affiche_vecteur(corrige4, n);
//     printf(" - syndrome corrige: ");
//     affiche_vecteur(syndrome(h, corrige4, k, n), n-k);
//     printf("\n");
//
//     corrige5 = corrige(bruit5, h, k, n);
//     printf("  - ");
//     affiche_vecteur(bruit5, n);
//     printf(" -> ");
//     affiche_vecteur(corrige5, n);
//     printf(" - syndrome corrige: ");
//     affiche_vecteur(syndrome(h, corrige5, k, n), n-k);
//     printf("\n");
//
//     corrige6 = corrige(bruit6, h, k, n);
//     printf("  - ");
//     affiche_vecteur(bruit6, n);
//     printf(" -> ");
//     affiche_vecteur(corrige6, n);
//     printf(" - syndrome corrige: ");
//     affiche_vecteur(syndrome(h, corrige6, k, n), n-k);
//     printf("\n");
//
//     corrige7 = corrige(bruit7, h, k, n);
//     printf("  - ");
//     affiche_vecteur(bruit7, n);
//     printf(" -> ");
//     affiche_vecteur(corrige7, n);
//     printf(" - syndrome corrige: ");
//     affiche_vecteur(syndrome(h, corrige7, k, n), n-k);
//     printf("\n");
//
//     printf("\nDecodage\n");
//     printf("  - ");
//     affiche_vecteur(corrige1, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige1, h, k, n), k);
//     printf("\n");
//
//     printf("  - ");
//     affiche_vecteur(corrige2, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige2, h, k, n), k);
//     printf("\n");
//
//     printf("  - ");
//     affiche_vecteur(corrige3, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige3, h, k, n), k);
//     printf("\n");
//
//     printf("  - ");
//     affiche_vecteur(corrige3, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige3, h, k, n), k);
//     printf("\n");
//
//     printf("  - ");
//     affiche_vecteur(corrige4, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige4, h, k, n), k);
//     printf("\n");
//
//     printf("  - ");
//     affiche_vecteur(corrige5, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige5, h, k, n), k);
//     printf("\n");
//
//     printf("  - ");
//     affiche_vecteur(corrige6, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige6, h, k, n), k);
//     printf("\n");
//
//     printf("  - ");
//     affiche_vecteur(corrige7, n);
//     printf(" -> ");
//     affiche_vecteur(decode(corrige7, h, k, n), k);
//     printf("\n");
//
    return 0;
}
