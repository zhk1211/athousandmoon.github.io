#include"testlib.h"
int main(int argc,char **argv)
{
	registerTestlibCmd(argc,argv);
	if(ouf.readInt()!=51241247) quitf(_wa,"");
	int t=ouf.readInt(),k=ouf.readInt(),n=ans.readInt();
	int s1=0,s2=0;
	while(n--)
	{
		int c1=ans.readInt(),c2=ans.readInt();
		s1+=c2; if(k<=c1) s2+=c2;
	}
	if(s1==s2&&t==5) quitf(_ok,"");
	else if(!s2||t==0) quitf(_wa,"");
	else quitp(s2*1./s1*t/5,"");
	return 0;
}