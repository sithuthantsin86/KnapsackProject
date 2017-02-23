#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
extern int count_add, count_merge;
using namespace std;
struct Array{
	int p, rc, prev;
};
class New_algo{
	Array *carrier, *temp;
	long int N, C;
    int *place, carrier_size, *p, *w;
	public:
	void read(char *file_name);
	int add(int ref, int psz, int p, int w);
	int merge(int ref, int psz, int temp_size);
	void merge();
	int solve();
	void print(int size);
};
void New_algo::read(char *file_name){
	ifstream g;
	int a, b, i=0;
	g.open(file_name);
	if(!g){
      		std::cerr << "Error: file could not be opened for <g>." << std::endl;
      		exit(1);
       	}
	g >> N;
	g >> C;
	p = (int *)malloc(N*sizeof(int));
	if(p == NULL){std::cerr<<"Error : Your size is too much for <place>.\n";exit(1);}
	w = (int *)malloc(N*sizeof(int));
	if(w == NULL){std::cerr<<"Error : Your size is too much for <place>.\n";exit(1);}
	while(!g.eof()){
		g >> a;
		p[i] = a;
		g >> b;
		w[i] = b;
		i++;
	}
}
int New_algo::add(int ref, int psz, int p, int w){
	int count = 0;
	//printf("add: ref = %d, psz = %d\n", ref, psz);
	for(int i=ref; i<ref+psz; i++){
		if(carrier[i].rc - w >= 0){
			temp[count].p = carrier[i].p + p;
			temp[count].rc = carrier[i].rc - w;
			temp[count].prev = i;
			count++;
			count_add++;
		}
	}
	return count;
}
int New_algo::merge(int ref, int psz, int temp_size){
	int nsz = 0, end, count_temp = 0, count_carrier = 0;
	count_carrier = end = ref + psz;
	while(ref < end || count_temp < temp_size){
		//For the condition that decision for carrier array is done. But some pairs remain in temp array.
		if(ref >= end  && count_temp < temp_size){
			carrier[count_carrier].p = temp[count_temp].p;
			carrier[count_carrier].rc = temp[count_temp].rc;
			carrier[count_carrier].prev = temp[count_temp].prev;
			count_temp++;
			count_carrier++;
			count_merge++;
			nsz++;
		}
		//For the condition that decision for temp array is done. But some pairs reamin in carrier array.
		else if(count_temp >= temp_size && ref < end){
			carrier[count_carrier].p = carrier[ref].p;
			carrier[count_carrier].rc = carrier[ref].rc;
			carrier[count_carrier].prev = ref;
			ref++;
			count_carrier++;
			count_merge++;
			nsz++;
		}
		else if(carrier[ref].p <= temp[count_temp].p){
			if(carrier[ref].rc > temp[count_temp].rc){
				carrier[count_carrier].p = carrier[ref].p;
				carrier[count_carrier].rc = carrier[ref].rc;
				carrier[count_carrier].prev = ref;
				count_carrier++;
				count_merge++;
				nsz++;
			}
			ref++;
		}
		else{
			if(carrier[ref].rc < temp[count_temp].rc){
				carrier[count_carrier].p = temp[count_temp].p;
				carrier[count_carrier].rc = temp[count_temp].rc;
				carrier[count_carrier].prev = temp[count_temp].prev;
				count_carrier++;
				count_merge++;
				nsz++;
			}
			count_temp++;
		}
	}	
	return nsz;
}	
int New_algo::solve(){
	int count_temp, count_carrier, dis_nxt, temp_size = 0, i, j, ref, psz, nsz=0;
	carrier = (Array *)malloc((N*C)*sizeof(Array));
    	if(carrier == NULL){std::cerr<<"Error : Your size is too much for <carrier>.\n";cout<<"\nCrushed size = "<<N*C<<endl;exit(1);}
	temp = (Array *)malloc((N*C)*sizeof(Array));
    	if(temp == NULL){std::cerr<<"Error : Your size is too much for <temp>.\n";exit(1);}
	place=(int *)malloc(N*sizeof(int));
	if(place == NULL){std::cerr<<"Error : Your size is too much for <place>.\n";exit(1);}
	carrier[0].p=0;
	carrier[0].rc = C;
	carrier[0].prev=0;
	ref = 0;
	psz = 1;
	for(i=0; i<N; i++){
		temp_size = add(ref, psz, p[i], w[i]);
		/*cout<<"\nAdded condition for ("<<i<<"th) step.\n";
		for(int j=0; j<ref + psz; j++){
			cout<<"["<<carrier[j].p<<","<<carrier[j].rc<<","<<carrier[j].prev<<"] ";
		}
		cout<<endl;
		for(int k=0; k<temp_size; k++){
			cout<<"["<<temp[k].p<<","<<temp[k].rc<<","<<temp[k].prev<<"] ";
		}
		getchar();*/
		nsz = merge(ref, psz, temp_size);
		ref += psz;
		psz = nsz;
		/*cout<<"\nMerged condition for ("<<i<<"th) step.\n";
		for(int j=0; j< ref + psz; j++){
			cout<<"["<<carrier[j].p<<","<<carrier[j].rc<<","<<carrier[j].prev<<"] ";
		}
		cout<<endl;
		for(int k=0; k<temp_size; k++){
			cout<<"["<<temp[k].p<<","<<temp[k].rc<<","<<temp[k].prev<<"] ";
		}
		cout<<"\nNSZ = "<<nsz;
		cout<<"\nref = "<<ref;
		getchar();*/
	}
	return ref+nsz;		
}
void New_algo::print(int size){
	int j=0;
	//cout<<"Maximum Profit = "<<carrier[size-1].p<<"\t"<<endl;
	//cout<<"Array size = "<<N*C<<"\n";
	/*for(int i=0; i<size; i++){
		if(i==place[j]){
			cout<<endl;
			j++;
		}
		cout<<"["<<carrier[i].p<<","<<carrier[i].rc<<","<<carrier[i].prev<<"] ";
	}
	cout<<endl;*/
}
int main(int argc, char* argv[]){
	time_t start, end;
	New_algo NA;
	int size;
	char* str = NULL;
    	if(argc >= 2){
      		str = argv[1];
   	}
    	else{
      		fprintf(stderr, "usage: %s <input_file>\n", argv[0]);
    		exit(-1);
    	}
	NA.read(str);
	start = clock();
	size =  NA.solve();
	end = clock();
	float diff((float)end-(float)start);
	float seconds = diff/CLOCKS_PER_SEC;
	cout<</*"Runtime = "<<*/(float)seconds<<"\t"/*<<endl*/;
	cout<</*"Added steps = "<<*/count_add<<"\t"/*<<endl*/;
	cout<</*"Merged steps = "<<*/count_merge<<"\t"/*<<endl*/;
	NA.print(size);
	return 0;
}
