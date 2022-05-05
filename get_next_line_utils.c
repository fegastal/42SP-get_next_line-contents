/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgastal- <fgastal-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 21:36:24 by fgastal-          #+#    #+#             */
/*   Updated: 2022/05/05 22:01:54 by fgastal-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h" // Inclusão do header

// Nesse arquivo, teremos funções auxiliares para o arquivo get_next_line.c
// Nota-se que houveram algumas alterações em relação às mesmas funções presentes no libft, por exemplo;

// Usamos a ft_strlen quando queremos fazer a verificação do buffer:
size_t	ft_strlen(const char *str) // Nota-se que não utiliza-se um pointer na função, porque retornamos um size_t;
{
	size_t	i; // Declaração de um contador;
	char	*cp; // Declaração de contador na string de cópia;

	i = 0; // Inicializando-se com i valendo 0;
	cp = (char *)(str); // A variável de cópia assumirá o valor (com type cast) da string original;
	while (cp && *cp) // Verificação de segurança (existência);
	{
		cp++; // Contador na string de cópia;
		i++; // Contador na string original;
	}
	return (i); // Retorno do tamanho da string;
}

// Usamos a ft_memcpy para realizar a função de cópia:
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i; // Declaração ode um contador;

	if (!src && !dest) // Condição de segurança entre as duas strings;
		return (0); // Retorna zero nessa situação;
	i = 0; // Inicializando o valor de i em 0;
	while (i < n) // Enquanto o i não chegar no fim;
	{
		((char *)dest)[i] = ((const char *)src)[i]; // O contador vai andando nas mesmas posições das duas strings e vai copiando;
		i++; // Incrementa-se o contador;
	}
	return (dest); // Retorna a string de destino;
}

// Função semelhante à strcat, mas com alocação de memória:
char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i; // Declaração de contador;
	size_t	s1len; // Comprimento da str1;
	size_t	s2len; // Comprimento da str2;
	char	*ptr; // Declaração de um pointer;

	i = 0; // Inicializando o contador em 0;
	ptr = NULL; // Inicializando o contador em nulo;
	if (!s1 && !s2) // Apenas erro (condição de segurança);
		return (NULL); // Retorno de nulo;
	if (s1 && !s2) // Se a string 2 não existir;
		return (ft_strdup(s1)); // Duplicar a string 1 como retorno;
	else if (!s1 && s2) // Se a string 1 não existir;
		return (ft_strdup(s2)); // Duplicar a string 2 como retorno;
	s1len = ft_strlen(s1); // Verificando o tamanho da string 1;
	s2len = ft_strlen(s2); // Verificando o tamanho da string 2;
	ptr = (char *)malloc(sizeof(char) * (s1len + s2len + 1)); //alocando memória para a concatenação das duas strings + 1 '\0' no fim;
	if (!ptr) // Condição de existência do pointer;
		return (NULL); // Retorno de nulo;
	while (i < (s1len + s2len + 1)) // Enquanto o contador i não chegar ao fim;
		ptr[i++] = 0; // Vai incrementando o i e o pointer é igual a zero;
	ft_memcpy(ptr, s1, s1len); // Copio a string 1 inteira;
	ft_memcpy(ptr + s1len, s2, s2len); // Digo a posição final da string 1 e depois copio a partir dessa posição a string 2;
	ptr[s1len + s2len] = '\0'; // Incluo esse caractere para finalizar a string;
	return (ptr); // Retorno o valor do pointer;
}

// Função de duplicação de uma string:
char	*ft_strdup(const char *s)
{
	char	*str; // Declaração de uma variável para a string duplicada;
	int		len; // Declaração de variável que conta o tamanho;

	if (s) // Condição de existência;
	{
		len = ft_strlen(s); // Passando a função de contagem de tamanho para a variável len;
		if (!len) // Condição de existência novamente;
			return (NULL); // Retorno de nulo;
		str = (char *)malloc(sizeof(char) * (len + 1)); // Alocando memória para o tamanho todo + 1 caractere '\0' no fim;
		if (!str) // Condição de existência;
			return (NULL); // Retorno de nulo;
		ft_memcpy(str, s, len); // Uso da função de cópia para fazer a duplicação;
		*(str + len) = '\0'; // Inclusão do caractere '\0' no fim da duplicação;
		return (str); // Retorno da string duplicada;
	}
	return (NULL); // Se a string original não existir, retornar nulo;
}

// Função para encontrar um determinado caractere (no caso, '\n') em uma string:
char	*ft_strchr(const char *s, int c)
{
	char	*tmp; // Declaração de uma variável temporária;
	
	if (s) // Condição de existência da string original;
	{
		tmp = (char *)(s); // Colocamos para a temporária o que há na string original;
		while (*tmp) // Condição de existência;
		{
			if (*tmp == (char)c) // Se encontrarmos, na temporária, o caractere c especificado;
				return (tmp); // Retornamos a temporária;
			tmp++; // Incrementa a temporária;
		}
		if (*tmp == c) // Se a temporária for igual a apenas o caractere;
			return (tmp); // Retornamos a temporária;
	}
	return (NULL); // Retorna nulo caso a string original não exista;
}
