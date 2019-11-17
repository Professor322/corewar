//
// Created by Dacey mormont Jon connington on 16/11/2019.
//

#include "../assembler.h"


int			ft_is_numeric(char *str)
{
	while(*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

/**
 *
 * @param num число для перевода
 * @param byte  кол-во байт, которое должно занимать число
 * @return строка
 */
char		*int_to_bin(int num, int byte)
{


	return (bin_str)
}

/**
 * определяем к какому типу относится аргумента
 * является ли он меткой
 * кодируем в бинарный вид
 * @param agr аргумент команды
 * @param pos
 * @param dir_size
 * @return pointer !!
 */
t_arg		get_arg(char *arg, int pos, int dir_size)
{
	t_arg arg_parse;

	if (arg[0] == 'r')
	{
		int r_val = ft_atoi(++arg);
		printf("REG %d\n",r_val);
		arg_parse.size = 1;
		arg_parse.type = T_REG;
		arg_parse.bin = int_to_bin(r_val)
		printf("size %d\n type %u\n", arg_parse.size, arg_parse.type);
		//register
	}
	else if (arg[0] == '%')
	{
		int dir_val = ft_atoi(++arg);
		printf("DIR %d\n", dir_val);
		arg_parse.size = dir_size;
		arg_parse.type = T_DIR;
		arg_parse.bin = int_to_bin(dir_val)
		printf("size %d\n type %u\n", arg_parse.size, arg_parse.type);
		//direct
	}
	else if (arg[0] == ':')
	{
		//мы должны знать вместо какого аргумента он тут стоит
		printf("LABEL %s\n", ++arg);
		arg_parse.label->name = arg;
		arg_parse.label->position = pos;

		arg_parse.label->size = dir_size; //label
	}
	else if (ft_is_numeric(arg))
	{
		int ind_val = ft_atoi(arg);
		printf("INDIR %d\n", ind_val);
		arg_parse.type = 3;
		arg_parse.size = T_IND;
		arg_parse.bin = int_to_bin(int_val)
		printf("size %d\n type %u\n", arg_parse.size, arg_parse.type);
		//indirect
	}
	else
	{
		printf("GOVNO");
		exit(0);
	}
}

/**получаем структуру вида
 * строчка для записи команды в бинарном виде
 * позиция, начиная с которой надо записывать команду
 * три строчки, содержащие в себе аргументы
 *
 * возращаем структуру, в которой будет число, со-
 * держащие кол-во байт, занятое командой и массив струткут
 * поинетор на метки
 *
 * что происходит?
 * для каждого аргумента команды создаем структуру t_arg, которая
 * будет содержать информацию о типе, является ли это значение меткой и какой? , значение в бинарном виде, и размер??
 *
**/
t_foo		*live(t_command command)
{
//	t_foo *foo;
//
//	t_arg arg1 = get_arg(command.arg1, command.position, LIVE_T_DIR_SIZE);
//	command.position += arg1.size;
//	t_arg arg2 = get_arg(command.arg2, command.position, LIVE_T_DIR_SIZE);
//	command.position += arg2.size;
//	t_arg arg3 = get_arg(command.arg3, command.position, LIVE_T_DIR_SIZE);
//	command.position += arg3.size;
//
//	arg_to_bin(bin, arg1);
//	bin += arg1.size;
//	arg_to_bin(bin, arg2);
//	bin += arg2.size;
//	arg_to_bin(bin, arg3);
//	bin += arg3.size;
//	// собрать массив из меток
//	return foo;
}

int main(int argc, char **argv)
{
	int i;

	i = 1;
	//while (i < argc)
	get_arg(argv[1], ft_atoi(argv[2]),ft_atoi(argv[3]));
	return (0);
}