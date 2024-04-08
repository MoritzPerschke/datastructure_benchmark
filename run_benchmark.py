import subprocess
import json

ratios = [
    (0, 100),
    (1, 99),
    (10, 90),
    (50, 50),
]

elem_sizes = [
    8,
    512,
    8000000,
]

elem_num = [
    10,
    1000,
    100000,
    10000000,
]

# times = {
#     "elem_size" :{
#         "elem_num" : {
#             "ratio" : {
#                 "operations" : operations,
#                 "times" : time
#             }
#         }
#     }
# }

times = {}
for size in elem_sizes:
    num_time = {}
    for num in elem_num:
        ratio_time = {}
        for ratio in ratios:
            if (size * num > (elem_sizes[2] * elem_num[3])):
                break
            run = subprocess.run(f"srun --time 60 build/benchmark {ratio[0]} {ratio[1]} {size} {num} array", shell=True, stderr=subprocess.PIPE).stderr.decode()
            print(f'Ratio: {ratio}, #elements: {num}, element size: {size}')
            ratio_time[f"{ratio}"] = json.loads(run)
        num_time[f'{num}'] = ratio_time
    times[f'{size}'] = num_time
    print(json.dumps(times, indent=4))

with open('array_times.json', '+x') as outfile:
    outfile.write(json.dumps(times, indent=4))
