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
	os <<method<<"_"<<N<<"_"<<R<<"_"<<C<<"_";
	if(num_instance<10)os <<"0"<<"0"<<num_instance;
	if(num_instance>=10 && num_instance<100)os <<"0"<<num_instance;
	if(num_instance>=100)os<<num_instance;
	return os.str();
}
void generator(string method, int number_of_items, int R, int capacity, int num_instances)
{
	time_t t;
	struct stat st;
	srand (time(&t));
	FILE *a, *b, *c, *d, *e, *f, *g;
	int *p, *w;
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
		if(method == "UC" || method == "ALL"){
			string M="UC";
			//if(stat("UC", &st) == 0)system("rm -r UC");
			mkdir("UC", 0777);
			a=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=0;i<number_of_items;i++){
				p[i]=rand()%R+1;
				w[i]=rand()%R+1;
			}
			printPair(a, p, w, number_of_items, capacity);
			fclose(a);
		}
		if(method == "WC" || method == "ALL"){
			string M="WC";
			int num;
			mkdir("WC", 0777);
			b=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=0;i<number_of_items;i++){
				num=rand()%R;
				w[i]=num+1;
				p[i]=num-(R/10)+(rand()%(R/5));
			}
			printPair(b, p, w, number_of_items, capacity);
			fclose(b);
		}
		if(method == "SC" || method == "ALL"){
			string M="SC";
			mkdir("SC", 0777);
			c=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=0;i<number_of_items;i++){
				w[i]=rand()%R+1;
				p[i]=w[i]+(R/10);
			}
			printPair(c, p, w, number_of_items, capacity);
			fclose(c);
		}
		if(method == "ISC" || method == "ALL"){
			string M="ISC";
			mkdir("ISC", 0777);
			d=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=0;i<number_of_items;i++){
				p[i]=rand()%R+1;
				w[i]=p[i]+(R/10);
			}
			printPair(d, p, w, number_of_items, capacity);
			fclose(d);
		}
		if(method == "ASC" || method == "ALL"){
			string M="ASC";
        		int num;
			mkdir("ASC", 0777);
        		e=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=0;i<number_of_items;i++){
            			num=rand()%R;
				p[i]=(num+(R/10)-(R/500))+(rand()%(R/250));
				w[i]=num+1;
       	 		}
			printPair(e, p, w, number_of_items, capacity);
        		fclose(e);
    		}
		if(method == "SS" || method == "ALL"){
			string M="SS";
			mkdir("SS", 0777);
        		f=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
			for(int i=0;i<number_of_items;i++)
				p[i]=w[i]=rand()%R+1;
            		printPair(f, p, w, number_of_items, capacity);
			fclose(f);
        	}
		if(method == "UCS" || method == "ALL"){
			string M="UCS";
			mkdir("UCS", 0777);
        		g=fopen(file_name(M, number_of_items, R, capacity, j+1).c_str(), "w");
        		for(int i=0;i<number_of_items;i++){
            			p[i]=rand()%1000+1;
				w[i]=rand()%100+100000;
        		}	
			printPair(g, p, w, number_of_items, capacity);
        		fclose(g);
    		}
	}
}
int main(int argc, char* argv[])
{
	string method;
	int num_instances;
	int number_of_items, R, capacity;
	if(argc >= 2){
		method = argv[1];
		if(argc == 6){
			number_of_items = atoi(argv[2]);
			R = atoi(argv[3]);
			capacity = atoi(argv[4]);
			num_instances = atoi(argv[5]);
		}
	}
	else{
		fprintf(stderr,"Usage: %s <method> <number of items> <range> <capacity> <How many instances>\n", argv[0]);
		exit(-1);
	}
	generator(method, number_of_items, R, capacity, num_instances);
	return 0;
}
