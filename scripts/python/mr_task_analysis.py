#!/usr/bin/python

import re
import sys

import mr_extract
import mr_plot

def grep(string, list):
    expr = re.compile(string)
    return filter(expr.search, list)

def get_time_range(lines):
    start_time = sys.maxint
    end_time = 0
    for line in lines : 
        time = mr_extract.get_time(line.split(' ')[1][0:8]) 
        if start_time > time :
            start_time = time
        if time > end_time :
            end_time = time
    return start_time, end_time

def count(time_range, tasks):
    A = [0 * i for i in range(time_range)]
    for task in tasks  :
        for index in range(task.run_start_time, task.run_finish_time + 1):
            A[index] = A[index] + 1
    return A

def count_start_time(time_range, tasks):
    A = [0 * i for i in range(time_range)]
    for task in tasks  :
        A[task.run_start_time] = A[task.run_start_time] + 1
    return A

def get_segs(tasks):
    A = {}
    for task in tasks  :
        seg = task.run_finish_time - task.run_start_time + 1;
        A[seg] = A.get(seg, 0) + 1 
    return A

def get_start_percent(time_range, tasks): 
    A = [i * 0 for i in range(time_range)]
    for task in tasks:      
        for time in range(task.run_start_time, time_range):
            A[time] = A[time] + 1
    for i in range(time_range):
        A[i] = A[i] * 1.0 / A[time_range - 1]
    return A

def get_finish_percent(time_range, tasks): 
    A = [i * 0 for i in range(time_range)]
    for task in tasks:      
        for time in range(task.run_finish_time, time_range):
            A[time] = A[time] + 1
    for i in range(time_range):
        A[i] = A[i] * 1.0 / A[time_range - 1]
    return A

def task_start_percent_analysis(time_range, map_tasks, shuffle_tasks, reduce_tasks):
    map_start = get_start_percent(time_range, map_tasks)
    shuffle_start = get_start_percent(time_range, shuffle_tasks)   
    reduce_start = get_start_percent(time_range, reduce_tasks)
    mr_plot.start_finish_analysis(time_range, map_start, shuffle_start, reduce_start, "start");    

def task_finish_percent_analysis(time_range, map_tasks, shuffle_tasks, reduce_tasks):
    map_start = get_finish_percent(time_range, map_tasks)
    shuffle_start = get_finish_percent(time_range, shuffle_tasks)   
    reduce_start = get_finish_percent(time_range, reduce_tasks)
    mr_plot.start_finish_analysis(time_range, map_start, shuffle_start, reduce_start, "finish");  

def normalized(array):
    all_sum = sum(array)
    for i in range(len(array)):
        array[i] = 1.0 * array[i] / all_sum
    return array


def task_run_dist_analysis(time_range, tasks, key):
    segs = get_segs(tasks)
    items = segs.keys()
    items.sort()
    x = []
    y = []
    for i in range(len(items)):
        x.append(items[i])
        y.append(segs[items[i]])
    y = normalized(y);
    mr_plot.task_time_dist(x, y, key + " running time Distribution", key + "-run-time-dist.png");

# ok
def task_analysis(time_range, map_tasks, shuffle_tasks, reduce_tasks):
    mapper = count(time_range, map_tasks);
    shuffler = count(time_range, shuffle_tasks);
    reducer = count(time_range, reduce_tasks);
    mr_plot.task_analysis(time_range, mapper, shuffler, reducer);


def get_map_task_num(map_tasks):
    map_task_num = 0
    for task in map_tasks:
        if task.map_id >= map_task_num:
            map_task_num = task.map_id + 1
    return map_task_num

def get_recduce_task_num(reduce_tasks):
    recduce_task_num = 0
    for task in reduce_tasks:
        if task.reduce_id >= recduce_task_num:
            recduce_task_num = task.reduce_id + 1
    return recduce_task_num

if __name__ == "__main__":
    lines = sys.stdin.readlines() 
    start_time, end_time = get_time_range(lines);
    time_range = end_time - start_time + 1
    # maptask
    map_tasks = mr_extract.map_task(start_time, lines)
    map_task_num = get_map_task_num(map_tasks)
    # shuffle_task
    shuffle_tasks = mr_extract.shuffle_task(start_time, lines)
    # reduce task
    reduce_tasks = mr_extract.reduce_task(start_time, lines)
    reduce_task_num = get_recduce_task_num(reduce_tasks)
    
    # shuffle request
    shuffle_requests = mr_extract.shuffle_request(start_time, lines);
    
    # figure 1
    task_analysis(time_range, map_tasks, shuffle_tasks, reduce_tasks)
    
    # figure 2, 3
    task_start_percent_analysis(time_range, map_tasks, shuffle_tasks, reduce_tasks)
    task_finish_percent_analysis(time_range, map_tasks, shuffle_tasks, reduce_tasks)
    
    # figure 4, 5, 6
    task_run_dist_analysis(time_range, map_tasks, "map")
    task_run_dist_analysis(time_range, shuffle_tasks, "shuffle")
    task_run_dist_analysis(time_range, reduce_tasks, "reduce")
   
    reduce_shuffle_tasks = mr_extract.shuffle_task_by_reduce(reduce_task_num, shuffle_tasks)

    # figure for shuffler_task client
    #for reduce_id in range(reduce_task_num):
    for reduce_id in range(2):
        tasks = reduce_shuffle_tasks[reduce_id]
        mr_plot.reducer_shuffler_task_analysis(time_range, reduce_id, tasks)
        shuffler_task_count = count(time_range, tasks)
        mr_plot.reducer_shuffle_task_num_analysis(reduce_id, time_range, shuffler_task_count);
    
    reduce_shuffle_requests = mr_extract.shuffle_request_by_reduce(reduce_task_num, shuffle_requests)
    # figure for shuffler client send request
    # for reduce_id in range(reduce_task_num):
    for reduce_id in range(2):
        tasks = reduce_shuffle_requests[reduce_id]
        request_count = count_start_time(time_range, tasks)
        mr_plot.reducer_request_analysis(reduce_id, time_range, request_count)
    
    #map_shuffle_requests = mr_extract.shuffle_request_by_map(map_task_num, shuffle_requests)
    # figure for shuffler server handle request 
    #for map_id in range(map_task_num):
    #    tasks = map_shuffle_requests[map_id]
    #    request_count = count_start_time(time_range, tasks)
    #    mr_plot.map_request_analysis(map_id, time_range, request_count)
