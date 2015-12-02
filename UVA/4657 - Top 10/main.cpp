#include <bits/stdc++.h>
#include <iostream>

using namespace std;

typedef pair<int,int> ii;

vector<string> d;

template<typename T>
class RMQ {

	public:
		RMQ() {}
		
		void buildRMQ(vector<T> b) {
		  a = b;
		  int n = a.size();
		  int k = floor(log(n)/log(2));
		  layer_idx.push_back(0);
		  rmq.push_back(vector<int>());
		  for(int i = 0; i < n; i++)
			rmq[0].push_back(i);

			for(int i = 1; i <= k; i++) {
				int s = pow(2,i); int m = (s-1)/2;
				layer_idx.push_back(rmq.size());
				for(int j = 0; j < s; j++) {
					rmq.push_back(vector<int>());
					for(int l = j; l+s-1 < n; l += s)
						rmq[layer_idx[i]+j].push_back((a[access(l,l+m)] < a[access(l+m+1,l+s-1)] ? access(l,l+m) : access(l+m+1,l+s-1)));		
				}
			}
		}

		int query(int i, int j) {
			int s = pow(2,floor(log(j-i+1)/log(2)));
			return (a[access(i,i+s-1)] < a[access(j-(s-1),j)] ? access(i,i+s-1) : access(j-(s-1),j));
		}

	private:
		int access(int i, int j) {
			//j-i+1 = 2^n n € N
			int k = j-i+1, layer = floor(log(k)/log(2)), off = i % max(k,1), idx = (i - off)/k;
			return rmq[layer_idx[layer]+off][idx];
		}


		vector<vector<int>> rmq;
		vector<int> layer_idx;
		vector<T> a;

};


class SuffixArray {

public:
  #define MAXN 121000
  typedef pair<int,int> rank;
  
  SuffixArray(string& s, vector<int>& doc_id, int d) : n(s.size()+1), d(d), s(s), sa(s.size()+1) {
    s.push_back('$');
    doc_id.push_back(doc_id[doc_id.size()-1]+1);
    memset(ra,0,sizeof(ra)); memset(temp_ra,0,sizeof(temp_ra)); memset(isa,0,sizeof(isa));
    for(int i = 0; i < sa.size(); i++)	{ sa[i] = make_pair(i,doc_id[i]); isa[i] = i; }
    constructSA();
    constructRMQOverDocumentPointerArray();
  }
  
  //Returns range of suffixes, which prefixes match with pattern p (|p| = m). Time Complexity O(m*log(n))
  ii findPattern(string& p) {
    int m = p.size();
    int l = 0, r = n-1;
    //Search lower bound of range
    while(l < r) {
	int mid = (l+r)/2;
	if(strncmp(s.c_str() + sa[mid].first,p.c_str(),m) >= 0) r = mid;
	else l = mid+1;
    }
    if(strncmp(s.c_str() + sa[l].first,p.c_str(),m) != 0) return ii(-1,-1);
    ii res; res.first = l;
    l = 0; r = n-1;
    //Search upper bound of range
    while(l < r) {
	int mid = (l+r)/2;
	if(strncmp(s.c_str() + sa[mid].first,p.c_str(),m) > 0) r = mid;
	else l = mid+1;
    }
    if(strncmp(s.c_str() + sa[r].first,p.c_str(),m) != 0) r--;
    res.second = r;
    return res;
  }
  
  vector<int> topDocuments(string& p) {
      vector<int> topK;
      ii q = findPattern(p);
      if(q.first == -1)
	return topK;  
      getAllDocumentsInRange(topK,q.first,q.second,q.first);
      return topK;
  }
  
private:
  
  //Construct a Suffix Array for a string s (Based on Ranking-Pairs). Time complexity O(n*log^2(n))
  void constructSA() {
    vector<rank> ra_p(n);
    //Initiliaze ra with ascii values of chars in s
    for(int i = 0; i < n; i++)	ra[i] = s[i];
    for(int k = 1; k < n; k <<= 1) {
      for(int j = 0; j < n; j++) { 
	ra_p[j] = make_pair(ra[sa[j].first],(sa[j].first + k < n ? ra[sa[j].first + k] : 0)); 
	isa[sa[j].first] = j;
      }
      //If we want to construct Suffix-Array in O(n*log(n)) we have to replace this naive sorting
      //stradegy with Counting-Sort
      sort(sa.begin(),sa.end(),[&](const rank& i, const rank& j) {
	return (ra_p[isa[i.first]] < ra_p[isa[j.first]]) || (ra_p[isa[i.first]] == ra_p[isa[j.first]] && isa[i.first] < isa[j.first]);
      });
      //Re-rank after sorting
      temp_ra[sa[0].first] = 0; int r = 0;
      for(int j = 1; j < n; j++)
	temp_ra[sa[j].first] = (ra[sa[j].first] == ra[sa[j-1].first] && ra[sa[j].first + (sa[j].first + k < n ? k : 0)] == ra[sa[j-1].first + (sa[j-1].first + k < n ? k : 0)]) ?
			 r : ++r;
      for(int j = 0; j < n; j++) ra[j] = temp_ra[j];
      if(ra[sa[n-1].first] == n-1) break;
    }
  }
  
  void constructRMQOverDocumentPointerArray() {
    vector<int> last_occ(d+1,-1);
    doc_p.assign(n,-1);
    for(int i = 0; i < n; i++) {
	int doc_id = sa[i].second;
	doc_p[i] = last_occ[doc_id];
	last_occ[doc_id] = i;
    }
    rmq.buildRMQ(doc_p);
  }
  
  void getAllDocumentsInRange(vector<int>& id, int i, int j, int l) {
    if(j >= i) {
      int idx = rmq.query(i,j);
      if(doc_p[idx] < l) {
	id.push_back(sa[idx].second);
	getAllDocumentsInRange(id,i,idx-1,l);
	getAllDocumentsInRange(id,idx+1,j,l);
      }
    }
  }
  
  int n, d;
  string s;
  RMQ<int> rmq;
  vector<rank> sa;
  vector<int> doc_p;
  int ra[MAXN], temp_ra[MAXN], isa[MAXN];
};

int main() {
  int n; cin >> n;
  d.resize(n);
  for(int i = 0; i < n; i++)
    cin >> d[i];
  
  vector<int> doc_id;
  string con_dic;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < d[i].size(); j++) {
      con_dic.push_back(d[i][j]);
      doc_id.push_back(i+1);
    }
    if(i != n-1) {
      con_dic.push_back('&');
      doc_id.push_back(i+1);
    }
  }
  
  SuffixArray sa(con_dic, doc_id, n+1);
  int q; cin >> q;
  for(int i = 0; i < q; i++) {
     string p; cin >> p;
     vector<int> topK = sa.topDocuments(p);

     sort(topK.begin(), topK.end(), [&](const int i1, const int i2) {
      int l1 = i1-1; int l2 = i2-1;
      return (d[l1].size() < d[l2].size()) || (d[l1].size() == d[l2].size() && d[l1].compare(d[l2]) < 0)
		|| (d[l1].size() == d[l2].size() && d[l1].compare(d[l2]) == 0 && l1 < l2);
     });
     
     if(topK.size() == 0) { cout << "-1" << endl; continue; }
     
     for(int j = 0; j < min(10,((int)topK.size())); j++) {
	cout << topK[j] << (j < min(10,((int)topK.size()))-1 ? " " : "");
     }
     cout << endl;
  }
  
  
  
  return 0;
}