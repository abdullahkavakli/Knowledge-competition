#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> 
#include <windows.h>
#include <conio.h>
#include <unistd.h>

struct soru {
	int soru_ID;
	char soru_metni[250];
	char secenek_A[30];
	char secenek_B[30];
	char secenek_C[30];
	char secenek_D[30];
	char Dogru_cevap; 
 }; 
 
 struct oyuncu{
 	char oyuncu_adi_soyadi[30];
 	int skor;
 };


 int secenekgir( void );
 void soruekle( FILE *fPtr );
 void sorusil( FILE *fPtr );
 void goster_ve_guncelle( FILE *fPtr );
 void cvp_ile_goster( FILE *fPtr , int numara );
 void guncelle( FILE *fPtr , int numara );
 void oyun_oyna( FILE *fPtr, FILE *sPtr );
 void enyuksekskor( FILE *fPtr );

 int main( void )
 {
	setlocale(LC_ALL, "Turkish");  	
	FILE *cfPtr; 
	FILE *sfPtr;
	int secim; 

	srand(time(NULL)); 
	int rasgele_soru_1;
 	int rasgele_soru_2;
 	int rasgele_soru_3;
 	int rasgele_soru_4;
 	int rasgele_soru_5;

	if ( !( cfPtr = fopen( "sorular.txt", "a+" ) ) ) {
	printf( "Dosya açýlmadý.\n" );
	} 
	else {
	fclose(cfPtr);
	while ( ( secim = secenekgir() ) != 6 ) {
	
	
	cfPtr = fopen( "sorular.txt", "r+" );
	
	 switch ( secim ) {
	
	 case 1:
	 soruekle( cfPtr );
	 break;
	
	 case 2:
	 sorusil( cfPtr );
	 break;
	
	 case 3:
	 goster_ve_guncelle( cfPtr );
	 break;
	
	 case 4:
	 sfPtr = fopen( "skorlar.txt", "a+b" );
	 oyun_oyna( cfPtr, sfPtr );
	 break;

	 case 5:
	 if ( !( sfPtr = fopen( "skorlar.txt", "r+b" ) ) ) {
		printf( "Skor mevcut deðil skorlar dosyasý açýlamadý.\n" );
	 } 
	 else {
		enyuksekskor( sfPtr );
	 }
	 break;	
	 
	 default:
	 printf( "Yanlýþ seçim :(\n" );
	 break;
	
	 }
	
	 }
	 }
	 
	
 return 0;
}

 int secenekgir( void ){
 int secim; 


 printf( "\nTarafýný seç\n"
 "1 - Soru ekle\n"
 "2 - Soru sil\n"
 "3 - Sorularý göster ve güncelle\n"
 "4 - Oyun oyna\n"
 "5 - En yüksek Skorlar\n"
 "6 - Çýk\n›››› " );

 scanf( "%d", &secim );

 return secim;

 }
 
 void soruekle( FILE *fPtr ){
 	
	int soru_num;
	printf("Soru numarasý:");
	scanf( "%d", &soru_num );
 	
	struct soru rasgele={0,"","","","","",'\0'};

	 fseek( fPtr, ( soru_num - 1 ) * sizeof( struct soru ), SEEK_SET );
	
	
	 fread( &rasgele, sizeof( struct soru ), 1, fPtr );


	 if ( rasgele.soru_ID != 0 ) { 
	 printf( "Burada soru varmýþ :(\n");
	 } 
	
	 else { 
	

	rasgele.soru_ID=soru_num;
	
	
	getchar();
		printf("Soru metnini giriniz:\n");
		scanf("%[^\n]",&rasgele.soru_metni);
	getchar();
		printf("A þýkkýný giriniz:\n");
		scanf("%[^\n]",&rasgele.secenek_A);
	getchar();
		printf("B þýkkýný giriniz:\n");
		scanf("%[^\n]",&rasgele.secenek_B);
	getchar();
		printf("C þýkkýný giriniz:\n");
		scanf("%[^\n]",&rasgele.secenek_C);
	getchar();
		printf("D þýkkýný giriniz:\n");
		scanf("%[^\n]",&rasgele.secenek_D);
	getchar();
		printf("Doðru cvp giriniz:\n");
		scanf("%[^\n]",&rasgele.Dogru_cevap);

		
	 fseek( fPtr, ( rasgele.soru_ID - 1 ) * sizeof( struct soru ), SEEK_SET );
	

	 fwrite( &rasgele, sizeof( struct soru ), 1, fPtr );
	 
	 
	 printf("Soru dosyaya yazýlýyor...\n");
	 sleep(3.5);
	 printf("Soru baþarýlý bir þekilde eklenmiþtir:)\n");
	
	 fclose( fPtr ); 
	 sleep(3);
	 }

 }
 
 
 
 void sorusil( FILE *fPtr ){
 	
 	struct soru alinacak;
	struct soru silinecek={0,"","","","","",'\0'};

	int soru_num,s_sayisi,a;
	char e_h;	
	


	 
	 		while(!feof(fPtr)){
		fread(&alinacak,sizeof(struct soru),1,fPtr);
		s_sayisi++;
		}

		printf("(Boþ sorular yazdýrýlmamýþtýr.)\n");
		for(a=1; a<s_sayisi; a++){
			 fseek( fPtr, ( a - 1 ) * sizeof( struct soru ), SEEK_SET );
			 fread( &alinacak, sizeof( struct soru ), 1, fPtr );
			
			if (alinacak.soru_ID==0) continue;
			printf("Soru numarasý:%d\n"
			"Metin:%s\n\n",alinacak.soru_ID,&alinacak.soru_metni);	
		}
		

	printf("Silinecek sorunun numarasýný giriniz:");
	scanf( "%d", &soru_num );
	
	fseek( fPtr, ( soru_num - 1 ) * sizeof( struct soru ), SEEK_SET );
	
	fread( &alinacak, sizeof( struct soru ), 1, fPtr );
	 
	if (alinacak.soru_ID!=0){
	printf("Sorunun numarasý:%d\n"
	"Metin:%s\n",alinacak.soru_ID,&alinacak.soru_metni);
	}

	 if ( alinacak.soru_ID == 0 ) { 
	 	printf( "Burada soru yokmuþ :(\n");
	 } 
 	else{
 		printf("Emin misiniz?[E/H]");
 		scanf(" %c",&e_h);
	 		if(e_h=='E'){
	 		fseek( fPtr, ( soru_num - 1 ) * sizeof( struct soru ), SEEK_SET );
	 		
	 		fwrite( &silinecek, sizeof( struct soru ), 1, fPtr );
	 		}
	 }
 	
 	fclose(fPtr);
 	
 }
  
 void goster_ve_guncelle( FILE *fPtr ){
 	int istenen_num,a,s_sayisi=1;
 	struct soru alinacak={0,"","","","","",'\0'};


		while(!feof(fPtr)){
		fread(&alinacak,sizeof(struct soru),1,fPtr);
		s_sayisi++;
		}

		s_sayisi--;
		
		for(a=1; a<s_sayisi; a++){
			 fseek( fPtr, ( a - 1 ) * sizeof( struct soru ), SEEK_SET );
			 fread( &alinacak, sizeof( struct soru ), 1, fPtr );
			
			if (alinacak.soru_ID==0) continue;
			
			printf("Sorunun numarasý:%d\n"
			"Metin:%s\n"
			"A:%s\n"
			"B:%s\n"
			"C:%s\n"
			"D:%s\n"
			"Cvp:%c\n",alinacak.soru_ID,&alinacak.soru_metni,&alinacak.secenek_A,
			&alinacak.secenek_B,&alinacak.secenek_C,&alinacak.secenek_D,alinacak.Dogru_cevap);	
		}
		
	
	printf("Güncellenecek soruyu seçiniz:");
	scanf( "%d", &istenen_num );
		
		
	 if ( alinacak.soru_ID == 0 ) { 
	 	printf( "Burada soru yokmuþ :(\n");
	 } 
	 else{
	cvp_ile_goster( fPtr , istenen_num );
	guncelle( fPtr , istenen_num );
	}
 	
 }
 
 
 
 void cvp_ile_goster( FILE *fPtr , int istenen_num ){
 	
 	struct soru istenen_soru={0,"","","","","",'\0'};
	
	istenen_soru.soru_ID=istenen_num;
	
	fseek( fPtr, ( istenen_num - 1 ) * sizeof( struct soru ), SEEK_SET );
	fread(&istenen_soru, sizeof( struct soru), 1, fPtr);
	
	printf("Sorunun numarasý:%d\n"
	"Metin:%s\n"
	"A:%s\n"
	"B:%s\n"
	"C:%s\n"
	"D:%s\n"
	"Cvp:%c\n",istenen_soru.soru_ID,&istenen_soru.soru_metni,&istenen_soru.secenek_A,
	&istenen_soru.secenek_B,&istenen_soru.secenek_C,&istenen_soru.secenek_D,istenen_soru.Dogru_cevap);	
 	
 }
 
 
 
 void guncelle( FILE *fPtr , int numara ){
 	struct soru istenen_soru={0,"","","","","",'\0'};
 	
 	istenen_soru.soru_ID=numara;
 	
 	getchar();
		printf("Yeni soru metnini giriniz:\n");
		scanf("%[^\n]",&istenen_soru.soru_metni);
	getchar();
		printf("Yeni a þýkkýný giriniz:\n");
		scanf("%[^\n]",&istenen_soru.secenek_A);
	getchar();
		printf("Yeni b þýkkýný giriniz:\n");
		scanf("%[^\n]",&istenen_soru.secenek_B);
	getchar();
		printf("Yeni c þýkkýný giriniz:\n");
		scanf("%[^\n]",&istenen_soru.secenek_C);
	getchar();
		printf("Yeni d þýkkýný giriniz:\n");
		scanf("%[^\n]",&istenen_soru.secenek_D);
	getchar();
		printf("Yeni doðru cvp giriniz:\n");
		scanf("%[^\n]",&istenen_soru.Dogru_cevap);
 	
 	 fseek( fPtr, ( istenen_soru.soru_ID - 1 ) * sizeof( struct soru ), SEEK_SET );


	 fwrite( &istenen_soru, sizeof( struct soru ), 1, fPtr );
	
	 
	 fclose (fPtr);
 	 	 	
 }
 
 
   
void oyun_oyna( FILE *fPtr, FILE *sPtr ){
 	struct soru okunan_soru={0,"","","","","",'\0'};
 	struct oyuncu sampiyon={"",0};
 	char dogru[6];
 	char kullanici[6];
 	int soru_sayisi=0;
 	char kulcevap;
	int puan=0;
	int dolu=0;
	
	getchar();
	printf("Adınız?\n");
	scanf("%[^\n]",&sampiyon.oyuncu_adi_soyadi);
	
	rewind( fPtr );
	while(!feof(fPtr)){
		fread(&okunan_soru,sizeof(struct soru),1,fPtr);
		soru_sayisi++;
		if(okunan_soru.soru_ID!=0)
			dolu++;
	}
	dolu=dolu-1;
	if(dolu>=5){
		printf("%d soru arasýndan 5 adet rastgele soru seciliyor...\n", dolu);
		sleep(2.9);
		soru_sayisi=soru_sayisi-1;
		
		int rastgele_id1;
		srand(time(NULL));
		while(1){
			rastgele_id1=rand()%soru_sayisi;
			
			fseek(fPtr, (rastgele_id1+1-1)*sizeof(struct soru), SEEK_SET);
		
			fread(&okunan_soru,sizeof(struct soru),1,fPtr);
		
 			if(okunan_soru.soru_ID!=0){
	 			printf("\nSorunun numarasý:%d\n"
				"Metin:%s\n"
				"A:%s\n"
				"B:%s\n"
				"C:%s\n"
				"D:%s\n"
				"Cvp?:\n",okunan_soru.soru_ID,okunan_soru.soru_metni,okunan_soru.secenek_A,okunan_soru.secenek_B,okunan_soru.secenek_C,okunan_soru.secenek_D);
		
				break;
			}
		}
		scanf(" %c",&kulcevap);
 		if(kulcevap==okunan_soru.Dogru_cevap){
			printf("\nDogru cevap verdin!\n ");
		}
		else
			printf("\nYanlýs cevap verdin!\n ");
		
		dogru[0]=okunan_soru.Dogru_cevap;
		kullanici[0]=kulcevap;

 	
	 	int rastgele_id2;
 		int rastgele_id3;
 		int rastgele_id4;
 		int rastgele_id5;	
 	
	 
	 	while(1){
			rastgele_id2=rand()%soru_sayisi;
			if(rastgele_id2!=rastgele_id1){
				fseek(fPtr, (rastgele_id2+1-1)*sizeof(struct soru), SEEK_SET);
				fread(&okunan_soru,sizeof(struct soru),1,fPtr);
				if(okunan_soru.soru_ID!=0){
	 				printf("\nSorunun numarasý:%d\n"
					"Metin:%s\n"
					"A:%s\n"
					"B:%s\n"
					"C:%s\n"
					"D:%s\n"
					"Cvp?:",okunan_soru.soru_ID,okunan_soru.soru_metni,okunan_soru.secenek_A,okunan_soru.secenek_B,okunan_soru.secenek_C,okunan_soru.secenek_D);
		
					break;
				}
			}
		}
 		scanf(" %c",&kulcevap);
 		if(kulcevap==okunan_soru.Dogru_cevap){
 			printf("\nDogru cevap verdin!\n");
 		}
		else
			printf("\nYanlýs cevap verdin!\n");

		dogru[1]=okunan_soru.Dogru_cevap;
		kullanici[1]=kulcevap;
 			
 		while(1){
			rastgele_id3=rand()%soru_sayisi;
			if(rastgele_id3!=rastgele_id1 && rastgele_id3!=rastgele_id2){
				fseek(fPtr, (rastgele_id3+1-1)*sizeof(struct soru), SEEK_SET);
				fread(&okunan_soru,sizeof(struct soru),1,fPtr);
				if(okunan_soru.soru_ID!=0){
	 				printf("\nSorunun numarasý:%d\n"
					"Metin:%s\n"
					"A:%s\n"
					"B:%s\n"
					"C:%s\n"
					"D:%s\n"
					"Cvp?:",okunan_soru.soru_ID,okunan_soru.soru_metni,okunan_soru.secenek_A,okunan_soru.secenek_B,okunan_soru.secenek_C,okunan_soru.secenek_D);
		
					break;
				}
			}
		}
 		scanf(" %c",&kulcevap);
 		if(kulcevap==okunan_soru.Dogru_cevap){
 			printf("\nDogru cevap verdin!\n");
		}
		else
			printf("\nYanlýs cevap verdin!\n");

		dogru[2]=okunan_soru.Dogru_cevap;
		kullanici[2]=kulcevap;
		
				
		while(1){
			rastgele_id4=rand()%soru_sayisi;
			if(rastgele_id4!=rastgele_id1 && rastgele_id4!=rastgele_id2 && rastgele_id4!=rastgele_id3){
				fseek(fPtr, (rastgele_id4+1-1)*sizeof(struct soru), SEEK_SET);
				fread(&okunan_soru,sizeof(struct soru),1,fPtr);
				if(okunan_soru.soru_ID!=0){
	 				printf("\nSorunun numarasý:%d\n"
					"Metin:%s\n"
					"A:%s\n"
					"B:%s\n"
					"C:%s\n"
					"D:%s\n"
					"Cvp?:",okunan_soru.soru_ID,okunan_soru.soru_metni,okunan_soru.secenek_A,okunan_soru.secenek_B,okunan_soru.secenek_C,okunan_soru.secenek_D);		
					break;
				}
			}
		}
 		scanf(" %c",&kulcevap);
 		if(kulcevap==okunan_soru.Dogru_cevap){
 			printf("\nDogru cevap verdin!\n");
 		}
 		else
 			printf("\nYanlýs cevap verdin!\n");
	
		dogru[3]=okunan_soru.Dogru_cevap;
		kullanici[3]=kulcevap;
	
		while(1){
			rastgele_id5=rand()%soru_sayisi;
			if(rastgele_id5!=rastgele_id1 && rastgele_id5!=rastgele_id2 && rastgele_id5!=rastgele_id3 && rastgele_id5!=rastgele_id4){
				fseek(fPtr, (rastgele_id5+1-1)*sizeof(struct soru), SEEK_SET);
				fread(&okunan_soru,sizeof(struct soru),1,fPtr);
				if(okunan_soru.soru_ID!=0){
	 				printf("\nSorunun numarasý:%d\n"
					"Metin:%s\n"
					"A:%s\n"
					"B:%s\n"
					"C:%s\n"
					"D:%s\n"
					"Cvp?:",okunan_soru.soru_ID,okunan_soru.soru_metni,okunan_soru.secenek_A,okunan_soru.secenek_B,okunan_soru.secenek_C,okunan_soru.secenek_D);
		
					break;
				}
			}
		}
 		scanf(" %c",&kulcevap);
 		if(kulcevap==okunan_soru.Dogru_cevap){ 
			printf("\nDogru cevap verdin!\n");
		}
		else
			printf("\nYanlýs cevap verdin!\n");
	
		dogru[4]=okunan_soru.Dogru_cevap;
		kullanici[4]=kulcevap;
	
	
		if(dogru[0]==kullanici[0])
			puan++;
	
		if(dogru[1]==kullanici[1])
			puan++;
			
		if(dogru[2]==kullanici[2])
			puan++;
			
		if(dogru[3]==kullanici[3])
			puan++;
			
		if(dogru[4]==kullanici[4])
			puan++;	
	
	
		sampiyon.skor=puan;
	 
		printf("Adýnýz: %s\n",sampiyon.oyuncu_adi_soyadi);
		printf("Puanýnýz: %d\n",sampiyon.skor);
		fwrite(&sampiyon,sizeof(struct oyuncu),1,sPtr);
		fclose(sPtr);
		printf("Adýnýz ve Puanýnýz skorlar.txt dosyasýna yazýldý.\n");
		sleep(2.7);
		printf("Ana menüye yönlendirliyorsunuz...\n");
		sleep(3.9);
	}
	
	else{
		printf("Soru sayýsý %d ve 5'den az rasgele 5 soru secilemiyor! Soru ekleyin!\n", dolu);
	}
 }
	
 
 
void enyuksekskor( FILE *fPtr ){
  	struct oyuncu sampiyon;
  	int xyz=0;
  	int asd1=0;
  	int asd2=0;
  	int asd3=0;
  	int asd4=0;
  	int asd5=0;
  	int asd6=0;
  	int sori=0;
  	int say;
  	
  	printf("### En yüksek 3 skor ###\n");
  	
  	while(!feof(fPtr)){
  		fread(&sampiyon,sizeof(struct oyuncu),1,fPtr);
  		sori++;
	}
	sori=sori-1;
	
	rewind( fPtr );
  	for(say=0;say<sori;say++){
  		fread(&sampiyon,sizeof(struct oyuncu),1,fPtr);
		if(sampiyon.skor==5){
			printf("%s	%d\n",sampiyon.oyuncu_adi_soyadi,sampiyon.skor);
			asd1++;
		}
	}
	if(asd1>0){
		xyz++;
		printf("__________________\n");
	}
	
	rewind( fPtr );
	for(say=0;say<sori;say++){
		fread(&sampiyon,sizeof(struct oyuncu),1,fPtr);
		if(sampiyon.skor==4){
			printf("%s	%d\n",sampiyon.oyuncu_adi_soyadi,sampiyon.skor);
			asd2++;
		}
	}
	if(asd2>0){
		xyz++;
		printf("__________________\n");
	}
		
	rewind( fPtr );
	for(say=0;say<sori;say++){
		fread(&sampiyon,sizeof(struct oyuncu),1,fPtr);
		if(sampiyon.skor==3){
			printf("%s	%d\n",sampiyon.oyuncu_adi_soyadi,sampiyon.skor);
			asd3++;
		}
	}
	if(asd3>0){
		xyz++;
		printf("__________________\n");
	}
		
	if(xyz<=3){
		rewind( fPtr );
		for(say=0;say<sori;say++){
			fread(&sampiyon,sizeof(struct oyuncu),1,fPtr);
			if(sampiyon.skor==2){
				printf("%s	%d\n",sampiyon.oyuncu_adi_soyadi,sampiyon.skor);
				asd4++;
			}
		}	
		if(asd4>0){
			xyz++;
			printf("__________________\n");
		}
	}
	if(xyz<=3){
		rewind( fPtr );
		for(say=0;say<sori;say++){
			fread(&sampiyon,sizeof(struct oyuncu),1,fPtr);
			if(sampiyon.skor==1){
				printf("%s	%d\n",sampiyon.oyuncu_adi_soyadi,sampiyon.skor);
				asd5++;
			}
		}
		if(asd5>0){
			xyz++;
			printf("__________________\n");
		}
	}
	if(xyz<=3){
		rewind( fPtr );
		for(say=0;say<sori;say++){
			fread(&sampiyon,sizeof(struct oyuncu),1,fPtr);
			if(sampiyon.skor==0){
				printf("%s	%d\n",sampiyon.oyuncu_adi_soyadi,sampiyon.skor);
				asd6++;
			}
		}
		if(asd6>0){
			printf("__________________\n");
		}
	}
	fclose(fPtr);
}
