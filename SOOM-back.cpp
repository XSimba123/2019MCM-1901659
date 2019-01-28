#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <fstream>
#include<cmath>
#include<map>
#include<algorithm>
#include<vector>
#include<sstream>
#include<ctime>
#include <set>
#define pi 3.1415926535
#define R 6370
#define Size 88
using namespace std;
double jing[Size] = { 0 };
double wei[Size] = { 0 };
double arr[Size][Size] = { 0 };
int county_number[Size] = { 0 };
int state1[Size] = { 0 }, state2[Size] = { 0 }, state3[Size] = { 0 }, state4[Size] = { 0 }, state5[Size] = { 0 }, state6[Size] = { 0 }, state7[Size] = { 0 };
int temp_arr[88];
double similarity(int state1[], int state2[],int time) {
	double num0 = 0,num1=0,num2=0,num3=0;
	double count0 = 0, count1 = 0, count2 = 0, count3 = 0;
	for (int i = 0; i < Size; i++)
	{
		if (state1[i] == state2[i] && state2[i] == 0)count0++;
		else if (state1[i] == state2[i] && state2[i] == 1)count1++;
		else if (state1[i] == state2[i] && state2[i] == 2)count2++;
		else if (state1[i] == state2[i] && state2[i] == 3)count3++;
		if (state2[i] == 0)num0++;
		else if (state2[i] == 1)num1++;
		else if (state2[i] == 2)num2++;
		else if (state2[i] == 3)num3++;
	}

	double ratio = (count0/num0+count1/num1+count2/num2+count3/num3 )/ 4;
	//cout <<time<<" times: "<< ratio * 100 << "%" << endl;
	return ratio;
}
double each_row(int row) {
	double sum_dist = 0;
	for (int i = 0; i < Size; i++) if(i!=row) sum_dist += 1 / arr[row][i] ;
	return sum_dist;
}
void fun(int state1[]) {
	int _sign = 0;

	int state_temp[Size];
	for (int i = 0; i < Size; i++)state_temp[i] = state1[i];

	double prob = 0, Rand = 0, numerator = 0;
	int count3 = 0;
	map<int, int> count;
	for (int i = 0; i < Size; i++) {
		numerator = 0;
		for (int k = 0; k < Size; k++) {
			if (k != i)
			{
				numerator += arr[i][k] * (state1[k] < state1[i] ? 1 : 0);
			}
		}
		prob = 1 / numerator;
		double p;
		if (prob != 0)_sign = prob / abs(prob);
		prob = abs(prob);
		Rand = (rand() % 1000000)*0.000001;
		
		if (Rand < prob) {
			count[state_temp[i]]++;
			state_temp[i] -= _sign;
			count3++;
		}
		if (state_temp[i] > 3)state_temp[i] = 3;
		if (state_temp[i] < 0)state_temp[i] = 0;
	}
	for (int i = 0; i < Size; i++){state1[i] = state_temp[i];}
}

string Trim(string& str)
{
	//str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
	str.erase(0, str.find_first_not_of(" \t\r\n"));
	str.erase(str.find_last_not_of(" \t\r\n") + 1);
	return str;
}
int stringToNumber(const string& element)
{
     int number;
     istringstream iss(element);
     iss >> number;
	 return number;
 }

int main()
{
	srand(time(NULL));

	ifstream fin("new1.csv"); //打开文件流操作
	string line;
	int temp = -1;
	while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
	{
		if (temp != -1) {
			//cout << "原始字符串：" << line << endl; //整行输出
			istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
			vector<string> fields; //声明一个字符串向量
			string field;
			while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			{
				fields.push_back(field); //将刚刚读取的字符串添加到向量fields中 
			}
			
			county_number[temp]=stringToNumber(Trim(fields[0])); //清除掉向量fields中第一个元素的无效字符，并赋值给变量name
			state1[temp] = stringToNumber(Trim(fields[1]));//清除掉向量fields中第二个元素的无效字符，并赋值给变量age
			state2[temp] = stringToNumber(Trim(fields[2])); //清除掉向量fields中第三个元素的无效字符，并赋值给变量birthday
			state3[temp] = stringToNumber(Trim(fields[3]));
			state4[temp] = stringToNumber(Trim(fields[4]));
			state5[temp] = stringToNumber(Trim(fields[5]));
			state6[temp] = stringToNumber(Trim(fields[6]));
			state7[temp] = stringToNumber(Trim(fields[7]));
			//cout << "处理之后的字符串 ：" << county_number[temp] << "\t" << state1[temp] << "\t" << state2[temp] << endl;
		}
		temp++;
	}
	
	for (int i = 0; i < Size; i++) {
		scanf_s("%lf°N %lf°W",&jing[i],&wei[i]);
		jing[i] = jing[i] * pi/180;
		wei[i] = wei[i] * pi/180;
	}
	for (int i = 0; i < Size; i++) {
		for (int k = 0; k < Size; k++) {
			if (i == k) arr[i][k] = 0;
			else arr[i][k] = R * acos(cos(jing[i]-jing[k])*cos(wei[i])*cos(wei[k])+sin(wei[i])*sin(wei[k]));
		}
	}
	
	int temp2; int times = 0;
	set<double> ratio_set;
	map<int, int> ratio_map;
	
	for (int i = 0; i < Size; i++)temp_arr[i] = state7[i];
	double max[88];
	int sum = 88;
	while (times<10000) {
		for (int i = 0; i < Size; i++)state7[i] = temp_arr[i];
		sum = 88;
		while (sum>=3) {
			fun(state7);
			sum = 0;
			for (int i=0; i < Size; i++)if (state7[i] != 0)sum++;
		}
		for (int i=0; i < Size; i++)if (state7[i] != 0)ratio_map[i]++;
		times++;
	}
	for (auto i : ratio_map)cout << i.first << " occurs " << i.second << " times" << endl;
	system("pause");
	
}
