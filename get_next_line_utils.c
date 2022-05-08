/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgastal- <fgastal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:36:24 by fgastal-          #+#    #+#             */
/*   Updated: 2022/05/09 00:40:33 by fgastal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" // Inclusão do header

size_t	ft_strlcpy(char *dst, char *src, size_t size) // Função de cópia de uma string source(src) terminada em nulo para o fim da destiny(dst).
{
	size_t	i; // Declaração de uma variável i, do tipo size_t

	if (!dst || !src) // Se a destiny ou a source não existirem
		return (0); // Retorna zero
	else if (!size) // Enquanto a variável size não existir
		return (ft_strlen(src)); // Iremos ter como retorno o valor de retorno da função strlen, com a string de origem como parâmetro (aqui temos recursividade)
	i = 0; // Inicializando-se i como zero
	while (src[i] && i < (size - 1)) // Enquanto o i na string de origem não chegar ao fim e o i for menor que o valor de size (total) - 1 ('\0')
	{
		dst[i] = src[i]; // O valor de i na destiny tem que ser igual ao valor de i na source (está copiando de uma para a outra)
		i++; // Incrementar o valor de i
	}
	dst[i] = '\0'; // Quando o i na destiny chegar no caractere de fim de linha
	return (ft_strlen(src)); // Retornar o valor de retorno presente em ft_strlen
}

char	*verif(char *s)
{
	int		i; // Declaração da variável i
	char	*tmp; // Declaração da variável temporária tmp

	i = 0; // Inicializando-se i igual a zero
	while (s[i] != '\n' && s[i]) // Enquanto o i na string s não chegar em '\n' e '\0'
		i++; // Incrementar o valor de i
	if (s[i] == '\0') // Quando o i encontrar o valor de '\0'
	{
		free(s); // Liberar a memória alocada na string s
		return (NULL); // Retornar nulo
	}
	tmp = malloc((ft_strlen(s) - i) + 1); // Se não chegar em '\n', alocar memória para a variável temporária, com tamanho da string total - i ('\n) e + 1 ('\0')
	if (!tmp) // Se a temporária não existir (não houver nada armazenado lá dentro)
		return (NULL); // Retornar nulo
	ft_strlcpy(tmp, s + i + 1, ft_strlen(s) - i + 1); // Se ela existir, fazer a função de cópia com os parâmetros indicados
	free(s); // Liberar a memoria alocada em s após isso
	return (tmp); // Retornar o valor da temporária
}

size_t	ft_strlen(const char *str) // Função de determinação de tamanho de uma string
{
	size_t	i; // Declarando-se a variável i

	i = 0; // Inicializando-se em zero
	if (!str) // Enquanto a string não existir
		return (0); // Retornar zero
	while (str[i] != '\0') // Quando i, que percorreu a string, não chegar no caractere nulo final
		i++; // Contador em i
	return (i); // Retornar o valor de i quando encontrar o caractere nulo final
}

char	*ft_strnldup(char *s1) // Função de duplicação de duas strings, com recursividade (ft_strlcpy)
{
	char	*str; // Declaração de uma variável str
	size_t	i; // Declaração de um contador i

	i = 0; // Inicializando a variável i em zero
	if (!s1) // Se a string original não existir
		return (0); // Retornar zero
	while (s1[i] && s1[i] != '\n') // Enquanto o i na string original não chegar no fim '\0' e o i não for o caractere '\n'
		i++; // Contador em i
	if (s1[i] == '\n') // Se o i encontrar o '\n'
		str = (char *)malloc(sizeof(char) * (i + 2)); // Alocar memória em str (string duplicada) para o valor em bytes de i + 2 bytes;
	else
		str = (char *)malloc(sizeof(char) * (i + 1)); // Se não encontrar o '\n', alocar apenas para o valor em bytes de i + 1 byte;
	if (!str) // Se a string duplicada não existir
		return (NULL); // Retornar nulo (condição de erro)
	ft_strlcpy(str, s1, i + 2); // Porém, se a string duplicada existir, usaremos a função de cópia de uma string, com os determinados parâmetros
	if (str[0] == '\0') // Se a casa inicial [0] da string duplicada for '\0'
	{
		free (str); // Liberar a memória alocada na string duplicada
		return (NULL); // e retornar nulo
	}
	return (str); // Se a casa inicial [0] da duplicada não for '\0', retornar então o valor presente em str
}

char	*ft_strjoin(char *s1, char *s2) // Função para unir duas string s1 e s2
{
	char	*str; // Declaração da variável temporária str
	size_t	i; // Declaração da variável temporária str
	size_t	j; // Declaração da variável j

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	// Alocação de memória para str, de acordo com o tamanho das duas strings s1, s2 e +1 por causa do '\0'
	if (!str) // Se a string str não existir
		return (NULL); // Retornar nulo
	i = 0; // Inicializando-se i em zero
	j = 0; // Inicializando-se j em zero
	while (s1[i]) // Enquanto o i percorrendo s1 não chegar no fim
	{
		str[j++] = s1[i]; // o j (incrementado) presente na string str tem que ser igual ao valor de i presente na string s1
		i++; // Incrementar também o valor de i
	}
	i = 0; // Considerando-se que o valor de i seja zero
	while (s2[i]) // Se o i na string s2 não chegar ao fim
	{
		str[j++] = s2[i]; // O valor de j (incrementado) na string temporária tem que ser igual ao valor de i na string s2
		i++; // Incrementar também o valor de i
	}
	str[j] = 0; // Se o valor de j na string temporária str for igual a zero (quando terminar a junção)
	return (str); // Retornar o valor de str (temporária, com as duas strings unidas)
}
