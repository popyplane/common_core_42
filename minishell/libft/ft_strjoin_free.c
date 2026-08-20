#include "libft.h"

static size_t	ft_count(char *s1, char *s2)
{
	size_t	count;
	size_t	total;

	if (!s1 && !s2)
		return (0);
	if (!s1 || !s1[0])
		return (ft_strlen(s2));
	if (!s2 || !s2[0])
		return (ft_strlen(s1));
	count = 0;
	total = 0;
	while (s1[count])
		count++;
	total += count;
	count = 0;
	while (s2[count])
		count++;
	total += count;
	return (total);
}

static char	*ft_catstr(char *s1, char *s2, char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		s[i] = s2[j];
		j++;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s;
	size_t	len;

	len = ft_count(s1, s2);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	ft_catstr(s1, s2, s);
	return (free(s1), free(s2), s);
}
