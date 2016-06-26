int		my_power(const int nbr, int power)
{
  if (power > 0)
    return (nbr * my_power(nbr, power - 1));
  else if (power == 0)
    return (1);
  return (0);
}
