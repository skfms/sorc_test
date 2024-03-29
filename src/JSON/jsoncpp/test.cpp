#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

#include "json/json.h" 

#include "./../../common/sutil.h" 

using namespace std;

void test1(Json::Value);
void test2(Json::Value);
void test3(Json::Value);
void test4(Json::Value);

void test5();

int main() 
{ 
	string s = csutil::io_readfile("test.json");
	
	Json::Value root;
	Json::Reader reader;
	
	reader.parse(s, root);
	
	//test4(root);
	
	test5();
	
	return 0; 
}

void test1(Json::Value v_root)
{
	printf("[%s] : %s\n", "name", v_root["name"].asString().c_str());
};


void test2(Json::Value v_root)
{
	Json::Value skills = v_root["skills"];
	
	printf("skills : ");
	for(int n=0; n<skills.size(); n++)
	{
		printf("%s ", skills[n].asString().c_str());
	};
	printf("\n");
};


void test3(Json::Value v_root)
{
	Json::Value skills = v_root["skills"];
	
	printf("skills : ");
	for(Json::ValueIterator it=skills.begin(); it != skills.end(); it++)
	{
		printf("%s ", (*it).asString().c_str());
	};
	printf("\n");
};


void test4(Json::Value v_root)
{
	string s = "city";
	
	if(v_root.isMember(s))
	{
		printf("city : %s\n", v_root[s].asString().c_str());
	};
};


void test5()
{
	char buf[100];
	
	Json::Value root;
	
	for(int n=0; n<3; n++)
	{
		Json::Value section;
		
		sprintf(buf, "section %d", n+1);
		section["name"] = buf;
		sprintf(buf, "data %d", n+1);
		section["data"] = buf;
		
		root["section"].append(section);
	};
	
	for(int n=0; n<5; n++)
	{
		root["array"].append(n+1);
	};
	
	Json::StyledWriter writer;
	string s = writer.write(root);
	
	printf("%s\n", s.c_str());
};
