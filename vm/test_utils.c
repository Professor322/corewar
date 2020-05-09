//
//#include "corewar.h"
//
//void	print_car(t_car *car) //
//{
//	ft_printf("🚗P\t%d | %s | pos=%-4d, carry=%d",
//			car->id + 1,
//			car->oper.f != NULL ? car->oper.name : "NULL",
//			car->pos,
//			car->carry);
//	ft_printf(" regs=[");
//	int i = -1;
//	while (++i < REG_NUMBER)
//		ft_printf("r%d %-2d, ", i+1, car->regs[i]);
//	ft_printf("]\n");
//}
//
//void	print_car_without_reg(t_car *car) //
//{
//    ft_printf("P\t%d | %4s | pos=%-4d, carry=%d",
//              car->id + 1,
//              car->oper.f != NULL ? car->oper.name : "NULL",
//              car->pos,
//              car->carry);
//}
//
//int	 countdown(int setup) {
//	static int count;
//	static int unset;
//	if (unset == 0) {
//		unset = 1;
//		count = setup;
//	}
//	if (count > 0) {
//		count--;
//		return (0);
//	}
//	return (1);
//
//}
//
//void print_bytes(t_cbox *cbox, t_car *car, int bytes_amount)
//{
//	unsigned char *arena = cbox->arena.arena;
//	int pos = car->pos;
//	for (int j = 0; j < bytes_amount; j++)
//	{
//		ft_printf("%.2x ", arena[pos +  j]);
//	}
//	ft_printf("\n");
//}
//
//int     get_fd_debug(void)
//{
//	static int fdd;
//
//	if (fdd == 0) {
//		fdd = open("debug.txt", O_WRONLY | O_CREAT, 0644);
//		if (fdd == -1) {
//			ft_printf("get_fd_debug - FAILED\n");
//			exit(1); // todo: unsafe exit
//		}
//	}
//	return fdd;
//}
//
//
//
//void	print_cars(t_cbox *cbox) {
//	int idx;
//
//	ft_printf("🏎️  🏎  ️🏎️\n");
//	idx = -1;
//	while (++idx < cbox->car_counter) {
//		print_car(((t_car **) cbox->cars->cont)[idx]);
//	}
//}
//
//void	print_eventloop(t_cbox *cbox) {
//	int idx;
//	int cycle;
//	int delta;
//
//	cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
//	ft_printf("⏱️  = %d\n", cycle);
//	idx = -1;
//	while (++idx < SIZE_OF_EVENTLOOP) {
//		if (cbox->eventloop[idx]->len) {
//			if (idx < cycle)
//				delta = SIZE_OF_EVENTLOOP - cycle + idx;
//			else
//				delta = idx - cycle;
//			ft_printf("idx = %3d [%3d]\tcont= %d --- ", delta, idx, cbox->eventloop[idx]->len/sizeof(t_pque));
//			print_car_without_reg(((t_car **) cbox->eventloop[idx]->cont)[0]);
//			ft_printf("\n");
//		}
//	}
//}
//
//void	print_cur_eventloop(t_cbox *cbox) {
//	int idx;
//	int cycle;
//	int car;
//	int delta;
//
//	cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
//	ft_printf("⏳  = %d\n", cycle);
//	idx = -1;
//	while (++idx < SIZE_OF_EVENTLOOP) {
//		if (cbox->eventloop[idx]->len) {
//			if (idx < cycle)
//				delta = SIZE_OF_EVENTLOOP - cycle + idx;
//			else
//				delta = idx - cycle;
//			car = -1;
//			while (++car < cbox->eventloop[idx]->len/sizeof(t_pque)) {
//				if (((t_car *) (((t_pque *) cbox->eventloop[idx]->cont)[car].data))->id == 546) {
//					ft_printf("idx = %3d [%3d]\tcont= %d --- ", delta, idx, cbox->eventloop[idx]->len/sizeof(t_pque));
//					print_car_without_reg(((t_pque *) cbox->eventloop[idx]->cont)[car].data);
//					ft_printf("\n");
//				}
//			}
//		}
//	}
//}
//
//void	print_full_eventloop(t_cbox *cbox) {
//	int idx;
//	int cycle;
//	int delta;
//	int car;
//
//	cycle = cbox->cycle_counter % SIZE_OF_EVENTLOOP;
//	ft_printf("⏱️  = %d\n", cycle);
//	idx = -1;
//	while (++idx < SIZE_OF_EVENTLOOP) {
//		if (cbox->eventloop[idx]->len) {
//			if (idx < cycle)
//				delta = SIZE_OF_EVENTLOOP - cycle + idx;
//			else
//				delta = idx - cycle;
//			car = -1;
//			while (++car < cbox->eventloop[idx]->len/sizeof(t_pque)) {
//				ft_printf("idx = %3d [%3d]\tcont= %d --- ", delta, idx, cbox->eventloop[idx]->len/sizeof(t_pque));
//				print_car_without_reg(((t_pque *) cbox->eventloop[idx]->cont)[car].data);
//				ft_printf("\n");
//			}
//			ft_printf("\n");
//		}
//	}
//}