#include <bits/stdc++.h>

using namespace std;

ifstream fin("java2016.in");
ofstream fout("java2016.out");

int main() {
  
        int c;
        
        fin >> c;
        
        if(!c){
            fout << "? / ? / ?" << endl;
           return 0; 
        }
        
        
        fout << "a = ? max ?" << endl;
        
        int i;
        for(i = 1; i < 11; i++){
            fout << (char)('a'+i) << " = " << (char)('a'+(i-1)) << " max " << (char)('a'+(i-1)) << endl;
        }
        fout << (char)('a'+i) << " = (" <<  (char)('a'+(i-1)) << " max " << (char)('a'+(i-1)) << ") / " << (char)('a'+(i-1)) << endl;
        i++;
        
        int s = i-1;
        int e = i+7;
        
        for(; i < e; i++){
             fout << (char)('a'+i) << " = " << (char)('a'+(i-1)) << " + " << (char)('a'+(i-1)) << endl;
        }
        
        vector<int> bt(8, 0);
        
        int cnt = 0;
        for(int j = 0; j < 8; j++){
            if(c & (1 << j)){
                if(cnt++ > 0) fout << " + ";
                fout << (char)('a'+(s+j));
            }
        }
        fout << endl;
        
	return 0;
}
