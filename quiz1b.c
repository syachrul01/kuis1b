#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void proses(char text[50]){

	int n = 0; // Membuat variabel integer n dan di inisialisasikan 0
	char temp[500]; // membuat array of char

	FILE *fdata; // membuat fdata
	fdata = fopen(text, "r"); // membuka & membaca file text.txt

	int status = 0; // Membuat variabel integer status dan di inisialisasikan 0

	// proses berjalan selama status nya 0 
	do{

		fscanf(fdata, "%s", temp); // Menyalin kata yg ada di file text ke temp
		if(strcmp(temp, "##") == 0){ // Jika kata yg disalinnya adalah "##"
			status = 1; // status nya menjadi 1
		}
		else{ // jika tidak
			n++; // Variabel integer n bertambah untuk menghitung banyaknya kata
		}

	}while(status == 0);

	// Menampilkan 
	printf("Jumlah kata text adalah %d \n", n);
	fclose(fdata); // Menutup file

}

void fork_1(){
	int pid;	
	proses("text1.txt");
		
	switch(pid = fork()){
	case 0:
		proses("text2.txt");
		break;
	default:
		printf("proses ortu: pid=%d, anak pid = %d\n", getpid(), pid);
		break;
	case -1:
		perror("fork");
		exit(1);
	}
	exit(0);
}

void *myThread(void *vargp){
	sleep(1);
	proses("text2.txt");
	return NULL;	
}

int main(int argc, char **argv){


	int menu; 
	printf("1) Fork \n2) Thread\n");
	scanf("%d", &menu);

	
	if(menu == 1){
		fork_1();
	}
	else if(menu == 2){
		pthread_t thread_id;
	
		printf("Sebelum Thread\n");

		proses("text1.txt");
		
		// buat thread
		pthread_create(&thread_id, NULL, myThread, NULL);

		
		// tunggu thread selesaim jika tidak ada join, maka akan lgsg exit
		pthread_join(thread_id, NULL);
		printf("Sesudah Thread\n");
		
		exit(0);
	}else{
		printf("Pilihan menu hanya 1/2\n");
	}
	
		
return 0;
}

