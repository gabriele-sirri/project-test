import random

# DATA
# 
# bin_content = [ 13, 19, 58, 113, 257, 346, 353, 285, 197, 156, 126, 97, 109, 
#     126, 95, 102, 118, 1.5 * 108, 1.5 * 106, 1.5 * 86, 1.5 * 84, 2 * 92, 
# 	2 * 70]

bin_content = [221, 1189, 2530, 3788, 4714, 5005, 4535, 3594, 2696, 2074, 
      1680, 1465, 1306, 1217, 1189, 1127, 1078, 1534, 1452, 1410, 1285, 
	  1658, 1548] 	
	
bin_edges = [ 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5,
    7.0, 7.5, 8.0, 8.5, 9.0, 9.75, 10.5, 11.25, 12.0, 13.0, 14.0]
	
data = []

for i in range(23):
   print(i, bin_edges[i], bin_edges[i+1], int(bin_content[i]))
   for x in range(int(bin_content[i])):
      data.append( random.uniform(bin_edges[i], bin_edges[i+1]))

print("n events: ", len(data))
	  
random.shuffle(data)

for x in data:
    print(x)

