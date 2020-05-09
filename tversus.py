import argparse
from os import listdir
from os.path import isfile, join
from tcorewar import experience_to_run

parser = argparse.ArgumentParser()
parser.add_argument('folders', nargs=2, help="python tversus.py " +
                                        "./vm_champs/team_a ./vm_champs/champs")
parser.add_argument('-t', '--timeout', help="timeout", type=int, default=None)
args = parser.parse_args()
folder_a = args.folders[0]
folder_b = args.folders[1]
timeout = args.timeout;


team_a = [f for f in listdir(folder_a) if isfile(join(folder_a, f)) and not f.startswith('.')]
team_b = [f for f in listdir(folder_b) if isfile(join(folder_b, f)) and not f.startswith('.')]
[print(item) for item in team_a]
print('\t ___      ___  ________  ')
print('\t|"  \    /"  |/"       ) ')
print('\t \   \  //  /(:   \___/  ')
print('\t  \\  \/. ./  \___  \    ')
print('\t   \.    //    __/  \\   ')
print('\t    \\   /    /" \   :)  ')
print('\t     \__/    (_______/  ')
print(f"\t\t\ttimeout={timeout}")
[print(f"\t\t\t\t{item}") for item in team_b]
print()

total_figth = len(team_a) * len(team_b)
idx = 0
vault = { "⌛️": 0, "🏁": 0, "⚠️": 0, "⛔️": 0 }
with    open("file_vs_finish", "w") as fini, \
        open("file_vs_limit", "w") as limi,  \
        open("file_vs_error", "w") as erro, \
        open("file_vs_error_sh", "w") as ersh, \
        open("file_vs_timeout", "w") as tiou:
    for champ_a in team_a:
        for champ_b in team_b:
            idx += 1
            print(f"{total_figth} - {idx:<{10}}{champ_a} vs {champ_b}")
            rls = experience_to_run(champ_a, champ_b, timeout, v_flag=15)
            to_save = f"python tbinary.py {champ_a} {champ_b}"
            if rls[0] == -2:
                print(to_save + f" -t {rls[2]}", file=tiou)
                vault["⌛️"] += 1
            elif rls[0] == 0:
                print(to_save, file=fini)
                vault["🏁"] += 1
            elif rls[0] == 1:
                print(to_save, file=limi)
                vault["⛔️"] += 1
            else:
                print(to_save, file=erro)
                print(rls[1], file=ersh)
                vault["⚠️"] += 1
            print()
            print(vault)
            print()
            if idx % 10 == 0:
                tiou.flush()
                fini.flush()
                limi.flush()
                erro.flush()
                ersh.flush()

#python tversus.py ./vm_champs/team_a ./vm_champs/team_a -t 1
#python tversus.py ./vm_champs/team_a ./vm_champs/champs -t 5
#python tversus.py ./vm_champs/team_b ./vm_champs/champs -t 5
#python tversus.py ./vm_champs/team_c ./vm_champs/champs -t 5
#python tversus.py ./vm_champs/team_d ./vm_champs/champs -t 5
#python tversus.py ./vm_champs/champs ./vm_champs/champs -t 3
