import os

def print_vault(vault):
    for key in vault.keys():
        print(key)
        for item in vault[key]:
            print(item)
    print()

def print_cur_vault(vault, total, idx):
    print(f"{total:{3}} -( {idx * 100 // total:{3}}% )- {idx:<{3}}", end='\t')
    for num, key in enumerate(vault.keys()):
        print(f"{num:{2}}_{len(vault[key]):<{4}}   ", end='')
    print()

def check_diff(vault, fds, cmd):
    with open('file_analysis', 'r') as diff:
        words = [ word for line in diff for word in line.split() if word.isalpha() ]
        t_words = tuple(sorted(set(words)))
        if not t_words in vault:
            vault[t_words] = [cmd]
            fds[t_words] = open(f'file_analysis_{len(vault)}', 'w')
            print('-'.join(t_words), file=fds[t_words])
            print(cmd, file=fds[t_words])
        else:
            vault[t_words].append(cmd)
            print(cmd, file=fds[t_words])

with open('file_vs_error_sh', 'r') as txt:
    lines = txt.readlines()
    total = len(lines)
    vault = dict()
    fds   = dict()
    for idx, cmd in enumerate(lines):
        cmd = cmd[:-1]
        os.system(f"{cmd} &> /dev/null") # result control and our
        os.system(f"diff control our > file_analysis")
        check_diff(vault, fds, cmd)
        print_cur_vault(vault, total, idx)
        if idx % 10 == 0:
            [fd.flush() for fd in fds.values()]
    print_vault(vault)
