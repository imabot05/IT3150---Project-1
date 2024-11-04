#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<unordered_map>
using namespace std;

const int MAXN = 100005;

std::unordered_map<std::string, std::map<std::string, int>> total_consume_of_customer_shop;
std::unordered_map<std::string, int> shopRevenue;
std::vector<int> answer;

int profit[MAXN];
int totalRevenue = 0;
int totalNumberOrders = 0;

int convert(std::string timePoint){
	int hh = stoi(timePoint.substr(0, 2));
	int mm = stoi(timePoint.substr(3, 5));
	int ss = stoi(timePoint.substr(6, 8));
	return hh * 3600 + mm * 60 + ss;
}

void inp(){
    fill(profit,profit + MAXN, 0);
	while (1){
		std::string customerId;
		std::string productId;
		int price;
		std::string shopId;
		std::string timePoint;
		std::cin>>customerId;
		if (customerId == "#"){
			break;
		}
		std::cin>>productId;
		std::cin>>price;
		std::cin>>shopId;
		std::cin>>timePoint;
		totalNumberOrders += 1;
		totalRevenue += price;
		profit[convert(timePoint)] += price;
		if (shopRevenue.find(shopId) != shopRevenue.end()){
			shopRevenue[shopId] += price;
		} else {
			shopRevenue.insert({shopId, price});
		}
		
		if (total_consume_of_customer_shop.find(shopId) == total_consume_of_customer_shop.end()){
			std::map<std::string, int> mp;
			total_consume_of_customer_shop.insert({shopId, mp});
		}
		if (total_consume_of_customer_shop[shopId].find(customerId) == total_consume_of_customer_shop[shopId].end()){
			total_consume_of_customer_shop[shopId].insert({customerId, price});
		} else {
			total_consume_of_customer_shop[shopId][customerId] += price;
		}
	}
	    int cur = profit[0];
		for (int i = 1 ; i <= 100000 ; i++){
			cur += profit[i];
			profit[i] = cur;
		}
}
void getAnswer(){
	std::string query;
	while(std::cin>>query){
	if (query == "#"){
		break;
	}
	if (query == "?total_number_orders"){
		answer.push_back(totalNumberOrders);
		continue;
	}
	if (query == "?total_revenue"){
		answer.push_back(totalRevenue);
		continue;
	}
	if (query == "?revenue_of_shop"){
		std::string temp;
		std::cin>>temp;
		answer.push_back(shopRevenue[temp]);
		continue;
	}
	if (query == "?total_consume_of_customer_shop"){
		std::string temp1,temp2;
		std::cin>>temp1;
		std::cin>>temp2;
		answer.push_back(total_consume_of_customer_shop[temp2][temp1]);
		continue;
	}
	if (query == "?total_revenue_in_period"){
		std::string temp1;
		std::string temp2;
		std::cin>>temp1>>temp2;
		int res = profit[convert(temp2)] - profit[convert(temp1) - 1];
		answer.push_back(res);
		continue;
	}
}
	for (auto it = answer.begin() ; it != answer.end() ; it++ ){
		std::cout<<*it<<" ";
	}
}
int main(int argc, const char** argv){
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	inp();
	getAnswer();
	return 0;
}
