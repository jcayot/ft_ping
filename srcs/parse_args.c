//
// Created by jules on 19/11/2024.
//

#include <ft_ping.h>

int	get_num_param(char** str, int* i, int j, int* dest)
{
	if (str[*i][j + 1] == 0)
	{
		*i = *i + 1;
		if (str[*i] == NULL)
			return (INVALID_ARGUMENT);
		*dest = strict_atoi(str[*i]);
	}
	else
		*dest = strict_atoi(&str[*i][j + 1]);
	if (*dest < 1)
		return (INVALID_ARGUMENT);
	return (OK);
}

int	get_params(char **arg, int *i, t_parsed_command* dest)
{
	int	j;

	j = 1;
	while (arg[*i][j] != '\0')
	{
		if (arg[*i][j] == '?')
			dest->help = true;
		else if (arg[*i][j] == 'a')
			dest->audible = true;
		else if (arg[*i][j] == 'v')
			dest->verbose = true;
		else if (arg[*i][j] == 'q')
			dest->quiet = true;
		else if (arg[*i][j] == 'c')
			return (get_num_param(arg, i, j, &dest->count));
		else if (arg[*i][j] == 's')
			return (get_num_param(arg, i, j, &dest->size));
		else if (arg[*i][j] == 'l')
			return (get_num_param(arg, i, j, &dest->preload));
		else
			return (UNKNOWN_PARAMETER);
		j++;
	}
	return (OK);
}

int	parse_args(int argc, char* argv[], t_parsed_command* dest)
{
	int	i;

	*dest = (t_parsed_command) {NULL,false,false, false, false, 0, 0, 0};
	if (argc < 2)
		return (NO_ARGUMENT);
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && strlen(argv[i]) > 1)
		{
			if (get_params(argv, &i, dest) != OK)
				return (UNKNOWN_PARAMETER);
		}
		else
			dest->destination = argv[i];
		i++;
	}
	if (!dest->destination && !dest->help)
		return (NO_ARGUMENT);
	return (OK);
}

int p_parsing_error(const int err)
{
	if (err == NO_ARGUMENT)
		ping_error("usage error: Destination address required");
	else if (err == UNKNOWN_PARAMETER)
		ping_error("usage error: Unknown parameter");
	else if (err == INVALID_ARGUMENT)
		ping_error("usage error: Invalid argument");
	return (err);
}
