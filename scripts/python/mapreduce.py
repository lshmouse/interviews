import xlrd
import math
import numpy as np
import matplotlib.pyplot as plt
wb=xlrd.open_workbook('mr.xls')
wb.sheet_names()
sh=wb.sheet_by_index(0)
first_column=sh.col_values(0)
second_column=sh.col_values(1)
third_column=sh.col_values(2)
forth_column=sh.col_values(3)
plt.xlim(0,500)
plt.ylim(0,4)
x=[]
for s in first_column:
    x.append(float(s))
y=[]
for s in second_column:
    y.append(np.log10(float(s)+1))
plt.plot(x,y)
y=[]
for s in third_column:
    y.append(np.log10(float(s)+1))
plt.plot(x,y)
y=[]
for s in forth_column:
    y.append(np.log10(float(s)+1))
plt.plot(x,y)
plt.ylabel('Number of Tasks')
plt.xlabel('Time Unit:s')
plt.title('Timing Chart of Mapreduce Task')
#plt.Annotation(
plt.legend(('Map Task','Shuffle Task','Reduce Task'),'upper right',shadow=True)
plt.show()
