#!/usr/bin/python
import sys
import task

def get_time(string):
    hour = int(string.split(':')[0])
    minute = int(string.split(':')[1])
    second = int(string.split(':')[2])
    return hour * 60 * 60 + minute * 60 + second

def map_task(start_time, lines):
    map_dict = {}
    map_tasks = []
    for line in lines :
        time = get_time(line.split(' ')[1][0:8]) - start_time 
        if line.find("Map runner is running map task id:") != -1 :
            map_id = line[line.index("map task id:") + 13:].replace('\n', '')
            if map_id in map_dict :
                sys.stderr.write(line)
            map_dict[map_id] = time
        elif line.find("Map runner finish running map task id:") != -1 :
            map_id = line[line.index("map task id:") + 13:].replace('\n', '')
            if map_id in map_dict :
                map_task = task.MapTask()
                map_task.map_id = int(map_id)
                map_task.run_start_time = map_dict[map_id];
                map_task.run_finish_time = time
                map_tasks.append(map_task)
                del map_dict[map_id]
    return map_tasks

def shuffle_task(start_time, lines):
    shuffle_dict = {}
    shuffle_tasks = []
    for line in lines :
        time = get_time(line.split(' ')[1][0:8]) - start_time
        if line.find(" start shuffle task:") != -1 :
            reduce_id = line[line.index("reduce[") + 7:line.index("] shuffle")]
            map_id = line[line.index("map[") + 4: line.index("] expect_shard_size")]
            shuffle_id = reduce_id + "-" + map_id
            if shuffle_id in shuffle_dict :
                sys.stderr.write(line)
            shuffle_dict[shuffle_id] = time
        elif line.find("completed shuffle task:") != -1 : 
            reduce_id = line[line.index("reduce[") + 7:line.index("] shuffle")]
            map_id = line[line.index("map[") + 4: line.rindex("]")]
            shuffle_id = reduce_id + "-" + map_id
            if shuffle_id in shuffle_dict :
                shuffle_task = task.ShuffleTask()
                shuffle_task.map_id = int(map_id)
                shuffle_task.reduce_id = int(reduce_id)
                shuffle_task.run_start_time = shuffle_dict[shuffle_id]
                shuffle_task.run_finish_time = time
                shuffle_tasks.append(shuffle_task)
                del shuffle_dict[shuffle_id]
            else :
                sys.stderr.write(line)
    return shuffle_tasks

def reduce_task(start_time, lines):
    reduce_dict = {}
    reduce_tasks = []
    for line in lines :
        time = get_time(line.split(' ')[1][0:8]) - start_time
        if line.find("Reduce runner is running reduce task id:") != -1 :
            reduce_id = line[line.index("reduce task id:") + 16:].replace('\n', '')
            if reduce_id in reduce_dict :
                sys.stderr.write(line)
            reduce_dict[reduce_id] = time
        elif line.find("Reduce runner is finish reduce task id:") != -1 : 
            reduce_id = line[line.index("reduce task id:") + 16:].replace('\n', '')
            if reduce_id in reduce_dict :
                reduce_task = task.ReduceTask()
                reduce_task.reduce_id = int(reduce_id)
                reduce_task.run_start_time = reduce_dict[reduce_id];
                reduce_task.run_finish_time = time
                reduce_tasks.append(reduce_task)
                del reduce_dict[reduce_id]
    return reduce_tasks

def shuffle_task_by_reduce(reduce_num, shuffle_tasks):
    tasks = [[] for i in range(reduce_num)]
    for shuffle_task in shuffle_tasks:
        tasks[shuffle_task.reduce_id].append(shuffle_task)
    return tasks

def shuffle_task_by_map(map_num, shuffle_tasks):
    tasks = [[] for i in range(map_num)]
    for shuffle_task in shuffle_tasks:
        tasks[shuffle_task.map_id].append(shuffle_task)
    return tasks

def shuffle_request(start_time, lines):
    requests = []
    for line in lines:
        if line.find("ClientGetShardData") != -1:
            fields = line.strip().split() 
            request = task.ShuffleRequest();
            request.run_start_time = get_time(fields[1][0:8]) - start_time
            request.request_type = fields[4][-4:]
            request.reduce_id = int(fields[5])
            request.map_id = int(fields[6])
            request.worker_id = int(fields[7])
            requests.append(request)
    return requests

def shuffle_request_by_reduce(reduce_num, shuffle_requests):
    requests = [[] for i in range(reduce_num)]
    for request in shuffle_requests:
        requests[request.reduce_id].append(request)
    return requests

def shuffle_request_by_map(map_num, shuffle_requests):
    requests = [[] for i in range(map_num)]
    for request in shuffle_requests:
        requests[request.map_id].append(request)
    return requests
