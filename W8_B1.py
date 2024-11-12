import os
import sys

from collections import defaultdict, deque

MAXN = 10 ** 5 + 5

userInfo = defaultdict(lambda: [0, 0])
userPoint = defaultdict(dict)

total_number_submissions = 0
number_error_submissions = 0
submissions_for_time = [0 for _ in range (MAXN)]

answers = []
# userPoint[userId][problemId] = point
# userInfo[userId] = [points, errors]
def get_point_by_userId(userId):
    points = 0
    if userId in userPoint:
        for point in userPoint[userId].values():
            points += int(point)
    return points

def convert(timePoint: str) -> int:
    hh = int(timePoint[0:2])
    mm = int(timePoint[3:5])
    ss = int(timePoint[6:8])
    return hh * 3600 + mm * 60 + ss


def inp():
    global total_number_submissions, number_error_submissions
    while True:
        line = sys.stdin.readline().strip()
        line_arr = line.split(' ')
        if line_arr[0] == '#':
            break
        userId = line_arr[0]
        problemId, timePoint, status, point = line_arr[1], line_arr[2], line_arr[3], int(line_arr[4])
        if userId not in userPoint:
            userPoint[userId][problemId] = point
        elif problemId not in userPoint[userId]:
            userPoint[userId][problemId] = point
        # If new point >= current point of userId -> update new point:
        elif point >= userPoint[userId][problemId]:
            userPoint[userId][problemId] = point

        userInfo[userId][0] = get_point_by_userId(userId)

        total_number_submissions += 1
        submissions_for_time[convert(timePoint)] += 1

        if status == 'ERR':
            number_error_submissions += 1
            userInfo[userId][1] += 1

    curr = 0
    for i in range (1, MAXN):
        curr += submissions_for_time[i]
        submissions_for_time[i] = curr


def do_query():
    global total_number_submissions, number_error_submissions
    while True:
        query = sys.stdin.readline().strip()
        if query == '#':
            break
        elif query == '?total_number_submissions':
            answers.append(total_number_submissions)
            continue
        elif query == '?number_error_submision':
            answers.append(number_error_submissions)
            continue
        elif query.startswith('?number_error_submision_of_user'):
            query_arr = query.split(' ')
            userId = query_arr[1]
            answers.append(userInfo[userId][1])
        elif query.startswith('?total_point_of_user'):
            query_arr = query.split(' ')
            userId = query_arr[1]
            answers.append(userInfo[userId][0])
        elif query.startswith('?number_submission_period'):
            query_arr = query.split(' ')
            from_time, to_time = query_arr[1], query_arr[2]
            from_time, to_time = convert(from_time), convert(to_time)
            if from_time == 0:
                answers.append(submissions_for_time[to_time])
                continue
            ans = submissions_for_time[to_time] - submissions_for_time[from_time - 1]
            answers.append(ans)
def main():
    inp()
    do_query()
    for ans in answers:
        print(ans, end = '\n')

if __name__ == '__main__':
    main()



