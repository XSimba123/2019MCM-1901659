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
int state1[Size] = { 0 }, state2[Size] = { 0 };

double similarity(int state1[], int state2[],int time) {
	double count = 0;
	for (int i = 0; i < Size; i++) 
		if (state1[i] == state2[i])count++;
	double ratio = count / Size;
	//cout <<time<<" times: "<< ratio * 100 << "%" << endl;
	return ratio;
}
double each_row(int row) {
	double sum_dist = 0;
	for (int i = 0; i < Size; i++) if(i!=row) sum_dist += 1 / arr[row][i];
	return sum_dist;
}
double self_change(int state_num) {
	/*double Rand = (rand() % 10000) / 200000;//宽度0.05
	switch (state_num) {
	case 0: {return Rand+0.1; break;}
	case 1: {return Rand+0.075; break; }
	case 2: {return Rand-0.05; break; }
	case 3: {return Rand-0.075; break; }
	case 4: {return Rand-0.1; break; }
	}
	*/
	/*switch (state_num)
	{
	case 0: {return 0.1; break; }
	case 1: {return 0.075; break; }
	case 2: {return 0.05; break; }
	case 3: {return - 0.075; break; }
	case 4: {return - 0.1; break; }
	}*/
	return 0;
}
void fun(int state1[]) {
	int _sign=0;

	int state_temp[Size];
	for (int i = 0; i < Size; i++)state_temp[i] = state1[i];

	double prob=0,Rand=0,numerator=0;
	int count3 = 0;
	for (int i = 0; i < Size; i++) {
		numerator = 0;
		for (int k = 0; k < Size; k++) {
			if (k != i)
			{
				//if (state1[k] > state1[i])prob += 1/88.0 / arr[i][k];
				//numerator += 1 / arr[i][k] * (state1[k] - state1[i]) / abs(state1[k] - state1[i]);
				numerator += 1 / arr[i][k] * (state1[k]>state1[i]?(state1[k] - state1[i]):0);
			}
		}
		prob = numerator / each_row(i) / 4;
	  	prob += 2*self_change(state1[i]);// cout << "self:"<<prob << endl;
		//prob = numerator /each_row(i)/40;
		//cout << "("<<prob << ") ";
		//prob += (double)(4 - state1[i]) / 160;
		//cout << (double)(4 - state1[i]) / 160 << " //";
		//cout << "sign" << " "<<_sign << endl;
		if (prob != 0)_sign = prob / abs(prob);
		prob = abs(prob);
		Rand= (rand() % 10000)*0.0001; //cout << "rand:" << Rand << endl;
		// cout<< numerator << " " << each_row(i) << " " << prob <<" " << Rand << " " << state1[i] ;
		if (Rand < prob) {//&& state1[i] + _sign >= 0 && state1[i] + _sign <= 4
			state_temp[i] += _sign;
			count3++;
		}
		//if (state_temp[i] > 4)state_temp[i] = 4;
		//cout << " " << state1[i];
		//Rand = (rand() % 10000)*0.0001;
		if (state_temp[i] > 4)state_temp[i] = 4;
		//cout << " " << state1[i] << endl;
	}
	//cout << "变化个数:"<<count3 << ";相似度：";
	for (int i = 0; i < Size; i++)state1[i] = state_temp[i];
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
			//cout << "处理之后的字符串 ：" << county_number[temp] << "\t" << state1[temp] << "\t" << state2[temp] << endl;
		}
		temp++;
	}
	/*
	FILE * recv ;
	fopen_s(&recv,"new1.csv","r");
	int temp = -1;
	int bin1, bin2, bin3;
	while (1) {
		if(temp==-1)fscanf_s(recv, "%d,%d,%d", &bin1,&bin2,&bin3);
		else fscanf_s(recv, "%d,%lf,%lf",&county_number[temp],&state1[temp],&state2[temp]);
		temp++;
		if (temp==Size)break;
	}
	for (int i = 0; i < Size; i++)
		cout << county_number[i] << "," << state1[i] << "," << state2[i] << endl;
	*/
	/*
	ifstream fin("geo_info.csv"); //打开文件流操作
	temp =0;
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

			county_number[temp] = stringToNumber(Trim(fields[0])); //清除掉向量fields中第一个元素的无效字符，并赋值给变量name
			state1[temp] = stringToNumber(Trim(fields[1]));//清除掉向量fields中第二个元素的无效字符，并赋值给变量age
			state2[temp] = stringToNumber(Trim(fields[2])); //清除掉向量fields中第三个元素的无效字符，并赋值给变量birthday
															//cout << "处理之后的字符串 ：" << county_number[temp] << "\t" << state1[temp] << "\t" << state2[temp] << endl;
		}
		temp++;
	}
	*/
	
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
	
	/*
	for (int i = 0; i < Size; i++) {
		for (int k = 0; k < Size; k++) {
			if (i != k && arr[i][k] == 0){cerr << "err";
			cout << i<<" "<<k<<" "<<arr[i][k] << " ";}
		}
		cout << endl;
	}
	cout << endl << endl;
	*/
	//for (int i = 0; i < Size; i++) 	cout << jing[i] << " " << wei[i] << endl
	cout << "初始相似度" << similarity(state1, state2, 0) << endl;
	int temp2; int times = 0;
	set<double> ratio_set;
	map<double, int> ratio_map;
	while (1) {
		times = 0;
		while (times < 10000) {
			fun(state1);
			//cout<<similarity(state1, state2, times)<<endl;
			times++;

			//double Rand = (rand() % 1000)*0.001;
			//ratio_set.insert(similarity(state1, state2, times));
			ratio_map.insert(make_pair(similarity(state1, state2, times), times));
			//cout<<"零"<<t[0]<<"一"<<t[1]<<"二"<<三四"
		}
		for (auto i : ratio_map)cout << i.first << " at " << i.second << " round" << endl;
		cin >> temp2;
		ratio_map.clear();
	}
	//for (auto i : ratio_set)cout << i << " ";
	/*
	cout << endl;
	for (int i = 0; i < Size; i++)cout << jing[i] << endl;
	cout << "   " << endl;
	for (int i = 0; i < Size; i++)cout << wei[i] << endl;
	*/

	system("pause");
	
}
