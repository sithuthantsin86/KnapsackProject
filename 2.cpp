#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<sstream>
#include<sys/stat.h>
using namespace std;
void printPair(FILE* f, int *p, int *w, int N, int C)
{
	fprintf(f, "%d\t%d\n", N, C);
	for(int i=0;i<N;i++)
		fprintf(f,"%d\t%d\n", p[i], w[i]);
}
string file_name(string method, int N, int R, int C, int num_instance)
{
	ostringstream os;
	os<<method<<"/";
	os <<method<<"_"<<N<<"_"<<R<<"_"/*<<C<<"_"*/;
	if(num_instance<10)os <<"0"<<"0"<<num_instance;
	if(num_instance>=10 && num_instance<100)os <<"0"<<num_instance;
	if(num_instance>=100)os<<num_instance;
	os <<"_"<<C;
	return os.str();
}
void generator(string method, int number_of_items, int R, /*int capacity,*/ int num_instances)
{
	int capacity = 0, C=0, i_alpha = 0;
	time_t t;
	struct stat st;
	srand (time(&t));
	FILE *a, *b, *c, *d, *e, *f, *g;
	int *p, *w;
	float alpha[]={0.1, 0.25, 0.5, 0.75, 0.9};
	int min=0, sum=0;
	int sec = num_instances/5;
	//cout<<"\nSize = "<<sizeof(alpha)<<endl;
	cout<<"\nAlpha = "<<sec<<endl;
	p=(int *)malloc(number_of_items*sizeof(int));
	if(p == NULL){cerr<<"Error : Your size is too much.\n";exit(1);}
	w=(int *)malloc(number_of_items*sizeof(int));
    	if(w == NULL){cerr<<"Error : Your size is too much.\n";exit(1);}
	if(method == "UC" || method == "ALL"){
		if(stat("UC", &st) == 0)system("rm -r UC");
	}
	if(method == "WC" || method == "ALL"){
                if(stat("WC", &st) == 0)system("rm -r WC");
        }
	if(method == "SC" || method == "ALL"){
                if(stat("SC", &st) == 0)system("rm -r SC");
        }
	if(method == "ISC" || method == "ALL"){
                if(stat("ISC", &st) == 0)system("rm -r ISC");
        }
	for(int j=0;j<num_instances;j++){
		if(j > 0 && j%sec ==  0)i_alpha++;
		if(method == "UC" || method == "ALL"){
			string M="UC";
			//if(stat("UC", &st) == 0)system("rm -r UC");
			mkdir("UC", 0777);
			//a=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			p[0]=rand()%R+1;
			w[0]=rand()%R+1;
			sum=sum+w[0];
			min=w[0];
			for(int i=1;i<number_of_items;i++){
				p[i]=rand()%R+1;
				w[i]=rand()%R+1;
				sum=sum+w[i];
				if(min>w[i])min=w[i];
			}
			//p = num_instances/sizeof(alpha);
			//if(j > 0 && j%p == 0)i_alpha++;
			C = alpha[i_alpha]*sum;
			if(C >= min)capacity = C;
			else{
				capacity = min;
			}
			a=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			printPair(a, p, w, number_of_items, capacity);
			fclose(a);
		}
		sum = 0;
		min = 0;
		if(method == "WC" || method == "ALL"){
			string M="WC";
			int num;
			mkdir("WC", 0777);
			num = rand()%R;
			w[0] = num + 1;
			p[0] = num - (R/10)+(rand()%(R/5));
			sum = sum+w[0];
			min = w[0];
			//b=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=1;i<number_of_items;i++){
				num=rand()%R;
				w[i]=num+1;
				p[i]=num-(R/10)+(rand()%(R/5));
				sum=sum+w[i];
				if(min>w[i])min=w[i];
			}
			C = alpha[i_alpha]*sum;
			if(C >= min)capacity = C;
			else{
				capacity = min;
			}
			b=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			printPair(b, p, w, number_of_items, capacity);
			fclose(b);
		}
		sum = 0;
		min = 0;
		if(method == "SC" || method == "ALL"){
			string M="SC";
			mkdir("SC", 0777);
			w[0] = rand()%R+1;
			p[0] = w[0]+(R/10);
			sum = sum+w[0];
			min = w[0];
			//c=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=1;i<number_of_items;i++){
				w[i]=rand()%R+1;
				p[i]=w[i]+(R/10);
				sum=sum+w[i];
				if(min>w[i])min=w[i];
			}
			C = alpha[i_alpha]*sum;
			if(C >= min)capacity = C;
			else{
				capacity = min;
			}
			c=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			printPair(c, p, w, number_of_items, capacity);
			fclose(c);
		}
		sum = 0;
		min = 0;
		if(method == "ISC" || method == "ALL"){
			string M="ISC";
			mkdir("ISC", 0777);
			p[0] = rand()%R+1;
			w[0] = p[0]+(R/10);
			sum = sum+w[0];
			min = w[0];
			//d=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=1;i<number_of_items;i++){
				p[i]=rand()%R+1;
				w[i]=p[i]+(R/10);
				sum=sum+w[i];
				if(min>w[i])min=w[i];
			}
			C = alpha[i_alpha]*sum;
			if(C >= min)capacity = C;
			else{
				capacity = min;
			}
			d=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			printPair(d, p, w, number_of_items, capacity);
			fclose(d);
		}
		sum = 0;
		min = 0;
		if(method == "ASC" || method == "ALL"){
			string M="ASC";
        	int num;
			mkdir("ASC", 0777);
			num=rand()%R;
			p[0]=(num+(R/10)-(R/500))+(rand()%(R/250));
			w[0]=num+1;
			sum = sum+w[0];
			min = w[0];
        	//e=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=1;i<number_of_items;i++){
            	num=rand()%R;
				p[i]=(num+(R/10)-(R/500))+(rand()%(R/250));
				w[i]=num+1;
				sum = sum+w[i];
				if(min>w[i])min=w[i];
       	 	}
       	 	C = alpha[i_alpha]*sum;
       	 	if(C >= min)capacity = C;
       	 	else{
       	 		capacity = min;
       	 	}
       	 	e=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			printPair(e, p, w, number_of_items, capacity);
        	fclose(e);
    	}
    	sum = 0;
		min = 0;
		if(method == "SS" || method == "ALL"){
			string M="SS";
			mkdir("SS", 0777);
			p[0]=w[0]=rand()%R+1;
			sum = sum+w[0];
			min = w[0];
        	//f=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=1;i<number_of_items;i++){
				p[i]=w[i]=rand()%R+1;
				sum = sum+w[i];
				if(min>w[i])min=w[i];
			}
			C = alpha[i_alpha]*sum;
       	 	if(C >= min)capacity = C;
       	 	else{
       	 		capacity = min;
       	 	}
       	 	f=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
            printPair(f, p, w, number_of_items, capacity);
			fclose(f);
        }
        sum = 0;
		min = 0;
		if(method == "UCS" || method == "ALL"){
			string M="UCS";
			mkdir("UCS", 0777);
			p[0]=rand()%1000+1;
			w[0]=rand()%100+100000;
			sum = sum+w[0];
			min = w[0];
        	//g=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
        	for(int i=1;i<number_of_items;i++){
            	p[i]=rand()%1000+1;
				w[i]=rand()%100+100000;
				sum = sum+w[i];
				if(min>w[i])min=w[i];
        	}
        	C = alpha[i_alpha]*sum;
       	 	if(C >= min)capacity = C;
       	 	else{
       	 		capacity = min;
       	 	}
       	 	g=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			printPair(g, p, w, number_of_items, capacity);
        	fclose(g);
    	}
    	sum = 0;
		min = 0;
	}
}
int main(int argc, char* argv[])
{
	string method;
	int num_instances;
	int number_of_items, R/*, capacity*/;
	if(argc >= 2){
		method = argv[1];
		if(argc == 5){
			number_of_items = atoi(argv[2]);
			R = atoi(argv[3]);
			//capacity = atoi(argv[4]);
			num_instances = atoi(argv[4]);
		}
	}
	else{
		fprintf(stderr,"Usage: %s <method> <number of items> <range> <How many instances>\n", argv[0]);
		exit(-1);
	}
	generator(method, number_of_items, R, /*capacity,*/ num_instances);
	return 0;
}
