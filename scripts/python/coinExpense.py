#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Created on Apr 2, 2011

@author: liushaohui
'''
import MySQLdb
import sys

mysqlcon = MySQLdb.connect(host="localhost", user="root", passwd="wobushihuairen", db="qq_data_analysis", port=3306)

def split(line, n):
    return list(line[k:k + n] for k in xrange(0, len(line), n))

def splitStat(log):
    record = log.split('|')
    record[0] = record[0][0:10] + " " + record[0][11:19];
    return record

def scale(conn, sql):
    cursor = conn.cursor()
    cursor.execute("SET NAMES utf8")
    cursor.execute(sql)
    table = cursor.fetchall()
    return table[0][0]

def scaleInsert(conn, sql):
    cursor = conn.cursor()
    cursor.execute("SET NAMES utf8")
    cursor.execute(sql)
    conn.commit()
    cursor.close()
    
# 获取是否是第一消费的标记
def getInsertFlag(record):
    countsql = "SELECT count(*) FROM coin_expense_record WHERE user_id=" + record[9] + " and first =1 "; 
    first = scale(mysqlcon, countsql)
    if first > 0:           
        countTimeSql = "SELECT count(*) FROM coin_expense_record WHERE user_id = " + \
        record[9] + " and first = 1 and date(add_time)=date(\"" + record[0] + "\")"
        #record[9] + " and first = 1 and abs(time_to_sec(timediff(add_time,\"" + record[0] + "\"))) < 300"
        timegap = scale(mysqlcon, countTimeSql);
        if timegap > 0:
            return "1"
        else:
            return "0"
    else :
        return "1"
    
def insertToDB(record, flag):
    insertsql = "insert into coin_expense_record(action, bid, bname, coin, add_time, user_id, user_level, user_cash, user_coin,first) \
        values('" + record[3] + "','" + record[4] + "','" + record[5] + "','" + record[7] + "','" + record[0] + "','" + record[9] + "','" \
    + record[10] + "','" + record[13] + "','" + record[14] + "','" + flag + "')"
    #print insertsql
    scaleInsert(mysqlcon, insertsql)
    
if __name__ == '__main__':
    #input = "2011-04-01-23:53:59|worldStat|incomeRecord|help|2|帮助好友清理|1|1|100|10068593|36|0|301002|17358114|0".decode('utf8');
    for input in sys.stdin:  
        if isinstance(input, basestring):
            record = splitStat(input);
            if record[7] > "0":
                flag = getInsertFlag(record);
                insertToDB(record, flag);
