#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>


using namespace std;

//global variable
fstream x; 

void LPSArray(string pat, int *lps)
{
    int len = 0;
 
    lps[0] = 0; 
 
    int i = 1;
    int M = pat.size();
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0)
            {
                len = lps[len-1];
            }
            else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}
 

int KMPSearch(string pat, string txt)
{
    int count = 0;
	int M = pat.size();
    int N = txt.size();
 
    int lps[M];
 
    LPSArray(pat, lps);
 
    int i = 0;  
    int j  = 0;  
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
 
        if (j == M)
        {
            //to check it is not a subword
			if((txt[i-j-1] == ' '  || txt[i-j-1] == '\"' || txt[i-j-1] == '\'' ||i-j == 0) && (txt[i-j+M] == ' ' || txt[i-j+M] == '.' || txt[i-j+M] == '!' || txt[i-j+M] == '?' || txt[i-j+M] == ',' || txt[i-j+M] == ';')){
            	count++;
			}
				
			j = lps[j-1];
        }
 
        else if (i < N && pat[j] != txt[i])
        {

            if (j != 0)
                j = lps[j-1];
            else
                i = i+1;
        }
    }
    return count;
}

void openFile(int page){
	string filename = "page_1.txt";
	if(page<=9){
		filename[5] = page + 48;
	}
	else { 
		filename[5]=  (page/10) + 48;
	    filename[6]=  (page%10) + 48;
		filename[7]='.';
		filename[8]='t';
		filename[9]='x';
		filename[10]='t';
	}
	//cout<<filename;
	x.open(filename.c_str());
}

 
 int main(){
     
	fstream queryfile;
	vector<string> querylist;
	string queryword;
	queryfile.open("queries.txt",ios::in);
	
	//getting the list of query words
	
	while(!queryfile.eof()){
	    
	    queryfile >> queryword; 
	    querylist.push_back(queryword);
	}
	queryfile.close();
	
	//opening the chapter files
		
	string fileline;
	int line = 0;
		
						
		for(int i=0;i<querylist.size();i++){
			char Continue;
			cout<<"Word:\t"<<querylist[i]<<endl;
			cout<<"Occurences:\n";
			cout<<"-----------------------------------------------------------------------------------------------\n";
			for (int a = 1; a <= 1 ; a++){
				openFile(a);
				
				while(getline(x,fileline)){
					getline(x,fileline);
					line ++;
					//cout<<fileline<<endl;
					int result = KMPSearch(querylist[i], fileline);
					if(result > 0){
						for(int j=1;j<=result;j++){
							cout<<"Page: "<<a<<"\tLine: "<<line<<endl;
						}
					}
				}
				
				x.close();
			}
			cout<<"PRESS ANY KEY TO GET THE NEXT QUERY";
			Continue = getchar();
		}
		

	return 0;
}

