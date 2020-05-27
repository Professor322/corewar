import os
import time
import math

limit_dump  = 999999
target_dump = 8000
path_org    = "./org_corewar"
path_our    = "../corewar"
path_champ  = "champs/"
v_flag      = 14

def create_cmd(champ_a, champ_b, dump=None, is_org=True, v_flag=14):
    cmd = f"{path_org}" if is_org else f"{path_our}"
    cmd += f" {path_champ}{champ_a} {path_champ}{champ_b}"
    if v_flag:
        cmd += f" -v {v_flag}"
    if dump != None:
        cmd += f" -d {dump}" if is_org else f" -dump {dump}"
    return cmd

#https://stackoverflow.com/questions/3346430/
#what-is-the-most-efficient-way-to-get-first-and-last-line-of-a-text-file
def read_last(fname):
    try:
        with open(fname, "rb") as f:
            first = f.readline().decode()[:-1]
            f.seek(-2, os.SEEK_END)
            while f.read(1) != b"\n":
                f.seek(-2, os.SEEK_CUR)
            last = f.readline().decode()[:-1]
            return last
    except:
            return None

def run_experience(champ_a, champ_b, dump, v_flag=14):
    file_out_org = "file_out_org"
    file_out_our = "file_out_our"
    file_out_diff = "file_out_diff"
    to_run_org = create_cmd(champ_a, champ_b, dump, v_flag=v_flag)
    to_run_our = create_cmd(champ_a, champ_b, dump, is_org=False, v_flag=v_flag)

    os.system(f"{to_run_org} > {file_out_org}")
    os.system(f"{to_run_our} > {file_out_our}")
    os.system(f"diff {file_out_org} {file_out_our} > {file_out_diff}")

    if os.stat(file_out_diff).st_size != 0: # diff_out is NOT Empty
        return -1
    elif read_last(file_out_org) and "has won" in read_last(file_out_org):
        return 0
    else:
        return 1

def extensible_binary_search(champ_a, champ_b, timeout=None, v_flag=14):
    low = 0
    hgh = target_dump
    cur = hgh
    memory = None
    last_bad = None
    interval = ""
    delta = 0
    while memory != cur:
        memory = cur
        start_time= time.perf_counter()
        rlt = run_experience(champ_a, champ_b, cur, v_flag)
        end_time = time.perf_counter()
        if timeout:
            delta = end_time - start_time
            interval = f"\t{round(delta, 3)}"
        if rlt > 0 and cur == limit_dump:
            print(f"{cur}\t- diff   ⛔️" + interval)
            return (1, cur, math.ceil(delta))
        elif rlt > 0 and cur == hgh:
            print(f"{cur}\t- diff   ♐️" + interval)
            low = hgh
            hgh = 2*hgh if 2*hgh < limit_dump else limit_dump
            cur = hgh
        elif rlt > 0:
            print(f"{cur}\t- diff   ✅" + interval)
            low = cur
            cur = (hgh - low) // 2 + low
        elif rlt < 0:
            print(f"{cur}\t- diff   ⚠️" + interval)
            last_bad = cur
            hgh = cur
            cur = (hgh - low) // 2 + low
        else:
            print(f"{cur}\t- diff   🏁" + interval)
            return (0, cur, math.ceil(delta))
        if timeout and timeout < delta:
            print(f"{memory}\t- diff   ⌛️" + interval)
            return (-2, cur, math.ceil(delta))
    return (-1, last_bad, math.ceil(delta))

def experience_to_run(champ_a, champ_b, timeout=None, v_flag=14):
    rls = extensible_binary_search(champ_a, champ_b, timeout, v_flag=v_flag)
    check_cmd = f"./test.sh -a {champ_a[:-4]} -b {champ_b[:-4]} -v {v_flag} -t 8 -f {rls[1]}"
    print(check_cmd)
    if rls[0] > 0:
        print(f"Result: ⛔️")
    elif rls[0] < -1:
        print(f"Result: ⌛️\t last_long={rls[1]}")
    elif rls[0] < 0:
        print(f"Result: ⚠️\t last_bad={rls[1]}")
    else:
        print(f"Result: 🏁")
    return (rls[0], check_cmd, rls[2])
