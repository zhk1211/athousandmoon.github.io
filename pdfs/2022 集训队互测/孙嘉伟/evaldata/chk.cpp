#include <random>
#include <string>
std::string generateToken()
{
	unsigned long long Seed = 19260817;
	std::mt19937_64 rng(Seed);
	for(int i = 1; i <= 2333; i++) rng();
	static char str[1 << 10];
	for(int i = 1; i <= 40; i++) sprintf(str + i,"%llX", (rng() & 15));
	return std::string(str + 1);
}
#include "testlib.h"
int main(int argc,char*argv[])
{
	//printf("%s\n",generateToken().c_str());
	registerTestlibCmd(argc, argv);
	std::string token_author = generateToken();
	std::string token_participant = ouf.readToken();
	if(token_author != token_participant)
		quitf(_wa,"Unauthorized output");
	std::string tResult = ouf.readToken();
	ouf.readEoln();
	std::string tMsg = ouf.readLine();
	if(tResult == "OK")
	{
		double s=ouf.readDouble();
		if(s>0.999)quitf(_ok,tMsg.c_str());
		else quitp(s,tMsg.c_str());
	}
	else if(tResult == "WA")
		quitf(_wa,tMsg.c_str());
	else quitf(_fail,"Failed to recognize verdict");
}