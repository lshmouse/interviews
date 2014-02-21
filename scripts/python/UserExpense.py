#! /usr/bin/env python
# -*- coding: utf8
import MySQLdb
import os
import datetime
import sys

path = os.path.dirname(sys.argv[0])

print path

title = "<tr><td>日期</td><td>总用户</td><td>日活跃</td><td>日新增</td><td>邀请成功量</td><td>第二天保留率</td><td>七天保留率</td><td>15天保留率</td><td>30天保留率</td></tr>"

def gen_insert(list):
    row = "<tr>"
    for e in list:
        row += "<td>" + str(e) + "</td>"
    row += "</tr>"
    return row

conn = MySQLdb.connect(host="10.135.140.211", user="root", passwd="wobushihuairen", db="qq", port=3306, unix_socket="/data/mysql/mysql.sock")
conn_analysis = MySQLdb.connect(host="10.135.144.123", user="root", passwd="wobushihuairen", db="qq_data_analysis", port=3306, unix_socket="/data/mysql/mysql.sock")


def scale(conn, sql):
    cursor = conn.cursor()
    cursor.execute("SET NAMES utf8")
    cursor.execute(sql)
    table = cursor.fetchall()
    return table[0][0]

today = datetime.date.today()
d = today - datetime.timedelta(days=1)

insert = "insert into user_retain_record(date,users_all,today_active,today_add,today_invite,retain_2d,retain_7d,retain_15d,retain_30d) values("
ds = "%d-%d-%d" % (d.year , d.month , d.day)
insert += "'" + str(ds) + "'"

#总用户数
all = scale(conn, "select count(*) from user_profile where state=0")
#data_row.append(all)
insert += ",'" + str(all) + "'"

#日活跃
today = scale(conn, "select count(*) from user_profile where last_login>subdate(curdate(),interval 1 day)")
#data_row.append(today)
insert += ",'" + str(today) + "'"

#日新增用户数
newusers = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 1 day) and curdate()")
#data_row.append(newusers)
insert += ",'" + str(newusers) + "'"

#邀请成功量
invitedusers = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 1 day) and curdate() and inviter >0")
insert += ",'" + str(invitedusers) + "'"

#第二天保留率
new2 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 2 day) and subdate(curdate(),interval 1 day)")
retain2 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 2 day) and subdate(curdate(),interval 1 day) and last_login>subdate(curdate(),interval 1 day)")
insert += ",'" + str(retain2 * 1.0 / new2) + "'"

#七天保留率
new7 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 7 day) and subdate(curdate(),interval 6 day)")
retain7 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 7 day) and subdate(curdate(),interval 6 day) and last_login>subdate(curdate(),interval 1 day)")
insert += ",'" + str(retain7 * 1.0 / new7) + "'"

#15天保留率
new15 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 15 day) and subdate(curdate(),interval 14 day)")
retain15 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 15 day) and subdate(curdate(),interval 14 day) and last_login>subdate(curdate(),interval 1 day)")
insert += ",'" + str(retain15 * 1.0 / new15) + "'"

#30天保留率
new30 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 30 day) and subdate(curdate(),interval 29 day)")
retain30 = scale(conn, "select count(*) from user_profile where addtime between subdate(curdate(),interval 30 day) and subdate(curdate(),interval 29 day) and last_login>subdate(curdate(),interval 1 day)")
insert += ",'" + str(retain30 * 1.0 / new30) + "'"
insert += ");"
mycursor = conn_analysis.cursor()
print insert
mycursor.execute(insert)
mycursor.close()
#提交操作
conn_analysis.commit()
conn.commit()
#关闭连接
conn_analysis.close()
conn.close()
