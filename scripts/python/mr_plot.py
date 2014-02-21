import math
import numpy as np
import matplotlib.pyplot as plt

def array_log10(data):
    x = []
    for s in data:
        x.append(math.log10(float(s) + 1))
    return x

def task_analysis(time_range, mapper, shuffler, reducer):
    plt.figure()
    # plt.xlim(0,500)
    # plt.ylim(0,4)
    time = [i * 1.0 for i in range(time_range)]
    x = array_log10(mapper)
    y = array_log10(shuffler)
    z = array_log10(reducer)
    plt.plot(time, x)
    plt.plot(time, y)
    plt.plot(time, z)
    plt.ylabel('Number of Tasks')
    plt.xlabel('Time Unit:s')
    plt.title('Timing Chart of Mapreduce Task')
    plt.legend(('Map Task', 'Shuffle Task', 'Reduce Task'), 'upper right', shadow=True)
    plt.grid(True)
    plt.savefig("task-analysis.png")

def start_finish_analysis(time_range, map_start, shuffle_start, reduce_start, key):
    plt.figure()
    time = [i * 1.0 for i in range(time_range)]
    plt.plot(time, map_start)
    plt.plot(time, shuffle_start)
    plt.plot(time, reduce_start)
    plt.ylabel('percent of Tasks')
    plt.xlabel('Time Unit:s')
    plt.title(key + " percent analysis")
    plt.axis([0, time_range, 0, 1.4])
    plt.legend(("Map Task " + key + " percent", "Shuffle Task" + key + " percent", \
                "Reduce Task " + key + "percent"), loc=1, shadow=True)
    plt.grid(True)
    plt.savefig("mapreduce-task-" + key + "-precent.png")

def task_time_dist(x, y, title, filename):
    plt.figure()
    plt.bar(x, y) 
    plt.ylabel('percent of Tasks')
    plt.xlabel('task run use Time Unit:s')
    plt.title(title)
    axisX_right = np.max(x) * 1.1
    axisY_right = np.max(y) * 1.1 
    plt.axis([0, axisX_right, 0, axisY_right])
    plt.grid(True)
    #plt.show()
    plt.savefig(filename)

def reducer_shuffler_task_analysis(time_range, reduce_id, shuffler_tasks):
    plt.figure()
    index = 0
    last = []
    for task in shuffler_tasks:
        s = task.run_start_time
        t = task.run_finish_time
        x = [i + s for i in range(t - s + 1)]
        flag = False
        for i in range(index) :
            if s >= last[i] :
                y = [k * 0 + i + 1 for k in range(t - s + 1)]
                plt.plot(x, y)
                last[i] = t
                flag = True
                break
        if flag == False:
            index = index + 1
            last.append(0)
            y = [k * 0 + index for k in range(t - s + 1)]
            plt.plot(x, y) 
            last[index - 1] = t
    plt.title('reduce '+ str(reduce_id) + " running shuffle task")
    plt.grid(True)
    plt.savefig("reduce-" + str(reduce_id) + "-shuffler-task.png")

def reducer_shuffle_task_num_analysis(reduce_id, time_range, shuffler_task_count):
    plt.figure()
    plt.plot(xrange(time_range), shuffler_task_count)
    plt.title("reducer: " + str(reduce_id) + " shuffle task num")
    plt.ylabel('num of requests')
    plt.xlabel('Time Unit:s')
    axisY_right = np.max(shuffler_task_count) * 1.1 
    plt.axis([0, time_range, 0, axisY_right])
    plt.savefig("reduce-" + str(reduce_id) + "-shuffle-task-num.png")
    
def reducer_request_analysis(reduce_id, time_range, request_count):
    plt.figure()
    plt.plot(xrange(time_range), request_count)
    plt.title("reducer: " + str(reduce_id) + " seed shuffle request num")
    plt.ylabel('num of requests')
    plt.xlabel('Time Unit:s')
    axisY_right = np.max(request_count) * 1.1 
    plt.axis([0, time_range, 0, axisY_right])
    plt.savefig("reduce-" + str(reduce_id) + "-request.png")

def map_request_analysis(map_id, time_range, request_count):
    plt.figure()
    plt.plot(xrange(time_range), request_count)
    plt.title("map: " + str(map_id) + "need handle time-request")
    plt.ylabel('num of requests')
    plt.xlabel('Time Unit:s')
    axisY_right = np.max(request_count) * 1.1 
    plt.axis([0, time_range, 0, axisY_right])
    plt.savefig("map-" + str(map_id) + "-request.png")



