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
struct Pairs{
	int p, w, k;
	float div;
};
class New_algo{
	Array *carrier, *temp;
	Pairs *input;
	long int N, C;
    	int *place, carrier_size, ubm;
	public:
	New_algo(int ubv){ubm = ubv;}
	void read(char *file_name);
	int add(int ref, int psz, int p, int w);
	int merge(int ref, int psz, int temp_size, int k);
	int upper_bound_1(int p, int rc, int k);
	int upper_bound_2(int p, int rc, int k);
	int upper_bound(int p, int rc, int k);
	int solve();
	void print(int size);
};
int New_algo::upper_bound_1(int p, int rc, int k){
	return p+(((double)input[k+1].p/(double)input[k+1].w)*(double)rc);
}
int New_algo::upper_bound_2(int p, int rc, int k){
	double bound=0;
	while(rc >= input[k+1].w && k < N){
		bound = bound + input[k+1].p;
		rc = rc - input[k+1].w;
		k++;
	}
	bound +=  (((double)rc/(double)input[k+1].w)*(double)input[k+1].p);
	bound += p;
	return bound;
}

int New_algo::upper_bound(int p, int rc, int k){
        double ub;
        if(ubm == 1) 
          ub = upper_bound_1(p, rc, k);
        else if(ubm == 2)
          ub = upper_bound_2(p, rc, k);
        else {
          printf("No bounding method set!\n");
          exit(-1);
        }
	return ub;
}
static int compare(const void *a, const void *b){
	const Pairs* ia = (struct Pairs *)a;
	const Pairs* ib = (struct Pairs *)b;
        if(ia->div > ib-> div)
          return -1;
        else if(ia->div == ib->div)
          return 0;
        else
          return 1;
}
void New_algo::read(char *file_name){
	ifstream g;
	int a, b, i=0;
	g.open(file_name);
	if(!g.is_open()){
      		std::cerr << "Error: file could not be opened for <g>." << std::endl;
      		exit(1);
       	}
	g >> N;
	g >> C;
	input = (Pairs *)malloc(N*sizeof(Pairs));
	if(input == NULL){std::cerr<<"Error : Your size is too much for <input>.\n";exit(1);}
	for(i = 0; i < N; i ++){
		g >> a;
		input[i].p = a;
		g >> b;
		input[i].w = b;
		input[i].k = i;
		input[i].div = ((float)a)/((float)b);
	}
        g.close();
	qsort(input, N, sizeof(Pairs), compare);
}
int New_algo::add(int ref, int psz, int p, int w){
	int count = 0;
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

int New_algo::merge(int ref, int psz, int temp_size, int k){
	int nsz = 0, end, max = 0, count_carrier = 0, count_temp = 0, me=0;
	count_carrier = end = ref + psz;
        //printf("IN MERGE\n"); fflush(stdout);
	for(int z=0; z<temp_size; z++)if(temp[z].p>max)max=temp[z].p;
        //printf("BEFORE WHILE\n"); fflush(stdout);
    	while(ref < end || count_temp < temp_size){
                //printf("ref = %d, end = %d, count_temp = %d, temp_size = %d\n", ref, end, count_temp, temp_size); fflush(stdout);
		if(ref >= end  && count_temp < temp_size){
			if( k < N-1 && upper_bound(temp[count_temp].p, temp[count_temp].rc, k) > max || max == temp[count_temp].p/*&& temp[count_temp].p >= max*/){
				carrier[count_carrier].p = temp[count_temp].p;
				carrier[count_carrier].rc = temp[count_temp].rc;
				carrier[count_carrier].prev = temp[count_temp].prev;
				count_carrier++;
				count_merge++;
				nsz++;
			}
			count_temp++;
		}
		else if(count_temp >= temp_size && ref < end){
			if( k < N-1 && upper_bound(carrier[ref].p, carrier[ref].rc, k) > max || max == carrier[ref].p/*&& carrier[ref].p >= max*/){
				carrier[count_carrier].p = carrier[ref].p;
				carrier[count_carrier].rc = carrier[ref].rc;
				carrier[count_carrier].prev = ref;
				count_carrier++;
				count_merge++;
				nsz++;
			}
			ref++;
		}
		else if(carrier[ref].p <= temp[count_temp].p){
			if(carrier[ref].rc > temp[count_temp].rc){
				if( k < N-1 && upper_bound(carrier[ref].p, carrier[ref].rc, k) > max || max == carrier[ref].p/*&& carrier[ref].p >= max*/){
					carrier[count_carrier].p = carrier[ref].p;
					carrier[count_carrier].rc = carrier[ref].rc;
					carrier[count_carrier].prev = ref;
					count_carrier++;
					count_merge++;
					nsz++;
				}
			}
			ref++;
		}
		else{
			if(carrier[ref].rc < temp[count_temp].rc){
				if( k < N-1 && upper_bound(temp[count_temp].p, temp[count_temp].rc, k) > max || max == temp[count_temp].p/*&& temp[count_temp].p >= max*/){
					carrier[count_carrier].p = temp[count_temp].p;
					carrier[count_carrier].rc = temp[count_temp].rc;
					carrier[count_carrier].prev = temp[count_temp].prev;
					count_carrier++;
					count_merge++;
					nsz++;
				}
			}
			count_temp++;
		}	
	}
        //printf("OUT MERGE\n"); fflush(stdout);
	return nsz;
}	
int New_algo::solve(){
	int count_temp, count_carrier, dis_nxt, temp_size = 0, i, j, ref, psz, nsz=0;
	carrier = (Array *)malloc((N*C)*sizeof(Array));
        if(carrier == NULL){std::cerr<<"Error : Your size is too much for <carrier>.\n";cout<<"\nCrushed size = "<<N*C<<endl;exit(1);}
	temp = (Array *)malloc((N*C)*sizeof(Array));
        if(temp == NULL){std::cerr<<"Error : Your size is too much for <temp>.\n";cout<<"\nCrushed size = "<<N*C<<endl;exit(1);}
	place=(int *)malloc(N*sizeof(int));
	if(place == NULL){std::cerr<<"Error : Your size is too much for <place>.\n";exit(1);}
	carrier[0].p=0;
	carrier[0].rc = C;
	carrier[0].prev=0;
	ref = 0;
	psz = 1;
	for(i=0; i<N; i++){
		//cout<<"\n##### Workng with "<<i<<"th object. #####\n";
		temp_size = add(ref, psz, input[i].p, input[i].w);
		/*cout<<"\n-Added condition for ("<<i<<"th) step.-\n\n";
		for(int j=0; j<ref + psz; j++){
			cout<<"["<<carrier[j].p<<","<<carrier[j].rc<<","<<carrier[j].prev<<"] ";
		}
		cout<<endl;
		for(int k=0; k<temp_size; k++){
			cout<<"["<<temp[k].p<<","<<temp[k].rc<<","<<temp[k].prev<<"] ";
		}
		getchar();*/
		if(temp_size > 0){
			nsz = merge(ref, psz, temp_size, i);
			ref += psz;
			psz = nsz;
		}
		/*cout<<"\n-Merged condition for ("<<i<<"th) step.-\n\n";
		for(int j=0; j< ref + psz; j++){
			cout<<"["<<carrier[j].p<<","<<carrier[j].rc<<","<<carrier[j].prev<<"] ";
		}
		cout<<"\n\n----------------------------------------------------------------------------------------------------------";
		getchar();*/
	}
	return ref+nsz;		
}
void New_algo::print(int size){
	int j=0;
	cout<</*"Maximum Profit = "<<*/carrier[size-1].p;
	cout<<"\t"<<C<<endl;
	//cout<<"Array size = "<<N*C<<"\n";
	/*for(int i=0; i<size; i++){
		if(i==place[j]){
			cout<<endl;
			j++;
		}
		cout<<"["<<carrier[i].p<<","<<carrier[i].rc<<","<<carrier[i].prev<<"] ";
	}*/
	//cout<<endl;
}
int main(int argc, char* argv[]){
	time_t start, end;
	int size, ubm;
	char* str = NULL;
    	if(argc >= 3){
		str = argv[1];
		if(argc == 3){
			ubm = atoi(argv[2]);
		}
   	}
    	else{
    		fprintf(stderr, "usage: %s <input_file> <method>\nIf upper bound, method = 1\nIf linear relaxation, method = 2\n", argv[0]);
    		exit(-1);
   	}
	New_algo NA(ubm);
	NA.read(str);
	start = clock();
	size =  NA.solve();
	end = clock();
	float diff((float)end-(float)start);
	float seconds = diff/CLOCKS_PER_SEC;
	cout<<fixed/*<<"Runtime = "*/<<seconds<<"\t";
	cout<<count_add<<"\t"<<count_merge<<"\t";
	if(ubm==2)NA.print(size);
	return 0;
}
