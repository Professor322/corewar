import os
import subprocess
from glob import glob
import difflib
import argparse
from typing import Optional, Dict, List, Tuple, NoReturn


def execute_2(cmd: str, input_file: Optional[str] = None,
              output_file: Optional[str] = None) -> NoReturn:
    """
    Execute bash command with subprocess,
    work with input, output redirection

    Parameters
    ----------
    cmd: str
        command for execute
    input_file: Optional[str]
        input redirection
    output_file: Optional[str]
        output redirection
    """
    if input_file:
        cat_file = subprocess.Popen(['cat', input_file],
                                    stdout=subprocess.PIPE)
        popen = subprocess.Popen(cmd.split(), stdin=cat_file.stdout,
                                 stdout=subprocess.PIPE)
    else:
        popen = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
    data = popen.communicate()
    if data[0]:
        command = data[0].decode()
        return command
    if output_file:
        if output_file.endswith("bin"):
            with open(output_file, 'wb') as f:
                f.write(data[0])
        else:
            with open(output_file, 'w') as f:
                for line in data[0].decode("UTF-8").split('\n'):
                    f.write(line)
                    f.write('\n')
    # print(f"DONE {cmd} < {input_file} > {output_file}")


def run_asm(asm_test, asm_std, champ_name):
    out_test, out_std = None, None
    name = "".join((os.path.splitext(champ_name)[0], ".cor"))
    test = execute_2(f"{asm_test} {champ_name}")
    if name in test:
        out_test = execute_2(f"xxd {name}")
    std = execute_2(f"{asm_std} {champ_name}")
    if name in std:
        out_std = execute_2(f"xxd {name}")
    print('\033[93m%s\033[0m' % "OUTPUT",test, std, sep='\t', end="\t")
    if "Writing" in std and "Writing" in test:
        if out_std == out_test:
            print("\033[92m%s\033[0m" %  "OK")
            print("_____________________________________________________________")
            return True
        else:
            print("\nDIFF TEST ASM WITH STANDART")
            for x in difflib.ndiff(out_test, out_std):
                print(x)
            print('\033[91m%s\033[0m' % "ERROR")
            print("_____________________________________________________________")
            return False
    elif "Writing" not in std and "Writing" not in test:
        print("\033[92m%s\033[0m" % "OK")
        print("_____________________________________________________________")
        return True
    print('\033[91m%s\033[0m' % "ERROR")
    print("_____________________________________________________________")
    return False


def get_champs(file_path):
    champions = []
    for root, subdirs, files in os.walk(file_path):
        for file in files:
            if file.endswith(".s"):
                # print(root, subdirs)
                if subdirs:
                    if not subdirs[0].startswith("."):
                        path = os.path.join(root, os.path.join(*subdirs), file)
                else:
                    path = os.path.join(root, file)
                #print(path)
                if path not in champions:
                    champions.append(path)
    return champions


def main():
    parse = argparse.ArgumentParser()
    parse.add_argument("champs", type=str, metavar='champs',
                       help='directory with champs')
    parse.add_argument("asm", type=str, metavar='asm',
                       help='asm for test')
    parse.add_argument("standart_asm", type=str, metavar='standart_asm',
                       help='standart asm')
    args = parse.parse_args()
    file_path = args.champs
    standart_asm = "./" + args.standart_asm
    asm = "./" + args.asm
    champions = get_champs(file_path)
    err = 0
    ok = 0
    for i, champ in enumerate(champions, start=1):
        print('\033[93m%s\033[0m' %  "TEST", '\033[93m%s\033[0m' % i, end=' ')
        if run_asm(asm, standart_asm, champ):
            ok += 1
        else:
            err += 1

    print('\033[91m%s\033[0m' % "ERROR", err, "\033[92m%s\033[0m" %  "OK", ok)


if __name__ == "__main__":
    main()
