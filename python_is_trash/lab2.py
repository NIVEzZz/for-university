def file_open(file):
    with open (file, "r") as f:
        data = f.readlines()
    data_float = [float(x) for x in data]
    print (data_float)
    return data_float

def file_mean_max_min_median(data_float):
    max_val = float("-inf")
    min_val = float("inf")
    sum = 0
    data_float = sorted(data_float)
    data_len = len(data_float)
    print (data_float)
    for i in range (data_len):
        num = data_float[i]
        sum += num
        if num > max_val:
            max_val = num
        if num < min_val:
            min_val = num
    if (data_len % 2 == 0):
        data_len //= 2
        median = (data_float[data_len] + data_float[data_len + 1]) / 2
    if (data_len % 2 != 0):
       data_len //= 2
       data_len -= 1
       median = data_float[data_len]

    mean = sum/len(data_float)

    return mean, max_val, min_val, median

def file_write (file):
    yc = file_open(file)
    file_mean_max_min_median(yc)
    f = open(f"out_{file}","w")
    f.write("Mean:", mean)
    f.write("Max:", max)
    f.write("Min:", min)
    f.write("Median:", median)

for x in range (1,9 + 1):
    file_write(f"yc-{x}.dat")
