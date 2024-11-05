#include<iostream>
#include<set>
#include<map>
#include<unordered_map>
#include<string>
#include<vector>

const int MAXN = 100005;

std::unordered_map<std::string, std::pair<int, int>> userInfo;
std::unordered_map<std::string, std::map<std::string, int>> userPoint;

int totalNumberSubmissions = 0;
int totalNumberErrorSubmissions = 0;
int submissionsForTime[MAXN];
std::vector<int> ans;

int getPointOfUserId(std::string userId){
	int ans = 0;
	if (userPoint.find(userId) != userPoint.end()){
		for (auto it: userPoint[userId]){
			ans += it.second;
		}	
	}
	return ans;
}

int convert(std::string timePoint){
	int sum = 0;
	int hh = std::stoi(timePoint.substr(0, 2));
	int mm = std::stoi(timePoint.substr(3, 5));
	int ss = std::stoi(timePoint.substr(6, 8));
	sum = hh * 3600 + mm * 60 + ss;
	return sum;
}

void inp(){
	while (true) {
		std::string userId;
		std::string problemId;
		std::string timePoint;
		std::string status;
		int point;
		std::cin>>userId;
		if (userId == "#"){
			break;
		}
		std::cin>>problemId;
		std::cin>>timePoint;
		std::cin>>status;
		std::cin>>point;
		// Update points for the problemId of userId
		// If newPoint <= point: No update, else: update
		if (userPoint.find(userId) == userPoint.end()){
			userPoint[userId][problemId] = point;
		} else if (userPoint[userId].find(problemId) == userPoint[userId].end()){
			userPoint[userId][problemId] = point;
		}		
		else {
			userPoint[userId][problemId] = std::max(userPoint[userId][problemId], point);
		}
		
		if (userInfo.find(userId) == userInfo.end()){
			userInfo[userId] = std::make_pair(point, 0);	
		} else {
			if (userPoint[userId][problemId] <= point){
				userInfo[userId].first = userInfo[userId].first - userPoint[userId][problemId] + point;
			}
		}
		
		if (status == "ERR"){
			userInfo[userId].second += 1;
			totalNumberErrorSubmissions += 1;
		}
		totalNumberSubmissions += 1;
		submissionsForTime[convert(timePoint)] += 1;
	}
	int temp = 0;
	for (int i = 1; i <= MAXN; i++){
		temp += submissionsForTime[i];
		submissionsForTime[i] = temp;
	}
}

void doQuery(){
	std::string query;
	while(true){
		std::cin>>query;
		if (query == "#"){
			break;
		}
		if (query == "?total_number_submissions"){
			ans.push_back(totalNumberSubmissions);
			continue;
		}
		if (query == "?number_error_submision"){
			ans.push_back(totalNumberErrorSubmissions);
			continue;
		}
		if (query == "?number_error_submision_of_user"){
			std::string userId;
			std::cin>>userId;
			ans.push_back(userInfo[userId].second);
			continue;
		}
		if (query == "?total_point_of_user"){
			std::string userId;
			std::cin>>userId;
			ans.push_back(getPointOfUserId(userId));
			continue;
		}
		if (query == "?number_submission_period"){
			std::string fromTime;
			std::string toTime;
			std::cin>>fromTime>>toTime;
			ans.push_back(submissionsForTime[convert(toTime)] - submissionsForTime[convert(fromTime) - 1]);
		}
	}
}

int main(int argc, const char** argv){
	std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    inp();
    doQuery();
    for (int i = 0; i < ans.size(); i++){
    	std::cout<<ans[i]<<"\n";
	}
	return 0;
}

/*
U001 P01 10:30:20 ERR 0
U001 P01 10:35:20 OK 10
U001 P02 10:40:20 ERR 0
U001 P02 10:55:20 OK 7
U002 P01 10:40:20 ERR 0
U001 P01 11:35:20 OK 8
U002 P02 10:40:20 OK 10
#
?total_number_submissions
?number_error_submision
?number_error_submision_of_user U002
?total_point_of_user U001
?number_submission_period 10:00:00 11:30:45
#
7
3
1
17
6
*/

