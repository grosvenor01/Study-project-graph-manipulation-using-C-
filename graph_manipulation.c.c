#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
int choix; //le numero de choix
int matrice_adja[100][100];
int taille=-1; // graphe n'est pas initialisé
int status; // l'etat de graphe si oriente ou non  

//int test1[][] = {{1,0,1,0},{1,0,1,0},{1,0,1,0},{1,0,1,0},};
void menu(){
    printf("******************************MENU******************************\n");
    printf("1. Construire un graphe\n");
    printf("2. Afficher le graphe\n");
    printf("3. Calculer la densité d'une graphe\n");
    printf("4. Calculer le degre d'un graphe\n");
    printf("5. Le graphe est eulerien ?\n");
    printf("6. Le graph est complet ?\n");
    printf("7. Le graph est un arbre ?\n");
    printf("8. Recherche d'un element dans le graphe\n");
    printf("9. Recherche de tous les chemins entre deux noueds\n");
    printf("10.Recherche de tous le chemin plus court entre deux noueds\n");
    printf("11.Recherche d'une composante connexe a partir d'un noeud\n");
    printf("12.Trouver tous les cycles/circuits dans le graphe\n");
    printf("13.Ajouter/Supprimer un noued avec ses liens\n");
    printf("14.ajouter une lien (arc ou arete) entre deux noueds existants\n");
    printf("******************************FIN MENU******************************\n");
}


void construire1(){ //utiliser la matrice d'adjacence 
    printf("Taper le nombre des noueds de votre graphe: ");
    scanf("%d",&taille);
    printf("Taper 1 si le graph est oriente et 2 sinon: ");
    scanf("%d",&status);
    while(status != 1 && status != 2){
        printf("Taper 1 si le graph est oriente et 2 sinon: ");
        scanf("%d",&status);
    }
    for(int i=0;i<taille;i++){
        for(int j=0;j<taille;j++){
          matrice_adja[i][j]=0; //initialization d'une matrice a 0 
        }
    }
}


void afficher1(){ //afichage de matrice d'adjacence
    if(taille == -1){
       printf("Le graphe n'existe pas\n");
    }
    else {
       printf("[\n");
       for(int i=0;i<taille;i++){
	 printf("[");
	 for(int j=0;j<taille;j++){
	    printf("%d   ",matrice_adja[i][j]);
	 }
	 printf("]\n");
       }
       printf("]\n");
    }
}


void densite1(){
   int numarc = 0; 
   for(int i =0;i<taille;i++){
       for(int j=0;j<taille;j++){
           if(matrice_adja[i][j]>0){
               numarc++;
           }
       }
   }
   double densite = (double)(2*numarc)/(taille * (taille -1));
   printf("la densite de ce graph est : %f\n",densite);
}

void degre1(){
   int maxDegree=0;
   if(status == 1){ //graphe orienté
      for (int i = 0; i < taille; i++) { 
        int inDegree = 0; 
        int outDegree = 0; 
        for (int j = 0; j < taille; j++) { 
            if (matrice_adja[i][j] == 1) { 
                outDegree++; 
            } 
            if (matrice_adja[j][i] == 1) { 
                inDegree++; 
            } 
        } 
        int degree = inDegree + outDegree; 
        if (degree > maxDegree) { 
            maxDegree = degree; 
        } 
      }
   }
   else { // graphe non orienté 
      for (int i = 0; i < taille; i++) { 
        int degree = 0; 
        for (int j = 0; j < taille; j++) { 
            if (matrice_adja[i][j] == 1) { 
                degree++; 
            } 
        } 
        if (degree > maxDegree) { 
            maxDegree = degree; 
        } 
      } 
   }
   printf("Le degre du graphe est : %d\n", maxDegree);
}
int isEulerian() {
    int oddDegree = 0; // calculer le degre de chaque noued 
    for (int i = 0; i < taille; i++) {
        int degree = 0;
        for (int j = 0; j < taille; j++) {
            if (matrice_adja[i][j] == 1) {
                degree++;
            }
        } 
        // si le degree est paire alors le graphe est eulerien 
        if (degree % 2 != 0) {
            oddDegree++;
        }
    }
    // si y'a pas un noued qui a un degre impaire 
    if (oddDegree== 0) {
        printf("Le graphe est eulerien\n");
    }
    // si le grape contient exactement deux noued avec degre impiare 
    else if (oddDegree == 2) {
        printf("Le graphe est semi eulerien\n");
    }
    else {
        printf("Le graphe est pas eulerien\n");
    }
}

void isComplete() {
    // tester si tous les noued sont connecter 
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            if (i != j && matrice_adja[i][j] != 1) {
                printf("Le graphe est pas complet\n");
                return;
            }
        }
    }
    
    printf("Le graphe est complet\n");
}



void isTree(int current, int parent) {
    bool visited[taille];
    visited[current] = true;
    for (int i = 0; i < taille; i++) {
        if (matrice_adja[current][i]) {
            // si le voisin n'est pas le parent et a déjà été visité, il y a un cycle
            if (i != parent && visited[i]) {
                printf("Le graphe est pas un arbre\n");
                return;
            }

            // Si le voisin n'a pas été visité, on effectue une recherche récursive
            if (!visited[i]) {
                isTree(i, current);
                if (!visited[current])
                    return;
            }
        }
    }
    if(visited[current]){
       printf("Le graphe est pas un arbre\n");
    }
}

void searchNode(int node) {
    printf("Noeud recherche : %d\n", node);
    if (node < 0 || node >= taille) {
        printf("Noeud non valide.\n");
        return;
    }

    printf("Liens du noeud %d :\n", node);
    for (int i = 0; i < taille; i++) {
        if (matrice_adja[node][i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
void printPath(int path[], int length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void findAllPaths(int current, int destination, int path[], int pathLength) {
    bool visited[taille];
    visited[current] = true;
    path[pathLength] = current;
    pathLength++;

    if (current == destination) {
        printPath(path, pathLength);
    } else {
        for (int i = 0; i < taille; i++) {
            if (matrice_adja[current][i] && !visited[i]) {
                findAllPaths(i, destination, path, pathLength);
            }
        }
    }

    visited[current] = false;
}

void searchPaths(int source, int destination) {
    printf("Recherche de tous les chemins entre les noeuds %d et %d :\n", source, destination);

    if (source < 0 || source >= taille || destination < 0 || destination >= taille) {
        printf("Noeuds non valides.\n");
        return;
    }

    int path[taille];
    int pathLength = 0;

    findAllPaths(source, destination, path, pathLength);
}


void dijkstra(int depart, int arrivee) {
    int distances[taille];
    bool visite[taille];
    int precedent[taille];
    // Initialiser les tableaux distances et visite
    for (int i = 0; i < taille; i++) {
        distances[i] = INT_MAX;
        visite[i] = false;
        precedent[i] = -1;
    }

    // Définir la distance du nœud de départ à 0
    distances[depart] = 0;

    for (int i = 0; i < taille - 1; i++) {
        int u = -1;
        int minDistance = INT_MAX;

        // Trouver le nœud non visité avec la plus petite distance actuelle
        for (int j = 0; j < taille; j++) {
            if (!visite[j] && distances[j] < minDistance) {
                u = j;
                minDistance = distances[j];
            }
        }

        if (u == -1)
            break;

        visite[u] = true;

        // Mettre à jour les distances des nœuds adjacents
        for (int v = 0; v < taille; v++) {
            if (!visite[v] && matrice_adja[u][v] != 0 && distances[u] != INT_MAX && distances[u] + matrice_adja[u][v] < distances[v]) {
                distances[v] = distances[u] + matrice_adja[u][v];
                precedent[v] = u;
            }
        }
    }

    // Afficher le plus court chemin
    printf("Plus court chemin du nœud %d au nœud %d :\n", depart, arrivee);
    printf("Distance : %d\n", distances[arrivee]);
    printf("Chemin : ");
    int courant = arrivee;
    while (courant != -1) {
        printf("%d ", courant);
        courant = precedent[courant];
    }
    printf("\n");
}

void printCycle(int cycle[], int cycleLength) {
    printf("Cycle : ");
    for (int i = 0; i < cycleLength; i++) {
        printf("%d ", cycle[i]);
    }
    printf("\n");
}

void findCyclesUtil(bool visited[], int cycle[], int currentNode, int startNode, int cycleLength) {
    visited[currentNode] = true;
    cycle[cycleLength] = currentNode;

    // Vérifier s'il y a un cycle complet
    if (currentNode == startNode && cycleLength > 1) {
        printCycle(cycle, cycleLength + 1);
    }

    // Parcourir les nœuds adjacents non visités
    for (int i = 0; i < taille; i++) {
        if (matrice_adja[currentNode][i] && !visited[i]) {
            findCyclesUtil(visited, cycle, i, startNode, cycleLength + 1);
        }
    }

    // Retirer le nœud courant de la liste des nœuds visités
    visited[currentNode] = false;
}

void findCyclesAndCircuits() {
    bool visited[taille];
    memset(visited,false,sizeof(visited));
    int cycle[taille];

    // Parcourir tous les nœuds comme nœud de départ potentiel
    for (int i = 0; i < taille; i++) {
        findCyclesUtil(visited, cycle, i, i, 0);
        visited[i] = true; // Marquer le nœud de départ comme visité
    }
}
void ajouter_supprimer(){
    int choice;
    int noued ,typearc;
    printf("Taper 1 pour ajouter ou 2 pour supprimer un noued: ");
    scanf("%d",&choice);
    
    if(choice == 1){
       taille++; //augmanter la taille de matrice 
       for(int i =0; i<taille;i++){       //ajouter une nouvelle ligne et collonne et les initializer a 0 
           matrice_adja[taille-1][i]=0;
           matrice_adja[i][taille-1]=0;
       }
       while(1){
         printf("relier le nouveau noued avec le noued numero (taper -1 pour quitter) : ");
         scanf("%d",&noued);
         if(noued >taille){
            printf("y'a que %d noueds",taille);
         }
         if(noued == -1){
            break;
         }
         if(status == 1){ //le graphe est oriente
             printf("Taper 1 pour arc entrant ou 2 pour arc sotant: ");
             scanf("%d",&typearc); 
             while(typearc!=1 && typearc!=2){
                 printf("Taper 1 pour arc entrant ou 2 pour arc sotant: ");
                 scanf("%d",&typearc);
             }
             if(typearc==2)
                 matrice_adja[taille-1][noued-1] = 1;
             else 
                 matrice_adja[noued-1][taille-1] = 1;
         }
         else if(status ==2){
             matrice_adja[taille-1][noued-1] = 1;
             matrice_adja[noued-1][taille-1] = 1;
         }
       }
    }
    else if(choice == 2){
       int node;
       printf("Tapez l'element que vous voulez supprimer: ");
       scanf("%d",&node);
       if(node>taille || node <0){
          printf("Noeuds non valides.\n");
          return;
       }
       for (int i = 0; i < taille; i++) {
           matrice_adja[node][i] = 0;
       }
       for (int i = 0; i < taille; i++) {
           matrice_adja[i][node] = 0;
       }
    }
}

void addEdge(int node1, int node2) {
    if(status==2){      //si le graph est pas oriente
        matrice_adja[node1][node2] = 1;
        matrice_adja[node2][node1] = 1;
    }
    else {
        matrice_adja[node1][node2] = 1;
    }
}

void DFS(int node, int visited[]) {
    visited[node] = 1;  // marquer le nœud comme visité
    printf("%d ", node);  // afficher le nœud visité
    
    for (int i = 0; i < taille; i++) {
        if (matrice_adja[node][i] == 1 && visited[i] == 0) {
            DFS(i,visited);  // appeler récursivement DFS pour les nœuds adjacents non visités
        }
    }
}
void rechercheComposanteConnexe(int a) {
    int visited[taille];
    // Initialiser le tableau visited à 0
    for (int i = 0; i < taille; i++) {
        visited[i] = 0;
    }
    
    printf("Composante connexe à partir du nœud %d : ", a);
    DFS(a,visited);
    printf("\n");
}
void main(){
    int source, destination;
    menu();
    while(1){
       printf("Tapez le numero de votre choix: ");
       scanf("%d",&choix);
       switch (choix){
          case 1 :  construire1(); // cree represetation matrice d'adjacance
                    printf("---Graphe cree---\n");
                    break;
                    
          case 2 :  afficher1(); // afficher representation matrice d'adjancence
                    break; 
                    
          case 3 :  densite1(); // calculer la densite avec representation matricielle
                    break;
          case 4 :  degre1();
                    break;
          case 5 :  isEulerian();
                    break;
          case 6 :  isComplete();
                    break; 
          case 7 :  isTree(0,-1);
                    break;
          case 8 :  int node;
                    printf("Taper le numero de noued que vous cherchez: ");
                    scanf("%d",&node);
                    searchNode(node);
                    break; 
          case 9 :  
                    printf("Entrer le numero du noeud source : ");
                    scanf("%d", &source);
                    printf("Entrer le numero du noeud destination : ");
                    scanf("%d", &destination);
                    searchPaths(source, destination);
                    break;
          case 10 : 
                    printf("Entrer le numero du noeud source : ");
                    scanf("%d", &source);
                    printf("Entrer le numero du noeud destination : ");
                    scanf("%d", &destination);
                    dijkstra(source,destination);
                    break; 
          case 11 : printf("Entrer le numero du noeud source : ");
                    scanf("%d", &source);
                    rechercheComposanteConnexe(source);
                    break;
          case 12 : findCyclesAndCircuits();
                    break;
          case 13 : ajouter_supprimer();
                    break; 
          case 14 : printf("Entrer le numero du noeud source : ");
                    scanf("%d", &source);
                    printf("Entrer le numero du noeud destination : ");
                    scanf("%d", &destination);
                    addEdge(source,destination);
                    break; 
       }
    }
}
