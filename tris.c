#include <stdio.h>

int vincente(int x[3][3]){
	int i;
	int j;
	int a;
	for (i=0;i<3;i++){
		a=0;
		for(j=0; j<2; j++) {
			if (x[i][j] == x[i][j+1]) a=a+1;
			if (a==2 && x[i][j]==1) return 1;
			if (a==2 && x[i][j]==2) return 2; 
		}
	}
	
	for (j=0;j<3;j++){
		a=0;
		for(i=0; i<2; i++) {
			if (x[i][j] == x[i+1][j]) a=a+1; 
			if (a==2 && x[i][j]==1) return 1;
			if (a==2 && x[i][j]==2) return 2;
		}	
	}
	
	a=0;
	for (j=0;j<2;j++)
	{
		if( x[j][j]==x[j+1][j+1]) a=a+1;
		if (a==2 && x[j][j]==1) return 1;
		if (a==2 && x[j][j]==2) return 2;
	}	
	a=0;
	for (j=0;j<2;j++){
		if (x[j][2-j]== x[j+1][1-j]) a=a+1;
		if (a==2 && x[j][j]==1) return 1;
		if (a==2 && x[j][j]==2) return 2;
	}
	
	return 0;
}

int pari (int x[3][3])
{
	int k,h;
	
	for (k=0; k<3; k++) {
		for (h=0;h<3;h++){
			if (x[k][h]==0) return 0;
		}
	}
	if (vincente(x)==0) return 1;
	return 0;
}

int mossa (int x[3][3], int giocatore, int i, int j, int con)
{
	int k, h, m[3][3];
	
	//printf("%i\n", con);
    
    for (k=0; k<3; k++) {
		for (h=0;h<3;h++){
			m[k][h]=x[k][h];
		}
	}
	
	if (m[i][j]!=0) return 0; 
	m[i][j]=giocatore;
	if (vincente(m)==giocatore) {
		//printf("Giocatore %d, %d / %d (1� IF)\n", giocatore, i+1, j+1);
		return vincente(m);//provvisorio
	}
	
	if (pari(m)) {
		//printf("Giocatore %d, %d / %d (2� IF)\n", giocatore, i+1, j+1);
		return 3;
	}
    for (k=0; k<3; k++) {
        for (h=0;h<3;h++) {
            return mossa(m, 3-giocatore, k, h, con+1);    //prova
        }
	}
	
	return 0;
}
	
int mossa_random (int x[3][3], int giocatore) 
{
	int i, j;
	
	for (i=0; i<3; i++) {
		for (j=0;j<3;j++){
			if (x[i][j]==0) { 
				x[i][j]=giocatore;
				printf("Giocatore %d, %d / %d  (mossa random)\n", giocatore, i+1, j+1);
				return 0;
			}
		}
	}
}


int gioca (int x[3][3], int giocatore)
{
	int a,b;
	
	for (a=0; a<3; a++) {
		for (b=0; b<3; b++) {
			if (mossa(x, giocatore, a, b, 0)==giocatore || mossa(x, giocatore, a, b, 0)==3) {
				x[a][b]=giocatore;
				printf("Giocatore %d, %d / %d \n", giocatore, a+1, b+1);
				return 1;
			}
			if (mossa(x, 3-giocatore, a, b, 0)==3-giocatore || mossa(x, 3-giocatore, a, b, 0)==3) {
				x[a][b]=giocatore;
				printf("Giocatore %d, %d / %d \n", giocatore, a+1, b+1);
				return 1;
			}/*
            x[a][b]=giocatore;
            if (gioca(x, 3-giocatore)==0) return 1; //Fare prova con schema gi� iniziato
            x[a][b]=0;
            */
		}
	}
	
	mossa_random(x, giocatore);
	
	return 0;
}



int main () {
	
	int x[3][3];
	int i, j, giocatore=2;
	
	for (i=0; i<3; i++) {
		for (j=0;j<3;j++){
			x[i][j]=0;
		}
	}
	while (vincente(x)==0 && pari(x)==0) {
		gioca(x, giocatore);
		giocatore = 3-giocatore;
    }
        
	if (vincente(x)) printf("Vince %d\n", vincente(x));
	if (pari(x)) printf("Avete pareggiato");
    return 0;
} 
