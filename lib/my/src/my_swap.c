void		my_swap(int *ptr_a, int *ptr_b)
{
  int		tmp;

  tmp = *ptr_a;
  *ptr_a = *ptr_b;
  *ptr_b = tmp;
  return ;
}
