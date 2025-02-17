/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpoka <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:50:46 by vpoka             #+#    #+#             */
/*   Updated: 2024/09/30 13:08:23 by vpoka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of words in a string based on a delimiter.
 *
 * This function takes a string and a delimiter character as input and counts
 * the number of words in the string. The words are separated by the delimiter
 * character.
 *
 * @param s The string to count the words in.
 * @param c The delimiter character.
 * @return The number of words in the string.
 */
static int	count_words(char const *s, char c)
{
	int	word_counter;
	int	new_word;
	int	pos;

	word_counter = 0;
	pos = 0;
	new_word = 1;
	while (s[pos])
	{
		if (s[pos] == c)
		{
			while (s[pos] == c)
				pos++;
			new_word = 1;
		}
		if (new_word == 1 && s[pos])
		{
			word_counter++;
			new_word = 0;
		}
		if (s[pos])
			pos++;
	}
	return (word_counter);
}

/**
 * @brief Allocates memory for a word in a string and updates the word length.
 *
 * This function is used to allocate memory for a word in a string,
 *  given a delimiter character.
 * It also updates the word length by reference.
 *
 * @param s The string containing the word.
 * @param c The delimiter character.
 * @param word_len A pointer to the variable storing the word length.
 * @return A pointer to the allocated memory for the word.
 */
static char	*allocate_word(char **s, char c)
{
	char	*start;
	char	*new_word;
	int		word_len;

	while (**s == c)
		(*s)++;
	start = *s;
	word_len = 0;
	while (**s && **s != c)
	{
		word_len++;
		(*s)++;
	}
	new_word = malloc((word_len + 1) * sizeof(char));
	if (!new_word)
	{
		return (NULL);
	}
	ft_strlcpy(new_word, start, word_len + 1);
	return (new_word);
}

/**
 * @brief Frees the memory allocated for the result array.
 *
 *
 * This function is responsible for freeing the memory allocated
 *  for the result array used in the `ft_split` function.
 *
 * @param res The result array to be freed.
 * @param words The number of words in the result array.
 */
static void	free_memory(char **result, int words)
{
	int	pos;

	pos = 0;
	while (pos < words)
	{
		free(result[pos]);
		pos++;
	}
	free(result);
}

/**
 * Splits a string into an array of substrings based on a specified delimiter.
 *
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return An array of strings representing the substrings.
 */
char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		cur_str;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	cur_str = 0;
	while (cur_str < word_count)
	{
		result[cur_str] = allocate_word((char **)&s, c);
		if (!result[cur_str])
		{
			free_memory(result, cur_str);
			return (NULL);
		}
		cur_str++;
	}
	result[cur_str] = NULL;
	return (result);
}

/*#include <stdio.h>
int	main(void)
{
	//char *str = "123456789 123456789 hallo";
	//int str1 = word_length(str, ' ');
	//int str2 = word_length((str + 10), ' ');
	//int str3 = word_length((str + 20), ' ');
	//printf("Str 1: %d\nStr 2: %d\nStr 3: %d\n", str1, str2, str3);
	
	char *s = "hello!";
	char c = ' ';
	char **res = ft_split(s, c);
	while (*res)
	{
		printf("%s\n", *res);
		res++;
	}
	printf("%s\n", *res);
}*/