#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define fi first
#define se second
#define si size()
#define bk back()
#define popb pop_back()
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define endl "\n"
#define lb lower_bound
#define ub upper_bound
#define emp empty()
#define beg begin()
#define en end()
#define emp empty()
#define ump unordered_map
#define forl(i,a,n) for(int i=a;i<n;i++)
#define rfor(i,n,a) for(int i=n;i>=a;i--)
#define fore(i,a,n) for(int i=a;i<=n;i++)
#define len length()
double doINF = 1.0/0.0 ;
ostream_iterator <int> outp(cout," ");
inline ll modadd(ll n,ll m,ll mod){
    ll sum = ((n+m)%mod+mod)%mod;
    return sum;
} 
inline ll modsub(ll n,ll m, ll mod){
    ll diff = ((n-m+mod)%mod+mod)%mod;
    return diff;
}
inline ll modpro(ll n,ll m,ll mod){
    ll pro = ((n*m)%mod+mod)%mod;
    return pro;
}
inline ll pow(int x,int y){
    ll res = 1;
    while (y > 0) {
        if (y & 1)
            res = res * x;
        y = y >> 1;
        x = x * x;
    }
    return res;
}
inline ll powmod(ll x,ll y,ll mod){
    ll res = 1;
    while (y > 0) {
        if (y & 1)
            res = modpro(res , x,mod);
        y = y >> 1;
        x = modpro(x , x,mod);
    }
    return res;
}
//ll min(ll a, ll b){
//    if(a>b){
//        return b;
//    }
//    return a;
//}
// 
//ll max(ll a, ll b){
//    if(a>b){
//        return a;
//    }
//    return b;
//}
bool pairdec(const pair<int,int> &a,  
               const pair<int,int> &b) 
{ 		if(a.fi!=b.fi)
       	return (a.fi> b.fi);
		else return a.se>b.se;  
} 
ll power(ll x, ll y, ll mod) 
{ 
    ll res = 1; 
    x = x%mod; 
    while (y > 0) { 
        if (y & 1) 
            res = (res * x) % mod; 
  
        y = y >> 1;
        x = (x * x) % mod; 
    } 
    return res; 
} 
ll modInverse(ll a, ll mod) 
{ 
    return  powmod(a, mod - 2, mod); 
} 
ll modFact(ll n, ll mod) 
{ 
    if (n >=mod) 
        return 0; 
  
    ll result = 1; 
    for (ll i = 1; i <= n; i++) 
        result = (result * i) %mod; 
  
    return result; 
} 
//cout<<setprecision(9)<<fixed<<sum<<endl; --- precision for double numbers
//copy(v.beg,v.en,outp);
FILE* cf(const char* str)
{
	FILE* fpointer;
	fpointer=fopen(str,"w");
	return fpointer;
}
typedef struct courses
{
	string cname;
    ll sem;
	ll C;   
}course;

float conv(string str)
{
	float x=0;
	if(str=="AA" || str=="AS") x=10;
	else if(str=="AB")x=9;
	else if(str=="BB")x=8;
	else if(str=="BC")x=7;
	else if(str=="CC")x=6;
	else if(str=="CD")x=5;
	else if(str=="DD")x=4;
	return x;
}
map<ll,string>numToRom;
int main()
{
    numToRom[1]="I";
    numToRom[2]="II";
    numToRom[3]="III";
    numToRom[4]="IV";
    numToRom[5]="V";
    numToRom[6]="VI";
    numToRom[7]="VII";
    numToRom[8]="VIII";
	map<string,string>stud; //roll --> name
    map<string,course>cid;//id-->course
    map<string,map<string,string>>rgrad;// roll --> {id-->grade}
    fstream file;
    file.open("students.csv",ios::in);
    while(!file.eof())
    {
        string rnum;
		string name;
        getline(file,name,',');
        getline(file,rnum,'\n');
        if(!name.emp) stud.insert({rnum,name});
            
    }
    file.close();
    file.open("courses.csv",ios::in);
    string line;
    while(getline(file,line,'\n'))
    {
        stringstream s(line);
        vector<string>v;
        string word;
        while(getline(s,word,','))
        {
            v.pb(word);
        }
        course cr;
        string sem,id;
		string C;
        sem=v[0];
        id=v[1];
        cr.cname=v[2];
        C=v[6];
        cr.sem=stoll(sem);
        cr.C=stoll(C);
        cid.insert({id,cr});
    }
    file.close();
    file.open("grades.csv", ios::in);
    while(!file.eof())
    {
        string roll,id;
		string grade;
        getline(file,roll,',');
        getline(file,id,',');
        getline(file,grade,'\n');
        if(!roll.emp)rgrad[roll][id] = grade;
    }
    file.close();  
	auto it=stud.beg;
	vector<float>spi;
	vector<float>cpi;   
	while(it!=stud.en)
     {  
     	const char* name= (it->se).c_str();
     	spi.clear();
     	cpi.clear();
        const char* strfile=(it->fi+".txt").c_str();
        FILE* stfile=cf(strfile);
        const char* rollnum= (it->fi).c_str();
        fprintf(stfile,"Roll Number : %s\n",rollnum);
        fprintf(stfile,"Name : %s\n",name);
        fprintf(stfile,"\n");
        float stcpi=0;
        float cptot=0;
        float cpst=0;
        forl(i,1,9)
        {
        	fprintf(stfile,"\n");
        	fprintf(stfile,"Semester %s\n",(numToRom[i]).c_str());
            fprintf(stfile,"\n");
            float studt=0;
            float sttot=0;
            float stspi=0;
            fprintf(stfile,"Course Number  Course Name                                       Credits   Grade \n");
            fprintf(stfile,"-------------- ------------------------------------------------- --------- -------\n");
            for(auto iter=rgrad[it->fi].begin();iter!=rgrad[it->fi].end();iter++)
            {
                string name=iter->fi;
                name.popb;

                if(cid[name].sem == i)
                {
                    const char* code= (iter->fi).c_str();
                    const char* gr= (iter->se).c_str();
                    const char* cname= (cid[name].cname).c_str();
                	ll cred= (cid[name].C);
//  			for(i,0,9)
//                {
//                	cout<<iter->fi<<endl;
//				}
                    fprintf(stfile,"%s",code);
                    //add 14
                    fore(t,(iter->fi).len,14)fprintf(stfile," ");
                    fprintf(stfile,"%s",cname);
                    //add 48
                    fore(t,(cid[name].cname).len,48)fprintf(stfile," "); ;
                    fprintf(stfile," %lld",cred);
                    string credstr=to_string(cred);
                    
                   // cout<<"-------------------"<<endl;
                    if(credstr.len==1)
                    for(int sp=0;sp<=7;sp++)fprintf(stfile," "); 
                    else for(int sp=0;sp<=6;sp++)fprintf(stfile," ");
                    
                    
                    fprintf(stfile," %s\n",gr);
                    
                    
                    sttot+=10*cid[name].C;
                    studt+=conv(iter->se)*(cid[name].C);
                }
                     
                }
                    stspi=studt/sttot;
                    
                    cpst+=stspi*sttot;
                    cptot+=10*sttot;
                    stcpi=cpst/cptot;
                    
                    
                    cpi.push_back(stcpi*100);
                    spi.push_back(stspi*10);
                
             }
             fprintf(stfile,"\n");
             fprintf(stfile,"      ");
             forl(i,1,9)
             {
             	int l=numToRom[i].len;
             	fprintf(stfile,"%s",(numToRom[i]).c_str());
             	forl(i,l,7)fprintf(stfile," ");
			 }
            fprintf(stfile,"\n");
            fprintf(stfile,"SPI   ");
            for(int k=0;k<8;k++)
            {
                fprintf(stfile,"%0.2f",spi[k]);
                forl(j,0,3)
                fprintf(stfile," ");
            }
            fprintf(stfile,"\n");
            fprintf(stfile,"CPI   ");
            for(int k=0;k<8;k++)
            {
                fprintf(stfile,"%0.2f",cpi[k]);
                forl(j,0,3)
                fprintf(stfile," ");
            }
            fprintf(stfile,"\n");
            fprintf(stfile,"\n");
         fclose(stfile);
	it++;
     }
     return 0;
     } 