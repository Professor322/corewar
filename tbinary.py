import argparse
from tcorewar import experience_to_run

parser = argparse.ArgumentParser()
parser.add_argument('champs', nargs=2, help="python tbinary.py Asombra.cor Explosive_Kitty.cor")
parser.add_argument('-t', '--timeout', help="timeout", type=int, default=None)
args = parser.parse_args()
champ_a = args.champs[0]
champ_b = args.champs[1]
timeout = args.timeout

experience_to_run(champ_a, champ_b, timeout)

#🏁#python tbinary.py comment_len_2048.cor Wall.cor
#⚠️#python tbinary.py Asombra.cor Varimathras.cor
#🏁#python tbinary.py Bazou.cor st_next.cor
#🏁#python tbinary.py Kappa.cor darksasuke.cor
