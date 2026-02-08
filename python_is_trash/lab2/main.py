def file(file, x):
    with open (file, "r") as f:
        data = f.readlines()
    data_float = [float(x) for x in data]


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


    fa = open(f"out_yc-{x}.dat","w")
    fa.write(f"Mean: {mean}\n")
    fa.write(f"Max: {max_val}\n")
    fa.write(f"Min: {min_val}\n")
    fa.write(f"Median: {median}\n")

for x in range (1,9 + 1):
    file(f"yc-{x}.dat", x)
